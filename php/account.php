<?php
session_start();
include "connessione.php"; // Verifica che il percorso sia esatto

if (!isset($_SESSION['id_utente'])) {
    header("Location: login.html");
    exit();
}

$id = $_SESSION['id_utente'];
$stmt = $conn->prepare("SELECT * FROM utente WHERE IdUtente = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$user = $stmt->get_result()->fetch_assoc();

// Questa riga "trasporta" i dati dentro il file HTML
include "account.html"; 
?>