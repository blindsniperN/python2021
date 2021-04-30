#include "game.h"
#include <string>
#include "database/database.h"
#include "person/person.h"
#include <ctime>
namespace game {
  int Level::PlayLevel() {
    // дописать увеличение здоровья
    std::cout << "The level has started...\n";
    std::string s, name;
    for (size_t i = 0; i < protagonists_.size(); ++i) {
      auto p = protagonists_.get();
      std::cout << "Current move is by your character " << p.getName() <<'\n';
      std::cout << "Type in the name of the attack you want to do\n";
      std::cin >> s;
      std::cout << "Type in the name of the opponent you want to attack\n";
      std::cin >> name;
      auto a = antagonists_.find(name);
      if (s == "seduce") { // если атака - соблазнение
        pers_class::DiceRoll prota = p.Seduce();
        int defense = a.RandomDefense();
        if (defense == 0) { // если противник игнорирует
          pers_class::DiceRoll anta = a.Ignore();
          if (prota < anta) { // если бросок провален
          } else { // если победа при броске
          }
        } else { // если противник меняет тему
          pers_class::DiceRoll anta = a.ChangeTheme();
        }
      } else if (s == "argument") {
      } else if (s == "convince") {
      } else if (s == "deceive") {
      } else if (s == "mock") {
      }
    }
  }

  Level Level::GenerateRandom(int difficulty, teams::Team protagonists, const IDataBase<PersonContainer>* antagonists_db) {
      difficulty = std::min(difficulty, kMaxDifficulty);
      int max_protagonists, max_antagonists;
      max_protagonists = kMaxProtagonistsOnLevel[difficulty];
      max_antagonists = kMaxAntagonistsOnLevel[difficulty];
      protagonists.updateMaxSize(max_protagonists);
      teams::Team antagonists(max_antagonists);
      std::vector<PersonContainer> antagonist_list = antagonists_db->listAll();
      int count = antagonist_list.size();
      //srand(std::time(0));
      for (int i = 0; i < std::min(max_antagonists, count); ++i) {
          int select = rand() % antagonist_list.size();
          antagonists.add(Person(antagonist_list[select]));
          antagonist_list.erase(antagonist_list.begin() + select);
      }
      return Level(difficulty, protagonists, antagonists);
  }
}