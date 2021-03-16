#pragma once
#include <vector>
#include <string>
#include "../stats/stats.h"
#include "person.h"

class Factory {
public:
    Factory(const std::string& name,
                    const stats_library::ParameterList& parameters,
                    const stats_library::SkillList& skills,
                    const std::vector<int>& att = std::vector<int> (6, 1),
                    const std::vector<int>& def = std::vector<int> (2, 1),
                    const std::vector<int>& tool = std::vector<int> (4, 1)):
                    name_(name), parameters_(parameters), skills_(skills), attack_(att), defense_(def), tools_(tool) {}
    Person createPerson() const {
        return Person(name_, parameters_, skills_, attack_, defense_, tools_);
    };

protected:
    std::string name_;
    stats_library::ParameterList parameters_;
    stats_library::SkillList skills_;
    std::vector<int> attack_;
    std::vector<int> defense_;
    std::vector<int> tools_;
};



