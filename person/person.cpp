#pragma once
#include "person.h"
#include "../stats/stats.cpp"
#include <string>
#include <vector>
namespace pers_class
{
    using namespace stats_library;
  // вспомогательный класс префиксных векторов

  PrefixVector::PrefixVector(const std::vector<short>& ref) {
    a = std::vector<short> (ref.size());
    a[0] = ref[0];
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
         const std::vector<short>& att = std::vector<short> (6, 1),
         const std::vector<short>& def = std::vector<short> (2, 1),
         const std::vector<short>& tool = std::vector<short> (4, 1)):
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

    std::string popFirst(std::string& data) {
        std::string answer = data.substr(0, data.find(';'));
        data = data.substr(data.find(';') + 2, data.size());
        return answer;
    }

//    short* popArray(std::string& data, int length) {
//        short* array = new short[length];
//        for (int i = 0; i < length; ++i) {
//            array[i] = std::stoi(popFirst(data));
//        }
//        return array;
//    }

    std::vector<short> popVector(std::string& data, int length) {
        std::vector<short> array(length);
        for (int i = 0; i < length; ++i) {
            array[i] = std::stoi(popFirst(data));
        }
        return array;
    }
  Person::Person(std::string data):     name_(popFirst(data)), parameters_(popVector(data, ParameterList::parameter_count_)),
                                        skills_(parameters_, popVector(data, SkillList::skill_count_)),
                                        att_prob_(popVector(data, att_count_)), def_prob_(popVector(data, def_count_)),
                                        tool_prob_(popVector(data, tool_count_)) {}

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

  Person& Person::operator=(const Person& another) {
      name_ = another.name_;
      parameters_ = another.parameters_;
      std::vector<short> skills = another.skills_.getSkills();
      skills_ = SkillList(parameters_, skills);
      att_prob_ = another.att_prob_;
      def_prob_ = another.def_prob_;
      tool_prob_ = another.tool_prob_;
      return *this;
  }

  Person::Person(const Person& another):    name_(another.name_), parameters_(another.parameters_),
                                            skills_(parameters_, another.skills_.getSkills()), att_prob_(another.att_prob_),
                                            def_prob_(another.def_prob_), tool_prob_(another.tool_prob_) {}
}

