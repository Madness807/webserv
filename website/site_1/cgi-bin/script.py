
#!/usr/bin/env python3
import cgi
import html
import os

UPLOAD_DIR = "/website/site_1/page/uploads"

def print_html_form():
    print("Content-Type: text/html; charset=utf-8")
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

            <input type="submit" name="submit_info" value="Envoyer">
        </form>

        <h2>Upload d'une image</h2>
        <form action="" method="post" enctype="multipart/form-data">
            <label for="image">Image :</label>
            <input type="file" id="image" name="image" accept="image/*"><br><br>
            <input type="submit" name="upload_image" value="Upload">
        </form>

        <h2>Suppression d'un fichier</h2>
        <form action="" method="post">
            <label for="delete_filename">Nom du fichier à supprimer :</label>
            <input type="text" id="delete_filename" name="delete_filename" required><br><br>
            <input type="submit" name="delete_file" value="Delete">
        </form>
    </body>
    </html>
    """)

def main():
    form = cgi.FieldStorage()

    if "submit_info" in form:
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

    elif "upload_image" in form:
        fileitem = form["image"]
        if fileitem.filename:
            fn = os.path.basename(fileitem.filename.replace("\\", "/"))
            filepath = os.path.join(UPLOAD_DIR, fn)
            
            # Vérifiez si le fichier existe déjà pour éviter l'écrasement
            if not os.path.exists(filepath):
                try:
                    with open(filepath, 'wb') as f:
                        f.write(fileitem.file.read())
                    print("Content-type: text/html")
                    print()
                    print(f"""
                    <!DOCTYPE html>
                    <html lang="fr">
                    <head>
                        <meta charset="UTF-8">
                        <title>Image Upload</title>
                    </head>
                    <body>
... (49lignes restantes)
Réduire
message.txt
6 Ko
﻿
#!/usr/bin/env python3
import cgi
import html
import os

UPLOAD_DIR = "/website/site_1/page/uploads"

def print_html_form():
    print("Content-Type: text/html; charset=utf-8")
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

            <input type="submit" name="submit_info" value="Envoyer">
        </form>

        <h2>Upload d'une image</h2>
        <form action="" method="post" enctype="multipart/form-data">
            <label for="image">Image :</label>
            <input type="file" id="image" name="image" accept="image/*"><br><br>
            <input type="submit" name="upload_image" value="Upload">
        </form>

        <h2>Suppression d'un fichier</h2>
        <form action="" method="post">
            <label for="delete_filename">Nom du fichier à supprimer :</label>
            <input type="text" id="delete_filename" name="delete_filename" required><br><br>
            <input type="submit" name="delete_file" value="Delete">
        </form>
    </body>
    </html>
    """)

def main():
    form = cgi.FieldStorage()

    if "submit_info" in form:
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

    elif "upload_image" in form:
        fileitem = form["image"]
        if fileitem.filename:
            fn = os.path.basename(fileitem.filename.replace("\\", "/"))
            filepath = os.path.join(UPLOAD_DIR, fn)
            
            # Vérifiez si le fichier existe déjà pour éviter l'écrasement
            if not os.path.exists(filepath):
                try:
                    with open(filepath, 'wb') as f:
                        f.write(fileitem.file.read())
                    print("Content-type: text/html")
                    print()
                    print(f"""
                    <!DOCTYPE html>
                    <html lang="fr">
                    <head>
                        <meta charset="UTF-8">
                        <title>Image Upload</title>
                    </head>
                    <body>
                        <h2>Image téléchargée</h2>
                        <p>Image: <img src="{filepath}" alt="Uploaded Image"></p>
                    </body>
                    </html>
                    """)
                except Exception as e:
                    print("Content-type: text/html")
                    print()
                    print(f"<html><body><h2>Erreur lors du téléchargement</h2><p>{str(e)}</p></body></html>")
            else:
                print("Content-type: text/html")
                print()
                print("<html><body><h2>Erreur: Fichier existe déjà</h2></body></html>")
        else:
            print("Content-type: text/html")
            print()
            print("<html><body><h2>Aucun fichier sélectionné</h2></body></html>")

    elif "delete_file" in form:
        delete_filename = html.escape(form.getfirst("delete_filename", ""))
        file_path = os.path.join(UPLOAD_DIR, delete_filename)

        if os.path.isfile(file_path):
            os.remove(file_path)
            message = f"Le fichier '{delete_filename}' a été supprimé."
        else:
            message = f"Le fichier '{delete_filename}' n'existe pas."

        print("Content-type: text/html")
        print()
        print(f"""
        <!DOCTYPE html>
        <html lang="fr">
        <head>
            <meta charset="UTF-8">
            <title>Suppression de fichier</title>
        </head>
        <body>
            <h2>Résultat de la suppression</h2>
            <p>{message}</p>
        </body>
        </html>
        """)

    else:
        print_html_form()

if __name__ == "__main__":
    main()