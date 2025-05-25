//
// Created by MINALP1 on 5/26/2025.
//

#include "Reward.h"
#include <iostream>



    Reward::Reward(const std::string &type, int value, int turns)
        : type(type), value(value), turns(turns)
    {
    }

    Reward::Reward(const Reward &r)
        : type(r.type), value(r.value), turns(r.turns)
    {
    }

    Reward &Reward::operator=(const Reward &r)
    {
        if (this != &r)
        {
            type = r.type;
            value = r.value;
            turns = r.turns;
        }
        return *this;
    }




     std::ostream &operator<<(std::ostream &os, const Reward &r)
    {
        os << "Reward(" << r.type << ", Value: " << r.value << ", Turns: " << r.turns << ")" << std::endl;;
        return os;
    }
     bool Reward::isInvincible() const//daca o comentez typeid functioneaaza diferit ptr ca nu mai am polimorfism
    {

        return false;
    }
     bool Reward::DoublePoints() const//daca o comentez typeid functioneaaza diferit ptr ca nu mai am polimorfism
   {
        return false;
   }





    bool Invincible::isInvincible() const
    {
        return true; //daca e invincibil poate sa manance ce peste vrea ptr o tura}
    }





    bool isDoublePoints::DoublePoints() const
    {
        return true; //manaci un peste si primesti scor dublu
    }


