#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <iostream>
#include <cstdlib>

#define DATABASE_NAME "password.txt"
using namespace std;

struct Student {
public:
	void print() {
		printf("%-10s|%-20s|%-27s|%-32s|%-23s\n", name, website, login, password, note);
	}

	void read() {
		cout << " Введите название: ";
		while (scanf_s("%s", name, 40) != 1) {
			cout << "Неверно введены данные. Больше 40 символов." << endl;
			while (getchar() != '\n');
			cout << "> ";
		}

		cout << " Введите вебсайт: ";
		while (scanf_s("%s", website, 40) != 1) {
			cout << "Неверно введены данные. Больше 40 символов." << endl;
			while (getchar() != '\n');
			cout << "> ";
		}

		cout << " Введите логин: ";
		while (scanf_s("%s", login, 40) != 1) {
			cout << "Неверно введены данные. Больше 40 символов." << endl;
			while (getchar() != '\n');
			cout << "> ";
		}

		cout << " Введите пароль: ";
		while (scanf_s("%s", password, 40) != 1) {
			cout << "Неверно введены данные. Больше 40 символов." << endl;
			while (getchar() != '\n');
			cout << "> ";
		}

		cout << " Введите заметки: ";
		while (scanf_s("%s", note, 40) != 1) {
			cout << "Неверно введены данные. Больше 40 символов." << endl;
			while (getchar() != '\n');
			cout << "> ";
		}
	}

	void edit() {
		int c = 0;
		c = getchar();
		cout << "ENTER, чтобы оставить." << endl;

		cout << " Измените название: [" << name << "]: ";
		c = getchar();
		if (c != '\n') {
			ungetc(c, stdin);
			while (scanf_s("%s", name, 40) != 1) {
				cout << "Неправильно введены данные для изменения названия." << endl;
				while (getchar() != '\n');
				cout << "  > ";
			}
			while (getchar() != '\n');
		}

		cout << " Измените вебсайт: [" << website << "]: ";
		c = getchar();
		if (c != '\n') {
			ungetc(c, stdin);
			while (scanf_s("%s", website, 40) != 1) {
				cout << "Неправильно введены данные для изменения вебсайта." << endl;
				while (getchar() != '\n');
				cout << "  > ";
			}
			while (getchar() != '\n');
		}

		cout << " Измените логин: [" << login << "]: ";
		c = getchar();
		if (c != '\n') {
			ungetc(c, stdin);
			while (scanf_s("%s", login, 40) != 1) {
				cout << "Неправильно введены данные для изменения логина." << endl;
				while (getchar() != '\n');
				cout << "  > ";
			}
			while (getchar() != '\n');
		}

		cout << " Измените пароль: [" << password << "]: ";
		c = getchar();
		if (c != '\n') {
			ungetc(c, stdin);
			while (scanf_s("%s", password, 40) != 1) {
				cout << "Неправильно введены данные для изменения пароля." << endl;
				while (getchar() != '\n');
				cout << "  > ";
			}
			while (getchar() != '\n');
		}

		cout << " Измените заметки: [" << note << "]: ";
		c = getchar();
		if (c != '\n') {
			ungetc(c, stdin);
			while (scanf_s("%s", note, 40) != 1) {
				cout << "Неправильно введены данные для изменения заметок." << endl;
				while (getchar() != '\n');
				cout << "  > ";
			}
			while (getchar() != '\n');
		}
	}

	int read_line(FILE* file) {
		int c;
		do {
			if (fscanf_s(file, "%s", name, 40) != 1) {
				c = fgetc(file);
				if (c == EOF) {
					return EOF;
				}
				else {
					ungetc(c, file);
				}
				cout << "ERROR: [input]: <name>" << endl;
				break;
			}
			if (fscanf_s(file, "%s", website, 40) != 1) {
				cout << "ERROR: [input]: <website>" << endl;
				break;
			}
			if (fscanf_s(file, "%s", login, 40) != 1) {
				cout << "ERROR: [input]: <login>" << endl;
				break;
			}
			if (fscanf_s(file, "%s", password, 40) != 1) {
				cout << "ERROR: [input]: <password>" << endl;
				break;
			}
			if (fscanf_s(file, "%s", note, 40) != 1) {
				cout << "ERROR: [input]: <note>" << endl;
				break;
			}
			return 0;
		} while (0);
		do {
			c = getc(file);
		} while (c != '\n' && c != EOF);
		return c;
	}

	void write_line(FILE* file) {
		fprintf(file, "%-1s %-1s %-1s %-1s %-1s\n", name, website, login, password, note);
	}

private:
	char name[40];
	char website[40];
	char login[40];
	char password[40];
	char note[40];
};

class StudentDatabase {
public:
	StudentDatabase() {
		max_count = 10;
		count = 0;
		students = new Student[max_count];
		if (students == NULL) {
			std::cout << "ERROR: StudentDatabase::StudentDatabase: new -> NULL" << std::endl;
			exit(0);
		}
	}

	~StudentDatabase() {
		if (students != NULL) {
			delete[] students;
		}
	}

	int add_student(Student student) {
		if (count == max_count) {
			max_count += 10;
			Student* new_array = new Student[max_count];
			if (new_array == NULL) {
				std::cout << "ERROR: StudentDatabase::add_student: new -> NULL" << std::endl;
				max_count -= 10;
				return -1;
			}
			else {
				memcpy(new_array, students, count * sizeof(Student));
				delete[] students;
				students = new_array;
			}
		}
		new (students + count) Student(student);
		count += 1;
		return count - 1;
	}

	int del_student(int index) {
		if (index < 0 || count <= index) {
			return -1;
		}
		count--;
		for (int i = index; i < count; i++) {
			memcpy(students + i, students + i + 1, sizeof(Student));
		}
		return 0;
	}

	int edit_student(int index) {
		if (index < 0 || count <= index) {
			return -1;
		}
		students[index].edit();
		return 0;
	}

	void print() {
		printf(" _______________________________________________________________________________________________        \n");
		printf("| №|_Название_|________Сайт________|______Имя_Пользователя_____|_____________Пароль_____________|Заметки\n");
		for (int i = 0; i < count; i++) {
			printf("|%2d|", i + 1);
			students[i].print();
		}
		printf("\n");
	}

	int load(const char* fname) {
		clear();
		FILE* file = fopen(fname, "r");
		if (file == NULL) {
			std::cout << "ERROR: StudentDatabase::read_file fopen_s -> NULL" << std::endl;
			return -1;
		}
		Student student;
		int read_stat = 0;
		do {
			read_stat = student.read_line(file);
			if (read_stat == 0) {
				this->add_student(student);
			}
		} while (read_stat != EOF);
		fclose(file);
		return 0;
	}

	int save(const char* fname) {
		FILE* file = fopen(fname, "w");
		if (file == NULL) {
			std::cout << "ERROR: StudentDatabase::read_file fopen_s -> NULL" << std::endl;
			return -1;
		}
		for (int i = 0; i < count; i++) {
			students[i].write_line(file);
		}
		fclose(file);
		return 0;
	}

	void clear() {
		count = 0;
	}

private:
	Student* students;
	int count;
	int max_count;
};

int menu(StudentDatabase* stList) {
	int cmd = 0;
	system("cls");
	cout << "\tМЕНЮ:" << endl;
	cout << "1 - Печать" << endl;
	cout << "2 - Добавить" << endl;
	cout << "3 - Редактировать" << endl;
	cout << "4 - Удалить" << endl;
	cout << "0 - Выход" << endl;
	cout << "Введите команду: ";
	while (scanf_s("%d", &cmd) == 0) {
		cout << "  #incorrect command" << endl;
		while (getchar() != '\n');
		cout << "  > ";
	}
	Student student;
	int index = 0;
	char fname[260];

	switch (cmd) {

	case 1: // Вывод всех
		stList->print();
		break;

	case 2: // Добавление
		student.read();
		stList->add_student(student);
		stList->print();
		stList->save(DATABASE_NAME);
		break;

	case 3: // Редактирование
		stList->print();
		cout << "Введите номер: ";
		while (scanf_s("%d", &index) == 0)
		{
			cout << "  #incorrect data" << endl;
			while (getchar() != '\n');
			cout << "  > ";
		}
		if (stList->edit_student(index - 1) == -1)
		{
			cout << "  #index out of range" << endl;
		}
		else
		{
			stList->print();
			stList->save(DATABASE_NAME);
		}
		break;

	case 4: // Удаление
		stList->print();
		cout << "Введите номер: ";
		while (scanf_s("%d", &index) == 0)
		{
			cout << "  #incorrect data" << endl;
			while (getchar() != '\n');
			cout << "  > ";
		}
		if (stList->del_student(index - 1) == -1)
		{
			cout << "  #index out of range" << endl;
		}
		else
		{
			stList->print();
			stList->save(DATABASE_NAME);
		}
		break;

	case 0: // Выход
		cout << "Выход из программы." << endl;
		stList->save(DATABASE_NAME);
		break;

	default:
		cout << "Такой команды нет. Повторите ввод." << endl;
		break;
	}
	return cmd;
}

int main() {
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Russian");
	StudentDatabase stList;
	stList.load(DATABASE_NAME);
	while (menu(&stList)) {
		system("pause");
	}
	return 0;
}