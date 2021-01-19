#pragma once
#include <vector>
#include <string>

//��� ������ ������, ������� �������� 0/1
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

//���������� �������� � ������ �������, ������ ���������� �����
void equalVecLen(Vec& v1, Vec& v2);

//��� ������, ������� ��������� ����� ��������, ������� �������� ����������� ���������
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
//��� ������, ���������� ����������� ��������� � ������������� �����.
struct Spectrum {

	std::vector<int> counts;
	Set basis;
	Spectrum();
	Spectrum(Set vectors);

	void saveDataToFile();
};
void mergeSpectr(Spectrum& result, Spectrum source);

//������� ��������� ���� ���� � ������� ������������ ���������
//������� k ��� ���������� ���� ��������� ��������� (��������� �����������)
void gray_all(size_t k, Vec v, Spectrum& s);
void grayR_all(size_t k, Vec v, Spectrum& s);

//������� ������������ ��������� ���� ���� � ������� ������������ ���������,
//���������� �������� ���������� ��������� ���������
//������� k ��� ���������� ���� ��������� ���������(��������� �����������)
void gray(size_t u, size_t v, Vec V, Spectrum& spectr);

//��������� �����
template <typename T>
long long factorial(T x);

//���������� �������� ����������� ������ ���������
void calcOneCycle(Spectrum& spectr);

//������� ���������� ���� ��������� ���������(������� ������������ �������)
std::vector<long long> combinationsVec(size_t power);
//��������� ���� ����������� � �������� ���������� ��������� ����� (��������� ������� �������� �������
// ��� �������� � ������������ ���������������� ���������)
std::vector<size_t> splitScheme(size_t power);

//���������� �������� �����������, ��������� ������������,
//������� �������� �������� ���������� ��������� ���������
//��� ����� �������������� ����������!!!!!
void calcManyCycles(Spectrum& spectr, size_t part);

//������ ����������� ���������� (�������� �� ����������!)
//��� ����������� ���� �������� �������� ��������� �� ������ � ����������� �� ����� ���������,
//������� ���� ��������� � ������ ������������.
void threadCalc(Spectrum& spectr);


