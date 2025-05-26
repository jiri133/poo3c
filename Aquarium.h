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
    std::vector<std::shared_ptr<Fish> > fishies;
    std::vector<std::shared_ptr<Reward> > rewards;
    std::vector<int> size = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

public:
    Aquarium() = default; //ptr ca am alti constr


    explicit Aquarium(const Aquarium &a)
        : fishies(a.fishies), rewards(a.rewards)
    {
    }

    Aquarium &operator=(const Aquarium &other)
    {
        if (this != &other)
        {
            fishies = other.fishies;
            rewards = other.rewards;
        }
        return *this;
    }


    ~Aquarium()
    {
    }


    void addFish(const std::shared_ptr<Fish> &fish)
    {
        fishies.push_back(fish); //  Acum vectorul conține pointeri, deci merge
    }

    const std::vector<std::shared_ptr<Fish> > &getFishies() const
    {
        return fishies;
    }

    void removeFish(int index)
    {
        if (index >= 0 && index < static_cast<int>(fishies.size()))
        {
            fishies.erase(fishies.begin() + index);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Aquarium &aquarium)
    {
        os << "Acvariul contine urmatorii pesti:\n";
        const auto &fishList = aquarium.getFishies(); // Accesam lista de pesti
        if (fishList.empty())
        {
            os << "Nu exista pesti in acvariu.\n";
        } else
        {
            int cnt = 0;
            for (const auto &fish: fishList)
            {
                os << cnt << '.' << *fish << std::endl;
                // Afișăm fiecare pește folosind operatorul << definit pentru Fish
                ++cnt;
            }
        }
        return os;
    }


    void addReward(std::shared_ptr<Reward> &r)
    {
        rewards.push_back(r);
    }

    std::vector<std::shared_ptr<Reward> > &getRewards() { return rewards; }

    void removeReward(int index)
    {
        if (index >= 0 && index < static_cast<int>(rewards.size()))
        {
            rewards.erase(rewards.begin() + index);
        }
    }
};

//
// Created by MINALP1 on 5/26/2025.
//




#endif //AQUARIUM_H
