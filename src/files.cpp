#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <ZipFile.h>

#define LOWER_CASE_PATH "res/tmp_lowercase.txt"

// returns the path of the downloaded file
std::string downloadFile(std::string const& url)
{
    std::string path = "res/archive.zip";
    std::string command = "curl -o " + path + " " + url + " --silent";
    system(command.c_str());
    return path;
}

void sortDico(std::string const& src, std::string const& dest)
{
    const std::string lowerCase = LOWER_CASE_PATH;
    std::string command1 = "cat " + src + " | LC_ALL=C grep -xE '[A-z]{5}' > " + lowerCase;
    std::string command2 = "tr '[:upper:]' '[:lower:]' < " + lowerCase + " > " + dest;
    // Execute the commands
    system(command1.c_str());
    system(command2.c_str());
}

std::vector<std::string> getWords()
{
    const std::string url = "http://www.3zsoftware.com/listes/liste_francais.zip";
    const std::string baseFileName = "liste_francais.txt";
    const std::string brutDicoPath = "res/tmp_dico.txt";
    const std::string dicoPath = "res/dico.txt";
    // load the dictionnary into a std::vector
    std::vector<std::string> words;

    std::ifstream file(dicoPath);
    if (!file.is_open()) {
        // download, extract and sort the dictionnary
        std::cout << "Téléchargement du dictionnaire..." << std::endl;
        std::string zipPath = downloadFile(url);
        ZipFile::ExtractFile(zipPath, baseFileName, brutDicoPath);
        sortDico(brutDicoPath, dicoPath);
        // remove temporary files
        std::remove(brutDicoPath.c_str());
        std::remove(LOWER_CASE_PATH);
        std::remove(zipPath.c_str());
        // retest the opening
        file.open(dicoPath);
        if (!file.is_open())
        {
            std::cerr << "Impossible d'ouvrir le fichier " << dicoPath << std::endl;
        }
        std::cout << "Dictionnaire téléchargé" << std::endl;
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