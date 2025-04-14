#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Logger - fara modificari necesare
class Logger {
public:
    static void logEvent(const std::string& msg) {
        std::cout << "[LOG] " << msg << std::endl;
    }
};

// Clasa Fish
class Fish {
    std::string name;
    int size;
    int speed;
    int growthFactor;

public:
    // Constructor cu parametri
    Fish(const std::string& name, int size, int speed, int growthFactor = 1)
        : name(name), size(size), speed(speed), growthFactor(growthFactor) {}

    // Constructor de copiere
    Fish(const Fish& f)
        : name(f.name), size(f.size), speed(f.speed), growthFactor(f.growthFactor) {}

    // Operator= de copiere
    Fish& operator=(const Fish& other) {
        if (this != &other) {
            name = other.name;
            size = other.size;
            speed = other.speed;
            growthFactor = other.growthFactor;
        }
        return *this;
    }

    // Destructor
    ~Fish() {}

    // Metode
    bool canEat(const Fish& other) const {
        return size > other.size;
    }

    void grow(int sizee, int spped) {
        size += sizee;
        speed += spped;
    }

    // void applyReward(const int bonus) {
    //     size += bonus;
    //     speed += bonus / 2;
    //     Logger::logEvent(name + " a primit un bonus! Dimensiune: " + std::to_string(size));
    // }

    void evolve() {
        if (size > 350) {
            name = "Reptila REMO";
            speed += 20;
            Logger::logEvent("Jucatorul a evoluat in Reptila!");
        }
        if (size > 500)
        {
            name = "Amfibianul.";
            speed += 30;
            Logger::logEvent("Jucatorul a evoluat in Amfibian hihi!");
        }


    }

    const std::string& getName() const { return name; }

    // Operator <<
    friend std::ostream& operator<<(std::ostream& os, const Fish& f) {
        os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
        return os;
    }

     int getSize() const { return size; }
    int getSpeed() const { return size; }
};

// Clasa Rewards
class Rewards {
    std::string type;
    int value;

public:

    explicit Rewards(const std::string& type, int value = 1)
        : type(type), value(value) {}

    // Constructor de copiere
    Rewards(const Rewards& r)
        : type(r.type), value(r.value) {}

    // Operator= de copiere
    Rewards& operator=(const Rewards& r) {
        if (this != &r) {
            type = r.type;
            value = r.value;
        }
        return *this;
    }

    // Destructor
    ~Rewards() {}



    friend std::ostream& operator<<(std::ostream& os, const Rewards& r) {
        os << "Reward(" << r.type << ", Value: " << r.value << ")";
        return os;
    }
};

// Clasa Aquarium
class Aquarium {
    std::vector<Fish> fishies;
    std::vector<Rewards> rewards;

public:
    // Constructor
    Aquarium() = default;

    // Constructor de copiere
    Aquarium(const Aquarium& a)
        : fishies(a.fishies), rewards(a.rewards) {}

    // Operator= de copiere
    Aquarium& operator=(const Aquarium& other) {
        if (this != &other) {
            fishies = other.fishies;
            rewards = other.rewards;
        }
        return *this;
    }

    // Destructor
    ~Aquarium() {}

    // Functii membru
    void addFish(const Fish& fish) { fishies.push_back(fish); }
    // void addReward(const Rewards& reward) { rewards.push_back(reward); }
    const std::vector<Fish>& getFishies() const { return fishies; }

    void removeFish(int index) {
        if (index >= 0 && index < static_cast<int>(fishies.size())) {
            fishies.erase(fishies.begin() + index);
        }
    }

    // Fish getBiggestFish() const {
    //     Fish biggest = fishies.front();
    //     for (const auto& f : fishies)
    //         if (f.getSize() > biggest.getSize())
    //             biggest = f;
    //     return biggest;
    // }nu inca
};

// Clasa Objective
class Objective {
    int goal;

public:
    // explicit pentru constructor cu un singur parametru
    explicit Objective(int goalScore) : goal(goalScore) {}

    // Constructor de copiere
    Objective(const Objective& o) : goal(o.goal) {}

    // Operator= de copiere
    Objective& operator=(const Objective& o) {
        if (this != &o) {
            goal = o.goal;
        }
        return *this;
    }

    // Destructor
    ~Objective() {}

    // Metoda const
    bool checkGoalReached(const int currentScore) const {
        return currentScore >= goal;
    }

    friend std::ostream& operator<<(std::ostream& os, const Objective& obj) {
        os << "Scopul jocului: atinge scorul " << obj.goal;
        return os;
    }
     // int getValue() const { return goal; }
};

// Clasa Game
class Game {
private:
    Fish player;
    Aquarium aquarium;
    Objective objective;
    int score;

public:
    // Constructor cu parametri
    Game(const Fish& player, const Objective& obj)
        : player(player), objective(obj), score(0) {}

    // Constructor de copiere
    Game(const Game& g)
        : player(g.player), aquarium(g.aquarium), objective(g.objective), score(g.score) {}

    // Operator= de copiere
    Game& operator=(const Game& g) {
        if (this != &g) {
            player = g.player;
            aquarium = g.aquarium;
            objective = g.objective;
            score = g.score;
        }
        return *this;
    }

    // Destructor
    ~Game() {}

    // Functii membru
    void spawnFish(const int num, const Fish playerFish) {
        srand(static_cast<unsigned int>(time(0)));
       int  minn=1000;
        for (int i = 0; i < num; ++i) {
            int randomSize = rand() % 100 + 1;
            int randomSpeed = rand() % 50 + 1;
            if (randomSize < minn )
            {
                minn=randomSize;
            }
            Fish newFish("Fish" + std::to_string(i), randomSize, randomSpeed);
            aquarium.addFish(newFish);
        }
        //in caz ca se spawneaza prea mari, sa aiba sanse sa sii castige
        if (minn > playerFish.getSize())
        {
            for (int i = 0; i < num; ++i) {
                int randomSize = rand() % playerFish.getSize() + 1;
                int randomSpeed = rand() % (playerFish.getSize()/2) + 1;

                Fish newFish("Fish" + std::to_string(i), randomSize, randomSpeed);
                aquarium.addFish(newFish);
            }
        }
    }

    void playTurn(const Fish& targetFish) {
        if (player.canEat(targetFish)) {
            player.grow(targetFish.getSize(), targetFish.getSpeed());
            score += 10;

            player.evolve();

            Logger::logEvent(player.getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(score));

        } else {
            Logger::logEvent(player.getName() + " a fost mancat de " + targetFish.getName() + "! GAME OVER!");
            exit(0);
        }
    }

    void chooseFishToAttack() {
        const auto& fishes = aquarium.getFishies();
        for (size_t i = 0; i < fishes.size(); ++i) {
            std::cout << i << ": " << fishes[i] << std::endl;
        }

        std::cout << "Alege indexul unui peste de atacat: ";
        int idx;
        std::cin >> idx;

        if (idx >= 0 && idx < static_cast<int>(fishes.size())) {
            playTurn(fishes[idx]);
            if (player.canEat(fishes[idx])) {

                aquarium.removeFish(idx);
            }
        } else {
            std::cout << "Index invalid!" << std::endl;
        }
    }

    void displayState() const {
        std::cout << "Player: " << player << " | Score: " << score << std::endl;
    }

    bool isObjectiveMet() const {
        return objective.checkGoalReached(score);
    }
    // Aquarium& getAquarium() {
    //     return aquarium;
    // }
};


int main() {
    Fish playerFish("Sharkey", 4, 0, 10);
    Objective goal(50);
    Game game(playerFish, goal);



    game.spawnFish(5, playerFish);
    game.displayState();




    while (!game.isObjectiveMet()) {
        game.chooseFishToAttack();
        game.displayState();
    }

    std::cout << "Felicitari! Ai atins scopul jocului!" << std::endl;
    return 0;

    ///trb sa elimin pestele mancat.
    /////constant trebuie sa am un nr minim de pesti micuti pe care sa-i manance ca sa poata sa manance pesti mai mari
}
