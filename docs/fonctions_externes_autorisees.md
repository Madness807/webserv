
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

Ce tableau offre un aperçu des fonctions que vous êtes autorisé à utiliser pour le développement de votre serveur HTTP, avec les bibliothèques correspondantes.
