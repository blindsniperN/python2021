#pragma once
#include "person.h"
#include "../stats/stats.cpp"
#include <string>
#include <vector>

namespace pers_class
{

  // атаки

  DiceRoll Person::Seduce() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % 10 + skills_.seduction_.parameter_.value_ +
                 skills_.seduction_.modifier_ + skills_.seduction_.value_;
    ans.dmg = 1 + rand() % 6 + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::MakeAnArgument() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % 10 + skills_.leadership_.parameter_.value_ +
                 skills_.leadership_.value_ + skills_.leadership_.modifier_;
    ans.dmg = 1 + rand() % 10 + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::Intimidate() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.intimidation_.parameter_.value_ +
                  skills_.intimidation_.value_ + skills_.intimidation_.modifier_;
    ans.dmg = 1 + rand() % 10 + parameters_.will_.value_;
    return ans;
  }

  DiceRoll Person::Deceive() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.deception_.parameter_.value_ +
                  skills_.deception_.value_ + skills_.deception_.modifier_;
    ans.dmg = 1 + rand() % 6 + parameters_.intelligence_.value_;
    return ans;
  }

  DiceRoll Person::Mock() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.etiquette_.parameter_.value_ +
                  skills_.etiquette_.value_ + skills_.etiquette_.modifier_;
    ans.dmg = 1 + rand() % 6 + parameters_.will_.value_;
    return ans;
  }

  // защиты

  DiceRoll Person::Ignore() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.persuasion_resist_.parameter_.value_
            + skills_.persuasion_resist_.value_ + skills_.persuasion_resist_.modifier_;
    ans.dmg = 1 + rand() % 10 + parameters_.will_.value_;
    return ans;
  }

  DiceRoll Person::ChangeTheme() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.persuasion_.parameter_.value_ +
                  skills_.persuasion_.value_ + skills_.persuasion_.modifier_;
    ans.dmg = 1 + rand() % 6 + parameters_.intelligence_.value_;
    return ans;
  }

  // рычаги

  short Person::Love() {
    return 1 + rand() % 10 + skills_.charisma_.value_ +
           skills_.charisma_.modifier_ + skills_.charisma_.parameter_.value_;
  }

  short Person::Research() {
    return 1 + rand() % 10 + skills_.people_understand_.value_ +
           skills_.people_understand_.modifier_ +
           skills_.people_understand_.parameter_.value_;
  }

  short Person::Hint() {
    return 1 + rand() % 10 + skills_.deception_.value_ +
           skills_.deception_.modifier_ + skills_.deception_.parameter_.value_;
  }

  short Person::Bribe() {
    return 1 + rand() % 10 + skills_.gambling_.value_ +
           skills_.gambling_.modifier_ + skills_.gambling_.parameter_.value_;
  }

  // конструктор - его точно не кокнет от этого?

  Person::Person(const std::string& s, const stats_library::ParameterList& p,
         const stats_library::SkillList& skill,
         const std::vector<int>& att = std::vector<int> (6, 1),
         const std::vector<int>& def = std::vector<int> (2, 1),
         const std::vector<int>& tool = std::vector<int> (4, 1)):
         name_(s), parameters_(p), skills_(skill) {
    attack_probability_ = std::vector<int> (6, 0);
    defense_probability_ = std::vector<int> (2, 0);
    tool_probability_ = std::vector<int> (4, 0);

    attack_probability_[0] = att[0];
    for (int i=1; i<6; ++i) {
      attack_probability_[i] = attack_probability_[i-1] + att[i];
    }

    defense_probability_[0] = def[0];
    defense_probability_[1] = def[0] + def[1];

    tool_probability_[0] = tool[0];
    for (int i=1; i<4; ++i) {
      tool_probability_[i] = tool_probability_[i-1] + tool[i];
    }
  }

  // custom атака/защита/рычаг

  int Person::CustomAttack() {
    int roll = rand() % attack_probability_[5];
    for (int i=0; i<6; ++i)
      if (roll < attack_probability_[i])
        return i+1;
  }

  int Person::CustomDefense() {
    int roll = rand() % defense_probability_[1];
    if (roll < defense_probability_[0])
      return 1;
    else
      return 2;
  }

  int Person::CustomTool() {
    int roll = rand() % tool_probability_[3];
    for (int i=0; i<4; ++i)
      if (roll < tool_probability_[i])
        return i+1;
  }
}
