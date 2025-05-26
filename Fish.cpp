
#include "Fish.h"
#include "Logger.h"

    // Fish::Fish(const std::string &name, int size, int speed, int growthFactor )
    //     : name(name), size(size), speed(speed), growthFactor(growthFactor)
    // {
    // }

    // Fish::Fish(const Fish &f)
    //     : name(f.name), size(f.size), speed(f.speed), growthFactor(f.growthFactor)
    // {
    // }

    // Operator= de copiere
    // Fish &Fish::operator=(const Fish &other)
    // {
    //     if (this != &other)
    //     {
    //         name = other.name;
    //         size = other.size;
    //         speed = other.speed;
    //         growthFactor = other.growthFactor;
    //     }
    //     return *this;
    // }

    // // Destructor
    // Fish::~Fish()
    // {
    // }
    //
    // // Metode
    // bool Fish::canEat(const Fish &other) const
    // {
    //     return size > other.size;
    // }
    //
    // void Fish::grow()
    // {
    //     size = size + 1;
    //     speed += 10;
    // }

    // void Fish::evolve()
    // {
    //     if (size > 6)
    //     {
    //         name = "Reptila REMO";
    //         speed += 20;
    //         Logger::logEvent("Jucatorul a evoluat in Reptila!");
    //     }
    //     if (size > 11)
    //     {
    //         name = "Amfibianul.";
    //         speed += 30;
    //         Logger::logEvent("Jucatorul a evoluat in Amfibian hihi!");
    //     }
    // }

    // const std::string &Fish::getName() const { return name; }
    //
    //  std::ostream &operator<<(std::ostream &os, const Fish &f)
    // {
    //     os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
    //     return os;
    // }

    // int Fish::getSize() const { return size; }
    // // int getSpeed() const { return speed; }



//
// Player::Player(): Fish()
//     {
//
//     }
// Player &Player::operator=(const Player &other)
//     {
//         if ( this != &other)
//         {
//             Fish::operator=(other);
//         }
//     }


// bool Player::canEat(const Fish &other) const
// {
//         return size > other.getSize();
//
// }
//
// void Player::grow(){
//         this->Fish::grow();
//     }
//


// const std::string &Player::getName()
// {
//     return name;
// }

Player::~Player(){}

