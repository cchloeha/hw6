#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T w[5] = {0, 0, 0, 0, 0};
        int n = static_cast<int>(k.size());
        int pos = n;
        int wIndex = 4;
        while(pos > 0 && wIndex >= 0) {
          int start = std::max(0, pos - 6);
          HASH_INDEX_T value = 0;
          HASH_INDEX_T power = 1;

          for(int i = pos - 1; i >= start; i--) {
            HASH_INDEX_T d = letterDigitToNumber(k[i]);
            value += d * power;
            power *= 36;
          }
          w[wIndex] = value;
          wIndex--;
          pos -= 6;
        }
        HASH_INDEX_T h = 0;
        for(int i = 0; i < 5; i++) {
          h += rValues[i] * w[i];
        }
        return h;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        unsigned char c = static_cast<unsigned char>(letter);
        c = static_cast<unsigned char>(std::tolower(c));
        if(c >= 'a' && c <= 'z') {
          return static_cast<HASH_INDEX_T>(c - 'a');
        }
        else if(c >= '0' && c <= '9') {
          return static_cast<HASH_INDEX_T>(26 + (c - '0'));
        }
        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
