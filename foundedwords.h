#pragma once
#include <string>
#include <list>
#include <fstream>
#include <map>
using std::string;
using std::list;

class FoundWords{
public:
  explicit FoundWords(std::ifstream &dataFile, const string &wdublKey, const string &key);

	list<string> getListWords() const {return words;}
	list<string> getListWordsWDublKey() const {return wordsWdublKey;}
private:
	list<string> wordsWdublKey, words;

	void makeList(std::ifstream &dataFile, const string &key);
	bool isSubset(const string &big, const string &small) const;
	bool isSubsetDubl(const string &big, const string &small) const;
	void createMapStr(const string &, std::map<char, int> &) const;
};

FoundWords::FoundWords(std::ifstream &dataFile, const string &wdublKey, const string &key)
{
	dataFile.clear();
	if(!dataFile.good()) throw "cannot handle bad dataFile, bye";

	makeList(dataFile, key);		//creates words

	wordsWdublKey = words;
	wordsWdublKey.remove_if([&](const string &s) {return !isSubsetDubl(s, wdublKey);});
}
void FoundWords::makeList(std::ifstream &dataFile, const string &key)
{
	string buffer;
	while(dataFile.good()) {
		getline(dataFile, buffer);

		std::for_each(buffer.begin(), buffer.end(), [](char &c) {c = tolower(c);});

		if(isSubset(buffer, key))
			words.push_back(buffer);
	}
}
bool FoundWords::isSubset(const string &big, const string &small) const
{
	for(string::const_iterator i = small.begin(); i != small.end(); i++) {
		if(big.find(*i) == big.npos && big.find(tolower(*i)) == big.npos) {
			return false;
		}
	}
	return true;
}
bool FoundWords::isSubsetDubl(const string &big, const string &small) const
{
	std::map<char, int> mb, ms;
	createMapStr(big, mb);
	createMapStr(small, ms);

	for(std::map<char, int>::iterator i = ms.begin(); i != ms.end(); i++) {
		if(mb.find(i->first) == mb.end() || mb[i->first] < i->second)
			return false;
	}
	return true;
}
void FoundWords::createMapStr(const string &str, std::map<char, int> &m) const
{
	for(string::const_iterator ci = str.begin(); ci != str.end(); ci++) {
		if(m.find(*ci) == m.end())
			m.insert(std::pair<char, int>(*ci, 1));
		else
			m[*ci]++;
	}
}
