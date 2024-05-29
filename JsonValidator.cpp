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
    {
        return this->validateSimpleBraces(json);
    }
    case BracesType::CURLY:
    {
        return this->validateCurlyBraces(json);
    }
    case BracesType::STRAIGHT:
    {
        return this->validateStraightBraces(json);
    }
    default:
    {
        return false;
    }
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

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if ((json[i] < '0' || '9' < json[i]))
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

    int dotsCount = 0;
    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (1 < dotsCount)
        {
            return false;
        }
        if (json[i] == '.')
        {
            dotsCount++;
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
        if (!this->isInteger(readed))
        {
            return false;
        }
        readed = new char[values.length()];
        readFrom = 0;
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
        if (!this->isFloatingPoint(readed))
        {
            return false;
        }
        readed = new char[values.length()];
        readFrom = 0;
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
    bool a = this->validateAllBraces(json);
    bool b = this->validateKeys(json);
    bool c = this->validateKeyValueSeparators(json); 
    //bool d = this->validateValues(json);
    bool e = this->validateCommas(json);

    return a && b && c && e;
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
    std::string& newJson = *new std::string("");
    int invertedCommasCount = 0;
    bool canBeSkipped = true;
    int index = 0;
    for(int i = 0; i < json.length() - 1;) {
        if(json[i] == '\"' && invertedCommasCount == 0) {
            canBeSkipped = false;
            invertedCommasCount++;
            i++;
            continue;
        } else if(json[i] == '\"' && invertedCommasCount > 0) {
            canBeSkipped = true;
            invertedCommasCount = 0;
        } 
        if(json[i] == ' ' && canBeSkipped) {
            i++;
            continue;
        }

        newJson += json[i++];
    }
    newJson += json[json.length() - 1];
    return newJson;
}
bool JsonValidator::validateAllBraces(const std::string& json) const 
{
    bool a = this->validateBraces(json, BracesType::SIMPLE);
    bool b = this->validateBraces(json, BracesType::CURLY);
    bool c = this->validateBraces(json, BracesType::STRAIGHT);

    return a && b && c;
}
bool JsonValidator::isArray(const std::string& json) const 
{
    return this->isNumbersArray(json) || this->isStringsArray(json) || this->isBooleansArray(json) || this->isObjectsArray(json);
}
// TODO: to think for better decision.
bool JsonValidator::validateKeys(const std::string& json) const 
{
    if (json.empty())
    {
        return true;
    }

    bool isValid = true;
    std::string newJson = json;
    for (unsigned int i = 1; i < newJson.length() - 1;)
    {
        if (newJson[i] == '{' || newJson[i] == ' ' || newJson[i] == ',' || newJson[i] == '\n' 
            || newJson[i] == '}' || newJson[i] == '[' || newJson[i] == ']')
        {
            i++;
            continue;
        }
        else if (newJson[i] == '\"')
        {
            while (newJson[i] != '\"')
            {
                i++;
            }
            std::string key = "" + newJson[i];
            do
            {
                if (newJson[i] == '\"' && newJson[i + 1] == ':')
                {
                    return true;
                } else {
                    isValid = false;
                    key += newJson[i++];
                }
            } while (newJson[i] != ':');
            unsigned int keySize = key.length();
            if (key[0] != '\"' || key[keySize - 1] != '\"')
            {
                return false;
            }
            while (newJson[i] != '\n')
            {
                i++;
            }
            key = "";
        }
        else
        {
            i++;
            continue;
        }
    }

    return isValid;
}
// TODO: to think fo better decision
bool JsonValidator::validateValues(const std::string& json) const 
{
    if (json.empty())
    {
        return true;
    }

    std::string newJson = json;
    for (unsigned int i = 1; i < json.length() - 1;)
    {
        if (newJson[i] = '{' || newJson[i] == ' ' || newJson[i] == ',' || newJson[i] == '}' || newJson[i] == '[' || newJson[i] == ']')
        {
            continue;
        }
        else if (newJson[i] == '\"')
        {
            while (newJson[i] != '\"')
            {
                i++;
            }
            std::string key = "";
            do
            {
                if (newJson[i] == '\0')
                {
                    break;
                }
                if (newJson[i] == '\"' && newJson[i + 1] != ':')
                {
                    return false;
                }
                i++;
            } while (newJson[i] != ':');
            while (newJson[i] == ' ')
            {
                i++;
            }
            do
            {
                if (newJson[i] == '\0')
                {
                    break;
                }
                key += newJson[i++];
            } while (newJson[i] != ',' && newJson[i + 1] != '\n');
            unsigned int keySize = key.length();
            if (this->isInteger(key) || this->isFloatingPoint(json) || this->isObject(key) || key == "null" || key == "true" || key == "false" || (key[0] == '\"' && key[keySize - 1] == '\"'))
            {
                return true;
            }
        }
        else
        {
            continue;
        }
    }

    return true;
}
bool JsonValidator::validateCommas(const std::string& json) const {
    /*std::string newJson = "";
    std::string skippedWhiteSpaces = this->skipWhiteSpaces(json, newJson);
    for(unsigned int i = 1; i < skippedWhiteSpaces.length(); ++i) {
        if((skippedWhiteSpaces[i - 1] == ',' && skippedWhiteSpaces[i] != '\n')
            || (skippedWhiteSpaces[i - 1] != ',' && skippedWhiteSpaces[i] == '\n')) {
            return false;
        }
    }*/
    return true;
}
bool JsonValidator::validateKeyValueSeparators(const std::string& json) const {
    /*std::string newJson = "";
    std::string skippedWhiteSpaces = this->skipWhiteSpaces(json, newJson);
    for(unsigned int i = 1; i < skippedWhiteSpaces.length(); ++i) {
        if(skippedWhiteSpaces[i - 1] != '\"' && skippedWhiteSpaces[i] == ':') {
            return false;
        }
    }*/
    return true;
}