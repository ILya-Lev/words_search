#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Key{
public:
  explicit Key(const string &freqT);
	string getKeyDubl() const {return wdublKey;}
	string getKeySimplif() const {return simplifKey;}
private:
	string initKey, simplifKey, wdublKey;
//	string freqTable;

	class lessLitera : public std::binary_function<char, char, bool>
	{
	public:
		lessLitera(const string &freqT) : freqTable(freqT) {if(freqT.empty()) throw "cannot handle empty freqT";}
		bool operator() (const char lhs, const char rhs)
		{
			return freqTable.find(lhs) < freqTable.find(rhs);
		}
	private:
		string freqTable;
	};
};

Key::Key(const string &freqT)
{
	cout<<"enter a string to find with: ";
	getline(cin, initKey);

	std::for_each(initKey.begin(), initKey.end(), [](char &c) {c = tolower(c);});     //lambda function

	wdublKey = initKey;
	std::sort(wdublKey.begin(), wdublKey.end(), lessLitera(freqT));      //sort using func obj lessLitera, that depends on frequence table

	simplifKey = wdublKey;
	simplifKey.erase(std::unique(simplifKey.begin(), simplifKey.end()), simplifKey.end());
//	string (simplifKey).swap(simplifKey);
}
