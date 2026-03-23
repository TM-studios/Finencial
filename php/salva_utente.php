<?php
include "connessione.php";

$nome = $_POST['nome'];
$cognome = $_POST['cognome'];
$email = $_POST['email'];
$passwordRaw = $_POST['password'];

// Gestione data
$day = $_POST['day'];
$month = $_POST['month'];
$year = $_POST['year'];
$dataN = sprintf('%04d-%02d-%02d', $year, $month, $day);

$sesso=$_POST['sesso'];
$nazionalita=$_POST['nazionalita'];
$telefono=$_POST['prefisso']." ".$_POST['telefono'];

// Password sicura
$passwordHash = password_hash($passwordRaw, PASSWORD_DEFAULT);

$stmt = $conn->prepare("INSERT INTO utente (Nome, Cognome, Sesso, DataNascita, Nazionalita, Telefono, Email, password) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
$stmt->bind_param("ssssssss", $nome, $cognome, $sesso, $dataN, $nazionalita,  $telefono, $email, $passwordHash);

if ($stmt->execute()) {
    header("Location: ../html/login.html");
} else {
    echo "Errore: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>