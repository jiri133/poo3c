#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Logger {
public:
    static void logEvent(const std::string& msg) {
        std::cout << "[LOG] " << msg << std::endl;
    }
};

class Fish {
    std::string name;
    int size;
    int speed;
    int growthFactor;

public:
    Fish(const std::string& name, int size, int speed, int growthFactor = 1)
        : name(name), size(size), speed(speed), growthFactor(growthFactor) {}

    Fish(const Fish& f)
        : name(f.name), size(f.size), speed(f.speed), growthFactor(f.growthFactor) {}

    ~Fish() = default;

    Fish& operator=(const Fish& other) {
        if (this != &other) {
            name = other.name;
            size = other.size;
            speed = other.speed;
            growthFactor = other.growthFactor;
        }
        return *this;
    }

    bool canEat(const Fish& other) const {
        return size > other.size;
    }

    void grow() {
        size += growthFactor;
    }

    void applyReward(int bonus) {
        size += bonus;
        speed += bonus / 2;
        Logger::logEvent(name + " a primit un bonus! Dimensiune: " + std::to_string(size));
    }

    void evolve() {
        if (size > 50) {
            name = "Reptile";
            speed += 5;
            Logger::logEvent("Jucatorul a evoluat in Reptila!");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Fish& f) {
        os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
        return os;
    }

    int getSize() const { return size; }
    const std::string& getName() const { return name; }
};

class Rewards {
    std::string type;
    int value;

public:
    explicit Rewards(const std::string& type, int value = 1)
        : type(type), value(value) {}

    Rewards(const Rewards& r)
        : type(r.type), value(r.value) {}

    friend std::ostream& operator<<(std::ostream& os, const Rewards& r) {
        os << "Reward(" << r.type << ", Value: " << r.value << ")";
        return os;
    }
};

class Aquarium {
    std::vector<Fish> fishies;
    std::vector<Rewards> rewards;

public:
    void addFish(const Fish& fish) { fishies.push_back(fish); }
    void addReward(const Rewards& reward) { rewards.push_back(reward); }

    const std::vector<Fish>& getFishies() const { return fishies; }
};

class Objective {
    int goal;
public:
    explicit Objective(int goalScore) : goal(goalScore) {}

    bool checkGoalReached(int currentScore) const {
        return currentScore >= goal;
    }

    friend std::ostream& operator<<(std::ostream& os, const Objective& obj) {
        os << "Scopul jocului: atinge scorul " << obj.goal;
        return os;
    }
};

class Game {
private:
    Fish player;
    Aquarium aquarium;
    Objective objective;
    int score;

public:
    Game(const Fish& player, const Objective& obj)
        : player(player), objective(obj), score(0) {}

    void spawnFish(int num) {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < num; ++i) {
            int randomSize = rand() % 100 + 1;
            int randomSpeed = rand() % 50 + 1;
            Fish newFish("Fish" + std::to_string(i), randomSize, randomSpeed);
            aquarium.addFish(newFish);
        }
    }

    void playTurn(const Fish& targetFish) {
        if (player.canEat(targetFish)) {
            player.grow();
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
};

int main() {
    Fish playerFish("Sharkey", 9, 0, 10);
    Objective goal(50);
    Game game(playerFish, goal);

    game.spawnFish(5);
    game.displayState();

    while (!game.isObjectiveMet()) {
        game.chooseFishToAttack();
        game.displayState();
    }

    std::cout << "Felicitari! Ai atins scopul jocului!" << std::endl;
    return 0;
}
