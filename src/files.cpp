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

    return words;
}

int addWord(std::string word, std::string path) {
    std::fstream file(path, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
        return EXIT_FAILURE;
    }

    file << std::endl << word;

    if (!file) {
        std::cerr << "Erreur lors de l'écriture du fichier : " << path << std::endl;
        return EXIT_FAILURE;
    }

    file.close();

    return EXIT_SUCCESS;
}