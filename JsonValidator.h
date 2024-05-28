#pragma once
#ifndef JSON_VALIDATOR_H
#define JSON_VALIDATOR_H

#include <vector>
#include <string>
#include <cstring>
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
    /// @brief 
    /// @param  
    /// @return 
    bool validateSimpleBraces(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateCurlyBraces(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateStraightBraces(const std::string&) const;
    /// @brief 
    /// @param  
    /// @param  
    /// @return 
    bool validateBraces(const std::string&, BracesType) const;
    /// @brief 
    /// @param c 
    /// @return 
    bool isDigit(char c) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isInteger(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isFloatingPoint(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isIntegersArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isFloatingPointsArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isNumbersArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isStringsArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isBooleansArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isObject(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isObjectsArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @param  
    /// @return 
    std::string& skipWhiteSpaces(const std::string&, std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateAllBraces(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool isArray(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateKeys(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateValues(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateCommas(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool validateKeyValueSeparators(const std::string&) const;
};

#endif