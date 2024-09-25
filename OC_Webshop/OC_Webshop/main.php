
<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Game Shop</title>
    <link rel="stylesheet" href="reset.css">
    <link rel="stylesheet" href="main.css">
</head>
<body>
    <header>
        <h1>OC Game Shop</h1>
    </header>
    <nav>
        <ul>
            <?php
                echo "<li class=\"active\"><a href=\"main.php\">Home</a></li>";
                echo "<li><a href=\"products.php\">Products</a></li>";
                if (isset($_SESSION['username'])) {
                    echo "<li><a href=\"cart.php\">Cart</a></li>";
                    echo "<li><a href=\"orders.php\">Orders</a></li>";
                    echo "<li><a href=\"logout.php\">Logout</a></li>";
                }
                if (isset($_SESSION['username']) && $_SESSION['userType'] == 'Administrator') {
                    echo "<li><a href=\"admin.php\">Admin</a></li>";
                }
                if (isset($_SESSION['username']) && $_SESSION['userType'] == 'Employee') {
                    echo "<li><a href=\"employee.php\">Employee</a></li>";
                }
                if (!isset($_SESSION['username'])) {
                    echo "<li><a href=\"login.php\">Login</a></li>";
                    echo "<li><a href=\"register.php\">Register</a></li>";
                }
            ?>
        </ul>
    </nav>
    <main>
        <?php
            if (isset($_SESSION['username'])) {
                echo "<div class=\"search\">";
                echo "<h2>Welcome " . $_SESSION['username'] . "</h2>";
                echo "</div>";
            }
        ?>
        <div class="edit">
            <img src="https://img.freepik.com/premium-photo/cyberpunk-gaming-controller-gamepad-joystick-illustration_691560-5778.jpg" alt="Game Controller">
            <br>
            <h2>Welcome to OC Game Shop</h2>
            <p>OC Game Shop is a web site that sells video games.</p>
            <p>We offer the latest games at the lowest prices.</p>
            <p>We have a wide selection of games for you to choose from.</p>
            <p>Click on the Products link to see what we have.</p>
            <p>We hope you enjoy your visit.</p>
        </div>
        
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>
