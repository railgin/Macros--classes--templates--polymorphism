//Розробити клас, що представляє студента.Студент характеризується
//ім'ям, прізвищем, групою і набором іспитів, які він складав. Іспит
//характеризується назвою предмета, оцінкою студента по ньому і датою
//складання(рік, семестр).Група характеризується курсом і факультетом.
//Розробити методи які дозволяють :
//1. дізнатися повне ім'я студента (ім'я + прізвище) і його курс
//2. дізнатися, чи вчиться він на заданому факультеті
//3. дізнатися найвищу оцінку серед усіх іспитів з даного предмету
//4. додати йому оцінку за іспит(назва передається як параметр)
//5. видалити для нього оцінку за іспит(назва передається як параметр)
//6. дізнатися число іспитів, які він склав зі вказаною оцінкою
//7. дізнатися його середній бал за вказаний семестр

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TExam
{
	string subject_name;
	double mark;
	int year, semestr;
	friend bool operator== (const TExam& t1, const TExam& t2);//чтобы не добавлять геттер
};

struct TGroup
{
	string gr_name;
	int course;
	string facultet;
};

class TStudent
{
private:
	int quantity_of_exams;
	string name, fam;
	TGroup group;
	TExam* Set_of_Exams;
public:
	
	//конс с параметрами
	TStudent(string stud_name, string stud_fam, TGroup stud_group, int qoe) : quantity_of_exams(qoe), name(stud_name),
		fam(stud_fam), group(stud_group)
	{
		Set_of_Exams = new TExam[quantity_of_exams];
	}
	//констр копирования
	TStudent(const TStudent& stud) : quantity_of_exams(stud.quantity_of_exams), name(stud.name), fam(stud.fam),
		group(stud.group)
	{
		for(int i = 0; i < quantity_of_exams; i++)
		{
			this->Set_of_Exams[i] = stud.Set_of_Exams[i];
		}
		cout << "Copy const worked here" << endl;
	}
	~TStudent()
	{
		//delete[] Set_of_Exams;
	}

	string GetFam()
	{
		return (*this).fam;//->this.fam
	}
	string GetName()
	{
		return (*this).name;
	}

	friend ostream& operator<<(ostream& out, const TStudent& st);
	friend void ClearMemory(vector<TStudent> students);

	void CheckFacultet(string facult)
	{
		if (facult == group.facultet)
		{
			cout << "This student is studying on this facultet" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}

	void EnteringExams(int yr, int sem, string subj, double mrk, int pos)
	{
		(*this).Set_of_Exams[pos].mark = mrk;
		(*this).Set_of_Exams[pos].semestr = sem;
		(*this).Set_of_Exams[pos].subject_name = subj;
		(*this).Set_of_Exams[pos].year = yr;
	}

	void InfoExams()
	{
		for (int i = 0; i < quantity_of_exams; i++)
		{
			cout << "----------------------------------------------" << endl;
			cout << "Year:" << (*this).Set_of_Exams[i].year << endl;
			cout << "Semestr:" << (*this).Set_of_Exams[i].semestr << endl;
			cout << "Subject:" << (*this).Set_of_Exams[i].subject_name << endl;
			cout << "Mark:" << (*this).Set_of_Exams[i].mark << endl;
			cout << "----------------------------------------------" << endl;
		}
	}

	double HigherMark(string sub)
	{
		vector <double>  AllMarksFromThisSubj;
		for (int i = 0; i < quantity_of_exams; i++)
		{
			if ((*this).Set_of_Exams[i].subject_name == sub)
			{
				AllMarksFromThisSubj.push_back((*this).Set_of_Exams[i].mark);
			}
		}
		double max = AllMarksFromThisSubj[0];
		for (int i = 1; i < AllMarksFromThisSubj.size(); i++)
		{
			if (AllMarksFromThisSubj[i] > max)
			{
				max = AllMarksFromThisSubj[i];
			}
		}
		return max;
	}

	int QOE_with_mark(double mrk)
	{
		int qoe_count = 0;
		for (int i = 0; i < quantity_of_exams; i++)
		{
			if ((*this).Set_of_Exams[i].mark == mrk)
			{
				qoe_count++;
			}
		}
		return qoe_count;
	}

	double AverageMarkOfSemestr(int sem)
	{
		int quantity_of_marks = 0;
		double sum = 0.0;
		double average = 0.0;
		for (int i = 0; i < quantity_of_exams; i++)
		{
			if ((*this).Set_of_Exams[i].semestr == sem)
			{
				quantity_of_marks++;
				sum += (*this).Set_of_Exams[i].mark;
			}
		}
		average = sum / quantity_of_marks;
		return average; //inf 
	}

	void AddNewExam(int yr, int sem, string subj, double mrk)
	{
		TExam tmp;
		tmp.year = yr;
		tmp.semestr = sem;
		tmp.subject_name = subj;
		tmp.mark = mrk;
		PushBack((*this).Set_of_Exams, quantity_of_exams, tmp);
	}

	void PushBack(TExam *&arr,int &size, const TExam value)
	{
		TExam* New_Set_of_Exams = new TExam[size + 1];
		for (int i = 0; i < size; i++)
		{
			New_Set_of_Exams[i] = arr[i];
		}
		New_Set_of_Exams[size] = value;
		size++;
		delete[] arr;
		arr = New_Set_of_Exams;
	}

	void DeleteEx(int yr, int sem, string subj, double mrk)
	{
		TExam tmp;
		tmp.year = yr;
		tmp.semestr = sem;
		tmp.subject_name = subj;
		tmp.mark = mrk;
		DeleteElemet((*this).Set_of_Exams, quantity_of_exams, tmp);
	}

	void DeleteElemet(TExam*& arr, int& size, const TExam value)
	{
		int position = size;
		for (int i = 0; i < size; i++)
		{
			if ((*this).Set_of_Exams[i] == value)
			{
				position = i;
			}
		}
		TExam* New_Set_of_Exams = new TExam[size - 1];
		for (int i = 0; i < size; i++)
		{
			if (i != position)
			{
				New_Set_of_Exams[i] = arr[i];
			}
		}
		size--;
		delete[] arr;
		arr = New_Set_of_Exams;
	}


	TStudent& operator=(const TStudent& st)
	{
		// Выполняем копирование значений
		quantity_of_exams = st.quantity_of_exams;
		name = st.name;
		fam = st.fam;
		group = st.group;
		Set_of_Exams = st.Set_of_Exams;

		// Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
		return *this;
	}
};

ostream& operator<<(ostream& out, const TStudent& st)
{
	out << "Name:" << st.name << endl;
	out << "Surname:" << st.fam << endl;
	out << "Course:" << st.group.course << endl;
	return out;
}

bool operator== (const TExam& t1, const TExam& t2)
{
	return ((t1.year == t2.year) &&
		(t1.semestr == t2.semestr) && (t1.subject_name == t2.subject_name) && (t1.mark == t2.mark));
}

void StudNameSurnameEnt(string& nam, string& sur)
{
	cout << "Enter name and surname:" << endl;
	cin >> nam >> sur;
}

double SearchingStudNumber(const string& nam, const string& sur, vector<TStudent>& students)
{
	double position;
	for (int i = 0; i < students.size(); i++)
	{

		if (students[i].GetFam() == sur && students[i].GetName() == nam)
		{
			position = i;
			return position;
		}
		else
		{
			cout << "Student not found" << endl;
			exit(0);
		}
	}

}

void ClearMemory(vector<TStudent> students)
{
	for (int i = 0; i < students.size(); i++)
	{
		delete[] students[i].Set_of_Exams;
	}
}

int main()
{
	vector<TStudent> students;
	cout << "Add students in format: Name, Surname, Group name, Facultet, Course, quantity of exams:"
		<< endl;
	char ans;
	int counter = 0;
	string ent_name, ent_surname;

	TGroup ent_group;
	string ent_group_name, ent_facultet;
	int ent_course;

	int ent_quantity_exams;

	do
	{
		cin >> ent_name >> ent_surname;

		//для структуры
		cin >> ent_group_name >> ent_facultet;
		cin >> ent_course;
		//заполнение структуры группы студента введёнными данными
		ent_group.gr_name = ent_group_name;
		ent_group.course = ent_course;
		ent_group.facultet = ent_facultet;

		cin >> ent_quantity_exams;

		TStudent st(ent_name, ent_surname, ent_group, ent_quantity_exams);

		int ent_year, ent_semestr;
		string ent_subject;
		double ent_mark;
		cout << "Enter info about exams in format year/semestr/subject/mark:" << endl;
		for (int i = 0; i < ent_quantity_exams; i++)
		{
			cin >> ent_year >> ent_semestr;
			cin >> ent_subject;
			cin >> ent_mark;
			st.EnteringExams(ent_year, ent_semestr, ent_subject, ent_mark, i);
		}
		students.push_back(st);

		counter++;

		cout << "Do u want to continue adding students? Y/N" << endl;
		cin >> ans;
		if (ans == 'Y')
		{
			continue;
		}
		else
		{
			break;
		}
	} while (true);

	char sign;
	do
	{
		char operation;
		cout << "There are actions with students:" << endl;
		cout << "1 - Check entered students" << endl;
		cout << "2 - Check full student FIO" << endl;
		cout << "3 - Check study on this facultet" << endl;
		cout << "4 - Check info about student exams" << endl;
		cout << "5 - Higher mark of all exams of this subject" << endl;
		cout << "6 - Quantity of exams with definitely mark" << endl;
		cout << "7 - Average mark for the given semestr" << endl;
		cout << "8 - Add mark (add new exam) to student" << endl;
		cout << "9 - Delete exam to student" << endl;
		cout << "Choose number of action:";
		cin >> operation;
		switch (operation)
		{
		case '1':
			for (int i = 0; i < counter; i++)
			{
				cout << students[i] << endl;
			}
			break;
		case '2':
		{
			string ent_sur;
			cout << "Enter surname:";
			cin >> ent_sur;
			for (int i = 0; i < counter; i++)
			{

				if (students[i].GetFam() == ent_sur)
				{
					cout << students[i] << endl;
				}
				else
				{
					cout << "Not found" << endl;
				}
			}
			break;
		}
		case '3':
		{
			string ent_name, ent_surn, ent_facult;
			StudNameSurnameEnt(ent_name, ent_surn);
			cout << "Enter searching facultet:";
			cin >> ent_facult;
			students[SearchingStudNumber(ent_name, ent_surn, students)].CheckFacultet(ent_facult);
			break;
		}
		case '4':
		{
			string ent_name, ent_surname;
			StudNameSurnameEnt(ent_name, ent_surname);
			students[SearchingStudNumber(ent_name, ent_surname, students)].InfoExams();
			break;
		}
		case '5':
		{
			string ent_name, ent_surn, ent_subj;
			StudNameSurnameEnt(ent_name, ent_surn);
			cout << "Enter searching subject:";
			cin >> ent_subj;
			cout << "Higher mark of subject " << ent_subj << " is "
				<< students[SearchingStudNumber(ent_name, ent_surn, students)].HigherMark(ent_subj) << endl;
			break;
		}
		case '6':
		{
			string ent_nam, ent_sur;
			double ent_mark;
			StudNameSurnameEnt(ent_nam, ent_sur);
			cout << "Enter mark:";
			cin >> ent_mark;
			cout << "Quantity of exams with mark " << ent_mark << " is " <<
				students[SearchingStudNumber(ent_name, ent_sur, students)].QOE_with_mark(ent_mark) << endl;
			break;
		}
		case '7':
		{
			string ent_nam, ent_sur;
			int ent_sem;
			StudNameSurnameEnt(ent_nam, ent_sur);
			cout << "Enter semestr:";
			cin >> ent_sem;
			cout << "Average mark of this semestr is " << 
				students[SearchingStudNumber(ent_name, ent_sur, students)].AverageMarkOfSemestr(ent_sem) << endl;
			break;
		}
		case '8':
		{
			string ent_nam, ent_sur;
			
			StudNameSurnameEnt(ent_nam, ent_sur);
			cout << "Enter new exam in format Year/Semestr/Subject/Mark" << endl;
			int ent_year, ent_sem;
			string ent_subj;
			double ent_mrk;
			cin >> ent_year >> ent_sem;
			cin >> ent_subj;
			cin >> ent_mrk;
			students[SearchingStudNumber(ent_name, ent_sur, students)].AddNewExam(ent_year, ent_sem, ent_subj, ent_mrk);
			break;
		}
		case '9':
		{
			string ent_nam, ent_sur;

			StudNameSurnameEnt(ent_nam, ent_sur);
			cout << "Enter deleting exam in format Year/Semestr/Subject/Mark" << endl;
			int ent_year, ent_sem;
			string ent_subj;
			double ent_mrk;
			cin >> ent_year >> ent_sem;
			cin >> ent_subj;
			cin >> ent_mrk;
			students[SearchingStudNumber(ent_name, ent_sur, students)].DeleteEx(ent_year, ent_sem, ent_subj, ent_mrk);
			break;
		}

		default:
			break;
		}


		cout << "Do you want to continue do operations? Y/N:";
		cin >> sign;
	} while (sign == 'Y');

	ClearMemory(students);

	return 0;
}