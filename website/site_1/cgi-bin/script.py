<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" sizes="32x32" href="/assets/img/42_Logo.ico">
    <link rel="stylesheet" type="text/css" href="/page/style.css">
    <title>Formulaire</title>
</head>
<body>
    <h2>Formulaire de saisie</h2>
    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Collecter les valeurs du formulaire
        $nom = htmlspecialchars($_POST['nom']);
        $prenom = htmlspecialchars($_POST['prenom']);
        $age = htmlspecialchars($_POST['age']);

        // Afficher les valeurs collectées
        echo "<h3>Informations reçues:</h3>";
        echo "<p>Nom: $nom</p>";
        echo "<p>Prénom: $prenom</p>";
        echo "<p>Âge: $age</p>";
    } else {
        // Afficher le formulaire
        echo '<form action="" method="post">
            <label for="nom">Nom :</label>
            <input type="text" id="nom" name="nom" required><br><br>

            <label for="prenom">Prénom :</label>
            <input type="text" id="prenom" name="prenom" required><br><br>

            <label for="age">Âge :</label>
            <input type="number" id="age" name="age" required><br><br>

            <input type="submit" value="Envoyer">
        </form>';
    }
    ?>
</body>
</html>
