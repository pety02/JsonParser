#include "JsonObject.h"

/// @brief a method that copies a definite JsonObject
/// @param other the copied object
/// @author Petya Licheva - pety02
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

/// @brief a method that destroys the current JsonObject
/// @author Petya Licheva - pety02
void JsonObject::destroy()
{
    this->children.clear();
    delete this->next;
}

/// @brief Default constructor of JsonObject class
/// @author Petya Licheva - pety02
JsonObject::JsonObject() : valueType(JsonValueType::STRING), key(""), value(""), 
    next(nullptr), children(std::vector<JsonObject*>())
{
}

/// @brief Constructor with all arguments
/// @param type the valueType of the JsonObject
/// @param key the key of the JsonObject
/// @param value the value of the JsonObject
/// @param children the nested JsonObjects 
///                 (children of the current JsonObject)
/// @param next the next JsonObject
/// @author Petya Licheva - pety02
JsonObject::JsonObject(JsonValueType type, const std::string &key, const std::string &value, 
    std::vector<JsonObject*> children, JsonObject *next)
    : valueType(type), key(key), value(value), next(next), children(std::vector<JsonObject*>())
{
    for(int i = 0; i < children.size(); ++i) {
        this->children.push_back(children[i]);
    }
}

/// @brief Copy constructor of JsonObject
/// @param other the copied JsonObject
/// @author Petya Licheva - pety02
JsonObject::JsonObject(const JsonObject &other)
{
    this->copy(other);
}

/// @brief Move copy constructor of JsonObject
/// @param other the copied JsonObject
/// @author Petya Licheva - pety02
JsonObject::JsonObject(JsonObject &&other) noexcept
{
    this->copy(other);
    other.children.clear();
    other.next = nullptr;
}

/// @brief Assignment operator of JsonObject
/// @param other the assigned JsonObject
/// @return a refernce to current JsonObject
/// @author Petya Licheva - pety02
JsonObject &JsonObject::operator=(const JsonObject &other)
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

/// @brief Assignement operator== for comparison of JsonObjects
/// @param left the left JsonObject
/// @param right the right JsonObject
/// @return true if the left JsonObject is equal to the 
///         right JsonObject and false if not
/// @author Petya Licheva - pety02
JsonObject &JsonObject::operator=(JsonObject &&other) noexcept
{
    if (this != &other)
    {
        this->destroy();
        this->copy(other);
        other.children.clear();
        other.next = nullptr;
    }

    return *this;
}

/// @brief Destroys the current JsonObject
/// @author Petya Licheva - pety02
JsonObject::~JsonObject()
{
    this->destroy();
}

/// @brief Operator== for comparison of JsonObjects
/// @param left the left JsonObject
/// @param right the right JsonObject
/// @return true if the left JsonObject is equal to the 
///         right JsonObject and false if not
/// @author Petya Licheva - pety02
bool operator==(const JsonObject &left, const JsonObject &right)
{
    bool areEqual = left.valueType == right.valueType && left.key == right.key 
        && left.value == right.value && left.next == right.next;
    
    if(!areEqual || left.children.size() != right.children.size()) {
        return false;
    }
    for(int i = 0; i < left.children.size(); ++i) {
        if(left.children[i] != right.children[i]) {
            areEqual = false;
            break;
        }
    }

    return areEqual;
}

/// @brief Operator== for comparison of JsonObjects
/// @param left the left JsonObject
/// @param right the right JsonObject
/// @return false if the left JsonObject is equal to the 
///         right JsonObject and true if not
/// @author Petya Licheva - pety02
bool operator!=(const JsonObject &left, const JsonObject &right)
{
    return left.key != right.key && left.value != right.value;
}

/// @brief a method that sets the next JsonObject
/// @param newNext the new next JsonObject
/// @author Petya Licheva - pety02
void JsonObject::setNext(const JsonObject &newNext)
{
    this->next = new JsonObject(newNext.getType(), newNext.getKey(), newNext.getValue(), newNext.getChildren(), newNext.getNext());
}

/// @brief a method that adds to the chain a new JsonObject node
/// @param node the new JsonObject node
/// @author Petya Licheva - pety02
void JsonObject::add(const JsonObject &node)
{
    this->children.push_back(new JsonObject(node));
}

/// @brief a method that removes from the chain a definite JsonObject node
/// @param node the definte JsonObject node
/// @author Petya Licheva - pety02
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

/// @brief a method that returns the valueType of the current JsonObject
/// @return the valueType of the current JsonObject
/// @author Petya Licheva - pety02
JsonValueType JsonObject::getType() const
{
    return this->valueType;
}

/// @brief a method that returns the key of the current JsonObject
/// @return the key of the current JsonObject
/// @author Petya Licheva - pety02
std::string JsonObject::getKey() const
{
    return this->key;
}

/// @brief a method that returns the value of the current JsonObject
/// @return the value of the current JsonObject
/// @author Petya Licheva - pety02
std::string JsonObject::getValue() const
{
    return this->value;
}

/// @brief a method that returns the next of the current JsonObject
/// @return the next of the current JsonObject
/// @author Petya Licheva - pety02 
JsonObject *JsonObject::getNext() const
{
    return this->next;
}

/// @brief a method that returns the children vector of the current JsonObject
/// @return the children vector of the current JsonObject 
/// @author Petya Licheva - pety02
std::vector<JsonObject *> JsonObject::getChildren() const
{
    return this->children;
}