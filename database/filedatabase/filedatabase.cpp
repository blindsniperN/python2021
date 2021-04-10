#pragma once
#include "filedatabase.h"
#include <fstream>

template <typename T>
FileDataBase<T>::FileDataBase(const std::string& name): IDataBase<T>(name) {
    std::ifstream f(name);
    std::string line;
    while (f >> line) {
        T tmp = line;
        items[tmp.getName()] = tmp;
    }
    f.close();
}

template<typename T>
void FileDataBase<T>::add(const T& item) {
    items.emplace(item.getName(), item);
}

template <typename T>
void FileDataBase<T>::del(const T& item) {
    items.erase(item.getName());
}

template <typename T>
T FileDataBase<T>::get(const std::string& name) {
    return items[name];
}

template <typename T>
FileDataBase<T>::~FileDataBase() {
    std::ofstream f(this->name_);
    for (auto it = items.begin(); it != items.end(); ++it) {
        f << (it->second).toString() << '\n';
    }
    f.close();
}