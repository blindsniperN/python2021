#ifndef STATS_LIBRARY_STATS_H
#define STATS_LIBRARY_STATS_H


namespace stats_library {

class Parameter {
  public:
    // отвечает за один параметр из четырёх
    // значения от 0 до 10, распределение до игры
    short value_=  0;

     Parameter() = default;

     ~Parameter() = default;

};
class ParameterList {
  public:
    // отвечает за все параметры юнита (шанели)
    // обаяние
    Parameter charm_;

    // хитрость
    Parameter cunning_;

    // интеллект
    Parameter intelligence_;

    // воля
    Parameter will_;

    // максимальное значение хп
    Parameter max_determination_;

    static const short parameter_count_;

     ParameterList() = default;

     ParameterList(const std::vector<short> & arr);

     ~ParameterList() = default;

    void UpdateMaxDetermination();

    // обновить макс. значение хп по формуле
    std::string toString() const;

};
class Skill {
  public:
    // навык
    // значение от 0 до 10, распределение на старте игры
    short value_=  0;

    // кумулятивный модификатор от атак
    short modifier_=  0;

    // параметр, от которого зависит навык
    Parameter * parameter_=  nullptr;

    inline short Roll();

     Skill() = default;

    inline  Skill(Parameter & p);

    inline  Skill(Parameter & p, short x);

     ~Skill() = default;

};
inline short Skill::Roll() {
}

inline  Skill::Skill(Parameter & p) {
}

inline  Skill::Skill(Parameter & p, short x) {
}

class SkillList {
  public:
    // интеллект
    // этикет
    Skill etiquette_;

    // понимание людей
    Skill people_understand_;

    // хитрость
    // обман
    Skill deception_;

    // азартные игры
    Skill gambling_;

    Skill leadership_;

    // обаяние
    
    Skill charisma_;

    // убеждение
    Skill persuasion_;

    Skill seduction_;

    // воля
    // запугивание
    Skill intimidation_;

    // сопротивление убеждению
    Skill persuasion_resist_;

    static const short skill_count_;

     SkillList() = default;

     SkillList(ParameterList & p);

     SkillList(ParameterList & p, const std::vector<short> & arr);

     ~SkillList() = default;

    std::string toString() const;

    std::vector<short> getSkills() const;

};

} // namespace stats_library
#endif
