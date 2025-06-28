#pragma once

/// \file

#include <string>
#include <iostream>

class Exception    ///Класс исключений
{
    private:
        std::string val;    ///<Текст исключения
    public:
        Exception(const std::string value);
    friend std::ostream& operator<<(std::ostream& os, Exception& obj)
    {
        os << obj.val;
        return os;
    }
};
