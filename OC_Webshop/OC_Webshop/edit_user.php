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
        if (!isset($_POST['UserID'])) {
            throw new MyException(400, "UserID not provided.");
        }

        $userID = $_POST['UserID'];

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
        <h2>Edit User:</h2>
        </div>
            <?php
                try {
                    // Connect to database
                    include "db_connect.php";

                    // Check connection
                    if ($conn->connect_error) {
                        throw new MyException(500, "Connection failed: " . $conn->connect_error);
                    }

                    // Query to retrieve user
                    $sql = "SELECT UserID, Username, Password, Email, FirstName, LastName FROM users WHERE UserID = " . $userID;
                    $result = $conn->query($sql);

                    // Check if user was found
                    if ($result->num_rows > 0) {
                        // Output data of each row
                        while($row = $result->fetch_assoc()) {
                            $UserID = htmlspecialchars($row['UserID']);
                            $Username = htmlspecialchars($row['Username']);
                            $Password = htmlspecialchars($row['Password']);
                            $Email = htmlspecialchars($row['Email']);
                            $FirstName = htmlspecialchars($row['FirstName']);
                            $LastName = htmlspecialchars($row['LastName']);

                            echo "<div class='edit'>";
                            echo "<h3>User ID: " . $UserID . "</h3>";
                            echo "<form action='edit_user.php' method='post'>";
                            echo "<input type='hidden' name='action' value='update'>";
                            echo "<input type='hidden' name='UserID' value='" . $UserID . "'>";
                            echo "<label>Username: </label>";
                            echo "<input type='text' name='Username' value='" . $Username . "'><br>";
                            echo "<label>Password: </label>";
                            echo "<input type='text' name='Password' value='' placeholder='Enter new password'><br>";
                            echo "<label>Email: </label>";
                            echo "<input type='email' name='Email' value='" . $Email . "'><br>";
                            echo "<label>First Name: </label>";
                            echo "<input type='text' name='FirstName' value='" . $FirstName . "'><br>";
                            echo "<label>Last Name: </label>";
                            echo "<input type='text' name='LastName' value='" . $LastName . "'><br>";
                            echo "<input type='submit' value='Update'>";
                            echo "</form>";
                            echo "<br>";
                            echo "<p id='error'></p>";
                            echo "</div>";
                        }
                    }
                    else {
                        throw new MyException(404, "No user found with UserID: " . $userID);
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
        $Username = htmlspecialchars($_POST['Username']);
        $Password = htmlspecialchars($_POST['Password']);
        $Email = htmlspecialchars($_POST['Email']);
        $FirstName = htmlspecialchars($_POST['FirstName']);
        $LastName = htmlspecialchars($_POST['LastName']);

        // Connect to database
        include "db_connect.php";

        // Check connection
        if ($conn->connect_error) {
            throw new MyException(500, "Connection failed: " . $conn->connect_error);
        }

        $Username = mysqli_real_escape_string($conn, $Username);
        $Password = mysqli_real_escape_string($conn, $Password);
        $Email = mysqli_real_escape_string($conn, $Email);
        $FirstName = mysqli_real_escape_string($conn, $FirstName);
        $LastName = mysqli_real_escape_string($conn, $LastName);

        $Password = password_hash($Password, PASSWORD_DEFAULT);

        // Check if username exists
        $sql = "SELECT Username FROM users WHERE Username = '$Username' AND UserID != '$userID'";
        $result = $conn->query($sql);

        if ($result->num_rows > 0) {
           echo "<script> document.getElementById('error').innerHTML = 'Username already exists.'; </script>";
        }
        else{
            // Query to update user
            $sql = "UPDATE users SET Username = '$Username', Password = '$Password', Email = '$Email', FirstName = '$FirstName', LastName = '$LastName' WHERE UserID = '$userID'";
            $result = $conn->query($sql);

            if (!$result) {
                throw new MyException(500, "Error updating user: " . $conn->error);
            }

            // Close the database connection
            $conn->close();
            
            if ($_SESSION['userType'] == 'Administrator') {
                header('Location: admin.php');
            }
            elseif ( $_SESSION['userType'] == 'Employee') {
                header('Location: employee.php');
            }
        }

    }
}
catch (MyException $e) {
    $e->HandleException();
}

?>