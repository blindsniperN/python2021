#pragma once
#include "../stats/stats.cpp"
#include "person.h"
#include <string>
#include <vector>
#include <iostream>
namespace teams
{
    using namespace pers_class;

    class Team {
    public:
        Team(int, const std::vector<Person>&);
        void add(Person);

        Person get();
        Person getRandom();
//        void apply(object)
        Person find(const std::string&);
        void del(const std::string&);
        void updateMaxSize(int);
        size_t size() const { return size_; }
    private:
        std::vector<Person> members_;
        int max_size_;
        int size_ = 0;
        int current_attacker_ = 0;

        template<typename... Args>
        void createTeam(Person, Args...);
        void createTeam();
        void shuffle();
    };

}