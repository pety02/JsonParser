#pragma once
#ifndef JSON_VALUE_TYPE_H
#define JSON_VALUE_TYPE_H

/// @brief an enum that contains all possible json value types
enum JsonValueType
{
    STRING,
    INT,
    DOUBLE,
    DATE,
    BOOLEAN,
    VALUE_ARRAY,
    OBJECT_ARRAY,
    OBJECT,
    NULL_VALUE
};

#endif