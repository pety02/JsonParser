#pragma once
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <sstream>
#include <cmath>
#include "JsonObject.h"

class JsonParser final
{
private:
    JsonObject *root;
    std::string filename;
 
    void copy(const JsonParser&); // works
    void destroy(); // works

    JsonValueType getType(std::string) const; // works
    int countWhitespaces(const JsonObject&) const; // works
    std::pair<JsonObject*, JsonObject*> findNodeAndParent(const std::string& path); 
    void printNode(JsonObject*, int&, std::ostream&) const; // works
    bool containsHelper(const std::string, JsonObject*) const; // works
    JsonObject* createFromJsonString(std::string); // works
    std::vector<std::string> splitBy(char, const std::string&);
    JsonObject* findBy(const std::string&, JsonObject*, int);
public:
    JsonParser(); // works
    JsonParser(const JsonObject&); // works
    JsonParser(const JsonParser&); // works
    JsonParser(JsonParser&&) noexcept; // works  
    JsonParser &operator=(const JsonParser&); // works
    JsonParser &operator=(JsonParser&&) noexcept; // works
    ~JsonParser(); // works

    bool validate(const std::string&) const; // works
    void print(std::ostream&) const; // works
    std::vector<JsonObject*> searchBy(const std::string&) const; // works
    bool contains(std::string) const; // works
    void setTo(const std::string&, const std::string&); // works
    void createPath(const std::string&, const std::string&); // TODO: to implment it
    void deletePath(const std::string&); // TODO: to implment it
    void move(const std::string&, std::string&); // TODO: to implment it
    void open(std::string); // works
    int exit(); // works
    void save() const; // works
    void saveAs(const std::string&) const; // works
};

#endif