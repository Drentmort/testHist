#include <iostream>
#include <chrono>
#include "gen.h"
#include "sort.h"

int main(){

	Set set;
	std::string name = "tst_20_32.txt";
	std::string dir = "C:\\Users\\Anton\\source\\repos\\TestVecrt\\TestVecrt";
	set.getDataFromFile(name, dir);
	Spectrum spectr(set);

	threadCalc(spectr);
	spectr.saveDataToFile();
	
	
	
}

