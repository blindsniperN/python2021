#pragma once
#include <vector>
#include "../person/teams.cpp"
#include "../phrases/phrases.cpp"
#include "../database/database.h"

namespace game {

  class Level {
   private:
    int difficulty_; // сложность
    teams::Team protagonists_; // протагонисты (шанели)
    teams::Team antagonists_; // антагонисты (противники)
   public:
    Level(int a, teams::Team b, teams::Team c): difficulty_(a), protagonists_(b),
                                                antagonists_(c) { }
    ~Level() = default;

    // 0 - пользователь вышел совсем, 1 - пользователь проиграл, 2 - выиграл
    // также тут можно немного настроить, если есть желание выдавать разное
    // количество очков за разные штуки
    int PlayLevel();

    static Level GenerateRandom(int, teams::Team,
                                const database::IDataBase<pers_class::PersonContainer>*);
  };

}
