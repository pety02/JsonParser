#include <string>
#include <iostream>
#include "JsonObject.cpp"
#include "JsonValidator.cpp"
#include "JsonParser.cpp"

int main()
{
    JsonParser jp = JsonParser();
    jp.open("C:\\Users\\User\\OneDrive\\Documents\\University\\1 kurs, 2 semestur\\OOP\\2023-2024\\JsonParser\\tst_data.txt");
    //jp.print(std::cout);
    jp.setTo("management/presidentId", "15");
    jp.print(std::cout);
    //jp.save();
    //jp.saveAs("C:\\Users\\User\\OneDrive\\Documents\\University\\1 kurs, 2 semestur\\OOP\\2023-2024\\JsonParser\\test_save_as2.txt");
    //jp.setTo("{\n \"name\": \"John\",\n \"age\": 25,\n \"name\": \"mara\",\n \"surname\": \"Doe\"\n}", "{\n \"grades\": [5, 4, 6, 3, 5]\n}");
    
    return jp.exit();
}