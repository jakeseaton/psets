
<?php
	// configuration
    require("../includes/config.php");

	// make them re-enter password?

	// if form was submitted
	if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// validate stock
		if (empty($_POST["symbol"]))
        {
           apologize("Derp...Please choose a stock to sell");
		}

		// validate shares to sell
		if 	(empty($_POST["shares"]) || !is_numeric($_POST["shares"]))
		{
			apologize("Derp...Please input number of shares to sell");
		}
		
		// must be whole number of shares
		else if (preg_match("/^\d+$/", $_POST["shares"]) === false)
		{
			apologize("Cannot sell fractions of shares");
		}
		
		$shares = query("SELECT shares FROM portfolios WHERE id  = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

		if ($shares === false)
		{
			apologize("Data Retrieval Failure");
		}
		
		else if ($_POST["shares"] > $shares[0]["shares"])
		{
			apologize("Derp...You dont't have that many!");
		}

		$stock = lookup($_POST["symbol"]);
		
		// update portfolio
		query("UPDATE portfolios SET shares = (shares - ?) WHERE (id, symbol) =(?,?)", $_POST["shares"], $_SESSION["id"], strtoupper($_POST["symbol"]));

		// update cash
		query("UPDATE users SET cash = (cash + (? * ?)) WHERE id = ?", $stock["price"], $_POST["shares"], $_SESSION["id"]);

		// update history
		query("INSERT INTO history (id, type, symbol, amount, price) VALUES (?, ?, ?, ?, ?) ", $_SESSION["id"], "S", strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
					
		// returb to portfolio
		redirect("index.php");
	}

	// else render sell form
	else
	{
		// fill rows
    	$rows = query("SELECT symbol FROM portfolios WHERE id = ?", $_SESSION["id"]);

		if ($rows === false)
		{
			apologize("Data Retrieval Failure");
		}
		// initialize positions
    	$positions = [];

		// iterate over rows
	    foreach ($rows as $row)
	    {
	        $stock = lookup($row["symbol"]);
	       
	            $positions[] = [
	                "symbol" => $row["symbol"]
	            ];
	    }
	    
	    // render
		render("sell_form.php", [ "positions" => $positions, "title" => "Sell Shares"]);
	}
?>