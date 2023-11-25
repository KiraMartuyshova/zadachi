#pragma once
#include <iostream>
#include <cmath>
#include <fstream>

//Построение треугольника с заданными двумя сторонами и углом между ними при помощи "циркуля и линейки"
using namespace std;

class Point { //Класс точки на плоскости 
private:
    double x, y;

public:
    Point(double trux, double truy) : x(trux), y(truy){} 
	Point() = default; //Конструктор по умолчанию
    Point(const Point& p); //Конструктор копирования
	
	//Методы получения координат 
    double getX() const;
    double getY() const;

	//Перегруженный оператор присваивания
    Point operator=(const Point& p); 
};

class Circle { //Класс окружности с задаными радиусом и центром
private:
    double radius;
    Point center;

public:
    Circle() = default; //Конструктор по умолчанию
    Circle(const Point& c, double r); //Конструктор для создания окружности
    Circle(const Circle& other); //Конструктор копирования

	//Методы для получения радиуса, центра
    double getRadius();
    Point getCenter();

	//Перегруженный оператор присваивания
    Circle operator=(const Circle& p);

	//Метод поиска точек пересения с другой окружностью
    void findIntersection(const Circle& other, Point& intersection1 /*Point& intersection2*/) const;
};

class Triangle { //Класс треугольникас тремя сторонами и вершинами A, B, C
private:
    double AB;
    double BC;
    double ang;
    Point A, B, C;

public:
    Triangle() = default; //Конструктор по умолчанию
    void set_Triangle(double nAB, double nBC, double nang); //Метод для установки сторон и угла

	//Методы для получения вершин
    Point getA();
    Point getB();
    Point getC();


    void print_Triangle(const string& filename) const; //Вывод треугольника в файл
    bool read_Triangle(const string& namefile); //Чтении треугольника из файла
    bool is_Triangle(double nang); //Проверка, является ли заданный угол углом треугльника
};