#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

class InvertedIndex {
private:
  std::map<std::string, std::vector<int>> index;
  std::set<std::string> common_words;

  void initialize_common_words();
  std::string process_word(const std::string& word);
  bool is_common_word(const std::string& word);

public:
  InvertedIndex();
  void build_from_file(const std::string& filename);
  void write_to_file(const std::string& filename);
};

#endif
