<?php

    // configuration
    require("../includes/config.php"); 

    // fill rows
    $rows = query("SELECT symbol, shares FROM portfolios WHERE id = ?", $_SESSION["id"]);

    // determine cash
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    // ensure success
    if ($rows === false || $cash === false)
    {
        apologize("Data Retrieval Failure");
    }

    // initialize positions
    $positions = [];
    
    // iterate over rows
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        
        // fill positions
        $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
        ];
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);

?>

