<?php
	// configuration
    require("../includes/config.php");

	// if form was submitted
	if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// validate amount
		if 	($_POST["amount"] === "None")
		{
			apologize("Please input amount of cash to add");
		}
			
		// update cash
		query("UPDATE users SET cash = (cash + ?) WHERE id = ?", $_POST["amount"], $_SESSION["id"]);
		
		// return to portfolio
		redirect("index.php");
	}
	
	// else render add form
	else
	{
		render("add_form.php", ["title" => "Add Cash"]);
	}
?>