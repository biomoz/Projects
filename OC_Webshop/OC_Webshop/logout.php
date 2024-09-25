
<?php 

include_once "error_handling.php";
include_once "exception_handling.php";

session_start();
session_destroy();
header('Location: main.php');
exit;
?>
