#include <iostream>
#include <thread>
#include "gen.h"

using namespace std;

int main(int argc, char *argv[]){	

	if (argc != 2) {
		cerr << "Incorrect count of input values" << endl;
		return 1;
	}

	Spectr spectr;

	spectr.getDataFromFile(argv[1]);

	threadCalc(spectr);

	spectr.saveDataToFile();

}

