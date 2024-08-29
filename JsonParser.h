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

/// @brief a class that descibes a json parser
class JsonParser final
{
private:
    JsonObject *root;
    std::string filename;
 
    void copy(const JsonParser&);
    void destroy();

    JsonValueType getType(std::string) const;
    int countWhitespaces(const JsonObject&) const;
    std::pair<JsonObject*, JsonObject*> findNodeAndParent(const std::string& path);
    void printNode(JsonObject*, int&, std::ostream&) const;

public:
    JsonParser(std::string);
    /// @brief Constructor with a parameter
    /// @param root an object to be set as root of the json objects array
    JsonParser(const JsonObject&);
    /// @brief 
    /// @param  
    JsonParser(JsonParser&&) noexcept;
    /// @brief Copy constructor
    /// @param other an object to be copied  
    JsonParser(const JsonParser&);
    /// @brief Operator=
    /// @param other an object to be assigned
    /// @return a reference to this object
    JsonParser &operator=(const JsonParser&);
    /// @brief 
    /// @param  
    /// @return 
    JsonParser &operator=(JsonParser&&) noexcept;
    /// @brief Destructor
    ~JsonParser();

    /// @brief checks if a string is a valid json  
    /// @param json a string to be checked
    /// @return true if the string is a valid json and false in the other cases
    bool validate(const std::string&) const;
    /// @brief prints a string in json format
    /// @param out
    void print(std::ostream&) const;
    /// @brief searches all json objects in the json objects array by a definite key 
    /// @param key the key to search
    /// @return a vector of JsonObject pointers
    std::vector<JsonObject*> searchBy(const std::string&) const;
    /// @brief checks if json objects array contains a definite value 
    /// @param value the value to be checked
    /// @return true if the json objects array contains this value and false in the other cases
    bool contains(const std::string&) const;
    /// @brief 
    /// @param  
    /// @param  
    void setTo(const std::string&, const std::string&);
    /// @brief 
    /// @param  
    /// @param  
    void createPath(const std::string&);
    /// @brief 
    /// @param  
    void deletePath(const std::string&);
    /// @brief 
    /// @param  
    /// @param  
    void move(const std::string&, std::string&);
    /// @brief 
    /// @param  
    void open(std::string);
    /// @brief 
    /// @param  
    void close(std::string);
    /// @brief 
    int exit();
    /// @brief 
    /// @param  
    void save() const;
    /// @brief 
    /// @param  
    /// @param  
    void saveAs(const std::string&) const;
};

#endif