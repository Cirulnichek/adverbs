#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <random>

std::list<std::tuple<int, int, std::string>> adverbs;

std::random_device rd;
std::mt19937 rng(rd());

void build() {
    std::ifstream in1("../words/fused");
    std::vector<std::tuple<int, int, std::string>> temp;
    std::string s;
    while (std::getline(in1, s))
        temp.emplace_back(0, 1, s);
    std::ifstream in2("../words/separate");
    while (std::getline(in2, s))
        temp.emplace_back(0, 2, s);
    std::shuffle(temp.begin(), temp.end(), rng);
    std::copy(temp.begin(), temp.end(), std::back_inserter(adverbs));
}

int main() {
    build();
    std::cout << "1 - слитно, 2 - раздельно, 3 - выход" << std::endl;
    while (!adverbs.empty()) {
        auto [cnt, right, s] = *adverbs.begin();
        adverbs.erase(adverbs.begin());
        std::cout << s << std::endl;
        int ans;
        std::cin >> ans;
        if (ans == 3) {
            std::cout << "Спасибо за игру" << std::endl;
            return 0;
        }
        if (ans == right) {
            ++cnt;
            if (cnt < 2) {
                auto it = --adverbs.end();
                int c = std::min(rng() % 16, adverbs.size());
                for (int i = 0; i < c; ++i, --it);
                adverbs.emplace(it, cnt, right, s);
            }
            std::cout << "\033[32mВерно\033[0m" << std::endl;
        } else {
            cnt /= 2;
            auto it = adverbs.begin();
            int c = std::min(5 + rng() % 8, adverbs.size());
            for (int i = 0; i < c; ++i, ++it);
            adverbs.emplace(it, cnt, right, s);
            std::cout << "\033[31mНеверно\033[0m" << std::endl;
        }
    }
    std::cout << "Вы выучили все наречия!!!" << std::endl;
}