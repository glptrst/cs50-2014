<?php
    
    require("../includes/config.php");
    
    $username = query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
    
        //if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("../templates/change_password_form.php", ["username" => $username, "title" => "Change password"]);
    }
    
    //else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //password and confirmation have to match
        if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Passwords do not match!");
        }
    
        //query 
        query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]);
        
        //redirect to portfolio
        render("password_changed.php", ["username" => $username, "title" => "Password changed"]);
    }
    
    
    
    
    
    
    
    
    
?>
