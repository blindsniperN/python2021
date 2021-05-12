#ifndef _FACTORIES_H
#define _FACTORIES_H


namespace pers_class { class PersonContainer; } 
namespace stats_library { class ParameterList; } 
namespace stats_library { class SkillList; } 

class Factory {
  public:
    inline pers_class::PersonContainer createPerson(const std::string & name, const stats_library::ParameterList & parameters, const stats_library::SkillList & skills, const std::vector<short> & attack = std::vector<short> (6, 1), const std::vector<short> & defense = std::vector<short> (2, 1), const std::vector<short> & tools = std::vector<short> (4, 1)) const;

};
inline pers_class::PersonContainer Factory::createPerson(const std::string & name, const stats_library::ParameterList & parameters, const stats_library::SkillList & skills, const std::vector<short> & attack, const std::vector<short> & defense, const std::vector<short> & tools) const {
}

#endif
