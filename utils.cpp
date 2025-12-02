#include "utils.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <limits>
#include <cctype>

namespace utils {

    // Определение цветов
    namespace color {
        const char* none = "\033[0m";
        const char* red = "\033[31m";
        const char* green = "\033[32m";
        const char* yellow = "\033[33m";
        const char* blue = "\033[34m";
        const char* magenta = "\033[35m";
        const char* cyan = "\033[36m";
        const char* white = "\033[37m";
        const char* bright_red = "\033[91m";
        const char* gray = " \033[90m";
    }

    // Глобальная переменная скорости
    int textSpeed = TextSpeeds::MEDIUM;

    void wait(int seconds) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    void print(const std::string& text, int time, const char* text_color) {
        int t = (time == -1) ? textSpeed : time;
        for (char c : text) {
            std::cout << text_color << c << color::none << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
        }
        std::cout << '\n';
    }

    void hrprint(const std::string& text, int time, const char* text_color) {
        int t = (time == -1) ? textSpeed : time;
        for (char c : text) {
            std::cout << text_color << (char)std::toupper((unsigned char)c) << color::none << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
        }
        std::cout << '\n';
    }

    int random(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }

    int rightValue() {
        int choice;
        while (true) {
            std::cin >> choice;
            if (std::cin.fail()) {
                print("Некорректный ввод. Пожалуйста, введите число.", 10, color::bright_red);
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                return choice;  
            }
        }
    }

    bool rightName(std::string& name, const std::string& prompt, int minLength, int maxLength) {
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, name);

            int nameLength = static_cast<int>(name.length());

            if (name.empty() || nameLength < minLength || nameLength > maxLength) {
                std::cout << "Ошибка! Имя должно содержать от " << minLength
                    << " до " << maxLength << " символов." << std::endl;
                continue;
            }

            bool hasLetter = false;
            for (char c : name) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    hasLetter = true;
                    break;
                }
            }

            if (!hasLetter) {
                std::cout << "Ошибка! Имя должно содержать хотя бы одну букву." << std::endl;
                continue;
            }

            return true;
        }
    }
}
