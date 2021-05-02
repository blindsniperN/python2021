#pragma once
#include <exception>

class TooManyPeopleException: public std::exception {}; // исключение бросаемое при переполнении команды
class NotFound: public std::exception {}; // исключение бросаемое в случае отсутствия объекта
class AlreadyExists: public std::exception {}; // вставка уже существующего элемента

class InvalidIDException: public std::exception {}; // сломался level, беды с id