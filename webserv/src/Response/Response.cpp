#include "../../include/Response/Response.hpp"

// Méthodes
// GETTERS
// SETTERS


// Constructeur
Response::Response() {
}
// Destructeur
Response::~Response() {
}


/*
Response.cpp
Rôle: Construit la réponse HTTP à envoyer au client.
Fonctions:
    Permet de construire une réponse HTTP, incluant le statut, les en-têtes, et le corps de la réponse.
    Offre des méthodes pour ajouter des en-têtes, définir le corps de la réponse, et éventuellement gérer les types de contenu MIME.
    Génère la réponse finale sous forme de chaîne ou de bytes à envoyer sur le réseau.
*/