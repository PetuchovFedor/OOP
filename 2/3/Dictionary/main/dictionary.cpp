#include "dictionary.h"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <fstream>
using namespace std;

//¬ќзвращать словарь
Dictionary LoadDictionary(const std::string& fileName)
{
	Dictionary dict;
	ifstream input(fileName);
	if (!input.is_open())
		return dict;
	string phrase;
	string translation;
	while (getline(input, phrase) && getline(input, translation))
		dict.insert({ phrase, translation });
	return dict;
}

void SaveDictionary(const std::string& fileName, const Dictionary& dict)
{
	ofstream output(fileName);
	for (const auto& [phrase, translation] : dict)
		output << phrase << "\n" << translation << "\n";
}

bool IsRussianPhrase(const std::string& phrase)
{
	//ѕробелы разрешить
	//string str = phrase;
	//неправильно remove прочитаь про идиому erase-remove 
	//remove(str.begin(), str.end(), ' ');
	return all_of(phrase.begin(), phrase.end(), [](char ch)
		{
		return (((ch >= 'ј') && (ch <= 'я') || (ch == '®')) || ((ch >= 'а') && (ch <= '€') || (ch == 'Є')) || (ch == '-') || (ch == ' '));
		});
}

bool TranslatePhraseFromEnglishToRussian(const Dictionary& dict, std::ostream& output, const std::string& phrase)
{
	//зачем искатьб 2 раза?

	// использовть structure buildings
	auto iters = dict.equal_range(phrase);
	if (iters.first == iters.second)
		return false;
	for (auto it = iters.first; it != iters.second; ++it)
	{
		if (it != iters.first)
		{
			output << ", ";
		}
		output << it->second;
	}
	output << "\n";
	return true;
}

bool TranslatePhraseFromRussianToEnglish(const Dictionary& dict, std::ostream& output, const std::string& phrase)
{
	//не пробегать по всему mapу
	int count = 0;	
	Dictionary::const_iterator iter;
	Dictionary::const_iterator startPos = dict.begin();
	do
	{
		iter = find_if(startPos, dict.end(), [&](const auto& key) {
			return key.second == phrase;
			}
		);
		if (iter == dict.end())
			break;
		if (count > 0)
			output << ", ";
		output << iter->first;
		count++;
		startPos = ++iter;
	} 
	while (iter != dict.end());
	/*while (iter != end)
	find_if()
	for (auto it = dict.begin(); it != dict.end(); ++it)
	{
		if (it->second == phrase)
		{
			if (count > 0)
				output << ", ";
			output << it->first;
			count++;
		}
		
	}*/
	if (count == 0) 
		return false;
	output << "\n";
	return true;
}

//другое название
std::string ReadPhraseTranslation(std::istream& input, Dictionary& dict, const std::string& phrase)
{
	string translation;
	getline(input, translation);
	if (translation.empty())
		return translation;
	if (translation.find(',') != string::npos)
	{
		stringstream ss(translation);
		//temp дл€ температуры
		string str;
		while (getline(ss, str, ','))
		{
			if (str[0] == ' ')
				str.erase(0, 1);
			InsertPhraseInDictionary(dict, make_pair(phrase, str));
		}
	}
	else 
		InsertPhraseInDictionary(dict, make_pair(phrase, translation));
	return translation;
}


bool DialogProgramWithUser(std::ostream& output, Dictionary& dict)
{
	string phrase;
	//не дублировать getline
	bool isChange = false;
	while (getline(cin, phrase))
	{
		if (phrase == "...")
			break;
		if (IsRussianPhrase(phrase))
			if (TranslatePhraseFromRussianToEnglish(dict, output, phrase))
				continue;
		if (TranslatePhraseFromEnglishToRussian(dict, output, phrase))
			continue;
		output << R"(Ќеизвестное слово У)" << phrase << R"(Ф. ¬ведите перевод или пустую строку дл€ отказа. ≈сли хотите ввести несколько слов)";
		output << " дл€ перевода, то вводите через зап€тую" << "\n";
		string translation = ReadPhraseTranslation(cin, dict, phrase);
		if (!translation.empty())
		{ 
			if (!isChange)
				isChange = true;
			output << R"(—лово У)" << phrase << R"(Ф сохранено в словаре как У)" << translation << R"(Ф.)" << "\n";
		}
		else
			output << R"(—лово У)" << phrase << R"(Фпроигнорировано.)" << "\n";
	}
	return isChange;
}

void InsertPhraseInDictionary(Dictionary& dict, const std::pair<const std::string, const std::string>& pr)
{
	if (IsRussianPhrase(pr.second))
		dict.insert(pr);
	else
		dict.insert({ pr.second, pr.first });
}

bool IsNeedToSaveDictionary(std::istream& input, std::ostream& output)
{
	output << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом.\n";
	char ch;
	input >> ch;
	return (ch == 'Y' || ch == 'y');
}
