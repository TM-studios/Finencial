<?php
include "connessione.php";

$email = $_POST['email'];
$password = $_POST['password'];

// 1. Cerchiamo l'utente solo tramite email (usando i Prepared Statements per sicurezza)
$stmt = $conn->prepare("SELECT * FROM utenti WHERE email = ?");
$stmt->bind_param("s", $email);
$stmt->execute();
$result = $stmt->get_result();

// 2. Verifichiamo se l'utente esiste
if ($result->num_rows > 0) {
    $utente = $result->fetch_assoc();
    
    // 3. Confrontiamo la password del form con l'hash salvato nel DB
    // password_verify() è la funzione magica che sa come gestire quegli hash "strani"
    if (password_verify($password, $utente['password'])) {
        echo "Login riuscito! Benvenuto " . $utente['nome'];
        
        // QUI in futuro potrai aggiungere:
        // session_start();
        // $_SESSION['utente_id'] = $utente['id'];
        
    } else {
        echo "Password errata!";
    }
} else {
    echo "Email non trovata!";
}

$stmt->close();
$conn->close();
?>