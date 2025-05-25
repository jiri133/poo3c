//
// Created by MINALP1 on 5/26/2025.
//
#include <iostream>
#include <vector>
#include "Fish.h"
#include "Reward.h"
#include <memory>
#ifndef AQUARIUM_H
#define AQUARIUM_H
#pragma once



class Aquarium
{
    std::vector<Fish> fishies;
    std::vector<std::shared_ptr <Reward>> rewards;
    std::vector<int> size = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

public:
    Aquarium() = default; //ptr ca am alti constr


    explicit Aquarium(const Aquarium &a);

    Aquarium &operator=(const Aquarium &other);


    ~Aquarium();


    void addFish(const Fish &fish) ;
    const std::vector<Fish> &getFishies() const ;

    void removeFish(int index);

    friend std::ostream &operator<<(std::ostream &os, const Aquarium &aquarium);


    void addReward( std::shared_ptr<Reward> &r);

    std::vector<std::shared_ptr<Reward>> &getRewards() ;

    void removeReward(int index);
};



#endif //AQUARIUM_H
