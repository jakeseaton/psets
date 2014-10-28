<?php
	// configuration
    require("../includes/config.php");

	if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// validate shares
		if 	(empty($_POST["shares"]) || !is_numeric($_POST["shares"]))
		{
			apologize("Please input number of shares to buy");
		}
		else if (preg_match("/^\d+$/", $_POST["shares"]) === false)
		{
			apologize("Cannot purchase fractions of shares");
		}

		// validate stock
		if (empty($_POST["symbol"]))
        {
            apologize("Please input a Symbol");
		}
		else 
		{
			$stock = lookup($_POST["symbol"]);
			if ($stock === false)
	    	{
	    		apologize("Invalid Symbol");
	    	}
		}
		
		// must have enough cash
		$cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
		
		if ($cash === false)
		{
			apologize("Data Retrieval Failure");
		}
		
		else if ($cash[0]["cash"] < ($_POST["shares"] * $stock["price"]))
		{
			apologize("You don't have enough cash :(");
		}
		
		// update portfolio
		query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = (shares + ?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"], $_POST["shares"]);
		
		// update cash
		query("UPDATE users SET cash = (cash - (? * ?)) WHERE id = ?", $stock["price"], $_POST["shares"], $_SESSION["id"]);
		
		// update history
		query("INSERT INTO history (id, type, symbol, amount, price) VALUES (?, ?, ?, ?, ?) ", $_SESSION["id"], "B", strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
		
		// return to portfolio
		redirect("index.php");
	}
	else
	{
		render("buy_form.php", ["title" => "Buy Shares"]);
	}
?>
