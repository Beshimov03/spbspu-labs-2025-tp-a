#ifndef BESHIMOW_FREQHASH_HPP
#define BESHIMOW_FREQHASH_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

namespace beshimow {

using FreqTable = std::unordered_map<std::string, std::size_t>;

FreqTable buildFreqTable(const std::string& text);

std::vector<std::pair<std::string, std::size_t>>
toSortedVector(const FreqTable& table, const std::string& sortMode = "freq");

}

#endif
