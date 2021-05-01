#include "game.h"
#include <string>
#include "database/database.h"
#include "person/person.h"
#include <ctime>
#include "../phrases/phrases.cpp"

namespace game {
  void print_team(const std::string& s, teams::Team& team1) {
    std::string s1;
    for (size_t i = 0; i < team1.size(); ++i) { // вывести живых шанелей
      s1 += team1.get().getName();
      if (i != team1.size() - 1) s1 += ", ";
    }
    std::cout << "Remaining " << s << " are: " << s1 << '\n';
  }

  int Level::PlayLevel() {
    for (size_t i = 0; i < antagonists_.size(); ++i) {
      auto a = antagonists_.get();
      a.HP() += 5 * difficulty_; // дописать увеличение здоровья
    }
    SuccessPhrases success;
    FailurePhrases fail;
    std::cout << "The level has started...\n";
    std::string s, name;
    // =============================== ИГРА ===================================
    while (protagonists_.size() != 0 and antagonists_.size() != 0) {
      print_team("Chanels", protagonists_);
      print_team("enemies", antagonists_); // вывести живых врагов
      // ============================ ХОД ИГРОКА =================================
      int size = protagonists_.size();
      for (size_t i = 0; i < size; ++i) {
        auto p = protagonists_.get();
        std::cout << "Current move is by your character " << p.getName()
                  << '\n';
        std::cout << "Type in the name of the attack you want to do\n";
        std::cin >> s;
        std::cout << "Type in the name of the opponent you want to attack\n";
        std::cin >> name;
        auto a = antagonists_.find(name);


        if (s == "seduce") { // если атака - соблазнение
          pers_class::DiceRoll prota = p.Seduce();
          std::cout << "You rolled " << prota.to_hit << " to hit.\n";
          int defense = a.RandomDefense();

          if (defense == 0) { // если противник игнорирует
            pers_class::DiceRoll anta = a.Ignore();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Ignore.\n";
            std::cout << prota.to_hit << ' ' << anta.to_hit << ' ' << difficulty_ << '\n';
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyIgnore(anta.dmg);

            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applySeduce(prota.dmg);
            }

          } else { // если противник меняет тему
            pers_class::DiceRoll anta = a.ChangeTheme();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Change Theme.\n";
              std::cout << prota.to_hit << ' ' << anta.to_hit << ' ' << difficulty_ << '\n';
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyChangeTheme(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applySeduce(prota.dmg);
            }
          }


        } else if (s == "argument") {
          pers_class::DiceRoll prota = p.MakeAnArgument();
          std::cout << "You rolled " << prota.to_hit << " to hit.\n";
          int defense = a.RandomDefense();
          if (defense == 0) { // если противник игнорирует
              pers_class::DiceRoll anta = a.Ignore();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Ignore.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyIgnore(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyArgument(prota.dmg);
            }

          } else { // если противник меняет тему
            pers_class::DiceRoll anta = a.ChangeTheme();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Change Theme.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyChangeTheme(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyArgument(prota.dmg);
            }
          }
        } else if (s == "convince") {
          pers_class::DiceRoll prota = p.Convince();
          std::cout << "You rolled " << prota.to_hit << " to hit.\n";
          int defense = a.RandomDefense();

          if (defense == 0) { // если противник игнорирует
            pers_class::DiceRoll anta = a.Ignore();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Ignore.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyIgnore(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyConvinceDefenser(prota.dmg);
              p.applyConvinceAttacker(prota.dmg);
            }

          } else { // если противник меняет тему
            pers_class::DiceRoll anta = a.ChangeTheme();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to ChangeTheme.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyChangeTheme(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyConvinceDefenser(prota.dmg);
              p.applyConvinceAttacker(prota.dmg);
            }
          }
        } else if (s == "deceive") {
          pers_class::DiceRoll prota = p.Deceive();
          std::cout << "You rolled " << prota.to_hit << " to hit.\n";
          int defense = a.RandomDefense();

          if (defense == 0) { // если противник игнорирует
            pers_class::DiceRoll anta = a.Ignore();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Ignore.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyIgnore(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyDeceiveDefenser(prota.dmg);
              p.applyDeceiveAttacker();
            }

          } else {  // если противник меняет тему
            pers_class::DiceRoll anta = a.ChangeTheme();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Change Theme.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyChangeTheme(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyDeceiveDefenser(prota.dmg);
              p.applyDeceiveAttacker();
            }
          }
        } else if (s == "mock") {
          pers_class::DiceRoll prota = p.Mock();
          std::cout << "You rolled " << prota.to_hit << " to hit.\n";
          int defense = a.RandomDefense();

          if (defense == 0) { // если противник игнорирует
            pers_class::DiceRoll anta = a.Ignore();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                                                    << " to Ignore.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyIgnore(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyMockDefenser(prota.dmg);
              p.applyMockAttacker(prota.dmg);
            }

          } else { // если противник меняет тему
            pers_class::DiceRoll anta = a.ChangeTheme();
            std::cout << a.getName() << " rolled " << anta.to_hit + difficulty_
                      << " to Change Theme.\n";
            if (prota.to_hit <
                anta.to_hit + difficulty_) { // если бросок провален
              std::cout << "You failed to attack!\n";
              std::cout << fail.generate() << '\n';
              p.applyChangeTheme(anta.dmg);
            } else { // если победа при броске
              std::cout << "You managed to attack!\n";
              std::cout << success.generate() << '\n';
              a.applyMockDefenser(prota.dmg);
              p.applyMockAttacker(prota.dmg);
            }
          }
        }
        if (a.HP() <= 0) {
          antagonists_.del(a.getName());
          std::cout << a.getName() << " was found dead.\n";
        }
        if (p.HP() <= 0) {
          protagonists_.del(p.getName());
          std::cout << p.getName() << " was found dead.\n";
        }
        // Если противник умер
      }
      // ============================= ХОД ВРАГА ===============================
      std::cout << "It's the time for antagonists to shine!!!\n";
      for (size_t i = 0; i < antagonists_.size(); ++i) {
        auto a = antagonists_.get();
        pers_class::Person p = protagonists_.getRandom();
        std::cout << p.getName() << " is being attacked!\n";
        std::cout << "Is she going to Ignore or ChangeTheme?\n";
        std::string s1;
        std::cin >> s1;

        // атаки
        pers_class::DiceRoll anta;
        pers_class::DiceRoll prota;
        switch(a.RandomAttack()) {
          case 0: // seduce
            anta = a.Seduce();
            if (s1 == "Ignore") {
              prota = p.Ignore();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applySeduce(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to ignore your opponent!\n";
                a.applyIgnore(prota.dmg);
              }
            } else {
              prota = p.ChangeTheme();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applySeduce(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to change the topic of discussion!\n";
                a.applyChangeTheme(prota.dmg);
              }
            }
            break;

          case 1: // MakeAnArgument
            anta = a.MakeAnArgument();
            if (s1 == "Ignore") {
              prota = p.Ignore();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyArgument(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to ignore your opponent!\n";
                a.applyIgnore(prota.dmg);
              }
            } else {
              prota = p.ChangeTheme();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyArgument(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to change the topic of discussion!\n";
                a.applyChangeTheme(prota.dmg);
              }
            }
            break;

          case 2: // Convince
            anta = a.Convince();
            if (s1 == "Ignore") {
              prota = p.Ignore();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyConvinceDefenser(anta.dmg);
                a.applyConvinceAttacker(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to ignore your opponent!\n";
                a.applyIgnore(prota.dmg);
              }
            } else {
              prota = p.ChangeTheme();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyConvinceDefenser(anta.dmg);
                a.applyConvinceAttacker(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to change the topic of discussion!\n";
                a.applyChangeTheme(prota.dmg);
              }
            }
            break;

          case 3: // Deceive
            anta = a.Deceive();
            if (s1 == "Ignore") {
              prota = p.Ignore();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyDeceiveDefenser(anta.dmg);
                a.applyDeceiveAttacker();
              } else {   // противник не попал
                std::cout << "You managed to ignore your opponent!\n";
                a.applyIgnore(prota.dmg);
              }
            } else {
              prota = p.ChangeTheme();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyDeceiveDefenser(anta.dmg);
                a.applyDeceiveAttacker();
              } else {   // противник не попал
                std::cout << "You managed to change the topic of discussion!\n";
                a.applyChangeTheme(prota.dmg);
              }
            }
            break;

          case 4: // Mock
            anta = a.Mock();
            if (s1 == "Ignore") {
              prota = p.Ignore();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyMockDefenser(anta.dmg);
                a.applyMockAttacker(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to ignore your opponent!\n";
                a.applyIgnore(prota.dmg);
              }
            } else {
              prota = p.ChangeTheme();
              if (prota.to_hit < anta.to_hit + difficulty_) { // противник попал
                std::cout << "You did not manage to outsmart your opponent!\n";
                p.applyMockDefenser(anta.dmg);
                a.applyMockAttacker(anta.dmg);
              } else {   // противник не попал
                std::cout << "You managed to change the topic of discussion!\n";
                a.applyChangeTheme(prota.dmg);
              }
            }
            break;
        }

        if (a.HP() <= 0) {
          antagonists_.del(a.getName());
          std::cout << a.getName() << " was found dead.\n";
        }
        if (p.HP() <= 0) {
          protagonists_.del(p.getName());
          std::cout << p.getName() << " was found dead.\n";
        }
        // Если противник умер
      }
    }
    if (antagonists_.size() == 0) {
      std::cout << "YOU WIN!\n";
      return 2;
    } else {
      std::cout << "YOU LOSE!\n";
      return 1;
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