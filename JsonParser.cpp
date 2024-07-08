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
    while(this->root->getNext()) {
        if(this->root->getKey() == key) {
            values.push_back(new JsonObject(this->root->getValue()));
        }
    }

    return values;
}
bool JsonParser::contains(const std::string& value) const
{
    return false;
}
void JsonParser::setTo(const std::string& path, const std::string& json)
{
}
void JsonParser::createPath(const std::string& path, const std::string& json)
{
}
void JsonParser::deletePath(const std::string& path)
{
}
void JsonParser::move(const std::string& fromPath, std::string& toPath)
{
}
void JsonParser::save(const std::string& path) const
{
}
void JsonParser::saveAs(const std::string& filename, const std::string& path) const
{
}