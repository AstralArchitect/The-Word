#include <iostream>
#include <algorithm>
#include <files.hpp>
#include <ctime>
#include <cstring>

std::string checkWord(std::string trial, std::string word, std::vector<char>& forbiddenLetters);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::vector<std::string> words = getWords((std::string)"res/dico.txt");
    std::vector<std::string> unknowWords;
    std::vector<char> forbiddenLetters;
    std::string word = words[rand() % words.size()];
    std::string trial;
    const unsigned short nbTrial = 5;
    unsigned short actualTrial = 0;

    // process cheat mode
    bool cheatMod = false;
    if (argc == 2 && strcmp("cheat", argv[1]) == 0)
    {
        cheatMod = true;
        std::cout << word << std::endl;
    }
    
    do
    {
        if (cheatMod)
            for (size_t i = 0; i < forbiddenLetters.size(); i++)
                std::cout << forbiddenLetters[i] << " ";
        if (cheatMod)
            std::cout << std::endl;
        
        
        std::cout << "Entrez un mot (essais n°" << actualTrial << "): ";
        std::cin >> trial;

        if (trial.size() != 5)
        {
            std::cout << "Entrez un mot de 5 lettes." << std::endl;
            continue;
        }

        if (trial == word)
        {
            std::cout << "Bravo, vous avez trouvé le mot : " << word << std::endl;
            break;
        }
        else if(actualTrial < nbTrial - 1)
        {
            if (std::find(words.begin(), words.end(), trial) == words.end()) {
                std::cout << "Le mot n'existe pas dans le dictionnaire." << std::endl;
                unknowWords.push_back(trial);
                continue;
            }

            std::string indice = checkWord(trial, word, forbiddenLetters);
            if (indice == "")
            {
                std::cout << "le mot ne contient pas une des lettres que vous avez entré." << std::endl;
                continue;
            }
            
            std::cout << "Ce n'est pas le bon mot, réessayez. (" << indice << ")" << std::endl;
        }
        else
        {
            std::cout << "Perdu ! Le mot était " << word << std::endl;
        }
        
        
        actualTrial++;
    } while (actualTrial < nbTrial);

    for (size_t i = 0; i < unknowWords.size(); i++)
    {
        std::string rep;
        std::cout << "Voulez-vous ajouter " << unknowWords[i] << " au dictionnaire ?(y/n)" << std::endl;
        std::cin >> rep;

        if (rep == "y" || rep == "Y")
        {
            addWord(unknowWords[i], "res/dico.txt");
        }
    }
    
    return EXIT_SUCCESS;
}

std::string checkWord(std::string trial, std::string word, std::vector<char>& forbiddenLetters) {
    std::string result(5, '-');

    for (unsigned long i = 0; i < std::min(trial.size(), word.size()); i++)
    {
        if(std::find(forbiddenLetters.begin(), forbiddenLetters.end(), trial[i]) != forbiddenLetters.end())
            return "";
    }
    

    for (unsigned long i = 0; i < std::min(trial.size(), word.size()); i++) {
        if (trial[i] == word[i])
            result[i] = word[i];
        else if (std::find(word.begin(), word.end(), trial[i]) != word.end())
            result[i] = '*';
        else
            forbiddenLetters.push_back(trial[i]);
    }

    return result;
}