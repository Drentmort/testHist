#pragma once
#include <valarray>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//������� ���� ���������, ���� ��������� ������������ ����
struct Spectr {
	valarray<long long> counts;
	vector<valarray<size_t>> basis;
	size_t basisVecNum;
	size_t basisVecLen;

	void getDataFromFile(string name);
	size_t calcWeight(valarray<size_t> gen);
	void saveDataToFile();
};

//���������� ���������� ������� �� ������
valarray<size_t> fillArr(string input);

//������� ������������ ��������� ���� ���� � ������� ������������ ���������,
//���������� �������� ���������� ��������� ���������
//������� k ��� ���������� ���� ��������� ���������(��������� �����������)
void enumiration(size_t order, size_t ones_count, valarray<size_t> V, Spectr& spectr);

//�������, �� ������� enumiration, ������� ��������� ������������� ���������� 
void calculate(Spectr& spectr, size_t mask_count, size_t mask_weight);

//����������� �������, ��� ������������ ������������
void threadCalc(Spectr& spectr);
