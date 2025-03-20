#include <iostream>
/*
	1. ���������� ������������
	������������ � ��� ��������� ���, ����������� ���������� ������ � ������
	�� ��������� � ���� ������ ��������, ������� ���������� ������� ��� 
	����������, � �������� �� � ������� ������������� ������� private � protected.
*/

//class User
//{
//private:
//	int age;
//public:
//	void SetAge(int age)
//	{
//		if (age > 0)
//			this->age;
//	}
//};

/*
	2. ��� ����� ������������
	3. ����������� ������������
	������������ � ��� ��������� ���, ������� ��������� ��������� ����� ������ 
	�� ������ ��� ������������.
*/

/*
	4. ���������� ������������
	��������� ������������:
	class ���_���������_������ : �����������_������������ ���_�������������_������
	{
		���������� ������
	};

	��������� �����������:
	�������� -> ������������
	����������� -> �������
*/

struct Point{};

class Person{};

class Vehicle
{
private:
	Point position;
	double height;
	double length;
	double width;
	double weight;
public:
	void Move(Point direction);
	void Rotate(Point direction);
	void Scale(float factor);
};

class Car : public Vehicle
{
private:
	int doors;
	int tankCapacity;
	char model[30];
	char mark[30];
	bool isStarted;
public:
	void FillUp(int points);
	void Start();
};

class Plane : public Vehicle
{
private:
	int seets;
	Point route[2];
public:
	void AuthorizePeople(const Person* peopleList);
	void Fly();
	void CallDispatcher(Person dispatcher);
};

int main()
{
	Car car;
	Plane plane;
	//car.Move();
	//plane.Move();
	return 0;
}