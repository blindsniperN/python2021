#pragma once
#include "../stats/stats.cpp"
#include "person.h"
#include <string>
#include <vector>

namespace teams
{
    using namespace pers_class;

    class Team {
    public:
        Team(const std::vector<Person>&);
        void add(Person);

        template<typename... Args>
        Team(Args... args) { createTeam(args...); }
        Person get();
//        void apply(object)
        Person find(const std::string&);
    private:
        std::vector<Person> members_;
        int max_size_;
        int size_ = 0;
        int current_attacker_ = 0;

        template<typename... Args>
        void createTeam(Person, Args...);
        void shuffle();
    };

}