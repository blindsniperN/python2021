#pragma once
#include <string>
namespace database {
    template <typename T>
    class IDataBase {
    public:
        IDataBase(const std::string& name): name_(name) {}
        virtual void add(const T&) = 0;
        virtual void del(const T&) = 0;
        virtual T get(const std::string&) = 0;
        virtual ~IDataBase() = 0;

    protected:
        std::string name_;
    };
}
