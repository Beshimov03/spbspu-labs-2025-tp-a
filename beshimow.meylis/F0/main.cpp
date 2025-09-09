#include "freqhash.hpp"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
  // Поддержка простого режима сортировки через аргумент:
  // ./freqhash --alpha  или  ./freqhash (по умолчанию -- freq)
  const std::string sortMode = (argc > 1 && std::string(argv[1]) == "--alpha")
    ? "alpha"
    : "freq";

  std::ostringstream buffer{};
  std::string line{};

  while (std::getline(std::cin, line))
  {
    buffer << line << ' ';
  }

  const beshimow::FreqTable table = beshimow::buildFreqTable(buffer.str());
  const std::vector<std::pair<std::string, std::size_t>> sorted =
    beshimow::toSortedVector(table, sortMode);

  for (const auto& kv : sorted)
  {
    std::cout << kv.first << ' ' << kv.second << '\n';
  }

  return 0;
}
