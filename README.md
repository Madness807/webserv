# Projet Webserv en C++ 98

Ce projet vise à construire un serveur HTTP en respectant la norme C++ 98, pour approfondir la connaissance du protocole HTTP et des principes de base de la programmation réseau.

## Table des Matières

- [Fondamentaux du Serveur HTTP](#fondamentaux-du-serveur-http)
  - Fonctionnement d'un serveur HTTP
  - Rôle et gestion des méthodes HTTP: GET, POST, DELETE

- [Protocole HTTP](#protocole-http)
  - Détails de la RFC HTTP
  - Gestion des en-têtes HTTP
  - [Codes d'état HTTP](#codes-detat-http)

- [Interfaces d'Entrée/Sortie de Base](#interfaces-dentréesortie-de-base)
  - Lecture et écriture sur des sockets
  - Manipulation de chaînes de caractères

- [Création et Manipulation de Sockets](#création-et-manipulation-de-sockets)
  - Établissement de connexions

- [Résolution de Noms de Domaine et Adresses](#résolution-de-noms-de-domaine-et-adresses)
  - Fonction `getaddrinfo`

- [Gestion des Numéros d'Erreur](#gestion-des-numéros-derreur)
  - Utilisation de `strerror` et `gai_strerror`

- [Surveillance de Descripteurs de Fichiers](#surveillance-de-descripteurs-de-fichiers)
  - `select` et `poll`

- [Optimisation sur Linux avec epoll](#optimisation-sur-linux-avec-epoll)
  - `epoll_create`, `epoll_ctl`, `epoll_wait`

- [Notification d'Événements pour BSD](#notification-dévénements-pour-bsd)
  - `kqueue` et `kevent`

- [Manipulation des Attributs de Fichiers](#manipulation-des-attributs-de-fichiers)
  - Utilisation de `fcntl`

- [Gestion de Processus et Signaux](#gestion-de-processus-et-signaux)
  - `fork` et `execve`, gestion de signaux

- [Informations sur les Fichiers et Répertoires](#informations-sur-les-fichiers-et-répertoires)
  - `stat`, `opendir`, `readdir`, `closedir`

- [Sécurité](#sécurité)
  - Sécurisation des communications avec SSL/TLS
  - Contrôle d'accès et authentification

- [Configuration et Optimisation du Serveur](#configuration-et-optimisation-du-serveur)
  - Fichier de configuration
  - Pages d'erreur par défaut
  - Limitation de la taille du body des clients

- [Développement Web Complet](#développement-web-complet)
  - Support de différents types de contenu
  - Intégration avec des bases de données

- [Tests et Débogage](#tests-et-débogage)
  - Stratégies de tests avancées
  - Outils et techniques de débogage

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



## Interfaces d'Entrée/Sortie de Base

### Lecture et écriture sur des sockets
Détaillez comment votre serveur lit et écrit sur des sockets réseau.

### Manipulation de chaînes de caractères
Expliquez les stratégies utilisées pour manipuler les chaînes de caractères en C++ 98.

## Création et Manipulation de Sockets

### Établissement de connexions
Décrit le processus d'établissement de connexions réseau avec les clients.

## Résolution de Noms de Domaine et Adresses

### Fonction `getaddrinfo`
Expliquez comment vous utilisez `getaddrinfo` pour la résolution de noms de domaine.

## Gestion des Numéros d'Erreur

### Utilisation de `strerror` et `gai_strerror`
Détaillez comment votre serveur traite les erreurs réseau et système.

## Surveillance de Descripteurs de Fichiers

### `select` et `poll`
Décrivez votre approche pour la surveillance des descripteurs de fichiers.

## Optimisation sur Linux avec epoll

### `epoll_create`, `epoll_ctl`, `epoll_wait`
Expliquez comment et pourquoi vous utilisez epoll sur Linux pour une surveillance efficace.

## Notification d'Événements pour BSD

### `kqueue` et `kevent`
Discutez de l'utilisation de kqueue pour la gestion d'événements sur BSD.

## Manipulation des Attributs de Fichiers

### Utilisation de `fcntl`
Expliquez comment vous utilisez `fcntl` pour manipuler les attributs de fichiers ouverts.

## Gestion de Processus et Signaux

### `fork` et `execve`, gestion de signaux
Détaillez la gestion des processus et des signaux dans votre serveur.

## Informations sur les Fichiers et Répertoires

### `stat`, `opendir`, `readdir`, `closedir`
Expliquez comment votre serveur interagit avec le système de fichiers.

## Sécurité

### Sécurisation des communications avec SSL/TLS
Discutez de l'importance de sécuriser les communications et comment cela pourrait être implémenté.

### Contrôle d'accès et authentification
Expliquez les mécanismes d'authentification et de contrôle d'accès que vous pourriez envisager.

## Configuration et Optimisation du Serveur

### Fichier de configuration
Détaillez comment le fichier de configuration est structuré et utilisé.

### Pages d'erreur par défaut
Expliquez comment vous gérez les pages d'erreur par défaut.

### Limitation de la taille du body des clients
Discutez des raisons et des méthodes pour limiter la taille du corps des requêtes clients.

## Développement Web Complet

### Support de différents types de contenu
Décrit comment votre serveur traite différents types de contenu.

### Intégration avec des bases de données
Expliquez comment, théoriquement, votre serveur pourrait être étendu pour interagir avec une base de données.

## Tests et Débogage

### Stratégies de tests avancées
Décrivez les méthodes de test que vous avez utilisées pour assurer la fiabilité de votre serveur.

### Outils et techniques de débogage
Partagez les outils et techniques de débogage qui se sont avérés utiles.

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




