#!/usr/bin/env python3
import cgi
import html

def print_html_form():
    print("Content-Type: text/html, charset=utf-8")
    print()
    print("""
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
        <form action="" method="post">
            <label for="nom">Nom :</label>
            <input type="text" id="nom" name="nom" required><br><br>

            <label for="prenom">Prénom :</label>
            <input type="text" id="prenom" name="prenom" required><br><br>

            <label for="age">Âge :</label>
            <input type="number" id="age" name="age" required><br><br>

            <input type="submit" value="Envoyer">
        </form>
    </body>
    </html>
    """)

def main():
    form = cgi.FieldStorage()
    if "nom" in form and "prenom" in form and "age" in form:
        nom = html.escape(form.getfirst("nom", ""))
        prenom = html.escape(form.getfirst("prenom", ""))
        age = html.escape(form.getfirst("age", ""))
        
        print("Content-type: text/html")
        print()
        print(f"""
        <!DOCTYPE html>
        <html lang="fr">
        <head>
            <meta charset="UTF-8">
            <title>Réponse du Formulaire</title>
        </head>
        <body>
            <h2>Informations reçues</h2>
            <p>Nom: {nom}</p>
            <p>Prénom: {prenom}</p>
            <p>Âge: {age}</p>
        </body>
        </html>
        """)
    else:
        print_html_form()

if __name__ == "__main__":
    main()
