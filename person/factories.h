#pragma once
#include <vector>
#include <string>
#include "../stats/stats.h"
#include "person.h"

class Factory {
public:
    pers_class::PersonContainer createPerson(const std::string& name,
    const stats_library::ParameterList& parameters,
    const stats_library::SkillList& skills,

    const std::vector<short>& attack = std::vector<short> (6, 1),
    const std::vector<short>& defense = std::vector<short> (2, 1),
    const std::vector<short>& tools = std::vector<short> (4, 1)) const {
        return pers_class::PersonContainer(name, parameters, skills, attack, defense, tools);
    };
};




