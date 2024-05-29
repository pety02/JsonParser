#pragma once
#ifndef JSON_VALIDATOR_H
#define JSON_VALIDATOR_H

#include <vector>
#include <string>
#include <cstring>

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
public:
    /// @brief validates if all simple bracces are put correctly
    /// @param json text
    /// @return true if all simple braces are correctly opened and closed and false in the other cases
    bool validateSimpleBraces(const std::string&) const;
    /// @brief validates if all curly bracces are put correctly
    /// @param json text
    /// @return true if all curly braces are correctly opened and closed and false in the other cases
    bool validateCurlyBraces(const std::string&) const;
    /// @brief validates if all straight bracces are put correctly
    /// @param json text
    /// @return true if all straight braces are correctly opened and closed and false in the other cases
    bool validateStraightBraces(const std::string&) const;
    /// @brief validates if all bracces from a definite type are put correctly
    /// @param json text
    /// @param bracesType type of the braces to be validated
    /// @return true if all bracces from a definite type are correctly opened and closed and false in the other cases
    bool validateBraces(const std::string&, BracesType) const;
    /// @brief checks if a character is a digit
    /// @param c definite character to be validated
    /// @return true if the character is a digit and else in the other cases
    bool isDigit(char) const;
    /// @brief chacks if a string represents an integer
    /// @param json definite string to be checked
    /// @return true if the text represents an integer and false in the other cases
    bool isInteger(const std::string&) const;
    /// @brief chacks if a string represents a floating point
    /// @param json definite string to be checked
    /// @return true if the text represents a floating point and false in the other cases
    bool isFloatingPoint(const std::string&) const;
    /// @brief check if a string represents an integers array 
    /// @param json a string to be checked
    /// @return true if the text represents an integers array
    bool isIntegersArray(const std::string&) const;
    /// @brief check if a string represents a floating point array 
    /// @param json a string to be checked
    /// @return true if the text represents a floating point array
    bool isFloatingPointsArray(const std::string&) const;
    /// @brief check if a string represents a numbers array 
    /// @param json a string to be checked
    /// @return true if the text represents a numbers array 
    bool isNumbersArray(const std::string&) const;
    /// @brief check if a string represents a strings array 
    /// @param json a string to be checked
    /// @return true if the text represents a strings array
    bool isStringsArray(const std::string&) const;
    /// @brief check if a string represents a booleans array 
    /// @param json a string to be checked
    /// @return true if the text represents a booleans array
    bool isBooleansArray(const std::string&) const;
    /// @brief check if a string represents an object 
    /// @param json a string to be checked
    /// @return true if the text represents an objectn 
    bool isObject(const std::string&) const;
    /// @brief check if a string represents an objects array 
    /// @param json a string to be checked
    /// @return true if the text represents an objects array 
    bool isObjectsArray(const std::string&) const;
    /// @brief skips all odd whitespaces in a string 
    /// @param json a string in which should be skipped whitespaces
    /// @param newJson the new string in which should store the json string with the skipped whitespaces
    /// @return the newJson string
    std::string& skipWhiteSpaces(const std::string&, std::string&) const;
    /// @brief validates that all braces are put correctly
    /// @param json a string to be validated
    /// @return true if all braces are opened and closed correctly and false in the other cases
    bool validateAllBraces(const std::string&) const;
    /// @brief validates that a string represent an array
    /// @param json a string to be validated
    /// @return true if the string represents an array and false in the other cases
    bool isArray(const std::string&) const;
    /// @brief validates that all keys are correctly written
    /// @param json a string to be validated
    /// @return true if all keys are written correctly and false in the other cases
    bool validateKeys(const std::string&) const;
    /// @brief validates that all values are correctly written
    /// @param json a string to be validated
    /// @return true if all values are written correctly and false in the other cases
    bool validateValues(const std::string&) const;
    /// @brief validates that all commas are correctly written as separators of key value pairs
    /// @param json a string to be validated
    /// @return true if all commas are written correctly and false in the other cases
    bool validateCommas(const std::string&) const;
    /// @brief validates that all separators of keys and values are correctly written
    /// @param json a string to be validated
    /// @return true if all separators of keys and values are correctly written and false in the other cases
    bool validateKeyValueSeparators(const std::string&) const;
};

#endif