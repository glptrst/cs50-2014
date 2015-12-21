<?php

    // configuration
    require("../includes/config.php"); 
    
    
    
    //$rows = query("SELECT symbol, shares FROM portfolios WHERE ID = ?", $_SESSION["id"]);
    
    $cash = query("SELECT cash FROM users WHERE ID = ?", $_SESSION["id"]);
    
    dump($cash[0]["cash"]);

    //dump($_SESSION);

?>
