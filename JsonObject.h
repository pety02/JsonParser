#pragma once
#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <string>
#include <vector>
#include "JsonValueType.h"
#include "JsonValidator.h"

/// @brief a class that describes a json object as struct that contains the type of the value, 
/// the key, the value, the next node and vector of pointer to all embedded json objects in this 
/// json object. 
class JsonObject final
{
private:
    JsonValueType valueType;
    std::string key;
    std::string value;
    JsonObject* next;
    std::vector<JsonObject*> children;

    void copy(const JsonObject &);
    void destroy();
public:
    /// @brief Default constructor
    JsonObject() = default;
    /// @brief Constructor with one parameter
    /// @param json text 
    JsonObject(const std::string&);
    /// @brief Constructor with four parameters that describe all object's fields
    /// @param valueType the type of the object's value
    /// @param key the key of the object
    /// @param value the value of the object
    /// @param next the next node of the object
    JsonObject(JsonValueType, const std::string&, const std::string&, std::vector<JsonObject*>,  JsonObject*);
    /// @brief Copy constructor
    /// @param other an object to be copied
    JsonObject(const JsonObject&);
    /// @brief Operator=
    /// @param other an object to be assigned
    /// @return reference to this object
    JsonObject& operator=(const JsonObject&);
    /// @brief Operator== for comparison
    /// @param left reference to left object 
    /// @param right reference to right object
    /// @return compares all fields of left and right objects and returns true if they are equal and false if not 
    friend bool operator==(const JsonObject&, const JsonObject&);
    /// @brief Operator!= for comparison
    /// @param left reference to left object 
    /// @param right reference to right object
    /// @return Compares all fields of left and right objects and returns true if they are not equal and false in the other cases
    friend bool operator!=(const JsonObject &, const JsonObject&);
    /// @brief Destructor 
    ~JsonObject();

    /// @brief sets new value for the next node
    /// @param next
    void setNext(const JsonObject&);
    /// @brief adds new JsonObject in this JsonObject's children
    /// @param node new child node to be added
    void add(const JsonObject&);
    /// @brief removes a JsonObject from this JsonObject's children
    /// @param node a child node to be removed
    void remove(const JsonObject&);

    /// @brief value type getter
    /// @return returns the value type of this JsonObject 
    JsonValueType getType() const;
    /// @brief key getter
    /// @return returns the key of this JsonObject
    std::string getKey() const;
    /// @brief value getter
    /// @return returns the value of this JsonObject
    std::string getValue() const;
    /// @brief next node getter
    /// @return returns the next node of this JsonObject
    JsonObject *getNext() const;
    /// @brief children getter
    /// @return returns the children of this JsonObject
    std::vector<JsonObject *> getChildren() const;
};

#endif