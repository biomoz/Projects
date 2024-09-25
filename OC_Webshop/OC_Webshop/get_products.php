<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

try {
    include "db_connect.php";

    if ($conn->connect_error) {
        throw new MyException(500, "Connection failed: " . $conn->connect_error);
    }

    // Get the search query from the URL parameter
    if (isset($_GET['search'])) {
        $searchQuery = htmlspecialchars($_GET['search']);
        //check if search query has SQL injection
        $searchQuery = mysqli_real_escape_string($conn, $searchQuery);
    } else {
        $searchQuery = '';
    }

    $sql = "SELECT ProductID, ProductName, UnitPrice, Description, Active, ProductImage FROM products";

    // Append a WHERE clause for searching if a search query is provided
    if (!empty($searchQuery)) {
        $sql .= " WHERE ProductName LIKE '%$searchQuery%'";
    }

    $result = $conn->query($sql);

    if (!$result) {
        throw new MyException(500, "Error executing query: " . $conn->error);
    }

    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $productImage = htmlspecialchars($row['ProductImage']);
            $productName = htmlspecialchars($row['ProductName']);
            $unitPrice = htmlspecialchars($row['UnitPrice']);
            $description = htmlspecialchars($row['Description']);
            $active = htmlspecialchars($row['Active']);
            $productID = htmlspecialchars($row['ProductID']);

            if ($active == 1) {
                // Output product details as a card or any desired HTML structure
                echo "<div class='product-card'>";
                echo "<img src='$productImage' alt='$productName'>";
                echo "<h3>$productName</h3>";
                echo "<p>$description</p>";
                echo "<p>Price: $unitPrice</p>";
                if (isset($_SESSION['username'])) {
                    echo "<form method='POST' action='products.php'>";
                    echo "<input type='hidden' name='productID' value='$productID'>";
                    echo "<input type='number' name='quantity' value='1' min='1' max='10'>";
                    echo "<input type='submit' value='Add to cart'>";
                    echo "</form>";
                }
                echo "</div>";
            }
        }
    } else {
        echo "<div class='answer'> No products found </div>";
    }

    $conn->close();
} catch (MyException $e) {
    $e->HandleException();
}
?>
