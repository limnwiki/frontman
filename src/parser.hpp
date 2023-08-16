#pragma once
#include <vector>
#include <iostream>

struct String
{
    String()
    {
        str = "";
    }

    String(std::string s)
    {
        str = s;
    }

    String(const char* s)
    {
        str = s;
    }

    String(std::vector<std::string> vec, const std::string& join = " ")
    {
        for (const auto& item : vec)
            str+=item+join;
    }

    String(std::vector<String> vec, const std::string& join = " ")
    {
        for (const auto& item : vec)
            str+=item.str+join;
    }

    String inside(std::string_view a, std::string_view b)
    {
        const unsigned first = str.find(a);
        const unsigned last = str.find(b, first+1);

        return str.substr(first+a.length(), last-first-a.length());
    }

    bool has_inside(std::string_view a, std::string_view b)
    {
        const auto first = str.find(a);

        if (first == std::string_view::npos)
            return false;

        const auto last = str.find(b, first+1);

        if (last == std::string_view::npos)
            return false;

        return true;
    }

    String outside(std::string_view a, std::string_view b)
    {
        const unsigned first = str.find(a);
        const unsigned last = str.find(b, first+1);

        std::string s = str;
        s.erase(first, last-first+b.length());

        return s;
    }

    std::vector<String> split(const char delim)
    {
        std::string s;
        std::vector<String> tokens;

        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] == delim)
            {
                tokens.push_back(s);
                s.clear();
            }
            else s+=str[i];
        }

        if (!s.empty())
            tokens.push_back(s);

        return tokens;
    }

    String remove_duplicate(const char ch)
    {
        std::string s = str;

        for (size_t i = 0; i < s.length(); i++)
        {
            if (s[i] == ch && i > 0 && s[i-1] == ch)
            {
                s.erase(i, 1);
                i--;
            }
        }

        return s;
    }

    String remove_padding(const char ch = ' ')
    {
        std::string s = str;

        if (s.empty() || s.length() < 2)
            return s;

        if (s[0] == ch)
            s.erase(s.begin());
        
        if (s[s.length()-1] == ch)
            s.pop_back();

        return s;
    }

    String remove(const char ch)
    {
        std::string s = str;

        for (size_t i = 0; i < s.length(); i++)
        {
            if (s[i] == ch)
                s.erase(i, 1);
        }

        return s;
    }

    String replace(const std::string& a, const std::string& b)
    {
        std::string s = str;
        std::size_t pos = s.find(a);
        
        if (pos == std::string::npos) 
            return "";
            
        s.replace(pos, a.length(), b);
        return s;
    }
    size_t find(const std::string& s)
    {
        return str.find(s);
    }

    size_t length()
    {
        return str.length();
    }

    operator std::string()
    {
        return str;
    }

    String operator+(const char c)
    {
        return str+c;
    }

    String operator+(const std::string& s)
    {
        return str+s;
    }

    std::string str;
};

std::ostream &operator<<(std::ostream &os, const String &str) 
{
    return os << str.str;
}