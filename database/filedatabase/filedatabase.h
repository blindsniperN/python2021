#ifndef _FILEDATABASE_H
#define _FILEDATABASE_H


#include "database.h"

template<typename T>
class FileDataBase : public database::IDataBase<T> {
  public:
     FileDataBase(const std::string & name);

    void add(const T & item) override;

    void del(const std::string & name) override;

    T get(const std::string & name) const override;

    std::vector<T> listAll() const override;

     ~FileDataBase() override;


  private:
    std::string, T items;

};
#endif
