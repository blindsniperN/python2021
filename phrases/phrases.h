#ifndef _PHRASES_H
#define _PHRASES_H


class Phrases {
  protected:
    std::string data_;


  public:
     Phrases() = default;

    inline  Phrases(const std::vector<std::string> & x);

     ~Phrases() = default;

    inline void add(const std::string & s);

    inline void del(const std::string & s);

    inline std::string generate();

};
inline  Phrases::Phrases(const std::vector<std::string> & x) {
}

inline void Phrases::add(const std::string & s) {
}

inline void Phrases::del(const std::string & s) {
}

inline std::string Phrases::generate() {
}

#endif
