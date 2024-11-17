#include <iostream>
#include <iomanip>
#include <ios>
#include <limits>
#include <windows.h>
#include <conio.h>
#include <fstream>

const int maxStrSize = 256;

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
						"\nУказываемый год рождения должен быть в диапазоне 1970-2022!\n",
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
						"\nВводимый год должен находиться в диапазоне 1970-2022!\n",
						"\nВерхняя граница не может быть меньше нижней!\n",
						"\nУказан неверный номер семестра!\n",
						"\nНомер года не соотвествует заданным границам!\n",
						"\nВерхняя граница не может быть меньше нижней!\n",
						"\nЗапрашиваемый список студентов пуст!\n",
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
						"[4] Сортировка по успеваемости 1 и 2 семестра с интервалом года рождения",
						"[5] Сортировка по успеваемости 1 семестра с интервалом года рождения",
						"[6] Сортировка по успеваемости 2 семестра с интервалом года рождения",
						"[7] Удалить запись о студенте",
						"[8] Выход из программы",
						"[1] Изменить фамилию",
						"[2] Изменить имя",
						"[3] Изменить отчество",
						"[4] Изменить дату рождения",
						"[5] Изменить пол",
						"[6] Изменить номер зачетной книжки",
						"[7] Изменить номер группы",
						"[8] Изменить название факультета",
						"[9] Изменить название кафедры",
						"[10] Изменить названия предметов",
						"[11] Изменить оценки",
						"\nЗавершение работы программы...\n",
						"\nВ каком семестре будет отредактирована информация?\n",
						"\nВведите новую оценку по предмету  (оценки по пустым предметам будут приняты, но не будут внесены в базу!)\n",
						"\nВведите новое название предмета\n",
						"\nВведите год нижней границы отбора (1970 - 2022)\n",
						"\nВведите год верхней границы отбора (1970 - 2022)\n",
						"\n|№|      Фамилия       |        Имя         |      Отчество      | Номер зачетки |  Год рождения  |   Процент троек   |",
						"\n| |                    |                    |                    |               |                |за выбранный период|",
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

class Crypto : public StrManager {
public:
	void encrypt()
	{
		srand(time(NULL));
		char* pass = new char[64];
		for (int i = 0; i < 64; ++i)
		{
			switch (rand() % 3)
			{
			case 0:
				pass[i] = rand() % 10 + '0';
				break;
			case 1:
				pass[i] = rand() % 26 + 'A';
				break;
			case 2:
				pass[i] = rand() % 26 + 'a';
			}
		}
		pass[64] = 0;

		char* fullcomm = new char[256];
		const char* command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in f.txt -out f.enc -pass pass:";
		CharStrCopy(fullcomm, command);
		CharStrAdd(fullcomm, pass);

		system(fullcomm);

		remove("f.txt");

		ofstream _file;
		_file.open("passwd.bin", ios::binary);

		_file.write(pass, 65);
		_file.close();

		const char* command1 = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey key.public -pubin -in passwd.bin -out passwd.enc";
		system(command1);

		remove("passwd.bin");
		delete[] fullcomm;
	}



	void decrypt()
	{
		const char* command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey key.private -in passwd.enc -out passwd.bin";
		system(command);

		remove("passwd.enc");


		char* pass = new char[64];
		ifstream _file;
		_file.open("passwd.bin", ios::binary);


		_file.read(pass, 65);
		_file.close();

		char* fullcomm = new char[256];

		const char* command1 = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in f.enc -out f.txt -pass pass:";
		CharStrCopy(fullcomm, command1);
		CharStrAdd(fullcomm, pass);

		system(fullcomm);

		remove("f.enc");
		delete[] fullcomm;
	}
};


Crypto CryptoManager;


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
		char zachetka[8];
		unsigned char sex;
		char predmname[9][10][30];
		char notes[9][10];
		float p;
	};

	info StudentInfo;

	Student() {};

	~Student() {};
	void filewrite();
	void filewrite(FILE* file, int position);

};

class Program {

public:
	FILE* mainfile;
	FILE* buffer;

	int StudentCount;
	int fopenerror;
	bool RunProcess;

	Program() {
		StudentCount = 0;
		fopenerror = -1;
		RunProcess = true;
	};

	~Program() {};

	bool CorrectNameInput(const char *a);
	int openfile(const char* name, const char* mode);

	long getfilesize(FILE* file);

	Student* fileread();
	Student fileread(int NoS);
	Student fileread(FILE* file, int NoS);

	void ReturnMsg(int code);
	void SortStudent(Student *arr, int start, int end);
	int StudArrPartition(Student *arr, int start, int end);

	Student* CreateSortArr(Student arr[], int mode, int firstyear, int secondyear);

	void Set3ProcentInclusion(Student arr[], int mode);

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

	void IncludeOrCreateDatabase();

	void ExtractStudents(int firstyear, int secondyear);

	void SwapInBuf(int ind1, int ind2);
};

class Err : public Program {
public:
	void ReturnErrMsg(int code);
};

void Err::ReturnErrMsg(int code) {
	cout << errmsg[code];
}
Err ErrorManager;

class UI : virtual public StrManager, virtual public Program {
	friend class Err;
public:
	int menu();
	void doProgramAction(int chioce);
	int RedactMenuChoice(Student &student);

};

int UI::menu() {
	system("cls");
	int line = 0;
	char key = -1;
	while (key != 13) {
		int wline = 0;
		cout << "Здравствуйте, " << ErrorManager.GetwinUserName() << "\n" << endl;
		ReturnMsg(16);
		for (int i = 0; i < 8; i++) {
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
		if (line > 7) line = 7;
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
			ReturnMsg(i + 27);
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
}

UI ProgramInterface;

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

char* Program::CharStrAdd(char *dest, const char *src)
{
	size_t i, j;
	for (i = 0; dest[i] != '\0'; i++);
	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return dest;
}

int Program::openfile(const char* name, const char* mode) {
	errno_t err = fopen_s(&mainfile, name, mode);
	if (err != NULL) {
		fopen_s(&mainfile, name, "wb+");
	}
	fopenerror = 0;
	fclose(mainfile);
	fopen_s(&mainfile, name, mode);

	return fopenerror;
}

void Program::IncludeOrCreateDatabase() {
	FILE* filetest;
	errno_t err = fopen_s(&filetest, "f.txt", "rb+");
	if (err == NULL) {
		fclose(filetest);
		CryptoManager.encrypt();
		return;
	}

	err = fopen_s(&filetest, "f.enc", "rb+");
	if (err != NULL) {
		fopen_s(&filetest, "f.txt", "wb+");
		fclose(filetest);

		CryptoManager.encrypt();
	}
	else {
		fclose(filetest);
	}
	return;
}

long Program::getfilesize(FILE* file) {
	fseek(file, 0, SEEK_END);
	long int t = ftell(mainfile);
	fseek(file, 0, SEEK_SET);
	return t;
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
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int Program::getInt() {
	int value;
	ClearBuf();
	cin >> value;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	ClearBuf();
	return value;
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

Student* Program::CreateSortArr(Student arr[], int mode, int firstyear, int secondyear) {
	int SortCount = 0;
	StudentCount = 0;
	for (int i = 0; i < getfilesize(mainfile) / sizeof(Student::info); i++) {
		if (numZachFormat(arr[i].StudentInfo.zachetka) == true and arr[i].StudentInfo.byear >= firstyear and arr[i].StudentInfo.byear <= secondyear) StudentCount++;
	}
	Student* StudentsSortArr = new Student[StudentCount];
	int maspoz = 0;

	for (int i = 0; i < getfilesize(mainfile) / sizeof(Student::info); i++) {
		if (numZachFormat(arr[i].StudentInfo.zachetka) == true and arr[i].StudentInfo.byear >= firstyear and arr[i].StudentInfo.byear <= secondyear) StudentsSortArr[maspoz++] = arr[i];
	}
	return StudentsSortArr;
}

void Program::Set3ProcentInclusion(Student arr[], int mode) {
	switch (mode) {
	case 0: {
		int max = 0;
		for (int i = 0; i < StudentCount; i++) {
			int count = 0;
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 10; k++) {
					if (arr[i].StudentInfo.notes[j][k] >= 2 and arr[i].StudentInfo.notes[j][k] <= 5) count++;
				}
			}
			if (count > max) max = count;
		}
		for (int i = 0; i < StudentCount; i++) {

			int pcount = 0;
			int tcount = 0;
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 10; k++) {
					if (arr[i].StudentInfo.notes[j][k] >= 2 and arr[i].StudentInfo.notes[j][k] <= 5) pcount++;
					if (arr[i].StudentInfo.notes[j][k] == 3) tcount++;
				}
			}

			if (max != 0 and pcount != 0) {
				float n = pcount / (float)max;
				float d = (tcount / (float)pcount) * n;
				arr[i].StudentInfo.p = d * 100;
			}
			else {
				arr[i].StudentInfo.p = 0;
			}
		}
		break;
	}

	case 1: {
		int max = 0;
		for (int i = 0; i < StudentCount; i++) {
			int count = 0;
			for (int k = 0; k < 10; k++) {
				if (arr[i].StudentInfo.notes[0][k] >= 2 and arr[i].StudentInfo.notes[0][k] <= 5) count++;
			}
			if (count > max) max = count;
		}
		for (int i = 0; i < StudentCount; i++) {
			int pcount = 0;
			int tcount = 0;

			for (int k = 0; k < 10; k++) {
				if (arr[i].StudentInfo.notes[0][k] >= 2 and arr[i].StudentInfo.notes[0][k] <= 5) pcount++;
				if (arr[i].StudentInfo.notes[0][k] == 3) tcount++;
			}

			if (max != 0) {
				float n = pcount / float(max);
				float d = (tcount / float(pcount)) * n;
				arr[i].StudentInfo.p = d * 100;
			}
			else {
				arr[i].StudentInfo.p = 0;
			}
		}
		break;
	}

	case 2: {
		int max = 0;
		for (int i = 0; i < StudentCount; i++) {
			int count = 0;
			for (int k = 0; k < 10; k++) {
				if (arr[i].StudentInfo.notes[1][k] >= 2 and arr[i].StudentInfo.notes[1][k] <= 5) count++;
			}
			if (count > max) max = count;
		}
		for (int i = 0; i < StudentCount; i++) {
			int pcount = 0;
			int tcount = 0;

			for (int k = 0; k < 10; k++) {
				if (arr[i].StudentInfo.notes[1][k] >= 2 and arr[i].StudentInfo.notes[1][k] <= 5) pcount++;
				if (arr[i].StudentInfo.notes[1][k] == 3) tcount++;
			}

			if (max != 0) {
				float n = pcount / float(max);
				float d = (tcount / float(pcount)) * n;
				arr[i].StudentInfo.p = d * 100;
			}
			else {
				arr[i].StudentInfo.p = 0;
			}
		}
		break;
	}
	}
}

void Program::ClearBuf() {
	cin.clear();
	_flushall();
	cin.ignore(cin.rdbuf()->in_avail());
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

	if (year < 1970 or year > 2022) {
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

bool operator==(Student &prototype, Student &current);

int Program::FindByZach() {
	int studFilePos = 0;
	Student* prototype = new Student;

	char zachetka[8];
	ReturnMsg(8);
	while (true) {
		ClearBuf();
		ReturnMsg(2);
		cin.getline(zachetka, 8);
		if (numZachFormat(zachetka) == true) break;
		ClearBuf();
	}
	InputManager.setstr(prototype->StudentInfo.zachetka, zachetka);

	Student* stud = fileread();
	int numstud = 0;
	for (int i = 0; i < getfilesize(mainfile) / sizeof(Student::info); i++) {
		if (*prototype == stud[i]) {
			studFilePos = i;
			delete[] stud;
			delete prototype;
			return studFilePos + 1;
		}
	}
	delete prototype;
	delete[] stud;
	return 0;
}

void Program::DeleteStudent() {
	int pos = FindByZach();
	if (pos != 0) {
		Student student;
		pos--;
		student.filewrite(mainfile,pos);
		ReturnMsg(18);
	}
	else {
		ErrorManager.ReturnErrMsg(20);
	}
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
		ReturnMsg(49);
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
		ReturnMsg(39);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sem;
			if (sem >= 49 and sem <= 57) break;
			ErrorManager.ReturnErrMsg(23);
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
		ReturnMsg(41);
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
		ReturnMsg(39);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			cin >> sem;
			if (sem >= 49 and sem <= 57) break;
			ErrorManager.ReturnErrMsg(23);
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

		ReturnMsg(40);
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

Program MainProcess;

bool operator==(Student &prototype, Student &current) {
	if (MainProcess.StrComp(prototype.StudentInfo.zachetka, current.StudentInfo.zachetka))
		return true;
	return false;
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

void Student::filewrite() {
	long int size = MainProcess.getfilesize(MainProcess.mainfile);
	int FileStudCount = size / sizeof(Student::info);
	int nonFictStud = 0;

	for (int i = 0; i < size; i += sizeof(Student::info)) {
		fseek(MainProcess.mainfile, i, SEEK_SET);
		Student* s = new Student;
		fread(&(*s), sizeof(Student::info), 1, MainProcess.mainfile);
		if (MainProcess.NoneZachNum(s->StudentInfo.zachetka) == true) nonFictStud++;
		delete s;
	}

	if (nonFictStud == FileStudCount) {
		fseek(MainProcess.mainfile, size, SEEK_SET);
		fwrite((char*)&StudentInfo, sizeof(Student::info), 1, MainProcess.mainfile);
	}

	else {
		long shift = 0;
		for (int i = 0; i < size; i += sizeof(Student::info)) {
			fseek(MainProcess.mainfile, i, SEEK_SET);
			Student* s = new Student;
			fread(&(*s), sizeof(Student::info), 1, MainProcess.mainfile);
			if (MainProcess.NoneZachNum(s->StudentInfo.zachetka) == false) {
				shift = i;
				delete s;
				break;
			}
			delete s;
		}
		fseek(MainProcess.mainfile, shift * sizeof(Student::info), SEEK_SET);
		fwrite((char*)&StudentInfo, sizeof(Student::info), 1, MainProcess.mainfile);
	}
}

void Student::filewrite(FILE* file, int position) {
	fseek(file, 0, SEEK_SET);
	long int shift = position * sizeof(Student::info);
	fseek(file, shift, SEEK_SET);
	fwrite((char*)&StudentInfo, sizeof(Student::info), 1, file);
}

Student* Program::fileread() {
	fseek(mainfile, 0, SEEK_SET);
	long size = getfilesize(mainfile);
	Student* array = new Student[(int)size / (sizeof(Student::info))];
	for (int i = 1; i <= (size / sizeof(Student::info)); i++) {
		fseek(mainfile, i, SEEK_SET);
		array[i - 1] = fileread(i);
	}
	return array;
}

Student Program::fileread(int NoS) {
	Student student;
	fseek(mainfile, 0, SEEK_SET);
	long shift = (NoS - 1) * sizeof(Student::info);
	fseek(mainfile, shift, SEEK_SET);
	fread(&student, sizeof(Student::info), 1, mainfile);
	return student;
}

Student Program::fileread(FILE* file, int NoS) {
	Student student;
	fseek(file, 0, SEEK_SET);
	long shift = (NoS - 1) * sizeof(Student::info);
	fseek(file, shift, SEEK_SET);
	fread(&student, sizeof(Student::info), 1, file);
	return student;
}

int Program::StudArrPartition(Student *arr, int start, int end)
{

	float pivot = arr[start].StudentInfo.p;

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i].StudentInfo.p <= pivot)
			count++;
	}

	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i].StudentInfo.p <= pivot) {
			i++;
		}

		while (arr[j].StudentInfo.p > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void Program::SortStudent(Student *arr, int start, int end) {
	if (start >= end)
		return;

	int p = StudArrPartition(arr, start, end);

	SortStudent(arr, start, p - 1);

	SortStudent(arr, p + 1, end);
}

bool Program::UniqZachNum(const char* zach) {
	Student* stud = fileread();
	for (int i = 0; i < getfilesize(mainfile) / sizeof(Student::info); i++) {
		if (StrComp(stud[i].StudentInfo.zachetka, zach) == true) {
			ErrorManager.ReturnErrMsg(19);
			delete[] stud;
			return false;
		}
	}
	delete[] stud;
	return true;
}

int Program::RedactStudInfo() {
	int pos = FindByZach();

	Student newinfo = fileread(pos);

	if (pos != 0) {
		pos--;
		int mode = ProgramInterface.RedactMenuChoice(newinfo);
		if (mode == -1) {
			system("cls");
			return -1;
		}
		if (AddMember(newinfo, mode) == -2) {
			system("cls");
			return -1;
		}

		newinfo.filewrite(mainfile,pos);
		ReturnMsg(15);
		return 1;
	}
	else {
		ErrorManager.ReturnErrMsg(20);
		return 0;
	}
}

void Program::FindStudent() {
	Student stud;
	int pos = MainProcess.FindByZach();
	if (pos != 0) cout << stud.StudentInfo.surname << " " << stud.StudentInfo.name << " " << stud.StudentInfo.lastname << " " << stud.StudentInfo.zachetka << " " << stud.StudentInfo.group << endl;
}

int Program::GetYear(char* year) {
	int y = (year[0] - 48) * 1000 + (year[1] - 48) * 100 + (year[2] - 48) * 10 + (year[3] - 48);
	return y;
}

void UI::doProgramAction(int choice) {
	int redactcode;
	int firstyear = 0;
	int secondyear = 0;

	if (choice == 3 or choice == 4 or choice == 5) {
		ReturnMsg(42);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			firstyear = MainProcess.getInt();
			if (firstyear >= 1970 and firstyear <= 2022) break;
			ErrorManager.ReturnErrMsg(24);
			ClearBuf();
		}

		ReturnMsg(43);
		while (true) {
			ClearBuf();
			ReturnMsg(2);
			secondyear = MainProcess.getInt();
			if (secondyear >= 1970 and secondyear <= 2022 and secondyear >= firstyear) break;
			else {

				if (secondyear < 1970 or secondyear > 2022) {
					ErrorManager.ReturnErrMsg(24);
					continue;
				}
				ErrorManager.ReturnErrMsg(25);
			}
			ClearBuf();
		}
	}
	system("cls");

	switch (choice) {

	case 0: {
		Student student1;
		MainProcess.AddMember(student1, 0);
		student1.filewrite();
		break;
	}

	case 1: {
		redactcode = MainProcess.RedactStudInfo();
		break;
	}

	case 2: {
		Student* students = MainProcess.fileread();
		int count = MainProcess.getfilesize(MainProcess.mainfile) / (sizeof(Student::info));

		int tcount = 0;
		for (int i = 0; i < count; i++) {
			if (NoneZachNum(students[i].StudentInfo.zachetka) != 0) tcount++;
		}
		system("cls");
		if (tcount == 0) ErrorManager.ReturnErrMsg(27);
		else {
			ReturnMsg(46);
			cout << "\n";
			ReturnMsg(47);
			ReturnMsg(46);
			cout << '\n';
			for (int i = 0; i < count; i++) {
				if (MainProcess.NoneZachNum(students[i].StudentInfo.zachetka) != 0) {
					cout << '|' << setw(20) << students[i].StudentInfo.surname << '|' << setw(20) << students[i].StudentInfo.name << '|';
					cout << setw(20) << students[i].StudentInfo.lastname << '|' << setw(17) << students[i].StudentInfo.zachetka << '|';
					cout << setw(14) << students[i].StudentInfo.group << '|' << setw(21) << students[i].StudentInfo.postyear << '|' << endl;
					ReturnMsg(48);
				}
			}
		}
		delete[] students;
		break;
	}

	case 3: {
		Student* students = MainProcess.fileread();

		Student* SortStudents = MainProcess.CreateSortArr(students, 0, firstyear, secondyear);
		system("cls");
		MainProcess.Set3ProcentInclusion(SortStudents, 0);

		MainProcess.SortStudent(SortStudents, 0, MainProcess.StudentCount - 1);
		
		if (MainProcess.StudentCount == 0) ErrorManager.ReturnErrMsg(26);
		else {
			ReturnMsg(44);
			ReturnMsg(45);
			ReturnMsg(46);
			cout << '\n';
			for (int i = MainProcess.StudentCount; i >= 0; i--) {
				if (SortStudents[i].StudentInfo.byear >= firstyear and SortStudents[i].StudentInfo.byear <= secondyear) {
					cout << '|' << MainProcess.StudentCount - i << '|' << setw(20) << SortStudents[i].StudentInfo.surname << '|' << setw(20) << SortStudents[i].StudentInfo.name << '|';
					cout << setw(20) << SortStudents[i].StudentInfo.lastname << '|' << setw(15) << SortStudents[i].StudentInfo.zachetka << '|';
					cout << setw(16) << SortStudents[i].StudentInfo.byear << '|' << setw(18) << SortStudents[i].StudentInfo.p << '%' << '|' << endl;
					ReturnMsg(48);
				}
			}
		}
		delete[] students;
		delete[] SortStudents;
		break;
	}

	case 4: {
		Student* students = MainProcess.fileread();

		Student* SortStudents = MainProcess.CreateSortArr(students, 1, firstyear, secondyear);
		MainProcess.ExtractStudents(firstyear, secondyear);

		system("cls");
		MainProcess.Set3ProcentInclusion(SortStudents, 1);

		MainProcess.SortStudent(SortStudents, 0, MainProcess.StudentCount - 1);
		if (MainProcess.StudentCount == 0) ErrorManager.ReturnErrMsg(26);
		
		else {
			ReturnMsg(44);
			ReturnMsg(45);
			ReturnMsg(46);
			cout << '\n';
			for (int i = MainProcess.StudentCount; i >= 0; i--) {
				if (SortStudents[i].StudentInfo.byear >= firstyear and SortStudents[i].StudentInfo.byear <= secondyear) {
					cout << '|' << MainProcess.StudentCount - i << '|' << setw(20) << SortStudents[i].StudentInfo.surname << '|' << setw(20) << SortStudents[i].StudentInfo.name << '|';
					cout << setw(20) << SortStudents[i].StudentInfo.lastname << '|' << setw(15) << SortStudents[i].StudentInfo.zachetka << '|';
					cout << setw(16) << SortStudents[i].StudentInfo.byear << '|' << setw(18) << SortStudents[i].StudentInfo.p << '%' << '|' << endl;
					ReturnMsg(48);
				}
			}
		}

		delete[] SortStudents;
		delete[] students;
		break;
	}

	case 5: {
		Student* students = MainProcess.fileread();

		Student* SortStudents = MainProcess.CreateSortArr(students, 2, firstyear, secondyear);
		system("cls");
		MainProcess.Set3ProcentInclusion(SortStudents, 2);

		MainProcess.SortStudent(SortStudents, 0, MainProcess.StudentCount - 1);

		if (MainProcess.StudentCount == 0) ErrorManager.ReturnErrMsg(26);

		else {
			ReturnMsg(44);
			ReturnMsg(45);
			ReturnMsg(46);
			cout << '\n';
			for (int i = MainProcess.StudentCount; i >= 0; i--) {
				if (SortStudents[i].StudentInfo.byear >= firstyear and SortStudents[i].StudentInfo.byear <= secondyear) {
					cout << '|' << MainProcess.StudentCount - i << '|' << setw(20) << SortStudents[i].StudentInfo.surname << '|' << setw(20) << SortStudents[i].StudentInfo.name << '|';
					cout << setw(20) << SortStudents[i].StudentInfo.lastname << '|' << setw(15) << SortStudents[i].StudentInfo.zachetka << '|';
					cout << setw(16) << SortStudents[i].StudentInfo.byear << '|' << setw(18) << SortStudents[i].StudentInfo.p << '%' << '|' << endl;
					ReturnMsg(48);
				}
			}
		}

		delete[] SortStudents;
		delete[] students;
		break;
	}

	case 6: {
		MainProcess.DeleteStudent();
		break;
	}

	case 7: {
		MainProcess.RunProcess = false;
	}

	}
	if (choice == 1 and redactcode == -1) return;
	if (choice != 7) {
		MainProcess.ReturnMsg(17);
		_getch();
		return;
	}
	else {
		return;
	}
}

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MainProcess.IncludeOrCreateDatabase();

	CryptoManager.decrypt();

	MainProcess.openfile("f.txt", "rb+");

	while (MainProcess.RunProcess == true) {
		int code = ProgramInterface.menu();
		ProgramInterface.doProgramAction(code);
	}
	fclose(MainProcess.mainfile);

	CryptoManager.encrypt();

	system("cls");

	MainProcess.ReturnMsg(38);

	return 0;

}
