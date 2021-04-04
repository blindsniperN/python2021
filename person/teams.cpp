#pragma once
#include "person.h"
#include "../stats/stats.cpp"
#include <string>
#include <vector>
#include "teams.h"
#include <algorithm>
#include <random>
#include <exception>

namespace teams
{
    class TooManyPeopleException: public std::exception {}; // исключение бросаемое при переполнении команды
    class PersonNotFound: public std::exception {};

    Team::Team(const std::vector<Person>& people): members_(people), size_(people.size()) {
        if (members_.size() > max_size_) {
            members_.resize(max_size_);
            size_ = max_size_;
            shuffle();
            throw TooManyPeopleException();
        }
        shuffle();
    }

    template<typename... Args>
    void Team::createTeam(Person person, Args... args) {
        if (size_ < max_size_) {
            add(person);
            createTeam(args...);
        } else {
            throw TooManyPeopleException();
        }
    }

    void Team::shuffle() {
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(members_), std::end(members_), rng);
    }

    void Team::add(Person person) {
        if (size_ < max_size_) {
            members_.push_back(person);
            ++size_;
            shuffle();
        } else {
            throw TooManyPeopleException();
        }
    }

    Person Team::get() {
        int index = current_attacker_;
        current_attacker_ = (current_attacker_ + 1) % size_;
        return members_[index];
    }

    Person Team::find(const std::string& name) {
        for (Person p: members_) {
            if (p.name_ == name) return p;
        }
        throw PersonNotFound();
    }
}

