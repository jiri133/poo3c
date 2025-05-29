#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <limits>
#include "Fish.h"
#include "Logger.h"
#include "Reward.h"
#include "Aquarium.h"
#include "Objective.h"
#include "Game.h"
#include<stdexcept>


// Clasa Game


int main()
{
    std::shared_ptr<Fish> playerFish = std::make_shared<Player>("Sharkey", 1, 0, 10);
    Objective goal(500);
    Game game(playerFish, goal);
    std::cout<<"vrei sa joci?(da/nu)\n";
    std::string input;
    std::cin>>input;
    if (input == "da")
    {
        std::cout << "Alege nivelul de dificultate(Threat Level):\n";
        std::cout << "1. Sunrise (easy)\n";
        std::cout << "2. Noon (medium)\n";
        std::cout << "3. Midnight (hard)\n";
        int levelChoice;
        std::cin >> levelChoice;

        ThreatLevel level;
        switch (levelChoice)
        {
            case 1: level = ThreatLevel::Sunrise;
            break;
            case 2: level = ThreatLevel::Noon;
            break;
            case 3: level = ThreatLevel::Midnight;
            break;
            default: level = ThreatLevel::Sunrise;
            break;
        }

        game.setThreatLevel(level);

        std::thread rewardThread(&Game::rewardSpawnerThread, &game);

        game.spawnFish(5, playerFish, level);
        game.displayState();

        while (!game.isObjectiveMet() && game.isRunning())
        {
            game.ChooseAction();
            game.continuespawnfish(level, *playerFish); //ca sa am constant pestisori mici in acvariu
        }
        game.stop(); // o metodă care setează running = false
        if (rewardThread.joinable())
        {
            rewardThread.join();
        }
        if (game.isObjectiveMet())
        {
            std::cout << "Felicitari! Ai atins scopul jocului!" << std::endl;
        } else
        {
            std::cout << "Jocul s-a terminat!" << std::endl;
        }
        return 0;
    }
    else
        return 0;

    ///trb sa elimin pestele mancat --check .
    /////constant trebuie sa am un nr minim de pesti micuti pe care sa-i manance ca sa poata sa manance pesti mai mari
    ////cum sa functioneze-- pe nivele, depinde de ce threat alegi--- threat mic, putin pesti mari-- threat mare-- multi pesti mari- dar in orice caz trb sa exisre--ideea de baza check-poate fii elaborata in sensul ca ar trebui spawnati recurent pesti
    /////nr minim de pesti mici ca sa poti sa castigi
    ///
    /////la un anumit interval de timp se spawneazaa pestisior mai mici constant--check- nu e la un interval de timp, ci dupa fiecare tura in fct de threatlevel
    //////poate mi-ar fi mai usor daca ar exista valori implicite la marimi-adica 6 marimi de pesti
    ///
    ////si pestele incepe constant la o anumita dimensiune
    ///////adaptare pe threat level cati se spawneza
    ///de cizelat faza cu reptilele
    //////in momentul cand ma aproprii  de un peste mare, pestele mare sa incerce sa ma manance
    ///
    /////cd evolueaza sa manance reptile si pesti
    ///
    /////pot sa adaug rewards
    ///
    /////sa pun isDoubllePoints cu timer
}
