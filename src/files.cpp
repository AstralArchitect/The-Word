#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

std::vector<std::string> getWords(std::string path)
{
    std::vector<std::string> words;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
        return words;
    }

    std::string word;
    while (std::getline(file, word)) {
        words.push_back(word);
    }

    file.close();

    // verifie the word list
    for (std::string word : words)
    {
        if (word.size() != 5)
        {
            std::cerr << "Le mot " << word << " n'a pas 5 lettres." << std::endl;
            exit(1);
        }
    }

    return words;
}