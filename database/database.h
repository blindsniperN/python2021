#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H


namespace database {

template<typename T>
class IDataBase {
  public:
    inline  IDataBase(const std::string & name);

    inline virtual void add(const T & ) = 0;

    inline virtual void del(const std::string & ) = 0;

    inline virtual T get(const std::string & ) const = 0;

    inline virtual std::vector<T> listAll() const = 0;

    virtual  ~IDataBase() = 0;


  protected:
    // имя БД (в нашей нужно для названия файла)
    std::string name_;

};
template<typename T>
inline  IDataBase<T>::IDataBase(const std::string & name) {
}


} // namespace database
#endif
