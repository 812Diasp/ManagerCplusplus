#include <iostream>
#include "vector"
#include <random>
#include <map>

using namespace std;

class ESM_Request {
private:
    int playerId;
    int ESMcount;
    int requestPrice;
public:
    ESM_Request(int playerId, int ESMcount, int requestPrice) {
        this->playerId = playerId;
        this->ESMcount = ESMcount;
        this->requestPrice = requestPrice;
    }
    int getRequestPlayerId() {
        return this->playerId;
    };
    void printRequest(){
        cout<<"\n игрок:"<<playerId<<"\t количество"<<ESMcount<<"\t цена"<<requestPrice;
    }
};
//основной элемент игры контролирует цены и тп
class Bank {
private:
    int price_level;
    int playerId;
    int numberPlayers;
    int current_game_length;

    int MIN_ESM_Price;
    int MAX_EGP_Price;

    vector<ESM_Request> requestsESM;

    int availableESM, availableEGP;
public:
    Bank(int game_length, int numberOfPlayers) {
        this->current_game_length = game_length;
        this->playerId = 1;
        this->numberPlayers = numberOfPlayers;
        //default
        this->price_level = 3;
    }

     void setNextPlayer() {
        if (this->playerId <= this->numberPlayers) {
            this->playerId = playerId + 1;
        } else {
            this->playerId = 0;
        }

    }
    int getNextPlayer(){
        return this->playerId;
    }
    void setNewRequest(int player_id, int ESMcount, int requestPrice ){
        cout<<"\nRequest Принят\n";
        requestsESM.push_back(ESM_Request(player_id,ESMcount,requestPrice ));
        requestsESM[0].printRequest();

    }
    void sellESM(){
        for(int i=0;i<requestsESM.size();i++){
            ESM_Request req = requestsESM[i];
            if(req.getRequestPlayerId() == this->playerId){

            }else{

            }
        }

    }


    void setEGP_ESM() {
        if (price_level == 1) {
            this->MIN_ESM_Price = 800;
            this->MAX_EGP_Price = 6500;
            this->availableESM = floor(1.0 * numberPlayers);
            this->availableEGP = floor(3.0 * numberPlayers);
        }
        if (price_level == 2) {
            this->MIN_ESM_Price = 650;
            this->MAX_EGP_Price = 6000;
            this->availableESM = floor(1.5 * numberPlayers);
            this->availableEGP = floor(2.5 * numberPlayers);
        }
        if (price_level == 3) {
            this->MIN_ESM_Price = 500;
            this->MAX_EGP_Price = 5500;
            this->availableESM = floor(2.0 * numberPlayers);
            this->availableEGP = floor(2.0 * numberPlayers);
        }
        if (price_level == 4) {
            this->MIN_ESM_Price = 400;
            this->MAX_EGP_Price = 5000;
            this->availableESM = floor(2.5 * numberPlayers);
            this->availableEGP = floor(1.5 * numberPlayers);
        }
        if (price_level == 5) {
            this->MIN_ESM_Price = 300;
            this->MAX_EGP_Price = 4500;
            this->availableESM = floor(3.0 * numberPlayers);
            this->availableEGP = floor(1.0 * numberPlayers);
        }
        cout << "\n" << " min_ESM " << MIN_ESM_Price << " max_egp  " << MAX_EGP_Price << "\n";
    }

    int setPriceLevel() {
        //очищаем предыдыщие заявки
        requestsESM.clear();
        int oldLevel = price_level;

        //СВЯТОЙ РАНДОМ!!!!!
        random_device rd;
        mt19937 gen(rd());
        std::map<int, int> m;
        int newlevel;
        if (oldLevel == 1) {
            discrete_distribution<> dist({0, 0.3, 0.3, 0.16, 0.08, 0.08});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            for (auto p: m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout << " past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;
        }
        if (oldLevel == 2) {
            discrete_distribution<> dist({0, 0.25, 0.3, 0.25, 0.0833, 0.0833});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            for (auto p: m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout << " past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;
        }
        if (oldLevel == 3) {
            discrete_distribution<> dist({0, 0.08, 0.25, 0.30, 0.25, 0.0833});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            for (auto p: m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout << " past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;
        }
        if (oldLevel == 4) {
            discrete_distribution<> dist({0, 0.08, 0.08, 0.25, 0.30, 0.25});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            for (auto p: m)
                std::cout << p.first << " generated " << p.second << " times\n";
            cout << "past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;
        }
        if (oldLevel == 5) {
            discrete_distribution<> dist({0, 0.08, 0.08, 0.16, 0.30, 0.30});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            for (auto p: m)
                std::cout << p.first << " generated " << p.second << " times \n";
            cout << "past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;

        }
        setEGP_ESM();
    }
    int getPrice_EGP(){
        return MAX_EGP_Price;
    }
    int getPrice_ESM(){
        return MIN_ESM_Price;
    }
    int getAvailableESM(){
        return this->availableESM;
    }
    int getPrice_Level() const {
        return price_level;
    }
    int getPlayerId() const {
        return playerId;
    }

    int getGameLength() const {
        return current_game_length;
    }

    int getAvailableEGP() const {
        return availableEGP;
    }

};

class Fabric {
private:
    int playerId;
    string FabricType;
    int fabricId;
    int costOfRecycleESM;
public:
    Fabric(int playerId, string FabricType) {

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
    Player(int id, string nname) {
        this->default_fabric = 2;
        this->auto_fabric = 0;
        this->money = 10000;
        this->egp = 2;

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

    void printInfo() const {
        cout << "\n" << nickname << " ID-" << id << "\nденег: " << money << "$" << "\nфабрики автоматизированные:"
             << auto_fabric << "\nфабрики обычные: " << default_fabric << "\n";
    }
    void makeRequest(Bank manager){
        cout<< "\n"<<"Введите вашу цену покупки ЕСМ для производсва ЕГП"<<endl;
        cout<< "\nЕСМ \t ЕГП\n";
        cout<< manager.getPrice_ESM()<<"\t"<<manager.getPrice_EGP()<<endl;
        cout<<"\n доступные для продажи Еденицы Сырья и Материалов: "<< manager.getAvailableESM();
        cout<<"\n доступные для продажи Еденицы Готовых Продуктов: "<<manager.getAvailableEGP();
        cout<< "\n Введите цену(больше цены ЕСМ):\n";
        int player_price;
        cin >> player_price;
        cout<< "\n Введите количество ЕСМ:\n";
        int esm_count;
        cin >> esm_count;
        manager.setNewRequest(this->id,player_price,esm_count);

    }
};

void setup_Game() {}

int main() {
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

    cout << "----------Менеджер----------" << endl;

    cout << "Введите желаемое число раундов >= 24: \n";
    cin >> GAME_LENGTH;
    if (GAME_LENGTH < 24 || GAME_LENGTH > 100) {
        while (GAME_LENGTH < 24) {
            cout << "Введите желаемое число раундов >= 24: \n";
            cin >> GAME_LENGTH;
            if (GAME_LENGTH >= 24) {
                break;
            }
        }
    }
    cout << "\nВведите ваш никнейм:\n ";
    cin >> p_client_nickname;
    Player client(p_client_id, p_client_nickname);
    //СОздание ботов
    players.emplace_back(client);
    const int BOT_COUNT = 2;
    for (int i = 0; i < BOT_COUNT; i++) {
        string arr[BOT_COUNT] = {"Морти", "Рик"};
        players.emplace_back(Player(i + 1, arr[i]));
    }
    for (int i = 0; i < players.size(); i++) {
        players[i].printInfo();
    }
    //cout<<"\n\n players.size() ="<<players.size()<<"\n\n";


    //НАШ ВЛАДЫКА
    Bank Manager(GAME_LENGTH, players.size() - 1);

    for (int i = 0; i <= 2; i++) {
        cout<<"\n\n\n\n\n";

        Manager.setPriceLevel();

        int MAX_egpPrice = Manager.getPrice_EGP();
        int MIN_esmPrice = Manager.getPrice_ESM();


        int primePlayer = Manager.getNextPlayer();
        Manager.getPrice_Level();
        for (int j = 0; j < players.size(); j++) {
            Player p = players[j];
            cout<<"\n\n\n\n\n";
            cout << "Сейчас ход игрока №" << p.getId() << " " << p.getNickname();
            p.printInfo();
            p.makeRequest(Manager);
            // продаем ESM
            //Manager.sellESM();
        }


    }
}
