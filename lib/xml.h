/*!
    \file
    \brief Заголовочный файл с описанием прототипов функций

    Данный файл содержит в себе определения функций индивидуального задания и их перегрузок, используемых в лабораторной работе
*/

#ifndef XML_H

#define XML_H

#include <iostream>
#include <string>
#include <algorithm>

namespace lab1 {
    void input();

    std::string array2xml(const char* array_name, const char* element_tag, const int* values, size_t array_size);

    std::string array2xml(const char* array_name, const char* element_tag, const int* values, size_t array_size, size_t& string_size);

    std::string array2xml(const std::string& array_name, const std::string& element_tag, const int* values, size_t array_size);

    int* xml2array(const char* xmlString, std::string& array_name, std::string& element_tag, size_t& array_size);

    int* xml2array(const char* xmlString, size_t string_size, std::string& array_name, std::string& element_tag, size_t& array_size);

    int* xml2array(const std::string& xmlString, std::string& array_name, std::string& element_tag, size_t& array_size);
}

#endif // XML_H
