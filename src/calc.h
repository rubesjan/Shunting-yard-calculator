#ifndef CALC753654
#define CALC753654

#include <cstdlib>
#include <map>
#include <string>

#include "parser.h"
#include "./num/num.h"

/**
 * @brief Processing expressions from standard input and evaluating them
 *
 * This class enables user to store variables and export or import them to user readable file
 *
 */
class CCalc
{
public:
    /**
     * @brief Construct a new CCalc object
     *
     */
    CCalc();
    CCalc(const CCalc &x) = delete;
    CCalc &operator=(const CCalc &x) = delete;
    /**
     * @brief Destroy the CCalc object
     *
     */
    ~CCalc();
    /**
     * @brief start reading expressions from standard input until "exit"
     *
     * Reads expressions from standard input, evaluates it, prints result to standard output.
     */
    void run();

private:
    /**
     * @brief Evaluates expression from input, called by method "run".
     *
     * @param expr contains expression, from standard input, given by methon "run"
     * @return number returns number - result of the evaluated expression
     */
    number evaluateExpression(const string &expr) const;
    /**
     * @brief Decides if this instance should end - if given string contains "exit"
     *
     * @param s
     * @return true given string contains "exit", therefore this instance should stop reading expressions from standard input and end
     * @return false given string does not contain "exit" - contains mathematical expression
     */
    static bool shouldExit(const string &s);
    /**
     * @brief Finds variable identifier in the given string and returns it
     *
     * @param s string, in which to search for the identifier
     * @return string separated variable identifier
     */
    static string getID(string s);
    /**
     * @brief Checks, if the given ID is valid and allowed
     *
     * @param s ID, which is supposed to be checked
     * @return true given ID is valid and allowed
     * @return false given ID is not valid or allowed
     */
    static bool checkID(const string &s);
    /**
     * @brief Imports variables from file and stores them.
     *
     * If can not open file exception invalid_argument is thrown.
     * If stream failed while reading exception ios_base::failure is thrown.
     *
     * @param file name of file, containing wanted variables with values
     */
    void importVar(const string &file);
    /**
     * @brief Exports stored variables into file.
     *
     * If can not open the file exception invalid_argument is thrown.
     * If stream failed when writing exception ios_base::failure is thrown.
     *
     * @param file name of file, to which variables are exported
     */
    void exportVar(const string &file);
    /**
     * @brief Process input provided by method "run"
     *
     * Tries to evaluate the given expression. Prints result to cout. If the expression is supposed to be stored in a variable it calls method "processVarExpr" and does not print anything. If the given expression si not valid, then it prints the error message to cerr.
     *
     * @param line string of mathematical expression to process and evaluate
     * @return 0 if expressino is valid
     */
    int processExpr(const string &line);
    /**
     * @brief Processes expression that is supposed to be stored in variable.
     *
     * If it is not a variable expression exception invalid_argument is thrown.
     *
     * @param line Expression to evaluate and store, containing ID of the variable
     * @return 0 when the given expression is valid and no excpetions are thrown.
     * @return -1 when ID is not valid/allowed or when the given expression is not valid
     */
    int processVarExpr(const string &line);
    /**
     * @brief Checks if the given string cointains "import" or "export" with file name
     *
     * @param out string which is supposed to be checked
     * @return true given string contains "import" or "export"
     * @return false given string does not contain "import" or "export"
     */
    bool externStream(const string &out);
    /**
     * @brief Checks if the given strings are same. Not case sensitive.
     *
     * @param a first string
     * @param b second string
     * @return true both strings are same
     * @return false strings are not same
     */
    static bool isSame(const string &a, const string &b);
    /**
     * @brief Stores variables with their values.
     *
     * Key is the name of the variable. Value in the map is value of the variable. It is key sensitive.
     */
    map<string, CNumPtr> m_variables;
};

#endif