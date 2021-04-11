#pragma once
#include "stats.h"

namespace stats_library {

  ParameterList::ParameterList(const std::vector<short>& arr) {
    charm_.value_ = arr[0];
    cunning_.value_ = arr[1];
    intelligence_.value_ = arr[2];
    will_.value_ = arr[3];
  }

  std::string ParameterList::toString() const {
      std::string answer;
      answer = std::to_string(charm_.value_) + "; " + std::to_string(cunning_.value_) + "; "
              + std::to_string(intelligence_.value_) + "; " + std::to_string(will_.value_);
      return answer;
  }

  void ParameterList::UpdateMaxDetermination() {
    max_determination_.value_ = (will_.value_ + intelligence_.value_)*5/2;
  }

  SkillList::SkillList(ParameterList& p):
    etiquette_(p.intelligence_), people_understand_(p.intelligence_),
    deception_(p.cunning_), gambling_(p.cunning_), leadership_(p.cunning_),
    charisma_(p.charm_), persuasion_(p.charm_), seduction_(p.charm_),
    intimidation_(p.will_), persuasion_resist_(p.will_) {}

  SkillList::SkillList(ParameterList& p, const std::vector<short>& arr):
          etiquette_(p.intelligence_, arr[0]),
          people_understand_(p.intelligence_, arr[1]),
          deception_(p.cunning_, arr[2]),
          gambling_(p.cunning_, arr[3]),
          leadership_(p.cunning_, arr[4]),
          charisma_(p.charm_, arr[5]), persuasion_(p.charm_, arr[6]),
          seduction_(p.charm_, arr[7]),
          intimidation_(p.will_, arr[8]),
          persuasion_resist_(p.will_, arr[9]) {}
  std::string SkillList::toString() const {
      std::string answer;
      answer = std::to_string(etiquette_.value_) + "; " + std::to_string(people_understand_.value_) + "; " +
              std::to_string(deception_.value_) + "; " + std::to_string(gambling_.value_) + "; " + std::to_string(leadership_.value_) + "; " +
              std::to_string(charisma_.value_) + "; " + std::to_string(persuasion_.value_) + "; " + std::to_string(seduction_.value_) + "; " +
              std::to_string(intimidation_.value_) + "; " + std::to_string(persuasion_resist_.value_);
      return answer;
  }

  std::vector<short> SkillList::getSkills() const {
      std::vector<short> array(skill_count_);
      array[0] = etiquette_.value_;
      array[1] = people_understand_.value_;
      array[2] = deception_.value_;
      array[3] = gambling_.value_;
      array[4] = leadership_.value_;
      array[5] = charisma_.value_;
      array[6] = persuasion_.value_;
      array[7] = seduction_.value_;
      array[8] = intimidation_.value_;
      array[9] = persuasion_resist_.value_;
      return array;
  }
}

