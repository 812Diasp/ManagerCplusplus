#include <iostream>
#include "vector"
#include <random>
#include <map>

using namespace std;

// запрос на есм от игроков
class Request {
private:
    int playerId;
    int ESMcount;
    int requestPrice;

public:
    Request(int playerId, int ESMcount, int requestPrice) {
        //this->ESM_or_EGP=ESM_or_EGP;

        this->playerId = playerId;
        this->ESMcount = ESMcount;
        this->requestPrice = requestPrice;
    }
    int getRequestPlayerId() const {
        return this->playerId;
    };
    void printRequest() {
        cout << "\nигрок: " << playerId << "\t количество " << ESMcount << "\t цена " << requestPrice;
    }




    int getEsm() const {
        return this->ESMcount;
    }

    int getReqPrice() const {
        return this->requestPrice;
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

    vector<Request> requestsESM;

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
        if (playerId + 1 > numberPlayers) {
            playerId = 1;
        } else {
            playerId += 1;
        }
    }
    int getNextPlayer() {
        return this->playerId;
    }


    void setNewRequest(int player_id, int count, int requestPrice) {
        cout << "\nRequest Принят\n";
        Request newReq(player_id, count, requestPrice);
        this->requestsESM.push_back(newReq);
        cout << "-----------\nin Bank successfuly request pushed-----------\n" << this->requestsESM.size();
        for (Request req: this->requestsESM) {
            req.printRequest();
        }
        // requestsESM[0].printRequest();
    }
    vector<Request> getRequestList() {
        return this->requestsESM;
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
// просто выводим что сгенериловалось ДЛЯ ДЕБАГА
//            for (auto p: m)
//                std::cout << p.first << " generated " << p.second << " times\n";
//            cout << " past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;
        }
        if (oldLevel == 2) {
            discrete_distribution<> dist({0, 0.25, 0.3, 0.25, 0.0833, 0.0833});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            this->price_level = newlevel;
        }
        if (oldLevel == 3) {
            discrete_distribution<> dist({0, 0.08, 0.25, 0.30, 0.25, 0.0833});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;


            this->price_level = newlevel;
        }
        if (oldLevel == 4) {
            discrete_distribution<> dist({0, 0.08, 0.08, 0.25, 0.30, 0.25});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;

            this->price_level = newlevel;
        }
        if (oldLevel == 5) {
            discrete_distribution<> dist({0, 0.08, 0.08, 0.16, 0.30, 0.30});
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p: m)
                newlevel = p.first;


            this->price_level = newlevel;

        }
        setEGP_ESM();
    }

    void sellESM(int tooSellESM){
        if (this->availableESM-tooSellESM>=0){
            this->availableESM-=tooSellESM;
        }
    }
    void sellEGP(int toSellEGP){
        if (this->availableESM-toSellEGP>=0){
            this->availableESM-=toSellEGP;
        }
    };

    int getPrice_EGP() {
        return MAX_EGP_Price;
    }
    int getPrice_ESM() {
        return MIN_ESM_Price;
    }
    int getAvailableESM() {
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
    void printPrimePlayer() {
        cout << "\n Player #" << playerId << " is prime, he has executive right to buy esm firstly\n";
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
    int esm;
public:
    Player(int id, string nname) {
        this->default_fabric = 2;
        this->auto_fabric = 0;
        this->money = 10000;
        this->egp = 2;

        this->esm = 4;
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

    int getEsm() const {
        return esm;
    }

    void setEsm(int esmCount, int esmPrice) {
        this->esm += esmCount;
        this->money -= esmPrice * esmCount;
    }
    void setEGP(int egpCount, int egpPrice) {
        this->egp += egpCount;
        this->money += egpCount * egpPrice;
    }

    void printInfo() const {
        cout << "\n---------\n" << nickname << " номер-" << id << "\nденег: " << money << "$" << "\nфабрики автоматизированные:"
             << auto_fabric << "\nфабрики обычные: " << default_fabric << "\n---------\n";
    }

//    void makeRequest(Bank manager,string ESMorEGP) {
//        cout << "\n" << "Введите вашу цену покупки ЕСМ для производсва ЕГП" << endl;
//        cout << "\nЕСМ \t ЕГП\n";
//        cout << manager.getPrice_ESM() << "\t" << manager.getPrice_EGP() << endl;
//        cout << "\n доступные для продажи Еденицы Сырья и Материалов: " << manager.getAvailableESM();
//        cout << "\n доступные для продажи Еденицы Готовых Продуктов: " << manager.getAvailableEGP();
//        cout << "\n Введите цену(больше цены ЕСМ):\n";
//        int player_price;
//        cin >> player_price;
//        cout << "\n Введите количество ЕСМ:\n";
//        int esm_count;
//        cin >> esm_count;
//        manager.setNewRequest(this->id, esm_count, player_price,ESMorEGP);
//
//    }
};


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
    int p_client_id = 1;
    string p_client_nickname;

    vector<Player> players;

    cout << "----------Менеджер----------" << endl;

    //Проверка числа раундов
//    cout << "Введите желаемое число раундов >= 24: \n";
//    cin >> GAME_LENGTH;
//    if (GAME_LENGTH < 24 || GAME_LENGTH > 100) {
//        while (GAME_LENGTH < 24) {
//            cout << "Введите желаемое число раундов >= 24: \n";
//            cin >> GAME_LENGTH;
//            if (GAME_LENGTH >= 24) {
//                break;
//            }
//        }
//    }
    //Никнейм
    cout << "\nВведите ваш никнейм:\n ";
    cin >> p_client_nickname;
    // создаем первого игрока(предполагается что клиент будет играть за него
    Player client(p_client_id, p_client_nickname);

    players.emplace_back(client);
    //СОздание других
    const int BOT_COUNT = 2;
    for (int i = 0; i < BOT_COUNT; i++) {
        string arr[BOT_COUNT] = {"Морти", "Рик"};
        players.emplace_back(Player(i + 2, arr[i]));
    }
//    for (int i = 0; i < players.size(); i++) {
//        players[i].printInfo();
//    }
    //cout<<"\n\n players.size() ="<<players.size()<<"\n\n";


    //НАШ ВЛАДЫКА
    Bank Manager(GAME_LENGTH, players.size());


    for (int i = 0; i < 4; i++) {
        cout << "\n\n\n\n\n";

        Manager.setPriceLevel();

        int MAX_egpPrice = Manager.getPrice_EGP();
        int MIN_esmPrice = Manager.getPrice_ESM();


        int primePlayer = Manager.getPlayerId();
        Manager.getPrice_Level();
        cout << "\n Старший игрок: " << primePlayer << "\n\n";
        Manager.printPrimePlayer();
        vector<Request> esmRequestList;
        vector<Request> egpRequestList;
        for (int j = 0; j < players.size(); j++) {

            Player p = players[j];
            cout << "\n\n\n\n\n";
            Manager.printPrimePlayer();
            cout << "Сейчас ход игрока №" << p.getId() << " " << p.getNickname();
            p.printInfo();
            // p.makeRequest(Manager);
            //Создаем новый запрос и помещаем его в список запросов
            cout << "\n" << "Введите вашу цену покупки ЕСМ для производсва ЕГП" << endl;
            cout << "\nЕСМ \t ЕГП\n";
            cout << Manager.getPrice_ESM() << "\t" << Manager.getPrice_EGP() << endl;
            cout << "\n доступные для продажи Еденицы Сырья и Материалов: " << Manager.getAvailableESM();
            cout << "\n доступные для продажи Еденицы Готовых Продуктов: " << Manager.getAvailableEGP();
            cout << "\n Введите цену(больше цены ЕСМ):\n";
            int player_price;
            // цена есм
            cin >> player_price;
            if (player_price < Manager.getPrice_ESM()) {
                while (player_price < Manager.getPrice_ESM()) {
                    cout << "\nЕще раз Введите количество ЕСМ:\n";
                    cin >> player_price;
                    if (player_price >= Manager.getPrice_ESM()) {
                        break;
                    }
                }
            }
            // количество есм
            cout << "\n Введите количество ЕСМ:\n";
            int esm_count;
            cin >> esm_count;
            if (esm_count > Manager.getAvailableESM()) {
                while (esm_count > Manager.getAvailableESM()) {
                    cout << "\n Введите количество ЕСМ:\n";
                    cin >> esm_count;
                    if (esm_count <= Manager.getAvailableESM()) {
                        break;
                    }
                }
            }

            Request ESMnewRequest = Request(p.getId(), esm_count, player_price);


            // добавляем запрос в список
            esmRequestList.push_back(ESMnewRequest);

            // печатаем
//            for (ESM_Request req:requestList) {
//                req.printRequest();
//            }

        }


        // Обрабатываем запросы на есм и егп
        for (Request request: esmRequestList) {
            // платим старшему игроку
            for (Request rESM: esmRequestList) {
                if (Manager.getPlayerId() == rESM.getRequestPlayerId()) {
                    // cout<< "\nprime до:";
                    players[Manager.getPlayerId() - 1].printInfo();
                    players[Manager.getPlayerId() - 1].setEsm(rESM.getEsm(), rESM.getReqPrice());
                    // cout<< "\nprime после:";
                    players[Manager.getPlayerId() - 1].printInfo();
                    // cout<<"\nprime игрок получил свои есм\n";
                    auto iter = esmRequestList.cbegin(); // указатель на первый элемент
                    if (Manager.getPlayerId() == 1) {
                        esmRequestList.erase(iter);
                    } else {
                        esmRequestList.erase(iter + Manager.getPlayerId() - 1);
                    }
                }
                break;
            }


            cout << "\nПосле prime\n";
            //сортируем заявки ЕСМ по цене
            for (int f = 0; f < esmRequestList.size(); f++) {
                if (esmRequestList[f].getReqPrice() < esmRequestList[f + 1].getReqPrice()) {
                    swap(esmRequestList[f], esmRequestList[f + 1]);
                    f++;
                }
            }
            cout<<"\nsorted\n";
            for (Request rsf: esmRequestList) {
                rsf.printRequest();
            }

            for (Request r: esmRequestList) {


                int idPlayerReq = r.getRequestPlayerId() - 1;
                // cout<<"\nДО";
                // players[idPlayerReq].printInfo();
                players[idPlayerReq].setEsm(r.getEsm(), r.getReqPrice());

                Manager.sellESM(r.getEsm());
               // Manager.sellEGP(r.getEGP());
                // cout<<"\nПосле";
                // players[idPlayerReq].printInfo();
                // cout<<"\nВсе реквесты\n";
            }
            break;
        }
        //Конец месяца
        cout << "\nКонец месяца\n";
        Manager.setNextPlayer();


    }
}
