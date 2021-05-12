#ifndef GAME_GAME_H
#define GAME_GAME_H


#include "teams.h"

namespace game {

class Level {
  private:
    // сложность
    int difficulty_;

    // протагонисты (шанели)
    teams::Team protagonists_;

    // антагонисты (противники)
    teams::Team antagonists_;


  public:
    inline Level(int a, teams::Team b, teams::Team c) : difficulty_(a), protagonists_(b),
                                                    antagonists_(c) { };

    ~Level() = default;

    // 0 - пользователь вышел совсем, 1 - пользователь проиграл, 2 - выиграл
    // также тут можно немного настроить, если есть желание выдавать разное
    // количество очков за разные штуки
    int PlayLevel();

    static Level GenerateRandom(int difficulty, teams::Team protagonists, const database::IDataBase<pers_class::PersonContainer> * antagonists_db);

};

} // namespace game
#endif
