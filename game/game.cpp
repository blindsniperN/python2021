#include "game.h"
#include <iostream>
#include <windows.h>
#include <string>

Game::Game() {
  // считываем всё из базы данных
  std::cout << "Hi, bitches! Do you want to start the game, or do you need some help?\n";
  Sleep(200);
  std::cout << "Oh";
  for (int i = 0; i < 3; ++i) {
    Sleep(200);
    std::cout << ".";
  }
  std::cout << '\n';
  Sleep(200);
  std::cout << "So I cannot hear you...";
  Sleep(200);
  std::cout << "Then";
  for (int i = 0; i < 3; ++i) {
    Sleep(200);
    std::cout << ".";
  }
  std::cout << '\n';
  Sleep(200);
  std::string s = "";
  while ((s != "START") and (s != "HELP")) {
    std::cout << "Type START to start game and type HELP to get help!\n";
    std::cin >> s;
    if (s == "START") { }
    else if (s == "HELP") { }
    else std::cout << "Are you stupid or something? Let's try one more fucking time!\n";
  }
}

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

