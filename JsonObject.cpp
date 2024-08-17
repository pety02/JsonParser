#include "JsonObject.h"

void JsonObject::copy(const JsonObject &other)
{
    this->valueType = other.valueType;
    this->key = other.key;
    this->value = other.value;
    this->next = other.next;
    this->children.reserve(other.children.size());
    for (unsigned int index = 0; index < other.children.size(); ++index)
    {
        this->children.push_back(other.children[index]);
    }
}
void JsonObject::destroy()
{
    delete this->next;
    this->children.clear();
}
// TODO: to think how to implement it recursivelly.
JsonObject::JsonObject(const std::string& json)
{
    std::string key, value, read;
    for(unsigned int i = 1; i < json.length();) {
        do {
            read += json[i++];
        } while (json[i] != '\"');
        read = json[i];
        do {
            read += json[i++];
        } while (json[i] != ':');
        this->key = read.substr(1, read.length() - 1);
        read = "";
        do {
            read += json[i++];
        } while (json[i] != '\"');
        read = json[i];
        do {
            read += json[i++];
        } while (json[i] != ',' && json[i] != '\n');
        this->value = read.substr(1, read.length() - 1);
        if(JsonValidator::isObject(this->value) && this->value != "null") {
            this->valueType = JsonValueType::OBJECT;
        } else if (JsonValidator::isNumbersArray(this->value) 
                || JsonValidator::isBooleansArray(this->value) 
                || JsonValidator::isStringsArray(this->value)) {
            this->valueType = JsonValueType::VALUE_ARRAY;
        } else if (JsonValidator::isObjectsArray(this->value)) {
            this->valueType = JsonValueType::OBJECT_ARRAY;
        } else if (JsonValidator::isInteger(this->value)) {
            this->valueType = JsonValueType::INT;
        } else if (JsonValidator::isFloatingPoint(this->value)) {
            this->valueType = JsonValueType::DOUBLE;
        } else if(JsonValidator::isDate(this->value)) {
            this->valueType = JsonValueType::DATE;
        } else if (this->value == "true" || this->value == "false") {
            this->valueType = JsonValueType::BOOLEAN;
        } else if (this->value == "null") {
            this->valueType = JsonValueType::NULL_VALUE;
        } else {
            this->valueType = JsonValueType::STRING;
        }
        if(json[i] == '\n') {
            this->next = nullptr;
        } else {
            this->next = new JsonObject(json.substr(i, json.length()));
        }
    }
}
JsonObject::JsonObject(JsonValueType type, const std::string &key, const std::string &value, std::vector<JsonObject*> children, JsonObject *next)
    : valueType(type), key(key), value(value), next(next), children(std::vector<JsonObject*>())
{
    for(int i = 0; i < children.size(); ++i) {
        this->children.push_back(children[i]);
    }
}
JsonObject::JsonObject(const JsonObject &other)
{
    this->copy(other);
}
JsonObject &JsonObject::operator=(const JsonObject &other)
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
    }

    return *this;
}
bool operator==(const JsonObject &left, const JsonObject &right)
{
    return left.valueType == right.valueType && left.key == right.key 
        && left.value == right.value && left.next == right.next 
        && left.children == right.children;
}
bool operator!=(const JsonObject &left, const JsonObject &right)
{
    return !(left == right);
}
JsonObject::~JsonObject()
{
    this->destroy();
}
void JsonObject::setNext(const JsonObject &newNext)
{
    this->next = new JsonObject(newNext);
}
void JsonObject::add(const JsonObject &node)
{
    this->children.push_back(new JsonObject(node));
}
void JsonObject::remove(const JsonObject &node)
{
    for (unsigned int index = 0; index < this->children.size(); ++index)
    {
        if (*this->children[index] == node)
        {
            this->children.pop_back();
            break;
        }
    }
}
JsonValueType JsonObject::getType() const
{
    return this->valueType;
}
std::string JsonObject::getKey() const
{
    return this->key;
}
std::string JsonObject::getValue() const
{
    return this->value;
}
JsonObject *JsonObject::getNext() const
{
    return this->next;
}
std::vector<JsonObject *> JsonObject::getChildren() const
{
    return this->children;
}