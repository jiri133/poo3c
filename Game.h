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
    Fish player;
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
    Game(const Fish &player, const Objective &obj);
    Game(const Game &g);

    Game &operator=(const Game &g);
    ~Game();

    void setThreatLevel(ThreatLevel level);

    void spawnFish(const int num, const Fish &playerFish, const ThreatLevel &Level);

    void playTurn(const Fish &targetFish);

    void continuespawnfish(const ThreatLevel &level, const Fish &playerFish);
    void chooseFishToAttack();

    void displayState() const;

    bool isObjectiveMet() const;


    void RandomReward();

    void rewardSpawnerThread();
    void chooseReward();
    void ChooseAction();

    void stop();
    bool isRunning() const;

    bool activerewards() const;
};


#endif //GAME_H
