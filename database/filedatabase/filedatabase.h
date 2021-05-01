#pragma once
#include "database/database.h"
#include <string>
#include <map>
using namespace database;

template <typename T>
class FileDataBase: public IDataBase<T> {
public:
    FileDataBase(const std::string&);
    void add(const T&) override;
    void del(const std::string&) override;
    T get(const std::string&) const override;
    std::vector<T> listAll() const override;
    ~FileDataBase() override;
private:
    std::map<std::string, T> items;
};