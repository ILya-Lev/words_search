#pragma once
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <algorithm>
#include <iostream>
using std::string;
using std::map;
using std::cout;
using std::endl;

class FreqTable{
public:
  explicit FreqTable(std::ifstream &dataFile, std::ifstream &tableFile = std::ifstream ("freqTable.txt"));
	explicit FreqTable(string &dataFileName, string &tableFileName = string ("freqTable.txt"));
	string createTable(std::ifstream &dataFile) const;
	string getFreqTable() const {return freqTable;}
private:
	string freqTable;
	bool tolowerMy(char &c) const;
};

FreqTable::FreqTable(std::ifstream &dataFile, std::ifstream &tableFile)
{
	if(tableFile.good())
		freqTable.assign(std::istream_iterator<char>(tableFile), std::istream_iterator<char>());
	else {
		freqTable = createTable(dataFile);		//this function throws an exception if file isn't good
	}
}
FreqTable::FreqTable(string &dataFileName, string &tableFileName)
{
	std::ifstream tableFile(tableFileName);
	if(tableFile.good())
		freqTable.assign(std::istream_iterator<char>(tableFile), std::istream_iterator<char>());
	else {
		std::ifstream dataFile(dataFileName);
		freqTable.assign(createTable(dataFile));	//this function throws an exception if file isn't good

		std::ofstream outputFile(tableFileName);
		outputFile<<freqTable;
	}
}

string FreqTable::createTable(std::ifstream &dataFile) const
{
	if(!dataFile.good()) {
		throw "dataFile isn't good, cannot handle this situation";
	}
	map<char, int> mci;
	for(char c='a';c<='z';c++)
		mci.insert(map<char, int>::value_type(c,0));	//initial values in the map

	std::list<char> buffer((std::istreambuf_iterator<char>(dataFile)), (std::istreambuf_iterator<char>()));	//remember about similar function declaration !
//	cout<<"list buffer has been filled; its size "<<buffer.size()<<endl;

	for(std::list<char>::iterator i = buffer.begin(); i != buffer.end(); i++) {
		if(tolowerMy(*i))
			mci[*i]++;                        //map that contains amount of each litera in the text
	}

	std::multimap<int, char> mmic;        //this multimap is used to sort literas from the most rare to the most common
	for(map<char, int>::iterator i = mci.begin(); i != mci.end(); i++) {
		mmic.insert(std::multimap<int, char>::value_type(i->second, i->first));
	}

	string answer;
	for(std::multimap<int, char>::iterator i=mmic.begin(); i != mmic.end(); i++) {
		answer.push_back(i->second);
	}
	return answer;                        //interface of the class is reproduced with strings
}

bool FreqTable::tolowerMy(char &c) const
{
	if(c >= 'A' && c <= 'Z') {              //this function checks if the char is litera of english alphabet
		c += ('a'-'A');                       //and changes capital literas to small ones
		return true;
	}
	if(c >= 'a' && c <= 'z') {
		return true;
	}
	return false;
}
