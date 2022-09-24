//Створити шаблонний базовий клас, який містить одновимірний
//шаблонний масив.Визначити конструктор за замовчуванням, конструктор з
//параметрами і конструктор копіювання.Деструктор має бути віртуальним.У
//базовому класі визначити чисто віртуальні методи введення і виведення.
//Створити клас наступник, в якому зазначено, що масив є масивом
//структур з ім'ям STUDENT, який містить наступні поля: прізвище та ініціали;
//номер групи; успішність(масив з п'яти елементів).
//	Перевизначити функції введення і виведення.
//	Реалізувати у вигляді методів виведення на дисплей прізвищ і номерів
//	груп для всіх студентів, включених до масиву, якщо середній бал студента
//	більше заданого, якщо таких студентів немає, вивести відповідне повідомлення.
//	Написати програму, що виконує наступні дії : ведення з клавіатури даних
//	в масив, що складається структур типу STUDENT; виведення на дисплей
//	прізвищ і номерів груп для всіх студентів, включених в масив, якщо середній
//	бал студента більше заданого
#include <iostream>
#include <string>
using namespace std;

struct Student
{
	string name, surname, patronymic;
	int group_number;
	double marks[5];
};

template <typename A>
class Abstract
{
protected:
	int n;
	A* arr;
public:
	Abstract():n(0) 
	{
		arr = new A[n];
	}
	Abstract(int k) : n(k)
	{
		arr = new A[n];
	}
	Abstract(const Abstract& Abst)
	{
		this->n = Abst.n;
		this->arr = new A[n];
		for (int i = 0; i < n; i++)
		{
			this->arr[i] = Abst.arr[i];
		}
	}
	~Abstract()
	{
		delete[] arr;
	}

	virtual void input() = 0;
	virtual void output() = 0; 
	virtual void filtr() = 0;

};

class TStud: public Abstract<Student>
{
public:
	TStud(): Abstract<Student>(){}
	TStud(int k): Abstract<Student>(k){}
	TStud(const TStud &st): Abstract<Student>(st){}

	virtual void input()
	{
		cout << "Inputing info for " << n << " students" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "enter name/surname/fam" << endl;
			cin >> arr[i].name >> arr[i].surname >> arr[i].patronymic;
			cout << "Enter group number:";
			cin >> arr[i].group_number;
			cout << "Enter five marks: ";
			for (int j = 0; j < 5; j++)
			{
				cin >> arr[i].marks[j];
			}
		}
	}

	virtual void output()
	{
		for (int i = 0; i < n; i++)
		{
			
			cout << "FIO: " << arr[i].name << " " << arr[i].surname << " " << arr[i].patronymic << endl;
			cout << "Group number: " << arr[i].group_number << endl;
			cout << "marks: ";
			for (int j = 0; j < 5; j++)
			{
				cout << arr[i].marks[j] << "|";
			}
			cout << endl;
		}
	}
	virtual void filtr()
	{
		double ent_mark;
		cout << "Enter mark, from which need to print students:";
		cin >> ent_mark;
		
		for (int i = 0; i < n; i++)
		{
			double local_average = 0.0;
			for (int j = 0; j < 5; j++)
			{
				local_average += arr[i].marks[j];
			}
			local_average /= 5;
			if (local_average > ent_mark)
			{
				cout << arr[i].surname << " from group " <<arr[i].group_number << ", Avg = " << local_average << endl;
			}
		}
	}
};

int main()
{
	int n;
	cout << "Enter quantity of students:";
	cin >> n;
	TStud students(n);
	students.input();
	students.output();
	students.filtr();


	return 0;

}