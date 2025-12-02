#pragma once

#include <string>

namespace utils {
    namespace color {
        extern const char* none;
        extern const char* red;
        extern const char* green;
        extern const char* yellow;
        extern const char* blue;
        extern const char* magenta;
        extern const char* cyan;
        extern const char* white;
        extern const char* bright_red;
        extern const char* gray;
    }

    namespace TextSpeeds {
        constexpr int SLOW = 40;
        constexpr int MEDIUM = 20;
        constexpr int FAST = 10;
        constexpr int INSTANT = 0;
        constexpr int MAX_MANUAL = 100;
    }

    extern int textSpeed;

    void wait(int seconds);
    void print(const std::string& text, int time, const char* text_color = color::none);
    void hrprint(const std::string& text, int time, const char* text_color = color::none);
    int random(int min, int max);
    bool rightName(std::string& name, const std::string& prompt, int minLength, int maxLength);

    int rightValue();
}