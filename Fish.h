//
// Created by MINALP1 on 5/26/2025.
//

#ifndef FISH_H
#define FISH_H
#include <string>
#include <iostream>
#pragma once


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
    Fish(const std::string &name, int size, int speed, int growthFactor = 1): name(name), size(size), speed(speed),
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
    virtual ~Fish()=default;

    // Metode


    virtual void grow()
    {
        size = size + 1;
        speed += 10;
    }

    // void evolve();
    virtual bool canEat(const Fish &other) const =0;

    virtual const std::string &getName() const =0 ;

    friend std::ostream &operator<<(std::ostream &os, const Fish &f)
    {
        os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
        return os;
    }
    int getSize() const { return size; }
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

    Player(const std::string &name, int size, int speed, int growthFactor = 1): Fish(name, size, speed, growthFactor){}

    ~Player() override;

    bool canEat(const Fish &other) const override
    {
        return size > other.getSize();
    }

    void grow() override
    {
        this->Fish::grow();
    }

    // void evolve();

    const std::string &getName() const override
    {
        return name;
    }
};

class NPCFish : public Fish
{
    using Fish::Fish;
    bool canEat(const Fish &other) const override
    {
        return size > other.getSize();
    }

    void grow()override
    {
        this->Fish::grow();
    }

    // void evolve();

    const std::string &getName() const override
    {
        return name;
    }


};
class NPCPlayer mic : public NPCFish{
using NPCFish::NPCFish;


public:
};

class NPCNPCFish mare : public NPCFish{
using NPCFish::NPCFish;};


#endif //FISH_H
