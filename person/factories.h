//
// Created by Savichev Dmitrii on 14.03.2021.
//

#ifndef PERSON_FACTORIES_H
#define PERSON_FACTORIES_H
#include "person.cpp"
#ifndef STATS_H
    #include "../stats/stats.cpp"
#endif

class AbstractFactory {
public:
    virtual Person createPerson(const std::string& name, const stats_library::ParameterList& parameters, const stats_library::SkillList& skills) const = 0;
};

class ProtagonistFactory: public AbstractFactory {
    Person createPerson(const std::string& name, const stats_library::ParameterList& parameters, const stats_library::SkillList& skills) const override {
        return Protagonist(name, parameters, skills);
    }
};

class AntagonistFactory: public AbstractFactory {
    Person createPerson(const std::string& name, const stats_library::ParameterList& parameters, const stats_library::SkillList& skills) const override {
        return Antagonist(name, parameters, skills);
    }
};

#endif //PERSON_FACTORIES_H
