#pragma once

/// \file


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include "exceptions.hpp"

struct Pair	///Клас для хранения слов с их статусом использования
{
	std::string word;	///<Слово
	bool status;		///<Статус слова

	friend std::ostream& operator<<(std::ostream& os, Pair& value)
	{
		os << value.word << " - " << value.status;
		return os;
	}
};

struct Coordinates	///Класс для хранения координат и направления слов
{
	int orientation;	///<Ориентация слова
	size_t h;			///<Значение высоты
	size_t w;			///<Значение широты

	friend std::ostream& operator<<(std::ostream& os, Coordinates& value)
	{
		os << "orientation - ";
		if (value.orientation > 0)
			os << "vertical\t";
		else if (value.orientation < 0)
			os << "gorizontal\t";
		else 
			os << "not\t";
		os << value.h << " - " << value.w;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, Coordinates value)
	{
		os << "orientation - ";
		if (value.orientation > 0)
			os << "vertical\t";
		else if (value.orientation < 0)
			os << "gorizontal\t";
		else 
			os << "not\t";
		os << value.h << " - " << value.w;
		return os;
	}
};

class Words	///Класс хранящий слова и их расположения
{
	private:
		std::vector<Pair> words_and_status; 	///<Вектор хранящий слова и их статусы
		std::vector<Coordinates> coordinates;	///<Вектор хранящий координаты
		size_t numbers;							///<Количество слов
		size_t used_numbers;					///<Количество использованных слов
	public:
		///Составление списка слов из файла
		/// \param filename Имя файла
		Words(std::string filename);
		///Метод получения слова по его номеру
		/// \details В ходе работы выписывает все неподходящие слова и сортирует подходящие слова 
		/// \param n Номер элемента вектора
		std::string get_word(size_t n);
		///Метод получения статуса слова по его номеру
		/// \param n Номер элемента вектора
		/// \return Значение статуса
		bool get_word_status(size_t n);
		///Метод изменения стаутса слова по его номеру
		/// \param n Номер элемента вектора
		/// \param value Устанавливаемое значение
		void change_word_status(size_t n, bool value);
		///Метод добавления нового слова
		/// \param value Устанавливаемое значение
		void add_word(std::string value);
		///Метод возврата количество слов
		/// \return Количествл слов
		size_t get_words_numbers();
		///Метод возврата количества использованных слов
		/// \return Колиство использованных слов
		size_t get_words_used_numbers();
		///Метод воззврада кординат слова по номеру
		/// \param n Номер элемента вектора
		/// \return Координаты слова
		Coordinates get_coordinates(size_t n);
		///Метод установки координат слова по номеру
		/// \param n Номер элемента вектора
		/// \param o Направление слова
		/// \param h Значение координаты высоты
		/// \param w Значение координаты широты
		void set_coordinates(size_t n, int o, size_t h, size_t w);
		///Метод установки координат как неиспользующихся по номеру
		/// \param n Номер элемента вектора
		/// \param o Направление слова
		void set_coordinates(size_t n, int o);
    	///Метод проверки использования всех слов
		/// \return Использованны ли все слова
		bool are_all_words_used();
	friend std::ostream& operator<<(std::ostream& os, Words& value)
	{
		for (auto& e : value.words_and_status)
			os << e << std::endl;
		return os;
	}
};
