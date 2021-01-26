#pragma once
#include <valarray>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Оставил одну структуру, добы уменьшить избыточность кода
struct Spectr {
	valarray<long long> counts;
	vector<valarray<size_t>> basis;
	size_t basisVecNum;
	size_t basisVecLen;

	void getDataFromFile(string name);
	size_t calcWeight(valarray<size_t> gen);
	void saveDataToFile();
};

//Заполнение численного массива из строки
valarray<size_t> fillArr(string input);

//Перебор подмножество двоичного кода Грея в порядке минимального изменения,
//содержащих заданное количество ненулевых элементов
//порядка k для нахождения всех возможных вариантов(считается рекуррентно)
void enumiration(size_t order, size_t ones_count, valarray<size_t> V, Spectr& spectr);

//обертка, на функцию enumiration, которая позволяет распаралелить вычисления 
void calculate(Spectr& spectr, size_t mask_count, size_t mask_weight);

//исполняющая функция, где используется многопоточка
void threadCalc(Spectr& spectr);
