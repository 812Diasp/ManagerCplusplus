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
    int currentRound;

    int MIN_ESM_Price;
    int MAX_EGP_Price;

    vector<Request> requestsESM;

    int availableESM, availableEGP;
public:
    Bank(int game_length, int numberOfPlayers) {
        this->current_game_length = game_length;
        this->playerId = 0;
        this->numberPlayers = numberOfPlayers;
        this->currentRound = 1;
        //default
        this->price_level = 3;
    }

    void updateRound() {
        currentRound = currentRound + 1;
    }
    int getRound() {
        return currentRound;
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

        }
        if (oldLevel == 2) {
            discrete_distribution<> dist({ 0, 0.25, 0.3, 0.25, 0.0833, 0.0833 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;

        }
        if (oldLevel == 3) {
            discrete_distribution<> dist({ 0, 0.08, 0.25, 0.30, 0.25, 0.0833 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;

        }
        if (oldLevel == 4) {
            discrete_distribution<> dist({ 0, 0.08, 0.08, 0.25, 0.30, 0.25 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;


        }
        if (oldLevel == 5) {
            discrete_distribution<> dist({ 0, 0.08, 0.08, 0.16, 0.30, 0.30 });
            for (int n = 0; n < 1; ++n)
                ++m[dist(gen)];
            //Назначение нового уровня цены
            for (auto p : m)
                newlevel = p.first;

        }
        this->price_level = newlevel;
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

class Loan {
public:
    int playerId;
    int money;
    int deadline;

    // Конструктор класса
    Loan(int playerId, int money, int deadline) {
        this->playerId = playerId;
        this->money = money;
        this->deadline = deadline;
    }
    int getId() {
        return playerId;
    }
    int getMoney() {
        return money;
    }
    int getDeadline() {
        return deadline;
    }
    void print() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\nID: " << playerId << " " << money << "$ Срок:" << deadline;
    }

    // Дополнительные методы и функции класса Loan могут быть добавлены здесь
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
    bool isBancrupt;
    vector <Loan> loans;

public:

    Player(int id, string nname) {
        this->default_fabric = 2;
        this->auto_fabric = 1;
        this->money = 10000;
        this->egp = 2;
        this->esm = 4;
        this->nickname = nname;
        this->id = id;
        //инициализация вектора (БЕЗ ЭТОГО НЕ РАБОТАЕТ)
        this->loans.push_back(Loan(id, 100, 0));
        this->loans.clear();
    };
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
    /*купили есм потратили деньги*/
    void setEsm(int esmCount, int esmPrice) {
        this->esm += esmCount;
        this->money -= esmPrice * esmCount;
    }
    // проали егп получили деньги
    void setEGP(int egpCount, int egpPrice) {
        this->egp -= egpCount;
        this->money += egpCount * egpPrice;
    }



    int getTaxAmount() {
        return abs(300 * getEsm() + 500 * getEgp() + 1000 * getDefaultFabrics() + 1500 * getAutoFabrics());
    }

    int getTotalCapital(Bank Manager) {
        int capital =
                Manager.getPrice_ESM() * this->esm
                + Manager.getPrice_EGP() * this->egp
                + this->money
                + getAutoFabrics() * 10000
                + getDefaultFabrics() * 5000;
        return capital;
    }
    //Для вычисления примерного капитала без использования текущих данных ЕСМ И ЕГП
    int getExampleCapital() {
        // Среднее значение
        // ЕГП = 5500  ЕСМ=530
        int capital = getEsm() * 530
                      + getEgp() * 5500
                      + this->money
                      + getAutoFabrics() * 10000
                      + getDefaultFabrics() * 5500;
        return capital;
    }

    void printInfo() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "\n------------------\n" << nickname
             << " Номер-" << id;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "\n\nДенег: " << money << "$" << "\nНАЛОГИ ~" << getTaxAmount() + 500 << "$\n";
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\nЕСМ:" << this->esm << " ЕГП:" << this->egp
             << "\nАвто Фабрики:" << auto_fabric
             << "\nОбычные Фабрики:" << default_fabric
             << "\n\nНалоги\nЕСМ: 300$" << "\nЕГП: 500$" << "\nОб.Фабрика: 1000$\nАвто.Фабрика: 1500$\n\n"

             << "------------------\n";

        cout << "\nНепогашенные ссуды:" << this->loans.size() << endl;

        for (int i = 0; i < loans.size(); i++) {
            this->loans[i].print();
        }


        SetConsoleTextAttribute(hConsole, 11);

    }
    void displayResults() {
        cout << nickname << " " << money << "$ Капитал: " << getExampleCapital() << "$";
    }


    Request buyESM(Bank Manager) {
        char FLAG = '1';

        this->printInfo();
        cout << "\nТЕКУЩИЙ РАУНД:" << Manager.getRound();
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
        cout << "\nС вашего счета спишется " << player_esm_price * player_esm_count << "$ \n";
        cout << "\nВведите 0 для подтверждения\n";
        cin >> FLAG;
        if (FLAG == '0')
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
        char FLAG = '1';
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
        if (player_egp_count <= getEgp())
        {
            cout << "\nПри продаже на ваш счет может поступить " << player_egp_price * player_egp_count << "$ \n";
            cout << "\nВведите 0 для подтверждения\n";
            cin >> FLAG;
            if (FLAG == '0')
            {
                if (player_egp_count > this->getEgp())
                {
                    Request ESMnewRequest = Request(this->id, 0, 0);
                    return ESMnewRequest;
                }
                else {
                    Request ESMnewRequest = Request(this->id, player_egp_count, player_egp_price);
                    // добавляем запрос в список
                    return ESMnewRequest;
                }

            }
                //если ввел другое
            else {
                // пустой
                Request ESMnewRequest = Request(this->id, 0, 0);
                return ESMnewRequest;
            }
        }



    }

    void payTaxes() {
        int taxAmount = 0;
        taxAmount = getTaxAmount();
        money = money - taxAmount;
        cout << taxAmount << "$\n";

    }

    void produceEGP() {
        system("cls");
        int esmCount = 0;
        int defFabCost = 2000;
        int autoFabCost = 3000;
        // для подтверждений
        int confirm;
        this->printInfo();
        cout << "\nВведите желаемое количество ЕСМ для переработки в ЕГП:";
        cin >> esmCount;
        if (esmCount != 0)
        {
            // если есм четное и есть авто фабрики
            if ((esmCount % 2 == 0) && (this->getAutoFabrics() >= 1)) {
                int playerAutoFabs = this->getAutoFabrics();

                cout << "На " << playerAutoFabs << " авто-фабриках вы можете произвести только " << playerAutoFabs * 2 << " ЕГП из " << playerAutoFabs * 2 << " ЕСМ";
                cout << "\nПереработать " << playerAutoFabs * 2 << " шт. ЕСМ? за " << playerAutoFabs * autoFabCost << "$\nНажмите 0 для подтверждения и 1 для отказа: ";
                cin >> confirm;
                if (confirm == 0)
                {
                    this->money -= playerAutoFabs * autoFabCost;
                    this->esm -= playerAutoFabs * 2;
                    this->egp += playerAutoFabs * 2;
                }

            }
                //обычный случай
            else if (esmCount <= this->getEsm()) {
                int playerDefFabs = this->getDefaultFabrics();
                if (esmCount > playerDefFabs)
                {
                    cout << "\nНа " << playerDefFabs << " обычных-фабриках вы можете произвести только " << playerDefFabs << " ЕГП из " << playerDefFabs << " ЕСМ";

                    cout << "\nПереработать " << playerDefFabs << " шт. ЕСМ? за " << playerDefFabs * defFabCost << "$\nНажмите 0 для подтверждения и 1 для отказа: ";
                    cin >> confirm;
                    if (confirm == 0) {
                        this->money -= playerDefFabs * defFabCost;
                        this->egp += playerDefFabs;
                        this->esm -= playerDefFabs;
                    }
                }
                else {
                    cout << "\nНа " << playerDefFabs << " обычных-фабриках вы можете произвести " << esmCount << " ЕГП из " << esmCount << " ЕСМ";
                    cout << "\nПереработать " << esmCount << " шт. ЕСМ? за " << esmCount * defFabCost << "$\nНажмите 0 для подтверждения и 1 для отказа: ";
                    cin >> confirm;
                    if (confirm == 0) {
                        this->money -= esmCount * defFabCost;
                        this->egp += esmCount;
                        this->esm -= esmCount;
                    }
                }


            }

        }


    }

    //ссуда
    int getLoanAmount() {
        int rez = (auto_fabric * 10000) + (default_fabric * 5000);
        return rez;
    }

    //платим ссуды
    void payLoanPercent() {
        double percent;
        double summ = 0;
        for (Loan l : loans) {
            summ += l.getMoney();
        }
        percent = summ / 100;
        int intValue = static_cast<int>(percent);
        //выплачиваем процент
        money = money - percent;

    }
    void addLoan(int loanmoney, int date) {
        Loan newLoan(id, loanmoney, date);
        loans.push_back(newLoan);
        money = money + loanmoney;
    }
    bool loanCheck() {
        int loanTotalAmount = 0;
        for (Loan loan : loans) {
            loanTotalAmount = loanTotalAmount + loan.getMoney();
        }
        //Проверка на не превышение половины капитала
        if (loanTotalAmount > getExampleCapital() / 2) {
            return false;
        }
        else {
            return true;
        }
    }
    void loanPayment(int round) {
        for (int i = 0; i < loans.size(); i++) {
            Loan l = loans[i];
            if (l.getDeadline() == round) {
                string s = "";
                cout << "\nВам нужно заплатить ссуду в размере " << l.getMoney() << "\n Подтвердите операцию любым символом: ";
                cin >> s;
                money = money - l.getMoney();
                cout << "\nВы заплатили ссуду в размере " << l.getMoney() << " ваш баланс составляет " << money << "$";
                //удаляем ссуду из списка
                auto iter = loans.cbegin();
                loans.erase(iter + i);
                if (money < 0) {
                    cout << "\nВы банкрот :)\n";
                }

            }
        }
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
        string arr[BOT_COUNT] = { "Фаррел Корпорейтед", "Арасака Индастриз" };
        players.emplace_back(Player(i + 1, arr[i]));
    }
    //    for (int i = 0; i < players.size(); i++) {
    //        players[i].printInfo();
    //    }
    //cout<<"\n\n players.size() ="<<players.size()<<"\n\n";


    // Главный менеджер игры в котором происходит все
    Bank Manager(GAME_LENGTH, players.size());

    for (int round = 0; round <= GAME_LENGTH; round++) {
        for (Player player : players) {
            //Проверка не банкрот ли игрок
            if (player.getMoney() < 0) {
                auto iter = players.cbegin();
                players.erase(iter + Manager.getPlayerId());
            }
        }
        cout << "\n\n\n\n\n";
        Manager.setPriceLevel();
        Manager.getPrice_Level();
        Manager.updatePlayerCount(players.size());
        /* Manager.currentRound(i);*/
        vector<Request> esmRequestList;
        vector<Request> egpRequestList;
        vector<Loan> playerLoans;


        for (int j = 0; j < players.size(); j++) {
            system("cls");

            //текущий игрок
            Player p = players[j];
            // 3 есм покупка
            esmRequestList.push_back(p.buyESM(Manager));
            //4 егп производство
            p.produceEGP();
            //5 егп продажа
            egpRequestList.push_back(p.sellEGP(Manager));
            //6 платим ссудный процент
            p.payLoanPercent();
            //если срок то платим процент
            p.loanPayment(Manager.getRound());
            //7 берем ссудуу
            system("cls");
            p.printInfo();
            cout << "Взять ссуду в размере " << p.getLoanAmount() << "$ и получить их на счет?\n0 для подтверждения\n";
            int ch;
            cin >> ch;
            if (ch == 0)
            {
                if (p.loanCheck()) {
                    p.addLoan(p.getLoanAmount(), Manager.getRound() + 12);
                }
            }

            p.printInfo();

            players[j] = p;

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
            else {
                players[idPlayerReq].setEGP(Manager.getAvailableEGP(), r.getReqPrice());
                Manager.sellEGP(Manager.getAvailableEGP());
                break;
            }
        }



        system("cls");
        cout << "\n-----\nВ конце месяца плата налогов\n------\n";
        for (Player p : players) {
            cout << "\n\n налоги: ";
            p.payTaxes();
            // заплатить ссуды
            cout << "\n";
            p.printInfo();
            cout << "\ncapital:" << p.getTotalCapital(Manager);
        }
        string finish;
        cout << "\nЗакончить месяц (нажмите enter)\n";
        cin >> finish;
        egpRequestList.clear();
        esmRequestList.clear();

        cout << "\nКонец месяца\n";
        Manager.setNextPlayer();
        Manager.updateRound();


        //конец игры когда round==gameLength
        if (round == GAME_LENGTH) {

            system("cls");

            SetConsoleTextAttribute(hConsole, 10);
            cout << "РЕЗУЛЬТАТЫ ИГРЫ";
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\nИгроки:";

            for (Player p : players) {
                cout << "\n";
                p.displayResults();
                cout << "\n";
            }
            cout << "\n\n\n\n";
            break;
        }
    }
}