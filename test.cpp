// #include "JsonParser.cpp"
// #include "JsonObject.cpp"
#include <string>
#include <iostream>
#include "JsonValidator.cpp"

int main()
{

    /*JsonObject* json = new JsonObject(JsonValueType::STRING, "name", "John Doe",
        new JsonObject(JsonValueType::VALUE_ARRAY, "gradesAtUni", "[6.0, 3.0, 5.0, 4.4]",
            new JsonObject(JsonValueType::DOUBLE, "salary", "1500", nullptr)));
    JsonParser jp = JsonParser(*json);
    jp.print();*/

    JsonValidator v = JsonValidator();
    std::string js = "[25.30, 15.34]";
    std::cout << v.isArray(js);
    return 0;
}