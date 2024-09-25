
<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

// Check if user is logged in
if (!isset($_SESSION['username']) || !isset($_SESSION['userType'])) {
    header('Location: main.php');
    exit;
}

if ($_SESSION['userType'] != "Employee") {
    header('Location: main.php');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if ($_POST['action'] == 'toggle_user') {
        // Connect to database
        include "db_connect.php";

        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }

        // Get user ID
        $userID = $_POST['UserID'];

        // Query to retrieve user
        $sql = "SELECT Active FROM users WHERE UserID = '$userID'";
        $result = $conn->query($sql);

        // Check if user was found
        if ($result->num_rows > 0) {
            // Get user details
            $row = $result->fetch_assoc();
            $Active = $row['Active'];

            // Toggle user status
            $Active = ($Active == 1) ? 0 : 1;

            // Query to update user status
            $sql = "UPDATE users SET Active = '$Active' WHERE UserID = '$userID'";
            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error updating user status: " . $conn->error);
            }

            // Close the database connection
            $conn->close();
        }
    }

    if ($_POST['action'] == 'toggle_product') {
        // Connect to database
        include "db_connect.php";

        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }

        // Get product ID
        $productID = $_POST['ProductID'];

        // Query to retrieve product
        $sql = "SELECT Active FROM products WHERE ProductID = '$productID'";
        $result = $conn->query($sql);

        // Check if product was found
        if ($result->num_rows > 0) {
            // Get product details
            $row = $result->fetch_assoc();
            $Active = $row['Active'];

            // Toggle product status
            if ($Active == 1) {
                $Active = 0;
            }
            else if ($Active == 0) {
                $Active = 1;
            }

            // Query to update product status
            $sql = "UPDATE products SET Active = '$Active' WHERE ProductID = '$productID'";
            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error updating product status: " . $conn->error);
            }

            // Close the database connection
            $conn->close();
        }
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
                    echo "<li><a href=\"orders.php\">Orders</a></li>";
                    echo "<li><a href=\"logout.php\">Logout</a></li>";
                }
                if (isset($_SESSION['username']) && $_SESSION['userType'] == 'Administrator') {
                    echo "<li class=\"active\"><a href=\"admin.php\">Admin</a></li>";
                }
                if (isset($_SESSION['username']) && $_SESSION['userType'] == 'Employee') {
                    echo "<li class=\"active\"><a href=\"employee.php\">Employee</a></li>";
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
        <p>Employee:</p>
        </div>
        <div class="edit">
        <p>Users:</p>
        <table>
            <tr>
                <th>User ID</th>
                <th>Username</th>
                <th>Password</th>
                <th>Email</th>
                <th>First Name</th>
                <th>Last Name</th>
                <th>User Type</th>
                <th>Active</th>
                <th colspan="2">Options</th>
            </tr>
            <?php
                $conn = new mysqli("localhost", "Webuser", "Lab2021", "oc_webshop");

                // Check connection
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                // Query to retrieve users
                $sql = "SELECT UserID, Username, Email, FirstName, LastName, UserType, Active FROM users";
                $result = $conn->query($sql);

                // Check if any users found
                if ($result->num_rows > 0) {
                    // Loop through each user
                    while ($row = $result->fetch_assoc()) {

                        //htmlspecialchar()
                        $UserID = htmlspecialchars($row['UserID']);
                        $Username = htmlspecialchars($row['Username']);
                        $Email = htmlspecialchars($row['Email']);
                        $FirstName = htmlspecialchars($row['FirstName']);
                        $LastName = htmlspecialchars($row['LastName']);
                        $UserType = htmlspecialchars($row['UserType']);
                        $Active = htmlspecialchars($row['Active']);

                        if ($Active == 1) {
                            $Active_string = "Active";
                        }
                        else if ($Active == 0) {
                            $Active_string = "Inactive";
                        }

                        echo "<tr>";
                        echo "<td>" . $UserID . "</td>";
                        echo "<td>" . $Username . "</td>";
                        echo "<td>" . $Email . "</td>";
                        echo "<td>" . $FirstName . "</td>";
                        echo "<td>" . $LastName . "</td>";
                        echo "<td>" . $UserType . "</td>";
                        echo "<td>" . $Active_string . "</td>";
                        if ($UserType != "Administrator" && $UserType != "Employee") {
                            echo "<td> <form action='employee.php' method='post'>
                            <input type='hidden' name='UserID' value='" . $UserID . "'>
                            <input type='hidden' name='action' value='toggle_user'>
                            <input type='submit' value='Toggle'></form></td>";
                            echo "<td> <form action='edit_user.php' method='post'> 
                            <input type='hidden' name='UserID' value='" . $UserID . "'>
                            <input type='hidden' name='action' value='edit'>
                            <input type='submit' value='Edit'></form></td>";
                            echo "</tr>";
                        }
                    }
                } else {
                    echo "<tr><td colspan='7'>No users found</td></tr>";
                }

                // Close the database connection
                $conn->close();
            ?>
        </table>
        </div>
        <div class="edit">
        <p>Products:</p>
        <table>
            <tr>
                <th>Product ID</th>
                <th>Product Name</th>
                <th>Description</th>
                <th>Unit Price</th>
                <th>Active</th>
                <th colspan="2">Options</th>
            </tr>
            <?php
                include "db_connect.php";

                // Check connection
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                // Query to retrieve products
                $sql = "SELECT ProductID, ProductName, UnitPrice, Description, Active FROM products";
                $result = $conn->query($sql);

                // Check if any products found
                if ($result->num_rows > 0) {
                    // Loop through each product
                    while ($row = $result->fetch_assoc()) {
                        
                        //htmlspecialchar()
                        $ProductID = htmlspecialchars($row['ProductID']);
                        $ProductName = htmlspecialchars($row['ProductName']);
                        $UnitPrice = htmlspecialchars($row['UnitPrice']);
                        $Description = htmlspecialchars($row['Description']);
                        $Active = htmlspecialchars($row['Active']);

                        if ($Active == 1) {
                            $Active_string = "Active";
                        }
                        else if ($Active == 0) {
                            $Active_string = "Inactive";
                        }

                        echo "<tr>";
                        echo "<td>" . $ProductID . "</td>";
                        echo "<td>" . $ProductName . "</td>";
                        echo "<td>" . $Description . "</td>";
                        echo "<td>" . $UnitPrice . "</td>";
                        echo "<td>" . $Active_string . "</td>";
                        echo "<td> <form action='employee.php' method='post'>
                        <input type='hidden' name='ProductID' value='" . $ProductID . "'>
                        <input type='hidden' name='action' value='toggle_product'>
                        <input type='submit' value='Toggle'></form></td>";
                        echo "<td> <form action='edit_product.php' method='post'> 
                        <input type='hidden' name='ProductID' value='" . $ProductID . "'>
                        <input type='hidden' name='action' value='edit'>
                        <input type='submit' value='Edit'></form></td>";
                        echo "</tr>";
                    }
                } else {
                    echo "<tr><td colspan='5'>No products found</td></tr>";
                }

                // Close the database connection
                $conn->close();
            ?>
        </table>
        </div>
        <div class="edit">
        <p>Orders:</p>
        <table>
            <tr>
                <th>Order ID</th>
                <th>Order Date</th>
                <th>Order Price</th>
                <th>User ID</th>
                <th>Options</th>
            </tr>
            <?php
                include "db_connect.php";

                // Check connection
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                // Query to retrieve orders
                $sql = "SELECT OrderID, OrderDate, OrderPrice, UserID FROM orders";
                $result = $conn->query($sql);

                // Check if any orders found
                if ($result->num_rows > 0) {
                    // Loop through each order
                    while ($row = $result->fetch_assoc()) {
                        
                        //htmlspecialchar()
                        $OrderID = htmlspecialchars($row['OrderID']);
                        $OrderDate = htmlspecialchars($row['OrderDate']);
                        $OrderPrice = htmlspecialchars($row['OrderPrice']);
                        $UserID = htmlspecialchars($row['UserID']);

                        echo "<tr>";
                        echo "<td>" . $OrderID . "</td>";
                        echo "<td>" . $OrderDate . "</td>";
                        echo "<td>" . $OrderPrice . "</td>";
                        echo "<td>" . $UserID . "</td>";
                        echo "<td> <form action='order_details.php' method='post'> 
                        <input type='hidden' name='orderID' value='" . $OrderID . "'>
                        <input type='hidden' name='userID' value='" . $UserID . "'>
                        <input type='hidden' name='action' value='view'>
                        <input type='submit' value='View'></form></td>";
                        echo "</tr>";
                    }
                } else {
                    echo "<tr><td colspan='4'>No orders found</td></tr>";
                }

                // Close the database connection
                $conn->close();
            ?>
        </table>
        </div>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>
