#pragma once
#include "person.h"
#include "../stats/stats.cpp"
#include <string>
#include <vector>

namespace pers_class
{
  // вспомогательный класс префиксных векторов

  PrefixVector::PrefixVector(const std::vector<int>& ref) {
    a = std::vector<int> (ref.size());
    a[0] = a[0];
    for (int i = 1; i < ref.size(); ++i)
      a[i] = a[i - 1] + ref[i];
  }

  // атаки

  DiceRoll Person::Seduce() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % 10 + skills_.seduction_.Roll();
    ans.dmg = 1 + rand() % 6 + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::MakeAnArgument() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % 10 + skills_.leadership_.Roll();
    ans.dmg = 1 + rand() % 10 + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::Intimidate() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.intimidation_.Roll();
    ans.dmg = 1 + rand() % 10 + parameters_.will_.value_;
    return ans;
  }

  DiceRoll Person::Deceive() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.deception_.Roll();
    ans.dmg = 1 + rand() % 6 + parameters_.intelligence_.value_;
    return ans;
  }

  DiceRoll Person::Mock() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.etiquette_.Roll();
    ans.dmg = 1 + rand() % 6 + parameters_.will_.value_;
    return ans;
  }

  // защиты

  DiceRoll Person::Ignore() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.persuasion_resist_.Roll();
    ans.dmg = 1 + rand() % 10 + parameters_.will_.value_;
    return ans;
  }

  DiceRoll Person::ChangeTheme() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % 10 + skills_.persuasion_.Roll();
    ans.dmg = 1 + rand() % 6 + parameters_.intelligence_.value_;
    return ans;
  }

  // рычаги

  short Person::Love() {
    return 1 + rand() % 10 + skills_.charisma_.Roll();
  }

  short Person::Research() {
    return 1 + rand() % 10 + skills_.people_understand_.Roll();
  }

  short Person::Hint() {
    return 1 + rand() % 10 + skills_.deception_.Roll();
  }

  short Person::Bribe() {
    return 1 + rand() % 10 + skills_.gambling_.Roll();
  }

  // конструктор

  Person::Person(const std::string& s, const stats_library::ParameterList& p,
         const stats_library::SkillList& skill,
         const std::vector<int>& att = std::vector<int> (6, 1),
         const std::vector<int>& def = std::vector<int> (2, 1),
         const std::vector<int>& tool = std::vector<int> (4, 1)):
         name_(s), parameters_(p), skills_(skill), att_prob_(att),
         def_prob_(def), tool_prob_(tool) { }

  // custom атака/защита/рычаг

  int Person::RandomAttack() {
    return att_prob_.Index(rand() % att_prob_.Sum());
  }

  int Person::RandomDefense() {
    return def_prob_.Index(rand() % def_prob_.Sum());
  }

  int Person::RandomTool() {
    return tool_prob_.Index(rand() % tool_prob_.Sum());
  }
}
