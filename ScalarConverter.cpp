#include "ScalarConverter.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <limits>
#include <string>
#include <cmath>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& src) { (void)src; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& src) { (void)src; return *this; }
ScalarConverter::~ScalarConverter() {}

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string& literal)
{
    if (literal.empty())
        return INVALID;

    if (literal.length() == 1 && isprint(literal[0]))
        return CHAR;

    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'' && isprint(literal[1]))
        return CHAR;
    
    if (literal == "nan" || literal == "+inf" || literal == "-inf" || 
        literal == "nanf" || literal == "+inff" || literal == "-inff")
        return PSEUDO_LITERAL;
    
    bool isFloat = false;
    if (literal.length() > 0 && literal[literal.length() - 1] == 'f')
        isFloat = true;
    
    
    char* endptr;
    std::string valueToConvert = isFloat ? literal.substr(0, literal.length() - 1) : literal;
    
    double value = std::strtod(valueToConvert.c_str(), &endptr);
    
    if (*endptr == '\0')
    {
        if (value == static_cast<int>(value) && !isFloat && value <= std::numeric_limits<int>::max() && value >= std::numeric_limits<int>::min())
            return INT;
        return isFloat ? FLOAT : DOUBLE;
    }
    
    return INVALID;
}

void ScalarConverter::displayChar(double value, bool impossible)
{
    std::cout << "char: ";
    if (impossible || std::isnan(value) || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
        std::cout << "impossible";
    else if (!isprint(static_cast<char>(value)))
        std::cout << "Non displayable";
    else
        std::cout << "'" << static_cast<char>(value) << "'";
    std::cout << std::endl;
}

void ScalarConverter::displayInt(double value, bool impossible)
{
    std::cout << "int: ";
    if (impossible || std::isnan(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        std::cout << "impossible";
    else
        std::cout << static_cast<int>(value);
    std::cout << std::endl;
}

void ScalarConverter::displayFloat(double value, bool impossible)
{
    std::cout << "float: ";
    if (impossible && !std::isnan(value) && !std::isinf(value))
        std::cout << "impossible";
    else
    {
        std::cout << static_cast<float>(value);
        if (value == static_cast<int>(value) && !std::isnan(value) && !std::isinf(value))
            std::cout << ".0";
        std::cout << "f";
    }
    std::cout << std::endl;
}

void ScalarConverter::displayDouble(double value, bool impossible)
{
    std::cout << "double: ";
    if (impossible && !std::isnan(value) && !std::isinf(value))
        std::cout << "impossible";
    else
    {
        std::cout << value;
        if (value == static_cast<int>(value) && !std::isnan(value) && !std::isinf(value))
            std::cout << ".0";
    }
    std::cout << std::endl;
}

void ScalarConverter::handlePseudoLiteral(const std::string& literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    
    if (literal == "nanf" || literal == "+inff" || literal == "-inff")
    {
        std::cout << "float: " << literal << std::endl;
        if (literal == "nanf")
            std::cout << "double: nan" << std::endl;
        else if (literal == "+inff")
            std::cout << "double: +inf" << std::endl;
        else
            std::cout << "double: -inf" << std::endl;
    }
    else
    {
        if (literal == "nan")
            std::cout << "float: nanf" << std::endl;
        else if (literal == "+inf")
            std::cout << "float: +inff" << std::endl;
        else
            std::cout << "float: -inff" << std::endl;
        std::cout << "double: " << literal << std::endl;
    }
}

void ScalarConverter::convert(const std::string& literal)
{
    LiteralType type = detectType(literal);
    
    switch (type)
    {
        case CHAR:
        {
            char c = (literal.length() == 3) ? literal[1] : literal[0];
            double value = static_cast<double>(c);
    
            displayChar(value, false);
            displayInt(value, false);
            displayFloat(value, false);
            displayDouble(value, false);
            break;
        }
        case INT:
        case FLOAT:
        case DOUBLE:
        {
            std::string valueStr = (type == FLOAT) ? literal.substr(0, literal.length() - 1) : literal;
            
            char* endptr;
            double value = std::strtod(valueStr.c_str(), &endptr);
            
            displayChar(value, false);
            displayInt(value, false);
            displayFloat(value, false);
            displayDouble(value, false);
            break;
        }
        case PSEUDO_LITERAL:
            handlePseudoLiteral(literal);
            break;
        case INVALID:
        default:
            std::cout << "Error: Invalid literal format." << std::endl;
            break;
    }
}