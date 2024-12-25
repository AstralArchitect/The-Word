#include <iostream>
#include <algorithm>
#include <files.hpp>
#include <ctime>
#include <cstring>

std::string checkWord(std::string const& trial, std::string word);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::vector<std::string> words = getWords();
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

std::string checkWord(std::string const& trial, std::string word)
{
    std::string result(5, '-');

    for (size_t i = 0; i < trial.size(); i++)
    {
        size_t pos = word.find(trial[i]);
        if (pos == i)
        {
            result[i] = trial[i];
            word[pos] = '0';
        }
        else if (pos != std::string::npos)
        {
            result[i] = '*';
            word[pos] = '0';
        }
        else
        {
            result[i] = '-';
        }

    }
    return result;
}