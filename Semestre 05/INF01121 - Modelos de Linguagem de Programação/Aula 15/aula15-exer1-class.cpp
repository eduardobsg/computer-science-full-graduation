#include "aula15-exer1-class.h"

//Construtor
Point::Point() {
	this->x = 0;
	this->y = 0;
}
Point::Point(double _x, double _y) {
	this->x = _x;
	this->y = _y;
}

//Destrutor
Point::~Point() {
	//cout << "Ponto: (" << this->x << "," << this->y << ") foi destruido." << endl;
}

//Getters
double Point::getX() {
	return this->x;
}
double Point::getY() {
	return this->y;
}
Point Point::getPoint() {
	return Point(this->x, this->y);
}

//Setters
void Point::setX(double _x) {
	this->x = _x;
}
void Point::setY(double _y) {
	this->y = _y;
}
void Point::setPoint(double _x, double _y) {
	this->x = _x;
	this->y = _y;
}

//Operations
Point Point::operator+(Point p) {
	Point pt;
	pt.x = this->x + p.x;
	pt.y = this->y + p.y;
	return pt;
}

Point Point::operator-(Point p) {
	Point pt;
	pt.x = this->x - p.x;
	pt.y = this->y - p.y;
	return pt;
}

Point& Point::operator=(const Point& p) {
	this->x = p.x;
	this->y = p.y;
	return *this;
}

ostream& operator<<(ostream &out, const Point &p) {
    out << "Point: (" << p.x << "," << p.y << ")" << endl;
    return out;
}


