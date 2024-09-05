#include "JsonParser.h"

/// @brief a method that copies a definite JsonParser object
/// @param other the copied JsonParser object
/// @author Petya Licheva - pety02
void JsonParser::copy(const JsonParser& other)
{
    this->root = other.root;
    this->filename = other.filename;
}

/// @brief a method that destroys the current JsonParser object
/// @author Petya Licheva - pety02
void JsonParser::destroy()
{
    delete this->root;
}

/// @brief a method that returns the type of a definite JsonObject by its value validation
/// @param value the value of a JsonObject
/// @return the type of a definite JsonObject by its value validation
/// @author Petya Licheva - pety02
JsonValueType JsonParser::getType(std::string value) const
{
    if(JsonValidator::isInteger(value)) {
        return JsonValueType::INT;
    } else if (JsonValidator::isFloatingPoint(value)) {
        return JsonValueType::DOUBLE;
    } else if (JsonValidator::isDate(value)) {
        return JsonValueType::DATE;
    } else if (value == "true" || value == "false") {
        return JsonValueType::BOOLEAN;
    } else if (JsonValidator::isIntegersArray(value) || JsonValidator::isFloatingPointsArray(value) 
        || JsonValidator::isBooleansArray(value) || JsonValidator::isDatesArray(value) 
        || JsonValidator::isStringsArray(value)) {
        return JsonValueType::VALUE_ARRAY;
    } else if (JsonValidator::isObject(value)) {
        return JsonValueType::OBJECT;
    } else if (JsonValidator::isObjectsArray(value)) {
        return JsonValueType::OBJECT_ARRAY;
    } else {
        return JsonValueType::STRING;
    }
}

/// @brief a method that counts the whitespaces needed for pretty print of the JsonObject
/// @param root the definite JsonObject
/// @return the count of the whitespaces needed for pretty print of the JsonObject
/// @author Petya Licheva - pety02
int JsonParser::countWhitespaces(const JsonObject &root) const
{
    int newWhiteSpaces = 1;
    if(root.getValue() == "" && root.getType() != JsonValueType::OBJECT) {
        if(root.getNext() != nullptr) {
            newWhiteSpaces = std::min(root.getNext()->getKey().length(), root.getKey().length()) + 1;
        } else {
            newWhiteSpaces = root.getKey().length() + 1;
        }
    } else if(root.getValue() != "") {
        newWhiteSpaces = root.getKey().length() + 1;
    } else if(root.getValue() == "" && root.getType() == JsonValueType::OBJECT) {
        newWhiteSpaces = std::min(root.getNext()->getKey().length(), root.getKey().length()) + 3;
    }
    
    return newWhiteSpaces;
}

/// @brief a method that finds a node and its parent by a definite path
/// @param path the definite path
/// @return the node and its parent that stays on the definite path
/// @author Petya Licheva - pety02
std::pair<JsonObject*, JsonObject*> JsonParser::findNodeAndParent(const std::string& path) {
    std::stringstream ss(path);
    std::string key;
    JsonObject* parent = nullptr;
    JsonObject* current = root;
    while (std::getline(ss, key, '/')) {
        bool found = false;
        for (JsonObject* child : current->getChildren()) {
            if (child->getKey() == key) {
                parent = current;
                current = child;
                found = true;
                break;
            }
        }
        if (!found) {
            return {nullptr, nullptr}; // Path does not exist
        }
    }
    return {current, parent};
}

/// @brief a method that prints a node of JsonObject class
/// @param root the node of JsonObject class
/// @param whiteSpaces the count of needed whitespaces for pretty ptint
/// @param out the ostream in which the JsonObject will be printted
/// @author Petya Licheva - pety02
void JsonParser::printNode(JsonObject* root, int& whiteSpaces, std::ostream& out) const
{
    if (root == nullptr)
    {
        return;
    }

    if (root->getValue() != "")
    {
        std::string whites = std::string(whiteSpaces, ' ');
        out << whites << " \"" << root->getKey() << "\": ";
        if (root->getType() == JsonValueType::STRING || root->getType() == JsonValueType::DATE)
        {
            out << "\"" << root->getValue() << "\"";
        }
        else if (root->getType() == JsonValueType::INT 
            || root->getType() == JsonValueType::DOUBLE 
            || root->getType() == JsonValueType::BOOLEAN)
        {
            out << root->getValue();
        }
        else if (root->getType() == JsonValueType::VALUE_ARRAY)
        {
            std::string whites = std::string(whiteSpaces + 1, ' ');
            out << whites << "[ ";
            out << whites << root->getValue().substr(1, root->getValue().length() - 2);
            out << whites << " ]" << std::endl;
        }
        else if (root->getType() == JsonValueType::NULL_VALUE)
        {
            out << "null";
        } 
    } else {
        if (root->getType() == JsonValueType::OBJECT)
        {
            out << " \"" << root->getKey() << "\": ";
            whiteSpaces = this->countWhitespaces(*root->getChildren()[0]);
            
            std::string whites = std::string(whiteSpaces + 1, ' ');
            out << std::endl << whites << " {" << std::endl;
            this->printNode(root->getChildren()[0], whiteSpaces, out);
            out << std::endl << whites << " }";
        } else {
        out << " \"" << root->getKey() << "\": ";
        whiteSpaces = this->countWhitespaces(*root);
        if (root->getType() == JsonValueType::OBJECT_ARRAY)
        {
            std::string whites = std::string(whiteSpaces + 1, ' ');
            out << std::endl << whites << "[";
            std::string newWhites = std::string(whiteSpaces + 1, ' ');
            for (unsigned int i = 0; i < root->getChildren().size(); ++i)
            {
                whiteSpaces = this->countWhitespaces(*root->getChildren()[i]);
                out << std::endl << newWhites << " {" << std::endl;
                this->printNode(root->getChildren()[i], whiteSpaces, out);
                if(i == root->getChildren().size() - 1) {
                    out << std::endl << newWhites << " }" << std::endl;
                } else {
                    out << std::endl << newWhites << " },";
                }
            }
            out << whites << "]";
        }
        else if (root->getType() == JsonValueType::OBJECT)
        {
            this->printNode(root->getChildren()[0], whiteSpaces, out);
        }
        }
    }

    if (root->getNext() == nullptr)
    {
        return;
    }

    out << "," << std::endl;
    this->printNode(root->getNext(), whiteSpaces, out);
}

/// @brief a helper method that do the checks for the contains method
/// @param value the checked value
/// @param obj the JsonObject in which checks for this value
/// @return true if the current JsonObject contains this value and false if not
/// @author Petya Licheva - pety02
bool JsonParser::containsHelper(const std::string value, JsonObject *obj) const
{
    JsonObject* temp = obj;
    while(temp) {
        JsonValueType currentType = this->getType(temp->getValue());
        if((currentType == JsonValueType::NULL_VALUE || currentType == JsonValueType::INT 
            || currentType == JsonValueType::DOUBLE || currentType == JsonValueType::DATE
            || currentType == JsonValueType::BOOLEAN) && temp->getValue() == value) {
            return true;
        } else if (currentType == JsonValueType::VALUE_ARRAY) {
            std::string vals = temp->getValue();
            std::string val = "";
            for(int i = 0; i < vals.length(); ++i) {
                if(vals[i] == '[' || vals[i] == ']' || vals[i] == ' ') {
                    continue;
                }
                if(vals[i] == ',') {
                    if(val == value) {
                        return true;
                    }
                    val = "";
                    continue;
                }
                val += vals[i];
            }
        } else if (currentType == JsonValueType::OBJECT) {
            if(containsHelper(value, temp->getChildren()[0])) {
                return true;
            }
        } else if (currentType == JsonValueType::OBJECT_ARRAY) {
            for(int i = 0; i < temp->getChildren().size(); ++i) {
                if(containsHelper(value, temp->getChildren()[i])) {
                    return true;
                }
            }
        } else if(currentType == JsonValueType::STRING) {
            std::string val = temp->getValue();
            if(val.length() < value.length()) {
                temp = temp->getNext();
                continue;
            }
            for(int i = 0; i < val.length(); ++i) {
                if(val[i] == value[i]) {
                    if(val.length() - i < value.length()) {
                        continue;
                    }
                    val = val.substr(i, value.length());
                    if(val == value) {
                        return true;
                    }
                }
            }
        } else {
            temp = temp->getNext();
            continue;
        }
        temp = temp->getNext();
    }
    return false;
}

/// @brief a method that initializes a JsonObject of a definite string
/// @param allData the definite string
/// @return the initilized JsonObject
/// @throw std::invalid_argument with a custom message on invalid json string format
/// @author Petya Licheva - pety02
JsonObject* JsonParser::createFromJsonString(std::string allData)
{
    if(!this->validate(allData)) {
        throw std::invalid_argument("Read data not valid json!");
    }
    std::vector<std::string> keys;
    std::vector<std::string> currObjKeys, currObjValues;
    std::vector<std::string> values;
    std::string currKey, currValue;
    std::vector<std::vector<std::string>> currObjsValues;
    std::vector<std::vector<JsonObject*>> objsVecs;
    JsonValueType currentType;

    JsonObject* newNode = nullptr;
    JsonObject* tmp = nullptr;
    JsonObject* newNode2 = nullptr;
    int nextIndex = 0;

    bool hasChildren = false, isEndOfText = false;
    for(int i = 0; i < allData.length();) {
        while(!JsonValidator::isLetter(allData[i])) {
            if (allData[i] == '\0') {
                isEndOfText = true;
                break;
            }
            i++;
        }
        if(isEndOfText) {
            break;
        }
        while(allData[i] != '\"') {
            currKey += allData[i++];
        }

        if(!hasChildren) {
            keys.push_back(currKey);
            i++;
        } 
        while(allData[i] != '\"' && allData[i] != '[' && allData[i] != '{' && !JsonValidator::isDigit(allData[i])) {
            i++;
        }
        if(allData[i] == '\"') {
            currentType = JsonValueType::STRING;
            i++;
            while(allData[i] != '\"') {
                currValue += allData[i++];
            }
            
            values.push_back(currValue);
            if(newNode == nullptr) {
                newNode = new JsonObject(currentType, currKey, currValue, std::vector<JsonObject*>(), nullptr);
                tmp = newNode; 
            } else {
                newNode2 = new JsonObject(currentType, currKey, currValue, std::vector<JsonObject*>(), nullptr);
                tmp->setNext(*newNode2);
                tmp = tmp->getNext();
            }
            currKey = "";
            currValue = "";
            i++; 
        } else if (allData[i] == '[') {
            while(allData[i] != '\"' && !JsonValidator::isLetter(allData[i]) && !JsonValidator::isDigit(allData[i]) 
                && !JsonValidator::isLetter(allData[i]) && allData[i] != '{') {
                i++;
            }
            if(allData[i] == '{') {
                currentType = JsonValueType::OBJECT_ARRAY;
                std::vector<JsonObject*> objects = std::vector<JsonObject*>();
                while(allData[i] != ']') {
                    if(allData[i] == '}') {
                        currValue += allData[i];
                        JsonObject* currentObject = this->createFromJsonString(currValue);
                    
                        objects.push_back(currentObject);
                        currValue = "";
                        i++;
                        while(allData[i] != '{' && allData[i] != ']') {
                            i++;
                        }
                    } else {
                        currValue += allData[i++];
                    }
                }
                objsVecs.push_back(objects);
                currObjsValues.push_back(currObjValues);
                if(newNode == nullptr) {
                    newNode = new JsonObject(currentType, currKey, currValue, objsVecs[nextIndex++], nullptr); 
                    tmp = newNode;
                } else {
                    newNode2 = new JsonObject(currentType, currKey, currValue, objsVecs[nextIndex++], nullptr); 
                    tmp->setNext(*newNode2);
                    tmp = tmp->getNext();
                }
                currKey = "";
                currValue = "";
                i++;
            } else {
                currentType = JsonValueType::VALUE_ARRAY;
                while(allData[i] != ']') {
                    if(allData[i] == ',') {
                        currObjValues.push_back(currValue);
                        currValue = "";
                        i++;
                        continue;
                    }
                    currValue += allData[i++];
                }
                currObjsValues.push_back(currObjValues);
                if(newNode == nullptr) {
                    newNode = new JsonObject(currentType, currKey, currValue, std::vector<JsonObject*>(), nullptr); 
                    tmp = newNode;
                } else {
                    newNode2 = new JsonObject(currentType, currKey, currValue, std::vector<JsonObject*>(), nullptr);
                    tmp->setNext(*newNode2);
                    tmp = tmp->getNext();
                }
                currKey = "";
                currValue = "";
                i++;
            }
        } else if (allData[i] == '{') {
            currentType = JsonValueType::OBJECT;
            while((allData[i] != '}' && allData[i + 1] != ',') || (allData[i] != '}' && allData[i + 1] != '\n')) {
                currValue += allData[i++];
            }
            currValue += allData[i]; // sub-object 
            std::vector<JsonObject*> vec = std::vector<JsonObject*>();
            JsonObject* obj = this->createFromJsonString(currValue);
            values.push_back(currValue);
            vec.push_back(obj);
            objsVecs.push_back(vec);
            if(newNode == nullptr) {
                newNode = new JsonObject(currentType, currKey, "", objsVecs[nextIndex++], nullptr); 
                tmp = newNode;
            } else {
                newNode2 = new JsonObject(currentType, currKey, "", objsVecs[nextIndex++], nullptr);
                tmp->setNext(*newNode2);
                tmp = tmp->getNext();
            }
            currKey = "";
            currValue = "";
            i++;
        } else if (JsonValidator::isDigit(allData[i])) {
            while(allData[i] != ',' && allData[i] != '\n') {
                currValue += allData[i++];
            }
            currentType = this->getType(currValue);
            values.push_back(currValue);
            currentType = this->getType(currValue);
            if(newNode == nullptr) {
                newNode = new JsonObject(currentType, currKey, currValue, std::vector<JsonObject*>(), nullptr); 
                tmp = newNode;
            } else {
                newNode2 = new JsonObject(currentType, currKey, currValue, std::vector<JsonObject*>(), nullptr);
                tmp->setNext(*newNode2);
                tmp = tmp->getNext();
            }
            currKey = "";
            currValue = "";
            i++;
        } else {
            i++;
        }
    }

    return newNode;
}

/// @brief a method that splits a string by definite separator
/// @param sep the definite separator 
/// @param str the definite string
/// @return a vector of splitted substrings
/// @author Petya Licheva - pety02
std::vector<std::string> JsonParser::splitBy(char sep, const std::string &str)
{
    std::vector<std::string> vals = std::vector<std::string>();
    std::string currValue = "";
    for(int i = 0; i <= str.length(); ++i) {
        if(str[i] == sep || str[i] == '\0') {
            vals.push_back(currValue);
            currValue = "";
            continue;
        }
        currValue += str[i];
    }

    return vals;
}

/// @brief a method that finds json subobjects by a definite key in a definite JsonObject 
/// @param key a definite key
/// @param root a definite root JsonObject's pointer
/// @param index a definite index (nesting level)
/// @return a pointer to the found JsonObject
/// @author Petya Licheva - pety02
JsonObject *JsonParser::findBy(const std::string &key, JsonObject *root, int index = 0)
{   
    JsonObject* value = nullptr;
    JsonObject* temp = root;
    while(temp) {
        if(temp->getKey() == key) {
            JsonValueType currentType = temp->getType();
            value = new JsonObject(currentType, temp->getKey(), temp->getValue(), temp->getChildren(), temp->getNext());
            break;
        }
        temp = temp->getNext();
    }
   
    return value; 
}

/// @brief Default constructor of JsonParser class
/// @author Petya Licheva - pety02
JsonParser::JsonParser()
{
    this->root = nullptr;
    this->filename = "";
}

/// @brief Constructor with one parameter of JsonParser class
/// @param root the root JsonObject class's object
/// @author Petya Licheva - pety02
JsonParser::JsonParser(const JsonObject &root)
{
    this->root = new JsonObject(root);
}

/// @brief Copy constructor of JsonParser class
/// @param root the copied JsonParser object
/// @author Petya Licheva - pety02
JsonParser::JsonParser(const JsonParser &other)
{
    this->copy(other);
}

/// @brief Move copy constructor of JsonParser class
/// @param other the moved JsonParser object
/// @author Petya Licheva - pety02
JsonParser::JsonParser(JsonParser &&other) noexcept
{
    this->copy(other);
    other.filename = "";
    other.root = nullptr;
}

/// @brief Assignment operator of JsonParser class 
/// @param other the assigned JsonParser object
/// @return a reference to the current JsonParser
/// @author Petya Licheva - pety02
JsonParser &JsonParser::operator=(const JsonParser& other)
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

/// @brief Move assignment operator of JsonParser class 
/// @param other the assigned JsonParser object
/// @return a reference to the current JsonParser
/// @author Petya Licheva - pety02
JsonParser &JsonParser::operator=(JsonParser &&other) noexcept
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
        other.filename = "";
        other.root = nullptr;
    }

    return *this;
}

/// @brief Destructor of JsonParser class
/// @author Petya Licheva - pety02
JsonParser::~JsonParser()
{
    this->destroy();
}

/// @brief a validation method of a definite json string
/// @param json the definite json string
/// @return true if the string is in valid json format
/// @throw std::invalid_argument with a custom message if the json string is not valid 
/// @author Petya Licheva - pety02
bool JsonParser::validate(const std::string& json) const
{
    bool isValid = JsonValidator::isObject(json);
    if(isValid == true) {
        return isValid;
    }
    if (!JsonValidator::validateAllBraces(json))
    {
        throw std::invalid_argument("Braces error: Please, check all opening and closing braces!");
    }
    if (!JsonValidator::validateKeys(json))
    {
        throw std::invalid_argument("Keys error: Please, check if all your keys' values are written in inverted commas!");
    }
    if (!JsonValidator::validateValues(json))
    {
        throw std::invalid_argument("Values error: Please, check all your values syntax! Numbers, booleans and null values should be written without inverted commas. Arrays should be written in [] and all element should be separated by a comma. Strings should be written in inverted commas.");
    }
    if(!JsonValidator::validateSeparators(json)) {
        throw std::invalid_argument("Separators error: Please, check if all separators are put on the right place!");
    }

    throw std::invalid_argument("Invalid json string!");
}

/// @brief Prints the current JsonObject with a pretty print
/// @param out the ostream in which the current JsonObject will be printted
/// @author Petya Licheva - pety02
void JsonParser::print(std::ostream& out) const
{
    out << "{" << std::endl;
    int whiteSpaces = 0;
    this->printNode(this->root, whiteSpaces, out);
    out << std::endl
              << "}";
}

/// @brief a method that searches JsonObjects by a definite key
/// @param key the definite key
/// @return a vector of found JsonObjects
/// @author Petya Licheva - pety02
std::vector<JsonObject*> JsonParser::searchBy(const std::string& key) const
{
    std::vector<JsonObject*> values = std::vector<JsonObject*>();
    JsonObject* temp = this->root;
    while(temp) {
        if(temp->getKey() == key) {
            JsonValueType currentType = this->getType(temp->getValue());
            values.push_back(new JsonObject(currentType, temp->getKey(), temp->getValue(), std::vector<JsonObject*>(), temp->getNext()));
        }
        temp = temp->getNext();
    }

    return values;
}

/// @brief a method that checks if a value is contained in the current JsonObject
/// @param value the checked value
/// @return true if the current JsonObject contains this value and false if not
/// @author Petya Licheva - pety02
bool JsonParser::contains(std::string value) const
{
    return containsHelper(value, this->root);
}

/// @brief a method that sets a JsonObject on a definite path
/// @param path the definite path
/// @param json the JsonObject as string
/// @throw std::runtime_error with a custom message if the path is not found
/// @author Petya Licheva - pety02
void JsonParser::setTo(const std::string &path, const std::string &value)
{
    // TODO: to think if I have an array of objects how to identify in which object to add the given value
    if(!JsonValidator::isInteger(value) && !JsonValidator::isFloatingPoint(value) && !JsonValidator::isDate(value) 
        && !JsonValidator::isArray(value) && !JsonValidator::isObject(value) && value != "true" && value != "false" 
        && !JsonValidator::isString(value)) {
            throw std::invalid_argument("Invalid value!");
    }
    
    std::vector<std::string> keys = this->splitBy('/', path);
    for(int i = 0; i < keys.size(); ++i) {
        std::cout << "Key " << i + 1 << ": " << keys[i] << std::endl;
    }

    JsonObject* obj = this->findBy(keys[0], this->root);
    int index = 0;

    JsonObject* temp = nullptr;
    for(int i = 1; i < keys.size(); ++i) {
        JsonObject* obj2 = nullptr;
        if(obj->getNext() != nullptr) {
            obj2 = this->findBy(keys[i], obj);
        } else {
            obj2 = this->findBy(keys[i], obj->getChildren()[index]);
            index++;
        }

        if(temp == nullptr) {
            temp = new JsonObject(*obj2);
        } else {
            temp->setNext(*obj2);
        }
        temp = temp->getNext();

        if(obj != obj2) {
            obj = obj2;
        }
    }

    obj->setValue(value);
    JsonObject* rootTemp = this->root;
    JsonObject* newRoot = nullptr;
    JsonObject* newNode = new JsonObject(rootTemp->getType(), rootTemp->getKey(), rootTemp->getValue(), rootTemp->getChildren(), rootTemp->getNext());
    if(newRoot == nullptr) {
        this->root = newNode;
        newRoot = this->root;
        rootTemp = rootTemp->getNext();
    } else {
        newRoot->setNext(*newNode);
        newRoot = newRoot->getNext();
        rootTemp = rootTemp->getNext();
    }
    while(rootTemp != nullptr) {
        newNode = new JsonObject(rootTemp->getType(), rootTemp->getKey(), rootTemp->getValue(), rootTemp->getChildren(), rootTemp->getNext());
        if(rootTemp->getKey() == obj->getKey()) {
            newRoot->setNext(*obj);
        } else if(rootTemp->getType() == JsonValueType::OBJECT || rootTemp->getType() == JsonValueType::OBJECT_ARRAY) {
            bool isBroken = false;
            for(int i = 0; i < rootTemp->getChildren().size(); ++i) {
                JsonObject* currObj = rootTemp->getChildren()[i];
                while(currObj != nullptr) {
                    if(currObj->getKey() == obj->getKey()) {
                        currObj->setValue(obj->getValue());
                        rootTemp->getChildren()[i] = currObj;
                        isBroken = true;
                        break;
                    }
                    currObj = currObj->getNext();
                }
                if(isBroken) {
                    break;
                }
            }
        } else {
            newRoot->setNext(*newNode);
        }

        newRoot = newRoot->getNext();
        rootTemp = rootTemp->getNext();
    }
}

/// @brief 
/// @param 
/// @param
/// @throw
/// @author Petya Licheva - pety02
void JsonParser::createPath(const std::string& path, const std::string& json)
{
    
}

/// @brief 
/// @param path 
/// @author Petya Licheva - pety02
void JsonParser::deletePath(const std::string& path)
{
    
}

/// @brief 
/// @param fromPath 
/// @param toPath 
/// @author Petya Licheva - pety02
void JsonParser::move(const std::string& fromPath, std::string& toPath)
{
    
}

/// @brief a method that opens a file by its filename and initialize the current 
///        JsonObject via the createFromJsonString method
/// @param filename the definite filenme 
/// @throw std::runtime_error with a custom message if the file cannot be opened
/// @author Petya Licheva - pety02
void JsonParser::open(std::string filename)
{
    this->filename = filename; // set the filename to know the current file 
    std::ifstream in(filename);
    if(!in) {
        throw std::runtime_error("Cannot open the file for writing!");
    }

    std::string allData;
    try {
        while(in.good()) {
            const int maxLineChars = 256;
            char readData[maxLineChars];
            in.getline(readData, maxLineChars);
            allData += readData;
            allData += '\n';
        }
        
        this->root = this->createFromJsonString(allData);
    } catch(std::exception&) {
        this->root = nullptr;
    }
    in.close();
}

/// @brief a method that asks the user of he/she want to save the changes and if the user wants
///       then the method save them and exit the progam, if not the method only exit the program
/// @return the exit code of the program (0 on success and, -1 on exception)
/// @author Petya Licheva - pety02
int JsonParser::exit()
{
    std::cout << std::endl << std::endl << "Would you want to save all changes?" 
        << std::endl << std::endl << "Y/N" << std::endl << "> ";
    char option;
    do {
        std::cin >> option;
    } while (option != 'Y' && option != 'N');

    if(option == 'Y') {
        try {
            if(this->filename == "") {
                std::cout << "Enter filename: ";
                std::cin >> this->filename;
            }
            this->save();
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            return -1;
        }
    } else {
        return 0;   
    }
}

/// @brief a method that saves the current JsonObject in the current file 
/// @throw std::runtime_error with a custom message when the file cannot be oppened
/// @author Petya Licheva - pety02
void JsonParser::save() const
{
    try {
        this->saveAs(this->filename);
    } catch (std::exception&) {
        throw;
    }
}

/// @brief a method that saves the current JsonObject in a definite file
/// @param filename the definite file's filename
/// @throw std::runtime_error with a custom message when the file cannot be oppened
/// @author Petya Licheva - pety02
void JsonParser::saveAs(const std::string& filename) const
{
    std::ofstream out(filename);
    if(!out) {
        throw std::runtime_error("Cannot open the file for writing!");
    }
    
    this->print(out);
    out.close();
}