
#include "teams.h"
#include "database.h"

namespace teams {

 Team::Team(int max_size, const std::vector<Person> & people) {

        if (members_.size() > max_size_) {
            members_.resize(max_size_);
            size_ = max_size_;
            shuffle();
            throw TooManyPeopleException();
        }
        shuffle();
}

void Team::add(const pers_class::Person & person) {

        //srand(std::time(0));
        if (size_ < max_size_) {
            auto it = members_.begin() + ((size_ != 0) ? rand() % (size_ + 1) : 0); // Todo мб поставить другой рандом
            members_.insert(it, person);
            ++size_;
        } else {
            throw TooManyPeopleException();
        }
}

pers_class::Person Team::get() {

        int index = current_attacker_;
        current_attacker_ = (current_attacker_ + 1) % size_;
        return members_[index];
}

pers_class::Person Team::getRandom() {

        int index = rand() % size_;
        return members_[index];
}

//        void apply(object)
pers_class::Person Team::find(const std::string & name) {

        for (Person& p: members_) {
            if (p.getName() == name) return p;
        }
        throw NotFound();
}

void Team::del(const std::string & name) {

        for (auto it = members_.begin(); it != members_.end(); ++it) {
            if (it->getName() == name) {
                members_.erase(it);
                --size_;
                return;
            }
        }
        throw NotFound();
}

void Team::updateMaxSize(int new_max_size) {

        max_size_ = new_max_size;
        if (size_ > max_size_) {
            size_ = max_size_;
            members_.resize(size_);
        }
}

Team Team::FormTeam(int max_size, const IDataBase<PersonContainer> & protagonists_db)
{

        Team new_team(max_size);
        std::cout << "Now you need to form a team! Due to the chosen difficulty, its maximum size shouldn't exceed " << max_size << " characters\n";
        std::cout << "Select characters from the following list (they shouldn't dublicate)\n";
        std::vector<PersonContainer> protagonists = protagonists_db->listAll();
        print(protagonists);
        std::cout << "What size do you want your team be?\n";
        int size;
        std::cin >> size;
        size = std::min(size, max_size);
        std::cout << "No enter character's names\n";
        for (int i = 0; i < size; ++i) {
            std::string name;
            std::cin >> name;
            try {
                new_team.add(protagonists_db->get(name));
            } catch (NotFound) {
                std::cout << "Oops... There are no such characters. Please try again.";
                --i;
            }
        }
        return new_team;
}

void Team::createTeam() {
 return;
}

void Team::shuffle() {

        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(members_), std::end(members_), rng);
}


} // namespace teams
