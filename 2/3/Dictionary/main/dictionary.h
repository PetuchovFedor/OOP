#pragma once
//убрать лишние инклуды
#include <map>
#include <iostream>
#include <utility>
#include <string>

using Dictionary = std::multimap<std::string, std::string>;

Dictionary LoadDictionary(const std::string& fileName);

void SaveDictionary(const std::string& fileName, const Dictionary& dict);

bool IsRussianPhrase(const std::string& phrase);

bool TranslatePhraseFromEnglishToRussian(const Dictionary& dict, std::ostream& output, const std::string& phrase);

bool TranslatePhraseFromRussianToEnglish(const Dictionary& dict, std::ostream& output, const std::string& phrase);

std::string ReadPhraseTranslation(std::istream& input, Dictionary& dict, const std::string& phrase);

bool DialogProgramWithUser(std::ostream& output, Dictionary& dict);

void InsertPhraseInDictionary(Dictionary& dict, const std::pair<const std::string, const std::string>& pr);

bool IsNeedToSaveDictionary(std::istream& input, std::ostream& output);