<?php
echo "Content-Type: text/plain;charset=utf-8\r\n\r\n";
echo "Hello, World! This is a CGI script in PHP.\n\n";

// Affichage de la méthode de la requête
echo "Request Method: " . $_SERVER['REQUEST_METHOD'] . "\n";

// Affichage des données reçues dans le cas d'une méthode POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    echo "POST Data: \n";
    foreach ($_POST as $key => $value) {
        echo "$key: $value\n";
    }
}

// Affichage des données de Query String pour une requête GET
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    echo "GET Data: \n";
    foreach ($_GET as $key => $value) {
        echo "$key: $value\n";
    }
}

// Affichage de quelques variables d'environnement CGI pertinentes
echo "\nServer Information:\n";
echo "Server Software: " . $_SERVER['SERVER_SOFTWARE'] . "\n";
echo "Server Name: " . $_SERVER['SERVER_NAME'] . "\n";
echo "Script Name: " . $_SERVER['SCRIPT_NAME'] . "\n";
echo "Request URI: " . $_SERVER['REQUEST_URI'] . "\n";
?>
