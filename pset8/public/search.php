<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]

    //if geo is postal code
    //if ( is_numeric($_GET["geo"]) )
    
    //the following line works for postal codes
    //$places = query("SELECT * from places WHERE postal_code = ?", $_GET["geo"]);
    

    $places = query("SELECT * FROM `places` WHERE MATCH (postal_code, place_name, admin_name1, admin_code1, country_code) AGAINST (? IN BOOLEAN MODE)", $_GET["geo"]);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
