#pragma once
#include "filedatabase.h"
#include <fstream>
#include <iostream>
#include "../../exceptions/exceptions.h"
template <typename T>
FileDataBase<T>::FileDataBase(const std::string& name): IDataBase<T>(name) {
    std::ifstream f(name);
    std::string line;
    while (std::getline(f, line)) {
        std::cout << line;
        T tmp = line;
        items[tmp.getName()] = tmp;
        std::cout << tmp.toString() << '\n';
    }
    f.close();

}

template<typename T>
void FileDataBase<T>::add(const T& item) {
    items.emplace(item.getName(), item);
}

template <typename T>
void FileDataBase<T>::del(const std::string& name) {
    try {
        items.erase(name);
    } catch (...) {
        //throw NotFound();
        std::cout << "del failed";
    }

}

template <typename T>
T& FileDataBase<T>::get(const std::string& name) {
    try {
        return items[name];
    } catch (...) {
        //throw NotFound();
        std::cout << "get failed";
    }
}

template <typename T>
FileDataBase<T>::~FileDataBase() {
    std::cout << this->name_ << '\n';
    std::ofstream f(this->name_);
    for (auto it = items.begin(); it != items.end(); ++it) {
        f << (it->second).toString() << '\n';
    }
    f.close();
}