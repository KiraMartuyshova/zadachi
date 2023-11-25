#pragma once 
#include <iostream>

//Êëàññ ÷èñåë ñ àáñîëþòíîé ïîãðåøíîñòüþ

class abs_error 
{
public:
	//Êîíñòðóêòîðû
	abs_error(); //Êîíñòðóêòîð ïî óìîë÷àíèþ
	abs_error(double x);
	abs_error(double x, double y);
	abs_error(const abs_error& other); //Êîíñòðóêòîð êîïèðîâàíèÿ
	
	//Ïåðåãðóæåííûå îïåðàòîðû àðèôìåòè÷åñêèõ îïåðàöèé
	abs_error operator=(const abs_error& other); 
	abs_error operator+=(const abs_error& other); 
	abs_error operator/=(const abs_error& other); 
	abs_error operator*=(const abs_error& other); 
	abs_error operator-=(const abs_error& other); 
	abs_error operator+(const abs_error& other) const; 
	abs_error operator-(const abs_error& other) const;
	abs_error operator*(const abs_error& other) const;
	abs_error operator/(const abs_error& other) const;
	
	//Ïåðåãðóæåííûé îïåðàòîð ðàâåíñòâà äëÿ ñðàâíåíèÿ äâóõ îáúåêòîâ
	bool operator==(const abs_error& other) const; 
	
	//Ïåðåãðóæåííûé îïåðàòîð <<, ïîçâîëÿþùèé âûâîäèòü îáúåêòû êëàññà â ïîòîê 
	friend std::ostream& operator<<(std::ostream& os, const abs_error& num); 

	//Ìåòîäû ïîëó÷åíèÿ è óñòàíîâêè çíà÷åíèé
	double Get_Num() const;			
	double Get_Err() const;
	void Set_Num(double x);
	void Set_Err(double x);

	//Ìåòîäû âûâîäà
	void Print_Num();
	void Print_Err();
	void Print();

private:
	double num;
	double err;
};
