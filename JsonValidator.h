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
    bool validateSimpleBraces(std::string) const;
    bool validateCurlyBraces(std::string) const;
    bool validateStraightBraces(std::string) const;
    bool validateBraces(std::string, BracesType) const;
    bool isDigit(char c) const;
    bool isInteger(std::string) const;
    bool isFloatingPoint(std::string) const;
    bool isIntegersArray(std::string) const;
    bool isFloatingPointsArray(std::string) const;
    bool isNumbersArray(std::string) const;
    bool isStringsArray(std::string) const;
    bool isBooleansArray(std::string) const;
    bool isObject(std::string) const;
    bool isObjectsArray(std::string) const;

public:
    bool validateAllBraces(std::string) const;
    bool isArray(std::string) const;
    bool validateKeys(std::string) const;
    bool validateCommas(std::string) const;
    bool validateValues(std::string) const;
};

#endif