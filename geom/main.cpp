#include "geom.h"

//Построение треугольника с заданными двумя сторонами и углом между ними при помощи "циркуля и линейки"
//Данные считываются из файла "input.txt", точки для построения рисунка выводятся в "output.txt"
int main(){
    Triangle ABC;
    if(ABC.read_Triangle("input.txt")){
        ABC.print_Triangle("output.txt");
    }
    return 0;
}
