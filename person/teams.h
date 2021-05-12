#ifndef TEAMS_TEAMS_H
#define TEAMS_TEAMS_H


#include "person.h"

namespace database { template<typename T> class IDataBase; } 
namespace pers_class { class PersonContainer; } 

namespace teams {

class Team {
  public:
     Team(int max_size, const std::vector<Person> & people);

    void add(const pers_class::Person & person);

    pers_class::Person get();

    pers_class::Person getRandom();

    //        void apply(object)
    pers_class::Person find(const std::string & name);

    void del(const std::string & name);

    void updateMaxSize(int new_max_size);

    inline size_t size() const;

    static Team FormTeam(int max_size, const IDataBase<PersonContainer> & protagonists_db);


  private:
    pers_class::Person members_;

    int max_size_;

    int size_=  0;

    int current_attacker_=  0;

    void createTeam();

    void shuffle();

};
inline size_t Team::size() const {
}


} // namespace teams
#endif
