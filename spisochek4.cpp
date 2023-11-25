#include <iostream>
#include <fstream>
#include <forward_list>
#include <algorithm>
#include <list>
#include <chrono>
#include "spisok4.h"

//Однонаправленный список, внешний итератор
//Сортировка списка методом insertion (по возрастанию и убыванию), проверка на корректную работу сортировки
//Сравнение библиотечной сортировки и моей, время работы двух программ
using namespace std;
using namespace chrono;

void read1(forward_list<double>& spisok, const string& filename) { //Метод для считывания списка из файла
    ifstream file(filename);
    double value;
    while (file >> value) {
        spisok.push_front(value);
    }
    file.close();
}

void read2(List<double>& spisok, const string& filename) { //Метод для считывания списка из файла
    ifstream file(filename);
    double value;
    while (file >> value) {
        spisok.prepend(value);
    }
    file.close();
}

void Program() { //Создание односвязного списка класса List и его сортировка по возрастанию
    List<double> spisok;
    read2(spisok, "1.txt");

    auto start1 = high_resolution_clock::now(); //Засекаем время
  
    cout << "Исходный список: ";
    spisok.print(); 

    spisok.insertionSort(true); //Сортируем список по возрастанию методом insertion
	//spisok.insertionSort(false); //Сортируем список по убыванию методом insertion

    cout << "Отсортированный список: ";
    spisok.print(); 
  
    auto end1 = high_resolution_clock::now(); //Останавливаем время
    duration<double> time1 = end1 - start1;
    cout << "Время выполнения моей программы: " << time1.count() << " секунд" << endl;
	
	//Проверка сортировки по возрастанию
	bool res = spisok.proverka(true);
	if(!res) {
		cout << "Неверная сортировка :( ";
	}
	
	/*/Проверка сортировки по убыванию
	bool res1 = spisok.proverka(false);
	if(!res1) {
		cout << "Неверная сортировка :( ";
	}*/
}

int main() {
    forward_list<double> spisok;
    read1(spisok, "1.txt");

    auto start2 = high_resolution_clock::now(); //Засекаем время
  
    cout << "Исходный список: ";
    for (const auto& elem : spisok) {
        cout << elem << " ";
    }
    cout << endl;
  
    spisok.sort(); //Сортируем список по возрастанию библиотечной сортировкой
	//spisok.sort(greater<double>()); //Сортируем список по убыванию библиотечной сортировкой

    cout << "Отсортированный список: ";
    for (const auto& elem : spisok) {
        cout << elem << " ";
    }
    cout << endl;

    auto end2 = high_resolution_clock::now(); //Останавливаем время
    duration<double> time2 = end2 - start2;
    cout << "Время выполнения библиотечной программы: " << time2.count() << " секунд" << endl << endl;
	
    Program(); 

    return 0;
}