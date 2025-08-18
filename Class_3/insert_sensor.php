<?php
// Database credentials
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "iot_data";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Get data from URL parameters
$temperature = $_GET['temperature'];
$humidity = $_GET['humidity'];

// Prepare and bind
$stmt = $conn->prepare("INSERT INTO sensor_reading (temperature, humidity) VALUES (?, ?)");
$stmt->bind_param("dd", $temperature, $humidity);

// Execute and check
if ($stmt->execute()) {
  echo "New record created successfully";
} else {
  echo "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
