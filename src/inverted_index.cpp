#include "inverted_index.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

InvertedIndex::InvertedIndex() {
  initialize_common_words();
}

void InvertedIndex::initialize_common_words() {
  common_words = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};
}

std::string InvertedIndex::process_word(const std::string& word) {
  std::string processed;

  for (char c : word) {
    if (std::isalnum(c) || c == '-') {
      processed += std::tolower(c);
    }
  }

  return processed;
}

bool InvertedIndex::is_common_word(const std::string& word) {
  return common_words.find(word) != common_words.end();
}

void InvertedIndex::build_from_file(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  std::string word;
  int position = 0;

  while (file >> word) {
    std::string processed = process_word(word);

    if (!processed.empty() && !is_common_word(processed)) {
      index[processed].push_back(position);
    }

    position++;
  }

  file.close();
}

void InvertedIndex::write_to_file(const std::string& filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Could not create file " << filename << std::endl;
    return;
  }

  for (const auto& [word, positions] : index) {
    file << word << ": ";

    for (size_t i = 0; i < positions.size(); ++i) {
      file << positions[i];
      if (i < positions.size() - 1) {
        file << ", ";
      }
    }

    file << std::endl;
  }

  file.close();
}
