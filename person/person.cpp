#pragma once
#include "person.h"
#include "../stats/stats.cpp"
#include <string>
#include <vector>

namespace pers_class
{
    using namespace stats_library;
  // вспомогательный класс префиксных векторов

  PrefixVector::PrefixVector(const std::vector<int>& ref) {
    a = std::vector<int> (ref.size());
    a[0] = a[0];
    for (int i = 1; i < ref.size(); ++i)
      a[i] = a[i - 1] + ref[i];
  }

  std::string PrefixVector::toString() const {
      std::string answer;
      answer += std::to_string(a[0]);
      for (int i = 1; i < a.size(); ++i) {
          answer += "; " + std::to_string(a[i] - a[i - 1]);
      }
      return answer;
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

    std::string& popFirst(std::string& data) {
        std::string answer = data.substr(0, data.find(';'));
        data = data.substr(data.find(';'), data.size() - 1);
        return answer;
    }

  Person::Person(std::string data) {
      name_ = popFirst(data);
      short* parameters = new short[ParameterList::parameter_count_];
      for (int i = 0; i < ParameterList::parameter_count_; ++i) {
          parameters[i] = std::stoi(popFirst(data));
      }
      parameters_ = ParameterList(parameters);
      short* skills = new short[SkillList::skill_count_];
      for (int i = 0; i < SkillList::skill_count_; ++i) {
          parameters[i] = std::stoi(popFirst(data));
      }
      skills_ = SkillList(parameters_, skills);

      std::vector<int> att;
      for (int i = 0; i < att_count_; ++i) {
          att.push_back(std::stoi(popFirst(data)));
      }
      att_prob_ = PrefixVector(att);

      std::vector<int> def;
      for (int i = 0; i < def_count_; ++i) {
          def.push_back(std::stoi(popFirst(data)));
      }
      def_prob_ = PrefixVector(def);

      std::vector<int> tools;
      for (int i = 0; i < tool_count_; ++i) {
          tools.push_back(std::stoi(popFirst(data)));
      }
      tool_prob_ = PrefixVector(tools);
  }

  std::string Person::toString() const {
      std::string answer;
      answer += name_ + "; ";
      answer += parameters_.toString() + "; ";
      answer += skills_.toString() + "; ";
      answer += att_prob_.toString() + "; ";
      answer += def_prob_.toString() + "; ";
      answer += tool_prob_.toString() + "; ";
      return answer;
  }
}
