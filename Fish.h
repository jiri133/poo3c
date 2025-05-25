//
// Created by MINALP1 on 5/26/2025.
//

#ifndef FISH_H
#define FISH_H
#include <string>
#include <iostream>
#pragma once



class Fish {

        std::string name;
        int size;
        int speed;
        int growthFactor;

    public:
        // Constructor cu parametri
        Fish(const std::string &name, int size, int speed, int growthFactor = 1);

        // Constructor de copiere
        Fish(const Fish &f);
        // Operator= de copiere
        Fish &operator=(const Fish &other);

        // Destructor
        ~Fish();

        // Metode
        bool canEat(const Fish &other) const;

        void grow();

        void evolve();

        const std::string &getName() const ;

        friend std::ostream &operator<<(std::ostream &os, const Fish &f);

        int getSize() const ;
        // int getSpeed() const { return speed; }


};



#endif //FISH_H
