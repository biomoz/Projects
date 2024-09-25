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
        if (!isset($_POST['ProductID'])) {
            throw new MyException(400, "ProductID not provided.");
        }

        $ProductID = $_POST['ProductID'];
      
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
                    echo "<li><a href=\"orders.php\">Orders</a></li>";
                    echo "<li><a href=\"logout.php\">Logout</a></li>";
                }
                if (isset($_SESSION['username']) && $_SESSION['userType'] == 'Administrator') {
                    echo "<li class='active'><a href=\"admin.php\">Admin</a></li>";
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
        <h2>Edit Product:</h2>
        </div>
            <?php
                try {
                    include "db_connect.php";

                    // Check connection
                    if ($conn->connect_error) {
                        throw new MyException(500, "Connection failed: " . $conn->connect_error);
                    }

                    // Query to retrieve product
                    $sql = "SELECT ProductID, ProductName, UnitPrice, Description, ProductImage FROM products WHERE ProductID = " . $ProductID;
                    $result = $conn->query($sql);

                    // Check if product was found
                    if ($result->num_rows > 0) {
                        // Output data of each row
                        while($row = $result->fetch_assoc()) {
                            $ProductID = htmlspecialchars($row['ProductID']);
                            $ProductName = htmlspecialchars($row['ProductName']);
                            $UnitPrice = htmlspecialchars($row['UnitPrice']);
                            $Description = htmlspecialchars($row['Description']);
                            $ProductImage = htmlspecialchars($row['ProductImage']);

                            echo "<div class='edit'>";
                            echo "<img src='" . $ProductImage . "' alt='" . $ProductName . "'>";
                            echo "<h3>ProductID: " . $ProductID . "</h3>";
                            echo "<form action='edit_product.php' method='post'>";
                            echo "<input type='hidden' name='action' value='update'>";
                            echo "<input type='hidden' name='ProductID' value='" . $ProductID . "'>";
                            echo "<label>Product Name:</label>";
                            echo "<input type='text' name='ProductName' value='" . $ProductName . "'><br>";
                            echo "<label>Unit Price:</label>";
                            echo "<input type='text' name='UnitPrice' value='" . $UnitPrice . "'><br>";
                            echo "<label>Description:</label> <br>";
                            echo "<textarea name='Description' rows='5' cols='40'>" . $Description . "</textarea><br>";
                            echo "<label>Product Image:</label>";
                            echo "<input type='text' name='ProductImage' value='" . $ProductImage . "'><br>";
                            echo "<input type='submit' value='Update Product'>";
                            echo "</form>";
                            echo "<br>";
                            echo "<p id='error'></p>";
                            echo "</div>";
                        }
                    }
                    else {
                        throw new MyException(404, "No product found with ProductID: " . $ProductID);
                    }
                } catch (MyException $e) {
                    $e->HandleException();
                } finally {
                    $conn->close();
                }
            ?>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>

<?php

try {
    if ($_POST['action'] == 'update') {
        $ProductName = htmlspecialchars($_POST['ProductName']);
        $UnitPrice = htmlspecialchars($_POST['UnitPrice']);
        $Description = htmlspecialchars($_POST['Description']);
        $ProductImage = htmlspecialchars($_POST['ProductImage']);
    
        // Connect to database
        include "db_connect.php";
    
        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }
    
        $ProductName = mysqli_real_escape_string($conn, $ProductName);
        $UnitPrice = mysqli_real_escape_string($conn, $UnitPrice);
        $Description = mysqli_real_escape_string($conn, $Description);
        $ProductImage = mysqli_real_escape_string($conn, $ProductImage);
    
        // Check if product name exists
        $sql = "SELECT ProductName FROM products WHERE ProductName = '$ProductName' AND ProductID != '$ProductID'";
        $result = $conn->query($sql);
    
        //check if unit price is a number
        if (!is_numeric($UnitPrice)) {
            echo "<script> document.getElementById('error').innerHTML = 'Unit price must be a number.'; </script>";
        }
        else if ($result->num_rows > 0) {
            echo "<script> document.getElementById('error').innerHTML = 'Product name already exists.'; </script>";
        
        }
        else{
        // Query to update product
            $sql = "UPDATE products SET ProductName = '$ProductName', UnitPrice = '$UnitPrice', Description = '$Description', ProductImage = '$ProductImage' WHERE ProductID = '$ProductID'";
            $result = $conn->query($sql);
    
            if (!$result) {
                throw new MyException(500, "Error updating product: " . $conn->error);
            }
    
            // Close the database connection
            $conn->close();
    
            if ($_SESSION['userType'] == 'Administrator') {
                header('Location: admin.php');
            }
            else if ($_SESSION['userType'] == 'Employee') {
                header('Location: employee.php');
            }
        }
    }
}
catch (MyException $e) {
    $e->HandleException();
}

?>

