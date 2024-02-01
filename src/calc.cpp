#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include "calc.h"
#include "./num/num.h"
#include "parser.h"

bool CCalc::isSame(const string &a, const string &b)
{
    if (a.size() != b.size())
        return false;

    for (size_t i = 0; i < a.size(); i++)
    {
        if (toupper(a[i]) != toupper(b[i]))
            return false;
    }
    return true;
}

CCalc::CCalc() {}

CCalc::~CCalc() {}

bool CCalc::checkID(const string &x)
{
    if (x.empty())
        return false;

    // check forbidden indentifiers
    if (isSame(x, "import") || isSame(x, "export") || isSame(x, "exit") || isSame(x, "factorial") || isSame(x, "round"))
        return false;

    for (size_t i = 0; i < x.size(); i++)
    {
        if (isspace(x[i]) || !isalpha(x[i]))
            return false;
    }
    return true;
}

bool CCalc::shouldExit(const string &s)
{
    auto it = s.begin();
    while (it != s.end() && isspace(*it))
    {
        ++it;
    }
    if (toupper(*it++) == 'E' && toupper(*it++) == 'X' && toupper(*it++) == 'I' && toupper(*it++) == 'T')
    {
        while (isspace(*it) && it != s.end())
        {
            ++it;
        }
        if (it == s.end())
            return true;
        return false;
    }
    return false;
}

string CCalc::getID(string s)
{
    auto it = s.rbegin();
    while (it != s.rend() && isspace(*it))
    {
        s.pop_back();
        it = s.rbegin();
    }

    // remove WS from the beginning of string s
    auto itf = s.begin();
    while (itf != s.end() && isspace(*itf))
    {
        s.erase(s.begin());
        itf = s.begin();
    }

    return s;
}

bool CCalc::externStream(const string &line)
{
    size_t i = 0;
    while (isspace(line[i]))
        ++i;

    if (line.size() < i + 6)
    {
        return false;
    }

    if (isSame(line.substr(i, 6), "import") && isspace(line[i + 6]))
    {
        if (line.size() < i + 8)
            cerr << "Missing file name!" << endl;
        else
        {
            string file = line.substr(i + 7);
            try
            {
                this->importVar(file);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << endl;
            }
        }
        return true;
    }
    else if (isSame(line.substr(i, 6), "export") && isspace(line[i + 6]))
    {
        if (line.size() < i + 8)
            cerr << "Missing file name!" << endl;
        else
        {
            string file = line.substr(i + 7);
            try
            {
                this->exportVar(file);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << endl;
            }
        }
        return true;
    }
    return false;
}

int CCalc::processExpr(const string &line)
{

    auto it = line.find('=');
    if (it != string::npos)
    {
        return this->processVarExpr(line);
    }
    else
    {
        try
        {
            cout << evaluateExpression(line)->print() << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << endl;
        }
    }
    return 0;
}

int CCalc::processVarExpr(const string &line)
{
    auto it = line.find('=');
    if (it == string::npos)
    {
        throw std::invalid_argument("Variable name missing");
    }
    string id = line.substr(0, it);
    id = getID(move(id));
    if (!checkID(id))
    {
        cerr << "invalid identifier: \""s + id + "\""s << endl;
        return -1;
    }

    string expression = line.substr(it + 1);
    CNumPtr num;

    try
    {
        num = this->evaluateExpression(expression);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << endl;
        return -1;
    }

    auto var = m_variables.emplace(id, num);
    if (!var.second)
        var.first->second = num;

    return 0;
}

void CCalc::run()
{
    string line;
    while (getline(cin, line))
    {
        if (this->shouldExit(line))
            break;

        if (this->externStream(line))
            continue;

        this->processExpr(line);
    }
}

number CCalc::evaluateExpression(const string &expr) const
{
    return CParser(expr, m_variables).evaluate();
}

void CCalc::importVar(const string &file)
{
    ifstream in;
    in.open(file, std::ios::in);
    if (!in.good() || !in.is_open())
    {
        throw invalid_argument("Can not open file: \""s + file + "\"");
    }
    string line;
    while (getline(in, line))
    {
        if (!in.good())
        {
            in.close();
            throw std::ios_base::failure("error when reading line from: \""s + file + "\"");
        }

        try
        {
            this->processVarExpr(line);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << " in: \"" << line << "\"" << endl;
        }
    }
    in.close();
}

void CCalc::exportVar(const string &file)
{
    ofstream out;
    out.open(file, std::ios::out);
    if (!out.good() || !out.is_open())
    {
        throw std::invalid_argument("can not open file: \""s + file + "\"");
    }
    for (auto x : m_variables)
    {
        out << x.first << "=" << x.second << endl;
        if (!out.good())
        {
            out.close();
            throw std::ios_base::failure("error when writing variable \""s + x.first + "\"");
        }
    }
    out.close();
}