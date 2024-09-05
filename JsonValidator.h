#pragma once
#ifndef JSON_VALIDATOR_H
#define JSON_VALIDATOR_H

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

class JsonParser;

class JsonValidator final
{
private:
    enum BracesType
    {
        CURLY,
        STRAIGHT
    };
    JsonValidator() = delete;

public:
    static std::string& skipWhiteSpaces(const std::string&);
    static bool isDigit(char);
    static bool isLetter(char);

    static bool validateCurlyBraces(const std::string&);
    static bool validateStraightBraces(const std::string&);
    static bool validateBraces(const std::string&, BracesType);
    static bool validateAllBraces(const std::string&);
    
    static bool isInteger(const std::string&);
    static bool isFloatingPoint(const std::string&);
    static bool isISODateFormat(const std::string&);
    static bool isUSADateFormat(const std::string&);
    static bool isEURDateFormat(const std::string&);
    static bool isDate(const std::string&); 
    static bool isObject(const std::string&);
    static bool isString(const std::string&);

    static bool validateKeys(const std::string&);
    static bool validateValues(const std::string&);
    static bool validateSeparators(const std::string&);

    static bool isIntegersArray(const std::string&);
    static bool isFloatingPointsArray(const std::string&);
    static bool isNumbersArray(const std::string&);
    static bool isDatesArray(const std::string&);
    static bool isObjectsArray(const std::string&);
    static bool isStringsArray(const std::string&);
    static bool isBooleansArray(const std::string&);
    static bool isArray(const std::string&);
};

#endif