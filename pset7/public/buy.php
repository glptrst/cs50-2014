<?php
    
    require("../includes/config.php");
    
    $username = query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);

    //if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("../templates/buy_form.php", ["username" => $username, "title" => "Buy stocks"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //make symbol in uppercase
        $_POST["symbol"] = strtoupper ( $_POST["symbol"] );
    
        //store stock's price in $total_price
        $stock = lookup($_POST["symbol"]);
        $single_price = $stock["price"];
        $total_price = ($_POST["shares"])*$single_price;
        
        //store user's cash in $user_cash
        $user_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        //ERROR CHECKING      
        //chech if user has typed a correct number in the form
        $shares_correctness = preg_match("/^\d+$/", $_POST["shares"]);
        if ( $shares_correctness === false || $shares_correctness === 0)
        {
            apologize("Write a correct number of shares please!");          
        }
        //check if user can afford the stock?       
        else if ($user_cash[0]["cash"] < $total_price)
        {
            apologize("You don't have enough money to buy this stock!");
        }
        else
        {
            //update portfolios
            query("INSERT INTO portfolios (id, symbol, shares) VALUES (?, ?, ?)
                  ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
                  $_SESSION["id"], $_POST["symbol"], $_POST["shares"] );
        
            //update cash
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $total_price, $_SESSION["id"] );
            
            //update history
            $transaction = "BUY";
            query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, ?, NOW(), ?, ?, ?)", 
                                    $_SESSION["id"], $transaction, $_POST["symbol"], $_POST["shares"], $total_price);
            //redirect to index
            redirect("/");
        }     
    }
    
?>
      
