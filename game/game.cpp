#include "game.h"
#include <iostream>
void Game::ListLevels() {
    for (Level level: levels_) {
        std::cout << level << '\n';
    }
}

void Game::ListTeams() {
    for (Team team: teams_) {
        std::cout << team << '\n';
    }
}

void Game::DeleteLevel(const std::string& name) {
    auto it = levels_.find(name);
    if (it != levels_.end()) {
        levels_.erase(it);
    } else {
        std::exception NotFound;
        throw NotFound;
    }
}

void Game::DeleteTeam(const std::string& name) {
    auto it = teams_.find(name);
    if (it != teams_.end()) {
        teams_.erase(it);
    } else {
        std::exception NotFound;
        throw NotFound;
    }
}

