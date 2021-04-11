#pragma once
#include <string>
#include <map>
class Game {
 public:
  // основные комманды
  Game(); // подготовка настроек, запуск самой игры
  ~Game(); // обновление базы данных и корректное завершение игры
  void Help();
  void Play(Level, Team);

  // вывод данных
  void ListPeople();
  void ListLevels();
  void ListTeams();

  // создание
  void CreatePerson();
  void CreateTeam();
  void CreateLevel();

  // удаление
  void DeletePerson(const std::string&);
  void DeleteTeam(const std::string&);
  void DeleteLevel(const std::string&);

  // язык
  std::string Translate(const std::string&); // перевод с русского на английский
  void ChangeLanguage(const std::string&); // изменить язык игры

  // магазин
  void ListObjects();
  void BuyObject(const std::string&);
  int GetBalance();

 private:
  int state; // что сейчас происходит (нужно для вывода помощи)
  std::map<std::string, Factory> people_templates_;
  std::map<std::string, Levels> levels_;
  std::map<std::string, Team> teams_;
};
