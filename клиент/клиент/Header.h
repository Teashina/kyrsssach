#pragma once
#include "iostream"
#include <vector>
#include <iomanip>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

class Enter {
public:
	char login[20];
	char password[20];
public:
	Enter()
	{
		login[0] = NULL;
		password[0] = NULL;
	}
	friend ofstream &operator <<(ofstream &a, Enter &b);
	friend ifstream &operator >>(ifstream &a, Enter &b);
	~Enter() {}
};

class Matrix
{
public:
	static const int size = 3;

	int **R;
	int **C;
	double r[size];
	double D[size];
	double Ck[size];
	double Dc[size];
	
	void show();

	

	Matrix() {
		R = new int*[size];
		for (int i = 0; i < size; i++)
			R[i] = new int[size];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
			{
				R[i][j] = 0;
			}
		}
		C = new int*[size];
		for (int i = 0; i < size; i++)
			C[i] = new int[size];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
			{
				C[i][j] = 0;
			}
		}
		for (int j = 0; j < size; j++)
		{
			r[j] = 0;
			D[j] = 0;
			Ck[j] = 0;
			Dc[j] = 0;
		}

	}
	~Matrix() {
		for (int i = 0; i < size; i++)
		{
			delete[] R[i];
		}
		delete[]R;
		for (int i = 0; i < size; i++)
		{
			delete[] C[i];
		}
		delete[]C;
	}
};

void Matrix::show()
{
	std::cout << "Матрица взаимных оценок компетентности экспертов:" << std::endl;
	int k = 0;
	cout << setfill('_') << setw(10) << "_" << setw(size * 7 - 1) << "_" << endl;
	cout << setw(10) << setfill(' ') << "|" << setw(size * 7) << "Эj |" << endl;
	cout << setw(10) << "Эi |" << setw(size * 7) << setfill('-') << "|" << endl;
	cout << setw(10) << setfill(' ') << "|";
	for (int i = 0; i < size; i++)
		cout << setw(5) << "Э" << i + 1 << "|";
	cout << endl << setfill('-') << setw(10) << "|" << setw(size * 7) << "|" << setfill(' ') << endl;
	for (int i = 0; i < size; i++) {
		cout << setw(8) << "Э" << k + 1 << "|"; k++;
		for (int j = 0; j < size; j++)
		{
			if(i == j) cout << setw(5) << " --" << " |";
			else cout << setw(6) << R[i][j] << "|";
		}
		cout << endl << setfill('-') << setw(10) << "|" << setw(size * 7) << "|" << setfill(' ') << endl;
	}
	cout <<  endl << "1. Директор" << endl << "2. Кондитер " << endl << "3. Бухгалтер" << endl;
	cout << "B1 - Сфокусироваться на улучшении качества продукции" << endl;
	cout << "B2 - Сфокусироваться на улучшении технологии производства" << endl;
	cout << "B3 - Сфокусироваться на улучшении качества исходных материалов" << endl;
	std::cout << endl <<  "Матрица оценок целей" << std::endl;
	k = 0;
	cout << setfill('_') << setw(10) << "_" << setw(size * 7 - 1) << "_" << endl;
	cout << setw(10) << setfill(' ') << "|" << setw(size * 7) << "Bj |" << endl;
	cout << setw(10) << "Эi |" << setw(size * 7) << setfill('-') << "|" << endl;
	cout << setw(10) << setfill(' ') << "|";
	for (int i = 0; i < size; i++)
		cout << setw(5) << "B" << i + 1 << "|";
	cout << endl << setfill('-') << setw(10) << "|" << setw(size * 7) << "|" << setfill(' ') << endl;
	for (int i = 0; i < size; i++) {
		cout << setw(8) << "Э" << k + 1 << "|"; k++;
		for (int j = 0; j < size; j++)
		{
			 cout << setw(6) << C[i][j] << "|";
		}
		cout << endl << setfill('-') << setw(10) << "|" << setw(size * 7) << "|" << setfill(' ') << endl;
	}
	
}















#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <conio.h>
#include <iomanip>

#define BUFF 512
using namespace std;

class Experttt {
private:
	string name;
	string surname;
public:
	Experttt(string name, string surname) :name(name), surname(surname) {};
	Experttt(const Experttt& experttt) :name(experttt.name), surname(experttt.surname) {};
	void setName(string name) {
		this->name = name;
	};
	void setSurname(string surname) {
		this->surname = surname;
	};
	string getExperttt() {
		string output;
		output = name + " " + surname;
		return output;
	}
};

class Job {
private:
	map<string, Experttt> experttts;
	map<string, Experttt>::iterator it;
	string JobName;
public:
	Job(string JobName) : JobName(JobName) {};
	void addExperttts(string expNum, string name, string surname) {
		Experttt experttt(name, surname);
		experttts.insert(pair<string, Experttt>(expNum, experttt));
	}
	string getJobName() {
		return this->JobName;
	}
	void getExperttts() {
		for (it = experttts.begin(); it != experttts.end(); it++) {
			cout << it->first << " " << it->second.getExperttt() << endl;
		}
	}
};

class Jobs {
private:
	list<Job> job;
	list<Job>::iterator it;
	string name;
public:
	Jobs(string name) : name(name) {};
	void addJob(string JobName) {
		Job test(JobName);
		job.push_back(test);
	}
	void addExperttt(string JobName, string expNum, string name, string surname) {
		it = job.begin();
		string tist;
		for (it = job.begin(); it != job.end(); it++) {
			tist = it->getJobName();
			if (tist == JobName) {
				it->addExperttts(expNum, name, surname);
				tist.erase();
				return;
			}
			tist.erase();
		}
		cout << "Должность " + JobName + " отсутствует" << endl;
	}
	void outputExperttts(string JobName) {
		string tist;
		for (it = job.begin(); it != job.end(); it++) {
			tist = it->getJobName();
			if (tist == JobName) {
				it->getExperttts();
				return;
			}
			tist.erase();
		}
		cout << "Должность " + JobName + " отсутствует" << endl;
	}
	void outputJob() {
		if (job.size() == 0) {
			cout << "Должности отсутствуют" << endl;
			return;
		}
		int id = 0;
		cout << endl;
		cout << "|  Номер  |            Должность            |" << endl;
		cout << "*********************************************" << endl;
		for (it = job.begin(); it != job.end(); it++, id++) {
			cout << "|" << setw(5) << id << setw(5) << "|" << setw(25) << it->getJobName() << setw(4) << "|" << endl;
		}
		cout << "*********************************************" << endl;
	}
	void delJob() {
		int num;
		system("cls");
		while (true) {
			this->outputJob();
			cout << "Введите номер Должности: ";
			cin >> num;
			if (num > job.size() || num < 0) {
				cout << "Ошибка. Попробуйте еще раз" << endl;
				rewind(stdin);
				cin.clear();
				cin.get();
				continue;
			}
			break;
		}
		it = job.begin();
		advance(it, num);
		job.erase(it);
		this->outputJob();
		cout << "Нажмите Enter чтобы продолжить" << endl;
		cin.clear();
		rewind(stdin);
		cin.get();
	}
	void addExperttt() {
		system("cls");
		string name;
		string JobName;
		string expNum;
		string surname;
		cout << "Имя эксперта: "; cin >> name;
		cout << "Фамилия эксперта: "; cin >> surname;
		cout << "Должность, которую занимает эксперт: "; cin >> JobName;
		expNum = "   ";
		this->addExperttt(JobName, expNum, name, surname);
		cout << "Нажмите Enter чтобы продолжить" << endl;
		cin.clear();
		rewind(stdin);
		cin.get();
	}
	void addJob() {
		system("cls");
		string test;
		cout << "Должность: "; cin >> test;
		this->addJob(test);
	}
	void addJobt() {
		system("cls");
		string tak="Директор";
		this->addJob("Директор");
		
		this->addJob("Кондитер"); 
		this->addJob("Бухгалтер");
	}
};

