#include "../include/Server.hpp"

// Méthodes
// GETTERS
// SETTERS

// Constructeur
Server::Server(){
}
// Destructeur
Server::~Server(){
}



/*
ecoute sur les ports specifiés dans le fichier de configuration
accepte les connexions entrantes et cree des objets de type Request pour chaque requete recu
utilise des objets de type Response pour repondre aux requetes
gere la logique de selection/polling pour traiter les connexions de maniere non bloquante
*/