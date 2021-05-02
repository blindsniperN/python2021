#include "stats.h"

namespace stats_library {

  ParameterList::ParameterList(const short* arr) {
    charm_.value_ = arr[0];
    cunning_.value_ = arr[1];
    intelligence_.value_ = arr[2];
    will_.value_ = arr[3];
  }

  void ParameterList::UpdateMaxDetermination() {
    max_determination_.value_ = (will_.value_ + intelligence_.value_)*5/2;
  }

  SkillList::SkillList(ParameterList& p):
    etiquette_(p.intelligence_), people_understand_(p.intelligence_),
    deception_(p.cunning_), gambling_(p.cunning_), leadership_(p.cunning_),
    charisma_(p.charm_), persuasion_(p.charm_), seduction_(p.charm_),
    intimidation_(p.will_), persuasion_resist_(p.will_) {}

  SkillList::SkillList(ParameterList& p, const short* arr):
          etiquette_(p.intelligence_, arr[0]),
          people_understand_(p.intelligence_, arr[1]),
          deception_(p.cunning_, arr[2]),
          gambling_(p.cunning_, arr[3]),
          leadership_(p.cunning_, arr[4]),
          charisma_(p.charm_, arr[5]), persuasion_(p.charm_, arr[6]),
          seduction_(p.charm_, arr[7]),
          intimidation_(p.will_, arr[8]),
          persuasion_resist_(p.will_, arr[9]) {}

}

