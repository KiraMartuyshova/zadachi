#include <iostream>
#include "a.h"
#include <cmath>
#include <chrono>

//Подсчет синуса через ряд Тейлора для чисел с абсолютной погрешностью и вещественных чисел, сравнение результатов 
//Подсчет времени, затраченного на вычисления 

abs_error priv(abs_error& term) { //Приводим значение к диапазону от 0 до 2 pi, чтобы считать большие числа
    double pi = 2 * acos(0.0);
    while (fabs(term.Get_Num()) > 2 * pi) {
        term -= 2 * pi;
    }
    return term;
}


abs_error sin_T(abs_error x, double epsilon) { //Подсчет синуса через ряд Тейлора для чисел с абсолютной погрешностью
    abs_error result;
    result.Set_Num(0.0);
    result.Set_Err(0.0);
    abs_error term = x;
	int n = 1;
	
    priv(term);
	
    while (fabs(term.Get_Num()) >= epsilon) {
        result += term;
        term = (term * x * x / ((2 * n + 1) * (2 * n)))*(-1);
        n++;
    }

    return result;
}

double priv1(double term) { //Приводим значение к диапазону от 0 до 2 pi, чтобы считать большие числа
    double pi = 2 * acos(0.0);
    while (fabs(term) > 2 * pi) {
        term -= 2 * pi;
    }
    return term;
}

double sin_T1(double x, double epsilon) { //Подсчет синуса через ряд Тейлора для вещественных чисел
    double result = 0.0;
    double term = x;
    int n = 1;

    while (fabs(term) >= epsilon) {
        result += term;
        term = -term * x * x / ((2 * n + 1) * (2 * n));
        n++;
    }

    return result;
}


int main() {

    double x_value, x_error, epsilon;

     std::cout << "Введите угол: ";
    
	if(!(scanf("%lf", &x_value))) { //Проверка на то, введено ли пользователем число
		std::cout << "Введено не число" << std::endl; 
		std::terminate();
	}

    std::cout << "Введите абсолютную погрешность угла: ";

	
	if(!(scanf("%lf", &x_error))) { //Проверка на то, введено ли пользователем число
	std::cout << "Введено не число" << std::endl; 
	std::terminate();
	}

    std::cout << "Введите погрешность для синуса: ";
    
	
	if(!(scanf("%lf", &epsilon))) { //Проверка на то, введено ли пользователем число
	std::cout << "Введено не число" << std::endl; 
	std::terminate();
	}
	
    abs_error x(x_value, x_error);
    priv(x); //
    auto start = std::chrono::high_resolution_clock::now(); //Засекаем время, затраченное на подсчет синуса для чисел с абсолютной погрешностью
	abs_error sinResult = sin_T(x, epsilon);
    auto end = std::chrono::high_resolution_clock::now(); //Останавливаем время
    std::chrono::duration<double> time = end - start;
	
	double x1 = priv1(x_value);
    auto start1 = std::chrono::high_resolution_clock::now(); //Засекаем время, затраченное на подсчет синуса для вещественных чисел 
    double sin_Res = sin_T1(x1, epsilon);
    auto end1 = std::chrono::high_resolution_clock::now(); //Останавливаем время
    std::chrono::duration<double> time1 = end1 - start1;
	
	
    std::cout << "sin(" << x_value << " +- " << x_error << ") = ";
    sinResult.Print();
    std::cout << std::endl;
	std::cout << "Время работы: " << time.count() << " секунд" << std::endl;
	std::cout << "sin(" << x_value << ") = " << sin_Res << std::endl;
    std::cout << "Время работы: " << time1.count() << " секунды" << std::endl;

    return 0;
}