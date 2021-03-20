#include "game/game.h"
#include <string>
#include <map>
#include <iostream>
int main() {
    Game game;
    while (true) {
        std::string command;
        std::cin >> command;
        switch (game.Translate(command)) { // подумать как переделать свитч для строк
            case "help":
                game.Help();
                break;
            case "people":
                game.ListPeople();
                break;
            case "levels":
                game.ListLevels();
                break;
            case "teams":
                game.ListTeams();
                break;
            case "play":
                std::string level, team;
                std::cin >> level >> team;
                game.Play(game.GetLevel(level), game.GetTeam(team));
            case "create":
                std::string what;
                std::cin >> what;
                switch (game.Translate(what)) {
                    case "person":
                        game.CreatePerson();
                        break;
                    case "team":
                        game.CreateTeam();
                        break;
                    case "level":
                        game.CreateLevel();
                        break;
                }
                break;
            case "delete":
                std::string instance, which;
                std::cin >> instance >> which;
                switch (game.Translate(instance)) {
                    case "person":
                        game.DeletePerson(which);
                        break;
                    case "team":
                        game.DeleteTeam(which);
                        break;
                    case "level":
                        game.DeleteLevel(which);
                        break;
                }
                break;
            case "language":
                std::string language;
                std::cin >> language;
                game.ChangeLanguage(language);
                break;
            // функции для магазина
            case "market":
                game.ListObjects();
                break;
            case "buy":
                std::string object;
                std::cin >> object;
                game.BuyObject(object);
            case "balance":
                std::cout << "Your balance: " << game.GetBalance();
                break;
        }
    }
}