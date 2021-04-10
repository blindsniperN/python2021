#pragma once
#include "person.h"
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
    ans.to_hit = 1 + rand() % kHitDice + skills_.seduction_.Roll()
            + love_modifier_;
    ans.dmg = 1 + rand() % kSeduceDmgDice + parameters_.charm_.value_;
    return ans;
  }

  DiceRoll Person::MakeAnArgument() {
    DiceRoll ans;
    ans.to_hit = 1 + rand() % kHitDice + skills_.leadership_.Roll()
            + love_modifier_;
    ans.dmg = 1 + rand() % kArgumentDmgDice + parameters_.charm_.value_;
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
    ans.dmg = 1 + rand() % kDeceiveDmgDice + parameters_.intelligence_.value_;
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
         const std::vector<int>& att = std::vector<int> (kAttackAmount, 1),
         const std::vector<int>& def = std::vector<int> (kDefenseAmount, 1),
         const std::vector<int>& tool = std::vector<int> (kToolAmount, 1)):
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
}
