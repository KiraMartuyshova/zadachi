#pragma once 
#include <iostream>

//����� ����� � ���������� ������������

class abs_error 
{
public:
	//������������
	abs_error(); //����������� �� ���������
	abs_error(double x);
	abs_error(double x, double y);
	abs_error(const abs_error& other); //����������� �����������
	
	//������������� ��������� �������������� ��������
	abs_error operator=(const abs_error& other); 
	abs_error operator+=(const abs_error& other); 
	abs_error operator/=(const abs_error& other); 
	abs_error operator*=(const abs_error& other); 
	abs_error operator-=(const abs_error& other); 
	abs_error operator+(const abs_error& other) const; 
	abs_error operator-(const abs_error& other) const;
	abs_error operator*(const abs_error& other) const;
	abs_error operator/(const abs_error& other) const;
	
	//������������� �������� ��������� ��� ��������� ���� ��������
	bool operator==(const abs_error& other) const; 
	
	//������������� �������� <<, ����������� �������� ������� ������ � ����� 
	friend std::ostream& operator<<(std::ostream& os, const abs_error& num); 

	//������ ��������� � ��������� ��������
	double Get_Num() const;			
	double Get_Err() const;
	void Set_Num(double x);
	void Set_Err(double x);

	//������ ������
	void Print_Num();
	void Print_Err();
	void Print();

private:
	double num;
	double err;
};
