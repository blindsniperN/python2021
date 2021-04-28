#pragma once
#include "../database/filedatabase/filedatabase.h"
#include "../person/person.h"
using namespace pers_class;
class Settings {
public:
    static void Start();
    static IDataBase<PersonContainer>* protagonists_;
    static IDataBase<PersonContainer>* antagonists_;
private:
    template<bool IsProtagonist>
    static void CreatePerson(); // true - protagonist, false - antagonist

    template<bool IsProtagonist>
    static void UpdatePerson(const std::string&);
};

IDataBase<PersonContainer>* Settings::protagonists_ = nullptr;
IDataBase<PersonContainer>* Settings::antagonists_ = nullptr;