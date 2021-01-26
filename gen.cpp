#include <iostream>
#include <thread>
#include <chrono>
#include "gen.h"

void Spectr::getDataFromFile(string name)
{
	ifstream file(name);

	if (!file.is_open()) {
		cerr << "there is no file with this name" << endl;
		exit(3);
	}

	std::string buffer;
	basisVecNum = 0;
	basisVecLen = 0;

	do
	{
		file >> buffer;

		valarray<size_t> tmp = fillArr(buffer);
		basis.push_back(tmp);

		++basisVecNum;
		if (basisVecNum > 1 && 
			basisVecLen != buffer.size()) {

			cerr << "Incorrect input data";
			exit(4);
		}

		basisVecLen = tmp.size();
		buffer.clear();

	} while (!file.eof());


	counts.resize(basisVecLen+1);
	file.close();
}

size_t Spectr::calcWeight(valarray<size_t> gen)
{
	valarray<size_t> tmp(basisVecLen);
	for (size_t i = 0; i < basisVecNum ; i++) {
		if (gen[i]) tmp ^= basis.at(i);
	}

	size_t weight = tmp.sum();
	return weight;
}

void Spectr::saveDataToFile()
{
	string name = "out_";
	name += to_string(basisVecNum);
	name += '_';
	name += to_string(basisVecLen);
	name += ".txt";

	ofstream outFile(name);

	for (size_t i = 0; i < counts.size(); i++)
	{
		outFile << i << '\t' << counts[i] << std::endl;
	}
	outFile.close();
}

valarray<size_t> fillArr(string input)
{
	valarray<size_t> output(input.size());
	for (int i = 0; i < output.size(); i++) {
		if (input[i] == '0')
			output[i] = 0;
		else if (input[i] == '1')
			output[i] = 1;
		else {
			cerr << "incorrect data" << endl;
			exit(2);
		}
	}

	return output;
}

void enumiration(size_t order, size_t ones_count, valarray<unsigned int> V, Spectr& spectr)
{
	if (order == ones_count) {
		for (size_t i = V.size() - order; i < V.size(); i++)
			V[i] = 1;

		int tmp = spectr.calcWeight(V);
		++spectr.counts[tmp];
		return;
	}
	else if (ones_count == 0) {
		for (size_t i = V.size() - order; i < V.size(); i++)
			V[i] = 0;

		int tmp = spectr.calcWeight(V);
		++spectr.counts[tmp];
		return;
	}
	else {
		V[V.size() - order] = 1;
		enumiration(order - 1, ones_count - 1, V, spectr);
		V[V.size() - order] = 0;
		enumiration(order - 1, ones_count, V, spectr);
	}
}

void calculate(Spectr& spectr, size_t mask_count, size_t mask_weight) {
	
	if (mask_count > mask_weight)
		return;

	valarray<size_t> V(spectr.basisVecNum);

	for (int i = mask_count-1; i <= spectr.basisVecNum; i += mask_weight)
	{
		enumiration(V.size(), i, V, spectr);
	}
}

void threadCalc(Spectr& spectre)
{
	size_t thread_count = thread::hardware_concurrency();
	vector<thread> threads;
	threads.reserve(thread_count);

	auto start = chrono::high_resolution_clock::now();

	vector<Spectr> spectries (thread_count,spectre);
	
	for (int i = 0; i < thread_count; ++i) {
		threads.emplace_back(calculate, std::ref(spectries.at(i)), i+1,thread_count);
	}

	for (auto& thread : threads) {
		thread.join();
	}

	for (auto& element : spectries) {
		spectre.counts += element.counts;
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> durat = end - start;

	cout << "Calculation time - " << durat.count() << " seconds";

}
