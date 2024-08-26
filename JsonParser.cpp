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
        std::cout << whites << " \"" << root->getKey() << "\": ";
        if (root->getType() == JsonValueType::STRING || root->getType() == JsonValueType::DATE)
        {
            std::cout << "\"" << root->getValue() << "\"";
        }
        else if (root->getType() == JsonValueType::INT 
            || root->getType() == JsonValueType::DOUBLE 
            || root->getType() == JsonValueType::BOOLEAN)
        {
            std::cout << root->getValue();
        }
        else if (root->getType() == JsonValueType::VALUE_ARRAY)
        {
            std::string whites = std::string(whiteSpaces + 1, ' ');
            std::cout << whites << "[ ";
            std::cout << whites << root->getValue().substr(1, root->getValue().length() - 2);
            std::cout << whites << " ]" << std::endl;
        }
        else if (root->getType() == JsonValueType::NULL_VALUE)
        {
            std::cout << "null";
        }
    } else {
        if (root->getType() == JsonValueType::OBJECT)
        {
            std::cout << " \"" << root->getKey() << "\": ";
            whiteSpaces = this->countWhitespaces(*root->getChildren()[0]);
            
            std::string whites = std::string(whiteSpaces + 1, ' ');
            std::cout << std::endl << whites << " {" << std::endl;
            this->printNode(root->getChildren()[0], whiteSpaces, out);
            std::cout << std::endl << whites << " }";
        } else {
        std::cout << " \"" << root->getKey() << "\": ";
        whiteSpaces = this->countWhitespaces(*root);
        if (root->getType() == JsonValueType::OBJECT_ARRAY)
        {
            std::string whites = std::string(whiteSpaces + 1, ' ');
            std::cout << std::endl
                      << whites << "[";
            std::string newWhites = std::string(whiteSpaces + 1, ' ');
            for (unsigned int i = 0; i < root->getChildren().size(); ++i)
            {
                whiteSpaces = this->countWhitespaces(*root->getChildren()[i]);
                std::cout << std::endl << newWhites << " {" << std::endl;
                this->printNode(root->getChildren()[i], whiteSpaces, out);
                if(i == root->getChildren().size() - 1) {
                    std::cout << std::endl << newWhites << " }" << std::endl;
                } else {
                    std::cout << std::endl << newWhites << " },";
                }
            }
            std::cout << whites << "]";
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

    std::cout << "," << std::endl;
    this->printNode(root->getNext(), whiteSpaces, out);
}
JsonParser::JsonParser(std::string filename)
{
    this->root = nullptr;
    this->filename = filename;
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
    while(temp->getNext()) {
        if(this->root->getKey() == key) {
            values.push_back(new JsonObject(this->root->getValue()));
        }
        temp->setNext(*root->getNext());
    }

    return values;
}
bool JsonParser::contains(const std::string& value) const
{
    JsonObject* obj = new JsonObject(value);
    JsonObject* temp = this->root;
    while(temp->getNext()) {
        if(this->root == obj) {
            return true;
        }
        temp->setNext(*this->root->getNext());
    }
    return false;
}
void JsonParser::setTo(const std::string& path, const std::string& json)
{
    JsonObject* temp = this->root;
    JsonObject* pathJsonObj = new JsonObject(path);
    JsonObject* newJsonObj = new JsonObject(json);
    while(temp->getNext()) {
        if(temp == pathJsonObj) {
            newJsonObj->setNext(*temp->getNext());
            pathJsonObj->setNext(*newJsonObj);
            temp->setNext(*pathJsonObj);
            break;
        }
        temp->setNext(*temp->getNext());
    }
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
        /*if(!this->validate(allData)) {
            throw std::invalid_argument("Read data not valid json!");
        }*/
        std::vector<std::string> keys;
        std::vector<std::string> currObjKeys;
        std::vector<std::string> values;
        std::string currKey, currValue;
        std::vector<std::string> currObjValues;
        bool hasChildren = false, isEndOfText = false;;
        for(int i = 0; i < allData.length();) {
            while(allData[i] != '\"') {
                if (allData[i] == '\0') {
                    isEndOfText = true;
                    break;
                }
                i++;
            }
            if(isEndOfText) {
                break;
            }
            while(!JsonValidator::isLetter(allData[i])) {
                currKey += allData[i++];
            }
            if(!hasChildren) {
                keys.push_back(currKey);
                currKey = "";
            } else {
                currObjKeys.push_back(currKey);
                currKey = "";
            }
            while(allData[i] != '\"' && allData[i] != '[' && allData[i] != '{') {
                i++;
            }
            if(allData[i] == '\"') {
                while(allData[i] != ',' && allData[i] != '\n') {
                    currValue += allData[i++];
                }
                if(!hasChildren) {
                    values.push_back(currValue);
                    currValue = "";
                } else {
                    currObjValues.push_back(currValue);
                    currValue = "";
                }
            } else if (allData[i] == '[') {
                /*if(allData[i + 1] == '{') {
                    hasChildren = true;
                    continue;
                } */
                while(allData[i] != ']') {
                    currValue += allData[i++];
                }
                if(!hasChildren) {
                    values.push_back(currValue);
                    currValue = "";
                } else {
                    currObjValues.push_back(currValue);
                    currValue = "";
                }
            } else {
                i++;
            }
        }

        JsonObject* tmp = nullptr;
        for (int i = 0; i < keys.size(); ++i) {
            JsonObject* newNode = new JsonObject(JsonValueType::STRING, keys[i], values[i], std::vector<JsonObject*>(), nullptr);
            if (i == 0) {
                this->root = newNode;
                tmp = this->root;
            } else {
                tmp->setNext(*newNode); 
                tmp = newNode;
            }
        }
    } catch(std::exception&) {
        this->root = nullptr;
    }
    in.close();
}
void JsonParser::close(std::string filename)
{
    std::ofstream out(filename);
    if(out) {
        out.close();
    }
}
int JsonParser::exit()
{
    std::ofstream out(this->filename);
    if(out) {
        out.close();
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