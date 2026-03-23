<?php
session_start();
session_unset();
session_destroy();

// Il percorso qui sotto deve riportarti alla pagina di login o alla index
// Se logout.php è in /php/ e il login è in /html/login.html:
header("Location: ../html/login.html");
exit();
?>