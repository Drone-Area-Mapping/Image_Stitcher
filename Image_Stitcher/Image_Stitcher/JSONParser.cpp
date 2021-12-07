#include "JSONParser.h"



JSONParser::JSONParser()
{
	cout << "initializing JSON object...\n";
};

JSONParser::~JSONParser()
{
    cout << "closing JSON object...\n";
};

string JSONParser::getDataTitle(string input)
{
    if (input == "") return "";
    string target = "\"";
#ifdef DEBUG
    cout << strpos(input, target, 3) << ":" << strpos(input, target, 4) << ":" << input.length();
#endif
    return input.substr((strpos(input, target, 3) + 1), (strpos(input, target, 4) - strpos(input, target, 3) - 1));
};

string JSONParser::getDataValue(string input)
{
    if (input == "") return "";
    string target = "\"";
    if(strpos(input, target, 7) != -1) return input.substr((strpos(input, target, 7) + 1), (input.length() - strpos(input, target, 7) - 3));
    else return input.substr((strpos(input, target, 6) + 2), (input.length() - strpos(input, target, 6)) - 4);
};

string JSONParser::writeJson(string, string)
{
    return NULL;
};

int JSONParser::strpos(string input, string target, int nth)
{
    size_t pos = 0;
    int cnt = 0;

    while (cnt != nth)
    {
        pos += 1;
        pos = input.find(target, pos);
        if (pos == std::string::npos)
            return -1;
        cnt++;
    }
    return pos;
}