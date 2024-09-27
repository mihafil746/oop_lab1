/*!
    \file
    \brief Файл с реализацией основной функции программы main()
*/

#include <iostream>
#include "lib/xml.h"

using namespace lab1;

/*!
    Основная функция лабораторной работы, вызывающая диалоговую функцию и обрабатывабщая исключения
    \throw std::bad_alloc В случае неудачного выделения памяти
    \throw std::exception В случае получения исключений внутри диалоговой функции
    \return Код возврата(0 - успех, 1 - ошибка)
*/
int main () {
    try {
        input();
    }
    catch (const std::bad_alloc& ba) {
        std::cerr << "Not enough memory!" << std::endl;
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}