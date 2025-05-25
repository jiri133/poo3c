//
// Created by MINALP1 on 5/26/2025.
//

#include "Aquarium.h"
#include <iostream>
#include <vector>
#include "Fish.h"
#include "Reward.h"
#include <memory>





     Aquarium::Aquarium(const Aquarium &a)
        : fishies(a.fishies), rewards(a.rewards)
    {
    }

    Aquarium &Aquarium::operator=(const Aquarium &other)
    {
        if (this != &other)
        {
            fishies = other.fishies;
            rewards = other.rewards;
        }
        return *this;
    }





    void Aquarium::addFish(const Fish &fish) { fishies.push_back(fish); }
    const std::vector<Fish> &Aquarium::getFishies() const { return fishies; }

    void Aquarium::removeFish(int index)
    {
        if (index >= 0 && index < static_cast<int>(fishies.size()))
        {
            fishies.erase(fishies.begin() + index);
        }
    }

    std::ostream &operator<<(std::ostream &os, const Aquarium &aquarium)
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
                os << cnt << '.' << fish << std::endl;
                // Afișăm fiecare pește folosind operatorul << definit pentru Fish
                ++cnt;
            }
        }
        return os;
    }


    void Aquarium::addReward( std::shared_ptr<Reward> &r)
    {
        rewards.push_back(r);
    }

    std::vector<std::shared_ptr<Reward>> &Aquarium::getRewards()  { return rewards; }

    void Aquarium::removeReward(int index)
    {
        if (index >= 0 && index < static_cast<int>(rewards.size()))
        {
            rewards.erase(rewards.begin() + index);
        }
    }
    Aquarium::~Aquarium(){}


