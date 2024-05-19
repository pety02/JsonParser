#pragma once
#ifndef JSON_VALUE_TYPE_H
#define JSON_VALUE_TYPE_H

enum JsonValueType
{
    STRING,
    INT,
    DOUBLE,
    BOOLEAN,
    VALUE_ARRAY,
    OBJECT_ARRAY,
    OBJECT,
    NULL_VALUE
};

#endif