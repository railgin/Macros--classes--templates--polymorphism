#include <iostream>
#include <string>
using namespace std;

struct Comp
{
	string name;
	double frequency;
	int RAM;
};

template<typename T>
class Device
{
protected:
	T* arr;
	int n;
public:
	Device(): n(0)
	{
		arr = new T[n];
	}
	Device(int k): n(k)
	{
		arr = new T[n];
	}
	Device(const Device& Dev)
	{
		this->n = Dev.n;
		this->arr = new T[n];
		for (int i = 0; i < n; i++)
		{
			this->arr[i] = Dev.arr[i];
		}
	}

	~Device()
	{
		delete[] arr;
	}
	
	virtual void input() = 0;
	virtual void output() = 0; //= 0 - должны быть переопределы в дочерних классах
	virtual void filtr(double freq, int ram) = 0;
};

class TComp : public Device<Comp>
{
public:
	TComp(): Device<Comp>(){}
	TComp(int k): Device<Comp>(k){}
	TComp(const TComp & Cmp): Device<Comp>(Cmp){}

	virtual void input()
	{
		cout << "Inputing info for " << n << " computers" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "Input name: ";
			cin >> arr[i].name;
			cout << "Input frequency of processor: ";
			cin >> arr[i].frequency;
			cout << "Input RAM (mb): ";
			cin >> arr[i].RAM;
		}
	}

	virtual void output()
	{
		for (int i = 0; i < n; i++)
		{
			cout << "Name: " << arr[i].name << "\nFrequency: " << arr[i].frequency << "\nRam: " << arr[i].RAM << endl << endl;
		}
	}

	virtual void filtr(double freq, int ram)
	{
		for (int i = 0; i < n; i++)
		{
			if (arr[i].frequency >= freq && arr[i].RAM > ram)
			{
				cout << "Name: " << arr[i].name << "\nFrequency: " << arr[i].frequency << "\nRam: " << arr[i].RAM << endl << endl;
			}
		}
	}
};
int main()
{
	cout << "Enter computers quantity:";
	int n;
	cin >> n;
	TComp computers(n);
	computers.input();
	computers.output();
	/*TComp computers1(computers);
	computers1.output();*/ //пример конструктора копирования
	cout << "Enter frequency and RAM, from which computers needed to print:";
	double ent_ram;
	int ent_freq;
	cin >> ent_freq;
	cin >> ent_ram;
	computers.filtr(ent_freq,ent_ram);
	return 0;
}