#include <iostream>
#include <memory>
#include <string>
#include <conio.h>
#include "StlData.hpp"
using std::cout;
using std::endl;
using std::cin;

enum ASCII { ESC = 27, ONE = 49, TWO = 50 };




int main() {					// its just interface to reliable work with algo
	stl::StlData stlDt;
	while (true) {

		std::string  path;
		std::cout << "Enter path to .stl file (\"E:\\SomeCatalog\\Somefile.stl\"):" << std::endl;
		cin >> path;
		if (!stlDt.parseData(path.c_str())) {
			system("cls");
			std::cerr << "ERROR: enter correct path!" << endl;
			continue;
		}

		while (true) {
			system("cls");
			cout << "Press '1' to enter your own coordinate" << endl;
			cout << "Press '2' to choose two random coordinate" << endl;
			cout << "Press ESC to exit" << endl;
			char keyButton = _getch();
			switch (keyButton) {
			case ONE: {
				system("cls");
				cout << "Enter start vertex coord : " << endl;
				float x, y, z;
				cout << "Enter x: ";
				cin >> x;
				cout << endl << "Enter y: ";
				cin >> y;
				cout << endl << "Enter z: ";
				cin >> z;
				cout << endl;
				stl::Vertex  start(x, y, z);
				cout << "Enter end vertex coord:" << endl;
				cin >> x, y, z;
				stl::Vertex end(x, y, z);
				cout << "Shortest distance between start(" << start.x_ << ',' << start.y_ << ',' << start.z_ << ")"
					<< "and end(" << end.x_ << ',' << end.y_ << ',' << end.z_ << ") is: ";
				cout << stlDt.useDijkstraAlgorithm(&start, &end) << endl;
			}
					  break;
			case TWO: {
				size_t randomPosition;
				randomPosition = rand() % stlDt.vertices_.size();
				auto iter = stlDt.vertices_.begin();
				for (int i = 0; i < randomPosition; i++)  iter++;
				stl::Vertex start = *(*iter);
				randomPosition = rand() % stlDt.vertices_.size();
				iter = stlDt.vertices_.begin();
				for (int i = 0; i < randomPosition; i++)  iter++;
				stl::Vertex end = *(*iter);
				cout << "Shortest distance between start(" << start.x_ << ',' << start.y_ << ',' << start.z_ << ")"
					<< "and end(" << end.x_ << ',' << end.y_ << ',' << end.z_ << ") is: ";
				cout << stlDt.useDijkstraAlgorithm(&start, &end) << endl;
				system("pause");
			}
					  break;
			case ESC: {
				return 0;
			}
			}

		}
	}
}
