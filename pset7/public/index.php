<?php

    // configuration
    require("../includes/config.php"); 
    
    $username = query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    
    $cash = query("SELECT cash FROM users WHERE ID = ?", $_SESSION["id"]);    
    
    //store symbol and share in $rows
    $rows = query("SELECT symbol, shares FROM portfolios WHERE ID = ?", $_SESSION["id"]);
    
    foreach ($rows as $row) 
    {
        $stock = lookup($row["symbol"]); 
        if ($stock !== false)
        {
             $positions[] = [
             "name" => $stock["name"],
             "price" => $stock["price"],
             "shares" => $row["shares"],
             "symbol" => $row["symbol"]
              ]; 
        }
    }

    // render portfolio
    render("portfolio.php", ["username" => $username, "cash" => $cash, "rows" => $rows, 
           "positions" => $positions, "title" => "Portfolio"]);

?>
