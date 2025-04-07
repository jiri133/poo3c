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
        return this->size > other.size;
    }

    void grow() {
        size += growthFactor;
    }

    void applyReward(int bonus) {
        size += bonus;
        speed += bonus / 2;
        Logger::logEvent(name + " a primit un bonus! Dimensiune: " + std::to_string(size));
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

    void showFish() const {
        for (const auto& fish : fishies) {
            std::cout << fish << std::endl; // foloseste operator<< compus
        }
    }

    const std::vector<Fish>& getFishies() const { return fishies; } // getter in loc de friend

    int countBiggerThan(const Fish& f) const { // functie mai complexa
        int count = 0;
        for (const auto& fish : fishies) {
            if (fish.getSize() > f.getSize()) ++count;
        }
        return count;
    }

    friend std::ostream& operator<<(std::ostream& os, const Aquarium& a) {
        os << "Aquarium:\n";
        for (const auto& fish : a.fishies) os << fish << "\n";
        for (const auto& reward : a.rewards) os << reward << "\n";
        return os;
    }
};

class Game {
private:
    Fish player;
    Aquarium aquarium;
    int score;

public:
    explicit Game(const Fish& player) : player(player), score(0) {
        Logger::logEvent("Jocul a fost pornit!");
    }

    void spawnFish(int num) {
        srand((unsigned)time(0));
        for (int i = 0; i < num; ++i) {
            int randomSize = rand() % 10 + 1;
            int randomSpeed = rand() % 5 + 1;
            Fish newFish("Fish" + std::to_string(i), randomSize, randomSpeed);
            aquarium.addFish(newFish);
        }
    }

    void playTurn(const Fish& targetFish) {
        if (player.canEat(targetFish)) {
            player.grow();
            score += 10;
            std::cout << player.getName() << " a mancat " << targetFish.getName() << "! Scor: " << score << std::endl;
            checkWinCondition();
        } else {
            std::cout << player.getName() << " a fost mancat de " << targetFish.getName() << "! GAME OVER!" << std::endl;
            exit(0);
        }
    }

    void displayState() const {
        std::cout << "Player: " << player << " | Score: " << score << std::endl;
    }

    void evaluateRisk() const {
        int threats = aquarium.countBiggerThan(player);
        std::cout << "Numar de pesti mai mari decat jucatorul: " << threats << std::endl;
    }

    void checkWinCondition() const {
        if (score >= 100) {
            std::cout << "Felicitari! Ai castigat jocul!" << std::endl;
            exit(0);
        }
    }

    const std::vector<Fish>& getFishies() const { return aquarium.getFishies(); }
};

int main() {
    Fish playerFish("Sharkey", 9, 2, 3);
    Game game(playerFish);

    game.spawnFish(5);
    game.displayState();
    game.evaluateRisk();

    for (const auto& fish : game.getFishies()) {
        std::cout << "Incerc sa mananc " << fish.getName() << std::endl;
        game.playTurn(fish);
    }

    return 0;
}
