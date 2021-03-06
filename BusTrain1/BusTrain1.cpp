#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
using namespace std;
const int SIZE_ARR_OF_ACCOUNTS = 1;
const char *ADMIN_STATUS = "111";
const string FILE_OF_ACCOUNTS = "User.txt";
const string FILE_OF_TICKETS = "Ticket.txt";
const int SIZE_ARR_OF_TICKET = 100;
int account_point = 0;
struct Accounts {
	string login;
	string password;
	string role; // USER-100/ADMIN-111
}ac;
struct Tickets {
	string price;
	string Number_of_route;
	string Num_of_ticket;
	string DepDate;
	string ArrDate;
	string DeparturePlace;
	string ArrivalPlace;
}tk;
void writeEndFileAccounts(Accounts new_account);
void writeEndFileTickets(Tickets mas_ticket);
string SetLogin();
string SetPassword();
//void auth_block();
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	primary_authorization();

}
void primary_authorization() {
	Accounts mas_of_accounts[SIZE_ARR_OF_ACCOUNTS];
	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (fin.peek() == EOF) {
		cout << "Вы являетесь первым пользователем программы!" << endl;
		cout << "Введите логин:" << endl;
		mas_of_accounts[0].login = SetLogin();
		cout << "Введите пароль:" << endl;
		mas_of_accounts[0].password = SetPassword();
		mas_of_accounts[0].role = "111";
		account_point = 1;
		writeEndFileAccounts(mas_of_accounts[0]);
		menu::authorization();
		fin.close();
	}
	else {
	menu::authorization();
	switch (checkInterval(1, 3)) {
	case 1: auth(); break;
	case 2: signup(); break;
	case 3: exit(1);
	}
	}

}
void writeEndFileAccounts(Accounts new_account)
{
	ofstream fout(FILE_OF_ACCOUNTS, ios::app);
	fout << new_account.login << " " << new_account.password << " " << new_account.role;
	fout << endl;
	fout.close();
}
void auth() {
	char* login = new char[256];
	char* password = new char[256];
	int controller, autho;
	int access = 0;
	autho = controller = 0;
	cout << "Login: "; cin.clear(); cin.getline(login, 256, '\n');
	cout << "Password: "; cin.clear(); cin.getline(password, 256, '\n');
	cout << endl;
	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	char* checher_login = new char[256];
	char* checher_password = new char[256];
	char* checher_role = new char[256];
	fin.seekg(0, ios::beg);

	if (!fin) {
		cout << "Нет доступа к файлу,обратитесь к админу///";
	}
	else {
		while (strcmp(checher_login, login) != 0 && !fin.eof()) {
			fin >> checher_login;
			if (strcmp(login, checher_login) == 0) {
				fin >> checher_password;
				controller = 0;
			}
			else {
				controller = 1;
			}
		}
		if (strcmp(password, checher_password) != 0) {
			controller = 1;
		}
		else {
			fin >> checher_role;
		}
		if (controller == 1) {
			delete[]login;
			delete[]password;
			delete[]checher_login;
			delete[]checher_password;
			fin.close();
			cout << "Логин или пароль введены неверно.Повторите попытку" << endl;
			main();
		}
		else {
			cout << "Вы вошли...." << endl;
			if (strcmp(checher_role,ADMIN_STATUS) == 0) {
				system("cls");
				delete[]login;
				delete[]password;
				delete[]checher_login;
				delete[]checher_password;
				delete[]checher_role;
				fin.close();
				admin_menu();
			}
			else {
				delete[]login;
				delete[]password;
				delete[]checher_login;
				delete[]checher_password;
				delete[]checher_role;
				system("cls");
				fin.close();
				user();
			}
			
		}
	}
}
void admin_menu(){
	system("cls");
	menu::vibor_menu();
	switch (checkInterval(1, 4)) {
	case 1: admin(); break;
	case 2: user(); break;
	case 3: primary_authorization(); break;
	case 4: exit(1);
	}
}
void signup() {
	if (account_point == 0) {
		char* login = new char[256];
		int controller = 0;
		Accounts mas_of_accounts[SIZE_ARR_OF_ACCOUNTS];
		ifstream fout(FILE_OF_ACCOUNTS);
		cout << "\t\tРегестрация:" << endl;
		cout << "Введите логин:" << endl;
		strcpy(login, SetLogin().data());

		char* login_check_povtor = new char[256];
		if (!fout.is_open()) {
			cout << "Не удаётся открыть бд...Обратитесь к Администратору"<<endl;
		}
		else {
			while (!fout.eof()) {
				fout >> login_check_povtor;
				if (strcmp(login_check_povtor, login) != 0) {
					controller =0;
				}
				else {
					controller = 1;
					break;
				}
			}
		}
		if (controller == 0) {
			mas_of_accounts[0].login = login;
			cout << "Введите пароль:" << endl;
			mas_of_accounts[0].password = SetPassword();
			mas_of_accounts[0].role = "100";
			account_point = 1;
			writeEndFileAccounts(mas_of_accounts[0]);
			system("cls");
			cout << "Регестрация прошла успешно" << endl;
			primary_authorization();
		}
		else {
			delete[] login;
			delete[] login_check_povtor;
			fout.close();
			cout << "Такой логин уже существует повторите попытку...."<<endl;
			signup();
		}
     
	}
	else {
		cout << "Вы уже создали аккаунт...Авторизуйтесь" << endl;
		primary_authorization();
	}
}
string SetLogin() {
	int controller;
	char* BufForWriting = new char[100];
	char symbols[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm._-1234567890";
	do {
		controller = 0;
		cin.clear();
		cin.getline(BufForWriting, 100, '\n');
		if (strlen(BufForWriting) < 6)
		{
			cout << "Логин должен содержать 6 или более символов: ";
			controller = 1;
		}
		else
		{
			for (register int i = 0; BufForWriting[i] != '\0'; i++)
			{
				controller = 2;
				for (register int j = 0; symbols[j] != '\0'; j++)
				{
					if (BufForWriting[i] == symbols[j]) { controller = 0; break; }
				}
				if (controller == 2)
				{
					cout << "Логин может содержать латинские буквы, цифры и специальные символы(-._): ";
					break;
				}
			}
		}
	} while (controller != 0);
	return  BufForWriting;
	delete[] BufForWriting;
}
string SetPassword()
{
	char* BufForWriting = new char[100];
	int controller, num, alpha;
	do {
		controller = 0; alpha = 0; num = 0;
		cin.clear(); cin.getline(BufForWriting, 100, '\n');
		if (strlen(BufForWriting) < 8)
		{
			cout << "Пароль должен содержать 8 или более символов: ";
			controller = -1;
		}
		else
		{
			for (register int i = 0; BufForWriting[i] != '\0'; i++)
			{
				if (isspace(BufForWriting[i]))
				{
					cout << "Пароль не должен содержать пробелы: ";
					controller = -1;
					break;
				}
				else if (isdigit(BufForWriting[i]))
					num++;
				else if (isalpha(BufForWriting[i]))
					alpha++;
			}
			if (controller != -1 && (num == 0 || alpha == 0))
			{
				cout << "Пароль должен содержать буквы и цифры: ";
				controller = -1;
			}
		}
	} while (controller == -1);
	return BufForWriting;
	delete[] BufForWriting;
}

 void addInformation(){
	 system("cls");
	 Tickets *mas_of_ticket= new Tickets[SIZE_ARR_OF_TICKET];
	 cout << "\tВведите количество добавлений ~ Автобусных рейсов" << endl;
	 int chislo;
	 cin >> chislo;
	 for (int i = 0; i < chislo; i++){
		 cout << "\tВведите номер рейса:"<<endl;
		 cin >> mas_of_ticket[i].Number_of_route;
		 cout << "\tВведите место отправления :" << endl;
		 cin >> mas_of_ticket[i].DeparturePlace;
		 cout << "\tВведите место прибытия:" << endl;
		 cin >> mas_of_ticket[i].ArrivalPlace;
		 cout << "\tВведите время отправления:" << endl;
		 cin >> mas_of_ticket[i].DepDate;
		 cout << "\tВведите время прибытия:" << endl;
		 cin >> mas_of_ticket[i].ArrDate;
		 cout << "\tВведите количество билетов:" << endl;
		 cin >> mas_of_ticket[i].Num_of_ticket;
		 cout << "\tВведите цену:" << endl;
		 cin >> mas_of_ticket[i].price;
		 writeEndFileTickets(mas_of_ticket[i]);
	 }
	 delete[]mas_of_ticket;
	 admin();
 }
 void writeEndFileTickets(Tickets mas_ticket)
 {
	 ofstream fout(FILE_OF_TICKETS, ios::app);
	 fout<< mas_ticket.Number_of_route << " " << mas_ticket.DeparturePlace << " " << mas_ticket.ArrivalPlace << " " << mas_ticket.DepDate << " " << mas_ticket.ArrDate << " " << mas_ticket.Num_of_ticket << " " << mas_ticket.price;
	 fout << endl;
	 fout.close();
 }
 
 void changeInformation() {

	 system("cls");
	 ifstream fout(FILE_OF_TICKETS, ios::in);
	 showInormatiom();
	 cout << "\tВведите номер рейса который нужно изменить:" << endl;
	 int i_number_line_delete;
	 char* number_of_route = new char[256];
	 char* number_check = new char[256];

	 int counter = 0;
	 int counter_check = 0;
	 int counter_check_str = 0;
	 int counter_check_str_first = 0;
	 cin >> number_of_route;
	 /*i_number_line_delete=atoi(number_of_route);*/
	 vector <string> vec;
	 while (!fout.eof()) {
		 fout >> number_check;
		 counter++;
		 if (counter % 8 == 0 || counter == 1) {

			 if (strcmp(number_of_route, number_check) == 0) {
				 counter_check_str++;
				 while (counter_check <= 6) {
					 vec.push_back(number_check);
					 fout >> number_check;
					 counter_check++;
					 
				 }
				 break;
			 }
		 }
		 if (counter == 8) {
			 counter = 1;
			 counter_check_str++;
			 
		 }
	 }
	 if (counter == 1) {
		 counter_check_str = 1;
	 }
	 else {
		 counter_check_str++;
	 }
	 fout.seekg(0, ios::beg);
	 int i_number_line_now = 0;
	 string line;
	 string line_file_text;
	 
	 while (getline(fout, line)) {
		 i_number_line_now++;
		 if (!(i_number_line_now == counter_check_str)) {
			 line_file_text.insert(line_file_text.size(), line);
			 line_file_text.insert(line_file_text.size(), "\r\n");
		 }
	 }
	 fout.close();
	 ofstream fz;
	 fz.open(FILE_OF_TICKETS, ios::trunc | ios::binary);
	 fz.write(line_file_text.c_str(), line_file_text.size());
	 fz.clear();
	 fz.close();
	 delete[]number_check;
	 delete[]number_of_route;
	 Tickets* mas_of_ticket = new Tickets[SIZE_ARR_OF_TICKET];
	 menu::change_tickets();
	 switch (checkInterval(1, 9)) {
	 case 1:
		 cout << "\tВведите номер рейса:" << endl;
		 cin >> mas_of_ticket[0].Number_of_route;
		 cout << "\tВведите место отправления :" << endl;
		 cin >> mas_of_ticket[0].DeparturePlace;
		 cout << "\tВведите место прибытия:" << endl;
		 cin >> mas_of_ticket[0].ArrivalPlace;
		 cout << "\tВведите время отправления:" << endl;
		 cin >> mas_of_ticket[0].DepDate;
		 cout << "\tВведите время прибытия:" << endl;
		 cin >> mas_of_ticket[0].ArrDate;
		 cout << "\tВведите количество билетов:" << endl;
		 cin >> mas_of_ticket[0].Num_of_ticket;
		 cout << "\tВведите цену:" << endl;
		 cin >> mas_of_ticket[0].price;
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 2:
		 cout << "\tВведите номер рейса:" << endl;
		 cin >> mas_of_ticket[0].Number_of_route;
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].ArrivalPlace = vec[2];
		 mas_of_ticket[0].DepDate = vec[3];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 3:
		 mas_of_ticket[0].Number_of_route = vec[0];
		 cout << "\tВведите место отправления :" << endl;
		 cin >> mas_of_ticket[0].DeparturePlace;
		 mas_of_ticket[0].ArrivalPlace = vec[2];
		 mas_of_ticket[0].DepDate = vec[3];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 4:
		 cout << "\tВведите место прибытия:" << endl;
		 cin >> mas_of_ticket[0].ArrivalPlace;
		 mas_of_ticket[0].Number_of_route = vec[0];
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].DepDate = vec[3];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case5:
		 cout << "\tВведите время отправления:" << endl;
		 cin >> mas_of_ticket[0].DepDate;
		 mas_of_ticket[0].ArrivalPlace= vec[2];
		 mas_of_ticket[0].Number_of_route = vec[0];
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 6:
		 cout << "\tВведите время прибытия:" << endl;
		 cin >> mas_of_ticket[0].ArrDate;
		 mas_of_ticket[0].DepDate=vec[3];
		 mas_of_ticket[0].ArrivalPlace = vec[2];
		 mas_of_ticket[0].Number_of_route = vec[0];
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 7:
		 cout << "\tВведите количество билетов:" << endl;
		 cin >> mas_of_ticket[0].Num_of_ticket;
		 mas_of_ticket[0].Number_of_route = vec[0];
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].ArrivalPlace = vec[2];
		 mas_of_ticket[0].DepDate = vec[3];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 8:
		 cout << "\tВведите цену:" << endl;
		 cin >> mas_of_ticket[0].price;
		 mas_of_ticket[0].Number_of_route=vec[0];
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].ArrivalPlace = vec[2];
		 mas_of_ticket[0].DepDate = vec[3];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 writeEndFileTickets(mas_of_ticket[0]);
		 delete[]mas_of_ticket;
		 break;
	 case 9:
		 mas_of_ticket[0].Number_of_route = vec[0];
		 mas_of_ticket[0].DeparturePlace = vec[1];
		 mas_of_ticket[0].ArrivalPlace = vec[2];
		 mas_of_ticket[0].DepDate = vec[3];
		 mas_of_ticket[0].ArrDate = vec[4];
		 mas_of_ticket[0].Num_of_ticket = vec[5];
		 mas_of_ticket[0].price = vec[6];
		 writeEndFileTickets(mas_of_ticket[0]);
		 
		 system("pause");
		 admin();
		 break;
	 }
	 admin();
 }
 void showInormatiom() {
	 ifstream fout(FILE_OF_TICKETS, ios::in);
	 TextTable t('-', '|', '+');
	 t.add("Номер рейса");
	 t.add("Место отправления");
	 t.add("Место прибытия");
	 t.add("Время отправления");
	 t.add("Время прибытия");
	 t.add("В наличии");
	 t.add("Цена,$");
	 t.endOfRow();
	 while (fout >> tk.Number_of_route >> tk.DeparturePlace >> tk.ArrivalPlace >> tk.DepDate >> tk.ArrDate >> tk.Num_of_ticket >> tk.price) {
		 t.add(tk.Number_of_route);
		 t.add(tk.DeparturePlace);
		 t.add(tk.ArrivalPlace);
		 t.add(tk.DepDate);
		 t.add(tk.ArrDate);
		 t.add(tk.Num_of_ticket);
		 t.add(tk.price);
		 t.endOfRow();
	 }
	 sort();
	 cout << t;
	 fout.close();
 }
 void delInformation() {
	 system("cls");
	 ifstream fout(FILE_OF_TICKETS, ios::in);
	 fout.seekg(0, ios::beg);
	 showInormatiom();
	 cout << "\tВведите номер рейса который нужно удалить:" << endl;
	 int i_number_line_delete;
	 char* number_of_route = new char[256];
	 char* number_check = new char[256];
	 int counter = 0;
	 int counter_check = 0;
	 int counter_check_str = 0;
	 int counter_check_str_first = 0;
	 cin >> number_of_route;
	 /*i_number_line_delete=atoi(number_of_route);*/
	 vector <string> vec;
	 while (!fout.eof()) {
		 fout >> number_check;
		 counter++;
		 if (counter % 8 == 0 || counter == 1) {

			 if (strcmp(number_of_route, number_check) == 0) {
				 counter_check_str++;
				 while (counter_check <= 6) {
					 vec.push_back(number_check);
					 fout >> number_check;
					 counter_check++;

				 }
				 break;
			 }
		 }
		 if (counter == 8) {
			 counter = 1;
			 counter_check_str++;

		 }
	 }
	 if (counter == 1) {
		 counter_check_str = 1;
	 }
	 else {
		 counter_check_str++;
	 }
	 fout.seekg(0, ios::beg);
	 int i_number_line_now = 0;
	 string line;
	 string line_file_text;

	 while (getline(fout, line)) {
		 i_number_line_now++;
		 if (!(i_number_line_now == counter_check_str)) {
			 line_file_text.insert(line_file_text.size(), line);
			 line_file_text.insert(line_file_text.size(), "\r\n");
		 }
	 }
	 fout.close();
	 ofstream fzz;
	 fzz.open(FILE_OF_TICKETS, ios::trunc | ios::binary);
	 fzz.write(line_file_text.c_str(), line_file_text.size());
	 fzz.clear();
	 fzz.close();
	 delete[]number_check;
	 delete[]number_of_route;
	 cout << "Измененная таблица" << endl;
 }
 void user() {
	 menu::user();
 }
 void admin() {
	 menu::admin();
	 switch (checkInterval(1, 8)) {
	 case 1: addInformation();  break;
	 case 2: changeInformation(); break;
	 case 3: system("cls"); showInormatiom(); system("pause"); system("cls"); admin(); break;
	 case 4: delInformation(); showInormatiom(); system("pause"); system("cls"); admin(); break;
	 case 5: system("cls"); showInormatiom(); sort(); showInormatiom(); system("pause"); admin(); break;
	 case 6: system("cls"); change_user(); break;
	 case 7: system("cls"); break;
	 case 8: exit(1);
	 }
 }
 void sort() {
	 ifstream in(FILE_OF_TICKETS);
	 vector<string>vs;
	 string s;
	 while (getline(in, s)) vs.push_back(s);
	 sort(vs.begin(), vs.end());
	 ofstream on(FILE_OF_TICKETS);
	 copy(vs.begin(), vs.end(), ostream_iterator<string>(on, "\n"));
	 cout << "Сортировка прошла успешно" << endl;
	 cout << "Новая таблица:" << endl;
	 on.close();
	 in.close();
 }
 void change_user() {
	 ifstream fout(FILE_OF_ACCOUNTS, ios::in);
	 cout << "ТАБЛИЦА ПОЛЬЗОВАТЕЛЕЙ~"<<endl;
	 TextTable user('*', '|', '+');
	 user.add("ЛОГИН");
	 user.add("ПАРОЛЬ");
	 user.add("СТАТУС");
	 user.endOfRow();
	 while (fout >> ac.login >> ac.password >> ac.role) {
		 user.add(ac.login);
		 user.add(ac.password);
		 user.add(ac.role);
		 user.endOfRow();
	 }
	 cout << user;
	 fout.close();
	 menu::controlUsers();
	 switch (checkInterval(1, 4)) {
	 case 1:  break;
	 case 2: break;
	 case 3: break;
	 case 4: admin(); break;
	 }
 }
 