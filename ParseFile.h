#pragma once
#include "stdwin.h"

class ParseFile
{    
public:
    ParseFile() {  }

    void ParsingFile(string path)
    {
        this->path=path;
        vector<string> v = ReadFile();
        vector<string> v_parse;
        parse_stroki.clear();
        for (const auto& stroka_parse : v)
        {
            parse_stroki.push_back(Boost_fn(stroka_parse, razdelitelii));
        }
    }

    vector<string> Get_ParsingStroki()
    {        
        return parse_stroki;
    }

    string Get_FileName()
    {        
        return path;
    }


private:
    string path;
    string razdelitelii;
    vector<string> parse_stroki; //Вектор строк


    vector<string> ReadFile()
    {
        vector<string> v;         
        ifstream fin;
        fin.open(path);
        if (!fin.is_open())
        {
            std::cout << "\nError open file\n";
        }
        else
        {
          
            std::string str;
            int k = 0;          
            while (!fin.eof())
            {
                fin >> str;
                v.push_back(str);                
            };
        }

        razdelitelii = v[0];
        return v;
    }

    string Boost_fn(const std::string str = " ", const std::string razdelitel = " ;,.|")
    {        
        vector<string> split_vector;
        boost::split(split_vector, str, boost::is_any_of(razdelitelii));  // парсер каждой строки      
        string stroka_parse="";
        for (const auto& stroka : split_vector)
        {
            stroka_parse += " " + stroka;
        }        
        return stroka_parse;
    }
};

