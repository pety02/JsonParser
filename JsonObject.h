#pragma once
#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <string>
#include <vector>
#include "JsonValueType.h"
#include "JsonValidator.h"

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
    JsonObject();
    JsonObject(JsonValueType, const std::string&, const std::string&, std::vector<JsonObject*>,  JsonObject*);
    JsonObject(const JsonObject&);
    JsonObject(JsonObject&&) noexcept;
    JsonObject& operator=(const JsonObject&);
    JsonObject& operator=(JsonObject&&) noexcept;
    ~JsonObject();

    friend bool operator==(const JsonObject&, const JsonObject&);
    friend bool operator!=(const JsonObject &, const JsonObject&);

    void setNext(const JsonObject&);
    void add(const JsonObject&);
    void remove(const JsonObject&);
    JsonValueType getType() const;
    std::string getKey() const;
    std::string getValue() const;
    JsonObject *getNext() const;
    std::vector<JsonObject *> getChildren() const;
};

#endif