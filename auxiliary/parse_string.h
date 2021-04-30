#pragma once
#include <string>
#include <vector>

std::string popFirst(std::string& data, char separator=';') {
    std::string answer = data.substr(0, data.find(';'));
    data = data.substr(data.find(';') + 2, data.size());
    return answer;
}


std::vector<short> popVector(std::string& data, int length, char separator=';') {
    std::vector<short> array(length);
    for (int i = 0; i < length; ++i) {
        array[i] = std::stoi(popFirst(data, separator));
    }
    return array;
}