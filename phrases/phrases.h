#pragma once
#include <string>
#include <vector>


class Phrases {
 protected:
  std::vector <std::string> data_;
 public:
  Phrases() = default;
  Phrases(std::vector <std::string> x): data_(std::move(x)) { }
  ~Phrases() = default;

  void add(const std::string& s) { data_.push_back(s); }
  void del(const std::string& s) {
    for (auto i = data_.end() - 1; i >= data_.begin(); --i)
      if (*i == s) {
        data_.erase(i);
    }
  }

  std::string generate() { return data_[rand() % data_.size()]; }
};