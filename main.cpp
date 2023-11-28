#include <iostream>
#include <utility>
#include "vector"
using namespace std;
//основной элемент игры контролирует цены и тп
class Bank {
private:
    int price_level;
    int playerId;
    int current_game_length;
    int ESM_Price,EGP_Price;
    int availableESM;
public:
    int getPrice_Level() const{
        return price_level;
    }
    int getPlayerId() const{
        return playerId;
    }
    int getGameLength() const{
        return current_game_length;
    }
    int getESM_Price() const{
        return ESM_Price;
    }
    int getEGP_Price() const{
        return EGP_Price;
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

    int auto_fabric;
    int default_fabric;
    int egp;
    int ecm;


public:
    Player(int id, string nickname){
        this->default_fabric=2;
        this->auto_fabric=0;
        this->money=10000;
        this->egp = 2;
        this->ecm = 4;
        this->nickname = nickname;
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

    cout << "Enter desired game length in months (rounds) more or equal than 25: \n";
    cin >> GAME_LENGTH;
    if (GAME_LENGTH<25){
        while (GAME_LENGTH<25){
            cout << "Enter desired game length in months (rounds) more or equal than 25: \n";
            cin >> GAME_LENGTH;
            if (GAME_LENGTH>=25){
                break;
            }
        }
    }

    cout<<"Введите ваш никнейм:\n ";
    cin>>p_client_nickname;

    Player client(p_client_id,p_client_nickname);

    players.emplace_back(client);

    for (int i = 1; i <= 3; i++ ) {
        string arr[3] = {"Ivan","Morty","Rick"};
        players.emplace_back(Player(i,arr[i-1]));
    }
     for (int i = 0; i < 4; i++ ) {
        players[i].printInfo();
    }



    for (int i = 0; i <= GAME_LENGTH; i++) {

    }
}
