#include "a.h"
#include <iostream>
//Связан с файлом "test3.cpp"
//Класс чисел с абсолютной погрешностью

abs_error::abs_error() { 
	this->num = 0;
	this->err = 0;
}
	
abs_error::abs_error(double x) { 
	this->num = x;
	this->err = 0.0;
}

abs_error::abs_error(double x, double y) { 
	this->num = x;
	this->err = y;
}


abs_error::abs_error(const abs_error& other) { 
	this->num = other.num;
	this->err = other.err;
}

abs_error abs_error::operator=(const abs_error& other) { 
	this->num = other.num;
	this->err = other.err;
	return *this;
}

abs_error abs_error::operator+=(const abs_error& other) {
	this->num = this->num + other.num;
	this->err = this->err + other.err;
	return *this;
}
abs_error abs_error::operator/=(const abs_error& other) {
	double a = this->num, b = this->err;
	
	if (!(other.num <= 0 and other.num >= 0)) {
		this->num = a * other.num;
		this->err = (a * other.err + b * other.num) / (other.num * other.num);
	}
	else {
		std::cout << "Деление на ноль, операция не выполнена :( ";
		return *this;
	}
	
	return *this;
}

abs_error abs_error::operator*=(const abs_error& other) {
	double a = this->num, b = this->err;
	this->num = a * other.num;
	this->err = a * other.err + b * other.num;
	return *this;
}
abs_error abs_error::operator-=(const abs_error& other) {
	this->num = this->num - other.num;
	this->err = this->err + other.err;
	return *this;
}
abs_error abs_error::operator+(const abs_error& other) const { 
	abs_error c;
	c.num = this->num + other.num;
	c.err = this->err + other.err;
	return c;
}
abs_error abs_error::operator-(const abs_error& other) const {
	abs_error c;
	c.num = this->num - other.num;
	c.err = this->err + other.err;
	return c;
}
abs_error abs_error::operator*(const abs_error& other) const {
	abs_error c;
	c.num = this->num * other.num;
	c.err = this->num*other.err + this->err * other.num;
	return c;
}
abs_error abs_error::operator/(const abs_error& other) const {
	abs_error c;
	if (!(other.num <= 0 and other.num >= 0)) {
		c.num = this->num / other.num;
		c.err = (this->num * other.err + this->err * other.num) / (other.num * other.num);
	}
	else {
		std::cout << "Деление на ноль, операция не выполнена :( ";
		c.num = this->num;
		c.err = this->err;
	}
	return c;
}

bool abs_error::operator==(const abs_error& other) const {
    return (this->num == other.num) && (this->err == other.err);
}

std::ostream& operator<<(std::ostream& os, const abs_error& num) {
    os << num.Get_Num() << " +- " << num.Get_Err();
    return os;
}

double abs_error::Get_Num () const{
	return this->num;
}
double abs_error::Get_Err () const{
	return this->err;
}
void abs_error::Set_Num(double x) {
	this->num = x;
}
void abs_error::Set_Err(double x) {
	this->err = x;
}

void abs_error::Print_Num() {
	std::cout << "Значение числа: " << this->num << " ";
}
void abs_error::Print_Err() {
	std::cout << "Абсолютная погрешность числа: " << this->err << " ";
}
void abs_error::Print() {
	std::cout << this->num << " +- " << this->err << " ";
}
