#include <iostream>   
#include <fstream>    
#include <string>     
#include <ctime>      
using namespace std;


class BullsAndCows {
private:
    string secret;     
    int attempts;      

    
    string generateNumber() {
        string digits = "123456789"; // Первая цифра не может быть 0
        string result = "";

        // Выбираем первую цифру
        int pos = rand() % digits.length();
        result += digits[pos];
        digits.erase(pos, 1); 
        digits += "0"; 

        
        for (int i = 1; i <3; i++) {
            pos = rand() % digits.length();
            result += digits[pos];
            digits.erase(pos, 1);
        }

        return result;
    }

    
    bool isValid(string guess) {
        // Проверка длины
        if (guess.length() != 3) {
            cout << "Ошибка: должно быть 3 цифры!\n";
            return false;
        }

        // Проверка, что все символы - цифры
        for (int i = 0; i < 3; i++) {
            if (guess[i] < '0' || guess[i] > '9') {
                cout << "Ошибка: должны быть только цифры!\n";
                return false;
            }
        }

        // Проверка, что первая цифра не 0
        if (guess[0] == '0') {
            cout << "Ошибка: первая цифра не может быть 0!\n";
            return false;
        }

 

        return true;
    }

    // Подсчет быков и коров
    void countBullsCows(string guess, int& bulls, int& cows) {
        bulls = 0;
        cows = 0;

        
        for (int i = 0; i < 3; i++) {
            if (guess[i] == secret[i]) {
                bulls++;
            }
        }

        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i != j && guess[i] == secret[j]) {
                    cows++;
                    break;
                }
            }
        }
    }

    // Сохранение лога игры в файл
    void saveToFile(string mode) {
        ofstream file("game_log.txt", ios::app); // ios::app - добавляем в конец файла

        file << "\n=== Новая игра ===\n";
        file << "Режим: " << mode << "\n";
        file << "Загаданное число: " << secret << "\n";
        file << "Попыток: " << attempts << "\n";
        file << "===================\n";

        file.close();
        cout << "Лог сохранен в файл game_log.txt\n";
    }

public:
    
    BullsAndCows() {
        srand(time(0)); 
    }

    // Игра против компьютера
    void playVsComputer() {
        cout << "\n=== ИГРА ПРОТИВ КОМПЬЮТЕРА ===\n";

        
        secret = generateNumber();
        attempts = 0;

        cout << "Компьютер загадал 3-значное число.\n";
        cout << "Цифры в числе не повторяются.\n";
        cout << "Первая цифра не может быть 0.\n";

        string guess;
        bool won = false;

        // Основной игровой цикл
        while (!won) {
            cout << "\nПопытка " << (attempts + 1) << ": ";
            cin >> guess;

            // Проверяем ввод
            if (!isValid(guess)) {
                cout << "Попробуйте снова: ";
                continue;
            }

            attempts++;

            // Считаем быков и коров
            int bulls, cows;
            countBullsCows(guess, bulls, cows);

            cout << "Быки: " << bulls << ", Коровы: " << cows << "\n";

            // Проверяем победу
            if (bulls == 3) {
                won = true;
                cout << "\nПОБЕДА! Вы угадали число " << secret << "\n";
                cout << "Количество попыток: " << attempts << "\n";
            }
        }

        // Сохраняем результат
        saveToFile("Игрок vs Компьютер");
    }

    // Игра для двух игроков
    void playTwoPlayers() {
        cout << "\n=== ИГРА ДЛЯ ДВУХ ИГРОКОВ ===\n";

        
        cout << "Игрок 1, загадайте число: ";
        do {
            cin >> secret;
        } while (!isValid(secret));

        attempts = 0;

        
        for (int i = 0; i < 40; i++) cout << "\n";

        cout << "Игрок 2, угадывайте число!\n";

        string guess;
        bool won = false;

        // Основной игровой цикл
        while (!won) {
            cout << "\nПопытка " << (attempts + 1) << ": ";
            cin >> guess;

            // Проверяем ввод
            if (!isValid(guess)) {
                cout << "Попробуйте снова: ";
                continue;
            }

            attempts++;

            // Считаем быков и коров
            int bulls, cows;
            countBullsCows(guess, bulls, cows);

            cout << "Быки: " << bulls << ", Коровы: " << cows << "\n";

            // Проверяем победу
            if (bulls == 3) {
                won = true;
                cout << "\nПОБЕДА! Игрок 2 угадал число " << secret << "\n";
                cout << "Количество попыток: " << attempts << "\n";
            }
        }

        // Сохраняем результат
        saveToFile("Два игрока");
    }

    // Показать правила
    void showRules() {
        cout << "\n=== ПРАВИЛА ИГРЫ ===\n";
        cout << "1. Загадывается 3-значное число\n";
        cout << "2. Цифры в числе не повторяются\n";
        cout << "3. Первая цифра не может быть 0\n";
        cout << "4. Игрок пытается угадать число\n\n";
        cout << "Быки - цифры на своих местах\n";
        cout << "Коровы - цифры есть в числе, но не на своих местах\n\n";
        cout << "Пример:\n";
        cout << "Загадано: 1234\n";
        cout << "Игрок ввел: 1356\n";
        cout << "Результат: 1 бык (цифра 1), 1 корова (цифра 3)\n";
    }
};

// Главная функция программы
int main() {
    setlocale(LC_ALL,"RU");

    BullsAndCows game; 
    int choice;        

    do {
        // Показываем меню
        cout << "\n=== БЫКИ И КОРОВЫ ===\n";
        cout << "1. Играть против компьютера\n";
        cout << "2. Играть вдвоем\n";
        cout << "3. Правила игры\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";
        cin >> choice;

        // Обрабатываем выбор
        switch (choice) {
        case 1:
            game.playVsComputer();
            break;
        case 2:
            game.playTwoPlayers();
            break;
        case 3:
            game.showRules();
            break;
        case 0:
            cout << "До свидания!\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }

        // Спрашиваем, хочет ли пользователь продолжить
        if (choice != 0) {
            cout << "\nХотите вернуться в меню? (1-да, 0-нет): ";
            int continueChoice;
            cin >> continueChoice;
            if (continueChoice == 0) {
                choice = 0;
            }
        }

    } while (choice != 0);

    return 0;
}
