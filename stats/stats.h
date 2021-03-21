#pragma once

namespace stats_library {

  class Parameter { // отвечает за один параметр из четырёх
   public:
    short value_ = 0; // значения от 0 до 10, распределение до игры

    Parameter() = default;
    ~Parameter() = default;
  };

  class ParameterList { // отвечает за все параметры юнита (шанели)
   public:
    Parameter charm_; // обаяние
    Parameter cunning_; // хитрость
    Parameter intelligence_; // интеллект
    Parameter will_; // воля

    Parameter max_determination_; // максимальное значение хп

    ParameterList() = default;
    ParameterList(const short*);
    ~ParameterList() = default;

    void UpdateMaxDetermination(); // обновить макс. значение хп по формуле
  };

  class Skill { // навык
   public:
    short value_ = 0; // значение от 0 до 10, распределение на старте игры
    short modifier_ = 0; // кумулятивный модификатор от атак
    Parameter& parameter_; // параметр, от которого зависит навык
    
    short Roll() { return value_ + modifier_ + parameter_.value_; }
    Skill(Parameter& p): parameter_(p) {}
    Skill(Parameter& p, short x): parameter_(p), value_(x) {}
    ~Skill() = default;
  };

  class SkillList {
   public:
    // интеллект
    Skill etiquette_; // этикет
    Skill people_understand_; // понимание людей
    // хитрость
    Skill deception_; // обман
    Skill gambling_; // азартные игры
    Skill leadership_;
    // обаяние
    Skill charisma_;
    Skill persuasion_; // убеждение
    Skill seduction_;
    // воля
    Skill intimidation_; // запугивание
    Skill persuasion_resist_; // сопротивление убеждению

    SkillList(ParameterList&);
    SkillList(ParameterList&, const short*);
    ~SkillList() = default;
  };
}

