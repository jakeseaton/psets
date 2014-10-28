<?php
    require("../includes/config.php"); 

    // fill rows
    $rows = query("SELECT type, symbol, amount, price, time FROM history WHERE id = ?", $_SESSION["id"]);
    
    if ($rows === false)
    {
        apologize("Data Retrieval Failure");
    }
    
    // render history
    render("history_form.php", ["rows" => $rows, "title" => "Transaction History"]);

?>

