<?php
	// configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST" )
    {
    	// validate submission
    	if (empty($_POST["symbol"]))
        {
            apologize("Please input a Symbol");
        }
    	
    	// lookup stock
    	$stock = lookup($_POST["symbol"]);
    	
    	// validate stock
    	if ($stock === false)
    	{
    		apologize("Invalid Symbol");
    	}
    	
    	// display
    	else 
    	{
    		render("display_quote.php", ["name" => $stock["name"],"symbol" => $stock["symbol"], "price" => $stock["price"]]);
    	}
    }
    
    // else display form
    else
    {
    	render("quote_form.php", ["title" => "Quote"]);
    }
?>