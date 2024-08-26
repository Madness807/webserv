# Projet Webserv en C++ 98

Ce projet vise à construire un serveur HTTP en respectant la norme C++ 98, pour approfondir la connaissance du protocole HTTP et des principes de base de la programmation réseau.


## Fondamentaux du Serveur HTTP

### Fonctionnement d'un serveur HTTP
Réception de la Requête : Tout commence quand un client (généralement un navigateur web ou un robot d'indexation) envoie une requête HTTP au serveur. Cette requête inclut une méthode HTTP (comme GET, POST, DELETE), l'URL de la ressource demandée, et éventuellement d'autres en-têtes et données.

Analyse de la Requête : Le serveur reçoit la requête et l'analyse pour déterminer l'action requise. Cela implique d'extraire la méthode HTTP, l'URL demandée, et d'autres informations potentiellement incluses dans les en-têtes HTTP et le corps de la requête (pour les méthodes comme POST).

Traitement de la Requête : Selon la méthode HTTP et l'URL demandée, le serveur effectue l'action appropriée. Cela peut inclure la récupération d'un fichier statique depuis le système de fichiers, la génération dynamique d'une page web, ou l'exécution d'un script CGI pour générer du contenu dynamique.

Accès aux Ressources : Si la requête demande une ressource statique (comme une page HTML, une image, ou un fichier CSS), le serveur recherche le fichier dans son répertoire racine ou le chemin spécifié dans la configuration. Pour les contenus dynamiques, il peut exécuter des scripts ou des programmes externes.

Création de la Réponse : Une fois l'action requise terminée, le serveur prépare une réponse HTTP. Cette réponse inclut un code d'état (comme 200 OK ou 404 Not Found), des en-têtes HTTP (comme le type de contenu), et le corps de la réponse, qui peut contenir le contenu demandé, un message d'erreur, ou les résultats d'un script CGI.

Envoi de la Réponse : Le serveur envoie la réponse au client. Si la ressource a été trouvée et est accessible, le corps de la réponse contiendra les données demandées. Dans le cas contraire, le serveur peut renvoyer une page d'erreur ou un code d'état indiquant le problème.

Gestion des Connexions : Après l'envoi de la réponse, le serveur décide, en fonction des en-têtes HTTP (comme Connection: keep-alive), si la connexion doit être fermée ou maintenue ouverte pour de futures requêtes.

Logs et Monitoring : Le serveur enregistre la requête et la réponse dans ses logs, ce qui permet un suivi pour le débogage, la surveillance de la performance, et la sécurité.

### Rôle et gestion des méthodes HTTP: GET, POST, DELETE
| Méthode   | Description                                                                                             |
|:----------|:--------------------------------------------------------------------------------------------------------|
| GET       | Demande une représentation de la ressource spécifiée. Utilisée pour récupérer des données.              | 
| POST      | Envoie des données au serveur pour créer/mettre à jour une ressource.                                   | 
| HEAD      | Identique à GET, mais le serveur ne retourne que les en-têtes de réponse.                               | 
| PUT       | Remplace toutes les représentations actuelles de la ressource ciblée par la charge utile de la requête. | 
| DELETE    | Supprime la ressource spécifiée.                                                                        | 
| CONNECT   | Établit un tunnel vers le serveur identifié par la ressource ciblée.                                    | 
| OPTIONS   | Décrit les options de communication pour la ressource ciblée.                                           | 
| TRACE     | Effectue un test de boucle retour le long du chemin vers la ressource ciblée.                           | 
| PATCH     | Utilisée pour appliquer des modifications partielles à une ressource.                                   |

## Protocole HTTP

### Détails de la RFC HTTP
🔴Abordez les aspects clés de la RFC HTTP que vous avez implémentés.🔴

### Gestion des en-têtes HTTP
🔴Expliquez comment votre serveur gère les en-têtes HTTP.🔴

### Codes d'état HTTP

❕ Réponses Informatives (1xx)
| Code | Signification         | Explication                                                                 |
|------|-----------------------|-----------------------------------------------------------------------------|
| 100  | Continue              | La requête initiale a été reçue, le client peut continuer avec sa requête. |
| 101  | Switching Protocols   | Le serveur accepte la demande de changement de protocole du client.        |
| 102  | Processing            | La requête est en cours de traitement, réponse principalement utilisée par WebDAV. |

✅ Succès (2xx)
| Code | Signification     | Explication                                                             |
|------|-------------------|-------------------------------------------------------------------------|
| 200  | OK                | La requête a réussi.                                                    |
| 201  | Created           | La requête a réussi et une nouvelle ressource a été créée.              |
| 202  | Accepted          | La requête a été acceptée pour traitement, mais le traitement n'est pas terminé. |
| 204  | No Content        | La requête a réussi mais ne nécessite pas de retour d’information.     |
| 206  | Partial Content   | La requête a réussi et le client a reçu une partie du contenu demandé. |

⤴️ Redirections (3xx)
| Code | Signification     | Explication                                                         |
|------|-------------------|---------------------------------------------------------------------|
| 301  | Moved Permanently | La ressource a été déplacée de manière permanente vers une nouvelle URL. |
| 302  | Found             | La ressource demandée a été temporairement déplacée vers une nouvelle URL. |
| 304  | Not Modified      | Il n’y a pas eu de modification de la ressource depuis la dernière demande. |

🔴 Erreurs Client (4xx)
| Code | Signification         | Explication                                                                      |
|------|-----------------------|----------------------------------------------------------------------------------|
| 400  | Bad Request           | La syntaxe de la requête est erronée.                                            |
| 401  | Unauthorized          | Authentification requise pour accéder à la ressource.                            |
| 403  | Forbidden             | Le serveur a compris la requête, mais refuse de l'exécuter.                      |
| 404  | Not Found             | La ressource demandée n'a pas été trouvée.                                       |
| 405  | Method Not Allowed    | La méthode de requête est connue par le serveur mais n'a pas été activée pour la ressource. |

🔴 Erreurs Serveur (5xx)
| Code | Signification         | Explication                                                                 |
|------|-----------------------|-----------------------------------------------------------------------------|
| 500  | Internal Server Error | Une erreur interne du serveur a été rencontrée.                             |
| 501  | Not Implemented       | Le serveur ne prend pas en charge la fonctionnalité requise pour traiter la requête. |
| 502  | Bad Gateway           | Le serveur a reçu une réponse invalide de la part d'un serveur en amont.    |
| 503  | Service Unavailable   | Le serveur n'est pas prêt à traiter la requête (surcharge ou arrêt pour maintenance). |
| 504  | Gateway Timeout       | Le serveur agissant en tant que passerelle n'a pas reçu de réponse à temps. |

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




