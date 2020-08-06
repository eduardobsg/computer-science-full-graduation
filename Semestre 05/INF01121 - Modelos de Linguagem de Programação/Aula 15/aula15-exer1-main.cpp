#include <iostream>
#include "aula15-exer1-class.h"

using namespace std;

int main(int argc, char *argv[]) {

	Point point1(10,10), point2(15,30), point3;
  
	point3 = point1 + point2;
	
	cout << point1;
	cout << point2;
	cout << point3;

	return 0;
}
