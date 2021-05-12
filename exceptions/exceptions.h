#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H


typedef std::exception typedef1;
class TooManyPeopleException : public typedef1 {
};
// исключение бросаемое при переполнении команды
class NotFound : public typedef1 {
};
// исключение бросаемое в случае отсутствия объекта
class AlreadyExists : public typedef1 {
};
// вставка уже существующего элемента
class InvalidIDException : public typedef1 {
};
#endif
