#pragma once
#include "../stats/stats.cpp"
#include <string>
#include "game_mechanics.h"
#include <vector>
#include "settings/settings.h"
namespace pers_class
{

  struct DiceRoll { // надо потом перенести в другой файл
    short to_hit = 0; // на попадание
    short dmg = 0; // урон
    DiceRoll() = default;
    ~DiceRoll() = default;
  };

  bool operator < (const DiceRoll &d1, const DiceRoll &d2)
  {
    return (d1.to_hit < d2.to_hit);
  }

  class PrefixVector {
   private:
    std::vector<short> a;
   public:
    int Sum() { return a.back(); }
    int Index(int roll) { return lower_bound(a.begin(), a.end(), roll)
                                 - a.begin(); }
    PrefixVector(const std::vector<short>&);
    PrefixVector() = default;
    ~PrefixVector() = default;
    std::string toString() const;
  };


  class PersonContainer {
   public:
      std::string getName() const { return name_; };
      void setName(const std::string& name) { name_ = name; }
    // конструктор / деструктор
    PersonContainer(const std::string&, const stats_library::ParameterList&,
           const stats_library::SkillList&, const std::vector<short>&,
           const std::vector<short>&, const std::vector<short>&);
    ~PersonContainer() = default;
    // конструктор / деструктор

    PersonContainer(const PersonContainer&);
    PersonContainer& operator=(const PersonContainer& another);
    // для базы данных
    PersonContainer() = default;
    PersonContainer(std::string);
    std::string toString() const;

  protected:
      std::string name_;
      stats_library::ParameterList parameters_;
      stats_library::SkillList skills_;
      PrefixVector att_prob_; // вероятности атак
      PrefixVector def_prob_; // вероятности защит
      PrefixVector tool_prob_; // вероятности рычагов

      template<bool IsProtagonist>
      friend void Settings::UpdatePerson();

      friend void Settings::showData(const PersonContainer&);
  };

  class Person: public PersonContainer {
   private:
    short health_ = 0; // поля для накапливающегося урона
    short seduce_dmg_ = 0;
    short emp_dmg_ = 0; // кумулятивный эффект на кумулятивные атаки
    short deceive_to_hit_ = 0;
    short mock_to_hit_ = 0;
    short love_modifier_ = 0;
   public:
    short& HP() { return health_; }

    // атаки
    DiceRoll Seduce(); // соблазнить
    DiceRoll MakeAnArgument(); // привести довод
    DiceRoll Convince(); // убедить
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

    // конструктор
    Person(const std::string& s, const stats_library::ParameterList& p,
           const stats_library::SkillList& skill,
           const std::vector<short>& att = std::vector<short> (kAttackAmount, 1),
           const std::vector<short>& def = std::vector<short> (kDefenseAmount, 1),
           const std::vector<short>& tool = std::vector<short> (kToolAmount, 1)):
           PersonContainer(s, p, skill, att, def, tool),
           health_(parameters_.max_determination_.value_) { }
    Person(const PersonContainer& base): PersonContainer(base), health_(parameters_.max_determination_.value_) {};
    Person() = default; // для пустой команды
    // применение эффектов атак
    void applySeduce(short); // эффект для защищающегося
    void applyArgument(short); // привести довод
    void applyConvinceDefenser(short); // убеждение по защищаемуся
    void applyConvinceAttacker(short); // убеждение по атакующему
    void applyDeceiveDefenser(short); // обмануть защищающийся
    void applyDeceiveAttacker(); // обмануть атакующий
    void applyMockDefenser(short); // насмехнуться по защищаемуся
    void applyMockAttacker(short); // насмехнуться по защищаемуся
    // защиты
    void applyIgnore(short); // игнорировать
    void applyChangeTheme(short); // смена темы
    // рычаги
    void applyLove(); // любовь
    void applyResearch(); // изучить
    /*
    void applyHint(); // намёк
    void applyBribe(); // подкуп
     */
  };


  void substractHealth(short& hp, short dmg) {
    if (dmg < hp)
      hp -= dmg;
    else
      hp = 0;
  }

}

