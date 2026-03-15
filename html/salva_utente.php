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

// Password sicura
$passwordHash = password_hash($passwordRaw, PASSWORD_DEFAULT);

$stmt = $conn->prepare("INSERT INTO utenti (nome, cognome, dataN, email, password) VALUES (?, ?, ?, ?, ?)");
$stmt->bind_param("sssss", $nome, $cognome, $dataN, $email, $passwordHash);

if ($stmt->execute()) {
    echo "Registrazione completata con successo!";
} else {
    echo "Errore: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>