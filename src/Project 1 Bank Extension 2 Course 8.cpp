#include <iostream>
#include <string>
#include <vector>
#include<cctype>
#include<fstream>
#include<iomanip>
//#include "DateLib.h";
//#include "MyString.h";
using namespace std;
//using namespace DateLib;
//using namespace MyString;

const string ClientsFile = "Clinets.txt";

const string UsersFile = "Users.txt";

enum ePermission {
FullAccess = -1,
CanShowClientList = 1,
CanAddNewClient = 2,
CanDeleteClient = 4,
CanUpdateClient = 8,
CanFindClient = 16,
CanShowTransactionsMenue = 32,
CanMangeUsers = 64
};

void ShowTransactionsMenue();

void Login();

void BackToMain();

void MainMenueScreen();

void ShowUserMenueScreen();

enum enMainMenue {
	ShowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClient = 4,
	FindClient = 5,
	Transactions = 6,
	MangeUser = 7,
	LogOut = 8

};

enum enTransactionsMenue {

	Deposit = 1,
	Withdraw = 2,
	TotalBalance = 3,
	MainMenue = 4

};

enum enUesrsMenue {
	ListUesrs = 1,
	AddNewUser = 2,
	DeleteUser = 3,
	UpdateUser = 4,
	FindUser = 5,
	MainMenueForUser = 6

};

struct sClint {

	string AccountNumber;
	string PinCode;
	string Name;
	string phone;
	double AccountBalance;
	bool Mark = false;

};

struct sUser {

	string UserName;
	string Password;
	int Permissions =0 ;
	bool MarkForUser = false;

};

sUser CurrentUser;

string ConvertRecordToLine(sClint Clint, string delim = "//##//") {

	string sRecord;

	sRecord += Clint.AccountNumber + delim;
	sRecord += Clint.PinCode + delim;
	sRecord += Clint.Name + delim;
	sRecord += Clint.phone + delim;
	sRecord += to_string(Clint.AccountBalance);

	return sRecord;

}

string ConvertRecordToLine(sUser User, string delim = "//##//") {

	string sRecord;

	sRecord += User.UserName + delim;
	sRecord += User.Password + delim;
	sRecord += to_string(User.Permissions);
	return sRecord;

}

short ReadMianMenue() {
	short Chooes = 0;
	cout << "Chooes What Do you want to do ? [1 to 7]. ";
	cin >> Chooes;
	return Chooes;
}

short ReadTransactionsMenue() {
	short Chooes = 0;
	cout << "Chooes What Do you want to do ? [1 to 4]. ";
	cin >> Chooes;
	return Chooes;
}

short ReadUsersMenue() {
	short Chooes = 0;
	cout << "Chooes What Do you want to do ? [1 to 6]. ";
	cin >> Chooes;
	return Chooes;
}

int ReadDepositOrWithdraw() {
	int D = 0;
	cout << "\nplease enter deposit amount? ";
	cin >> D;
	return D;
}

bool AskToConfermTransaction(char ask) {

	cout << "are sure you want perform this transaction? y/n ";
	cin >> ask;
	if (toupper(ask) == 'Y') {
		return false;
	}
	else
	{

		system("cls");
		ShowTransactionsMenue();

	}

}

vector <sClint> SaveDataClientsToFile(vector<sClint>& vClint, string ClientsFile) {

	fstream MyFile;

	MyFile.open(ClientsFile, ios::out);
	string Line;
	if (MyFile.is_open()) {



		for (sClint& C : vClint) {

			if (C.Mark == false) {

				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;

			}
		}

		MyFile.close();
	}
	return vClint;
}

vector <sUser> SaveDataUsersToFile(vector<sUser>& vUser, string UserFile) {

	fstream MyFile;

	MyFile.open(UsersFile, ios::out);
	string Line;
	if (MyFile.is_open()) {



		for (sUser& C : vUser) {

			if (C.MarkForUser == false) {

				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;

			}
		}

		MyFile.close();
	}
	return vUser;
}

vector <string> SplitEachWordInVector(string S, string delim) {


	short pos = 0;
	string Word;
	vector <string> vWord;


	while ((pos = S.find(delim)) != std::string::npos) {

		Word = S.substr(0, pos);
		if (Word != "")
		{
			vWord.push_back(Word);

		}

		S.erase(0, pos + delim.length());

	}
	if (S != "")
	{
		vWord.push_back(S);
	}
	return vWord;

}

sClint ConvertLineToRecord(string line, string delim = "//##//") {

	sClint clint;
	vector <string> vConvert;
	vConvert = SplitEachWordInVector(line, delim);

	clint.AccountNumber = vConvert[0];
	clint.PinCode = vConvert[1];
	clint.Name = vConvert[2];
	clint.phone = vConvert[3];
	clint.AccountBalance = stod(vConvert[4]);

	return clint;

}

sUser ConvertLineToRecordForUser(string line, string delim = "//##//") {

	sUser User;
	vector <string> vConvert;
	vConvert = SplitEachWordInVector(line, delim);

	User.UserName = vConvert[0];
	User.Password = vConvert[1];
	User.Permissions = stoi(vConvert[2]);

	return User;

}

string ReadAccountNumber() {

	string AccountNumber;
	cout << "please enter AccountNumber? : ";
	cin >> AccountNumber;
	cout << "\n";
	return AccountNumber;
}

string ReadUserName() {

	string AccountNumber;
	cout << "Enter UserName? : ";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}

string ReadPassword() {

	string AccountNumber;
	cout << "Enter Password? : ";
	getline(cin >> ws, AccountNumber);
	cout << "\n";
	return AccountNumber;
}

void PrintClintData(sClint clint) {

	cout << "-----------------------------------\n";
	cout << "your account number  : " << clint.AccountNumber << endl;
	cout << "your pin code        : " << clint.PinCode << endl;
	cout << "your name            : " << clint.Name << endl;
	cout << "your phone           : " << clint.phone << endl;
	cout << "your account balance : " << clint.AccountBalance << endl;
	cout << "-----------------------------------\n";
}

void PrintUserData(sUser User) {

	cout << "-----------------------------------\n";
	cout << "your User Name      : " << User.UserName << endl;
	cout << "your Password       : " << User.Password << endl;
	cout << "your Permissions    : " << User.Permissions << endl;
	cout << "-----------------------------------\n";
}

void AddLinesToFiles(string ClientsFile, string Line) {
	fstream MyFile;

	MyFile.open(ClientsFile, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << Line << endl;

		MyFile.close();
	}

}

vector <sClint> LoadFileContentToVector(string ClientsFile) {
	vector <sClint> vClint;
	fstream MyFile;

	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {

		string Line;
		sClint clint;
		while (getline(MyFile, Line)) {

			clint = ConvertLineToRecord(Line);

			vClint.push_back(clint);

		}

		MyFile.close();
	}
	return vClint;
}

vector <sUser> LoadFileContentToVectorForUser(string UsersFile) {
	vector <sUser> vUser;
	fstream MyFile;

	MyFile.open(UsersFile , ios::in);

	if (MyFile.is_open()) {

		string Line;
		sUser User;
		while (getline(MyFile, Line)) {

			User = ConvertLineToRecordForUser(Line);

			vUser.push_back(User);

		}

		MyFile.close();
	}
	return vUser;
}

bool CheakUserIfUserRrepeted(string UserName, string UsersFile) {

	fstream MyFile;

	MyFile.open(UsersFile, ios::in);

	if (MyFile.is_open()) {

		string Line;
		sUser User;
		while (getline(MyFile, Line)) {

			User = ConvertLineToRecordForUser(Line);
			if (UserName == User.UserName) {
				MyFile.close();
				return true;

			}


		}

		MyFile.close();
	}
	return false;
}

bool CheakClientIfUserRrepeted(string AccountNum, string ClientsFile) {

	fstream MyFile;

	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {

		string Line;
		sClint clint;
		while (getline(MyFile, Line)) {

			clint = ConvertLineToRecord(Line);
			if (AccountNum == clint.AccountNumber) {
				MyFile.close();
				return true;

			}


		}

		MyFile.close();
	}
	return false;
}

short ReadPermissions() {

	int Permissions =0;
	char AddPermissions = 'Y';

	cout << "Do You Wnat To Give Full Access? Y/N ";
	cin >> AddPermissions;

	if (toupper(AddPermissions) == 'Y') {
		Permissions |= ePermission::FullAccess;
	}

	else {
		cout << "Do You Wnat To Give Access To : \n";

		cout << "Show Client? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions = Permissions | ePermission::CanShowClientList;
		} // 0001 = 1

		cout << "Add New Client? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions |= ePermission::CanAddNewClient;
		}
		//0001
		//0010
		//----
		//0011 = 3

		cout << "Delete Client ? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions |= ePermission::CanDeleteClient;
		}
		/*
		0011
		0100
		----
		0111 = 7

		*/


		cout << "Update Client ? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions |= ePermission::CanUpdateClient;
		}
		/*
		0111
		1000
		----
		1111 = 15


		*/
		cout << "Find Client ? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions |= ePermission::CanFindClient;
		}
		cout << "Can Show Transactions ? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions |= ePermission::CanShowTransactionsMenue;
		}
		cout << "Can Show Mange Users ? y/n? ";
		cin >> AddPermissions;

		if (toupper(AddPermissions) == 'Y') {
			Permissions |= ePermission::CanMangeUsers;
		}

	}

	return Permissions;
}

void AccessDenied() {
	system("cls");
	cout << "-----------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You Dont Have Permissions to do this,\n";
	cout << "Plsease Conact Your Admin.\n";
	cout << "-----------------------------------\n";
	BackToMain();
}

bool CheckPermissions(ePermission Permission) {
	
	if (CurrentUser.Permissions == ePermission::FullAccess) {
		return true;
	}

	if ((CurrentUser.Permissions & Permission) == Permission)
		return true;
	else
		return false;

}



sClint ReadClint() {

	sClint Clint;

	cout << "Enter your account number :";
	getline(cin >> ws, Clint.AccountNumber);

	while (CheakClientIfUserRrepeted(Clint.AccountNumber, ClientsFile)) {

		cout << "client with [" << Clint.AccountNumber << "] already exists,"
			<< " enter another Account Number? ";
		getline(cin >> ws, Clint.AccountNumber);

	}

	cout << "Enter your pin code :";
	getline(cin, Clint.PinCode);

	cout << "Enter your name :";
	getline(cin, Clint.Name);

	cout << "Enter your phone :";
	getline(cin, Clint.phone);

	cout << "Enter your account balance :";
	cin >> Clint.AccountBalance;

	return Clint;
}

sUser ReadUser() {

	sUser User;

	cout << "Enter your User Name :";

	getline(cin >> ws, User.UserName);

	while (CheakUserIfUserRrepeted(User.UserName,UsersFile )) {

		cout << "User with [" << User.UserName << "] already exists,"
			<< " enter another Account Number? ";
		getline(cin >> ws, User.UserName);

	}

	cout << "Enter your pin code :";
	getline(cin,User.Password);

	User.Permissions = ReadPermissions();

	return User;
}

sClint ChangeClintForClient(string AccountNum)
{
	sClint Clint;

	Clint.AccountNumber = AccountNum;

	cout << "Enter your pin code :";
	getline(cin >> ws, Clint.PinCode);

	cout << "Enter your name :";
	getline(cin, Clint.Name);

	cout << "Enter your phone :";
	getline(cin, Clint.phone);

	cout << "Enter your account balance :";
	cin >> Clint.AccountBalance;

	return Clint;
}

sUser ChangeClintForUser(string NameUser)
{
	sUser User;

	User.UserName = NameUser;

	cout << "Enter your password :";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissions();
	
	return User;
}

void AddClient() {

	cout << "Adding New Client\n\n";

	sClint client;
	client = ReadClint();

	AddLinesToFiles(ClientsFile, ConvertRecordToLine(client));

}

void AddUser() {

	cout << "Adding New User\n\n";

	sUser User;
	User = ReadUser();

	AddLinesToFiles(UsersFile, ConvertRecordToLine(User));

}

void PrintOwnClint(sClint clint) {

	cout << "| " << setw(15) << left << clint.AccountNumber;
	cout << "| " << setw(10) << left << clint.PinCode;
	cout << "| " << setw(40) << left << clint.Name;
	cout << "| " << setw(12) << left << clint.phone;
	cout << "| " << setw(12) << left << clint.AccountBalance;

}

void PrintOwnUser(sUser User) {

	cout << "| " << setw(20) << left << User.UserName;
	cout << "| " << setw(15) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;

}

void PrintOwnClintForBalancesList(sClint clint) {

	cout << "| " << setw(20) << left << clint.AccountNumber;
	cout << "| " << setw(50) << left << clint.Name;
	cout << "| " << setw(30) << left << clint.AccountBalance;

}

bool FindAccountNumber(string AccountNumber, vector <sClint> vClint, sClint& clint)
{

	vClint = LoadFileContentToVector(ClientsFile);
	for (sClint& C : vClint) {

		if (C.AccountNumber == AccountNumber) {

			clint = C;
			return true;

		}

	}
	return false;
}

bool FindUserName(string UserName, vector <sUser> vUser, sUser& User)
{

	vUser = LoadFileContentToVectorForUser(UsersFile);
	for (sUser& C : vUser) {

		if (C.UserName == UserName) {

			User = C;
			return true;

		}

	}
	return false;
}

bool DepositAmount(vector <sClint>& vClint, string AccountNum, int amount) {

	char ask = 'y';


	if (AskToConfermTransaction(ask));
	{
		for (sClint& C : vClint) {
			if (C.AccountNumber == AccountNum) {
				C.AccountBalance += amount;
				SaveDataClientsToFile(vClint, ClientsFile);
				cout << "Done succssfuly New Balance is :" << C.AccountBalance << endl;
				return true;
			}
		}
	}
	return false;
}

void ListAndTotalBalances(vector <sClint> vClint) {
	unsigned int Totalbalances = 0;
	cout << "\n\t\t\t\t\tClient List (" << vClint.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "Accout Number";
	cout << "| " << left << setw(50) << "Client Name";
	cout << "| " << left << setw(30) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClint Client : vClint)
	{
		PrintOwnClintForBalancesList(Client);
		cout << endl;
		Totalbalances += Client.AccountBalance;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n";


	cout << "\t\t\t\t\tTotal Balances =" << Totalbalances << endl;

}

bool MarkClintToDelete(string AccountNum, vector<sClint>& vClint) {

	for (sClint& C : vClint) {

		if (C.AccountNumber == AccountNum) {

			C.Mark = true;
			return true;

		}



	}
	return false;


}

bool MarkUserToDelete(string UserName, vector<sUser>& vUser) {

	for (sUser& C : vUser) {

		if (C.UserName == UserName) {

			C.MarkForUser = true;
			return true;

		}



	}
	return false;


}

bool DeleteClintByAccountNumber(string AccountNum, vector<sClint>& vClint) {

	sClint Clint;
	char ask = 'y';
	if (FindAccountNumber(AccountNum, vClint, Clint)) {

		PrintClintData(Clint);
		cout << "\ndo you want realy to delete this client ? ";
		cin >> ask;
		if (toupper(ask) == 'Y') {
			MarkClintToDelete(AccountNum, vClint);

			SaveDataClientsToFile(vClint, ClientsFile);

			vClint = LoadFileContentToVector(ClientsFile);

			cout << "\nclient are deleted succssfuly.\n";

			return true;

		}
	}
	else {

		cout << "Account Number not found.\n";

	}


	return false;
}

bool DeleteUsers(string UserName, vector<sUser>& vUser) {

	sUser User;
	char ask = 'y';
	if (FindUserName(UserName, vUser, User)) {

		PrintUserData(User);
		cout << "\ndo you want realy to delete this client ? ";
		cin >> ask;
		if (toupper(ask) == 'Y') {
			MarkUserToDelete(UserName, vUser);

			SaveDataUsersToFile(vUser, ClientsFile);

			vUser = LoadFileContentToVectorForUser(UsersFile);

			cout << "\nclient are deleted succssfuly.\n";

			return true;

		}
	}
	else {

		cout << "Account Number not found.\n";

	}


	return false;
}

vector <sClint> ApditeClintsFromFile(vector<sClint>& vClint, string ClientsFile) {

	fstream MyFile;

	MyFile.open(ClientsFile, ios::out);
	string Line;
	if (MyFile.is_open()) {



		for (sClint& C : vClint) {

			if (C.Mark == false) {

				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;

			}
		}

		MyFile.close();
	}
	return vClint;
}

vector <sUser> ApditeUserFromFile(vector<sUser>& vUser, string UserFile) {

	fstream MyFile;

	MyFile.open(UsersFile, ios::out);
	string Line;
	if (MyFile.is_open()) {



		for (sUser& C : vUser) {

			if (C.MarkForUser == false) {

				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;

			}
		}

		MyFile.close();
	}
	return vUser;
}

bool ApditeClintByAccountNumber(string AccountNum, vector<sClint>& vClint) {

	sClint Clint;
	char ask = 'y';
	if (FindAccountNumber(AccountNum, vClint, Clint)) {

		PrintClintData(Clint);
		cout << "\ndo you want realy to apdite this client ? ";
		cin >> ask;
		if (toupper(ask) == 'Y') {

			for (sClint& C : vClint) {

				if (C.AccountNumber == AccountNum) {

					C = ChangeClintForClient(AccountNum);
					break;
				}
			}

			ApditeClintsFromFile(vClint, ClientsFile);

			cout << "\nclient are Apdite succssfuly.\n";

			return true;

		}
	}
	else {

		cout << "Account Number not found.\n";

	}


	return false;
}

bool UpditeUser(string UserName, vector<sUser>& vUser) {

	sUser User;
	char ask = 'y';
	if (FindUserName(UserName, vUser, User)) {

		PrintUserData(User);
		cout << "\ndo you want realy to apdite this client ? ";
		cin >> ask;
		if (toupper(ask) == 'Y') {

			for (sUser& C : vUser) {

				if (C.UserName == UserName) {

					C = ChangeClintForUser(UserName);
					break;
				}
			}

			ApditeUserFromFile(vUser, UsersFile);

			cout << "\nclient are Apdite succssfuly.\n";

			return true;

		}
	}
	else {

		cout << "Account Number not found.\n";

	}


	return false;
}

void PrintClintsList(vector <sClint> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClint Client : vClients)
	{
		PrintOwnClint(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}


void AddMoreClients() {
	char AddMore = 'Y';
	do {
		system("cls");
		AddClient();

		cout << "\nMission seccssfuly,Do you want add more? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');


}

void AddMoreUsers() {
	char AddMore = 'Y';
	do {
		system("cls");
		AddUser();

		cout << "\nMission seccssfuly,Do you want add more? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');


}

void BackToMain() {

	cout << "\nPress any key to go back to Main Menue...";
	system("pause>0");
	system("cls");
	MainMenueScreen();

}

void ShowClientListScrren()
{
	if (!CheckPermissions(ePermission::CanShowClientList)) {
		AccessDenied();
	}

	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);

	PrintClintsList(vClint);
	BackToMain();

}

void ShowAddNewClientScrren()
{
	if (!CheckPermissions(ePermission::CanAddNewClient)) {
		AccessDenied();
	}
	cout << "-----------------------------------\n";
	cout << "\t Add New Client Screen \n";
	cout << "-----------------------------------\n";
	AddMoreClients();
	BackToMain();

}

void ShowDeleteClientScrren()
{

	if (!CheckPermissions(ePermission::CanDeleteClient)) {
		AccessDenied();
	}

	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);
	string AccountNumber;
	sClint Clint;

	cout << "-----------------------------------\n";
	cout << "\t Delete Client Screen \n";
	cout << "-----------------------------------\n";
	AccountNumber = ReadAccountNumber();
	DeleteClintByAccountNumber(AccountNumber, vClint);
	BackToMain();

}

void ShowUpdateClientScrren()
{

	if (!CheckPermissions(ePermission::CanUpdateClient)) {
		AccessDenied();
	}

	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);
	string AccountNumber;
	sClint Clint;

	cout << "-----------------------------------\n";
	cout << "\t Update Client Screen \n";
	cout << "-----------------------------------\n";
	AccountNumber = ReadAccountNumber();
	ApditeClintByAccountNumber(AccountNumber, vClint);
	vClint = LoadFileContentToVector(ClientsFile);
}

void ShowFindClientScrren()
{

	if (!CheckPermissions(ePermission::CanFindClient)) {
		AccessDenied();
	}

	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);
	string AccountNumber;
	sClint Clint;
	cout << "-----------------------------------\n";
	cout << "\t Find Client Screen \n ";
	cout << "-----------------------------------\n";
	AccountNumber = ReadAccountNumber();
	if (FindAccountNumber(AccountNumber, vClint, Clint)) {

		PrintClintData(Clint);

	}
	else
	{
		cout << "\nThe clint Account number(" << AccountNumber << ") not found.\n";
	}
	BackToMain();
}

void ShowExitScrren()
{
	cout << "-----------------------------------\n";
	cout << "\t Program Ends :-] \n";
	cout << "-----------------------------------\n";
}

void BackToTransactionMenue() {

	cout << "\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	system("cls");
	ShowTransactionsMenue();

}

void ShowDepositScreen() {
	string AccountNumber;
	sClint Clint;
	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);
	int amount = 0;
	cout << "-----------------------------------\n";
	cout << "\t Deposit Screen \n";
	cout << "-----------------------------------\n";

	AccountNumber = ReadAccountNumber();

	while (!FindAccountNumber(AccountNumber, vClint, Clint)) {

		cout << "Client with [" << AccountNumber << "] is not exist.";

		AccountNumber = ReadAccountNumber();
	}

	PrintClintData(Clint);

	amount = ReadDepositOrWithdraw();

	DepositAmount(vClint, AccountNumber, amount);

}

void ShowWithdrawScreen() {
	string AccountNumber;
	sClint Clint;
	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);
	int amount = 0;
	cout << "-----------------------------------\n";
	cout << "\t Withdraw Screen \n";
	cout << "-----------------------------------\n";

	AccountNumber = ReadAccountNumber();
	while (!FindAccountNumber(AccountNumber, vClint, Clint)) {

		cout << "Client with [" << AccountNumber << "] is not exist.";

		AccountNumber = ReadAccountNumber();
	}

	PrintClintData(Clint);

	cout << "please enter withdraw amount ?" << endl;
	cin >> amount;

	while (amount > Clint.AccountBalance) {
		cout << "Amount Exceeds the balance, you can withdraw up to : " << amount;
		cout << "please enter anouther withdraw amount ?" << endl;
		cin >> amount;
	}

	DepositAmount(vClint, AccountNumber, amount * -1);
}

void ShowListAndTotalBalances() {
	vector <sClint> vClint = LoadFileContentToVector(ClientsFile);

	ListAndTotalBalances(vClint);


}

void PrintUsersList(vector <sUser> vUser)
{
	cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "User Name";

	cout << "| " << left << setw(15) << "Password";

	cout << "| " << left << setw(40) << "Permissions";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sUser U : vUser)
	{
		PrintOwnUser(U);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowUsersList() {

	vector <sUser> vUser = LoadFileContentToVectorForUser(UsersFile);

	PrintUsersList(vUser);
}

void ShowAddNewUserScreen() {


	cout << "-----------------------------------\n";
	cout << "\t Add New User Screen \n";
	cout << "-----------------------------------\n";
	AddMoreUsers();


}

void ShowUserDeleteScreen() {


	vector <sUser> vUser = LoadFileContentToVectorForUser(UsersFile);
	string UserName ;
	cout << "-----------------------------------\n";
	cout << "\t Delete User Screen \n";
	cout << "-----------------------------------\n";
	UserName = ReadAccountNumber();
	DeleteUsers(UserName, vUser);

}

void ShowUpdateUserScreen() {

	vector <sUser> vUser = LoadFileContentToVectorForUser(UsersFile);
	string UserName;

	cout << "-----------------------------------\n";
	cout << "\t Update User Screen \n";
	cout << "-----------------------------------\n";
	UserName = ReadAccountNumber();
	UpditeUser(UserName, vUser);
	vUser = LoadFileContentToVectorForUser(UsersFile);


}

void ShowFindUserScreen() {
	vector <sUser> vUser = LoadFileContentToVectorForUser(UsersFile);
	string UserName;
	sUser User;
	cout << "-----------------------------------\n";
	cout << "\t Find UserName Screen \n ";
	cout << "-----------------------------------\n";
	UserName = ReadAccountNumber();
	if (FindUserName(UserName, vUser, User)) {

		PrintUserData(User);

	}
	else
	{
		cout << "\nThe UserName (" << UserName << ") not found.\n";
	}
}

void BackToUserMenue() {

	cout << "\nPress any key to go back to User Menue...";
	system("pause>0");
	system("cls");
	ShowUserMenueScreen();

}



void PerformUserMenue(enUesrsMenue UserMenue) {

	switch (UserMenue) {

	case enUesrsMenue::ListUesrs:
		system("cls");
		ShowUsersList();
		BackToUserMenue();
		break;

	case enUesrsMenue::AddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		BackToUserMenue();
		break;

	case enUesrsMenue::DeleteUser:
		system("cls");
		ShowUserDeleteScreen();
		BackToUserMenue();
		break;

	case enUesrsMenue::UpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		BackToUserMenue();
		break;

	case enUesrsMenue::FindUser:
		system("cls");
		ShowFindUserScreen();
		BackToUserMenue();
		break;
		 
	case enUesrsMenue::MainMenueForUser:
		system("cls");
		MainMenueScreen();
		break;
	}
	


}

void ShowUserMenueScreen() {

	if (!CheckPermissions(ePermission::CanMangeUsers)) {
		AccessDenied();
	}

	cout << "===============================================\n";
	cout << "\t\t User Menue Screen\n";
	cout << "===============================================\n";
	cout << "\t[1] Show Users List. \n";
	cout << "\t[2] Add New User. \n";
	cout << "\t[3] Delete User. \n";
	cout << "\t[4] Uapdate User Info. \n";
	cout << "\t[5] Find User. \n";
	cout << "\t[6] Main Menue.\n";
	cout << "===============================================\n";
	PerformUserMenue(enUesrsMenue(ReadUsersMenue()));
}

void PerformTransactionsMenue(enTransactionsMenue TransactionsMenue) {

	switch (TransactionsMenue) {

	case enTransactionsMenue::Deposit:
		system("cls");
		ShowDepositScreen();
		BackToTransactionMenue();
		break;

	case enTransactionsMenue::Withdraw:
		system("cls");
		ShowWithdrawScreen();
		BackToTransactionMenue();
		break;

	case enTransactionsMenue::TotalBalance:
		system("cls");
		ShowListAndTotalBalances();
		BackToTransactionMenue();
		break;

	case enTransactionsMenue::MainMenue:
		system("cls");
		MainMenueScreen();
		break;

	}

}

void ShowTransactionsMenue() {

	if (!CheckPermissions(ePermission::CanShowTransactionsMenue)) {
		AccessDenied();
	}

	cout << "===============================================\n";
	cout << "\t Transactions Menue Screen\n";
	cout << "===============================================\n";
	cout << "\t[1] Deposit. \n";
	cout << "\t[2] WithDraw. \n";
	cout << "\t[3] Total Balance. \n";
	cout << "\t[4] Main Menue. \n";

	cout << "===============================================\n";

	PerformTransactionsMenue(enTransactionsMenue(ReadTransactionsMenue()));

}

void PerformMainMenue(enMainMenue MainMenue) {


	sUser User;

	switch (MainMenue) {

	case enMainMenue::ShowClientList:
		system("cls");
		ShowClientListScrren();
		BackToMain();
		break;
	case enMainMenue::AddNewClient:
		system("cls");
		ShowAddNewClientScrren();
		BackToMain();
		break;
	case enMainMenue::DeleteClient:
		system("cls");
		ShowDeleteClientScrren();
		BackToMain();
		break;
	case enMainMenue::UpdateClient:
		system("cls");
		ShowUpdateClientScrren();
		BackToMain();
		break;
	case enMainMenue::FindClient:
		system("cls");
		ShowFindClientScrren();
		BackToMain();
		break;
	case enMainMenue::Transactions:
		system("cls");
		ShowTransactionsMenue();
		break;
	case enMainMenue::MangeUser:
		system("cls");
		ShowUserMenueScreen();
		break;
	case enMainMenue::LogOut:
		system("cls");
		Login();
		break;
	}

}

void MainMenueScreen() {

	cout << "===============================================\n";
	cout << "\t\t Main Menue Screen\n";
	cout << "===============================================\n";
	cout << "\t[1] Show Client List. \n";
	cout << "\t[2] AddNew Client. \n";
	cout << "\t[3] Delete Client. \n";
	cout << "\t[4] Uapdate Client Info. \n";
	cout << "\t[5] Find Client. \n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Mange Users.\n";
	cout << "\t[8] LogOut. \n";
	cout << "===============================================\n";

	PerformMainMenue(enMainMenue(ReadMianMenue()));
}

bool FindUserByUsernameAndPassword(string UserName,string Password , sUser User) {

	vector <sUser> vUser = LoadFileContentToVectorForUser(UsersFile);

	for (sUser& C : vUser) {

		if (C.UserName == UserName && C.Password == Password) {

			CurrentUser = C;
			return true;

		}
	}
	return false;
}

bool InfoUser(string UserName, string Password) {

	return FindUserByUsernameAndPassword(UserName, Password, CurrentUser);

}

void Login() {

	bool flag = false;
	string UserName, Password;

	do {
		system("cls");
		cout << "-----------------------------------\n";
		cout << "\t Login Screen \n";
		cout << "-----------------------------------\n";
		if (flag) {
			cout << "Invlaid Username/Password!\n";
		}
		cout << "Enter UserName :";
		cin >>UserName ;
		cout << "Enter Password :";
		cin >> Password;
		flag = !InfoUser(UserName, Password);


	} while (flag);
	system("cls");
	MainMenueScreen();

}

int main() {

	Login();

	system("pause>0");
	return 0;
}