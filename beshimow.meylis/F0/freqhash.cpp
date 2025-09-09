#include "freqhash.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

// Вспомогательные функции скрыты в анонимном пространстве имён.
namespace {

std::string toLower(const std::string& s)
{
  std::string result;
  result.reserve(s.size());

  for (unsigned char ch : s) {
    result.push_back(static_cast<char>(std::tolower(ch)));
  }

  return result;
}

std::string stripPunctuation(std::string word)
{
  while (!word.empty() && std::ispunct(static_cast<unsigned char>(word.front())))
  {
    word.erase(word.begin());
  }

  while (!word.empty() && std::ispunct(static_cast<unsigned char>(word.back())))
  {
    word.pop_back();
  }

  return word;
}

} // namespace

beshimow::FreqTable beshimow::buildFreqTable(const std::string& text)
{
  FreqTable table{};
  std::istringstream iss{text};
  std::string token{};

  while (iss >> token)
  {
    const std::string cleaned = stripPunctuation(token);

    if (cleaned.empty())
    {
      continue;
    }

    const std::string key = toLower(cleaned);
    ++table[key];
  }

  return table;
}

std::vector<std::pair<std::string, std::size_t>>
beshimow::toSortedVector(const FreqTable& table, const std::string& sortMode)
{
  std::vector<std::pair<std::string, std::size_t>> result{table.begin(), table.end()};

  if (sortMode == "alpha")
  {
    std::sort(result.begin(), result.end(),
      [] (const auto& a, const auto& b) -> bool
      {
        return a.first < b.first;
      });
  }
  else
  {
    std::sort(result.begin(), result.end(),
      [] (const auto& a, const auto& b) -> bool
      {
        if (a.second == b.second)
        {
          return a.first < b.first;
        }
        return a.second > b.second;
      });
  }

  return result;
}
