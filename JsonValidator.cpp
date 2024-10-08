#include "JsonValidator.h"

/// @brief skips all whiteSpaces in the json string 
/// @param json the definite json string
/// @return the json string with the skipped whiteSpaces
/// @author Petya Licheva - pety02
std::string& JsonValidator::skipWhiteSpaces(const std::string& json)
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

/// @brief validates that the char c is digit
/// @param c the definite char c
/// @return true if the char c is digit and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isDigit(char c)
{
    return '0' <= c && c <= '9';
}

/// @brief validates that the char c is letter
/// @param c the definite char c
/// @return true if the char c is letter and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isLetter(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

/// @brief validates the curly braces in the json string
/// @param json the definite json string
/// @return true if the json string contains valid curly braces and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateCurlyBraces(const std::string& json)
{
    // Here std::vector is used as std::stack
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
            braces.erase(braces.begin());
        }
    }

    return braces.size() == 0;
}

/// @brief validates the straight braces in the json string
/// @param json the definite json string
/// @return true if the json string contains valid straight braces and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateStraightBraces(const std::string& json)
{
    // Here std::vector is used as std::stack
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
            braces.erase(braces.begin());
        }
    }

    return braces.size() == 0;
}

/// @brief validates the braces in the json string
/// @param json the definite json string
/// @param braceType the type of the braces
/// @return true if the json string contains valid braces and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateBraces(const std::string& json, BracesType braceType) 
{
    switch (braceType)
    {
        case BracesType::CURLY:
            return JsonValidator::validateCurlyBraces(json);
        case BracesType::STRAIGHT:
            return JsonValidator::validateStraightBraces(json);
        default:
            return false;
    }
}

/// @brief validates the all braces in the json string
/// @param json the definite json string
/// @return true if in the definite json string all braces are valid and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateAllBraces(const std::string& json) 
{
    return JsonValidator::validateBraces(json, BracesType::CURLY) 
        && JsonValidator::validateBraces(json, BracesType::STRAIGHT);
}

/// @brief validates the json string is an integer
/// @param json the definite json string
/// @return true if the json string is an integer and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isInteger(const std::string& json) 
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
        if(json[i] == '-' && JsonValidator::isDigit(json[i + 1])) {
            signCount++;
        } else if (json[i] == '-' && !JsonValidator::isDigit(json[i + 1])) {
            return false;
        }
        if(json[i] == '-' && 1 < signCount) {
            return false;
        } 
        if (json[i] != '-' && !JsonValidator::isDigit(json[i]))
        {
            return false;
        }
    }

    return true;
}

/// @brief validates the json string is a floating point number
/// @param json the definite json string
/// @return true if the definite json string is a floating point number and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isFloatingPoint(const std::string& json) 
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
        if(json[i] == '-' && JsonValidator::isDigit(json[i + 1])) {
            signCount++;
        } else if (json[i] == '-' && !JsonValidator::isDigit(json[i + 1])) {
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
        if(json[i] != '-' && !JsonValidator::isDigit(json[i]) && json[i] != '.') {
            return false;
        }
    }

    return true;
}

/// @brief validates the json string is an ISO date
/// @param json the definite json string
/// @return true if the definite json string is an ISO date and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isISODateFormat(const std::string& json)
{
    if(json[4] != '-' || json[7] != '-') {
        return false;
    }
    return true;
}

/// @brief validates the json string is an USA date
/// @param json the definite json string
/// @return true if the definite json string is an USA date and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isUSADateFormat(const std::string& json)
{
    if(json[2] != '\\' || json[5] != '\\') {
        return false;
    }
    return true;
}

/// @brief validates the json string is an EUR date
/// @param json the definite json string
/// @return true if the definite json string is an EUR date and false if not
/// @author Petya Licheva - pety02 
bool JsonValidator::isEURDateFormat(const std::string& json)
{
    if(json[2] != '.' || json[5] != '.') {
        return false;
    }
    return true;
}

/// @brief validates the json string is a date
/// @param json the definite json string
/// @return true if the definite json string is a date and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isDate(const std::string& json)
{
    try {
        int year = 0, month = 0, date = 0;
        if(JsonValidator::isISODateFormat(json)) {
            year = std::atoi(json.substr(0, 4).c_str());
            month = std::atoi(json.substr(5,2).c_str());
            date = std::atoi(json.substr(8,2).c_str());
        } else if (JsonValidator::isUSADateFormat(json) 
            || JsonValidator::isEURDateFormat(json)) {
            year = std::atoi(json.substr(6, 4).c_str());
            month = std::atoi(json.substr(3,2).c_str());
            date = std::atoi(json.substr(0,2).c_str());
        } 

        if(year < 1900) {
            return false;
        }
        if(month < 1 || 12 < month) {
            return false;
        }
        if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
            && (date < 1 || 31 < date)) { // 31 days months
            return false;
        } else if((month == 4 || month == 6 || month == 9 || month == 11) 
            && (date < 1 || 30 < date)) { // 30 days months
            return false;
        } else { // special case of February
            if(year % 4 == 0 || year % 400 == 0) { // leap year
                if(month == 2 && (date < 1 || 29 < date)) {
                    return false;
                } 
            } else { // not leap year
                if(month == 2 && (date < 1 || 28 < date)) {
                    return false;
                } 
            }
        }

        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
    } catch (const std::exception& e) {
        return false;
    }
}

/// @brief validates the json string is an object
/// @param json the definite json string
/// @return true if the definite json string is an object and false if not
/// @author Petya Licheva - pety02 
bool JsonValidator::isObject(const std::string& json)
{
    std::string skippedWhites = JsonValidator::skipWhiteSpaces(json);
    bool isValid = skippedWhites == "null" || 
        (JsonValidator::validateAllBraces(skippedWhites)
        && JsonValidator::validateKeys(skippedWhites) 
        && JsonValidator::validateSeparators(skippedWhites) 
        && JsonValidator::validateValues(skippedWhites));

    return isValid;
}

/// @brief 
/// @param json 
/// @return 
/// @author
bool JsonValidator::isString(const std::string &json)
{
    return json[0] == '\"' && json[json.length() - 1] == '\"';
}

/// @brief validates all keys in the json string are valid
/// @param json the definite json string
/// @return true if the all keys in the json string are valid and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateKeys(const std::string& json) 
{
    // empty string 
    if (json.empty())
    {
        return false;
    }

    // valid emprty json object
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
            
            // chacks if all keys of not empty a json object is in inverted commas
            if(key[0] == '\"' && key[key.length() - 1] == '\"') {
                isValid = true;
            } else {
                isValid = false;
                break;
            }
            key = "";
            while(json[i] != '\n' && json[i] != '\0') {
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    return isValid;
}

/// @brief validates all values in the json string are valid
/// @param json the definite json string
/// @return true if the all values in the json string are valid and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateValues(const std::string& json)
{
    // empty string
    if(json.empty()) {
        return false;
    }

    // valid empty json object 
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
            || (JsonValidator::isDigit(json[i]) && json[i - 1] == ':') 
            || (json[i] == '[' && json[i - 1] == ':')
            || (('a' <= json[i] && json[i] <= 'z') && json[i - 1] == ':')) // needs only lowercases
        {   
            if(json[i] == '[') {
                hasArray = true;
            }
            if(!hasArray) {
                do {   
                    if((json[i] == ',' && json[i + 1] == '\n') || json[i] == '\n' || json[i] == '\0') {
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
            
            // checks if the json object's value is valid value or not
            if((value[0] == '\"' && value[value.length() - 1] == '\"') 
                || JsonValidator::isInteger(value) 
                || JsonValidator::isFloatingPoint(value) || value == "null" 
                || JsonValidator::isObject(value) || value == "true" || value == "false" 
                || JsonValidator::isArray(value)
                || JsonValidator::isDate(value)) {
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

/// @brief validates all separators in the json string are valid
/// @param json the definite json string
/// @return true if the all separators in the json string are valid and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::validateSeparators(const std::string& json) 
{
    // empty string
    if (json.empty())
    {
        return false;
    }

    // valid emprty json object
    if(json.length() == 2 && json[0] == '{' && json[1] == '}') {
        return true;
    }

    int separatorsCount = 0, keyValuePairsCount = 0;
    std::string key = "";
    bool hasArray = false;
    for (int i = 1; i < json.length() - 1;)
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
                    if(i == json.length() - 2) {
                        break;
                    }
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

    // checks if the separators count is valid or not in comparison with key-value pairs count
    return separatorsCount + 1 == keyValuePairsCount || keyValuePairsCount == separatorsCount;
}

/// @brief validates the json string is an integer array
/// @param json the definite json string
/// @return true if the definite json string is an integer array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isIntegersArray(const std::string& json) 
{
    // checks if the array starts with '[' and ends with ']' 
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
        // checks if every read number is an integer
        if (json[i] != '-' && !JsonValidator::isInteger(readed))
        {
            return false;
        }
        readed = "";
    }

    return true;
}

/// @brief validates the json string is a floting points array
/// @param json the definite json string
/// @return true if the definite json string is a floating points array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isFloatingPointsArray(const std::string& json) 
{
    // checks if the array starts with '[' and ends with ']' 
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
        // check if every read number is a floating point
        if (!JsonValidator::isFloatingPoint(readed))
        {
            return false;
        }
        readed = "";
    }

    return true;
}

/// @brief validates the json string is a number array
/// @param json the definite json string
/// @return true if the definite json string is a number array and false if not
/// @author Petya Licheva - pety02 
bool JsonValidator::isNumbersArray(const std::string& json)
{
    return JsonValidator::isIntegersArray(json) || JsonValidator::isFloatingPointsArray(json);
}

/// @brief validates the json string is a date array
/// @param json the definite json string
/// @return true if the definite json string is a date array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isDatesArray(const std::string& json)
{
    // checks if the array starts with '[' and ends with ']'
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
        // checks if every read value is a date
        if (!JsonValidator::isDate(readed))
        {
            return false;
        }
        readed = "";
    }

    return true;
}

/// @brief validates the json string is an objects array
/// @param json the definite json string
/// @return true if the definite json string is an objects array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isObjectsArray(const std::string& json) 
{
    // checks if the array starts with '[' and ends with ']'
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
        // checks if every read value is a valid json object
        if (!JsonValidator::isObject(readedAsString) && readedAsString != "null")
        {
            return false;
        }
        readed = new char[values.length()];
        readFrom = 0;
    }

    return true;
}

/// @brief validates the json string is a string array
/// @param json the definite json string
/// @return true if the definite json string is a string array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isStringsArray(const std::string& json)
{
    // checks if the array starts with '[' and ends with ']'
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
        // checks if every read value starts and ends with '\"'
        if (readed[0] != '\"' || readed[readFrom - 1] != '\"')
        {
            return false;
        }
        readed = new char[values.length()];
        readFrom = 0;
    }

    return true;
}

/// @brief validates the json string is a boolean array
/// @param json the definite json string
/// @return true if the definite json string is a boolean array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isBooleansArray(const std::string& json)
{
    // checks if the array starts with '[' and ends with ']'
    if (json[0] != '[' || json[json.length() - 1] != ']')
    {
        return false;
    }
    unsigned int size = json.length();
    std::string values = json.substr(1, size - 2);
    std::string readed = "";
    for (unsigned int i = 0; i < values.length();)
    {
        while (!JsonValidator::isLetter(json[i]))
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
        i++;
        // checks if evry read value is "true" or "false"
        if (readed != "true" && readed != "false")
        {
            return false;
        }
        readed = "";
    }

    return true;
}

/// @brief validates the json string is an array
/// @param json the definite json string
/// @return true if the definite json string is an array and false if not
/// @author Petya Licheva - pety02
bool JsonValidator::isArray(const std::string& json) 
{
    return JsonValidator::isNumbersArray(json) 
        || JsonValidator::isStringsArray(json) 
        || JsonValidator::isBooleansArray(json) 
        || JsonValidator::isObjectsArray(json)
        || JsonValidator::isDatesArray(json);
}