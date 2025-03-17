#include <iostream>
#include <vector>

class Fish
{
    std :: string name;
    int size;
    int speed;
    int growthFactor;

public:
    Fish(const std :: string& name, int size, int speed, int growthFactor = 1)//constrde initializare
    : name(name), size(size), speed(speed), growthFactor(growthFactor){}

    Fish ( const Fish& f )//const de copiere
    :name(f.name),size(f.size),speed(f.size),growthFactor(f.growthFactor){}

    ~Fish() = default;


    //operator=
    Fish& operator=(const Fish& other) {
        if (this != &other) {  // Verificăm auto-atribuierea
            name = other.name;
            size = other.size;
            speed = other.speed;
            growthFactor = other.growthFactor;
        }
        return *this;  // Returnăm obiectul curent
    }
    // verific dacă poate mânca alt pește
    bool canEat(const Fish& other) const {
        return this->size > other.size;
    }
    // Creste pestele dupa ce a mancat
    void grow() {
        size += growthFactor;
    }
    friend std::ostream& operator<<(std::ostream& os, const Fish& f) {
        os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
        return os;
    }
    void applyReward(int bonus) {
        size += bonus;
        speed += bonus / 2;
        std::cout << name << " a primit un bonus! Dimensiune: " << size << ", Viteză: " << speed << std::endl;
    }


    // void display() const
    // {
    //     std :: cout << name << " " << size << " " << speed << " " << growthFactor << std :: endl;
    // }

    int getSize() const { return size; }
    const std::string& getName() const { return name; }
};
class Rewards
{
    std :: string type;
    int value;
public:
    Rewards(const std :: string& type, int value = 1)
        : type(type), value(value){}
    Rewards(const Rewards& r)
        :type(r.type),value(r.value){}
    friend std::ostream& operator<<(std::ostream& os, const Rewards& r) {
        os << "Reward(" << r.type << ", Value: " << r.value << ")";
        return os;
    }




};

class Aquarium
{
    std :: vector <Fish> fishies;
    std :: vector <Rewards> rewards;

public:
    void addFish(const Fish& fish) { fishies.push_back(fish); }
    void addReward(const Rewards& reward) { rewards.push_back(reward); }

    void showFish() const {
        for (const auto& fish : fishies) {
            std::cout << fish << std::endl;
        }

    }
    friend class Game;
};
class Game {
private:
    Fish player;
    Aquarium aquarium;
    int score;

public:
    Game(const Fish& player) : player(player), score(0) {}

    void spawnFish(int num) {
        srand(time(0));
        for (int i = 0; i < num; ++i) {
            int randomSize = rand() % 10 + 1;//de adaugat o formula mai buna la randomizare
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
        } else {
            std::cout << player.getName() << " a fost mancat de " << targetFish.getName() << "! GAME OVER!" << std::endl;
            exit(0);
        }
    }

    void displayState() const {
        std::cout << "Player: " << player << " | Score: " << score << std::endl;
    }
    const auto& getFishies() const { return aquarium.fishies; }//clasa Game e friedn cu clasa aquarium

};

int main()
{
    // Fish nemo("Nemo",20,3,1);
    // nemo.display();

    Fish playerFish("Sharkey", 9, 0, 55);
    Game game(playerFish);

    game.spawnFish(8); // Spawnează 5 pești în acvariu
    game.displayState();


    for (const auto& fish: game.getFishies())
    {
        std :: cout <<"Incerc sa mananc "<< fish << std::endl;///de pus doar numele
        game.playTurn(fish);

    }
    ///DEADAUGATmesaj ca a castigat sau au pierdut!!
    ///
    return 0;
}