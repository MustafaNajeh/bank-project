#pragma once


#include <iostream>
#include <string>
#include <vector>
#include<cctype>
#include<fstream>
#include<iomanip>
using namespace std;

namespace MyString {

	const string ClientsFile = "MyFile.txt";

	void ShowTransactionsMenue();

	void MainMenueScreen();

	enum enMainMenue {
		ShowClientList = 1,
		AddNewClient = 2,
		DeleteClient = 3,
		UpdateClient = 4,
		FindClient = 5,
		Transactions = 6,
		LogOut = 7

	};

	enum enTransactionsMenue {

		Deposit = 1,
		Withdraw = 2,
		TotalBalance = 3,
		MainMenue = 4

	};

	struct sClint {

		string AccountNumber;
		string PinCode;
		string Name;
		string phone;
		double AccountBalance;
		bool Mark = false;
	};

	string ConvertRecordToLine(sClint Clint, string delim = "//##//") {

		string sRecord;

		sRecord += Clint.AccountNumber + delim;
		sRecord += Clint.PinCode + delim;
		sRecord += Clint.Name + delim;
		sRecord += Clint.phone + delim;
		sRecord += to_string(Clint.AccountBalance);

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

	string ReadAccountNumber() {

		string AccountNumber;
		cout << "please enter AccountNumber? : ";
		cin >> AccountNumber;
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

	void AddClient() {

		cout << "Adding New Client\n\n";

		sClint client;
		client = ReadClint();

		AddLinesToFiles(ClientsFile, ConvertRecordToLine(client));

	}

	void PrintOwnClint(sClint clint) {

		cout << "| " << setw(15) << left << clint.AccountNumber;
		cout << "| " << setw(10) << left << clint.PinCode;
		cout << "| " << setw(40) << left << clint.Name;
		cout << "| " << setw(12) << left << clint.phone;
		cout << "| " << setw(12) << left << clint.AccountBalance;

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

	void BackToMain() {

		cout << "\nPress any key to go back to Main Menue...";
		system("pause>0");
		system("cls");
		MainMenueScreen();

	}

	void ShowClientListScrren()
	{
		vector <sClint> vClint = LoadFileContentToVector(ClientsFile);

		PrintClintsList(vClint);
		BackToMain();

	}

	void ShowAddNewClientScrren()
	{

		cout << "-----------------------------------\n";
		cout << "\t Add New Client Screen \n";
		cout << "-----------------------------------\n";
		AddMoreClients();
		BackToMain();

	}

	void ShowDeleteClientScrren()
	{
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
		case enMainMenue::LogOut:
			system("cls");
			ShowExitScrren();
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
		cout << "\t[7] LogOut. \n";
		cout << "===============================================\n";

		PerformMainMenue(enMainMenue(ReadMianMenue()));
	}

}