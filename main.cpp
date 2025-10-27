#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include "src/inverted_index.hpp"

std::string generate_random_filename() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 15);
  
  std::stringstream ss;
  ss << "inverted_index_";
  for (int i = 0; i < 8; ++i) {
    ss << std::hex << std::setw(1) << dis(gen);
  }
  ss << ".txt";
  return ss.str();
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  std::string input_file = argv[1];
  std::filesystem::path input_path = std::filesystem::absolute(input_file);
  
  if (!std::filesystem::exists(input_path)) {
    std::cerr << "Error: File not found: " << input_path << std::endl;
    return 1;
  }
  
  std::string output_file = generate_random_filename();
  std::filesystem::path output_path = std::filesystem::current_path() / output_file;

  InvertedIndex index;
  
  index.build_from_file(input_path.string());
  index.write_to_file(output_path.string());
  
  std::cout << "Done!" << std::endl;
  
  return 0;
}
