#pragma once
#include <vector>

template <typename T>
void quickSortA(std::vector <T>& arr, std::vector <size_t>& indexes, size_t left, size_t right);

template<typename T>
inline void quickSortA(std::vector<T>& arr, std::vector <size_t>& indexes, size_t left, size_t right)
{
	size_t i = left, j = right;
	size_t ind_tmp;
	T tmp;
	T pivot = arr.at((left + right) / 2);

	/* partition */
	while (i <= j) {
		while (arr.at(i) < pivot)
			i++;
		while (arr.at(j) > pivot)
			j--;
		if (i <= j) {
			tmp = arr.at(i);
			arr.at(i) = arr.at(j);
			arr.at(j) = tmp;
			ind_tmp = indexes.at(i);
			indexes.at(i) = indexes.at(j);
			indexes.at(j) = ind_tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSortA(arr, indexes, left, j);
	if (i < right)
		quickSortA(arr, indexes, i, right);
}


template <typename T>
void quickSortD(std::vector <T>& arr, std::vector <size_t>& indexes, size_t left, size_t right);

template<typename T>
inline void quickSortD(std::vector<T>& arr, std::vector <size_t>& indexes, size_t left, size_t right)
{
	size_t i = left, j = right;
	size_t ind_tmp;
	T tmp;
	T pivot = arr.at((left + right) / 2);

	/* partition */
	while (i <= j) {
		while (arr.at(i) > pivot)
			i++;
		while (arr.at(j) < pivot)
			j--;
		if (i <= j) {
			tmp = arr.at(i);
			arr.at(i) = arr.at(j);
			arr.at(j) = tmp;
			ind_tmp = indexes.at(i);
			indexes.at(i) = indexes.at(j);
			indexes.at(j) = ind_tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSortD(arr, indexes, left, j);
	if (i < right)
		quickSortD(arr, indexes, i, right);
}
