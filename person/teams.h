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
//        void apply(object)
        Person find(const std::string&);
        void del(const std::string&);
        size_t size() { return size_; }
        void updateMaxSize(int);
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