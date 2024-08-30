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
 
    void copy(const JsonParser&); // works
    void destroy(); // works

    JsonValueType getType(std::string) const; // works
    int countWhitespaces(const JsonObject&) const; // works
    std::pair<JsonObject*, JsonObject*> findNodeAndParent(const std::string& path); 
    void printNode(JsonObject*, int&, std::ostream&) const; // works
    bool containsHelper(const std::string, JsonObject*) const; // works
public:
    /// @brief Default constructor
    JsonParser(); // works
    /// @brief Constructor with a parameter
    /// @param root an object to be set as root of the json objects array
    JsonParser(const JsonObject&); // works
    /// @brief Move copy constructor 
    /// @param other the object that must be copied from
    JsonParser(JsonParser&&) noexcept; // works
    /// @brief Copy constructor
    /// @param other an object to be copied  
    JsonParser(const JsonParser&); // works
    /// @brief Assignment operator
    /// @param other an object to be assigned
    /// @return a reference to this object
    JsonParser &operator=(const JsonParser&); // works
    /// @brief Move assignment operator
    /// @param other an object to be moved
    /// @return a reference to this object
    JsonParser &operator=(JsonParser&&) noexcept; // works
    /// @brief Destructor
    ~JsonParser(); // works

    /// @brief checks if a string is a valid json  
    /// @param json a string to be checked
    /// @return true if the string is a valid json and false in the other cases
    bool validate(const std::string&) const; // works
    /// @brief prints a string in json format in an output stream
    /// @param out the output stream
    void print(std::ostream&) const; // works
    /// @brief searches all json objects in the json objects array by a definite key 
    /// @param key the key to search
    /// @return a vector of JsonObject pointers
    std::vector<JsonObject*> searchBy(const std::string&) const; // works
    /// @brief checks if json objects array contains a definite value 
    /// @param value the value to be checked
    /// @return true if the json objects array contains this value and false in the other cases
    bool contains(std::string) const; // works
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
    void open(std::string); // works
    /// @brief 
    /// @param  
    void close(std::string);
    /// @brief 
    int exit();
    /// @brief 
    /// @param  
    void save() const; // works
    /// @brief 
    /// @param  
    /// @param  
    void saveAs(const std::string&) const; // works
};

#endif