#include "game.h"
#include <string>
#include "../database/database.h"
#include "../person/person.h"
#include <ctime>
#include "../phrases/phrases.cpp"
#include "../exceptions/exceptions.h"

namespace game {

  // вывести тиму на экран
  void print_team(const std::string& s, teams::Team& team1) {
    std::string s1;
    for (size_t i = 0; i < team1.size(); ++i) { // вывести живых шанелей
      s1 += team1.get().getName();
      if (i != team1.size() - 1) s1 += ", ";
    }
    std::cout << "Remaining " << s << " are: " << s1 << '\n';
  }

  // проверить на смерть
  void checkDeath(pers_class::Person& a, pers_class::Person& p,
                  teams::Team& protagonists_, teams::Team& antagonists_) {
    if (a.HP() <= 0) {
      antagonists_.del(a.getName());
      std::cout << a.getName() << " was found dead.\n";
    }
    if (p.HP() <= 0) {
      protagonists_.del(p.getName());
      std::cout << p.getName() << " was found dead.\n";
    }
  }

  // применение эффектов
  void ApplyEffects(int id, pers_class::Person& attacker,
                    pers_class::Person& defender, short dmg, std::string s) {
    std::cout << s << dmg << " points of damage.\n";
    switch (id) {
      case kIDSeduce:
        defender.applySeduce(dmg);
        break;
      case kIDArgument:
        defender.applyArgument(dmg);
        break;
      case kIDConvince:
        defender.applyConvinceDefenser(dmg);
        attacker.applyConvinceAttacker(dmg);
        break;
      case kIDDeceive:
        defender.applyDeceiveDefenser(dmg);
        attacker.applyDeceiveAttacker();
        break;
      case kIDMock:
        defender.applyMockDefenser(dmg);
        attacker.applyMockAttacker(dmg);
        break;
      case kIDIgnore:
        attacker.applyIgnore(dmg);
        break;
      case kIDChangeTheme:
        attacker.applyChangeTheme(dmg);
        break;
      default:
        throw InvalidIDException();
    }
  }

  void blankLines(int n) {
    for (int i = 0; i < n; ++i) std::cout << '\n';
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

      int prota_id = 0;
      int anta_id = 0;

      // ============================ ХОД ИГРОКА =================================
      int size = protagonists_.size();
      for (size_t i = 0; i < size; ++i) {
        auto p = protagonists_.get();
        std::cout << "Current move is by your character " << p.getName()
                  << '\n';
        std::cout << "Type in the name of the opponent you want to attack\n";
        std::cin >> name;
        auto a = antagonists_.find(name);
        // считываем атаку из входа
        std::string s;
        std::cout << "Type in the name of the attack you want to do\n";
        std::cin >> s;

        pers_class::DiceRoll prota = p.ActionFromInput(prota_id, s);
        pers_class::DiceRoll anta;
        std::cout << "You rolled " << prota.to_hit << " to hit.\n";

        // генерируем защиту
        if (a.RandomDefense() == 0) { //
          anta = a.Ignore();
          anta_id = kIDIgnore;
        } else {
          anta = a.ChangeTheme();
          anta_id = kIDChangeTheme;
        }
        anta.to_hit += difficulty_;
        std::cout << a.getName() << " rolled " << anta.to_hit << " to defend.\n";

        // проверяем, что мы победили
        if (prota.to_hit >= anta.to_hit) {
          std::cout << "You managed to attack!\n";
          std::cout << success.generate() << '\n';
          ApplyEffects(prota_id, p, a, prota.dmg, "You inflicted ");
        } else {
          std::cout << "You failed to attack!\n";
          std::cout << fail.generate() << '\n';
          ApplyEffects(anta_id, p, a, prota.dmg, a.getName() + " inflicted ");
        }

        // Если противник умер
        checkDeath(a, p, antagonists_, protagonists_);
        blankLines(10);
      }
      // ============================= ХОД ВРАГА ===============================
      if (protagonists_.size() != 0) {
        std::cout << "It's the time for antagonists to shine!!!\n";
        for (size_t i = 0; i < antagonists_.size(); ++i) {
          auto a = antagonists_.get();
          pers_class::Person p = protagonists_.getRandom();
          std::cout << p.getName() << " is being attacked!\n";
          std::cout << "Is she going to Ignore or ChangeTheme?\n";
          std::string s1;
          std::cin >> s1;

          // атаки
          pers_class::DiceRoll anta = a.ActionFromInput(anta_id,
                                                        std::to_string(
                                                                a.RandomAttack()));
          anta.to_hit += difficulty_;
          std::cout << a.getName() << " rolled " << anta.to_hit << " to hit.\n";
          pers_class::DiceRoll prota = p.ActionFromInput(prota_id, s1);
          std::cout << "You rolled " << prota.to_hit << " to defend.\n";

          // проверяем, что мы победили
          if (prota.to_hit >= anta.to_hit) {
            std::cout << "You managed to defend!\n";
            std::cout << fail.generate() << '\n';
            ApplyEffects(prota_id, a, p, prota.dmg, "You inflicted ");
          } else {
            std::cout << "You failed to defend!\n";
            std::cout << success.generate() << '\n';
            ApplyEffects(anta_id, a, p, prota.dmg, a.getName() + " inflicted ");
          }
          // Если противник умер
          checkDeath(a, p, antagonists_, protagonists_);
          blankLines(10);
        }
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

  Level Level::GenerateRandom(int difficulty, teams::Team protagonists, const database::IDataBase<pers_class::PersonContainer>* antagonists_db) {
      difficulty = std::min(difficulty, kMaxDifficulty);
      int max_protagonists, max_antagonists;
      max_protagonists = kMaxProtagonistsOnLevel[difficulty];
      max_antagonists = kMaxAntagonistsOnLevel[difficulty];
      protagonists.updateMaxSize(max_protagonists);
      teams::Team antagonists(max_antagonists);
      std::vector<pers_class::PersonContainer> antagonist_list = antagonists_db->listAll();
      int count = antagonist_list.size();
      //srand(std::time(0));
      for (int i = 0; i < std::min(max_antagonists, count); ++i) {
          int select = rand() % antagonist_list.size();
          antagonists.add(pers_class::Person(antagonist_list[select]));
          antagonist_list.erase(antagonist_list.begin() + select);
      }
      return Level(difficulty, protagonists, antagonists);
  }

  void Play(const database::IDataBase<pers_class::PersonContainer>* protagonists_db, const database::IDataBase<pers_class::PersonContainer>* antagonists_db)
  {
      std::cout << "Please select the difficulty of the level (0-" << kMaxDifficulty << ")\n";
      int difficulty;
      std::cin >> difficulty;
      difficulty = std::min(kMaxDifficulty, std::max(0, difficulty)); // откидываем неправильные данные
      teams::Team protagonists = teams::Team::FormTeam(kMaxProtagonistsOnLevel[difficulty], protagonists_db);
      Level level = Level::GenerateRandom(difficulty, protagonists, antagonists_db);
      int result = level.PlayLevel();
      // do smth with result?
  }
}