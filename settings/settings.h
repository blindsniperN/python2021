#ifndef _SETTINGS_H
#define _SETTINGS_H


#include "database.h"

namespace pers_class { class PersonContainer; } 

class Settings {
  public:
    static void Start();

    static IDataBase<PersonContainer> * protagonists_;

    static IDataBase<PersonContainer> * antagonists_;

    static void showData(const pers_class::PersonContainer & person);


  private:
    template<bool IsProtagonist>
    static void CreatePerson();

    // true - protagonist, false - antagonist
    template<bool IsProtagonist>
    static void UpdatePerson();

    template<bool IsProtagonist>
    static void DeletePerson();

};
#endif
