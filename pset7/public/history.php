<?php

    require("../includes/config.php");
    
    $username = query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
    
    $history = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
    render("../templates/show_history.php", ["username" => $username, "history" => $history, "title" => "History"]);
?>
