//
// Created by MINALP1 on 5/26/2025.
//

#include "Objective.h"
#include <iostream>
#include "Fish.h"
#pragma once



    Objective::Objective(int goalScore) : goal(goalScore)
    {
    }

    Objective::Objective(const Objective &o) : goal(o.goal)
    {
    }

    Objective &Objective::operator=(const Objective &o)
    {
        if (this != &o)
        {
            goal = o.goal;
        }
        return *this;
    }

    Objective::~Objective()
    {
    }

    bool Objective::checkGoalReached(const int currentScore, const Fish &playerFish) const
    {
        return currentScore >= goal || playerFish.getSize() >= 12;
    }

    std::ostream &operator<<(std::ostream &os, const Objective &obj)
    {
        os << "Scopul jocului: atinge scorul " << obj.goal;
        return os;
    }
