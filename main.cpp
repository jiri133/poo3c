#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <thread>
#include <chrono>

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
        size =size+ 1;
        speed += 10;
    }

    void evolve() {
        if (size > 6) {
            name = "Reptila REMO";
            speed += 20;
            Logger::logEvent("Jucatorul a evoluat in Reptila!");
        }
        if (size > 11) {
            name = "Amfibianul.";
            speed += 30;
            Logger::logEvent("Jucatorul a evoluat in Amfibian hihi!");
        }
    }

    const std::string& getName() const { return name; }

    friend std::ostream& operator<<(std::ostream& os, const Fish& f) {
        os << "Fish(" << f.name << ", Size: " << f.size << ", Speed: " << f.speed << ")";
        return os;
    }

    int getSize() const { return size; }
    // int getSpeed() const { return speed; }
};

// Clasa Rewards
class Reward {
    std::string type;
    int value;
    int turns;

public:
     explicit Reward(const std::string& type, int value = 1,int turns = 1)
        : type(type), value(value), turns(turns) {}

    explicit Reward(const Reward& r)
        : type(r.type), value(r.value), turns(r.turns) {}

    Reward& operator=(const Reward& r) {
        if (this != &r) {
            type = r.type;
            value = r.value;
            turns = r.turns;
        }
        return *this;
    }

    bool isInvincible()const
    {
        return type == "Invincible";//daca e invincibil poate sa manance ce peste vrea ptr o tura

    }
    bool isDoublePoints()const
     {
         return type == "DoublePoints";//manaci un peste si primesti scor dublu
     }
    ~Reward() {}

    friend std::ostream& operator<<(std::ostream& os, const Reward& r) {
        os << "Reward(" << r.type << ", Value: " << r.value << ", Turns: " << r.turns<< ")"<<std:: endl;;
        return os;
    }
};

// Clasa Aquarium
class Aquarium {
    std::vector<Fish> fishies;
    std::vector<Reward> rewards;
    std::vector<int> size = {0, 1, 2, 3, 4, 5, 6,7,8,9,10,11,12};

public:
    Aquarium() = default;//ptr ca am alti constr


    explicit Aquarium(const Aquarium& a)
        : fishies(a.fishies), rewards(a.rewards) {}

    Aquarium& operator=(const Aquarium& other) {
        if (this != &other) {
            fishies = other.fishies;
            rewards = other.rewards;
        }
        return *this;
    }


    ~Aquarium() {}



    void addFish(const Fish& fish) { fishies.push_back(fish); }
    const std::vector<Fish>& getFishies() const { return fishies; }

    void removeFish(int index) {
        if (index >= 0 && index < static_cast<int>(fishies.size())) {
            fishies.erase(fishies.begin() + index);
        }
    }
   friend std::ostream& operator<<(std::ostream& os, const Aquarium& aquarium) {
        os << "Acvariul contine urmatorii pesti:\n";
        const auto& fishList = aquarium.getFishies();  // Accesam lista de pesti
        if (fishList.empty()) {
            os << "Nu exista pesti in acvariu.\n";
        } else {
            int cnt=0;
            for (const auto& fish : fishList) {
                os << cnt <<'.'<<fish << std::endl;  // Afișăm fiecare pește folosind operatorul << definit pentru Fish
                ++cnt;
            }
        }
        return os;
    }


    void addReward(const Reward& r)
    {
        rewards.push_back(r);
    }

    const std::vector<Reward>& getRewards() const { return rewards; }

    void removeReward(int index)
    {
        if (index >= 0 && index < static_cast<int>(rewards.size()))
        {
            rewards.erase(rewards.begin()+index);
        }
    }
};

// Clasa Objective
class Objective {
    int goal;

public:
    explicit Objective(int goalScore) : goal(goalScore) {}

    Objective(const Objective& o) : goal(o.goal) {}

    Objective& operator=(const Objective& o) {
        if (this != &o) {
            goal = o.goal;
        }
        return *this;
    }

    ~Objective() {}

    bool checkGoalReached(const int currentScore,const Fish& playerFish) const {
        return currentScore >= goal || playerFish.getSize() >= 12 ;
    }

    friend std::ostream& operator<<(std::ostream& os, const Objective& obj) {
        os << "Scopul jocului: atinge scorul " << obj.goal;
        return os;
    }
};

// Clasa Game
enum class ThreatLevel { Sunrise, Noon, Midnight };
class Game {

private:
    Fish player;
    Aquarium aquarium;
    Objective objective;
    int score;
    ThreatLevel threatLevel;
    bool isInvincible=false;
    bool running = true;
    bool isDoublePoints=false;


public:

    Game(const Fish& player, const Objective& obj)
        : player(player), objective(obj), score(0), threatLevel(ThreatLevel::Sunrise),isInvincible(false){}

    Game(const Game& g)
        : player(g.player), aquarium(g.aquarium), objective(g.objective), score(g.score), threatLevel(g.threatLevel),isInvincible(g.isInvincible),isDoublePoints(g.isDoublePoints) {}

    Game& operator=(const Game& g) {
        if (this != &g) {
            player = g.player;
            aquarium = g.aquarium;
            objective = g.objective;
            score = g.score;
            threatLevel = g.threatLevel;
            isInvincible = g.isInvincible;
            isDoublePoints = g.isDoublePoints;
        }
        return *this;
    }

    ~Game() {}

    void setThreatLevel(ThreatLevel level) {
        threatLevel = level;
    }

    void spawnFish(const int num, const Fish& playerFish, const ThreatLevel& Level) {//pun alt nume la Level si nu pun threatLevel ca sa nu mi mai dea eroare
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(playerFish.getSize() + 1, 6);

        // srand(static_cast<unsigned int>(time(0)));
        int i = 0;
        while (i <= num) {
            Fish newFish("Fish" + std::to_string(i), 0, 0);
            aquarium.addFish(newFish);
            i++;
        }
        int numfishspawn = 0;
        switch (Level)
        {
            case ThreatLevel::Sunrise:
               numfishspawn = 10;
                break;
            case ThreatLevel::Noon:
               numfishspawn = 20;
                break;
             case ThreatLevel::Midnight:
                 numfishspawn = 30;
                break;
            default:
                std :: cout<<"ThreatLevel is invalid";

        }
        for ( i = 0; i < numfishspawn; ++i) {
            int randomSize = distrib(gen);
            int randomSpeed = randomSize;
            Fish newFish("Fish" + std::to_string(i), randomSize, randomSpeed);
            aquarium.addFish(newFish);
        }
    }

    void playTurn(const Fish& targetFish)
    {
        if (activerewards()==false) {
            if (player.canEat(targetFish)) {
                if (targetFish.getSize() < player.getSize()) {
                    score += 20;
                } else {
                    score += 50;
                }
                if (score % 100 == 0)
                    player.grow();

                player.evolve();

                Logger::logEvent(player.getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(score));

            } else {
                Logger::logEvent(player.getName() + " a fost mancat de " + targetFish.getName() + "! GAME OVER!");
                stop(); // o metodă care setează running = false
                return;
            }
        }
        else
        {
            if (isInvincible)
            {
                score+=50;
                if (score % 100 == 0)
                    player.grow();

                player.evolve();

                Logger::logEvent(player.getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(score));
            }
            if (isDoublePoints)
            {
                if (player.canEat(targetFish)) {
                    if (targetFish.getSize() < player.getSize()) {
                        score += 40;
                    } else {
                        score += 100;
                    }
                    if (score % 100 == 0)
                        player.grow();

                    player.evolve();

                    Logger::logEvent("DOUBLEPOINTS! AI PRIMIT DUBLU DE PUNCTE PENTRU ACEST PESTISOR!");
                    Logger::logEvent(player.getName() + " a mancat " + targetFish.getName() + "! Scor: " + std::to_string(score));


                }
                else {
                    Logger::logEvent(player.getName() + " a fost mancat de " + targetFish.getName() + "! GAME OVER!");
                    stop(); // o metodă care setează running = false
                    return;

                }
            }
        }
    }
    void continuespawnfish( const ThreatLevel& level, const Fish& playerFish)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0,playerFish.getSize()-1);
        int num=0;

        switch (level)
        {
            case(ThreatLevel::Sunrise):
                num=3;
                break;
            case(ThreatLevel::Noon):
                num=2;
                break;
            case(ThreatLevel::Midnight):
                num=1;
                break;
            default:
                num=0;

        }
        for (int i = 0; i < num; ++i)
        {
            int randomsize=distrib(gen);
            Fish newFish("Fish" + std::to_string(distrib(gen)%3+distrib(gen)),randomsize,randomsize+1);
            aquarium.addFish(newFish);

        }
    }

    void chooseFishToAttack() {
        const auto& fishes = aquarium.getFishies();
        std :: cout << "Vrei sa vezi pestii ramasi in acvariu?(y/n)"<< std::endl;
        char answ;
        std::cin >> answ;
        int ok=1;

        while (ok==1)
        {
            switch (answ)
            {
                case 'y':
                {
                    displayState();
                    ok=0;
                    break;
                }
                case 'n':
                {
                    ok=0;
                    break;
                }
                default:
                {
                    std::cout<<"ai introdus o valoare gresita, te rog reincearca:"<<std:: endl;
                    std::cin >> answ;
                    break;
                }
            }
        }

        std::cout << "Alege indexul unui peste de atacat: "<<std:: endl;
        int idx;


        while (true) {
            std::cin >> idx;
            if (std::cin.fail()) {
                std::cin.clear(); // sterge starea de eroare
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arunca ce a ramas în buffer
                std::cout << "Input invalid! Te rog introdu un numar intre 0 si " << fishes.size()-1 << ": "<<std:: endl;
                continue;
            }
            if (idx >= 0 && idx < static_cast<int>(fishes.size())) {
                break; // index corect, ieșim din while
            }
            else {
                std::cout << "Index invalid! Introdu un numar intre 0 si " << fishes.size()-1 << ": "<<std:: endl;
            }
        }


        if (idx >= 0 && idx < static_cast<int>(fishes.size())) {

            if (player.canEat(fishes[idx])) {
                playTurn(fishes[idx]);
                aquarium.removeFish(idx);
            }
            else
            {
                playTurn(fishes[idx]);
                if (isInvincible==true)
                {
                    aquarium.removeFish(idx);
                    isInvincible=false;

                }
            }
        }
        else {
            std::cout << "Index invalid!" << std::endl;
        }
    }

    void displayState() const
    {
        std::cout << "Starea jocului: " << std::endl;
        std::cout << "Jucator: " << player << " | Scor: " << score << std::endl;
        std::cout << aquarium;//compunere op<<    }
    }

    bool isObjectiveMet() const {
        return objective.checkGoalReached(score,player);
    }


    void RandomReward()
    {
        std::vector<Reward> rewardz;
        rewardz.push_back(Reward("Invincible",2,1));
        rewardz.push_back(Reward("DoublePoints",2,1));
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0,static_cast<int>(rewardz.size())-11);

        int idx=distrib(gen);
        aquarium.addReward(rewardz[idx]);
    }
    void rewardSpawnerThread() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(30)); // asteapta 1 minut
            RandomReward(); // spawnez reward-ul
            Logger :: logEvent( " O recompensa  a aparut din neant!");
        }
    }

    void chooseReward()
    {
        int cnt=0;
        std::vector<Reward> rewards;
        rewards=aquarium.getRewards();
        std::cout<<"Alege indexul Recompensei: "<<std:: endl;
        cnt=0;
        for (const auto& reward : rewards)
        {
            std::cout << cnt <<". " <<reward<<std:: endl;
            cnt++;
        }
        int idx;
        while (true) {
            std::cin >> idx;
            if (std::cin.fail()) {
                std::cin.clear(); // sterge starea de eroare
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arunca ce a ramas în buffer
                std::cout << "Input invalid! Te rog introdu un numar intre 0 si " << rewards.size()-1 << ": "<<std:: endl;
                continue;
            }
            if (idx >= 0 && idx < static_cast<int>(rewards.size())) {
                break; // index corect, ieșim din while
            }
            else {
                std::cout << "Index invalid! Introdu un numar intre 0 si " << rewards.size()-1 << ": "<<std:: endl;
            }
        }

        if (rewards[idx].isInvincible())
        {
            isInvincible=true;
            Logger :: logEvent("Esti Invincibil, poti sa mananci ce peste vrei tu, fara sa mori pentru o tura!");
            chooseFishToAttack();
            aquarium.removeReward(idx);
        }
        if (rewards[idx].isDoublePoints())
        {
            isDoublePoints=true;
            Logger :: logEvent("LA FIECARE PESTE MANCAT, PRIMESTI DOUBLEPOINTS! DUREAZA PUTIN ASA CA MANANCA CAT MAI MULTI!");
            chooseFishToAttack();
            isDoublePoints=false;

            aquarium.removeReward(idx);

        }







    }
    void ChooseAction()
    {
        const auto& rewards = aquarium.getRewards();
        if (!rewards.empty())
        {
            std::cout<<"Alege actiunea pe care vrei sa o faci: "<<std:: endl;
            std::cout<<"1.Ataca un peste"<<std:: endl;
            std::cout<<"2.Revendica o recompensa"<<std:: endl;
            int idx;
            while (true) {
                std::cin >> idx;
                if (std::cin.fail()) {
                    std::cin.clear(); // sterge starea de eroare
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arunca ce a ramas în buffer
                    std::cout << "Input invalid! Te rog alege 1 sau 2"<<std:: endl;
                    continue;
                }
                if (idx==1 || idx==2) {
                    break; // index corect, ieșim din while
                }
                else {
                    std::cout << "Valoare invalida! Alege  1 sau 2"<<std:: endl;
                }
            }
            if (idx==1)
            {
                chooseFishToAttack();
            }
            else if (idx==2)
            {
                chooseReward();
            }
        }
        else
        {
            chooseFishToAttack();
        }
    }
    void stop() {
        running = false;
    }
    bool isRunning() const { return running; }
    bool activerewards() const
    {
        return isInvincible || isDoublePoints;
    }
};

int main() {
    Fish playerFish("Sharkey", 1, 0, 10);
    Objective goal(500);
    Game game(playerFish, goal);



    std::cout << "Alege nivelul de dificultate(Threat Level):\n";
    std::cout << "1. Sunrise (easy)\n";
    std::cout << "2. Noon (medium)\n";
    std::cout << "3. Midnight (hard)\n";
    int levelChoice;
    std::cin >> levelChoice;

    ThreatLevel level;
    switch (levelChoice) {
        case 1: level = ThreatLevel::Sunrise; break;
        case 2: level = ThreatLevel::Noon; break;
        case 3: level = ThreatLevel::Midnight; break;
        default: level = ThreatLevel::Sunrise; break;
    }

    game.setThreatLevel(level);

    std::thread rewardThread(&Game::rewardSpawnerThread, &game);

    game.spawnFish(5, playerFish, level);
    game.displayState();

    while (!game.isObjectiveMet() && game.isRunning()) {


        game.ChooseAction();
        game.continuespawnfish(level, playerFish);//ca sa am constant pestisori mici in acvariu


    }
    game.stop(); // o metodă care setează running = false
    if (rewardThread.joinable()) {
        rewardThread.join();
    }
    if (game.isObjectiveMet()) {
        std::cout << "Felicitari! Ai atins scopul jocului!" << std::endl;
    } else {
        std::cout << "Jocul s-a terminat!" << std::endl;
    }
    return 0;

    ///trb sa elimin pestele mancat --check .
    /////constant trebuie sa am un nr minim de pesti micuti pe care sa-i manance ca sa poata sa manance pesti mai mari
    ////cum sa functioneze-- pe nivele, depinde de ce threat alegi--- threat mic, putin pesti mari-- threat mare-- multi pesti mari- dar in orice caz trb sa exisre--ideea de baza check-poate fii elaborata in sensul ca ar trebui spawnati recurent pesti
    /////nr minim de pesti mici ca sa poti sa castigi
    ///
    /////la un anumit interval de timp se spawneazaa pestisior mai mici constant--check- nu e la un interval de timp, ci dupa fiecare tura in fct de threatlevel
    //////poate mi-ar fi mai usor daca ar exista valori implicite la marimi-adica 6 marimi de pesti
    ///
    ////si pestele incepe constant la o anumita dimensiune
    ///////adaptare pe threat level cati se spawneza
    ///de cizelat faza cu reptilele
    //////in momentul cand ma aproprii  de un peste mare, pestele mare sa incerce sa ma manance
    ///
    /////cd evolueaza sa manance reptile si pesti
    ///
    /////pot sa adaug rewards
    ///
    /////sa pun isDoubllePoints cu timer
}