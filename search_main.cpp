// file_istrbuf.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <algorithm>
#include "freqtable.h"
#include "key.h"
#include "foundedwords.h"
using std::map;
using std::string;
using std::cout;
using std::endl;


int _tmain(int argc, _TCHAR* argv[])
{
  try{
		FreqTable ft(string("names.txt"));
		cout<<ft.getFreqTable()<<endl;

		Key key(ft.getFreqTable());

		std::ifstream dataFile("names.txt");
		FoundWords fw(dataFile, key.getKeyDubl(), key.getKeySimplif());
		std::list<string> l1(fw.getListWords()), l2(fw.getListWordsWDublKey());

//		for(std::list<string>::iterator i = l1.begin(); i != l1.end(); i++)   //printing the list of found words
//			cout<<*i<<endl;                                                     //without counting literas dublicates
		cout<<"============================================================"<<endl;
		for(std::list<string>::iterator i = l2.begin(); i != l2.end(); i++)     //the same with dublicates
			cout<<*i<<endl;                                                       

	}
	catch(char *ex) {cout<<ex<<endl;}
	catch(...) {cout<<"unexpected exception, bye!"<<endl;}
	_getch();
	return 0;
}
