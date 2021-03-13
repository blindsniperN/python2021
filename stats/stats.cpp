#include "stats.h"

namespace stats_library {

  void ParameterList::UpdateMaxDetermination() {
    max_determination_.value_ = (will_.value_ + intelligence_.value_)*5/2;
  }

  SkillList::SkillList(ParameterList& p):
    etiquette_(p.intelligence_), people_understand_(p.intelligence_),
    deception_(p.cunning_), gambling_(p.cunning_), leadership_(p.cunning_),
    charisma_(p.charm_), persuasion_(p.charm_), seduction_(p.charm_),
    intimidation_(p.will_), persuasion_resist_(p.will_) {};

}
