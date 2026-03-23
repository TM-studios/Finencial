<?php
// 1. Definiamo le credenziali
$host = "localhost";    // Il server (di solito localhost su XAMPP)
$user = "root";         // L'utente predefinito di MySQL
$password = "";         // La password (vuota su XAMPP per Windows)
$db = "finencialdb";    // IL NOME ESATTO del database che hai creato

// 2. Creiamo la connessione "parlando" con il database
$conn = new mysqli($host, $user, $password, $db);

// 3. Verifichiamo se ha funzionato
if ($conn->connect_error) {
    // Se c'è un errore, ferma lo script e dimmi cosa non va
    die("Connessione fallita: " . $conn->connect_error);
} 

// Se arriviamo qui, il PHP è connesso al DB!
?>