#pragma once
#include "../stats/stats.cpp"
#include <string>
#include <vector>

namespace pers_class
{

  struct DiceRoll { // надо потом перенести в другой файл
    short to_hit = 0; // на попадание
    short dmg = 0; // урон
    DiceRoll() = default;
    ~DiceRoll() = default;
  };

  class Person {
   protected:
    stats_library::SkillList skills_;
    stats_library::ParameterList parameters_;
    std::vector<int> attack_probability_;
    std::vector<int> defense_probability_;
    std::vector<int> tool_probability_;
   public:
    std::string name_;
    // атаки
    DiceRoll Seduce(); // соблазнить
    DiceRoll MakeAnArgument(); // привести довод
    DiceRoll Intimidate(); // запугать
    DiceRoll Deceive(); // обмануть
    DiceRoll Mock(); // насмехнуться
    // защиты
    DiceRoll Ignore(); // игнорировать
    DiceRoll ChangeTheme(); // смена темы
    // рычаги
    short Love(); // любовь
    short Research(); // изучить
    short Hint(); // намёк
    short Bribe(); // подкуп
    // атака для ИИ, для игрока - случайная атака
    int CustomAttack();
    int CustomDefense();
    int CustomTool();
    // конструктор / деструктор
    Person(const std::string&, const stats_library::ParameterList&,
           const stats_library::SkillList&, const std::vector<int>&,
           const std::vector<int>&, const std::vector<int>&);
    ~Person() = default;
  };

}
