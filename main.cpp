#include <iostream>
#include "vector"
#include <random>
#include <map>
using namespace std;
//основной элемент игры контролирует цены и тп
class Bank {
private:
    int price_level;
    int playerId;
    double numberPlayers;
    int current_game_length;

    int MIN_ESM_Price,MIN_EGP_Price;
    int MAX_ESM_Price,MAX_EGP_Price;

    int availableESM,availableEGP;
public:
    Bank(int game_length,double numberOfPlayers){
        this->current_game_length=game_length;
        this->playerId=1;
        this->numberPlayers = numberOfPlayers;
        //default
        this->price_level=3;
    }
    int setNextPlayer(){
        this->playerId=playerId+1;
    }
    void setEGP_ESM(){
        if(price_level==1){
            this->MIN_ESM_Price=800;
            this->MAX_EGP_Price=6500;
            this->availableESM =floor(1.0 * numberPlayers);
            this->availableEGP =floor(3.0*numberPlayers);
        }
        if(price_level==2){
            this->MIN_ESM_Price=650;
            this->MAX_EGP_Price=6000;
            this->availableESM =floor(1.5 * numberPlayers);
            this->availableEGP =floor(2.5 * numberPlayers);
        }
        if(price_level==3){
            this->MIN_ESM_Price=500;
            this->MAX_EGP_Price=5500;
            this->availableESM =floor(2.0 * numberPlayers);
            this->availableEGP =floor(2.0 * numberPlayers);
        }
        if(price_level==4){
            this->MIN_ESM_Price=400;
            this->MAX_EGP_Price=5000;
            this->availableESM =floor(2.5 * numberPlayers);
            this->availableEGP =floor(1.5 * numberPlayers);
        }
        if(price_level==5){
            this->MIN_ESM_Price=300;
            this->MAX_EGP_Price=4500;
            this->availableESM =floor(3.0 * numberPlayers);
            this->availableEGP =floor(1.0 * numberPlayers);
        }
        cout<<"\n"<<"min_ESM"<<MIN_ESM_Price<<" max_egp"<<MAX_EGP_Price<<"\n";
    }
    int setPriceLevel() {
        int oldLevel = price_level;

        //СВЯТОЙ РАНДОМ!!!!!
        random_device rd;
        mt19937 gen(rd());
        std::map<int, int> m;
        int newlevel;
        if (oldLevel==1){
            discrete_distribution<> dist({0, 0.3, 0.3, 0.16,0.08,0.08 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel=p.first;

            for (auto p : m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout<<"past level = "<< price_level <<"newLevel = "<<newlevel;
            this->price_level=newlevel;
        }
        if (oldLevel==2){
            discrete_distribution<> dist({0, 0.25, 0.3, 0.25,0.0833,0.0833 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel=p.first;

            for (auto p : m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout<<"past level = "<< price_level <<"newLevel = "<<newlevel;
            this->price_level=newlevel;
        }
        if (oldLevel==3){
            discrete_distribution<> dist({0, 0.08, 0.25, 0.30,0.25,0.0833 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel=p.first;

            for (auto p : m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout<<"past level = "<< price_level <<"newLevel = "<<newlevel;
            this->price_level=newlevel;
        }
        if (oldLevel==4){
            discrete_distribution<> dist({0, 0.08, 0.08, 0.25,0.30,0.25 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel=p.first;

            for (auto p : m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout<<"past level = "<< price_level <<"newLevel = "<<newlevel;
            this->price_level=newlevel;
        }
        if (oldLevel==5){
            discrete_distribution<> dist({0, 0.08, 0.08, 0.16,0.30,0.30 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel=p.first;

            for (auto p : m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout<<"past level = "<< price_level <<"newLevel = "<<newlevel;
            this->price_level=newlevel;

        }
        setEGP_ESM();


    }

    int getPrice_Level() const{
        return price_level;
    }
    int getPlayerId() const{
        return playerId;
    }
    int getGameLength() const{
        return current_game_length;
    }

    int getAvailableESM() const{
        return availableESM;
    }

};

class Player {
private:
    int id;
    string nickname;
    int money;
    bool isBot;
    int auto_fabric;
    int default_fabric;
    int egp;
    int ecm;


public:
    Player(int id, string nname,bool bot){
        this->default_fabric=2;
        this->auto_fabric=0;
        this->money=10000;
        this->egp = 2;
        this->isBot=bot;
        this->ecm = 4;
        this->nickname = nname;
        this->id = id;
    };  // объявляем конструктор
    int getId() const {
        return id;
    }
    string getNickname() {
        return nickname;
    }
    int getMoney() const {
        return money;
    }
    int getEgp() const {
        return egp;
    }
    int getEcm() const {
        return ecm;
    }
    void printInfo() const{
        cout<<"\nIt`s "<<nickname<<" player #"<<id<<" he has "<< money <<"$"<<" factories auto/default :"<<auto_fabric<<" - "<<default_fabric<<"\n";
    }
};
void setup_Game(){}

int main()
{
    //Русский язык
    system("chcp 65001");

    const int esm_tax = 300;
    const int egp_tax = 500;
    const int defaultFabric_tax = 1000;
    const int autoFabric_tax = 1500;
    // длительность игры
    int GAME_LENGTH;
    // параметры клиентского игрока
    int p_client_id = 0;
    string p_client_nickname;



    vector<Player> players;

    cout<<"----------Менеджер----------"<<endl;

    cout << "Enter desired game length in months (rounds) more or equal than 5: \n";
    cin >> GAME_LENGTH;
    if (GAME_LENGTH<5){
        while (GAME_LENGTH<5){
            cout << "Enter desired game length in months (rounds) more or equal than 5: \n";
            cin >> GAME_LENGTH;
            if (GAME_LENGTH>=5){
                break;
            }
        }
    }

    cout<<"Введите ваш никнейм:\n ";
    cin>>p_client_nickname;

    Player client(p_client_id,p_client_nickname,false);

    players.emplace_back(client);

    for (int i = 1; i <= 3; i++ ) {
        string arr[3] = {"Ivan","Morty","Rick"};
        players.emplace_back(Player(i,arr[i-1], true));
    }
     for (int i = 0; i < 4; i++ ) {
        players[i].printInfo();
    }

    Bank Manager(GAME_LENGTH,4);

    for (int i = 0; i <= GAME_LENGTH; i++) {
        Manager.getPrice_Level();
        Manager.setPriceLevel();
        Manager.getPrice_Level();
    }
}
