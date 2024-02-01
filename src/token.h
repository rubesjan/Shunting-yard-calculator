#ifndef TOKEN548523
#define TOKEN548523

#include <optional>
#include <functional>
#include <cstdlib>
#include <iostream>

#include "./ast/node.h"

using namespace std;

/**
 * @brief Represents token in mathematical expression - number or operator
 *
 */
class CToken
{
public:
    /**
     * @brief Type of the token
     *
     */
    enum class CType
    {
        /**
         * @brief number
         */
        number,
        /**
         * @brief minus operator '-'
         */
        minus,
        /**
         * @brief plus operator '+'
         */
        plus,
        /**
         * @brief multiplication operator '*'
         */
        multiplicate,
        /**
         * @brief division operator '/'
         */
        divide,
        /**
         * @brief modulus operator '\%'
         */
        modulus,
        /**
         * @brief power operator '^'
         */
        pow,
        /**
         * @brief left parenthesis '('
         */
        lparen,
        /**
         * @brief right parenthesis ')'
         */
        rparen,
        /**
         * @brief end of expression
         */
        eof
    };

    /**
     * @brief Construct a new CToken object representing a number
     *
     * This constructor is used only for numbers.
     * @param type Type of the Token - what is this token representing
     * @param num value of the number
     */
    CToken(const CType type, const number num);
    /**
     * @brief Construct a new CToken object
     *
     * @param type Type of the token - what is this token representing
     */
    CToken(const CType type);
    /**
     * @brief Construct a new CToken object, deep copy
     *
     * @param x copy
     */
    CToken(const CToken &x);
    /**
     * @brief deep copy of x
     *
     * @param x copy
     * @return CToken& reference to the new copy, for chaining purposes
     */
    CToken &operator=(CToken x);
    /**
     * @brief If this token represents an operator
     *
     * @return true this token does represent an operator
     * @return false this token does not represent an operator
     */
    bool isOperator() const;
    /**
     * @brief If this token represents a number
     *
     * @return true this token does represent a number
     * @return false this token does not represent a number
     */
    bool isNumber() const;
    /**
     * @brief If this token represents left parenthesis
     *
     * @return true this token does represent left parenthesis
     * @return false this token does not represent left parenthesis
     */
    bool isLParen() const;
    /**
     * @brief If this token represents right parenthesis
     *
     * @return true this token does represent right parenthesis
     * @return false this token does not represent right parenthesis
     */
    bool isRParen() const;
    /**
     * @brief If this token represents end of expression
     *
     * @return true this token does represent an end of expression
     * @return false this token does not represent an end of expression
     */
    bool isEof() const;
    /**
     * @brief Get the Value of number, only if this token represents a number
     *
     * If this token does not represents a number, logic_error is thrown.
     *
     * @return number value of the number
     */
    number getValue() const;
    /**
     * @brief print this token
     *
     * For debugging purposes only.
     *
     * @param out ostream to which this token is printed
     */
    void print(ostream &out) const;
    /**
     * @brief Get priority of operator, which this token represents.
     *
     * If this token does not represents an operator. 0 is returned - lowest value.
     *
     * @return int value priority in relation to other operators
     */
    int priority() const;
    /**
     * @brief Get CNode from this token, only if this token represents a binary operator.
     *
     * If this token does not represent operator exception logic_error is thrown.
     *
     * @param left - left operand of the operation
     * @param right - right operand of the operation
     * @return - CNodePtr shared pointer to CNode created from this token
     */
    CNodePtr getNode(const CNodePtr &left, const CNodePtr &right) const;
    /**
     * @brief Get CNode from this token, only if this token represents a number.
     *
     * If this token does not represent a number exception logic_error is thrown.
     *
     * @return CNodePtr shared pointer to CNode created from this token
     */
    CNodePtr getNode() const;

private:
    /**
     * @brief Type of this token - what is this token representing.
     *
     */
    CType m_type;
    /**
     * @brief If this token represents a number, this is the value.
     *
     */
    optional<number> m_n;
};

#endif