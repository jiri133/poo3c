#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

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

    void grow() {

        size += 1;
        speed += 1;
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
    int getSpeed() const { return speed; }
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
    std::vector<int> size = {0, 1, 2, 3, 4, 5, 6};

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
    void spawnFish(const int num, const Fish& playerFish) {

        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(playerFish.getSize()+1, 6);

        srand(static_cast<unsigned int>(time(0)));
       int  minn=1000;
        int i=0;
        //20 de pesti micuti
        while (i <=20 )
        {
            Fish newFish("Fish" + std::to_string(i), 0, 0);
            aquarium.addFish(newFish);
            i++;
        }
        for (int i = 0; i < num; ++i) { //in fucntie de threat level
            int randomSize=distrib(gen);
            int randomSpeed=randomSize;
            Fish newFish("Fish" + std::to_string(i), randomSize, randomSpeed);
            aquarium.addFish(newFish);
        }

    }

    void playTurn(const Fish& targetFish) {
        if (player.canEat(targetFish)) {
            if (targetFish.getSize()<player.getSize())
            {
                score += 5;
            }
            else
                score += 10;
            if (score % 200 == 0)//cd mananca deja 20 de pestisori de un tip creste
            player.grow();


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

    //verific daca exista pestisori destui de mici sa fie mancati
};


int main() {
    Fish playerFish("Sharkey", 1, 0, 10);
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
    ////cum sa functioneze-- pe nivele, depinde de ce threat alegi--- threat mic, putin pesti mari-- threat mare-- multi pesti mari- dar in orice caz trb sa exisre
    /////nr minim de pesti mici ca sa poti sa castigi
    ///
    /////la un anumit interval de timp se spawneazaa pestisior mai mici constant
    //////poate mi-ar fi mai usor daca ar exista valori implicite la marimi-adica 6 marimi de pesti
    ///
    ////si pestele incepe constant la o anumita dimensiune
}
