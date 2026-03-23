<?php
session_start();
include "connessione.php";

if (isset($_SESSION['id_utente'])) {
    $id = $_SESSION['id_utente'];
    $stmt = $conn->prepare("DELETE FROM utente WHERE IdUtente = ?");
    $stmt->bind_param("i", $id);
    
    if ($stmt->execute()) {
        session_destroy();
        header("Location: ../index.html");
    }
}
?>