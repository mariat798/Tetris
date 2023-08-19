//
//  utils.cpp
//  Tetris
//
//  Created by Maria Trotskaya on 2023-06-25.
//

#include "utils.hpp"

#include <random>

namespace utils
{
    int random(int min, int max)
    {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<> d(min, max);
        
        return d(gen);
    }
}
