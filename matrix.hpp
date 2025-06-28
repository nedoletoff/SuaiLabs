#pragma once

/// \file

#include <iostream>
#include <vector>
#include "exceptions.hpp"

const int not_used(1);	///<Значение для неиспользуемых ячеек
const int gorizontal(2);///<Значение для клеток находящихся рядом с горизонтальными словами
const int vertical(3);	///<Значения для клеток находящихся рядом с вертикальными словами
const int used(5);		///<Значения для клеток хранящие буквы


class Matrix	///Класс для графического вывода
{
	private:
		size_t height;	///<Высота матрицы
		size_t width;	///<Ширина матрицы
		char** data;	///<Двумерный массив хранящий буквенные значения
		int** status;	///<Двумерный массиы хранящий численный значения статуса
	public:
		Matrix(size_t h, size_t w);
		~Matrix();	
		Matrix(Matrix& a);
		Matrix& operator=(Matrix& a);
		///Метод установки значения клетки
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \param value Устанавливаемое значение
		void set_cell(size_t h, size_t w, char value);	
		///Метод установки значения статуса клетки
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \param value Устанавливаемое значение
		void set_cell_status(size_t h, size_t w, int value);	
		///Метод умножения значения клетки статуса
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \param value Устанавливаемое значение
		void multiply_cell_status(size_t h, size_t w, int value);	
		///Метод деления значения клетки статуса
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \param value Устанавливаемое значение
		void divide_cell_status(size_t h, size_t w, int value);	
		///Метод возврата значения клетки
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \return Возвращает буквенноу значение клетки
		char get_cell(size_t h, size_t w);
		///Метод возврата значения статуса клетки	
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \return Возращает целочисленное значение клетки
		int get_cell_status(size_t h, size_t w);	
		///Метод возврата высоты матрицы
		/// \return	Возвращает высоту
		size_t get_height();	
		///Метод возврата ширины матрицы
		/// \return	Возвращает ширину
		size_t get_width();	
		///Метод возврата незаполненных клеток по значению
		/// \param check Значение принимаемое как ноль
		/// \return Количество незаполненных клеток
		size_t get_unfilled(char check);	
		///Метод возврата незаполненных клеток по статусу
		/// \return Количество незаполненных клеток
		size_t get_unfilled();	
		///Метод изменения значения  незаполненных клеток 
		/// \details принимает значение для незаполенной клетки и значение замены этой клетки
		/// \param check Заменяемое значение
		/// \param value Устанавливаемое значение
		void change_unfilled(char check, char value);
		///Метод увеличения размера	
		/// \param h Значение высоты новой матрицы
		/// \param w Значение широты новой матрицы
		void increase_size(size_t h, size_t w);
		///Метод приведения матрицы к оптимальному размеру
		/// \param check Значение принимаемое как ноль
		void shrink_to_fit(char check);	
		///Метод возврата коэфицента оптимальности матрицы
		/// \return Возвращает коэффициент
		double get_coef();	
		///Метод проверки возможности использования клетки
		/// \param h Координата высоты
		/// \param w Координата широты
		/// \return Можно ли использовать клетку
		bool legal(size_t h, size_t w);	

	friend std::ostream& operator<<(std::ostream& os, Matrix& value)
	{
		for (size_t i = 0; i < value.height; i++)
		{
			for (size_t j = 0; j < value.width; j++)
				os << value.data[i][j];
			os << std::endl;
		}
		return os;
	}
};
