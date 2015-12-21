<?php
    
    //configuration
    require("../includes/config.php");
    
    $username = query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
    
    //if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("../templates/quote_form.php", ["username" => $username, "title" => "Submit quote"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $s = lookup($_POST["symbol"]);
        
        if ($s !== false)
        {
            render("../templates/show_quote.php", ["username" => $username, "title" => "Quote's price", 
                                         "formatted_price" => number_format( $s["price"] , 2, '.', '') ]);
        }
        else
        {
            apologize("Cannot find this symbol!");
        }
    }
    
?>


