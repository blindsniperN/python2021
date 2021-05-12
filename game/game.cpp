
#include "game.h"

namespace game {

// 0 - пользователь вышел совсем, 1 - пользователь проиграл, 2 - выиграл
// также тут можно немного настроить, если есть желание выдавать разное
// количество очков за разные штуки
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

Level Level::GenerateRandom(int difficulty, teams::Team protagonists, const database::IDataBase<pers_class::PersonContainer> * antagonists_db)
{

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


} // namespace game
