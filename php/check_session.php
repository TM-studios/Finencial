<?php
session_start();

// Controlliamo se la variabile 'id_utente' è settata nella sessione
if (isset($_SESSION['id_utente'])) {
    // L'utente è già loggato
    header("Location: ../html/nav-link/account.html");
    exit();
} else {
    // L'utente NON è loggato
    header("Location: ../html/login.html"); // Assicurati che il percorso sia corretto
    exit();
}
?>