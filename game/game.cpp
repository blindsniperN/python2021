#include "game.h"
#include <string>

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
}