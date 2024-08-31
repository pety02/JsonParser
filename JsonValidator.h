#pragma once
#ifndef JSON_VALIDATOR_H
#define JSON_VALIDATOR_H

#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

class JsonParser;

/// @brief a class that validates json objects
class JsonValidator final
{
private:
    enum BracesType
    {
        SIMPLE,
        CURLY,
        STRAIGHT
    };

    /// @brief validates if all simple bracces are put correctly
    /// @param json text
    /// @return true if all simple braces are correctly opened and closed and false in the other cases
    static bool validateSimpleBraces(const std::string&);
    /// @brief validates if all curly bracces are put correctly
    /// @param json text
    /// @return true if all curly braces are correctly opened and closed and false in the other cases
    static bool validateCurlyBraces(const std::string&);
    /// @brief validates if all straight bracces are put correctly
    /// @param json text
    /// @return true if all straight braces are correctly opened and closed and false in the other cases
    static bool validateStraightBraces(const std::string&);
    /// @brief validates if all bracces from a definite type are put correctly
    /// @param json text
    /// @param bracesType type of the braces to be validated
    /// @return true if all bracces from a definite type are correctly opened and closed and false in the other cases
    static bool validateBraces(const std::string&, BracesType);
    /// @brief checks if a character is a digit
    /// @param c definite character to be validated
    /// @return true if the character is a digit and false in the other cases
    static bool isDigit(char);
    /// @brief checks if a character is a letter
    /// @param c definite character to be validated
    /// @return true if the character is a letter and false in the other cases
    static bool isLetter(char);
    /// @brief chacks if a string represents an integer
    /// @param json definite string to be checked
    /// @return true if the text represents an integer and false in the other cases
    static bool isInteger(const std::string&);
    /// @brief chacks if a string represents a floating point
    /// @param json definite string to be checked
    /// @return true if the text represents a floating point and false in the other cases
    static bool isFloatingPoint(const std::string&);
    /// @brief 
    /// @param  
    /// @return 
    static bool isISODateFormat(const std::string&);
    /// @brief 
    /// @param  
    /// @return 
    static bool isUSADateFormat(const std::string&);
    /// @brief 
    /// @param  
    /// @return 
    static bool isEURDateFormat(const std::string&);
    /// @brief 
    /// @param  
    /// @return 
    static bool isDate(const std::string&);
    /// @brief 
    /// @param  
    /// @return 
    static bool isDatesArray(const std::string&);
    /// @brief check if a string represents an integers array 
    /// @param json a string to be checked
    /// @return true if the text represents an integers array
    static bool isIntegersArray(const std::string&);
    /// @brief check if a string represents a floating point array 
    /// @param json a string to be checked
    /// @return true if the text represents a floating point array
    static bool isFloatingPointsArray(const std::string&);
    /// @brief check if a string represents a numbers array 
    /// @param json a string to be checked
    /// @return true if the text represents a numbers array 
    static bool isNumbersArray(const std::string&);
    /// @brief check if a string represents a strings array 
    /// @param json a string to be checked
    /// @return true if the text represents a strings array
    static bool isStringsArray(const std::string&);
    /// @brief check if a string represents a booleans array 
    /// @param json a string to be checked
    /// @return true if the text represents a booleans array
    static bool isBooleansArray(const std::string&);
    /// @brief check if a string represents an objects array 
    /// @param json a string to be checked
    /// @return true if the text represents an objects array 
    static bool isObjectsArray(const std::string&);
    /// @brief skips all odd whitespaces in a string 
    /// @param json a string in which should be skipped whitespaces
    /// @param newJson the new string in which should store the json string with the skipped whitespaces
    /// @return the newJson string
    static std::string& skipWhiteSpaces(const std::string&);
    /// @brief validates that all braces are put correctly
    /// @param json a string to be validated
    /// @return true if all braces are opened and closed correctly and false in the other cases
    static bool validateAllBraces(const std::string&);
    /// @brief validates that a string represent an array
    /// @param json a string to be validated
    /// @return true if the string represents an array and false in the other cases
    static bool isArray(const std::string&);
    /// @brief validates that all keys are correctly written
    /// @param json a string to be validated
    /// @return true if all keys are written correctly and false in the other cases
    static bool validateKeys(const std::string&);
    /// @brief validates that all values are correctly written
    /// @param json a string to be validated
    /// @return true if all values are written correctly and false in the other cases
    static bool validateValues(const std::string&);
    /// @brief validates that all separators of keys and values are correctly written
    /// @param json a string to be validated
    /// @return true if all separators of keys and values are correctly written and false in the other cases
    static bool validateSeparators(const std::string&);

    friend class JsonObject;
    friend class JsonParser;
    JsonValidator() = delete;

public:
    /// @brief check if a string represents an object 
    /// @param json a string to be checked
    /// @return true if the text represents an objectn 
    static bool isObject(const std::string&);
};

#endif