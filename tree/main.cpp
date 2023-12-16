#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <chrono>
#include "Twothreetree1.h"

using namespace std;
using namespace chrono;

//Проверка совпадения частотных словарей
void Equality(const TwoThreeTree<string, int>& tree, const map<string, int>& STLdictionary) {
    bool equal = false;
    for (const auto& pair : STLdictionary) {
		int value;
		if (tree.find(pair.first, value)) {
            if (value != pair.second) {
                cout << "Слово: " << pair.first << " имеет несовпадающую частоту: " << pair.second << " (STL) vs " << value << " (2-3 дерево)" << endl;
                equal = true;
            }
		} else {
            cout << "Слово: " << pair.first << " отсутствует в 2-3 дереве" << endl;
            equal = true;
        }
    }
	 
    if (!equal) {
        cout << "Частотные словари совпадают." << endl;
    }
}

int main() {
    //ТЕСТИРОВАНИЕ ОШИБОК
    TwoThreeTree<string, int> tree;
    TwoThreeTree<string, int> tree1;
	
    try {
        //Попытка открыть несуществующий файл
        tree.readFile("nofile.txt");
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    //Попытка открыть пустой файл
    string filename = "file.txt";
    tree1.readFile(filename);
    //ЗАВЕРШЕНИЕ ТЕСТА ОШИБОК


    //Измерение времени для реализации с моим 2-3 деревом
    auto start1 = high_resolution_clock::now(); //Засекаем время

    TwoThreeTree<string, int> dictionary; //Создаем 2-3 дерево
    dictionary.readFile("text.txt"); //Открываем файл, считываем слова
	
    cout << "Частота встречаемости слов в тексте (2-3 дерево):" << endl;
    dictionary.print_tree();

    auto end1 = high_resolution_clock::now(); //Останавливаем время
    duration<double> time1 = end1 - start1;
    cout << "Время выполнения моей программы: " << time1.count() << " секунд" << endl;

    //Измерение времени для STL
	auto start2 = high_resolution_clock::now(); //Засекаем время
	
	map<string, int> dictionary1; //Создаем дерево
    
	ifstream file("text.txt"); //Открываем файл 
    if (!file.is_open()) { //Проверяем на открытие файл
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) { //Считываем слова из файла построчно
        istringstream iss(line); //Создаем строковой поток
		
        string word;
        while (iss >> word) {
            for (char& c : word) {
                c = tolower(c);
                if (ispunct(c)) {
                    c = '\0'; 
                }
            }
            if (!word.empty()) {
                dictionary1[word]++;
            }
        }
    }

    file.close(); //Закрытие файла

    cout << "\nЧастота встречаемости слов в тексте для STL:" << endl;
    for (const auto& pair : dictionary1) {
        cout << "Слово: " << pair.first << "; Частота: " << pair.second << endl;
    }

    auto end2 = high_resolution_clock::now(); //Останавливаем время
    duration<double> time2 = end2 - start2;
    cout << "Время выполнения библиотечной программы: " << time2.count() << " секунд" << endl << endl;
		
    //Вызов проверки совпадения частотных словарей
    Equality(dictionary, dictionary1);

    return 0;
}
