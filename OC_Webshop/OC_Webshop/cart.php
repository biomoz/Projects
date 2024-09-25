
<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

if (!isset($_SESSION['username'])) {
    header('Location: main.php');
    exit;
}

try {
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        if ($_POST['action'] == 'remove') {
            $productID = htmlspecialchars($_POST['productID']);
            unset($_SESSION['cart'][$productID]);
            if (count($_SESSION['cart']) == 0) {
                unset($_SESSION['cart']);
            }
        } else if ($_POST['action'] == 'update') {
            $productID = htmlspecialchars($_POST['productID']);
            $quantity = htmlspecialchars($_POST['quantity']);
            $_SESSION['cart'][$productID] = $quantity;
        } else {
            throw new MyException(400, "Invalid action specified.");
        }
    }
} catch (MyException $e) {
    $e->HandleException();
}

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
                echo "<li><a href=\"main.php\">Home</a></li>";
                echo "<li><a href=\"products.php\">Products</a></li>";
                if (isset($_SESSION['username'])) {
                    echo "<li class=\"active\"><a href=\"cart.php\">Cart</a></li>";
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
            echo "<div class='search'>";
            echo "<h2>Cart:</h2>";
            echo "</div>";
            if (isset($_SESSION['username']) && isset($_SESSION['cart'])) {

                include "db_connect.php";
                // Check connection
                if ($conn->connect_error) {
                    throw new MyException(500, "Connection failed: " . $conn->connect_error);
                }

                foreach ($_SESSION['cart'] as $productID => $quantity) {
                    $sql = "SELECT ProductID, ProductName, UnitPrice, Description, ProductImage FROM products WHERE ProductID = " . $productID;
                    $result = $conn->query($sql);

                    if ($result->num_rows > 0) {
                        while ($row = $result->fetch_assoc()) {
                            $productID = htmlspecialchars($row['ProductID']);
                            $productName = htmlspecialchars($row['ProductName']);
                            $unitPrice = htmlspecialchars($row['UnitPrice']);
                            $description = htmlspecialchars($row['Description']);
                            $productImage = htmlspecialchars($row['ProductImage']);

                            echo "<div class='product-card'>";
                            echo "<img src='$productImage' alt='$productName'>";
                            echo "<h3>$productName</h3>";
                            echo "<p>$description</p>";
                            echo "<p>Total: $" . $unitPrice * $quantity . "</p>";
                            echo "<td><form method='POST' action='cart.php'>";
                            echo "<input type='hidden' name='action' value='remove'>";
                            echo "<input type='hidden' name='productID' value='" . $productID . "'>";
                            echo "<input type='submit' value='Remove'>";
                            echo "</form></td>";
                            echo "<td><form method='POST' action='cart.php'>";
                            echo "<input type='hidden' name='action' value='update'>";
                            echo "<input type='hidden' name='productID' value='" . $productID . "'>";
                            echo "<input type='number' name='quantity' value='" . $quantity . "' min='1'>";
                            echo "<input type='submit' value='Update'>";
                            echo "</form></td>";
                            echo "</div>";
                        }
                    }
                }

                $conn->close();

                echo "<div class='answer'>";
                echo "<form method='POST' action='orders.php'>";
                echo "<input type='hidden' name='action' value='order'>";
                echo "<input type='submit' value='Place Order'>";
                echo "</form>";
                echo "</div>";
            } else {
                echo "<div class='answer'>";
                echo "<p>No products in cart.</p>";
                echo "</div>";
            }
        ?>

    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>
