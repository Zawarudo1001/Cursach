#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>
#include <windows.h>
#include <conio.h>
#include <fstream>

const int maxStrSize = 256;

using namespace std;

const char *errmsg[] = { "\nОшибка при вводе даты рождения\n",
						 "\nНеверный формат номера студенческого билета\n",
						 "\nНедопустимое количество предметов в указанном семестре!\n",
						 "\nОшибка ввода! Недопустимый символ: ",
						 "\nОшибка ввода! Строка не должна быть пустой.\n",
						 "\nВвод некорректен!\n",
						 "\nОшибка ввода! Вводимые значения вводятся на русской раскладке.\n",
						 "\nОшибка ввода! Вводимое значение должно начинаться c заглавной буквы!\n",
						 "\nОшибка ввода! Вводимое значение не может содержать несколько заглавных букв!\n",
						 "\nНекорректно введена дата рождения!\n",
						 "\nУказываемый год рождения должен быть в диапазоне 1970-2024!\n",
						 "\nНомер зачетной книжки не соотвествует необходимому формату!\n",
						 "\nГод поступления меньше года рождения!\n",
						 "\nНомер группы не соотвествует необходимому формату!\n",
						 "\nВведенное значение не должно быть пустой строкой!\n",
						 "\nНеправильно указан пол!\n",
						 "\nУказано неправильное количество семестров!\n",
						 "\nВведенное значение не соотвествует указанному диапазону!\n",
						 "\nТакой предмет уже есть в списке!\n",
						 "\nСтудент с таким номером зачетки уже существует!\n",
						 "\nСтудент с указанным номером зачетки не найден!\n",
						 "\nВводимый год должен находиться в диапазоне 1970-2024!\n",
						 "\nУказан неверный номер семестра!\n",
						 "\nСписок студентов пуст!\n"
};

const char *sysmsg[] = { "\nВвод корректен.\n",
						 "\nМаксимальный размер вводимого адреса 256 символов. Введите полный путь к файлу:\n",
						 "::::::::::::::-> ",
						 "Введите 1 если хотите работать с внутренней базой данных. Иначе введите 2\n",
						 "\nВведите имя студента(20)\n",
						 "\nВведите фамилию студента(20)\n",
						 "\nВведите отчество студента(20)\n",
						 "\nВведите дату рождения(dd.mm.yyyy)\n",
						 "\nВведите номер зачетной книжки(NNLNNNN; N-цифра, L-буква)\n",
						 "\nВведите номер группы(LLLL-NN-NN; N-цифра, L-буква)\n",
						 "\nВведите название учебной кафедры(30)\n",
						 "\nУкажите количество семестров\n",
						 "\nУкажите пол(М/Ж)\n",
						 "\n§ Введите количество названия предметов за указанное количество семестров.\n",
						 "\n§ Укажите оценки по введенным предметам(2-5, введите 0 если оценки нет)\nУчтите, что отсутствие оценки будет исключать предмет при оценке успеваемости\n",
						 "\nДанные изменены\n",
						 "Выберите действие:(w - вверх, s - вниз, Enter - выбрать, Esc - главное меню)\n",
						 "\nНажмите любую клавишу для возврата в главное меню\n",
						 "\nДанные о студенте удалены\n",
						 "\n[1] Добавить новую запись о студенте",
						 "[2] Просмотреть/Редактировать информацию о существующем студенте",
						 "[3] Вывести всю базу студентов",
						 "[4] Показать всех студентов без единой тройки за весь период обучения с выборкой по полу",
						 "[5] Удалить запись о студенте",
						 "[6] Выход из программы",
						 "[1] Изменить фамилию",
						 "[2] Изменить имя",
						 "[3] Изменить отчество",
						 "[4] Изменить дату рождения",
						 "[5] Изменить пол",
						 "[6] Изменить номер зачетной книжки",
						 "[7] Изменить номер группы",
						 "[9] Изменить название факультета",
						 "[9] Изменить название кафедры",
						 "[10] Изменить названия предметов",
						 "[11] Изменить оценки",
						 "\nЗавершение работы программы...\n",
						 "\nВ каком семестре будет отредактирована информация?\n",
						 "\nВведите новую оценку по предмету  (оценки по пустым предметам будут приняты, но не будут внесены в базу!)\n",
						 "\nВведите новое название предмета\n",
						 "\n+=====================================================================================================================+",
						 "|       Фамилия      |         Имя        |      Отчество      |  Номер зачетки  |    Группа    |   Год поступления   |",
						 "+---------------------------------------------------------------------------------------------------------------------+\n",
						 "\nВведите название факультета(30)\n",
};

#undef max
using namespace std;

class StrManager {
public:
	void setstr(char* s, const char *a);

	virtual char* CharStrAdd(char *dest, const char *src) {
		size_t i, j;
		for (i = 0; dest[i] != '\0'; i++);
		for (j = 0; src[j] != '\0'; j++)
			dest[i + j] = src[j];
		dest[i + j] = '\0';
		return dest;
	}

	virtual char* CharStrCopy(char *d, const char *s) {
		char *saved = d;
		while (*s)
		{
			*d++ = *s++;
		}
		*d = 0;
		return saved;
	}
};


void StrManager::setstr(char* s, const char *a) {
	char c = 1;
	int i = 0;
	while (c != '\0') {
		s[i] = a[i];
		i++;
		c = a[i];
	}
	s[i] = '\0';
}

StrManager InputManager;

class Student {
public:
	struct info {
		char name[20];
		char surname[20];
		char lastname[20];
		char bdate[11];
		int byear;
		int postyear;
		char fak[30];
		char kaf[30];
		char group[11];
		char zachetka[8];		//наиболее важный параметр в данных студента
		unsigned char sex;
		char predmname[9][10][30];		//9 семестров по 10 предметов по 30 букв на предмет
		char notes[9][10];
	};

	info StudentInfo;

	Student() {
		memset((char*)&StudentInfo.predmname, 0, sizeof(StudentInfo.predmname));
		memset((char*)&StudentInfo.notes, 0, sizeof(StudentInfo.notes));
	};
	~Student() {};
};


class StudentList {
public:
	size_t size = 0;
	struct Node
	{
		Node* next = nullptr;
		Student data;
		Node() {};
		Node(Student &student) { data = student; }
	};

	Node* head = nullptr;
	Node* end = nullptr;

	void append(Student &student);
	void del(size_t index);
	void delete_all();

	Student get_val(size_t index);
	Student* get_element(size_t index);

	StudentList() {}
	~StudentList() {
		delete_all();
	}

	Student operator[](size_t index) {
		return get_val(index);
	}

	Student* operator()(size_t index) {
		return get_element(index);
	}
};

void StudentList::append(Student &student) {
	Node* temp = head;
	size++;
	if (temp == nullptr) {
		head = new Node(student);
		end = head;
	}
	else {
		end->next = new Node(student);
		end = end->next;
	}
}

void StudentList::del(size_t index) {
	Node* temp;
	Node* prev;
	temp = head;
	prev = head;
	if (index >= size) return;
	for (size_t t = 0; t < index; t++) {
		prev = temp;
		temp = temp->next;
	}
	if (index == size - 1) {
		end = prev;
	}
	if (index > 0 && size > 1) {
		prev->next = temp->next;
		delete temp;
	}
	if (index == 0) {
		if (size > 1) {
			head = temp->next;
			delete temp;
		}
		else {
			delete temp;
			head = nullptr;
			end = nullptr;
		}
	}
	size--;
}

Student StudentList::get_val(size_t index) {
	if (index >= size) return end->data;		//если значение выходит за пределы размера списка, вернем самое крайнее значение
	Node* temp = head;
	for (size_t t = 0; t < index; t++) {
		temp = temp->next;
	}
	return temp->data;
}

Student* StudentList::get_element(size_t index) {
	if (index >= size) return &(end->data);		//если значение выходит за пределы размера списка, вернем самое крайнее значение
	Node* temp = head;
	for (size_t t = 0; t < index; t++) {
		temp = temp->next;
	}
	return &(temp->data);
}



void StudentList::delete_all() {
	while (head != nullptr) {
		Node* temp = head->next;
		delete head;
		head = temp;
	}
	size = 0;
}


class Program : public StudentList {

public:
	fstream mainfile;
	StudentList Students;

	int StudentCount = 0;
	bool RunProcess = true;

	Program() {};
	~Program() {};

	void fileread();
	int uploadToFile();

	bool CorrectNameInput(const char *a);
	void ReturnMsg(int code);

	void ClearBuf();

	int AddMember(Student &student, int mode);

	int getInt();

	bool numZachFormat(const char* zach);

	bool StrComp(const char* a, const char* b);

	bool DateFormatCheck(const char *bdate, Student &student);

	int StrGetSize(const char* str);

	bool GroupFormatCheck(const char *group, Student &student);

	bool CorrStudyName(const char* kaf);

	char* GetwinUserName();

	char* CharStrCopy(char *d, const char *s);

	char* CharStrAdd(char *dest, const char *src);

	bool UniqZachNum(const char* zach);

	int FindByZach();

	int RedactStudInfo();

	void FindStudent();

	void DeleteStudent();

	bool NoneZachNum(const char* zach);

	int GetYear(char* year);

};

Program MainProcess;

class Err : public Program {
public:
	void ReturnErrMsg(int code);
};

void Err::ReturnErrMsg(int code) {
	cout << errmsg[code];
}
Err ErrorManager;

class UI : public Program, virtual public Student {
	friend class Err;

public:
	int menu();
	void doProgramAction(int chioce);
	int RedactMenuChoice(Student &student);

};

UI ProgramInterface;


int Program::GetYear(char* year) {
	int y = (year[0] - 48) * 1000 + (year[1] - 48) * 100 + (year[2] - 48) * 10 + (year[3] - 48);
	return y;
}

void Program::ClearBuf() {
	cin.clear();
	_flushall();
	cin.ignore(cin.rdbuf()->in_avail());
}


void Program::fileread() {
	mainfile.open("database.txt", ios::in);
	if (mainfile.is_open()) {
		mainfile.seekg(0, ios::end);
		size_t length = mainfile.tellg();
		mainfile.seekg(0, ios::beg);
		if (length == 0) return;
		Student stud;

		while (mainfile.getline(stud.StudentInfo.name, sizeof(stud.StudentInfo.name))) {

			mainfile.getline(stud.StudentInfo.surname, sizeof(stud.StudentInfo.surname));
			mainfile.getline(stud.StudentInfo.lastname, sizeof(stud.StudentInfo.lastname));
			mainfile.getline(stud.StudentInfo.bdate, sizeof(stud.StudentInfo.bdate));
			char temp_byear[5];
			char temp_postyear[5];
			mainfile.getline(temp_byear, sizeof(temp_byear));
			mainfile.getline(temp_postyear, sizeof(temp_postyear));
			mainfile.getline(stud.StudentInfo.fak, sizeof(stud.StudentInfo.fak));
			mainfile.getline(stud.StudentInfo.kaf, sizeof(stud.StudentInfo.kaf));
			mainfile.getline(stud.StudentInfo.group, sizeof(stud.StudentInfo.group));
			mainfile.getline(stud.StudentInfo.zachetka, sizeof(stud.StudentInfo.zachetka));
			char temp_sex[2];
			mainfile.getline(temp_sex, sizeof(temp_sex));
			stud.StudentInfo.sex = temp_sex[0];
			stud.StudentInfo.byear = GetYear(temp_byear);
			stud.StudentInfo.postyear = GetYear(temp_postyear);

			for (int i = 0; i < 9; i++) {
				for (int k = 0; k < 10; k++) {
					mainfile.getline(stud.StudentInfo.predmname[i][k], sizeof(stud.StudentInfo.predmname[i][k]));
					if (stud.StudentInfo.predmname[i][k][0] == '_') stud.StudentInfo.predmname[i][k][0] = '\0';
				}
			}
			for (int n = 0; n < 9; n++) {
				for (int k = 0; k < 10; k++) {
					char temp_note[2];
					mainfile.getline(temp_note, sizeof(temp_note));
					stud.StudentInfo.notes[n][k] = temp_note[0] - 48;
				}
			}
			MainProcess.Students.append(stud);
		}
	}
	mainfile.close();
}

bool operator==(Student prototype, Student current) {
	if (MainProcess.StrComp(prototype.StudentInfo.zachetka, current.StudentInfo.zachetka))
		return true;
	return false;
}

int Program::uploadToFile() {
	mainfile.open("database.txt", ios::out | ios::trunc);
	if (mainfile.is_open()) {
		for (size_t index = 0; index < MainProcess.Students.size; index++) {
			Student stud = MainProcess.Students[index];

			mainfile << stud.StudentInfo.name << '\n';
			mainfile << stud.StudentInfo.surname << '\n' << stud.StudentInfo.lastname << '\n' << stud.StudentInfo.bdate << '\n';
			mainfile << stud.StudentInfo.byear << '\n' << stud.StudentInfo.postyear << '\n' << stud.StudentInfo.fak << '\n' << stud.StudentInfo.kaf << '\n';
			mainfile << stud.StudentInfo.group << '\n' << stud.StudentInfo.zachetka << '\n' << stud.StudentInfo.sex << '\n';
			for (int i = 0; i < 9; i++) {
				for (int k = 0; k < 10; k++) {
					if (StrGetSize(stud.StudentInfo.predmname[i][k]) > 0)
						mainfile << stud.StudentInfo.predmname[i][k] << '\n';
					else mainfile << '_' << '\n';
				}
			}
			for (int n = 0; n < 9; n++) {
				for (int k = 0; k < 10; k++) {
					mainfile << char(stud.StudentInfo.notes[n][k] + 48) << '\n';
				}
			}
		}
		mainfile.close();
		return 0;
	}
	return -1;
}

char* Program::GetwinUserName()
{
	static char name[256];
	unsigned long size = sizeof(name);
	GetUserNameA(name, &size);
	return name;
}

void Program::ReturnMsg(int code) {
	cout << sysmsg[code];
}


int Program::RedactStudInfo() {
	int pos = FindByZach();

	if (pos != 0) {
		pos--;
		Student* newinfo = MainProcess.Students(pos);
		int mode = ProgramInterface.RedactMenuChoice(*newinfo);
		if (mode == -1) {
			system("cls");
			return -1;
		}
		if (AddMember(*newinfo, mode) == -2) {
			system("cls");
			return -1;
		}

		ReturnMsg(15);
		return 1;
	}
	else {
		ErrorManager.ReturnErrMsg(20);
		return 0;
	}
}

bool Program::DateFormatCheck(const char *bdate, Student &student) {
	bool format = true;
	for (int i = 0; i < 10; i++) {
		if ((i == 2 or i == 5) and bdate[i] != '.') format = false;
		if ((i != 2 and i != 5) and !(bdate[i] >= 48 and bdate[i] <= 57)) format = false;
	}

	int day = (bdate[0] - 48) * 10 + bdate[1] - 48;
	int month = (bdate[3] - 48) * 10 + bdate[4] - 48;
	int year = (bdate[6] - 48) * 1000 + (bdate[7] - 48) * 100 + (bdate[8] - 48) * 10 + bdate[9] - 48;

	int mdays = 0;
	if ((month <= 0 or month > 12)) {
		ErrorManager.ReturnErrMsg(9);
		return false;
	}

	if (year < 1970 or year > 2024) {
		ErrorManager.ReturnErrMsg(10);
		return false;
	}

	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12: mdays = 31; break;
	case 2: mdays = 29; break;
	case 4: case 6: case 9: case 11: mdays = 30; break;
	};

	if (day > mdays) format = false;
	if (year % 4 != 0 and day > 28 and month == 2) format = false;

	if (format == false) {
		ErrorManager.ReturnErrMsg(9);
		return false;
	}
	student.StudentInfo.byear = year;
	return true;
};

bool Program::GroupFormatCheck(const char* group, Student &student) {
	bool format = true;

	if (StrGetSize(group) != 10) format = false;

	for (int i = 0; i < 10; i++) {
		unsigned char s = group[i];
		if ((i == 4 or i == 7) and s != 45) format = false;
		if ((i >= 0 and i <= 3) and (s < 192 or s > 223)) format = false;
		if ((i == 5 or i == 6) and (s < 48 or s > 57)) format = false;
		if ((i == 8 or i == 9) and (s < 48 or s > 57)) format = false;
	}

	if (format == false) {
		ErrorManager.ReturnErrMsg(13);
		return false;
	}

	int pyear = (group[8] - 48) * 10 + group[9] - 48 + 2000;
	if (pyear < student.StudentInfo.byear) {
		ErrorManager.ReturnErrMsg(12);
		return false;
	}

	student.StudentInfo.postyear = pyear;
	return format;
}


int Program::FindByZach() {
	int studFilePos = 0;
	Student prototype;

	char zachetka[8];
	ReturnMsg(8);
	while (true) {
		ClearBuf();
		ReturnMsg(2);
		cin.getline(zachetka, 8);
		if (numZachFormat(zachetka) == true) break;
		ClearBuf();
	}
	InputManager.setstr(prototype.StudentInfo.zachetka, zachetka);

	int numstud = 0;
	for (int i = 0; i < Students.size; i++) {
		if (prototype == Students[i]) {
			studFilePos = i;
			return ++studFilePos;
		}
	}
	return 0;
}



int UI::menu() {
	system("cls");
	int line = 0;
	char key = -1;
	while (key != 13) {
		int wline = 0;
		cout << "Здравствуйте, " << "Артем" << "\n" << endl;	// ErrorManager.GetwinUserName()
		ReturnMsg(16);
		for (int i = 0; i < 6; i++) {
			ReturnMsg(i + 19);
			if (line == wline) cout << "	<-\n";
			else cout << '\n';
			wline++;
		}
		key = _getch();
		switch (key) {
		case 'w': case 'ц': line--; break;
		case 's': case 'ы': line++; break;
		}
		if (line > 5) line = 5;
		if (line < 0) line = 0;

		system("cls");
	}
	return line;
}

int UI::RedactMenuChoice(Student &student) {
	system("cls");
	int line = 0;
	char key = -1;
	while (key != 13) {
		int wline = 0;
		ReturnMsg(16);
		cout << '\n' << student.StudentInfo.surname << " " << student.StudentInfo.name << " " << student.StudentInfo.lastname << " " << endl;
		cout << "Дата рождения: " << student.StudentInfo.bdate << " Пол: " << student.StudentInfo.sex << endl;
		cout << "Номер зачетной книжки: " << student.StudentInfo.zachetka << " Номер группы: " << student.StudentInfo.group << endl;
		cout << "Год поступления: " << student.StudentInfo.postyear << endl;
		cout << "Факультет: " << student.StudentInfo.fak << endl;
		cout << "Кафедра: " << student.StudentInfo.kaf << "\n" << endl;

		for (int i = 0; i < 11; i++) {
			ReturnMsg(i + 25);
			if (line == wline) cout << "	<-\n";
			else cout << '\n';
			wline++;
		}
		key = _getch();
		switch (key) {
		case 'w': case 'ц': line--; break;
		case 's': case 'ы': line++; break;
		case 27: return -1;
		}
		if (line > 10) line = 10;
		if (line < 0) line = 0;

		system("cls");
	}
	return ++line;
};

void UI::doProgramAction(int choice) {

	int redactcode;

	system("cls");

	switch (choice) {


	case 0: {

		Student student1;
		MainProcess.AddMember(student1, 0);
		MainProcess.Students.delete_all();
		MainProcess.fileread();
		MainProcess.Students.append(student1);
		MainProcess.uploadToFile();
		break;
	}

	case 1: {
		MainProcess.Students.delete_all();
		MainProcess.fileread();
		redactcode = MainProcess.RedactStudInfo();
		MainProcess.uploadToFile();
		break;
	}

	case 2: {

		MainProcess.Students.delete_all();
		MainProcess.fileread();

		if (MainProcess.Students.size < 1) ErrorManager.ReturnErrMsg(23);
		else {
			ReturnMsg(40);
			cout << "\n";
			ReturnMsg(41);
			ReturnMsg(40);
			cout << '\n';
			for (size_t i = 0; i < MainProcess.Students.size; i++) {
				cout << '|' << setw(20) << MainProcess.Students[i].StudentInfo.surname;
				cout << '|' << setw(20) << MainProcess.Students[i].StudentInfo.name << '|';
				cout << setw(20) << MainProcess.Students[i].StudentInfo.lastname;
				cout << '|' << setw(17) << MainProcess.Students[i].StudentInfo.zachetka << '|';
				cout << setw(14) << MainProcess.Students[i].StudentInfo.group << '|' << setw(21) << MainProcess.Students[i].StudentInfo.postyear << '|' << endl;
				ReturnMsg(42);
			}
		}
		break;
	}

	case 3: {

		MainProcess.Students.delete_all();
		MainProcess.fileread();
		unsigned int n_student = 0;
		unsigned char sex;

		ReturnMsg(12);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sex;
			if (sex == 204 or sex == 198) break;
			ErrorManager.ReturnErrMsg(15);
			ClearBuf();
		}
		system("cls");
		for (size_t i = 0; i < MainProcess.Students.size; i++) {
			Student temp = MainProcess.Students[i];
			if (temp.StudentInfo.sex != sex) continue;
			bool only_four_five = true;
			for (int n = 0; n < 9; n++) {
				for (int k = 0; k < 10; k++) {
					if (temp.StudentInfo.notes[n][k] == 3) { only_four_five = false; break; }
				}
			}
			if (!only_four_five) continue;
			n_student++;
			if (n_student == 1) ReturnMsg(42);
			cout << '|' << n_student << '|' << setw(20) << temp.StudentInfo.surname << '|' << setw(20) << temp.StudentInfo.name << '|';
			cout << setw(20) << temp.StudentInfo.lastname << '|' << setw(15) << temp.StudentInfo.zachetka << '|';
			cout << setw(17) << temp.StudentInfo.postyear << '|' << setw(18) << temp.StudentInfo.group << '|' << endl;
			ReturnMsg(42);
		}
		break;

	}

	case 4: {
		MainProcess.Students.delete_all();
		MainProcess.fileread();
		MainProcess.DeleteStudent();
		MainProcess.uploadToFile();
		break;
	}

	case 5: {
		MainProcess.RunProcess = false;
	}

	}
	if (choice == 1 and redactcode == -1) return;

	if (choice != 5) {
		MainProcess.ReturnMsg(17);
		_getch();
		return;
	}
	else {
		return;
	}
}


bool Program::numZachFormat(const char* zach) {
	bool t = true;

	if (StrGetSize(zach) != 7) {
		t = false;
	}
	unsigned char s = 0;
	for (int i = 0; i < 7; i++) {
		s = zach[i];
		if (i == 2 and !((s >= 192) and (s <= 223))) { t = false; }
		if (i != 2 and !(s >= 48 and s <= 57)) t = false;
	}
	if (t == false) ErrorManager.ReturnErrMsg(11);
	return t;
}


int Program::AddMember(Student &student, int mode) {
	int sem = 1;
	char note;
	unsigned char sem_count;
	unsigned char sex;

	if (mode == 1 or mode == 0) {
		char* surname = new char[20];
		ReturnMsg(5);

		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(surname, 20);
			if (CorrectNameInput(surname) == true and StrGetSize(surname) != 0) break;
			ClearBuf();
		}

		ClearBuf();
		InputManager.setstr(student.StudentInfo.surname, "                   ");
		InputManager.setstr(student.StudentInfo.surname, surname);
		delete[] surname;
	}

	if (mode == 2 or mode == 0) {
		char* name = new char[20];
		ReturnMsg(4);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(name, 20);
			if (CorrectNameInput(name) == true and StrGetSize(name) != 0) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.name, "                   ");
		InputManager.setstr(student.StudentInfo.name, name);
		delete[] name;
	}

	if (mode == 3 or mode == 0) {
		char* lastname = new char[20];
		ReturnMsg(6);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(lastname, 20);
			if (CorrectNameInput(lastname) == true and StrGetSize(lastname) != 0) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.lastname, "                   ");
		InputManager.setstr(student.StudentInfo.lastname, lastname);
		delete[] lastname;
	}

	if (mode == 4 or mode == 0) {
		char* bdate = new char[11];
		ReturnMsg(7);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(bdate, 11);
			if (DateFormatCheck(bdate, student) == true) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.bdate, "          ");
		InputManager.setstr(student.StudentInfo.bdate, bdate);
		delete[] bdate;
	}

	if (mode == 5 or mode == 0) {
		ReturnMsg(12);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sex;
			if (sex == 204 or sex == 198) break;
			ErrorManager.ReturnErrMsg(15);
			ClearBuf();
		}
		student.StudentInfo.sex = sex;
	}

	if (mode == 6 or mode == 0) {
		char* zachetka = new char[8];
		ReturnMsg(8);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(zachetka, 8);
			if (numZachFormat(zachetka) == true and UniqZachNum(zachetka) == true) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.zachetka, "       ");
		InputManager.setstr(student.StudentInfo.zachetka, zachetka);
		delete[] zachetka;
	}

	if (mode == 7 or mode == 0) {
		char* group = new char[11];
		ReturnMsg(9);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(group, 11);
			if (GroupFormatCheck(group, student) == true) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.group, "          ");
		InputManager.setstr(student.StudentInfo.group, group);
		delete[] group;
	}

	if (mode == 8 or mode == 0) {
		char* fak = new char[30];
		ReturnMsg(43);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(fak, 30);
			if (CorrStudyName(fak) == true) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.fak, "                             ");
		InputManager.setstr(student.StudentInfo.fak, fak);
		delete[] fak;
	}

	if (mode == 9 or mode == 0) {
		char* kaf = new char[30];
		ReturnMsg(10);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin.getline(kaf, 30);
			if (CorrStudyName(kaf) == true) break;
			ClearBuf();
		}
		ClearBuf();
		InputManager.setstr(student.StudentInfo.kaf, "                             ");
		InputManager.setstr(student.StudentInfo.kaf, kaf);
		delete[] kaf;
	}

	if (mode == 0) {
		ReturnMsg(11);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sem_count;
			if (sem_count >= 48 and sem_count <= 57) break;
			ErrorManager.ReturnErrMsg(16);
			ClearBuf();
		}
		sem = sem_count - 48;
	}
	int* cpredm = new int[sem];

	if (mode == 10) {
		int needToPrint = 0;
		char sem;
		ReturnMsg(37);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sem;
			if (sem >= 49 and sem <= 57) break;
			ErrorManager.ReturnErrMsg(22);
			ClearBuf();
		}
		ClearBuf();

		needToPrint = sem - 49;
		char key = 0;
		int line = 0;
		system("cls");
		while (key != 13) {
			ReturnMsg(16);
			cout << '\n';
			int wline = 0;
			for (int i = 0; i < 10; i++) {
				unsigned char fletter = student.StudentInfo.predmname[needToPrint][i][1];
				if (fletter > 223) cout << student.StudentInfo.predmname[needToPrint][i];
				else cout << "Пусто";

				if (line == wline) cout << "	<-\n";
				else cout << '\n';
				wline++;
			}
			key = _getch();
			switch (key) {
			case 'w': case 'ц': line--; break;
			case 's': case 'ы': line++; break;
			case 27: line = -2; break;
			}
			if (line == -2) break;
			if (line > 9) line = 9;
			if (line < 0) line = 0;

			system("cls");
		}
		if (line == -2) return -2;

		char* predm = new char[30];
		bool t;
		ReturnMsg(39);
		while (true) {
			t = true;
			ClearBuf();
			ReturnMsg(2);
			cin.getline(predm, 30);

			for (int k = 0; k < 10; k++) {
				if (StrComp(predm, student.StudentInfo.predmname[needToPrint][k]) == true) {
					ErrorManager.ReturnErrMsg(18);
					t = false;
					break;
				}
			}
			if (t == false) continue;

			if (CorrStudyName(predm) == true) break;
			ClearBuf();
		}

		ClearBuf();
		InputManager.setstr(student.StudentInfo.predmname[needToPrint][line], "                             ");
		InputManager.setstr(student.StudentInfo.predmname[needToPrint][line], predm);

		delete[] predm;
	}

	if (mode == 0) {

		ReturnMsg(13);

		for (int i = 0; i < sem; i++) {
			cout << "\nВведите количество предметов в " << i + 1 << " семестре" << endl;
			int c;

			while (true) {
				ClearBuf();
				ReturnMsg(2);
				cin >> c;
				if (cin.good() and c >= 0 and c <= 10) break;
				ErrorManager.ReturnErrMsg(2);
				ClearBuf();
			}
			cpredm[i] = c;

			for (int j = 0; j < cpredm[i]; j++) {
				char* predm = new char[30];
				char note;
				bool t = true;

				cout << "\nВведите название " << j + 1 << " предмета " << i + 1 << " семестра\n" << endl;
				while (true) {
					t = true;
					ClearBuf();
					ReturnMsg(2);
					cin.getline(predm, 30);

					for (int k = 0; k < 10; k++) {
						if (StrComp(predm, student.StudentInfo.predmname[i][k]) == true) {
							ErrorManager.ReturnErrMsg(18);
							t = false;
							break;
						}
					}
					if (t == false) continue;

					if (CorrStudyName(predm) == true) break;
					ClearBuf();
				}

				ClearBuf();
				InputManager.setstr(student.StudentInfo.predmname[i][j], "                             ");
				InputManager.setstr(student.StudentInfo.predmname[i][j], predm);
			}
		}
	}

	if (mode == 11) {
		int needToPrint = 0;
		char sem;
		ReturnMsg(37);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sem;
			if (sem >= 49 and sem <= 57) break;
			ErrorManager.ReturnErrMsg(22);
			ClearBuf();
		}
		ClearBuf();

		needToPrint = sem - 49;
		char key = 0;
		int line = 0;
		system("cls");
		while (key != 13) {
			ReturnMsg(16);
			cout << '\n';
			int wline = 0;
			for (int i = 0; i < 10; i++) {
				unsigned char fletter = student.StudentInfo.predmname[needToPrint][i][1];
				if (fletter > 223) {
					cout << student.StudentInfo.predmname[needToPrint][i] << ' ';
					if ((char)(student.StudentInfo.notes[needToPrint][i] + 48) >= '0' and (char)(student.StudentInfo.notes[needToPrint][i] + 48) <= '5') {
						cout << (char)(student.StudentInfo.notes[needToPrint][i] + 48);
					}
					else cout << '0';
				}
				else cout << "Пусто 0";

				if (line == wline) cout << "	<-\n";
				else cout << '\n';
				wline++;
			}
			key = _getch();
			switch (key) {
			case 'w': case 'ц': line--; break;
			case 's': case 'ы': line++; break;
			case 27: line = -2; break;
			}
			if (line == -2) break;
			if (line > 9) line = 9;
			if (line < 0) line = 0;

			system("cls");
		}
		if (line == -2) return -2;

		bool t;
		ReturnMsg(38);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> note;
			if (note >= 50 and note <= 53 or note == 48) break;
			ErrorManager.ReturnErrMsg(17);
			ClearBuf();
		}
		unsigned char pcheck = student.StudentInfo.predmname[needToPrint][line][1];
		if (pcheck > 223) student.StudentInfo.notes[needToPrint][line] = note - 48;
		else student.StudentInfo.notes[needToPrint][line] = 0;
	}

	if (mode == 0) {

		ReturnMsg(14);
		for (int i = 0; i < sem; i++) {
			if (cpredm[i] != 0) {
				for (int j = 0; j < cpredm[i]; j++) {
					cout << "\nВведите оценку за " << i + 1 << " семестр по предмету " << student.StudentInfo.predmname[i][j] << "\n" << endl;
					while (true) {
						ClearBuf();
						ReturnMsg(2);
						cin >> note;
						if (note >= 50 and note <= 53 or note == 48) break;
						ErrorManager.ReturnErrMsg(17);
						ClearBuf();
					}
					student.StudentInfo.notes[i][j] = note - 48;
				}
			}
			else continue;
		}
	}
	return 0;
	delete[] cpredm;
};

bool Program::NoneZachNum(const char *zach) {
	bool t = true;

	if (StrGetSize(zach) != 7) {
		t = false;
	}
	unsigned char s = 0;
	for (int i = 0; i < 7; i++) {
		s = zach[i];
		if (i == 2 and !((s >= 192) and (s <= 223))) { t = false; }
		if (i != 2 and !(s >= 48 and s <= 57)) t = false;
	}
	return t;
}

bool Program::UniqZachNum(const char* zach) {
	for (int i = 0; i < Students.size; i++) {
		if (StrComp(Students[i].StudentInfo.zachetka, zach) == true) {
			ErrorManager.ReturnErrMsg(19);
			return false;
		}
	}
	return true;
}

void Program::FindStudent() {
	Student stud;
	int pos = MainProcess.FindByZach();
	if (pos != 0) cout << stud.StudentInfo.surname << " " << stud.StudentInfo.name << " " << stud.StudentInfo.lastname << " " << stud.StudentInfo.zachetka << " " << stud.StudentInfo.group << endl;
}

void Program::DeleteStudent() {
	int pos = FindByZach();
	if (pos != 0) {
		pos--;
		Students.del(pos);
		ReturnMsg(18);
	}
	else {
		ErrorManager.ReturnErrMsg(20);
	}
}


bool Program::CorrStudyName(const char* kaf) {
	int space_counter = 0;

	for (int i = 0; i < StrGetSize(kaf); i++) {
		unsigned char s = kaf[i];

		if ((s > 32 and s < 65) or (s > 90 and s < 97)) {
			ErrorManager.ReturnErrMsg(3); cout << "'" << s << "'" << endl;
			return false;
		}

		if ((s < 192 or s > 255) and s != 9 and s != 32) {
			ErrorManager.ReturnErrMsg(6);
			return false;
		}

		if (i == 0 and (s < 192 or s > 223) and s != 9 and s != 32) {
			ErrorManager.ReturnErrMsg(7);
			return false;
		}

		if (s == 32 or s == 9) {
			space_counter++;
		}

		if (i != 0 and (s >= 192 and s <= 223)) {
			ErrorManager.ReturnErrMsg(8);
			return false;
		}
	}
	if (space_counter == StrGetSize(kaf)) {
		ErrorManager.ReturnErrMsg(14);
		return false;
	}
	return true;
}

bool Program::CorrectNameInput(const char* a) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	for (int i = 0; i < maxStrSize; i++) {
		unsigned char s = *(a + i);

		if (s == '\0') {
			break;
		}
		if ((s >= 32 and s < 65) or (s > 90 and s < 97)) {
			ErrorManager.ReturnErrMsg(3); cout << "'" << s << "'" << endl;
			return false;
		}
		if (s < 192 or s > 255) {
			ErrorManager.ReturnErrMsg(6);
			return false;
		}

		if (i == 0 and (s < 192 or s > 223)) {
			ErrorManager.ReturnErrMsg(7);
			return false;
		}

		if (i != 0 and (s >= 192 and s <= 223)) {
			ErrorManager.ReturnErrMsg(8);
			return false;
		}

	}
	return true;
}


char* Program::CharStrCopy(char *d, const char *s)
{
	char *saved = d;
	while (*s)
	{
		*d++ = *s++;
	}
	*d = 0;
	return saved;
}

int Program::getInt() {
	int value;
	ClearBuf();
	cin >> value;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	ClearBuf();
	return value;
}

int Program::StrGetSize(const char* str) {
	int size = 0;
	for (int i = 0; i < maxStrSize; i++) {
		if (str[i] == '\0') break;
		size++;
	}
	return size;
}

bool Program::StrComp(const char *a, const char* b) {
	if (StrGetSize(a) != StrGetSize(b)) {
		return false;
	}

	for (int i = 0; i < StrGetSize(a); i++) {
		for (int i = 0; i < StrGetSize(a); i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}
}

char* Program::CharStrAdd(char *dest, const char *src)
{
	size_t i, j;
	for (i = 0; dest[i] != '\0'; i++);
	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return dest;
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	while (MainProcess.RunProcess == true) {
		int code = ProgramInterface.menu();
		ProgramInterface.doProgramAction(code);
	}

	return 0;
}

