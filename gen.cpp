#include <direct.h>
#include <fstream>
#include <iostream>
#include <thread>
#include "gen.h"
#include "sort.h"


Vec::Vec() :
	length(0)
{}

Vec::Vec(size_t length):
	length(length)
{
	for (size_t i = 0; i < length; i++)
	{
		arr.push_back(0);
	}
}

Vec::Vec(std::string src)
{
	length = src.size();
	for (size_t i = 0; i < length; i++)
	{
		if (src.at(i) == '0') {
			arr.push_back(0);
		}
		else if (src.at(i) == '1') {
			arr.push_back(1);
		}
		else arr.push_back(2);
		
	}
}

Vec Vec::operator+(Vec input)
{
	equalVecLen(*this, input);

	Vec output(this->length);

	for (size_t i = 0; i < this->length; ++i)
	{
		if (input.arr.at(i) == this->arr.at(i))
			output.arr.at(i) = 0;
		else
			output.arr.at(i) = 1;
	}

	return output;
}

unsigned char& Vec::operator[](size_t index)
{
	return arr.at(index);
}

size_t Vec::getLength()
{
	return length;
}

void Vec::addZeros(size_t num)
{
	for (size_t i = 0; i < num; i++)
	{
		arr.insert(arr.begin(), 0);
	}
	length += num;
}

void equalVecLen(Vec& v1, Vec& v2)
{
	if (v1.getLength() == v2.getLength()) {
		return;
	}

	else if (v1.getLength() > v2.getLength()) {
		v2.addZeros(v1.getLength() - v2.getLength());
	}

	else {
		v1.addZeros(v2.getLength() - v1.getLength());
	}
}

void Set::getDataFromFile(std::string name, std::string dir)
{
	if (_chdir(dir.c_str()))
		return;

	std::ifstream file(name);
	
	if (!file.is_open())
		return;

	std::string buffer;
	N = 0;
	for (file >> buffer; !file.eof(); file >> buffer) {
		Vec tmp(buffer);
		set.push_back(tmp);
		N = buffer.size() > N ? buffer.size() : N;
	}
	Vec tmp(buffer);
	set.push_back(tmp);
	K = set.size();
	file.close();

}

size_t Set::getN()
{
	return N;
}

size_t Set::getK()
{
	return K;
}

int Set::calcWeigth(Vec gen)
{
	if (gen.getLength() != set.size())
		return -1;

	int weigth = 0;
	Vec tmp(gen.getLength());

	for (int i = 0; i < set.size(); i++)
	{
		if (gen[i] != 0)
			tmp = tmp + set.at(i);
	}

	for (int i = 0; i < tmp.getLength(); i++)
	{
		if (tmp[i] != 0) ++weigth;
	}

	return weigth;
}

Spectrum::Spectrum(){}

Spectrum::Spectrum(Set vectors)
{
	basis = vectors;
	for (size_t i = 0; i < vectors.getN()+1; i++)
	{
		counts.push_back(0);
	}
}

void Spectrum::saveDataToFile()
{
	std::ofstream outFile("hist.txt");

	for (size_t i = 0; i < counts.size(); i++)
	{
		outFile << i << '\t' << counts.at(i) << std::endl;
	}
	outFile.close();

}

void gray(size_t order, size_t ones_count, Vec V, Spectrum& spectr) {
	if (order == ones_count) {
		for (size_t i = 0; i < V.getLength(); i++)
		{
			if (i >= V.getLength() - order)
				V[i] = 1;
		}
		int tmp = spectr.basis.calcWeigth(V);
		++spectr.counts.at(tmp);
		return;
	}
	else if (ones_count == 0) {
		for (size_t i = 0; i < V.getLength(); i++)
		{
			if (i >= V.getLength() - order)
				V[i] = 0;

		}
		int tmp = spectr.basis.calcWeigth(V);
		++spectr.counts.at(tmp);
		return;
	}
	else {
		V[V.getLength() - order] = 1;
		gray(order - 1, ones_count - 1, V, spectr);
		V[V.getLength() - order] = 0;
		gray(order - 1, ones_count, V, spectr);
	}
}

template <typename T>
long long factorial(T x)
{
	if (!x) return 1;
	return x * factorial(x - 1);
}

std::vector<long long> combinationsVec(size_t power)
{
	std::vector<long long> combinations;

	for (size_t i = 0; i <= power; i++)
	{
		long long n = factorial(power);
		long long m = factorial(i);
		long long n_m = factorial(power - i);
		combinations.push_back(n/m/n_m);
	}
	return combinations;
}

std::vector<size_t> splitScheme(size_t power) {

	std::vector<long long> combinationCounts = combinationsVec(power);
	std::vector<size_t> indexes;
	std::vector<size_t> scheme;
	for (int i = 0; i < combinationCounts.size(); i++)
	{
		indexes.push_back(i);
		scheme.push_back(0);
	}

	quickSortD(combinationCounts, indexes, 0, combinationCounts.size() - 1);

	std::vector<long long> weigths;
	weigths.push_back(combinationCounts.at(0));
	weigths.push_back(combinationCounts.at(1));
	
	scheme.at(indexes.at(0)) = 0;
	scheme.at(indexes.at(1)) = 1;

	for (int i = 2; i < combinationCounts.size(); i++)
	{
		if (weigths.at(0) + combinationCounts.at(i) <
			weigths.at(1) + combinationCounts.at(i)) {
			weigths.at(0) += combinationCounts.at(i);
			scheme.at(indexes.at(i)) = 0;
		}
		else {
			weigths.at(1) += combinationCounts.at(i);
			scheme.at(indexes.at(i)) = 1;
		}
	}

	return scheme;
}

void mergeSpectr(Spectrum& result, Spectrum source)
{
	if (result.counts.size() != source.counts.size())
		return;

	for (size_t i = 0; i < result.counts.size(); i++)
	{
		result.counts.at(i) += source.counts.at(i);
	}
}

void gray_all(size_t k, Vec v, Spectrum& s)
{
	if (k == v.getLength()) {
		int tmp = s.basis.calcWeigth(v);
		++s.counts.at(tmp);
		return;
	}

	v[k] = 0;
	gray_all(k + 1, v, s);
	v[k] = 1;
	grayR_all(k + 1, v, s);

}

void grayR_all(size_t k, Vec v, Spectrum& s)
{
	if (k == v.getLength()) {
		int tmp = s.basis.calcWeigth(v);
		++s.counts.at(tmp);
		//std::cout << tmp << std::endl;
		return;
	}
	v[k] = 1;
	gray_all(k + 1, v, s);
	v[k] = 0;
	grayR_all(k + 1, v, s);
}

void calcOneCycle(Spectrum& spectr)
{
	Vec v(spectr.basis.getK());
	gray_all(0, v, spectr);
}

void calcManyCycles(Spectrum& spectr, size_t part = 0)
{
	if (part) part = 1;
	Vec v(spectr.basis.getK());
	std::vector<size_t> scheme = splitScheme(spectr.basis.getK());

	 
	for (int i = 0; i < spectr.basis.getK(); i++)
	{
		if (scheme.at(i)) scheme.at(i) = 1;
		if(part == scheme.at(i))
			gray(v.getLength(), i, v, spectr);
	}
	
}

void threadCalc(Spectrum& spectr) {
	
	Spectrum spectr1 = spectr;
	Spectrum spectr2 = spectr;
	
	auto start = std::chrono::high_resolution_clock::now();

	std::thread T1(calcManyCycles, std::ref(spectr1), 0);
	std::thread T2(calcManyCycles, std::ref(spectr2), 1);

	T1.join();
	T2.join();

	mergeSpectr(spectr1, spectr2);
	spectr = spectr1;

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> durat = end - start;

	std::cout << "Calculation time - " << durat.count() << " seconds";

}



