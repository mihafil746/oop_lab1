/*!
    \file
    \brief Файл реализации функций индивидуального задания

    Данный файл содержит в себе реализацию функций индивидуального задания и их перегрузок, используемых в лабораторной работе
*/

#include "xml.h"

namespace lab1 {
    /*!
        Общается с пользователем через консоль и вызывает соответствующие функции логики
        \throw std::invalid_argument В случае некорректного ввода
        \return Возвращаемое значение не требуется
    */
    void input() {
    while (true) {
        std::cout << "0. Quit" << std::endl << "1. Transform number array to XML string" << std::endl << "2. Transform XML string to number array" << std::endl;
        int mode;
        std::cin >> mode;
        if (mode == 0)
            break;
        std::cout << "Select overload type:" << std::endl << "1. const char*" << std::endl << "2. const char* + size_t" << std::endl << "3. std::string" << std::endl;
        int overload;
        std::cin >> overload;
        if (mode == 1) {
            std::string array_name, element_tag, values_str, result;
            std::cout << "Enter array name: ";
            std::cin >> array_name;
            std::cout << "Enter element tag: ";
            std::cin >> element_tag;
            std::cout << "Enter values: ";
            std::cin >> values_str;
            size_t length = std::count(values_str.begin(), values_str.end(), ',') + 1;
            int* values = new int[length](0);
            size_t it = 0, result_size = 0;
            auto start = values_str.begin();
            auto shift = std::find(start, values_str.end(), ',');
            while (it < length) {
                std::string tmp = std::string(start, shift);
                try {
                    values[it++] = std::stoi(tmp);
                }
                catch (const std::exception& e) {
                    delete[] values;
                    throw std::invalid_argument("Invalid number recieved!");;
                }
                start = shift + 1;
                shift = std::find(start, values_str.end(), ',');
            }
            switch (overload) {
                case 1:
                    result = array2xml(array_name.c_str(), element_tag.c_str(), values, length);
                    break;
                case 2:
                    result = array2xml(array_name.c_str(), element_tag.c_str(), values, length, result_size);
                    break;
                case 3:
                    result = array2xml(array_name, element_tag, values, length);
                    break;
                default:
                    throw std::invalid_argument("Incorrect overload type!");
            }
            std::cout << "XML string: " << result << std::endl;
            delete[] values;
        } 
        else if (mode == 2) {
            std::string xml_string, array_name, element_tag;
            int* values = nullptr;
            size_t array_size = 0;
            std::cout << "Enter XML string: ";
            std::cin.ignore();
            std::getline(std::cin, xml_string);
            switch (overload) {
                case 1:
                    values = xml2array(xml_string.c_str(), array_name, element_tag, array_size);
                    break;
                case 2:
                    values = xml2array(xml_string.c_str(), xml_string.size(), array_name, element_tag, array_size);
                    break;
                case 3:
                    values = xml2array(xml_string, array_name, element_tag, array_size);
                    break;
                default:
                    throw std::invalid_argument("Incorrect overload type!");
            }
            std::cout << "Array name: " << array_name << std::endl << "Element tag: " << element_tag << std::endl << "Values: ";
            for (size_t i = 0; i < array_size; i++)
                std::cout << values[i] << " ";
            std::cout << std::endl;
            delete[] values;    
        } 
        else
            throw std::invalid_argument("Incorect work mode!");
    }
}
    /*!
        Преобразует массив целых чисел в строку формата XML. Данные о результирующей строке передаются через тип const char*
        \param array_name Имя массива
        \param element_tag Тэг элемента
        \param values Массив целых чисел
        \param array_size Размер массива с числами
        \throw std::invalid_argument В случае передачи некорректного аргумента
        \return Строка типа std::string с данными в формате XML
    */
    std::string array2xml(const char* array_name, const char* element_tag, const int* values, size_t array_size) {
        if (!array_name || !element_tag || !values)
            throw std::invalid_argument("Null argument passed to convert function!");
        std::string xml = "";
        const std::string name(array_name);
        const std::string tag(element_tag);
        return array2xml(name, tag, values, array_size);
    }

    /*!
        Преобразует массив целых чисел в строку формата XML. Данные о результирующей строке передаются через тип const char* + size_t
        \param array_name Имя массива
        \param element_tag Тэг элемента
        \param values Массив целых чисел
        \param array_size Размер массива с числами
        \param string_size Размер результирующей XML-строки
        \throw std::invalid_argument В случае передачи некорректного аргумента
        \return Строка типа std::string с данными в формате XML
    */
    std::string array2xml(const char* array_name, const char* element_tag, const int* values, size_t array_size, size_t& string_size) {
        if (!array_name || !element_tag || !values)
            throw std::invalid_argument("Null argument passed to convert function!");
        const std::string name(array_name);
        const std::string tag(element_tag);
        std::string xml = array2xml(name, tag, values, array_size);
        string_size = xml.length();
        return xml;
    }

    /*!
        Преобразует массив целых чисел в строку формата XML. Данные о результирующей строке передаются через тип std::string
        \param array_name Имя массива
        \param element_tag Тэг элемента
        \param values Массив целых чисел
        \param array_size Размер массива с числами
        \throw std::invalid_argument В случае передачи некорректного аргумента
        \return Строка типа std::string с данными в формате XML
    */
    std::string array2xml(const std::string& array_name, const std::string& element_tag, const int* values, size_t array_size) {
        if (array_name.empty() || element_tag.empty() || !values)
            throw std::invalid_argument("Null argument passed to convert function!");
        std::string xml = "";
        xml += "<" + array_name + ">";
        for (size_t i = 0; i < array_size; i++)
            xml += "<" + element_tag + ">" + std::to_string(values[i]) + "</" + element_tag + ">";
        xml += "</" + array_name + ">";
        return xml;
    }

    /*!
        Преобразует строку в формате XML в массив целых чисел. XML-строка передается через тип const char*
        \param xml_string XML-строка
        \param array_name Имя массива
        \param element_tag Тэг элемента
        \param array_size Размер результирующего массива с числами
        \throw std::invalid_argument В случае передачи некорректного аргумента или нечислового значения внутри XML-строки
        \return Указатель на полученный массив с целыми числами
    */
    int* xml2array(const char* xml_string, std::string& array_name, std::string& element_tag, size_t& array_size) {
        if (!xml_string)
            throw std::invalid_argument("Null argument passed to convert function!");
        std::string xml(xml_string);
        return xml2array(xml, array_name, element_tag, array_size);
    }

    /*!
        Преобразует строку в формате XML в массив целых чисел. XML-строка передается через тип const char* + size_t
        \param xml_string XML-строка
        \param string_size Размер XML-строки
        \param array_name Имя массива
        \param element_tag Тэг элемента
        \param array_size Размер результирующего массива с числами
        \throw std::invalid_argument В случае передачи некорректного аргумента или нечислового значения внутри XML-строки
        \return Указатель на полученный массив с целыми числами
    */
    int* xml2array(const char* xml_string, size_t string_size, std::string& array_name, std::string& element_tag, size_t& array_size) {
        if (!xml_string)
            throw std::invalid_argument("Null argument passed to convert function!");
        std::string xml(xml_string);
        return xml2array(xml, array_name, element_tag, array_size);
    }

    /*!
        Преобразует строку в формате XML в массив целых чисел. XML-строка передается через тип std::string
        \param xml_string XML-строка
        \param array_name Имя массива
        \param element_tag Тэг элемента
        \param array_size Размер результирующего массива с числами
        \throw std::invalid_argument В случае передачи некорректного аргумента или нечислового значения внутри XML-строки
        \return Указатель на полученный массив с целыми числами
    */
    int* xml2array(const std::string& xml_string, std::string& array_name, std::string& element_tag, size_t& array_size) {
        if (xml_string.empty())
            throw std::invalid_argument("Null argument passed to convert function!");
        auto pos1 = std::find(xml_string.begin(), xml_string.end(), '<');
        auto pos2 = std::find(xml_string.begin(), xml_string.end(), '>');
        array_name.resize(std::distance(pos1, pos2 - 1));
        std::copy(pos1 + 1, pos2, array_name.begin());
        pos1 = pos2 + 1;
        pos2 = std::find(pos1, xml_string.end(), '>');
        element_tag.resize(std::distance(pos1, pos2 - 1));
        std::copy(pos1 + 1, pos2, element_tag.begin());
        size_t length = (std::count(xml_string.begin(), xml_string.end(), '<') - 2) / 2;
        int* values = new int[length];
        size_t pos = 0, it = 0;
        std::string open_tag = "<" + element_tag + ">", close_tag = "</" + element_tag + ">";
        while (pos != std::string::npos) {
            pos = xml_string.find(open_tag, pos);
            size_t end_pos = xml_string.find(close_tag, pos);
            if (end_pos == std::string::npos)
                break;
            try {   
                    values[it++] = std::stoi(xml_string.substr(pos + open_tag.length(), end_pos - pos - open_tag.length()));
                }
            catch (const std::exception& e) {
                    delete[] values;
                    throw std::invalid_argument("Invalid number recieved!");
            }
            pos = end_pos + close_tag.length();
        }
        array_size = length;
        return values;
    }
}
