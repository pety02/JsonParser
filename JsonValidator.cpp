#include "JsonValidator.h"

bool JsonValidator::validateSimpleBraces(std::string json) const
{
    std::vector<char> braces = std::vector<char>();
    char firstBrace = ' ';

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (json[i] == '(' || json[i] == ')')
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
bool JsonValidator::validateCurlyBraces(std::string json) const
{
    std::vector<char> braces = std::vector<char>();
    char firstBrace = ' ';

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (json[i] == '{' || json[i] == '}')
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
bool JsonValidator::validateStraightBraces(std::string json) const
{
    std::vector<char> braces = std::vector<char>();
    char firstBrace = ' ';

    for (unsigned int i = 0; i < json.length(); ++i)
    {
        if (json[i] == '[' || json[i] == ']')
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
bool JsonValidator::validateBraces(std::string json, BracesType braceType) const
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
bool JsonValidator::isInteger(std::string json) const
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
bool JsonValidator::isFloatingPoint(std::string json) const
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
bool JsonValidator::isIntegersArray(std::string json) const
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
bool JsonValidator::isFloatingPointsArray(std::string json) const
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
bool JsonValidator::isNumbersArray(std::string json) const
{
    return this->isIntegersArray(json) || this->isFloatingPointsArray(json);
}
bool JsonValidator::isStringsArray(std::string json) const
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
bool JsonValidator::isBooleansArray(std::string json) const
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
bool JsonValidator::isObject(std::string json) const
{
    return false;
}
bool JsonValidator::isObjectsArray(std::string json) const
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
bool JsonValidator::validateAllBraces(std::string json) const
{
    return this->validateBraces(json, BracesType::SIMPLE) && this->validateBraces(json, BracesType::CURLY) && this->validateBraces(json, BracesType::STRAIGHT);
}
bool JsonValidator::isArray(std::string json) const
{
    return this->isNumbersArray(json) || this->isStringsArray(json) || this->isBooleansArray(json) || this->isObjectsArray(json);
}
bool JsonValidator::validateKeys(std::string) const
{
    return false;
}
bool JsonValidator::validateCommas(std::string) const
{
    return false;
}
bool JsonValidator::validateValues(std::string) const
{
    return false;
}