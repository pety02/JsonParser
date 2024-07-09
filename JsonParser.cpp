#include "JsonParser.h"

void JsonParser::copy(const JsonParser& other)
{
    this->root = other.root;
    this->validator = other.validator;
}
void JsonParser::destroy()
{
    delete this->root;
}
int JsonParser::countWhitespaces(const JsonObject &root) const
{
    return root.getKey().length() + 3;
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
void JsonParser::printNode(JsonObject* root, int& whiteSpaces) const
{
    if (root == nullptr)
    {
        return;
    }

    if (root->getValue() != "")
    {
        std::cout << " \"" << root->getKey() << "\": ";
        whiteSpaces = this->countWhitespaces(*root);
        if (root->getType() == JsonValueType::STRING)
        {
            std::cout << "\"" << root->getValue() << "\"";
        }
        else if (root->getType() == JsonValueType::INT || root->getType() == JsonValueType::DOUBLE || root->getType() == JsonValueType::BOOLEAN)
        {
            std::cout << root->getValue();
        }
        else if (root->getType() == JsonValueType::VALUE_ARRAY)
        {
            std::string whites = std::string(whiteSpaces + 1, ' ');
            std::cout << std::endl
                      << whites << "[" << std::endl;
            std::cout << whites << " " << root->getValue().substr(1, root->getValue().length() - 2);
            std::cout << std::endl
                      << whites << "]";
        }
        else if (root->getType() == JsonValueType::OBJECT_ARRAY)
        {
            std::string whites = std::string(whiteSpaces + 1, ' ');
            std::cout << std::endl
                      << whites << "[" << std::endl;
            for (unsigned int i = 0; i < root->getChildren().size(); ++i)
            {
                std::cout << whites << " ";
                this->printNode(root->getChildren()[i], whiteSpaces);
            }
            std::cout << std::endl
                      << whites << "]";
        }
        else if (root->getType() == JsonValueType::OBJECT)
        {
            this->printNode(root, whiteSpaces);
        }
        else if (root->getType() == JsonValueType::NULL_VALUE)
        {
            std::cout << "null";
        }
    }

    if (root->getNext() == nullptr)
    {
        return;
    }

    std::cout << "," << std::endl;
    this->printNode(root->getNext(), whiteSpaces);
}
JsonParser::JsonParser(const JsonObject& root)
{
    this->root = new JsonObject(root);
    this->validator = JsonValidator();
}
JsonParser::JsonParser(const JsonParser& other)
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
JsonParser::~JsonParser()
{
    this->destroy();
}
bool JsonParser::validate(const std::string& json) const
{
    if (!this->validator.validateAllBraces(json))
    {
        throw std::runtime_error("Braces error: Please, check all opening and closing braces!");
    }
    if (!this->validator.validateKeys(json))
    {
        throw std::runtime_error("Keys error: Please, check if all your keys' values are written in inverted commas!");
    }
    if (!this->validator.validateValues(json))
    {
        throw std::runtime_error("Values error: Please, check all your values syntax! Numbers, booleans and null values should be written without inverted commas. Arrays should be written in [] and all element should be separated by a comma. Strings should be written in inverted commas.");
    }
    if(!this->validator.validateKeyValueSeparators(json)) {
        throw std::runtime_error("Key Value pair separators error: Please, check if all key value pair separators are put on the right place!");
    }
    if(!this->validator.validateCommas(json)) {
        throw std::runtime_error("Commas error: Please, check if all key value pairs are written on the next line, separated by a comma!");
    }

    return true;
}
void JsonParser::print() const
{
    std::cout << "{" << std::endl;
    int whiteSpaces = 0;
    this->printNode(this->root, whiteSpaces);
    std::cout << std::endl
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
void JsonParser::save(const std::string& path) const
{
}
void JsonParser::saveAs(const std::string& filename, const std::string& path) const
{
}