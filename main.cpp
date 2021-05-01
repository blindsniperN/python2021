#pragma once
#include <iostream>
#include "database/filedatabase/filedatabase.cpp"
#include "person/person.cpp"
#include "person/factories.h"
#include <vector>
#include "exceptions/exceptions.h"
#include "person/teams.cpp"
#include "settings/settings.cpp"
#include "game/game.cpp"
#include <ctime>
using namespace teams;
using namespace database;
using namespace pers_class;
using namespace game;
int main() {
    srand(std::time(0));
    IDataBase<PersonContainer>* protagonists = new FileDataBase<PersonContainer>(kProtagonistsTableName);
    IDataBase<PersonContainer>* antagonists = new FileDataBase<PersonContainer>(kAntagonistsTableName);
    Settings::protagonists_ = protagonists;
    Settings::antagonists_ = antagonists;
    Settings::Start();
//    Team heroes(3);
//    std::vector<PersonContainer> help = protagonists->listAll();
//    //help.resize(std::min(3, help.size()));
//    for (const auto& i: help) {
//        heroes.add(Person(i));
//    }
//
//    for (int i = 0; i < heroes.size(); ++i)
//        std::cout << heroes.get().getName() << ' ';
//    Level level = Level::GenerateRandom(2, heroes, antagonists);
//    level.PlayLevel();
    delete protagonists;
    delete antagonists;
//    IDataBase<PersonContainer>* db = new FileDataBase<PersonContainer>("lol");
////    std::cout << "created";
////    Factory personFactory;
////    std::vector<short> params(4);
////    params[0] = 0; params[1] = 1; params[2] = 2; params[3] = 3;
////    ParameterList parameterList(params);
////    std::vector<short> skills(10);
////    for (short i = 0; i < 10; ++i) {
////        skills[i] = i;
////    }
////    SkillList skillList(parameterList, skills);
////    std::cout << "lol";
////    skills = skillList.getSkills();
////    std::cout << '"' << skills.size() << '"';
////    for (int i = 0; i < 10; ++i) {
////        std::cout << skills[i] << '\n';
////    }
////    std::vector<short> attack(6, 1);
////    std::vector<short> defense(2, 1);
////    std::vector<short> tools(4, 1);
////    Person person = personFactory.createPerson("Test", parameterList, skillList, attack, defense, tools);
////    db->add(person);
//    std::vector<Person> test_vec;
//    test_vec.push_back(db->get("Test"));
//    test_vec.push_back(db->get("LOl"));
//    Team test = Team(2, test_vec);
//    std::cout << test.find("lol").toString() << '\n';
//    for (int i = 0; i < test.size(); ++i) {
//        std::cout << test.get().toString() << '\n';
//    }
//    delete db;
}

