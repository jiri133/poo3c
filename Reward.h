//
// Created by MINALP1 on 5/26/2025.
//

#ifndef REWARD_H
#define REWARD_H
#include <string>
#pragma once


class Reward
{


protected:
    std::string type;
    int value;
    int turns;

public:
    Reward(){};
    explicit Reward(const std::string &type, int value = 1, int turns = 1);

    explicit Reward(const Reward &r);

    Reward &operator=(const Reward &r);


    virtual ~Reward() =  default;


    friend std::ostream &operator<<(std::ostream &os, const Reward &r);
    virtual bool isInvincible() const;//daca o comentez typeid functioneaaza diferit ptr ca nu mai am polimorfism;
    virtual bool DoublePoints() const;//daca o comentez typeid functioneaaza diferit ptr ca nu mai am polimorfism;

};

class Invincible : public Reward
{
public:
    Invincible(){};
    using Reward::Reward;//inherits the constructors from rewards
    bool isInvincible() const override;


};

class isDoublePoints : public Reward
{
public:
    isDoublePoints(){};
    using Reward::Reward;
    bool DoublePoints() const override;


};



#endif //REWARD_H
