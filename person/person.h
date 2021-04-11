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

  class PrefixVector {
   private:
    std::vector<short> a;
   public:
    int Sum() { return a[a.size() - 1]; }
    int Index(int roll) { return lower_bound(a.begin(), a.end(), roll)
                                 - a.begin(); }
    PrefixVector(const std::vector<short>&);
    PrefixVector() = default;
    ~PrefixVector() = default;
    std::string toString() const;
  };

  class Person {
   public:
    std::string name_;
    std::string getName() const { return name_; };
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
    int RandomAttack();
    int RandomDefense();
    int RandomTool();
    // конструктор / деструктор
    Person(const std::string&, const stats_library::ParameterList&,
           const stats_library::SkillList&, const std::vector<short>&,
           const std::vector<short>&, const std::vector<short>&);
    ~Person() = default;
    Person(const Person&);
    Person& operator=(const Person& another);
    // для базы данных
    Person() = default;
    Person(std::string);
    std::string toString() const;
  protected:
      stats_library::ParameterList parameters_;
      stats_library::SkillList skills_;
      PrefixVector att_prob_; // вероятности атак
      PrefixVector def_prob_; // вероятности защит
      PrefixVector tool_prob_; // вероятности рычагов

      static const int att_count_ = 6;
      static const int def_count_ = 2;
      static const int tool_count_ = 4;
  };

}

