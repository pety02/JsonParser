#include "JsonParser.h"

void JsonParser::copy(const JsonParser& other)
{
    this->root = other.root;
    this->filename = other.filename;
}
void JsonParser::destroy()
{
    delete this->root;
}
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
int JsonParser::countWhitespaces(const JsonObject &root) const
{
    int newWhiteSpaces = 1;
    if(root.getValue() == "" && root.getType() != JsonValueType::OBJECT) {
        if(root.getNext() != nullptr) {
            newWhiteSpaces = std::min(root.getNext()->getKey().length(), root.getKey().length()) + 1;
        } else {
            newWhiteSpaces = 11;
        }
    } else if(root.getValue() != "") {
        newWhiteSpaces = 10;
    } else if(root.getValue() == "" && root.getType() == JsonValueType::OBJECT) {
        newWhiteSpaces = 12;
    }
    
    return newWhiteSpaces;
}
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
JsonParser::JsonParser()
{
    this->root = nullptr;
    this->filename = "";
}
JsonParser::JsonParser(const JsonObject &root)
{
    this->root = new JsonObject(root);
}
JsonParser::JsonParser(JsonParser &&other) noexcept
{
    this->copy(other);
    other.root = nullptr;
}
JsonParser::JsonParser(const JsonParser &other)
{
    this->copy(other);
}
JsonParser &JsonParser::operator=(const JsonParser& other)
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
    }

    return *this;
}
JsonParser &JsonParser::operator=(JsonParser &&other) noexcept
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
        other.root = nullptr;
    }

    return *this;
}
JsonParser::~JsonParser()
{
    this->destroy();
}
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

    return false;
}
void JsonParser::print(std::ostream& out) const
{
    out << "{" << std::endl;
    int whiteSpaces = 0;
    this->printNode(this->root, whiteSpaces, out);
    out << std::endl
              << "}";
}
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
bool JsonParser::contains(std::string value) const
{
    return containsHelper(value, this->root);
}
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
JsonObject* JsonParser::createFromJsonString(std::string allData)
{
    JsonObject* obj = nullptr;
    if(!this->validate(allData)) {
        throw std::invalid_argument("Read data not valid json!");
    }
    std::vector<std::string> keys;
    std::vector<std::vector<std::string>> currObjsKeys;
    std::vector<std::string> currObjKeys, currObjValues;
    std::vector<std::string> values;
    std::string currKey, currValue;
    std::vector<std::vector<std::string>> currObjsValues;
    JsonValueType currentType;
    bool hasChildren = false, isEndOfText = false;;
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
            currKey = "";
            i++;
        } else {
            currObjKeys.push_back(currKey);
            currKey = "";
            i++;
        }
        while(allData[i] != '\"' && allData[i] != '[' && allData[i] != '{' && !JsonValidator::isDigit(allData[i])) {
            i++;
        }
        if(allData[i] == '\"') {
            i++;
            while(allData[i] != '\"') {
                currValue += allData[i++];
            }
            if(!hasChildren) {
                values.push_back(currValue);
                currValue = "";
                i++;
            } else {
                currObjValues.push_back(currValue);
                currValue = "";
                i++;
            }
        } else if (allData[i] == '[') {
            while(allData[i] != '\"' && !JsonValidator::isLetter(allData[i]) && !JsonValidator::isDigit(allData[i]) 
                && !JsonValidator::isLetter(allData[i]) && allData[i] != '{') {
                i++;
            }
            if(allData[i] == '{') {
                currentType = JsonValueType::OBJECT_ARRAY;
                while(allData[i] != ',') {
                    currValue += allData[i++];
                }
                hasChildren = true;
                continue;
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
            }
        } else if (JsonValidator::isDigit(allData[i])) {
            while(allData[i] != ',' && allData[i] != '\n') {
                currValue += allData[i++];
            }
            values.push_back(currValue);
            currValue = "";
        } else {
            i++;
        }
    }

    JsonObject* newNode = nullptr;
    if(currentType == JsonValueType::VALUE_ARRAY || currentType == JsonValueType::OBJECT_ARRAY) {
        std::string value = "[";
        for(int i = 0; i < currObjValues.size(); ++i) {
            if(i == currObjValues.size() - 1) {
                value += currObjValues[i];
                break;
            }
            value += currObjValues[i];
            value += ",";
        }
        value += "]";
        newNode = new JsonObject(currentType, keys[0], value, std::vector<JsonObject*>(), nullptr);
        currObjsValues.clear();
    } else {
        currentType = this->getType(values[0]);
        newNode = new JsonObject(currentType, keys[0], values[0], std::vector<JsonObject*>(), nullptr);
    }
    if (obj == nullptr) {
        obj = newNode;
    } 
    JsonObject* tmp = obj;
    for (int i = 1; i < keys.size(); ++i) {
        currentType = getType(values[i]);
        newNode = new JsonObject(currentType, keys[i], values[i], std::vector<JsonObject*>(), nullptr);
        tmp->setNext(*newNode); 
        tmp = tmp->getNext();
    }

    return obj;
}
void JsonParser::setTo(const std::string &path, const std::string &json)
{
    JsonObject* pathObj = this->createFromJsonString(path);
    JsonObject* readPathObj = pathObj;
    JsonObject* readRootObj = this->root;
    while(readPathObj->getNext() != nullptr && readRootObj->getNext() != nullptr) {
        if(readPathObj->getType() != readRootObj->getType() 
            || readPathObj->getKey() != readRootObj->getKey() 
            || readPathObj->getValue() != readRootObj->getValue()) {
            throw std::runtime_error("Path not found!");
        } 
        readPathObj = readPathObj->getNext();
        readRootObj = readRootObj->getNext();
    }

    JsonObject* newJsonObj = this->createFromJsonString(json);
    readRootObj->setNext(*newJsonObj);
}
void JsonParser::createPath(const std::string& json)
{
    JsonObject* newJsonObj = new JsonObject(json);
    this->root->setNext(*newJsonObj);
}
void JsonParser::deletePath(const std::string& path)
{
    JsonObject* temp = this->root;
    JsonObject* pathJsonObj = new JsonObject(path);
    while(temp->getNext()) {
        if(temp == pathJsonObj) {
            JsonObject* toBeDeleted = temp->getNext();
            temp->setNext(*toBeDeleted->getNext());
            delete toBeDeleted;
            break;
        }
        temp->setNext(*this->root->getNext());
    }
}
void JsonParser::move(const std::string& fromPath, std::string& toPath)
{
    auto [fromNode, fromParent] = findNodeAndParent(fromPath);
        auto [toNode, toParent] = findNodeAndParent(toPath);

        if (!fromNode || !toNode) {
            std::cerr << "Invalid path(s)" << std::endl;
            return;
        }

        // Swapping the nodes by adjusting the next pointers
        JsonObject* fromNext = fromNode->getNext();
        JsonObject* toNext = toNode->getNext();

        // If fromNode or toNode are direct children of their parents, adjust their parents' child pointers
        if (fromParent) {
            for (JsonObject*& child : fromParent->getChildren()) {
                if (child == fromNode) {
                    child = toNode;
                    break;
                }
            }
        }

        if (toParent) {
            for (JsonObject*& child : toParent->getChildren()) {
                if (child == toNode) {
                    child = fromNode;
                    break;
                }
            }
        }

        // Set the next pointers
        fromNode->setNext(*toNext);
        toNode->setNext(*fromNext);
}
void JsonParser::open(std::string filename)
{
    this->filename = filename; // set the filename to know the current file 
    std::ifstream in(filename);
    if(!in) {
        throw std::runtime_error("Cannot open the file for writing!");
    }
    // TODO: to initialize the object with the read data
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
int JsonParser::exit()
{
    std::cout << std::endl << std::endl << "Would you want to save all changes?" << std::endl << std::endl << "Y/N" << std::endl << "> ";
    char option;
    do {
        std::cin >> option;
    } while (option != 'Y' && option != 'N');

    if(option == 'Y') {
        this->save();
    } else {
        this->open(this->filename);
    }
    return 0;
}
void JsonParser::save() const
{
    std::ofstream out(this->filename);
    if(!out) {
        throw std::runtime_error("Cannot open the file for writing!");
    }
    this->print(out);
    out.close();
}
void JsonParser::saveAs(const std::string& filename) const
{
    std::ofstream out(filename);
    if(!out) {
        throw std::runtime_error("Cannot open the file for writing!");
    }
    // TODO: to make this path as JsonObject and to save it.
    this->print(out);
    out.close();
}