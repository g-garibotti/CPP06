#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <string>

class ScalarConverter {
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& src);
        ScalarConverter& operator=(const ScalarConverter& src);
        ~ScalarConverter();

        enum LiteralType
        {
            CHAR,
            INT,
            FLOAT,
            DOUBLE,
            PSEUDO_LITERAL,
            INVALID
        };

        static LiteralType detectType(const std::string& literal);
        
        static void displayChar(double value, bool impossible);
        static void displayInt(double value, bool impossible);
        static void displayFloat(double value, bool impossible);
        static void displayDouble(double value, bool impossible);
        
        static void handlePseudoLiteral(const std::string& literal);

    public:
        static void convert(const std::string& literal);
};

#endif