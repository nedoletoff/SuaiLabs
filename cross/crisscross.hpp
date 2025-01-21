#pragma once

/// \file

#include <iostream>
#include <list>
#include "matrix.hpp"
#include "words.hpp"
#include "exceptions.hpp"

extern const int not_used;  ///<Значение для неиспользуемых ячеек
extern const int gorizontal;    ///<Значение для клеток находящихся рядом с горизонтальными словами
extern const int vertical;  ///<Значения для клеток находящихся рядом с вертикальными словами
extern const int used;  ///<Значения для клеток хранящие буквы

///  Функция вставки слов в подходящее место матрицы
/// \param words Список слов
/// \param n Номер слова
/// \param matrix Матрица содержащая сетку кроссворда
 /// \return Добавилось ли слово
bool add_word(Words& words, size_t n, Matrix& matrix);

///Фунцкия удаления слов независящая от ориентации
/// \param words Список слов
/// \param n Номер слова
/// \param matrix Матрица содержащая сетку кроссворда
 /// \return Удалилось ли слово
bool delete_word(Words& words, size_t n, Matrix& matrix);

///Функция обертка алгоритма составления крисскросса
/// \param words Список слов
/// \param matrix Матрица содержащая сетку кроссворда
void crisscross(Words& words, Matrix& matrix);

///Рекурсивный алгоритм вставки слов
/// \param words Список слов
/// \param matrix Матрица содержащая сетку кроссворда
/// \param res Матрица содержащая наиболее оптимальную расстановку слов
/// \param saved Список слов, содержащий слова использованные для матрицы res
/// \param l Список слов, хранящий использованые слова
void cross(Words& words, Matrix& matrix, Matrix& res, std::list<size_t>& saved, std::list<size_t>& l);

///Функция удаления вертикальных слов
/// \param value Слово, подлежащее удалению
/// \param matrix Матрица содержащая сетку кроссворда
/// \param h Координата высоты
/// \param w Координата широты
void delete_word_v(std::string value, Matrix& matrix, size_t h, size_t w);

///Функция удаления горизонтальных слов
/// \param value Слово, подлежащее удалению
/// \param matrix Матрица содержащая сетку кроссворда
/// \param h Координата высоты
/// \param w Координата широты
void delete_word_g(std::string value, Matrix& matrix, size_t h, size_t w);

///Функция вставки слов по координатам
/// \param words Список слов
/// \param n Номер слова
/// \param matrix Матрица содержащая сетку кроссворда
/// \param h Координата высоты
/// \param w Координата широты
 /// \return Добавилось ли слово
bool add_word(Words& words, size_t n, Matrix& matrix, size_t h, size_t w);

///Функция вставки слов по координатам вертикально
/// \param words Список слов
/// \param n Номер слова
/// \param matrix Матрица содержащая сетку кроссворда
/// \param h Координата высоты
/// \param w Координата широты
 /// \return Добавилось ли слово
bool add_word_v(Words& words, size_t n, Matrix& matrix, size_t h, size_t w);

///Функция вставки слов по координатам горизонтально
/// \param words Список слов
/// \param n Номер слова
/// \param matrix Матрица содержащая сетку кроссворда
/// \param h Координата высоты
/// \param w Координата широты
 /// \return Добавилось ли слово
bool add_word_g(Words& words, size_t n, Matrix& matrix, size_t h, size_t w);