
#include "filedatabase.h"

template<typename T>
 FileDataBase<T>::FileDataBase(const std::string & name) {
}

template<typename T>
void FileDataBase<T>::add(const T & item) {

    if (items.find(item.getName()) != items.end())
        throw AlreadyExists();
    items.emplace(item.getName(), item);
}

template<typename T>
void FileDataBase<T>::del(const std::string & name) {

    if (items.find(name) != items.end())
        items.erase(name);
    else
        throw NotFound();
}

template<typename T>
T FileDataBase<T>::get(const std::string & name) const {

    if (items.find(name) != items.end())
        return items.at(name);
    else
        throw NotFound();

}

template<typename T>
std::vector<T> FileDataBase<T>::listAll() const {

    std::vector<T> list;
    for (auto i = items.begin(); i != items.end(); ++i)
        list.push_back(i->second);

    return list;
}

template<typename T>
 FileDataBase<T>::~FileDataBase() {

    std::ofstream f(kPathToData + this->name_);
    for (auto it = items.begin(); it != items.end(); ++it) {
        f << (it->second).toString() << '\n';
    }
    f.close();
}

