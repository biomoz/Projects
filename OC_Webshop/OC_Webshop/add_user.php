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
            <h2>Add User:</h2>
        </div>
        <div class="edit">
            <form action="add_user.php" method="post">
                <input type="hidden" name="action" value="add">
                <br>
                <label>User Type:</label>
                <select name="UserType">
                    <option value="Administrator">Administrator</option>
                    <option value="Registered">Registered</option>
                    <option value="Employee">Employee</option>
                </select><br><br>
                <label>Username:</label>
                <input type="text" name="Username" required><br><br>
                <label>Password:</label>
                <input type="text" name="Password" required><br><br>
                <label>Email:</label>
                <input type="email" name="Email" required><br><br>
                <label>First Name:</label>
                <input type="text" name="FirstName" required><br><br>
                <label>Last Name:</label>
                <input type="text" name="LastName" required><br><br>
                <input type="submit" value="Add User"><br><br>
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
        $Username = $_POST['Username'];
        $Password = $_POST['Password'];
        $Email = $_POST['Email'];
        $FirstName = $_POST['FirstName'];
        $LastName = $_POST['LastName'];
        $UserType = $_POST['UserType'];

        // Connect to database
        include "db_connect.php";

        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }

        // htmlspecialchars()

        $Username = htmlspecialchars($Username);
        $Password = htmlspecialchars($Password);
        $Email = htmlspecialchars($Email);
        $FirstName = htmlspecialchars($FirstName);
        $LastName = htmlspecialchars($LastName);
        $UserType = htmlspecialchars($UserType);

        // mysqli_real_escape_string()

        $Username = mysqli_real_escape_string($conn, $Username);
        $Password = mysqli_real_escape_string($conn, $Password);
        $Email = mysqli_real_escape_string($conn, $Email);
        $FirstName = mysqli_real_escape_string($conn, $FirstName);
        $LastName = mysqli_real_escape_string($conn, $LastName);
        $UserType = mysqli_real_escape_string($conn, $UserType);

        $Password = password_hash($Password, PASSWORD_DEFAULT);

        // Check if username exists
        $sql = "SELECT Username FROM users WHERE Username = '$Username'";
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
            echo "<script>document.getElementById('error').innerHTML = 'Username already exists'</script>";
        }
        else {
            // get the next available UserID
            $sql = "SELECT UserID FROM users ORDER BY UserID DESC LIMIT 1";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                // Get the last UserID
                $row = $result->fetch_assoc();
                $UserID = $row['UserID'];

                // Increment the UserID
                $UserID++;
            } else {
                // No users found, so set the UserID to 1
                $UserID = 1;
            }

            $Active = 1;

            // Query to insert product
            $sql = "INSERT INTO users (UserID, Username, Password, Email, FirstName, LastName, UserType, Active) VALUES ('$UserID', '$Username', '$Password', '$Email', '$FirstName', '$LastName', '$UserType', '$Active')";
            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error inserting user: " . $conn->error);
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
