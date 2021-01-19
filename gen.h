#pragma once
#include <vector>
#include <string>

//Тип данных вектор, которые содержит 0/1
class Vec {
private:
	std::vector<unsigned char> arr;
	size_t length;

public:
	Vec();
	Vec(size_t length);
	Vec(std::string src);

	Vec operator+ (Vec a);
	unsigned char& operator[] (size_t index);

	void addZeros(size_t num);
	size_t getLength();

};

//Приведение векторов к одному размеру, засчет добавление нулей
void equalVecLen(Vec& v1, Vec& v2);

//Тип данных, который описывает набор векторов, которые образуют порождающее множество
class Set {
	std::vector<Vec> set;
	size_t N;
	size_t K;
public:
	void getDataFromFile(std::string name, std::string dir);
	size_t getN();
	size_t getK();

	int calcWeigth(Vec gen);   
};
//Тип данных, содержащий порождающее множество и распределение весов.
struct Spectrum {

	std::vector<int> counts;
	Set basis;
	Spectrum();
	Spectrum(Set vectors);

	void saveDataToFile();
};
void mergeSpectr(Spectrum& result, Spectrum source);

//Перебор двоичного кода Грея в порядке минимального изменения
//порядка k для нахождения всех возможных вариантов (считается рекуррентно)
void gray_all(size_t k, Vec v, Spectrum& s);
void grayR_all(size_t k, Vec v, Spectrum& s);

//Перебор подмножество двоичного кода Грея в порядке минимального изменения,
//содержащих заданное количество ненулевых элементов
//порядка k для нахождения всех возможных вариантов(считается рекуррентно)
void gray(size_t u, size_t v, Vec V, Spectrum& spectr);

//Факториал числа
template <typename T>
long long factorial(T x);

//Нахождение значений гистограммы полным перебором
void calcOneCycle(Spectrum& spectr);

//Находим количество всех возможных сочетаний(сечение треугольника Паскаля)
std::vector<long long> combinationsVec(size_t power);
//Получение двух подмножеств с примерно одинаковым суммарным весом (позволяет разбить варианты расчета
// что приводит к оптимальному распаралеливанию алгоритма)
std::vector<size_t> splitScheme(size_t power);

//Нахождение значений гистограммы, перебирая подмножества,
//которые содержат заданное количество ненулевых элементов
//ТУТ МОЖНО РАСПАРАЛЛЕЛИТЬ ВЫЧИСЛЕНИЯ!!!!!
void calcManyCycles(Spectrum& spectr, size_t part);

//Пример паралельных вычислений (написано не оптимально!)
//Для оптимизации надо написать алгоритм разбиения на потоки в зависимости от числа вариантов,
//которые надо посчитать в каждом подмножестве.
void threadCalc(Spectrum& spectr);


