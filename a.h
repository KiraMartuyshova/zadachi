#pragma once 
#include <iostream>

//Класс чисел с абсолютной погрешностью

class abs_error 
{
public:
	//Конструкторы
	abs_error(); //Конструктор по умолчанию
	abs_error(double x);
	abs_error(double x, double y);
	abs_error(const abs_error& other); //Конструктор копирования
	
	//Перегруженные операторы арифметических операций
	abs_error operator=(const abs_error& other); 
	abs_error operator+=(const abs_error& other); 
	abs_error operator/=(const abs_error& other); 
	abs_error operator*=(const abs_error& other); 
	abs_error operator-=(const abs_error& other); 
	abs_error operator+(const abs_error& other) const; 
	abs_error operator-(const abs_error& other) const;
	abs_error operator*(const abs_error& other) const;
	abs_error operator/(const abs_error& other) const;
	
	//Перегруженный оператор равенства для сравнения двух объектов
	bool operator==(const abs_error& other) const; 
	
	//Перегруженный оператор <<, позволяющий выводить объекты класса в поток 
	friend std::ostream& operator<<(std::ostream& os, const abs_error& num); 

	//Методы получения и установки значений
	double Get_Num() const;			
	double Get_Err() const;
	void Set_Num(double x);
	void Set_Err(double x);

	//Методы вывода
	void Print_Num();
	void Print_Err();
	void Print();

private:
	double num;
	double err;
};
