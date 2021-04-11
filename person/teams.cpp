#pragma once
#include "person.h"
#include "../stats/stats.cpp"
#include <string>
#include <vector>
#include "teams.h"
#include <algorithm>
#include <random>
#include "../exceptions/exceptions.h"
#include <iostream>
namespace teams
{

    Team::Team(int max_size, const std::vector<Person>& people = std::vector<Person>(0)): members_(people), size_(people.size()), max_size_(max_size) {
        if (members_.size() > max_size_) {
            members_.resize(max_size_);
            size_ = max_size_;
            shuffle();
            throw TooManyPeopleException();
        }
        shuffle();
    }

    void Team::createTeam() { return; }

    void Team::shuffle() {
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(members_), std::end(members_), rng);
    }

    void Team::add(Person person) {
        if (size_ < max_size_) {
            auto it = members_.begin() + ((size_ != 0) ? rand() % size_ : 0); // Todo мб поставить другой рандом
            members_.insert(it, person);
            ++size_;
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
        throw NotFound();
    }
}

