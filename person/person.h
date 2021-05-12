#ifndef PERS_CLASS_PERSON_H
#define PERS_CLASS_PERSON_H


#include "stats.h"

namespace pers_class {

struct DiceRoll {
    // надо потом перенести в другой файл
    // на попадание
    short to_hit=  0;

    // урон
    short dmg=  0;

     DiceRoll() = default;

     ~DiceRoll() = default;

};
class PrefixVector {
  private:
    short a;


  public:
    inline int Sum();

    inline int Index(int roll);

     PrefixVector(const std::vector<short> & ref);

     PrefixVector() = default;

     ~PrefixVector() = default;

    std::string toString() const;

};
inline int PrefixVector::Sum() {
}

inline int PrefixVector::Index(int roll) {
}

class PersonContainer {
  public:
    inline std::string getName() const;

    inline void setName(const std::string & name);

    // конструктор / деструктор
     PersonContainer(const std::string & s, const stats_library::ParameterList & p, const stats_library::SkillList & skill, const std::vector<short> & att, const std::vector<short> & def, const std::vector<short> & tool);

     ~PersonContainer() = default;

    // конструктор / деструктор
     PersonContainer(const PersonContainer & another);

    PersonContainer operator =(const PersonContainer & another);

    // для базы данных
     PersonContainer() = default;

     PersonContainer(const std::string & data);

    std::string toString() const;


  protected:
    std::string name_;

    stats_library::ParameterList parameters_;

    stats_library::SkillList skills_;

    // вероятности атак
    PrefixVector att_prob_;

    // вероятности защит
    PrefixVector def_prob_;

    // вероятности рычагов
    PrefixVector tool_prob_;

    template<bool IsProtagonist>
    friend void Settings::UpdatePerson();

    friend void Settings::showData(const PersonContainer & );

};
inline std::string PersonContainer::getName() const {
}

inline void PersonContainer::setName(const std::string & name) {
}

class Person : public PersonContainer {
  private:
    // поля для накапливающегося урона
    short health_=  0;

    short seduce_dmg_=  0;

    // кумулятивный эффект на кумулятивные атаки
    short emp_dmg_=  0;

    short deceive_to_hit_=  0;

    short mock_to_hit_=  0;

    short love_modifier_=  0;


  public:
    inline short HP();

    // атаки
    DiceRoll Seduce();

    // соблазнить
    DiceRoll MakeAnArgument();

    // привести довод
    DiceRoll Convince();

    // убедить
    DiceRoll Deceive();

    // обмануть
    DiceRoll Mock();

    // насмехнуться
    // защиты
    DiceRoll Ignore();

    // игнорировать
    DiceRoll ChangeTheme();

    // смена темы
    // рычаги
    short Love();

    // любовь
    short Research();

    // изучить
    short Hint();

    // намёк
    short Bribe();

    // подкуп
    // атака для ИИ, для игрока - случайная атака
    int RandomAttack();

    int RandomDefense();

    int RandomTool();

    // атака по вводу
    DiceRoll ActionFromInput(int & id, const std::string & s);

    // конструктор
    inline  Person(const std::string & s, const stats_library::ParameterList & p, const stats_library::SkillList & skill, const std::vector<short> & att = std::vector<short> (kAttackAmount, 1), const std::vector<short> & def = std::vector<short> (kDefenseAmount, 1), const std::vector<short> & tool = std::vector<short> (kToolAmount, 1));

    inline  Person(const PersonContainer & base);

     Person() = default;

    // для пустой команды
    // применение эффектов атак
    void applySeduce(short dmg);

    // эффект для защищающегося
    void applyArgument(short dmg);

    // привести довод
    void applyConvinceDefenser(short dmg);

    // убеждение по защищаемуся
    void applyConvinceAttacker(short dmg);

    // убеждение по атакующему
    void applyDeceiveDefenser(short dmg);

    // обмануть защищающийся
    void applyDeceiveAttacker();

    // обмануть атакующий
    void applyMockDefenser(short dmg);

    // насмехнуться по защищаемуся
    void applyMockAttacker(short dmg);

    // насмехнуться по защищаемуся
    // защиты
    void applyIgnore(short dmg);

    // игнорировать
    void applyChangeTheme(short dmg);

    // смена темы
    // рычаги
    void applyLove();

    // любовь
    void applyResearch();

};
inline short Person::HP() {
}

// конструктор
inline  Person::Person(const std::string & s, const stats_library::ParameterList & p, const stats_library::SkillList & skill, const std::vector<short> & att, const std::vector<short> & def, const std::vector<short> & tool) {
}

inline  Person::Person(const PersonContainer & base) {
}


} // namespace pers_class
#endif
