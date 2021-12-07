#pragma once
#include <iostream>
#include <string>

using namespace std;

class JSONParser
{
	public:
		JSONParser();
		~JSONParser();
		string getDataTitle(string);
		string getDataValue(string);
		string writeJson(string, string);
		

	private:
		int strpos(string, string, int);
};		

