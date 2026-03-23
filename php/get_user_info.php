<?php
session_start();
include "connessione.php";

if (!isset($_SESSION['id_utente'])) {
    exit();
}

$id = $_SESSION['id_utente'];
$stmt = $conn->prepare("SELECT Nome, Cognome, Email, Telefono FROM utente WHERE IdUtente = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$result = $stmt->get_result();
$user = $result->fetch_assoc();

// Manda i dati all'HTML in formato leggibile (JSON)
echo json_encode($user);
?>