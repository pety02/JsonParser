#pragma once
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <iostream>
#include <stdexcept>
#include <exception>
#include "JsonObject.h"
class JsonParser final
{
private:
    JsonObject *root;
    JsonValidator validator;
    unsigned int capacity;
    unsigned int size;
 
    void copy(const JsonParser&);
    void destroy();
    void resize();
    JsonParser() = default;

    int countWhitespaces(const JsonObject&) const;
    void printNode(JsonObject*, int&) const;

public:
    /// @brief 
    /// @param  
    JsonParser(const JsonObject&);
    /// @brief 
    /// @param  
    JsonParser(const JsonParser&);
    /// @brief 
    /// @param  
    /// @return 
    JsonParser &operator=(const JsonParser&);
    /// @brief 
    ~JsonParser();

    /// @brief 
    /// @param  
    /// @return 
    bool validate(const std::string&) const;
    /// @brief 
    void print() const;
    /// @brief 
    /// @param  
    /// @return 
    std::vector<JsonObject*> searchBy(const std::string&) const;
    /// @brief 
    /// @param  
    /// @return 
    bool contains(const std::string&) const;
    /// @brief 
    /// @param  
    /// @param  
    void setTo(const std::string&, const std::string&);
    /// @brief 
    /// @param  
    /// @param  
    void createPath(const std::string&, const std::string&);
    /// @brief 
    /// @param  
    void deletePath(const std::string&);
    /// @brief 
    /// @param  
    /// @param  
    void move(const std::string&, std::string&);
    /// @brief 
    /// @param  
    void save(const std::string&) const;
    /// @brief 
    /// @param  
    /// @param  
    void saveAs(const std::string&, const std::string&) const;
};

#endif