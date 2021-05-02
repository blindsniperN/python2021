#pragma once
#include "person.h"
#include <string>
#include <vector>
#include <iostream>
#include "auxiliary/parse_string.h"
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
    ans.to_hit = 1 + rand() % kHitDice + skills_.seduction_.Roll()
            + love_modifier_;
    ans.dmg = 1 + rand() % kSeduceDmgDice + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::MakeAnArgument() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % kHitDice + skills_.leadership_.Roll()
            + love_modifier_;
    ans.dmg = 1 + rand() % kArgumentDmgDice + parameters_.cunning_.value_;
    return ans;
  }

  DiceRoll Person::Convince() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % kHitDice + skills_.persuasion_.Roll()
            + love_modifier_;
    ans.dmg = (1 + rand() % kConvinceDmgDice) / 2 + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::Deceive() {
    DiceRoll ans;
    ans.to_hit = std::max(1 + rand() % kHitDice +
            skills_.deception_.Roll() - deceive_to_hit_ + love_modifier_, 0);
    ans.dmg = 1 + rand() % kDeceiveDmgDice + parameters_.cunning_.value_;
    return ans;
  }

  DiceRoll Person::Mock() {
    DiceRoll ans;
    ans.to_hit = std::max(1 + rand() % kHitDice +
                           skills_.etiquette_.Roll() - mock_to_hit_
                           + love_modifier_, 0);
    ans.dmg = 1 + rand() % kMockDmgDice + parameters_.will_.value_;
    return ans;
  }

  // защиты

  DiceRoll Person::Ignore() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % kHitDice + skills_.persuasion_resist_.Roll();
    ans.dmg = 1 + rand() % kIgnoreDmgDice + parameters_.will_.value_;
    return ans;
  }

  DiceRoll Person::ChangeTheme() {
    DiceRoll ans;
    ans.to_hit =  1 + rand() % kHitDice + skills_.persuasion_.Roll();
    ans.dmg = 1 + rand() % kChangeThemeDmgDice +
            parameters_.intelligence_.value_;
    return ans;
  }

  // рычаги

  short Person::Love() {
    return 1 + rand() % kHitDice + skills_.charisma_.Roll();
  }

  short Person::Research() {
    return 1 + rand() % kHitDice + skills_.people_understand_.Roll();
  }

  short Person::Hint() {
    return 1 + rand() % kHitDice + skills_.deception_.Roll();
  }

  short Person::Bribe() {
    return 1 + rand() % kHitDice + skills_.gambling_.Roll();
  }

  // конструктор

  PersonContainer::PersonContainer(const std::string& s,
                                   const stats_library::ParameterList& p,
         const stats_library::SkillList& skill,

         const std::vector<short>& att = std::vector<short> (kAttackAmount, 1),
         const std::vector<short>& def = std::vector<short> (kDefenseAmount, 1),
         const std::vector<short>& tool = std::vector<short> (kToolAmount, 1)):

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


//    std::string popFirst(std::string& data) {
//        std::string answer = data.substr(0, data.find(';'));
//        data = data.substr(data.find(';') + 2, data.size());
//        return answer;
//    }
//
//
//    std::vector<short> popVector(std::string& data, int length) {
//        std::vector<short> array(length);
//        for (int i = 0; i < length; ++i) {
//            array[i] = std::stoi(popFirst(data));
//        }
//        return array;
//    }
  PersonContainer::PersonContainer(std::string data):     name_(popFirst(data)), parameters_(popVector(data, ParameterList::parameter_count_)),
                                        skills_(parameters_, popVector(data, SkillList::skill_count_)),
                                        att_prob_(popVector(data, kAttackAmount)), def_prob_(popVector(data, kDefenseAmount)),
                                        tool_prob_(popVector(data, kToolAmount)) {}

  std::string PersonContainer::toString() const {
      std::string answer;
      answer += name_ + "; ";
      answer += parameters_.toString() + "; ";
      answer += skills_.toString() + "; ";
      answer += att_prob_.toString() + "; ";
      answer += def_prob_.toString() + "; ";
      answer += tool_prob_.toString() + "; ";
      return answer;
  }

  PersonContainer& PersonContainer::operator=(const PersonContainer& another) {
      name_ = another.name_;
      parameters_ = another.parameters_;
      std::vector<short> skills = another.skills_.getSkills();
      skills_ = SkillList(parameters_, skills);
      att_prob_ = another.att_prob_;
      def_prob_ = another.def_prob_;
      tool_prob_ = another.tool_prob_;
      return *this;
  }

  PersonContainer::PersonContainer(const PersonContainer& another):    name_(another.name_), parameters_(another.parameters_),
                                            skills_(parameters_, another.skills_.getSkills()), att_prob_(another.att_prob_),
                                            def_prob_(another.def_prob_), tool_prob_(another.tool_prob_) {}

  // применение эффектов

  void Person::applySeduce(short dmg) { // соблазнить
    substractHealth(health_, emp_dmg_ + dmg + seduce_dmg_);
    seduce_dmg_ += kSeduceModifier;
  }

  void Person::applyArgument(short dmg) { // привести довод
    substractHealth(health_, emp_dmg_ + dmg);
    emp_dmg_ += kArgumentModifier;
  }

  void Person::applyConvinceDefenser(short dmg) { // убеждение по защищаемуся
    substractHealth(health_, emp_dmg_ + dmg);
  }

  // убеждение по атакующему
  void Person::applyConvinceAttacker(short dmg) { health_ += dmg; }

  void Person::applyDeceiveDefenser(short dmg) {
    substractHealth(health_, dmg);
  } // обмануть защищающийся

  void Person::applyDeceiveAttacker() {
    deceive_to_hit_ += kDeceiveModifier;
    love_modifier_ = 0;
  } // обмануть атакующий

  void Person::applyMockDefenser(short dmg) {
    substractHealth(health_, dmg);
  } // насмехнуться по защищаемуся

  void Person::applyMockAttacker(short dmg) {
    health_ += dmg;
    mock_to_hit_ += kMockModifier;
    love_modifier_ = 0;
  } // насмехнуться для атакующего

  // защиты
  void Person::applyIgnore(short dmg) { // игнорировать
    substractHealth(health_, dmg);
  }

  void Person::applyChangeTheme(short dmg) { // смена темы
    substractHealth(health_, dmg);
  }
  // рычаги
  void Person::applyLove() { love_modifier_ = kLoveModifier; } // любовь

  void Person::applyResearch() { health_ += parameters_.intelligence_.value_; }
  // увеличивает хп
  /*
  void Person::applyHint(); // намёк
  void Person::applyBribe(); // подкуп */

  DiceRoll Person::ActionFromInput(int& id, std::string s) {
    if (s == "seduce") {
      id = kIDSeduce;
      return Seduce();
    } else if (s == "argument") {
      id = kIDArgument;
      return MakeAnArgument();
    } else if (s == "convince") {
      id = kIDConvince;
      return Convince();
    } else if (s == "deceive") {
      id = kIDDeceive;
      return Deceive();
    } else if (s == "mock") {
      id = kIDMock;
      return Mock();
    } else if (s == "ignore") {
      id = kIDIgnore;
      return Ignore();
    } else if (s == "changetheme") {
      id = kIDChangeTheme;
      return ChangeTheme();
    }
  }
}

