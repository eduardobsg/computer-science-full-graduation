/*
Definição: Classe para manipular um Ponto. Possui as seguintes especificação: 
- Representação: Coordenada x, Coordenada y 
- Operações: Criação, Set e get x, Set e get y, Soma, Subtração, Clonagem/cópia
*/

#include <iostream>

using namespace std;

class Point {
	
	private:
		double x;
		double y;
	
	public:
		Point();
		Point(double, double);
		~Point();
	
		double getX(void);
		double getY(void);
		Point getPoint(void);
		Point operator+(Point);
		Point operator-(Point);
		Point& operator=(const Point&);
		friend ostream& operator<<(ostream&, const Point&);
	
	protected:
		void setX(double);
		void setY(double);
		void setPoint(double, double);
};
