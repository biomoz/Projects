<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

if (!isset($_SESSION['username'])) {
    header('Location: main.php');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    try {
        if ($_POST['action'] == 'order' && isset($_SESSION['cart'])) {
            // Connect to database
            include "db_connect.php";

            // Check connection
            if ($conn->connect_error) {
                throw new MyException(500, "Connection failed: " . $conn->connect_error);
            }

            // Get user ID
            $userID = $_SESSION['userID'];
            $orderDate = date("Y-m-d H:i:s");
            $orderPrice = 0;
            if (!isset($_SESSION['cart'])) {
                $_SESSION['cart'] = array();
            }

            $sql = "SELECT OrderID FROM orders ORDER BY OrderID DESC LIMIT 1";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                // Get the last order ID
                $row = $result->fetch_assoc();
                $orderID = htmlspecialchars($row['OrderID']);

                // Increment the order ID
                $orderID++;
            } else {
                // No orders found, so set the order ID to 1
                $orderID = 1;
            }

            // Query to insert order
            $sql = "INSERT INTO orders (OrderID, UserID, OrderDate, OrderPrice) VALUES ($orderID, $userID, '$orderDate', $orderPrice)";
            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error inserting order: " . $conn->error);
            }

            foreach ($_SESSION['cart'] as $productID => $quantity) {
                // Query to insert order
                $sql = "SELECT ProductID, UnitPrice FROM products WHERE ProductID = " . $productID;
                $result = $conn->query($sql);

                // Check if product was found
                if ($result->num_rows > 0) {
                    // Get product details
                    $row = $result->fetch_assoc();
                    $productID = htmlspecialchars($row['ProductID']);
                    $unitPrice = htmlspecialchars($row['UnitPrice']);
                    $totalPrice = $unitPrice * $quantity;
                    $orderPrice += $totalPrice;

                    // find the next available order ID
                    $sql = "SELECT OrderItemID FROM orderitems ORDER BY OrderItemID DESC LIMIT 1";
                    $result = $conn->query($sql);

                    if ($result->num_rows > 0) {
                        // Get the last order ID
                        $row = $result->fetch_assoc();
                        $orderItemID = htmlspecialchars($row['OrderItemID']);

                        // Increment the order ID
                        $orderItemID++;
                    } else {
                        // No orders found, so set the order ID to 1
                        $orderItemID = 1;
                    }

                    // Query to insert order
                    $sql = "INSERT INTO orderitems (OrderItemID, OrderID, ProductID, Quantity, TotalPrice) VALUES ($orderItemID, $orderID, $productID, $quantity, $totalPrice)";
                    $result = $conn->query($sql);
                }
            }

            // Update the order price
            $sql = "UPDATE orders SET OrderPrice = $orderPrice WHERE OrderID = $orderID";
            $result = $conn->query($sql);

            // Clear the cart
            unset($_SESSION['cart']);

            // Close the database connection
            $conn->close();
        }
    } catch (MyException $e) {
        $e->HandleException();
    }
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
                    echo "<li><a href=\"cart.php\">Cart</a></li>";
                    echo "<li class=\"active\"><a href=\"orders.php\">Orders</a></li>";
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
        <div class="search">
        <h2>Orders:</h2>
        </div>
            <?php
                // Connect to database
                include "db_connect.php";

                // Check connection
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                // Get user ID
                $userID = $_SESSION['userID'];

                // Query to retrieve orders
                $sql = "SELECT OrderID, OrderDate, OrderPrice FROM orders WHERE UserID = " . $userID;
                $result = $conn->query($sql);

                // Check if any orders found
                if ($result->num_rows > 0) {
                    // Loop through each order
                    while ($row = $result->fetch_assoc()) {
                        echo "<div class='product-card'>";
                        echo "<h3>Order #" . $row['OrderID'] . "</h3>";
                        echo "<p>Order Date: " . $row['OrderDate'] . "</p>";
                        echo "<p>Order Price: $" . $row['OrderPrice'] . "</p>";
                        echo "<form action='order_details.php' method='post'>";
                        echo "<input type='hidden' name='orderID' value='" . $row['OrderID'] . "'>";
                        echo "<input type='submit' value='View Order Details'>";
                        echo "</form>";
                        echo "</div>";
                    }
                }
                else {
                    echo "<div class='answer'>";
                    echo "<p>No orders found.</p>";
                    echo "</div>";
                }

                // Close the database connection
                $conn->close();
            ?>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>
