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
    std::string js = "{\n\"is\":1,\n\"nm\":\"object\",\n\"something\":{\n\"name\":\"Petya\",\n\"age\":21\n},\n\"price\":5.50,\n\"data\":[1,2,3,4,5]\n}";
    /*std::string* ns = new std::string("");
    ns = &v.skipWhiteSpaces(js);*/
    std::cout << std::boolalpha << v.isObject(js);
    
    return 0;
}