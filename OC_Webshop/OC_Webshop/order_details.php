
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

            if (!isset($_SESSION['username'])) {
                header('Location: main.php');
                exit;
            }

            if ($_SERVER['REQUEST_METHOD'] == 'POST') {
                if (isset($_POST['orderID'])) {
                    $orderID = $_POST['orderID'];
                }

                try {
                    
                    // Create connection
                    include "db_connect.php";

                    // Check connection
                    if ($conn->connect_error) {
                        throw new MyException(500, "Connection failed: " . $conn->connect_error);
                    }

                    if (!isset($_POST['action'])) {
                        $_POST['action'] = '';
                    }

                    if ($_POST['action'] == 'view') {
                        $userID = $_POST['userID'];
                    } else {
                        $userID = $_SESSION['userID'];
                    }

                    // Query to retrieve orders and order items
                    $sql = "SELECT o.OrderID, o.OrderDate, o.OrderPrice, oi.ProductID, oi.Quantity, oi.TotalPrice, p.ProductName, p.ProductImage
                            FROM orders o 
                            INNER JOIN OrderItems oi ON o.OrderID = oi.OrderID 
                            INNER JOIN products p ON oi.ProductID = p.ProductID
                            WHERE o.UserID = " . $userID . " AND o.OrderID = " . $orderID;

                    $result = $conn->query($sql);

                    // Check if orders and order items were found
                    if ($result->num_rows > 0) {
                        $row = $result->fetch_assoc();

                        $OrderID = htmlspecialchars($row['OrderID']);
                        $OrderDate = htmlspecialchars($row['OrderDate']);
                        $OrderPrice = htmlspecialchars($row['OrderPrice']);

                        echo "<div class='answer'>";
                        echo "<p>User ID: " . $userID . "</p>";
                        echo "<p>Order ID: " . $OrderID . "</p>";
                        echo "<p>Order Date: " . $OrderDate . "</p>";
                        echo "<p>Order Price: " . $OrderPrice . "</p>";
                        echo "<p>Order Details:</p>";
                        echo "</div>";

                        // Loop through the result to display order items
                        $result = $conn->query($sql);

                        if ($result->num_rows > 0) {
                            // Loop through each order detail
                            while ($row = $result->fetch_assoc()) {
                                $ProductID = htmlspecialchars($row['ProductID']);
                                $Quantity = htmlspecialchars($row['Quantity']);
                                $TotalPrice = htmlspecialchars($row['TotalPrice']);
                                $ProductName = htmlspecialchars($row['ProductName']);
                                $ProductImage = htmlspecialchars($row['ProductImage']);

                                echo "<div class='product-card'>";
                                echo "<img src='" . $ProductImage . "' alt='" . $ProductName . "'>";
                                echo "<p>Product Name: " . $ProductName . "</p>";
                                echo "<p>Quantity: " . $Quantity . "</p>";
                                echo "<p>Total Price: " . $TotalPrice . "</p>";
                                echo "</div>";
                            }
                        } else {
                            echo "<div class='answer'>";
                            echo "<p>No order details found</p>";
                            echo "</div>";
                        }
                    } else {
                        echo "<div class='answer'>";
                        echo "<p>No orders found</p>";
                        echo "</div>";
                    }

                    $conn->close();
                } catch (MyException $e) {
                    $e->HandleException();
                }
            }
            ?>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>
