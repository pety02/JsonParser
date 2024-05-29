// #include "JsonParser.cpp"
// #include "JsonParser.cpp"
#include <string>
#include <iostream>
#include "JsonObject.cpp"
#include "JsonValidator.cpp"
#include "JsonParser.cpp"

int main()
{

    /*JsonObject* json = new JsonObject(JsonValueType::STRING, "name", "John Doe",
        new JsonObject(JsonValueType::VALUE_ARRAY, "gradesAtUni", "[6.0, 3.0, 5.0, 4.4]",
            new JsonObject(JsonValueType::DOUBLE, "salary", "1500", nullptr)));
    JsonParser jp = JsonParser(*json);
    jp.print();*/

    JsonValidator v = JsonValidator();
    std::string js = "{\n      \"name\": \"Petya Licheva\",\n           \"age\":       21\n}";
    std::string* ns = new std::string("");
    ns = &v.skipWhiteSpaces(js);
    std::cout << *ns;
    
    return 0;
}