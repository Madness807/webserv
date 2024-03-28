#include <iostream>
#include <list>
#include <map>

int main() {
    // Déclaration de la liste contenant des maps
    std::list<std::map<std::string, std::string>> list_of_maps;

    // Exemple de données à insérer dans la liste de maps
    std::map<std::string, std::string> map1 = {{"key1", "value1"}, {"key2", "value2"}};
    std::map<std::string, std::string> map2 = {{"key3", "value3"}, {"key4", "value4"}};

    // Ajout des maps à la liste
    list_of_maps.push_back(map1);
    list_of_maps.push_back(map2);

    // Parcours de la liste et affichage des éléments
    for (const auto& map : list_of_maps) {
        for (const auto& pair : map) {
            std::cout << pair.first << " : " << pair.second << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}