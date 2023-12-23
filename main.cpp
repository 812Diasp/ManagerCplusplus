#include <iostream>
#include "vector"
#include <random>
#include <map>
#include <windows.h>
using namespace std;

// запрос на есм от игроков
class Request {
private:
    int playerId;
    int count;
    int requestPrice;

public:
    Request(int playerId, int ESMcount, int requestPrice) {
        //this->ESM_or_EGP=ESM_or_EGP;

        this->playerId = playerId;
        this->count = ESMcount;
        this->requestPrice = requestPrice;
    }

    int getRequestPlayerId() const {
        return this->playerId;
    };

    void printRequest() {
        cout << "\nигрок: " << playerId << "\t количество " << count << "\t цена " << requestPrice;
    }

    int getCount() const {
        return this->count;
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
        this->playerId = 0;
        this->numberPlayers = numberOfPlayers;
        //default
        this->price_level = 3;
    }

    void setNextPlayer() {
        if (playerId + 1 > numberPlayers) {
            playerId = 0;
        }
        else {
            playerId += 1;
        }
    }

    int getNextPlayer() {
        return this->playerId;
    }

    void updatePlayerCount(int playersSize) {

        this->numberPlayers = playersSize;
    }

    void setNewRequest(int player_id, int count, int requestPrice) {
        cout << "\nRequest Принят\n";
        Request newReq(player_id, count, requestPrice);
        this->requestsESM.push_back(newReq);
        cout << "-----------\nin Bank successfuly request pushed-----------\n" << this->requestsESM.size();
        for (Request req : this->requestsESM) {
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
            this->availableESM = floor(1 * numberPlayers);
            this->availableEGP = floor(3 * numberPlayers);
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
            this->availableESM = floor(2 * numberPlayers);
            this->availableEGP = floor(2 * numberPlayers);
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
            this->availableESM = floor(3 * numberPlayers);
            this->availableEGP = floor(1 * numberPlayers);
        }

    }

    void setPriceLevel() {
        //очищаем предыдыщие заявки
        requestsESM.clear();
        int oldLevel = price_level;

        //СВЯТОЙ РАНДОМ!!!!!
        random_device rd;
        mt19937 gen(rd());
        std::map<int, int> m;
        int newlevel;
        if (oldLevel == 1) {
            discrete_distribution<> dist({ 0, 0.3, 0.3, 0.16, 0.08, 0.08 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;
            // просто выводим что сгенериловалось ДЛЯ ДЕБАГА
            //            for (auto p: m)
            //                std::cout << p.first << " generated " << p.second << " times\n";
            //            cout << " past level = " << price_level << " newLevel = " << newlevel;
            this->price_level = newlevel;
        }
        if (oldLevel == 2) {
            discrete_distribution<> dist({ 0, 0.25, 0.3, 0.25, 0.0833, 0.0833 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;
            this->price_level = newlevel;
        }
        if (oldLevel == 3) {
            discrete_distribution<> dist({ 0, 0.08, 0.25, 0.30, 0.25, 0.0833 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;
            this->price_level = newlevel;
        }
        if (oldLevel == 4) {
            discrete_distribution<> dist({ 0, 0.08, 0.08, 0.25, 0.30, 0.25 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;

            this->price_level = newlevel;
        }
        if (oldLevel == 5) {
            discrete_distribution<> dist({ 0, 0.08, 0.08, 0.16, 0.30, 0.30 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;
            this->price_level = newlevel;
        }
        setEGP_ESM();
    }

    void sellESM(int toSellESM) {
        if (this->availableESM - toSellESM >= 0) {
            this->availableESM -= toSellESM;
        }
    }

    void sellEGP(int toSellEGP) {
        if (this->availableEGP - toSellEGP >= 0) {
            this->availableEGP -= toSellEGP;
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
        cout << "\n Игрок #" << playerId << " старший \n";
    }

};

//class Fabric {
//private:
//    int playerId;
//    string FabricType;
//    int fabricId;
//    int costOfRecycleESM;
//public:
//    Fabric(int playerId, string FabricType) {
//    }
//};


class Player {
private:
    int id;
    string nickname;
    int money;
    int auto_fabric;
    int default_fabric;
    int egp;
    int esm;
    bool isBancrupt;
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

    int getDefaultFabrics() {
        return default_fabric;
    }

    int getAutoFabrics() {
        return auto_fabric;
    }

    void setEsm(int esmCount, int esmPrice) {
        this->esm += esmCount;
        this->money -= esmPrice * esmCount;
    }

    void setEGP(int egpCount, int egpPrice) {
        this->egp -= egpCount;
        this->money += egpCount * egpPrice;
    }

    bool IfBankrupt() {
        if (this->money < 0) {
            this->isBancrupt = true;
            return true;
        }
        else {
            return false;
        }

    }

    int getTaxAmount() {
        return abs(300 * getEsm() + 500 * getEgp() + 1000 * getDefaultFabrics() + 1000 * getAutoFabrics());
    }

    void printInfo() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "\n------------------\n" << nickname
            << " Номер-" << id;
         SetConsoleTextAttribute(hConsole, 10);
         cout << "\n\nДенег: " << money << "$";
         SetConsoleTextAttribute(hConsole, 14);
           cout << "\nЕСМ:" << this->esm << " ЕГП:" << this->egp
            << "\nФабрики автоматизированные:" << auto_fabric
            << "\nФабрики обычные: " << default_fabric

            << "\n---------\nНалог ЕСМ:300$" << "\tЕГП:500$" << "\nОбычная Фабрика:1000$\tАвто Фабрика:1500$\n---------\n"
            << "\nНАЛОГИ В КОНЦЕ МЕСЯЦА ПРЕДПОЛАГАЕМЫЕ:"<< getTaxAmount()<<"$"
            << "\n------------------\n";
           SetConsoleTextAttribute(hConsole,11);

    }


    Request buyESM(Bank Manager) {
        int FLAG = 1;
        system("cls");
        this->printInfo();
        cout << "\n\nЗапрос на ЕСМ\n\n";
        cout << "\n доступные ЕСМ для покупки: " << Manager.getAvailableESM() << " шт. от "
            << Manager.getPrice_ESM();
        cout << "\n доступные ЕГП для продажи банку: " << Manager.getAvailableEGP() << " шт. до "
            << Manager.getPrice_EGP();

        int player_esm_price;
        int player_esm_count;

        cout << "\n Введите цену (больше " << Manager.getPrice_ESM() << "):";
        cin >> player_esm_price;
        cout << "\nВведите количество:";
        cin >> player_esm_count;
        cout << "\nС вашего счета спишется " << player_esm_price * player_esm_count << " \n";
        cout << "\nВведите 0 для подтверждения\n";
        cin >> FLAG;
        if (FLAG==0)
        {
            Request ESMnewRequest = Request(this->id, player_esm_count, player_esm_price);
            // добавляем запрос в список
            return ESMnewRequest;
        }
        else {
            // пустой
            Request ESMnewRequest = Request(this->id, 0, 0);
            return ESMnewRequest;
        }

    }

    Request sellEGP(Bank Manager) {
        system("cls");
        this->printInfo();
        int FLAG = 1;
        int player_egp_price, player_egp_count;
        cout << "\n\nЗапрос на ЕГП\n\n";
        cout << "\n доступные ЕСМ для покупки: " << Manager.getAvailableESM() << " шт. от "
            << Manager.getPrice_ESM();
        cout << "\n доступные ЕГП для продажи банку: " << Manager.getAvailableEGP() << " шт. до "
            << Manager.getPrice_EGP();

        cout << "\n Введите цену (меньше " << Manager.getPrice_EGP() << "):";
        cin >> player_egp_price;
        cout << "\n Введите количество ЕГП" << endl;
        cin >> player_egp_count;

        cout << "\nС вашего счета спишется " << player_egp_price * player_egp_count << " \n";
        cout << "\nВведите 0 для подтверждения\n";
        cin >> FLAG;
        if (FLAG == 0)
        {
            Request ESMnewRequest = Request(this->id, player_egp_count, player_egp_price);
            // добавляем запрос в список
            return ESMnewRequest;
        }
        else {
            // пустой
            Request ESMnewRequest = Request(this->id, 0, 0);
            return ESMnewRequest;
        }
    }

    void payTaxes() {
        int taxAmount = 0;
        taxAmount = getTaxAmount();
        money = money - taxAmount;
        cout << taxAmount << "$\n";

    }
};


int main() {
    //Русский язык
    setlocale(LC_ALL, "Russian");
    //стайл
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);


    const int esm_tax = 300;
    const int egp_tax = 500;
    const int defaultFabric_tax = 1000;
    const int autoFabric_tax = 1500;
    // длительность игры
    int GAME_LENGTH;
    // параметры клиентского игрока
    int p_client_id = 0;
    string p_client_nickname = "| Main Corp. |";

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

    Player client(p_client_id, p_client_nickname);

    players.emplace_back(client);
    //СОздание других
    const int BOT_COUNT = 2;
    for (int i = 0; i < BOT_COUNT; i++) {
        string arr[BOT_COUNT] = { "Арасака Индастриз", "Флоатинг Технолоджи" };
        players.emplace_back(Player(i + 1, arr[i]));
    }
    //    for (int i = 0; i < players.size(); i++) {
    //        players[i].printInfo();
    //    }
    //cout<<"\n\n players.size() ="<<players.size()<<"\n\n";


    // Главный менеджер игры в котором происходит все
    Bank Manager(GAME_LENGTH, players.size());

    for (int i = 0; i < GAME_LENGTH; i++) {
        for (Player player : players) {
            //Проверка не банкрот ли игрок
            if (player.getMoney()<0) {
                auto iter = players.cbegin();
                players.erase(iter + Manager.getPlayerId());
            }
        }
        cout << "\n\n\n\n\n";
        Manager.setPriceLevel();
        Manager.getPrice_Level();
        Manager.updatePlayerCount(players.size());
        vector<Request> esmRequestList;
        vector<Request> egpRequestList;


        for (int j = 0; j < players.size(); j++) {


            system("cls");
            //текущий игрок
            Player p = players[j];

            // p.makeRequest(Manager);
            //Создаем новый запрос и помещаем его в список запросов
            p.printInfo();
            esmRequestList.push_back(p.buyESM(Manager));
            egpRequestList.push_back(p.sellEGP(Manager));

        }
        // Обрабатываем запросы на есм и егп

        cout << "\nПосле prime\n";
        //сортируем заявки ЕСМ по цене
        for (int f = 0; f < esmRequestList.size() - 2; f++) {
            //предполагается что каждый делает какую либо заявку
            //заявки на есм
            if (esmRequestList[f].getReqPrice() < esmRequestList[f + 1].getReqPrice()) {
                swap(esmRequestList[f], esmRequestList[f + 1]);
                f++;
            }
            ////заявки на егп
            if (egpRequestList[f].getReqPrice() > egpRequestList[f + 1].getReqPrice()) {
                swap(egpRequestList[f], egpRequestList[f + 1]);
                f++;
            }
            cout << "отсортировано";
        }

        // ЕСМ Запрос
        cout << "ЕСМ ЗАПРОС";
        for (Request r : esmRequestList) {


            int idPlayerReq = r.getRequestPlayerId();

            cout << "\nECM запрос";
            // players[idPlayerReq].printInfo();
            if (Manager.getAvailableESM() >= r.getCount()) {
                players[idPlayerReq].setEsm(r.getCount(), r.getReqPrice());
                Manager.sellESM(r.getCount());

            }


        }
        // ЕГП Запрос
        for (Request r : egpRequestList) {

            int idPlayerReq = r.getRequestPlayerId();

            if (Manager.getAvailableEGP() >= r.getCount()) {
                players[idPlayerReq].setEGP(r.getCount(), r.getReqPrice());
                Manager.sellEGP(r.getCount());
            }
        }

        system("cls");
        cout << "\n-----\nВ конце месяца плата налогов\n------\n";
        for (Player p : players) {
            cout << "\n\n налоги: ";
            p.payTaxes();

            cout << "\n\n";
            p.printInfo();
        }
        string finish;
        cout << "\nЗакончить месяц (нажмите enter)\n";
        cin >> finish;
        egpRequestList.clear();
        esmRequestList.clear();

        cout << "\nКонец месяца\n";
        Manager.setNextPlayer();
    }
}