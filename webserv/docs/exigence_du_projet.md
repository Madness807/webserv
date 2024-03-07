# Exigences du Projet Webserv

## Fonctionnalités Générales

- [ ] Votre programme doit prendre un fichier de configuration en argument ou utiliser un chemin par défaut.
- [ ] Vous ne pouvez pas exécuter un autre serveur web.
- [ ] Votre serveur ne doit jamais bloquer et le client doit être correctement renvoyé si nécessaire.
- [ ] Il doit être non bloquant et utiliser qu’un seul `poll()` (ou équivalent) pour toutes les opérations entrées/sorties entre le client et le serveur (listen inclus).
- [ ] `poll()` (ou équivalent) doit vérifier la lecture et l’écriture en même temps.
- [ ] Vous ne devriez jamais faire une opération de lecture ou une opération d’écriture sans passer par `poll()` (ou équivalent).
- [ ] La vérification de la valeur de `errno` est strictement interdite après une opération de lecture ou d’écriture.
- [ ] Vous n’avez pas besoin d’utiliser `poll()` (ou équivalent) avant de lire votre fichier de configuration.
- [ ] Vous pouvez utiliser chaque macro et définir comme `FD_SET`, `FD_CLR`, `FD_ISSET`, `FD_ZERO` (comprendre ce qu’elles font et comment elles le font est très utile).
- [ ] Une requête à votre serveur ne devrait jamais se bloquer indéfiniment.
- [ ] Votre serveur doit être compatible avec le navigateur web de votre choix.
- [ ] NGINX est considéré comme conforme à HTTP 1.1 et peut être utilisé pour comparer les en-têtes et les comportements de réponse.
- [ ] Vos codes d’état de réponse HTTP doivent être exacts.
- [ ] Votre serveur doit avoir des pages d’erreur par défaut si aucune n’est fournie.
- [ ] Vous ne pouvez pas utiliser `fork` pour autre chose que CGI (comme PHP ou Python, etc).
- [ ] Vous devriez pouvoir servir un site web entièrement statique.
- [ ] Le client devrait pouvoir téléverser des fichiers.
- [ ] Vous avez besoin au moins des méthodes GET, POST, et DELETE.
- [ ] Stress testez votre serveur, il doit rester disponible à tout prix.
- [ ] Votre serveur doit pouvoir écouter sur plusieurs ports (cf. Fichier de configuration).

## Fichier de Configuration

- [ ] Choisissez le port et l’host de chaque "serveur".
- [ ] Setup `server_names` ou pas.
- [ ] Le premier serveur pour un host:port sera le serveur par défaut pour cet host:port (il répondra à toutes les requêtes qui n’appartiennent pas à un autre serveur).
- [ ] Setup des pages d’erreur par défaut.
- [ ] Limitez la taille du body des clients.

### Setup des Routes

- [ ] Définissez une liste de méthodes HTTP acceptées pour la route.
- [ ] Définissez une redirection HTTP.
- [ ] Définissez un répertoire ou un fichier à partir duquel le fichier doit être recherché (exemple : si l’URL `/kapouet` est rootée sur `/tmp/www`, l’URL `/kapouet/pouic/toto/pouet` correspond à `/tmp/www/pouic/toto/pouet`).
- [ ] Activez ou désactivez le listing des répertoires.
- [ ] Set un fichier par défaut comme réponse si la requête est un répertoire.
- [ ] Exécutez CGI en fonction de certaines extensions de fichier (exemple : `.php`).
  - [ ] Faites-le fonctionner avec les méthodes POST et GET.
  - [ ] Rendez la route capable d’accepter les fichiers téléversés et configurez où cela doit être enregistré.
- [ ] Le CGI doit être appelé avec le fichier demandé comme premier argument et exécuté dans le bon répertoire pour l’accès au fichier de chemin relatif.
- [ ] Votre serveur devrait fonctionner avec un seul CGI (php-CGI, Python, etc.).

### Note

- [ ] Vous devez fournir des fichiers de configuration et des fichiers de base par défaut pour tester et démontrer que chaque fonctionnalité fonctionne pendant l’évaluation.
