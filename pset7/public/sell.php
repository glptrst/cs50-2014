<?php
    
    require("../includes/config.php");
    
    $username = query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);

    //if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = query("SELECT * FROM portfolios WHERE id = ?", $_SESSION["id"]);
     
        //display stocks
        render("../templates/show_stocks.php", ["title" => "Stocks", "username" => $username, "rows" => $rows] );
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $shares = query("SELECT shares FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $stock = lookup($_POST["symbol"]);
        $single_price = $stock["price"];
        $total_price = ($shares[0]["shares"])*$single_price ;
        


        //update portfolios (delete symbol)
        query("DELETE FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //upadate cash in users (add price)
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $total_price, $_SESSION["id"]);
        
        //update history
        $transaction = "SELL";
        query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, ?, NOW(), ?, ?, ?)", 
                                    $_SESSION["id"], $transaction, $_POST["symbol"], $shares[0]["shares"], $total_price);
        
        //redirect to index.php
        redirect("/");
    }
?>
