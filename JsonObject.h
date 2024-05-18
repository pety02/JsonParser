#pragma once
#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <string>
#include <vector>
#include "JsonValueType.h"

class JsonObject final {
    private:
    JsonValueType valueType;
    std::string key;
    std::string value;
    JsonObject* next;
    std::vector<JsonObject*> children;

    void copy(const JsonObject&);
    void destroy();
    JsonObject() = default;

    public:
    JsonObject(JsonValueType, std::string, std::string);
    JsonObject(const JsonObject&);
    JsonObject& operator=(const JsonObject&);
    friend bool operator==(const JsonObject&, const JsonObject&);
    friend bool operator!=(const JsonObject&, const JsonObject&);
    ~JsonObject();

    void setNext(const JsonObject&);
    void add(const JsonObject&);
    void remove(const JsonObject&);
};

#endif