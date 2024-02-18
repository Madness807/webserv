# webserv


# Fonctions Externes Autorisées et Leur Utilité

| Fonction        | Utilité                                                                 | Librairie       |
|-----------------|-------------------------------------------------------------------------|-----------------|
| `execve`        | Exécute un programme                                                    | `unistd.h`      |
| `dup`/`dup2`    | Duplique un descripteur de fichier                                      | `unistd.h`      |
| `pipe`          | Crée un tube (pipe) pour la communication entre processus               | `unistd.h`      |
| `strerror`      | Renvoie une chaîne décrivant l'erreur numéro d'erreur                   | `string.h`      |
| `gai_strerror`  | Renvoie une description de l'erreur pour getaddrinfo                    | `netdb.h`       |
| `errno`         | Numéro de l'erreur du dernier appel de fonction                         | `errno.h`       |
| `fork`          | Crée un processus fils                                                  | `unistd.h`      |
| `socketpair`    | Crée une paire de sockets connectés                                      | `sys/socket.h`  |
| `htons`/`htonl` | Convertit des valeurs entre l'ordre des octets hôte et réseau           | `netinet/in.h`  |
| `ntohs`/`ntohl` | Convertit des valeurs entre l'ordre des octets réseau et hôte           | `netinet/in.h`  |
| `select`        | Surveille un ensemble de descripteurs de fichiers pour voir s'ils sont prêts à effectuer une E/S | `sys/select.h` |
| `poll`          | Comme `select`, mais potentiellement plus efficace                      | `poll.h`        |
| `epoll_create`, `epoll_ctl`, `epoll_wait` | Gère de multiples descripteurs de fichiers de manière efficace | `sys/epoll.h` |
| `kqueue`, `kevent`| Mécanisme de notification d'événements pour BSD                         | `sys/event.h`   |
| `socket`        | Crée un point de communication (socket)                                 | `sys/socket.h`  |
| `accept`        | Accepte une connexion sur un socket                                     | `sys/socket.h`  |
| `listen`        | Écoute sur un socket                                                    | `sys/socket.h`  |
| `send`/`recv`   | Envoie/reçoit des données sur un socket                                 | `sys/socket.h`  |
| `chdir`         | Change le répertoire courant du processus                               | `unistd.h`      |
| `bind`          | Associe une adresse à un socket                                         | `sys/socket.h`  |
| `connect`       | Établit une connexion sur un socket                                     | `sys/socket.h`  |
| `getaddrinfo`, `freeaddrinfo`| Récupère les informations d'adresse, libère les informations d'adresse| `netdb.h`     |
| `setsockopt`    | Configure les options du socket                                         | `sys/socket.h`  |
| `getsockname`   | Obtient l'adresse locale associée à un socket                           | `sys/socket.h`  |
| `getprotobyname`| Obtient les informations de protocole par nom                          | `netdb.h`       |
| `fcntl`         | Manipule le descripteur de fichier                                      | `fcntl.h`       |
| `close`         | Ferme un descripteur de fichier                                         | `unistd.h`      |
| `read`/`write`  | Lit/écrit sur un descripteur de fichier                                 | `unistd.h`      |
| `waitpid`       | Attend la fin d'exécution d'un processus fils                           | `sys/wait.h`    |
| `kill`          | Envoie un signal à un processus                                         | `signal.h`      |
| `signal`        | Installe un gestionnaire de signal                                      | `signal.h`      |
| `access`        | Vérifie les droits d'accès d'un fichier                                 | `unistd.h`      |
| `stat`          | Obtient les informations sur le fichier                                 | `sys/stat.h`    |
| `open`          | Ouvre un fichier                                                        | `fcntl.h`       |
| `opendir`, `readdir`, `closedir`| Gère la lecture dans les répertoires                           | `dirent.h`      |


# Methodes HTTP avec leur valeur de retour

| Méthode   | Description                                                                                             | Codes d'erreur courants                 | Signification des codes                                   |
|:----------|:--------------------------------------------------------------------------------------------------------|:----------------------------------------|:----------------------------------------------------------|
| GET       | Demande une représentation de la ressource spécifiée. Utilisée pour récupérer des données.              | 200 OK, 404 Not Found                   | Succès ou ressource non trouvée.                          |
| POST      | Envoie des données au serveur pour créer/mettre à jour une ressource.                                   | 200 OK, 201 Created, 400 Bad Request    | Succès, ressource créée ou requête invalide.              |
| HEAD      | Identique à GET, mais le serveur ne retourne que les en-têtes de réponse.                               | 200 OK, 404 Not Found                   | Succès ou ressource non trouvée.                          |
| PUT       | Remplace toutes les représentations actuelles de la ressource ciblée par la charge utile de la requête. | 200 OK, 201 Created, 204 No Content     | Succès, ressource créée ou pas de contenu.                |
| DELETE    | Supprime la ressource spécifiée.                                                                        | 200 OK, 202 Accepted, 404 Not Found     | Succès, accepté pour traitement ou ressource non trouvée. |
| CONNECT   | Établit un tunnel vers le serveur identifié par la ressource ciblée.                                    | 200 OK, 400 Bad Request                 | Succès ou requête invalide.                               |
| OPTIONS   | Décrit les options de communication pour la ressource ciblée.                                           | 200 OK, 204 No Content                  | Succès ou pas de contenu.                                 |
| TRACE     | Effectue un test de boucle retour le long du chemin vers la ressource ciblée.                           | 200 OK, 405 Method Not Allowed          | Succès ou méthode non autorisée.                          |
| PATCH     | Utilisée pour appliquer des modifications partielles à une ressource.                                   | 200 OK, 204 No Content, 400 Bad Request | Succès, pas de contenu ou requête invalide.               |
