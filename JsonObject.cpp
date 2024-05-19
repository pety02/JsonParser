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
JsonObject::JsonObject(JsonValueType type, std::string key, std::string value, JsonObject *next)
    : valueType(type), key(key), value(value), next(next), children(std::vector<JsonObject *>())
{
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