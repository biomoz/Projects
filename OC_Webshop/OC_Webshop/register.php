<?php

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
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
                    echo "<li><a href=\"admin.php\">Admin</a></li>";
                }
                if (isset($_SESSION['username']) && $_SESSION['userType'] == 'Employee') {
                    echo "<li><a href=\"employee.php\">Employee</a></li>";
                }
                if (!isset($_SESSION['username'])) {
                    echo "<li><a href=\"login.php\">Login</a></li>";
                    echo "<li class=\"active\"><a href=\"register.php\">Register</a></li>";
                }
            ?>
        </ul>
    </nav>
    <main>
        <div class="search">
            <h2>Register</h2>
        </div>
        <div class="edit">
        <form method="POST" action="register.php">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username" required><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password" required><br><br>
            <label for="email">Email:</label>
            <input type="email" id="email" name="email" required><br><br>
            <label for="firstName">First Name:</label>
            <input type="text" id="firstName" name="firstName" required><br><br>
            <label for="lastName">Last Name:</label>
            <input type="text" id="lastName" name="lastName" required><br><br>
            <input type="submit" value="Register">
        </form>
        <br>
        <p id="error"></p>
        <br>
        <p>Already have an account? <a href="login.php">Login here</a></p>
        </div>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>

<?php

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    try {
        // Retrieve form data
        $username = htmlspecialchars($_POST['username']);
        $password = htmlspecialchars($_POST['password']);
        $email = htmlspecialchars($_POST['email']);
        $firstName = htmlspecialchars($_POST['firstName']);
        $lastName = htmlspecialchars($_POST['lastName']);

        // Hash the password
        $password = password_hash($password, PASSWORD_DEFAULT);

        // Connect to database
        include "db_connect.php";

        $username = mysqli_real_escape_string($conn, $username);
        $password = mysqli_real_escape_string($conn, $password);
        $email = mysqli_real_escape_string($conn, $email);
        $firstName = mysqli_real_escape_string($conn, $firstName);
        $lastName = mysqli_real_escape_string($conn, $lastName);

        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }

        // Check if username already exists
        $sql = "SELECT Username FROM users WHERE Username = '$username'";
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
            // Username already exists, so return to register page
            echo "<script>document.getElementById('error').innerHTML = 'Username already exists';</script>";
        }
        else{
            // Username does not exist, so continue
            // Check for the next available user ID
            $sql = "SELECT UserID FROM users ORDER BY UserID DESC LIMIT 1";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                // Get the last user ID
                $row = $result->fetch_assoc();
                $userID = htmlspecialchars($row['UserID']);

                // Increment the user ID
                $userID++;
            } else {
                // No users found, so set the user ID to 1
                $userID = 1;
            }

            $UserType = "Registered";
            $Active = 1;

            // Query to insert user
            $sql = "INSERT INTO users (UserID, Username, Password, Email, FirstName, LastName, UserType, Active) VALUES ('$userID', '$username', '$password', '$email', '$firstName', '$lastName', '$UserType', '$Active')";
            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error inserting user: " . $conn->error);
            }

            // Redirect to a success page
            header('Location: login.php');
            exit;
        }
        // Close the database connection
        $conn->close();
    } catch (MyException $e) {
        $e->HandleException();
    }
        
}
?>
