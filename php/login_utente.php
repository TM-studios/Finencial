<?php
session_start(); // 1. Avvia la sessione all'inizio
include "connessione.php";

$email = $_POST['email'];
$password = $_POST['password'];

$stmt = $conn->prepare("SELECT * FROM utente WHERE Email = ?");
$stmt->bind_param("s", $email);
$stmt->execute();
$result = $stmt->get_result();

if ($result->num_rows > 0) {
    $utente = $result->fetch_assoc();
    
    if (password_verify($password, $utente['password'])) {
        // 2. Salviamo i dati importanti nella sessione
        $_SESSION['id_utente'] = $utente['IdUtente'];
        $_SESSION['nome_utente'] = $utente['Nome'];

        // 3. Reindirizziamo l'utente alla sua pagina account
        header("Location: ../html/nav-link/account.html");
        exit();
        
    } else {
        echo "Password errata!";
    }
} else {
    echo "Email non trovata!";
}

$stmt->close();
$conn->close();
?>