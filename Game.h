//
// Created by MINALP1 on 5/26/2025.
//

#ifndef GAME_H
#define GAME_H
#pragma once
#include "Aquarium.h"

#include "Fish.h"

#include "Objective.h"

#include <mutex>
#include <condition_variable>
#include "ThreatLevel.h"


class Game
{
private:
    std::shared_ptr<Fish> player;
    Aquarium aquarium;
    Objective objective;
    int score;
    ThreatLevel threatLevel;
    bool isInvincible = false;
    bool running = true;
    bool isDoublePoints = false;
    std::mutex rewardMutex;
    std::condition_variable rewardCV;

public:
    Game(std::shared_ptr<Fish> player, const Objective &obj)
        : player(player), objective(obj), score(0), threatLevel(ThreatLevel::Sunrise), isInvincible(false)
    {
    }

    Game(const Game &g)
        : player(g.player), aquarium(g.aquarium), objective(g.objective), score(g.score),
          threatLevel(g.threatLevel), isInvincible(g.isInvincible), isDoublePoints(g.isDoublePoints)
    {
    }

    Game &operator=(const Game &g)
    {
        if (this != &g)
        {
            player = g.player;
            aquarium = g.aquarium;
            objective = g.objective;
            score = g.score;
            threatLevel = g.threatLevel;
            isInvincible = g.isInvincible;
            isDoublePoints = g.isDoublePoints;
        }
        return *this;
    }

    ~Game()
    {
    }

    void setThreatLevel(ThreatLevel level)
    {
        threatLevel = level;
    }


    void spawnFish(int num, std::shared_ptr<Fish> playerFish, const ThreatLevel &Level)
    {
        //pun alt nume la Level si nu pun threatLevel ca sa nu mi mai dea eroare
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(playerFish->getSize() + 1, 6);

        // srand(static_cast<unsigned int>(time(0)));
        int i = 0;
        while (i <= num)
        {
            auto newFish = std::make_shared<NPCFish>("Fish" + std::to_string(i), 0, 0);
            aquarium.addFish(newFish); // ✅

            i++;
        }
        int numfishspawn = 0;
        switch (Level)
        {
            case ThreatLevel::Sunrise:
                numfishspawn = 10;
                break;
            case ThreatLevel::Noon:
                numfishspawn = 20;
                break;
            case ThreatLevel::Midnight:
                numfishspawn = 30;
                break;
            default:
                std::cout << "ThreatLevel is invalid";
        }
        for (i = 0; i < numfishspawn; ++i)
        {
            int randomSize = distrib(gen);
            int randomSpeed = randomSize;

            auto newFish = std::make_shared<NPCFish>("Fish" + std::to_string(i), randomSize, randomSpeed);
            aquarium.addFish(newFish);
        }
    }

    void playTurn(const Fish &targetFish)
    {
        if (activerewards() == false)
        {
            if (player->canEat(targetFish))
            {
                if (targetFish.getSize() < player->getSize())
                {
                    score += 20;
                } else
                {
                    score += 50;
                }
                if (score % 100 == 0)
                    player->grow();

                // player->evolve();

                Logger::logEvent(
                    player->getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(score));
            } else
            {
                Logger::logEvent(player->getName() + " a fost mancat de " + targetFish.getName() + "! GAME OVER!");
                stop(); // o metodă care setează running = false
                return;
            }
        } else
        {
            if (isInvincible)
            {
                score += 50;
                if (score % 100 == 0)
                    player->grow();

                // playerevolve();

                Logger::logEvent(
                    player->getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(score));
            }
            if (isDoublePoints)
            {
                if (player->canEat(targetFish))
                {
                    if (targetFish.getSize() < player->getSize())
                    {
                        score += 40;
                    } else
                    {
                        score += 100;
                    }
                    if (score % 100 == 0)
                        player->grow();

                    // player.evolve();

                    Logger::logEvent("DOUBLEPOINTS! AI PRIMIT DUBLU DE PUNCTE PENTRU ACEST PESTISOR!");
                    Logger::logEvent(
                        player->getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(
                            score));
                } else
                {
                    Logger::logEvent(
                        player->getName() + " a fost mancat de " + targetFish.getName() + "! GAME OVER!");
                    stop(); // o metodă care setează running = false
                    return;
                }
            }
        }
    }

    void continuespawnfish(const ThreatLevel &level, const Fish &playerFish)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, playerFish.getSize() - 1);
        int num = 0;

        switch (level)
        {
            case(ThreatLevel::Sunrise):
                num = 3;
                break;
            case(ThreatLevel::Noon):
                num = 2;
                break;
            case(ThreatLevel::Midnight):
                num = 1;
                break;
            default:
                num = 0;
        }
        for (int i = 0; i < num; ++i)
        {
            int randomsize = distrib(gen);
            auto newFish = std::make_shared<NPCFish>("Fish" + std::to_string(distrib(gen) % 3 + distrib(gen)),
                                                     randomsize, randomsize + 1);
            aquarium.addFish(newFish);
        }
    }

    void chooseFishToAttack()
    {
        const auto &fishies = aquarium.getFishies();
        std::cout << "Vrei sa vezi pestii ramasi in acvariu?(y/n)" << std::endl;
        char answ;
        std::cin >> answ;
        int ok = 1;

        while (ok == 1)
        {
            switch (answ)
            {
                case 'y':
                {
                    displayState();
                    ok = 0;
                    break;
                }
                case 'n':
                {
                    ok = 0;
                    break;
                }
                default:
                {
                    std::cout << "ai introdus o valoare gresita, te rog reincearca:" << std::endl;
                    std::cin >> answ;
                    break;
                }
            }
        }

        std::cout << "Alege indexul unui peste de atacat: " << std::endl;
        int idx;


        while (true)
        {
            std::cin >> idx;
            if (std::cin.fail())
            {
                std::cin.clear(); // sterge starea de eroare
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arunca ce a ramas în buffer
                std::cout << "Input invalid! Te rog introdu un numar intre 0 si " << fishies.size() - 1 << ": " <<
                        std::endl;
                continue;
            }
            if (idx >= 0 && idx < static_cast<int>(fishies.size()))
            {
                break; // index corect, ieșim din while
            } else
            {
                std::cout << "Index invalid! Introdu un numar intre 0 si " << fishies.size() - 1 << ": " <<
                        std::endl;
            }
        }


        if (idx >= 0 && idx < static_cast<int>(fishies.size()))
        {
            if (player->canEat(*fishies[idx]))
            {
                playTurn(*fishies[idx]);
                aquarium.removeFish(idx);
            } else
            {
                playTurn(*fishies[idx]);
                if (isInvincible == true)
                {
                    aquarium.removeFish(idx);
                    isInvincible = false;
                }
            }
        } else
        {
            std::cout << "Index invalid!" << std::endl;
        }
    }

    void displayState() const
    {
        std::cout << "Starea jocului: " << std::endl;
        std::cout << "Jucator: " << *player << " | Scor: " << score << std::endl;
        std::cout << aquarium; //compunere op<<    }
    }

    bool isObjectiveMet() const
    {
        return objective.checkGoalReached(score, *player);
    }


    void RandomReward()
    {
        std::vector<std::shared_ptr<Reward> > rewardz;
        rewardz.push_back(std::make_shared<::Invincible>("Invincible", 2, 1));
        rewardz.push_back(std::make_shared<::isDoublePoints>("isDoublePoints", 2, 1));
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(rewardz.size()) - 1);

        int idx = distrib(gen);
        aquarium.addReward(rewardz[idx]);
    }

    void rewardSpawnerThread()
    {
        int counter = 0;
        while (true)
        {
            std::unique_lock<std::mutex> lock(rewardMutex);

            // Wait for 1 second or until game stops
            if (rewardCV.wait_for(lock, std::chrono::seconds(1), [this] { return !running; }))
            {
                // If we're here because running is false, break the loop
                break;
            }

            // Check running status after wait (in case of spurious wakeup)
            if (!running)
            {
                break;
            }

            counter++;
            if (counter == 10)
            {
                RandomReward(); // spawn reward
                Logger::logEvent(" O recompensa a aparut din neant!");
                counter = 0;
            }
        }
    }

    void chooseReward()
    {
        int cnt = 0;
        std::vector<std::shared_ptr<Reward> > rewards;
        rewards = aquarium.getRewards();
        std::cout << "Alege indexul Recompensei: " << std::endl;
        cnt = 0;
        for (const auto &reward: rewards)
        {
            std::cout << cnt << ". " << *reward << std::endl;
            cnt++;
        }
        int idx;
        while (true)
        {
            std::cin >> idx;
            if (std::cin.fail())
            {
                std::cin.clear(); // sterge starea de eroare
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arunca ce a ramas în buffer
                std::cout << "Input invalid! Te rog introdu un numar intre 0 si " << rewards.size() - 1 << ": " <<
                        std::endl;
                continue;
            }
            if (idx >= 0 && idx < static_cast<int>(rewards.size()))
            {
                break; // index corect, ieșim din while
            } else
            {
                std::cout << "Index invalid! Introdu un numar intre 0 si " << rewards.size() - 1 << ": " <<
                        std::endl;
            }
        }

        if (rewards[idx]->isInvincible())
        {
            isInvincible = true;
            Logger::logEvent("Esti Invincibil, poti sa mananci ce peste vrei tu, fara sa mori pentru o tura!");
            chooseFishToAttack();
            aquarium.removeReward(idx);
        }
        if (rewards[idx]->DoublePoints())
        {
            isDoublePoints = true;
            Logger::logEvent(
                "LA FIECARE PESTE MANCAT, PRIMESTI DOUBLEPOINTS! DUREAZA PUTIN ASA CA MANANCA CAT MAI MULTI!");
            chooseFishToAttack();
            isDoublePoints = false;

            aquarium.removeReward(idx);
        }
    }

    void ChooseAction()
    {
        const auto &rewards = aquarium.getRewards();
        // if (sizeof(rewards) != 0)
        // {
        //     for ( const auto&  reward: rewards)
        //     {
        //         std::cout<< typeid(*reward).name()<< std::endl;
        //     }
        // } sa verific ca mi da bine type
        if (!rewards.empty())
        {
            std::cout << "Alege actiunea pe care vrei sa o faci: " << std::endl;
            std::cout << "1.Ataca un peste" << std::endl;
            std::cout << "2.Revendica o recompensa" << std::endl;
            int idx;
            while (true)
            {
                std::cin >> idx;
                if (std::cin.fail())
                {
                    std::cin.clear(); // sterge starea de eroare
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    // arunca ce a ramas în buffer
                    std::cout << "Input invalid! Te rog alege 1 sau 2" << std::endl;
                    continue;
                }
                if (idx == 1 || idx == 2)
                {
                    break; // index corect, ieșim din while
                } else
                {
                    std::cout << "Valoare invalida! Alege  1 sau 2" << std::endl;
                }
            }
            if (idx == 1)
            {
                chooseFishToAttack();
            } else if (idx == 2)
            {
                chooseReward();
            }
        } else
        {
            chooseFishToAttack();
        }
    }

    void stop()
    { {
            std::lock_guard<std::mutex> lock(rewardMutex);
            running = false;
        }
        rewardCV.notify_all(); // Wake up the waiting thread
    }

    bool isRunning() const { return running; }

    bool activerewards() const
    {
        return isInvincible || isDoublePoints;
    }
};



#include "Aquarium.h"

#include "Fish.h"
#include "Logger.h"
#include "Objective.h"
#include <random>
#include <cstdlib>
#include <mutex>
#include <condition_variable>
#include "ThreatLevel.h"


#endif //GAME_H
