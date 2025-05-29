//
// Created by MINALP1 on 5/26/2025.
//

#ifndef FISH_H
#define FISH_H
#pragma once
#include <string>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include<stdexcept>


#include "Logger.h"
class exceptie: public std::runtime_error
{
    public:
    using std::runtime_error::runtime_error;
    explicit exceptie(const std::string msg): std::runtime_error(msg)
    {

    }

};
class exceptie_mortala: public exceptie
{
    public:
    using exceptie::exceptie;

};

class Fish
{
protected:
    std::string name;
    int size;
    int speed;
    int growthFactor;

public:
    Fish()
    {
    };
    // Constructor cu parametri
    Fish(const std::string &name, int size, int speed=0, int growthFactor = 1): name(name), size(size), speed(speed),
                                                                              growthFactor(growthFactor)
    {
    }

    // Constructor de copiere
    Fish(const Fish &f): name(f.name), size(f.size), speed(f.speed), growthFactor(f.growthFactor)
    {
    }

    // Operator= de copiere
    Fish &operator=(const Fish &other)
    {
        if (this != &other)
        {
            name = other.name;
            size = other.size;
            speed = other.speed;
            growthFactor = other.growthFactor;
        }
        return *this;
    }

    // Destructor
    virtual ~Fish() = default;

    // Metode


    virtual void grow()
    {
        size = size + 1;
        speed += 10;
    }

    // void evolve();
    // virtual bool canEat(const Fish &other) const =0;

    virtual const std::string &getName() const =0;

    friend std::ostream &operator<<(std::ostream &os, const Fish &f)
    {
        os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
        return os;
    }

    virtual int getSize() const { return size; }
    virtual int getSpeed() const { return speed; }

};

class Player : public Fish
{
public:
    Player();

    Player &operator=(const Player &other)
    {
        if (this != &other)
        {
            Fish::operator=(other);
        }
        return *this;
    }

    Player(const std::string &name, int size, int speed, int growthFactor = 1): Fish(name, size, speed, growthFactor)
    {
    }

    ~Player() override = default;

    // bool canEat(const Fish &other) const override
    // {
    //
    // }

    void grow() override
    {
        this->Fish::grow();
    }

    // void evolve();

    const std::string &getName() const override
    {
        return name;
    }

    void takeDamage (int d,int s)
    {
        this->size-=d;
        this->speed-=s;
    }
};

class NPCFish : public Fish
{
protected:
    int escapeChance = 50;
    int ActualChance = 0;

public:
    using Fish::Fish;

    // bool canEat(const Fish &other) const override
    // {
    //     return size > other.getSize();
    // }

    void grow() override
    {
        this->Fish::grow();
    }

    virtual bool attemptEscape(const Player &player)
    {
        ActualChance = escapeChance - (player.getSize() - this->getSize()) * 10;
        return ActualChance > rand() % 100;
    }

    // void evolve();

    const std::string &getName() const override
    {
        return name;
    }
};

class NPCPlayer_mic : public NPCFish
{
private:
    int actualChance = 0;
    int EscapeChance = 60;
    bool isScared = false;

public:
    using NPCFish::NPCFish;

    bool attemptEscape(const Player &player) override
    {
        actualChance = EscapeChance - (player.getSize() - this->getSize()) * 10;
        return actualChance > rand() % 100;
    }

//trb sa se schimne si isScared
    int getBonusPoints() const  {
        return size * 10 + (isScared ? 5 : 0);
    }
    bool isscared() const { return isScared; }
};

class NPCPlayer_mare : public NPCFish
{
    public:
    using NPCFish::NPCFish;
    bool attemptEscape(const Player &player) override
    {
        return player.getSize() > this->size + 3 && (rand() % 100) < 20;
    }


  int  triggerChallange(Player &player, int &score)
    {
        Logger::logEvent("Se pare ca esti curajos! Haide sa vedem daca esti si norocos!");
        std::cout << "Alege strategia:\n";
        std::cout << "1. Ataca frontal (risc mare, reward mare)\n";
        std::cout << "2. Ataca lateral (risc mediu, reward mediu)\n";
        std::cout << "3. Incearca sa fugi (risc mic, fara reward)\n";
        int idx;
        while (true)
        {
            std::cin >> idx;
            if (std::cin.fail())
            {
                std::cin.clear(); // sterge starea de eroare
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arunca ce a ramas în buffer
                std::cout << "Input invalid! Te rog introdu un numar intre 1 si 3 "  << ": " <<
                        std::endl;
                continue;
            }
            if (idx >= 0 && idx <=3)
            {
                break; // index corect, ieșim din while
            } else
            {
                std::cout << "Index invalid! Introdu un numar intre 1 si 3 " <<
                        std::endl;
            }
        }
        switch (idx)
        {
            case 1: return handleFrontalAttack(player, score);

            case 2:return handleLateralAttack(player, score); ;
            case 3: return handleRetreat();

            default: return handleRetreat();
        }

    }

    int  handleFrontalAttack(  Player &player, int &score)
    {
     int succes = 30+(player.getSpeed() + 10);
        if (rand() % 100 < succes%100)
        {
            std::cout<<"BRAVO AI REUSIT!!! ESTI SI NOROCOS, NU DOAR CURAJOS. PENTRU ASTA PRIMESI SCOR MARE!";
            score+=300;
            return 1;
        }
        else
        {
            std::cout<<"Maiculita, ce ghinionist esti! Iti pierzi din tine!";
            player.takeDamage(3,30);
             throw exceptie_mortala("");
        }
    }
    int handleLateralAttack(  Player &player, int &score)
    {
        int succes = 60;
        if (rand() % 100 < succes%100)
        {
            std::cout<<"BRAVO!! ESTI SI NOROCOS, NU DOAR CURAJOS. PENTRU ASTA PRIMESI SCOR mai MARE!";
            score+=150;
            return 1;

        }
        else
        {
            std::cout<<"Maiculita, ce ghinionist esti! Iti pierzi din tine!";
            player.takeDamage(2,20);
            throw exceptie_mortala("ITI SCADE DIN SIZE SI SPEED");
        }
    }

    int handleRetreat()
    {
        throw exceptie("Fugi in siguranta, dar pierzi tura.");
    }
};


#endif //FISH_H
