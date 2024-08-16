#include "JsonValidator.h"

bool JsonValidator::validateSimpleBraces(const std::string& json) const
{
    std::vector<char> braces = std::vector<char>();
    char firstBrace = ' ';

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (i == 0 && (json[i] == '(' || json[i] == ')'))
        {
            firstBrace = json[i];
            if (firstBrace == ')')
            {
                return false;
            }
        }
        if (json[i] == '(')
        {
            braces.push_back(json[i]);
        }
        if (json[i] == ')' && !braces.empty())
        {
            braces.pop_back();
        }
    }

    return braces.size() == 0;
}

bool JsonValidator::validateCurlyBraces(const std::string& json) const 
{
    std::vector<char> braces = std::vector<char>();
    char firstBrace = ' ';

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (i == 0 && (json[i] == '{' || json[i] == '}'))
        {
            firstBrace = json[i];
            if (firstBrace == '}')
            {
                return false;
            }
        }
        if (json[i] == '{')
        {
            braces.push_back(json[i]);
        }
        if (json[i] == '}' && !braces.empty())
        {
            braces.pop_back();
        }
    }

    return braces.size() == 0;
}

bool JsonValidator::validateStraightBraces(const std::string& json) const
{
    std::vector<char> braces = std::vector<char>();
    char firstBrace = ' ';

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (i == 0 && (json[i] == '[' || json[i] == ']'))
        {
            firstBrace = json[i];
            if (firstBrace == ']')
            {
                return false;
            }
        }
        if (json[i] == '[')
        {
            braces.push_back(json[i]);
        }
        if (json[i] == ']' && !braces.empty())
        {
            braces.pop_back();
        }
    }

    return braces.size() == 0;
}

bool JsonValidator::validateBraces(const std::string& json, BracesType braceType) const 
{
    switch (braceType)
    {
        case BracesType::SIMPLE:
            return this->validateSimpleBraces(json);
        case BracesType::CURLY:
            return this->validateCurlyBraces(json);
        case BracesType::STRAIGHT:
            return this->validateStraightBraces(json);
        default:
            return false;
    }
}

bool JsonValidator::isDigit(char c) const 
{
    return '0' <= c && c <= '9';
}

bool JsonValidator::isInteger(const std::string& json) const 
{
    if (json.empty())
    {
        return false;
    }

    int signCount = 0;
    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if(1 < signCount || (i == json.length() - 1 && json[i] == '-')) {
            return false;
        }
        if(json[i] == '-' && this->isDigit(json[i + 1])) {
            signCount++;
        } else if (json[i] == '-' && !this->isDigit(json[i + 1])) {
            return false;
        }
        if(json[i] == '-' && 1 < signCount) {
            return false;
        } 
        if (json[i] != '-' && !this->isDigit(json[i]))
        {
            return false;
        }
    }

    return true;
}

bool JsonValidator::isFloatingPoint(const std::string& json) const 
{
    if (json.empty())
    {
        return false;
    }

    int dotsCount = 0, signCount = 0;
    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if(1 < signCount || (i == json.length() - 1 && json[i] == '-')) {
            return false;
        }
        if(json[i] == '-' && this->isDigit(json[i + 1])) {
            signCount++;
        } else if (json[i] == '-' && !this->isDigit(json[i + 1])) {
            return false;
        }
        if (json[i] == '.')
        {
            dotsCount++;
        }
        if (1 < dotsCount)
        {
            return false;
        }
        if(json[i] != '-' && !this->isDigit(json[i]) && json[i] != '.') {
            return false;
        }
    }

    return true;
}

bool JsonValidator::isIntegersArray(const std::string& json) const 
{
    if (json[0] != '[' || json[json.length() - 1] != ']')
    {
        return false;
    }
    unsigned int size = json.length();
    std::string values = json.substr(1, size - 2);
    std::string readed = "";
    for (unsigned int i = 0; i < values.length();)
    {
        while (values[i] == ' ')
        {
            i++;
        }
        do
        {
            if (values[i] == '\0')
            {
                break;
            }
            readed += values[i++];
        } while (values[i] != ',');
        ++i;
        if (json[i] != '-' && !this->isInteger(readed))
        {
            return false;
        }
        readed = "";
    }

    return true;
}

bool JsonValidator::isFloatingPointsArray(const std::string& json) const 
{
    if (json[0] != '[' || json[json.length() - 1] != ']')
    {
        return false;
    }
    unsigned int size = json.length();
    std::string values = json.substr(1, size - 2);
    std::string readed = "";
    for (unsigned int i = 0; i < values.length();)
    {
        while (values[i] == ' ')
        {
            i++;
        }
        do
        {
            if (values[i] == '\0')
            {
                break;
            }
            readed += values[i++];
        } while (values[i] != ',');
        ++i;
        if (!this->isFloatingPoint(readed))
        {
            return false;
        }
        readed = "";
    }

    return true;
}

bool JsonValidator::isNumbersArray(const std::string& json) const 
{
    return this->isIntegersArray(json) || this->isFloatingPointsArray(json);
}
bool JsonValidator::isStringsArray(const std::string& json) const 
{
    if (json[0] != '[' || json[json.length() - 1] != ']')
    {
        return false;
    }
    unsigned int size = json.length();
    std::string values = json.substr(1, size - 2);
    char *readed = new char[values.length()];
    unsigned int readFrom = 0;
    for (unsigned int i = 0; i < values.length();)
    {
        while (values[i] == ' ')
        {
            i++;
        }
        do
        {
            if (values[i] == '\0')
            {
                break;
            }
            readed[readFrom++] = values[i++];
        } while (values[i] != ',');
        ++i;
        if (readed[0] != '\"' || readed[readFrom - 1] != '\"')
        {
            return false;
        }
        readed = new char[values.length()];
        readFrom = 0;
    }

    return true;
}

bool JsonValidator::isBooleansArray(const std::string& json) const 
{
    if (json[0] != '[' || json[json.length() - 1] != ']')
    {
        return false;
    }
    unsigned int size = json.length();
    std::string values = json.substr(1, size - 2);
    std::string readed = "";
    unsigned int readFrom = 0;
    for (unsigned int i = 0; i < values.length();)
    {
        while ((values[i] < 'a' || 'z' < values[i]) && (values[i] < 'A' || 'Z' < values[i]))
        {
            i++;
        }
        do
        {
            if (values[i] == '\0')
            {
                break;
            }
            readed[readFrom++] = values[i++];
        } while (values[i] != ',');
        i++;
        if (readed != "true" && readed != "false")
        {
            return false;
        }
        readed = "";
        readFrom = 0;
    }

    return true;
}

bool JsonValidator::isObject(const std::string& json) const 
{
    std::string skippedWhites = this->skipWhiteSpaces(json);
    bool isValid = this->validateAllBraces(skippedWhites)
        && this->validateKeys(skippedWhites) 
        && this->validateSeparators(skippedWhites) 
        && this->validateValues(skippedWhites);

    return isValid;
}

bool JsonValidator::isObjectsArray(const std::string& json) const 
{
    if (json[0] != '[' || json[json.length() - 1] != ']')
    {
        return false;
    }
    unsigned int size = json.length();
    std::string values = json.substr(1, size - 2);
    char *readed = new char[values.length()];
    unsigned int readFrom = 0;
    for (unsigned int i = 0; i < values.length();)
    {
        do
        {
            if (values[i] == '\0')
            {
                break;
            }
            readed[readFrom++] = values[i++];
        } while (values[i] != ',');
        std::string readedAsString = readed;
        if (!this->isObject(readedAsString) && readedAsString != "null")
        {
            return false;
        }
        readed = new char[values.length()];
        readFrom = 0;
    }

    return true;
}

std::string& JsonValidator::skipWhiteSpaces(const std::string& json) const
{
    std::string* newJson = new std::string("");
    for(size_t i = 0; i < json.length();) {
        if(json[i] == '\"') {
            do {
                newJson->push_back(json[i++]);
            } while (json[i] == '\"');
        }
        if(json[i] == ' ') {
            i++;
            continue;
        }

        newJson->push_back(json[i++]);
    }
    return *newJson;
}

bool JsonValidator::validateAllBraces(const std::string& json) const 
{
    return this->validateBraces(json, BracesType::SIMPLE) 
        && this->validateBraces(json, BracesType::CURLY) 
        && this->validateBraces(json, BracesType::STRAIGHT);
}

bool JsonValidator::isArray(const std::string& json) const 
{
    return this->isNumbersArray(json) || this->isStringsArray(json) 
    || this->isBooleansArray(json) || this->isObjectsArray(json);
}

bool JsonValidator::validateKeys(const std::string& json) const 
{
    if (json.empty())
    {
        return false;
    }
    if(json.length() == 2 && json[0] == '{' && json[1] == '}') {
        return true;
    }

    bool isValid = false;
    std::string key = "";
    for (unsigned int i = 1; i < json.length() - 1;)
    {
        if (json[i] == '{' || json[i] == ' ' || json[i] == ',' 
            || json[i] == '\n' || json[i] == '}')
        {
            i++;
        } 
        else if(json[i] == '[') {
            i++;
        }
        else if (json[i] == '\"')
        {
            do
            {
                key += json[i++];
            } while (json[i] != ':');
            
            if(key[0] == '\"' && key[key.length() - 1] == '\"') {
                isValid = true;
            } else {
                isValid = false;
                break;
            }
            key = "";
            while(json[i] != '\n') {
                i++;
            }
        }
        else
        {
            isValid = false;
            break;
        }
    }

    return isValid;
}

bool JsonValidator::validateValues(const std::string& json) const 
{
    if(json.empty()) {
        return false;
    }
    if(json.length() == 2 && json[0] == '{' && json[1] == '}') {
        return true;
    }

    bool isValid = false;
    bool hasArray = false;
    std::string value = "";
    for (unsigned int i = 1; i < json.length() - 1;)
    {
        if (json[i] == '{' || json[i] == ' ' || json[i] == ',' 
            || json[i] == '\n' || json[i] == '}')
        {
            i++;
        }
        else if ((json[i] == '\"' && json[i - 1] == ':')
            || (this->isDigit(json[i]) && json[i - 1] == ':') 
            || (json[i] == '[' && json[i - 1] == ':')
            || (('a' <= json[i] && json[i] <= 'z') && json[i - 1] == ':'))
        {   
            if(json[i] == '[') {
                hasArray = true;
            }
            if(!hasArray) {
                do {   
                    if((json[i] == ',' && json[i + 1] == '\n') || json[i] == '\n') {
                        break;
                    }
                    value += json[i++];
                } while(true);
            } else {
                do {   
                    if((json[i] == ']' && json[i + 1] == ',')
                        || (json[i] == ']' && json[i + 1] == '\n')) {
                        value += json[i++];
                        break;
                    }
                    value += json[i++];
                } while (true);
                hasArray = false;
            }
            
            if((value[0] == '\"' && value[value.length() - 1] == '\"') 
                || this->isInteger(value) || this->isFloatingPoint(value) || value == "null" 
                || this->isObject(value) || value == "true" || value == "false" 
                || this->isArray(value)) {
                isValid = true;
            } else {
                isValid = false;
                break;
            }
            value = "";
            while(json[i] != ',' && json[i] != '\n') {
                i++;
            }
        }
        else
        {
            i++;
            continue;
        }
    }

    return isValid;
}

bool JsonValidator::validateSeparators(const std::string& json) const {
    if (json.empty())
    {
        return false;
    }
    if(json.length() == 2 && json[0] == '{' && json[1] == '}') {
        return true;
    }

    int separatorsCount = 0, keyValuePairsCount = 0;
    std::string key = "";
    bool hasArray = false;
    for (unsigned int i = 1; i < json.length() - 1;)
    {
        if (json[i] == '{' || json[i] == ' ' || json[i] == ',' 
            || json[i] == '\n' || json[i] == '}')
        {
            i++;
        } 
        else if (json[i] == '\"')
        {
            do
            {
                key += json[i++];
            } while (json[i] != ':');
            
            if(key[0] == '\"' && key[key.length() - 1] == '\"') {
                keyValuePairsCount++;
            } 
            key = "";
            i++;
            if(json[i] == '[') {
                hasArray = true;
            }
            if(!hasArray) {
                while(json[i] != ',') {
                    i++;
                }
                if(json[i] == ',') {
                    separatorsCount++;
                } 
            } else {
                while(json[i] != '\n') {
                    i++;
                }
                if(json[i] == '\n') {
                    separatorsCount++;
                }   
                hasArray = false;
            }
        } 
    }

    return separatorsCount + 1 == keyValuePairsCount || keyValuePairsCount == separatorsCount;
}