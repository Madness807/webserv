# webserv

# Table des matieres

- [Fonctions Externes et Librairies avec Paramètres et Valeurs de Retour](#fonctions-externes-et-librairies-avec-paramètres-et-valeurs-de-retour)
  - [Interfaces d'entrée/sortie de base](#unistdh)
  - [Création et manipulation de sockets](#syssocketh)
  - [Manipulation de chaînes de caractères](#stringh)
  - [Résolution de noms de domaine](#netdbh)
  - [Gestion des numéros d'erreur](#errnoh)
  - [Manipulation d'adresses réseau](#netinetinh)
  - [Surveillance de descripteurs de fichiers](#sysselecth-et-pollh)
  - [Surveillance efficace de descripteurs de fichiers sur Linux](#sysepollh)
  - [Notification d'événements pour BSD](#syseventh)
  - [Manipulation des attributs d'un fichier ouvert](#fcntlh)
  - [Gestion de processus, signaux, informations sur les fichiers, et répertoires](#syswaith-signalh-sysstath-direnth)

- [Methodes HTTP avec leur valeur de retour](##MethodesHTTPavecleurvaleurderetour)


# Fonctions Externes Autorisées et Leur Utilité

### `netdb.h`
**Utilité**: Fonctions pour la résolution des noms de domaine et la manipulation des informations de réseau.

| Fonction          | Utilité                                 | Paramètres                                               | Valeur de retour                                    |
|-------------------|-----------------------------------------|----------------------------------------------------------|-----------------------------------------------------|
| `gai_strerror`    | Renvoie une description de l'erreur     | int errcode                                              | const char* (message d'erreur)                      |
| `getaddrinfo`     | Récupère les informations d'adresse     | const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res | 0 en cas de succès, autre valeur en cas d'erreur   |
| `freeaddrinfo`    | Libère les informations d'adresse       | struct addrinfo *res                                     | void                                                |
| `getprotobyname`  | Obtient les informations de protocole   | const char *name                                         | struct protoent* ou NULL                            |

### `errno.h`
**Utilité**: Définit le numéro d'erreur du dernier appel de fonction échoué.

| Fonction | Utilité                                   | Paramètres     | Valeur de retour                                |
|----------|-------------------------------------------|----------------|-------------------------------------------------|
| `errno`  | Numéro de l'erreur du dernier appel       | (pas de paramètre, mais une variable externe)  | int (numéro d'erreur)                            |

### `netinet/in.h`
**Utilité**: Définit des structures et des fonctions pour la manipulation d'adresses réseau.

| Fonction        | Utilité                                   | Paramètres                                 | Valeur de retour                             |
|-----------------|-------------------------------------------|--------------------------------------------|----------------------------------------------|
| `htons`/`htonl` | Convertit des valeurs ordre des octets    | uint16_t hostshort, uint32_t hostlong      | valeur en ordre des octets réseau            |
| `ntohs`/`ntohl` | Convertit des valeurs ordre des octets    | uint16_t netshort, uint32_t netlong        | valeur en ordre des octets hôte              |

### `sys/select.h` et `poll.h`
**Utilité**: Fournissent des interfaces pour surveiller de multiples descripteurs de fichiers.

| Fonction | Utilité                                   | Paramètres                                                | Valeur de retour                             |
|----------|-------------------------------------------|-----------------------------------------------------------|----------------------------------------------|
| `select` | Surveille des descripteurs de fichiers    | int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout | int (nombre de descripteurs) ou -1 (erreur)  |
| `poll`   | Comme `select`, mais plus efficace        | struct pollfd *fds, nfds_t nfds, int timeout              | int (nombre de descripteurs) ou -1 (erreur)  |

### `sys/epoll.h`
**Utilité**: Offre un mécanisme efficace pour surveiller de multiples descripteurs de fichiers sur Linux.

| Fonction              | Utilité                                 | Paramètres                                           | Valeur de retour                                    |
|-----------------------|-----------------------------------------|------------------------------------------------------|-----------------------------------------------------|
| `epoll_create`, `epoll_ctl`, `epoll_wait` | Gère des descripteurs de fichiers    | int size, int epfd, int op, int fd, struct epoll_event *event, struct epoll_event *events, int maxevents, int timeout | int (succès ou nombre d'événements) ou -1 (erreur)  |

### `sys/event.h`
**Utilité**: Propose des interfaces pour les mécanismes de notification d'événements, spécifiques à BSD.

| Fonction     | Utilité                                 | Paramètres                                       | Valeur de retour                                    |
|--------------|-----------------------------------------|--------------------------------------------------|-----------------------------------------------------|
| `kqueue`, `kevent`| Mécanisme de notification d'événements | (divers selon la fonction)                       | int (succès ou nombre d'événements) ou -1 (erreur)  |

### `fcntl.h`
**Utilité**: Fournit des interfaces pour manipuler les attributs d'un fichier ouvert.

| Fonction | Utilité                                   | Paramètres                                      | Valeur de retour                                    |
|----------|-------------------------------------------|-------------------------------------------------|-----------------------------------------------------|
| `fcntl`  | Manipule le descripteur de fichier        | int fd, int cmd, ...                            | Divers (succès) ou -1 (erreur)                       |
| `open`   | Ouvre un fichier                          | const char *pathname, int flags, mode_t mode    | Descripteur de fichier ou -1 en cas d'erreur        |

### `sys/wait.h`, `signal.h`, `sys/stat.h`, `dirent.h`
**Utilité**: Fournissent diverses fonctionnalités pour la gestion de processus, signaux, informations sur les fichiers et manipulation des répertoires.

| Fonction           | Utilité                                 | Paramètres                                       | Valeur de retour                                    |
|--------------------|-----------------------------------------|--------------------------------------------------|-----------------------------------------------------|
| `waitpid`          | Attend la fin d'un processus fils       | pid_t pid, int *status, int options              | pid_t (PID du processus) ou -1 (erreur)             |
| `kill`             | Envoie un signal à un processus         | pid_t pid, int sig                               | 0 (succès) ou -1 (erreur)                           |
| `signal`           | Installe un gestionnaire de signal      | int signum, sighandler_t handler                 | Pointeur vers l'ancien gestionnaire ou SIG_ERR      |
| `stat`             | Obtient les informations sur le fichier | const char *pathname, struct stat *statbuf       | 0 (succès) ou -1 (erreur)                           |
| `opendir`, `readdir`, `closedir` | Gère la lecture dans les répertoires | const char *name, DIR *dirp                      | DIR* (répertoire) ou NULL, struct dirent* ou NULL   |

Note : Les descriptions des paramètres et valeurs de retour sont simplifiées pour une lecture facile. Pour des détails complets et précis, y compris les types de données et les cas d'erreur spécifiques, il est recommandé de consulter la documentation de la librairie standard de votre système ou environnement de développement.



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
