<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

try {
    if (isset($_POST['productID']) && isset($_SESSION['username'])) {
        $productID = $_POST['productID'];

        if (!isset($_SESSION['cart'])) {
            $_SESSION['cart'] = array();
        }

        $cart = $_SESSION['cart'];

        if (!isset($cart[$productID])) {
            $cart[$productID] = 0;
        }

        $quantity = $_POST['quantity'];
        $cart[$productID] += $quantity;
        $_SESSION['cart'] = $cart;

        // foreach ($_SESSION['cart'] as $productID => $quantity) {
        //     echo $productID . " " . $quantity . "<br>";
        // }
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
                echo "<li class=\"active\"><a href=\"products.php\">Products</a></li>";
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
        <div class="search">
            <label for="search">Search:</label>
            <input type="text" id="search" oninput="searchProducts()">
        </div>

        <div id="productList">
            <!-- Product listings will be dynamically loaded here -->
        </div>

        <script>
            function loadProducts(searchQuery = "") {
                var xhr = new XMLHttpRequest();

                xhr.onreadystatechange = function() {
                    if (xhr.readyState == 4 && xhr.status == 200) {
                        document.getElementById("productList").innerHTML = xhr.responseText;
                    }
                };

                // Fetch products.php with an additional parameter for search
                xhr.open("GET", "get_products.php?search=" + encodeURIComponent(searchQuery), true);
                xhr.send();
            }

            // Function to handle dynamic search
            function searchProducts() {
                var searchQuery = document.getElementById("search").value;
                loadProducts(searchQuery);
            }

            // Initial load of products
            window.onload = function() {
                loadProducts();
            };
        </script>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>
