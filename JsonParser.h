#pragma once
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <iostream>
#include <stdexcept>
#include <exception>
#include "JsonObject.h"
#include "JsonValidator.h"
class JsonParser final
{
private:
    JsonObject *root;
    JsonValidator validator;

    void copy(const JsonParser &);
    void destroy();
    JsonParser() = default;

    int countWhitespaces(const JsonObject &) const;
    void printNode(JsonObject *, int &) const;

public:
    JsonParser(const JsonObject &);
    JsonParser(const JsonParser &);
    JsonParser &operator=(const JsonParser &);
    ~JsonParser();

    bool validate(std::string) const;
    void print() const;
};

#endif