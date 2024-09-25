<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

if (!isset($_SESSION['username']) || $_SESSION['userType'] != 'Administrator') {
    header('Location: main.php');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (!isset($_POST['action'])) {
        $_POST['action'] = '';
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
                if (!isset($_SESSION['username'])) {
                    echo "<li><a href=\"login.php\">Login</a></li>";
                    echo "<li><a href=\"register.php\">Register</a></li>";
                }
            ?>
        </ul>
    </nav>
    <main>
        <div class="search">
        <h2>Add Product:</h2>
        </div>
        <div class="edit">
            <form action="add_product.php" method="post">
                <input type="hidden" name="action" value="add">
                <label>Product Name:</label>
                <input type="text" name="ProductName" required><br>
                <label>Unit Price:</label>
                <input type="text" name="UnitPrice" required><br>
                <label>Description:</label>
                <input type="text" name="Description" required><br>
                <label>Product Image:</label>
                <input type="text" name="ProductImage" required><br>
                <input type="submit" value="Add Product">
            </form>
            <br>
            <p id="error"></p>
        </div>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>

<?php

try {
    if ($_POST['action'] == 'add') {
        
        $ProductName = $_POST['ProductName'];
        $UnitPrice = $_POST['UnitPrice'];
        $Description = $_POST['Description'];
        $ProductImage = $_POST['ProductImage'];

        // Connect to database
        include "db_connect.php";

        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }

        // htmlspecialchars()

        $ProductName = htmlspecialchars($ProductName);
        $UnitPrice = htmlspecialchars($UnitPrice);
        $Description = htmlspecialchars($Description);
        $ProductImage = htmlspecialchars($ProductImage);

        // mysqli_real_escape_string()

        $ProductName = mysqli_real_escape_string($conn, $ProductName);
        $UnitPrice = mysqli_real_escape_string($conn, $UnitPrice);
        $Description = mysqli_real_escape_string($conn, $Description);
        $ProductImage = mysqli_real_escape_string($conn, $ProductImage);    

        // Check if product name exists
        $sql = "SELECT ProductName FROM products WHERE ProductName = '$ProductName'";
        $result = $conn->query($sql);

        //check if the unit price is a number
        if (!is_numeric($UnitPrice)) {
            echo "<script>document.getElementById('error').innerHTML = 'Unit price must be a number'</script>";
        }
        else if ($result->num_rows > 0) {
            echo "<script>document.getElementById('error').innerHTML = 'Product name already exists'</script>";
        }
        else{
            // get the highest productID
            $sql = "SELECT ProductID FROM products ORDER BY ProductID DESC LIMIT 1";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                // Get the last ProductID
                $row = $result->fetch_assoc();
                $ProductID = $row['ProductID'];

                // Increment the ProductID
                $ProductID++;
            } else {
                // No products found, so set the ProductID to 1
                $ProductID = 1;
            }

            $Active = 1;

            // Query to insert product
            $sql = "INSERT INTO products (ProductID, ProductName, UnitPrice, Description, ProductImage, Active) VALUES ('$ProductID', '$ProductName', '$UnitPrice', '$Description', '$ProductImage', '$Active')";

            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error inserting product: " . $conn->error);
            }

            // Close the database connection
            $conn->close();

            header('Location: admin.php');
        }
    }
} catch (MyException $e) {
    $e->HandleException();
}

?>