//
// Created by Joaquina Daeron on 10/4/23.
//

#include <configurates.h>

int main() {
    std::cout << "Input height and width of field: ";
    joaquind::size_t h, w;
    std::cin >> h >> w;
    joaquind::field f (h, w);
    joaquind::snake<joaquind::field> s(std::pair(h, w));
    joaquind::game<joaquind::field, joaquind::snake<joaquind::field>, joaquind::Meal> g(f, s);
    std::cout << "Press any key for start\n";
    g.start();
    return 0;
}