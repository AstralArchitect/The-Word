#include <iostream>
#include <algorithm>
#include <files.hpp>
#include <ctime>
#include <cstring>

std::string checkWord(std::string const& trial, std::string const&  word);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::vector<std::string> words = getWords((std::string)"res/dico.txt");
    std::string word = words[rand() % words.size()];
    std::string trial;
    const unsigned short maxTrial = 5;
    unsigned short actualTrial = 0;

    if (argc == 2 && strcmp("cheat", argv[1]) == 0)
    {
        std::cout << word << std::endl;
    }
    
    do
    {   
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
        else if(trial == ".exit")
        {
            std::cout << "Abandon" << std::endl << "Le mot était " << word << std::endl;
            break;
        }
        else if(actualTrial < maxTrial - 1)
        {
            if (std::find(words.begin(), words.end(), trial) == words.end()) {
                std::cout << "Le mot n'existe pas dans le dictionnaire." << std::endl;
                continue;
            }

            std::string indice = checkWord(trial, word);
            
            std::cout << "Ce n'est pas le bon mot, réessayez. (" << indice << ")" << std::endl;
        }
        else
        {
            std::cout << "Perdu ! Le mot était " << word << std::endl;
        }
        
        
        actualTrial++;
    } while (actualTrial < maxTrial);
    
    return EXIT_SUCCESS;
}

std::string checkWord(std::string const& trial, std::string const& word) {
    std::string result(5, '-');

    for (unsigned long i = 0; i < std::min(trial.size(), word.size()); i++) {
        if (trial[i] == word[i])
            result[i] = word[i];
        else if (std::find(word.begin(), word.end(), trial[i]) != word.end())
            result[i] = '*';
    }

    return result;
}