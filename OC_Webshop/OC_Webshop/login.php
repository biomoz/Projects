<?php
    include_once "error_handling.php";
    include_once "exception_handling.php";
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
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
                    echo "<li class=\"active\"><a href=\"login.php\">Login</a></li>";
                    echo "<li><a href=\"register.php\">Register</a></li>";
                }
            ?>
        </ul>
    </nav>
    <main>
        <div class="search">
            <h2>Login:</h2>
        </div>
        <div class="edit">
            <form method="POST" action="login.php">
                <label for="username">Username:</label>
                <input type="text" id="username" name="username" required><br><br>
                <label for="password">Password:</label>
                <input type="password" id="password" name="password" required><br><br>
                <input type="submit" value="Login">
            </form>
            <br>
            <p id="error"></p>
            <br>
            <p>Don't have an account? <a href="register.php">Register here</a></p>
        </div>
    </main>
    <footer>
        <p>OC Game Shop</p>
    </footer>
</body>
</html>

<?php  
    // Check if user is already logged in
    if (isset($_SESSION['username'])) {
        // Redirect to main page
        header('Location: main.php');
        exit;
    }
    
    // Check if form was submitted
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        try {
            // Get username and password from POST variables
            $post_username = htmlspecialchars($_POST['username']);
            $post_password = htmlspecialchars($_POST['password']);
    
            // Connect to database
            include "db_connect.php";
    
            if ($conn->connect_error) {
                throw new MyException(500, "Connection failed: " . $conn->connect_error);
            }

            $post_username = mysqli_real_escape_string($conn, $post_username);
            $post_password = mysqli_real_escape_string($conn, $post_password);

            // Query to retrieve user
            $sql = "SELECT UserID, Username, Password, Active, UserType FROM users WHERE Username = '$post_username'";
            $result = $conn->query($sql);

            // Check if user was found
            if ($result->num_rows > 0) {
                // Get user details
                $row = $result->fetch_assoc();
                $userID = htmlspecialchars($row['UserID']);
                $username = htmlspecialchars($row['Username']);
                $password = htmlspecialchars($row['Password']);
                $active = htmlspecialchars($row['Active']);
                $userType = htmlspecialchars($row['UserType']);

                // Check if user is active
                if ($active == 0) {
                    //put error message in id="error"
                    echo "<script>document.getElementById('error').innerHTML = 'User is not active';</script>";
                    exit;
                }
                // Verify password
                if (password_verify($post_password, $password)) {
                    // Password is correct, so start a new session
                    session_start();

                    // Store data in session variables
                    $_SESSION['userID'] = $userID;
                    $_SESSION['username'] = $username;
                    $_SESSION['userType'] = $userType;

                    // Redirect to main page
                    header('Location: main.php');
                    exit;
                }
                else {
                    // Password is incorrect, so return to login page
                    echo "<script>document.getElementById('error').innerHTML = 'Invalid username or password';</script>";
                }
            }
            else {
                // User not found, so return to login page
                echo "<script>document.getElementById('error').innerHTML = 'Invalid username or password';</script>";
            }

            // Close the database connection
            $conn->close();
        }
        catch (MyException $e) {
            $e->HandleException();
        }
    }
?>

