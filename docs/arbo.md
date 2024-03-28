webserv/
│
├── Makefile                     # Makefile pour compiler le projet
│
├── config/                      # Dossiers pour les fichiers de configuration
│   └── default.conf             # Fichier de configuration par défaut
│
├── src/                         # Dossier source contenant les fichiers .cpp
│   ├── main.cpp                 # Point d'entrée du serveur
│   ├── Server.cpp               # Implémentation de la classe Server
│   ├── Request.cpp              # Gestion des requêtes HTTP
│   ├── Response.cpp             # Gestion des réponses HTTP
│   ├── ConfigParser.cpp         # Analyseur du fichier de configuration
│   ├── Connection.cpp           # Gestion des connexions clients
│   └── CGIHandler.cpp           # Gestion des exécutions CGI
│
├── include/                     # Dossier pour les fichiers d'en-tête .hpp
│   ├── Server.hpp               # Déclaration de la classe Server
│   ├── Request.hpp              # Déclaration pour la gestion des requêtes
│   ├── Response.hpp             # Déclaration pour la gestion des réponses
│   ├── ConfigParser.hpp         # Déclaration de l'analyseur de configuration
│   ├── Connection.hpp           # Déclaration pour la gestion des connexions
│   └── CGIHandler.hpp           # Déclaration pour la gestion des CGI
│
├── assets/                      # Dossier pour les ressources web (images, CSS, JS)
│   ├── css/                     # Feuilles de style CSS
│   └── js/                      # Scripts JavaScript
│
├── test/                        # Dossier pour les tests unitaires et d'intégration
│   └── config_test.conf         # Fichier de configuration pour les tests
│
└── docs/                        # Documentation du projet, si nécessaire
