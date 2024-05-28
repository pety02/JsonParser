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
    /// @brief
    JsonObject() = default;
    /// @brief 
    /// @param  
    JsonObject(const std::string&);
    /// @brief 
    /// @param  
    /// @param  
    /// @param  
    /// @param  
    JsonObject(JsonValueType, const std::string&, const std::string&, JsonObject*);
    /// @brief 
    /// @param  
    JsonObject(const JsonObject &);
    /// @brief 
    /// @param  
    /// @return 
    JsonObject &operator=(const JsonObject &);
    /// @brief 
    /// @param  
    /// @param  
    /// @return 
    friend bool operator==(const JsonObject &, const JsonObject &);
    /// @brief 
    /// @param  
    /// @param  
    /// @return 
    friend bool operator!=(const JsonObject &, const JsonObject &);
    /// @brief 
    ~JsonObject();

    /// @brief 
    /// @param  
    void setNext(const JsonObject &);
    /// @brief 
    /// @param  
    void add(const JsonObject &);
    /// @brief 
    /// @param  
    void remove(const JsonObject &);

    /// @brief 
    /// @return 
    JsonValueType getType() const;
    /// @brief 
    /// @return 
    std::string getKey() const;
    /// @brief 
    /// @return 
    std::string getValue() const;
    /// @brief 
    /// @return 
    JsonObject *getNext() const;
    /// @brief 
    /// @return 
    std::vector<JsonObject *> getChildren() const;
};

#endif