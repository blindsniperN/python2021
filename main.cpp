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

void Help() {
    std::cout << "Very informative help\n";
}

int main() {
    srand(std::time(0));
    IDataBase<PersonContainer>* protagonists = new FileDataBase<PersonContainer>(kProtagonistsTableName);
    IDataBase<PersonContainer>* antagonists = new FileDataBase<PersonContainer>(kAntagonistsTableName);
    Settings::protagonists_ = protagonists;
    Settings::antagonists_ = antagonists;

    bool exit = false;
    while (!exit) {
        std::cout << "Welcome to Scream Queens Game! What would you like to do?\n";
        std::cout << "1. Read rules\n";
        std::cout << "2. Play\n";
        std::cout << "3. Settings\n";
        std::cout << "4. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                Help(); // запустить помощь
                break;
            case 2:
                Play(protagonists, antagonists);
                break;
            case 3:
                Settings::Start();
                break;
            case 4:
                exit = true;
                break;
            default:
                std::cout << "No such option was provided. Try again.\n";
        }
    }


    delete protagonists;
    delete antagonists;

}

