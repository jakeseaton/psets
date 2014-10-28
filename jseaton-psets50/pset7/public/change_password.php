<?php
	// configuration
    require("../includes/config.php");

	// if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST" )
    {
    	// validate submission
    	if (empty($_POST["newpassword"]) || empty($_POST["confirmation"]) )
        {
            apologize("Please input a new password and confirm");
        }
    	else if ($_POST["newpassword"] !== $_POST["confirmation"])
        {
          apologize("Passwords do not match.");
        }
    	
    	// change password
    	query("UPDATE users SET hash = ?", crypt($_POST["newpassword"]));
    	
    	// redirect
    	redirect("index.php");
    }
    
    // else display form
    else
    {
    	render("change_password_form.php", ["title" => "Change Password"]);
    }
?>