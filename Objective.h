//
// Created by MINALP1 on 5/26/2025.
//

#ifndef OBJECTIVE_H
#define OBJECTIVE_H
#include <iostream>
#include "Fish.h"
#pragma once


class Objective
{
    int goal;

public:
    explicit Objective(int goalScore) ;

    Objective(const Objective &o) ;

    Objective &operator=(const Objective &o);

    ~Objective();

    bool checkGoalReached(const int currentScore, const Fish &playerFish) const;

    friend std::ostream &operator<<(std::ostream &os, const Objective &obj);
};



#endif //OBJECTIVE_H
