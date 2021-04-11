#pragma once
#include <exception>

class TooManyPeopleException: public std::exception {}; // исключение бросаемое при переполнении команды
class NotFound: public std::exception {}; // исключение бросаемое в случае отсутствия объекта
