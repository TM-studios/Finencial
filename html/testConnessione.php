<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

$host = "localhost";
$user = "root";
$password = "";
$db = "finencialdb";

echo "<h3>Tentativo di connessione in corso...</h3>";

$conn = new mysqli($host, $user, $password, $db);

if ($conn->connect_error) {
    echo "<p style='color:red;'>❌ ERRORE: " . $conn->connect_error . "</p>";
    echo "<p>Codice Errore: " . $conn->connect_errno . "</p>";
} else {
    echo "<p style='color:green;'>✅ GRANDE! La connessione funziona.</p>";
    
    // Verifica se la tabella esiste davvero
    $res = $conn->query("SHOW TABLES LIKE 'utenti'");
    if($res->num_rows > 0) {
        echo "<p style='color:green;'>✅ La tabella 'utenti' esiste.</p>";
    } else {
        echo "<p style='color:orange;'>⚠️ Connesso, ma la tabella 'utenti' NON esiste nel database '$db'.</p>";
    }
}
?>