#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include "Header.h"

using namespace std;

template <class T>
T Check()
{
	T i;
	while (!(cin >> i) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода. Повторите попытку\n";
	}
	return i;
}

ofstream& operator<<(ofstream& a, Enter& b)
{
	a << b.login << endl << b.password << endl; return a;
}

ifstream& operator >> (ifstream& a, Enter& b)
{
	a >> b.login >> b.password; return a;
}

ostream& operator<<(ostream& a, Enter& b)
{
	a << "Логин " << b.login << endl << "Пароль " << b.password << endl << endl; return a;
}

istream& operator >> (istream& a, Enter& b)
{
	cout << "Логин: ";
	a >> b.login;
	cout << "Пароль: ";
	a >> b.password;
	return a;
}

int main()
{
	system("color F0");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wstock_matersionRequested;
	WSADATA wsaData;
	int err;
	wstock_matersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wstock_matersionRequested, &wsaData);
	if (err != 0) { return 0; }

	while (true)
	{
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in dest_addr;
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(1280);
		dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr));
		char stroka[20];
		char buf[20];
		char buf1[20];
		char name[20];
		Enter ob;
		vector<Enter> mas;
		Enter buf2;
		Matrix mat;
		char res[20];
		int result;
		int choice = 0;
		Jobs ntesti("KF");
		ntesti.addJobt();

		while (true)
		{
			//tryAgain:
			cout << "        Авторизация         " << endl;
			cout << "1. Войти под администратором" << endl;
			cout << "2. Войти под пользователем  " << endl;
			cout << "3. Завершение работы        " << endl;
			cout << endl;
			int flag;
			flag = Check<int>();
			while (flag < 0 || flag > 3) {
				cout << "Ошибка ввода. Повторите попытку\n";
				flag = Check<int>();
			};
			itoa(flag, stroka, 10);
			send(s, stroka, 20, 0);
			switch (flag)
			{
			case 1:
			{
				system("cls");
				int t = 0;
				while (t == 0)
				{
					cout << "1.  Продолжить работу\n";
					cout << "2.  Вернуться назад \n";
					int flag;
					flag = Check<int>();
					while (flag < 0 || flag > 2) {
						cout << "Ошибка ввода. Повторите попытку\n";
						flag = Check<int>();
					};
					itoa(flag, buf, 10);
					send(s, buf, 20, 0);
					switch (flag)
					{
					case 1:
					{
						system("cls");
						cout << "Введите логин администратора: " << endl;
						cin >> ob.login;
						send(s, ob.login, 20, 0);
						cout << "Введите пароль администратора: " << endl;
						cin >> ob.password;
						send(s, ob.password, 20, 0);
						if (recv(s, res, sizeof(res), 0) != 0)
						{
							result = atoi(res);
							if (result == 1)
							{

								for (int i = 0; i < mat.size; i++) {
									for (int j = 0; j < mat.size; j++) {
										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										mat.R[i][j] = result;
										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										mat.C[i][j] = result;
									}
								}


								system("cls");
								int u = 0;
								while (u == 0)
								{
									cout << "\tМеню администратора:\n" << endl;
									cout << "1. Заполнение матриц." << endl;
									cout << "2. Редактирование оценок." << endl;
									cout << "3. Вывод матриц оценок." << endl;
									cout << "4. Чтение из файла и проведение вычисления." << endl;
									cout << "5. Добавление нового пользователя." << endl;
									cout << "6. Удаление пользователей." << endl;
									cout << "7. Редактирование пользователей." << endl;
									cout << "8. Просмотр списка пользователей." << endl;
									cout << "9. Добавить должность" << endl;
									cout << "10. Удалить должность" << endl;
									cout << "11. Добавить эксперта" << endl;
									cout << "12. Список должностей" << endl;
									cout << "13. Найти эксперта, занимающего эту должность" << endl;
									cout << "0. Выход\n\n" << endl;

									int choice = Check<int>();
									while (choice < 0 || choice > 13) {
										cout << "Ошибка ввода. Повторите попытку\n";
										choice = Check<int>();
									};
									itoa(choice, buf, 10);
									send(s, buf, 20, 0);
									system("cls");
									switch (choice)
									{
									case 1:
									{
										system("cls");
										cout << "Заполните матрицу взаимных оценок компетентности экспертов." << endl;
										cout << "Учитывая, что"<< endl <<"1. Директор"<< endl << "2. Кондитер "<< endl << "3. Бухгалтер"  << endl;
										for (int i = 0; i < mat.size; i++) {
											for (int j = 0; j < mat.size; j++) {
												if (i == j) continue;
												switch (i) {
												case 0: 
													cout << "Директор";
													break;
												case 1:
													cout << "Кондитер";
													break;
												case 2:
													cout << "Бухгалтер";
													break;
												}
												switch (j) {
												case 0:
													cout << " -> Директор   ";
													break;
												case 1:
													cout << " -> Кондитер   ";
													break;
												case 2:
													cout << " -> Бухгалтер   ";
													break;
												}
												cout << "R" << i + 1 << j + 1 << " = ";
												mat.R[i][j] = Check<int>();
												cout << endl;
												while (mat.R[i][j] < 0 || mat.R[i][j] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "R" << i + 1 << j + 1 << " = ";
													mat.R[i][j] = Check<int>();
													cout << endl;
												};
												itoa(mat.R[i][j], buf, 10);
												send(s, buf, 20, 0);
											}
										}
										system("cls");
										cout << "Заполнените матрицу оценок целей." << endl;
										cout << "Альтернативы." << endl;
										cout << "B1 - Сфокусироваться на улучшении качества продукции" << endl;
										cout << "B2 - Сфокусироваться на улучшении технологии производства" << endl;
										cout << "B3 - Сфокусироваться на улучшении качества исходных материалов" << endl;
										cout << endl;
										for (int i = 0; i < mat.size; i++) {
											for (int j = 0; j < mat.size; j++) {
												switch (i) {
												case 0:
													cout << "Директор";
													break;
												case 1:
													cout << "Кондитер";
													break;
												case 2:
													cout << "Бухгалтер";
													break;
												}
												cout << "  оценивает  ";
												switch (j) {
												case 0:
													cout << "улучшение качества продукции ";
													break;
												case 1:
													cout << "улучшение технологии производства";
													break;
												case 2:
													cout << " улучшение качества исходных материалов";
													break;
												}
												cout << "С" << i + 1 << j + 1 << " = ";
												mat.C[i][j] = Check<int>();
												cout << endl;
												while (mat.C[i][j] < 0 || mat.C[i][j] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "С" << i + 1 << j + 1 << " = ";
													mat.C[i][j] = Check<int>();
													cout << endl;
												};
												itoa(mat.C[i][j], buf, 10);
												send(s, buf, 20, 0);
											}
										}
										system("pause");
									}; break;
									case 2:
									{

										while (true) {
											system("cls");
											mat.show();
											cout << endl << "1. Изменить матрицу взаимных оценок компетентности экспертов. " << endl;
											cout << endl << "2. Изменить матрицу оценок целей. " << endl;
											cout << endl << "0. Выход. " << endl;
											int choice = Check<int>();
											while (choice < 0 || choice > 2) {
												cout << "Ошибка ввода. Повторите попытку\n";
												choice = Check<int>();
											};
											if (choice == 1) {
												cout << "Введите номер Эi эксперта, значение оценки которого вы хотите изменить: ";
												cout << "Учитывая, что" << endl << "1. Директор" << endl << "2. Кондитер " << endl << "3. Бухгалтер" << endl;
												int in = Check<int>();;
												while (in < 1 || in > mat.size) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													in = Check<int>();
												};

												cout << "Введите номер Эj оценки, значение которой вы хотите изменить: ";
												
												int jn = Check<int>();;
												while (jn < 1 || jn > mat.size || in == jn) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													jn = Check<int>();
												};
												cout << "Введите новое значение: ";
												cout << "R" << in << jn << " = ";
												mat.R[in - 1][jn - 1] = Check<int>();
												cout << endl;
												while (mat.R[in - 1][jn - 1] < 0 || mat.R[in - 1][jn - 1] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "R" << in << jn << " = ";
													mat.R[in - 1][jn - 1] = Check<int>();
													cout << endl;
												};

											}
											if (choice == 2) {
												cout << "Введите номер Эi эксперта, значение оценки которого вы хотите изменить: " << endl;
												cout << "Учитывая, что" << endl << "1. Директор" << endl << "2. Кондитер " << endl << "3. Бухгалтер" << endl;
												int in = Check<int>();;
												while (in < 1 || in > mat.size) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													in = Check<int>();
												};

												cout << "Введите номер Bj варианта, значение оценки которого вы хотите изменить: ";
												cout << "Альтернативы." << endl;
												cout << "B1 - Сфокусироваться на улучшении качества продукции" << endl;
												cout << "B2 - Сфокусироваться на улучшении технологии производства" << endl;
												cout << "B3 - Сфокусироваться на улучшении качества исходных материалов" << endl;
												cout << endl;
												int jn = Check<int>();;
												while (jn < 1 || jn > mat.size) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													jn = Check<int>();
												};
												cout << "Введите новое значение: ";
												cout << "C" << in << jn << " = ";
												mat.C[in - 1][jn - 1] = Check<int>();
												cout << endl;
												while (mat.C[in - 1][jn - 1] < 0 || mat.C[in - 1][jn - 1] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "C" << in << jn << " = ";
													mat.C[in - 1][jn - 1] = Check<int>();
													cout << endl;
												}
											}


											if (choice == 0) {
												for (int i = 0; i < mat.size; i++) {
													for (int j = 0; j < mat.size; j++) {
														if (i == j) continue;
														itoa(mat.R[i][j], buf, 10);
														send(s, buf, 20, 0);
													}
												}
												for (int i = 0; i < mat.size; i++) {
													for (int j = 0; j < mat.size; j++) {
														itoa(mat.C[i][j], buf, 10);
														send(s, buf, 20, 0);
													}
												}
												break;
											}
										}

									}; break;
									case 3:
									{
										mat.show();
										getch();
									}break;
									case 4:
									{
										for (int i = 0; i < mat.size; i++)
										{
											double r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.r[i] = r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.D[i] = r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.Ck[i] = r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.Dc[i] = r;
										}
										
										mat.show();
										cout << "Оценки компетентности экспертов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											switch (i) {
											case 0:
												cout << "Директор:";
												break;
											case 1:
												cout << "Кондитер:";
												break;
											case 2:
												cout << "Бухгалтер:";
												break;
											}
											cout << "r" << i + 1 << " = " << mat.r[i] << endl;
										}
									/*cout << "Дисперсии оценок экспертов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											cout << "D" << i + 1 << " = " << mat.D[i] << endl;
										}

										cout << "B1 - Сфокусироваться на улучшении качества продукции" << endl;
										cout << "B2 - Сфокусироваться на улучшении технологии производства" << endl;
										cout << "B3 - Сфокусироваться на улучшении качества исходных материалов" << endl;
										cout << endl;
										*/
										cout << "Коэффициенты предпочтительности вариантов:" << endl;

										for (int i = 0; i < mat.size; i++)
										{
											switch (i) {
											case 0:
												cout << "Сфокусироваться на улучшении качества продукции: ";
												break;
											case 1:
												cout << "Сфокусироваться на улучшении технологии производства: ";
												break;
											case 2:
												cout << "Сфокусироваться на улучшении качества исходных материалов: ";
												break;
											}
											cout << "Ck" << i + 1 << " = " << mat.Ck[i] << endl;
										}
										/*cout << "Дисперсии оценок вариантов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											cout << "Dc" << i + 1 << " = " << mat.Dc[i] << endl;
										}*/
										system("pause");
									}break;
									case 5:
									{
										system("cls");
										cout << "Введите логин: " << endl;
										cin >> ob.login;
										send(s, ob.login, 20, 0);
										cout << "Введите пароль: " << endl;
										cin >> ob.password;
										send(s, ob.password, 20, 0);
										if (recv(s, res, sizeof(res), 0) != 0) {
											result = atoi(res);
											if (result == 0) {
												cout << "Регистрация прошла успешно." << endl;
											}
											else {
												if (result == 1)
													cout << "Такой логин уже используется." << endl;
												else if (result == 2)
													cout << "Логин должен состоять только из строчных букв." << endl;
												getch();
											}
										}

									}; break;
									case 6:
									{
										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										if (result > 0)
										{
											while (result > 0)
											{
												system("cls");
												cout << "           Список пользователей:" << endl << endl;
												for (int i = 0; i < result; i++)
												{
													recv(s, ob.login, sizeof(ob.login), 0);
													recv(s, ob.password, sizeof(ob.password), 0);
													cout << i + 1 << ") логин: " << ob.login << " пароль: " << ob.password << endl;
												}
												cout << "0 для выхода\nВведите номер удаляемого пользователя:" << endl;
												int choice = Check<int>();
												while (choice < 0 || choice > result) {
													cout << "Ошибка ввода. Повторите попытку\n";
													choice = Check<int>();
												};
												itoa(choice, buf, 10);
												send(s, buf, 20, 0);
												result--;
												if (choice == 0)
												{
													result = -1;
													break;
												}
											}
										}
										else { cout << "Пользователей нет" << endl << endl; }
										system("pause");
									}; break;
									case 7:
									{
										int k = 0;
										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										if (result > 0)
										{
											while (result)
											{
												system("cls");
												cout << "           Список пользователей:" << endl << endl;
												for (int i = 0; i < result; i++)
												{
													recv(s, ob.login, sizeof(ob.login), 0);
													recv(s, ob.password, sizeof(ob.password), 0);
													cout << i + 1 << ") логин: " << ob.login << " пароль: " << ob.password << endl;
												}
												cout << "0 для выхода\nВведите номер изменяемого пользователя:" << endl;
												int choice = Check<int>();
												while (choice < 0 || choice > result) {
													cout << "Ошибка ввода. Повторите попытку\n";
													choice = Check<int>();
												};
												itoa(choice, buf, 10);
												send(s, buf, 20, 0);
												if (choice == 0)
												{
													result = 0;
													break;
												}
												else {
													cout << "Введите логин: " << endl;
													cin >> ob.login;
													k = 1;
													cout << "Введите пароль: " << endl;
													cin >> ob.password;
													result = 0;
													break;
												}
											}
											if (k) {
												send(s, ob.login, 20, 0);
												send(s, ob.password, 20, 0);
												if (recv(s, res, sizeof(res), 0) != 0) {
													result = atoi(res);
													if (result == 0) {
														break;
													}
													else {
														if (result == 1)
															cout << "Такой логин уже используется." << endl;
														else if (result == 2)
															cout << "Логин должен состоять только из строчных букв." << endl;
														getch();
														break;
													}
												}
											}
										}
										else { cout << "Пользователей нет" << endl << endl; }
										system("pause");

									}; break;
									case 8:
									{

										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										if (result > 0)
										{
											system("cls");
											cout << "           Список пользователей:" << endl << endl;
											for (int i = 0; i < result; i++)
											{
												recv(s, ob.login, sizeof(ob.login), 0);
												recv(s, ob.password, sizeof(ob.password), 0);
												cout << i + 1 << ") логин: " << ob.login << " пароль: " << ob.password << endl;
											}
										}
										else { cout << "Пользователей нет" << endl << endl; }
										system("pause");
									}; break;
									case 9:
										ntesti.addJob();
										break;
									case 10:
										ntesti.delJob();
										break;
									case 11:
										ntesti.addExperttt();
										break;
									case 12:
									{
										system("cls");
										ntesti.outputJob();
										cout << "Нажмите Enter чтобы продолжить" << endl;
										cin.clear();
										rewind(stdin);
										cin.get();
									};
									break;
									case 13:
									{
										system("cls");
										string Jobb;
										cout << " Должность: ";
										cin >> Jobb;
										system("cls");
										ntesti.outputExperttts(Jobb);
										cout << "Нажмите Enter чтобы продолжить" << endl;
										cin.clear();
										rewind(stdin);
										cin.get();
									};
									break;



									case 0: {
										u = 1;
										t = 1; }; break;

									default: cout << "Неверный ввод"; break;
									}
									system("cls");
								}
							}
							else {
								t = 1;
								if (result == 2)
									cout << "Неверный логин или пароль!" << endl;
								else
									cout << "Неверный ввод!" << endl;
								getch();
							}
						}
						system("cls");
						break;
					}
					case 2:
					{
						t = 1;
						break;
					}
					default:
					{
						system("cls");
						cout << "Повторите ввод\n";
						system("pause");
						break; }
					}
				}
				system("cls");
				break;
			}
			case 2:
			{
				system("cls");
				int t = 0;
				while (t == 0) {
					cout << "1.  Вход под уже существующим пользователем\n";
					cout << "2.  Регистрация нового пользователя\n";
					cout << "3.  Выход \n";
					int flag;
					flag = Check<int>();
					while (flag < 0 || flag > 3) {
						cout << "Ошибка ввода. Повторите попытку\n";
						flag = Check<int>();
					};
					itoa(flag, buf, 10);
					send(s, buf, 20, 0);
					switch (flag)
					{
					case 1:
					{
						system("cls");
						cout << "Введите логин: " << endl;
						cin >> ob.login;
						send(s, ob.login, 20, 0);
						cout << "Введите пароль: " << endl;
						cin >> ob.password;
						send(s, ob.password, 20, 0);
						if (recv(s, res, sizeof(res), 0) != 0) {
							result = atoi(res);
							if (result == 1)
							{
								for (int i = 0; i < mat.size; i++) {
									for (int j = 0; j < mat.size; j++) {
										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										mat.R[i][j] = result;
										recv(s, res, sizeof(res), 0);
										result = atoi(res);
										mat.C[i][j] = result;
									}
								}
								system("cls");
								int u = 0;
								while (u == 0) {
									cout << "\tМеню пользователя:\n" << endl;
									cout << "1. Заполнение матриц." << endl;
									cout << "2. Редактирование оценок." << endl;
									cout << "3. Вывод матриц оценок." << endl;
									cout << "4. Чтение из файла и проведение вычисления." << endl;
									cout << "0. Выход\n\n" << endl;
									int choice = Check<int>();
									while (choice < 0 || choice > 4) {
										cout << "Ошибка ввода. Повторите попытку\n";
										choice = Check<int>();
									};
									itoa(choice, buf, 10);
									send(s, buf, 20, 0);
									system("cls");
									switch (choice)
									{
									case 1:
									{
										system("cls");
										cout << "Заполните матрицу взаимных оценок компетентности экспертов." << endl;
										for (int i = 0; i < mat.size; i++) {
											for (int j = 0; j < mat.size; j++) {
												if (i == j) continue;
												switch (i) {
												case 0:
													cout << "Директор";
													break;
												case 1:
													cout << "Кондитер";
													break;
												case 2:
													cout << "Бухгалтер";
													break;
												}
												switch (j) {
												case 0:
													cout << " -> Директор   ";
													break;
												case 1:
													cout << " -> Кондитер   ";
													break;
												case 2:
													cout << " -> Бухгалтер   ";
													break;
												}
												cout << "R" << i + 1 << j + 1 << " = ";
												mat.R[i][j] = Check<int>();
												cout << endl;
												while (mat.R[i][j] < 0 || mat.R[i][j] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "R" << i + 1 << j + 1 << " = ";
													mat.R[i][j] = Check<int>();
													cout << endl;
												};
												itoa(mat.R[i][j], buf, 10);
												send(s, buf, 20, 0);
											}
										}
										system("cls");
										cout << "Заполните матрицу оценок конкурирующих целей" << endl;
										for (int i = 0; i < mat.size; i++) {
											for (int j = 0; j < mat.size; j++) {
												switch (i) {
												case 0:
													cout << "Директор";
													break;
												case 1:
													cout << "Кондитер";
													break;
												case 2:
													cout << "Бухгалтер";
													break;
												}
												cout << "  оценивает  ";
												switch (j) {
												case 0:
													cout << " улучшение качества продукции: ";
													break;
												case 1:
													cout << "улучшение технологии производства: ";
													break;
												case 2:
													cout << "улучшение качества исходных материалов: ";
													break;
												}
												cout << "С" << i + 1 << j + 1 << " = ";
												mat.C[i][j] = Check<int>();
												cout << endl;
												while (mat.C[i][j] < 0 || mat.C[i][j] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "С" << i + 1 << j + 1 << " = ";
													mat.C[i][j] = Check<int>();
													cout << endl;
												};
												itoa(mat.C[i][j], buf, 10);
												send(s, buf, 20, 0);
											}
										}
										system("pause");
									}; break;
									case 2:
									{

										while (true) {
											system("cls");
											mat.show();
											cout << endl << "1. Изменить матрицу взаимных оценок компетентности экспертов. " << endl;
											cout << endl << "2. Изменить матрицу оценок конкурирующих вариантов. " << endl;
											cout << endl << "0. Выход. " << endl;
											int choice = Check<int>();
											while (choice < 0 || choice > 2) {
												cout << "Ошибка ввода. Повторите попытку\n";
												choice = Check<int>();
											};
											if (choice == 1) {
												cout << "Введите номер Эi эксперта, значение оценки которого вы хотите изменить: ";
												int in = Check<int>();;
												while (in < 1 || in > mat.size) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													in = Check<int>();
												};

												cout << "Введите номер Эj оценки, значение которой вы хотите изменить: ";
												int jn = Check<int>();;
												while (jn < 1 || jn > mat.size || in == jn) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													jn = Check<int>();
												};
												cout << "Введите новое значение: ";
												cout << "R" << in << jn << " = ";
												mat.R[in - 1][jn - 1] = Check<int>();
												cout << endl;
												while (mat.R[in - 1][jn - 1] < 0 || mat.R[in - 1][jn - 1] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "R" << in << jn << " = ";
													mat.R[in - 1][jn - 1] = Check<int>();
													cout << endl;
												};

											}
											if (choice == 2) {
												cout << "Введите номер Эi эксперта, значение оценки которого вы хотите изменить: ";
												int in = Check<int>();;
												while (in < 1 || in > mat.size) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													in = Check<int>();
												};

												cout << "Введите номер Bj варианта, значение оценки которого вы хотите изменить: ";
												int jn = Check<int>();;
												while (jn < 1 || jn > mat.size) {
													cout << "Ошибка ввода. Повторите попытку.\n";
													jn = Check<int>();
												};
												cout << "Введите новое значение: ";
												cout << "C" << in << jn << " = ";
												mat.C[in - 1][jn - 1] = Check<int>();
												cout << endl;
												while (mat.C[in - 1][jn - 1] < 0 || mat.C[in - 1][jn - 1] > 10) {
													cout << "Ошибка ввода. Повторите попытку. Оценка должна быть больше 0 и меньше 10\n";
													cout << "C" << in << jn << " = ";
													mat.C[in - 1][jn - 1] = Check<int>();
													cout << endl;
												}
											}


											if (choice == 0) {
												for (int i = 0; i < mat.size; i++) {
													for (int j = 0; j < mat.size; j++) {
														if (i == j) continue;
														itoa(mat.R[i][j], buf, 10);
														send(s, buf, 20, 0);
													}
												}
												for (int i = 0; i < mat.size; i++) {
													for (int j = 0; j < mat.size; j++) {
														itoa(mat.C[i][j], buf, 10);
														send(s, buf, 20, 0);
													}
												}
												break;
											}
										}

									}; break;
									case 3:
									{
										mat.show();
										getch();
									}break;
									case 4:
									{
										for (int i = 0; i < mat.size; i++)
										{
											double r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.r[i] = r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.D[i] = r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.Ck[i] = r;
											recv(s, res, sizeof(res), 0);
											r = atof(res);
											mat.Dc[i] = r;
										}
										cout << "Альтернативы." << endl;
										cout << "B1 - Сфокусироваться на улучшении качества продукции" << endl;
										cout << "B2 - Сфокусироваться на улучшении технологии производства" << endl;
										cout << "B3 - Сфокусироваться на улучшении качества исходных материалов" << endl;
										mat.show();
										cout << "Оценки компетентности экспертов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											cout << "r" << i + 1 << " = " << mat.r[i] << endl;
										}
										/*cout << "Дисперсии оценок экспертов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											cout << "D" << i + 1 << " = " << mat.D[i] << endl;
										}
										*/
										cout << "Коэффициенты предпочтительности вариантов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											cout << "Ck" << i + 1 << " = " << mat.Ck[i] << endl;
										}
										/*cout << "Дисперсии оценок вариантов:" << endl;
										for (int i = 0; i < mat.size; i++)
										{
											cout << "Dc" << i + 1 << " = " << mat.Dc[i] << endl;
										}
										*/
										system("pause");
									}break;
									case 0: {
										u = 1;
										t = 1; }; break;
									default: cout << "Неверный ввод"; break;
									}
									system("cls");
								}
							}
							else {
								t = 1;
								if (result == 0) {
									cout << "Неверно! Повторите ввод!." << endl;
								}
								else if (result == 2)
									cout << "Логин должен состоять только из строчных букв." << endl;
								else if (result == -1)
									cout << "Нет зарегистрированных пользователей." << endl;
								getch();
							}
						}
						//
						system("cls");
						break;
					}
					case 2: {
						system("cls");
						cout << "Введите логин: " << endl;
						cin >> ob.login;
						send(s, ob.login, 20, 0);
						cout << "Введите пароль: " << endl;
						cin >> ob.password;
						send(s, ob.password, 20, 0);
						if (recv(s, res, sizeof(res), 0) != 0) {
							result = atoi(res);
							if (result == 0) {
								cout << "Регистрация прошла успешно." << endl;
							}
							else {
								if (result == 1)
									cout << "Такой логин уже используется." << endl;
								else if (result == 2)
									cout << "Логин должен состоять только из строчных букв." << endl;
								getch();
							}
						}
						//
						system("cls");
						break;
					}
					case 3:
					{
						t = 1;
						break;
					}
					default:
					{
						system("cls");
						cout << "Неверный ввод. Введите другое число\n";
						system("pause");
						break; }
					}
				}
				system("cls");
				break;
			}
			case 3:
				return 0;
			default:
			{
				cout << "Неверный выбор" << endl;
				break; }
			}
		}
		closesocket(s);
	}
	WSACleanup();

}
