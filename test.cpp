// #include "JsonParser.cpp"
// #include "JsonParser.cpp"
#include <string>
#include <iostream>
#include "JsonObject.cpp"
#include "JsonValidator.cpp"
#include "JsonParser.cpp"

int main()
{

    JsonObject* json = 
        new JsonObject(JsonValueType::STRING, "name", "ACME Software Co.", std::vector<JsonObject*>(),
        new JsonObject(JsonValueType::STRING, "type", "Software Development Company", std::vector<JsonObject*>(),
        new JsonObject(JsonValueType::OBJECT_ARRAY, "officess", "", {
                                                                        new JsonObject(JsonValueType::STRING, "name", "Headquarters", std::vector<JsonObject*>(),
                                                                            new JsonObject(JsonValueType::STRING, "address", "Sofia", std::vector<JsonObject*>(), nullptr)),
                                                                        new JsonObject(JsonValueType::STRING, "name", "Front Offices", std::vector<JsonObject*>(),
                                                                            new JsonObject(JsonValueType::STRING, "address", "New York City", std::vector<JsonObject*>(), nullptr))},
        new JsonObject(JsonValueType::OBJECT_ARRAY, "members", "", {
                                                                        new JsonObject(JsonValueType::INT, "id", "0", std::vector<JsonObject*>(),
                                                                            new JsonObject(JsonValueType::STRING, "name", "John Smith", std::vector<JsonObject*>(),
                                                                                new JsonObject(JsonValueType::DATE, "birthdate", "1980-01-01", std::vector<JsonObject*>(), nullptr))),
                                                                        new JsonObject(JsonValueType::INT, "id", "1", std::vector<JsonObject*>(),
                                                                            new JsonObject(JsonValueType::STRING, "name", "Jane Smith", std::vector<JsonObject*>(),
                                                                                new JsonObject(JsonValueType::DATE, "birthdate", "1981-02-02", std::vector<JsonObject*>(), nullptr))),
                                                                        new JsonObject(JsonValueType::INT, "id", "2", std::vector<JsonObject*>(),
                                                                            new JsonObject(JsonValueType::STRING, "name", "John Doe", std::vector<JsonObject*>(),
                                                                                new JsonObject(JsonValueType::DATE, "birthdate", "1982-03-03", std::vector<JsonObject*>(), nullptr)))},
        new JsonObject(JsonValueType::OBJECT, "management", "", {
                                                                        new JsonObject(JsonValueType::INT, "directorId", "0", std::vector<JsonObject*>(),
                                                                            new JsonObject(JsonValueType::INT, "presidentId", "1", std::vector<JsonObject*>(), nullptr))
        }, nullptr)))));
    JsonParser jp = JsonParser("companies.txt");
    jp.print(std::cout);
    jp.save();
    
    return 0;
}