#include <iostream>
#include <string>
#include <ctime>
#include <direct.h>
#include <io.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

#define MaxAccountQuality 1001
#define MaxFolderAccountQuality 100

using namespace std;
namespace fs = std::filesystem;


void ShowMenu()
{
	cout << "1.����û�" << endl;
	cout << "2.ɾ���û�" << endl;
	cout << "3.��ʾ�û�" << endl;
	cout << "4.�����û�" << endl;
	cout << "5.�޸��û�����" << endl;
	cout << "6.��ʽ�����ݿ�" << endl;
	cout << "0.�˳����ݿ�" << endl;
}

struct User
{
	int AccountID;
	string AccountName;
	string AccountPassword;
	string EmailAddress;
	string RegisterTime;
	bool LoginAccountSafetyCheck;
};

struct DataLib
{
	struct User Account[MaxAccountQuality];
	int UserID;
};

tm* GetTime()
{
	time_t nowtime;
	time(&nowtime); //��ȡ1970��1��1��0��0��0�뵽���ھ���������
	tm* NowTime = localtime(&nowtime); //������ת��Ϊ����ʱ��,���1900����,��Ҫ+1900,��Ϊ0-11,����Ҫ+1
	return NowTime;
}

void CheckDataLibFolder()
{
	string DataLibFolderPosition = "./DataLib";
	if (_access(DataLibFolderPosition.c_str(), 0) == -1)
	{
		cout << "���ݿⲻ���ڣ�������..." << endl;
		int datalibfolderposition = _mkdir(DataLibFolderPosition.c_str());
		cout << "������ɣ�" << endl;
	}
	else {
		cout << "�ļ��д���" << endl;
	}
	system("cls");
}

void CheckAccountInformationFile()
{
	int FolderQuality = MaxAccountQuality / MaxFolderAccountQuality;
	int TheRestQuality = MaxAccountQuality % MaxFolderAccountQuality;
	int BeginQuality = 0;
	int EndQuality = 0;
	int LastEndQuality = 0;

	for (int Folder = 0; Folder < FolderQuality; Folder++)
	{
		BeginQuality = (Folder*MaxFolderAccountQuality) + 1;
		EndQuality = BeginQuality + (MaxFolderAccountQuality - 1);
		string FolderPosition = "./DataLib/" + to_string(BeginQuality) + "-" + to_string(EndQuality);
		if (_access(FolderPosition.c_str(), 0) == -1)
		{
			cout << "�ļ��в����ڣ�������..." << endl;
			int folderposition = _mkdir(FolderPosition.c_str());
			cout << "������ɣ�" << endl;
		}
		else {
			cout << "�ļ��д���" << endl;
		}
		if (Folder == FolderQuality)
		{
			LastEndQuality = EndQuality + TheRestQuality;
			string FolderPosition = "./DataLib/" + to_string(BeginQuality) + "-" + to_string(LastEndQuality);
			if (_access(FolderPosition.c_str(), 0) == -1)
			{
				cout << "�ļ��в����ڣ�������..." << endl;
				int folderposition = _mkdir(FolderPosition.c_str());
				cout << "������ɣ�" << endl;
			}
			else {
				cout << "�ļ��д���" << endl;
			}
		}
	}
	system("cls");
}

int ReadDataLib(DataLib *DL)
{
	int FolderQuality = MaxAccountQuality / MaxFolderAccountQuality;
	int TheRestQuality = MaxAccountQuality % MaxFolderAccountQuality;
	int BeginQuality = 0;
	int EndQuality = 0;
	int LastEndQuality = 0;

	int AccountQuality = 1;

	for (int Folder = 0; Folder < FolderQuality; Folder++)
	{
		BeginQuality = (Folder * MaxFolderAccountQuality) + 1;
		EndQuality = BeginQuality + (MaxFolderAccountQuality - 1);
		if (Folder != FolderQuality)
		{
			string CD = "cd ./DataLib/" + to_string(BeginQuality) + "-" + to_string(EndQuality);
			for (int Check = BeginQuality; Check <= EndQuality; Check++)
			{
				ifstream ReadAccountJson("./DataLib/" + to_string(BeginQuality) + "-" + to_string(EndQuality) + "/" + to_string(Check) + ".json");
				if (!ReadAccountJson.is_open())
				{
					cout << "û�и��û���" << endl;
				}
				else {
					cout << "��ȡ�ļ���..." << endl;
					// ��ȡJSON�ļ����ַ���
					std::string json_str((std::istreambuf_iterator<char>(ReadAccountJson)), std::istreambuf_iterator<char>());
					// ����JSON�ַ���
					nlohmann::json j = nlohmann::json::parse(json_str, nullptr, false);
					
					DL->Account[Check].AccountID = j["ID"];
					DL->Account[Check].AccountName = j["Name"];
					DL->Account[Check].EmailAddress = j["EmailAddress"];
					DL->Account[Check].AccountPassword = j["Password"];
					DL->Account[Check].RegisterTime = j["Register"];
					DL->Account[Check].LoginAccountSafetyCheck = j["SafetyCheck"];
					AccountQuality++;
					cout << "��ȡ��ɣ�" << endl;
				}
			}
		}
		else {
			LastEndQuality = EndQuality + TheRestQuality;
			string CD = "cd ./DataLib/" + to_string(BeginQuality) + "-" + to_string(LastEndQuality);
			for (int Check = BeginQuality; Check <= LastEndQuality; Check++)
			{
				ifstream ReadAccountJson("./DataLib/" + to_string(BeginQuality) + "-" + to_string(EndQuality) + "/" + to_string(Check) + ".json");
				if (!ReadAccountJson.is_open())
				{
					cout << "û�и��û���" << endl;
				}
				else {
					cout << "��ȡ�ļ���..." << endl;
					// ��ȡJSON�ļ����ַ���
					std::string json_str((std::istreambuf_iterator<char>(ReadAccountJson)), std::istreambuf_iterator<char>());
					// ����JSON�ַ���
					nlohmann::json j = nlohmann::json::parse(json_str, nullptr, false);

					DL->Account[Check].AccountID = j["ID"];
					DL->Account[Check].AccountName = j["Name"];
					DL->Account[Check].EmailAddress = j["EmailAddress"];
					DL->Account[Check].AccountPassword = j["Password"];
					DL->Account[Check].RegisterTime = j["Register"];
					DL->Account[Check].LoginAccountSafetyCheck = j["SafetyCheck"];
					AccountQuality++;
					cout << "��ȡ��ɣ�" << endl;
				}
			}
		}
	}
	system("cls");
	return AccountQuality;
}

void AddAccount(DataLib * DL)
{
	system("cls");
	if (DL->UserID == 0)
	{
		DL->UserID++;
	}
	if (DL->UserID == MaxAccountQuality)
	{
		cout << "�û������Ѵ����ޣ��޷���ӣ�" << endl;
		return;
	}

	string Name;
	string Password, Password_Again;
	string Email;

	cout << "�������û�����" << endl;
	cin >> Name;
	int Check = 1;
	while (Check != MaxAccountQuality)
	{
		if (DL->Account[Check].AccountID == 0)
		{
			break;
		}
		if (Name == DL->Account[Check].AccountName)
		{
			cout << "�˺������ظ�������������" << endl;
			cin >> Name;
			Check = 1;
		}
		else {
			Check++;
		}
	}

	cout << "���������룺" << endl;
	cin >> Password;
	while (true)
	{
		cout << "�ٴ�����������ȷ�ϣ�" << endl;
		cin >> Password_Again;
		if (Password_Again == Password)
		{
			break;
		}
		cout << "��������Ĳ�һ�£����������룺" << endl;
	}

	cout << "���������䣺" << endl;
	cin >> Email;
	Check = 1;
	while (Check != MaxAccountQuality)
	{
		if (DL->Account[Check].AccountID == 0)
		{
			break;
		}
		if (Email == DL->Account[Check].EmailAddress)
		{
			cout << "�˺������ظ�������������" << endl;
			cin >> Email;
			Check = 1;
		}
		else {
			Check++;
		}
	}

	string RegisterTime;
	tm* RTime = GetTime();
	RegisterTime = to_string(RTime->tm_year + 1900) + "-" + to_string(RTime->tm_mon + 1) + "-" + to_string(RTime->tm_mday) + "-" + to_string(RTime->tm_hour) + ":" + to_string(RTime->tm_min) + ":" + to_string(RTime->tm_sec);

	DL->Account[DL->UserID].AccountName = Name;
	DL->Account[DL->UserID].AccountPassword = Password_Again;
	DL->Account[DL->UserID].EmailAddress = Email;
	DL->Account[DL->UserID].AccountID = DL->UserID;
	DL->Account[DL->UserID].LoginAccountSafetyCheck = true;
	DL->Account[DL->UserID].RegisterTime = RegisterTime;

	nlohmann::json j;
	j["ID"] = DL->Account[DL->UserID].AccountID;
	j["Name"] = DL->Account[DL->UserID].AccountName;
	j["EmailAddress"] = DL->Account[DL->UserID].EmailAddress;
	j["Password"] = DL->Account[DL->UserID].AccountPassword;
	j["Register"] = DL->Account[DL->UserID].RegisterTime;
	j["SafetyCheck"] = DL->Account[DL->UserID].LoginAccountSafetyCheck;
	int BeginFolderPosition = DL->UserID / MaxFolderAccountQuality;
	int EndFolderPosition = DL->UserID % MaxFolderAccountQuality;
	int BeginFilePosition = (BeginFolderPosition * MaxFolderAccountQuality) + 1;
	int EndFilePosition = BeginFilePosition + (MaxFolderAccountQuality - 1);

	string FolderPosition = "./DataLib/" + to_string(BeginFilePosition) + "-" + to_string(EndFilePosition) + "/";
	
	string JsonFileName = FolderPosition + to_string(DL->UserID) + ".json";
	ofstream UserJsonFile(JsonFileName);
	UserJsonFile << j.dump(4);
	if (UserJsonFile.good())
	{
		cout << "�û�json�ļ������ɹ���" << endl;
	}
	else {
		cout << "�û�json�ļ�����ʧ�ܣ�" << endl;
	}


	cout << "�����ɣ�" << endl;
	system("pause");
	system("cls");
}

void DeleteAccount(DataLib *DL)
{
	int SelectAccountID = 0;
	string Password;
	cout << "������Ҫɾ�����û���ID��" << endl;
	cin >> SelectAccountID;
	while (true)
	{
		if (0 < SelectAccountID < MaxAccountQuality)
		{
			if (DL->Account[SelectAccountID].AccountID == 0)
			{
				cout << "�û������ڣ�����������!" << endl;
				cout << "������Ҫɾ�����û���ID��" << endl;
				cin >> SelectAccountID;
			}
			else {
				break;
			}
		}
	}	

	while (true)
	{
		cout << "����������ȷ�ϣ�" << endl;
		cin >> Password;
		if (Password == DL->Account[SelectAccountID].AccountPassword)
		{
			break;
		}
		cout << "����������������룡" << endl;
	}

	bool Ensure = true;

	do
	{
		cout << "ȷ��ɾ������0ͬ�⣬����1��ͬ�⣩" << endl;
		cin >> Ensure;
		if (Ensure == false)
		{
			break;
		}
		else {
			system("cls");
			return;
		}
	} while (true);

	cout << "ɾ����..." << endl;
	DL->Account[SelectAccountID].AccountID = 0;

	int BeginFolderPosition = DL->UserID / MaxFolderAccountQuality;
	int EndFolderPosition = DL->UserID % MaxFolderAccountQuality;
	int BeginFilePosition = (BeginFolderPosition * MaxFolderAccountQuality) + 1;
	int EndFilePosition = BeginFilePosition + (MaxFolderAccountQuality - 1);

	string FolderPosition = "./DataLib/" + to_string(BeginFilePosition) + "-" + to_string(EndFilePosition) + "/" + to_string(SelectAccountID) + ".json";

	// ɾ���ļ�
	try {
		// ����ļ��Ƿ����
		if (fs::exists(FolderPosition)) {
			// ɾ���ļ�
			fs::remove(FolderPosition);
			std::cout << "�ļ���ɾ��" << std::endl;
			cout << "ɾ����ɣ�" << endl;
		}
		else {
			std::cout << "�ļ�������" << std::endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "����: " << e.what() << std::endl;
	}
	system("pause");
	system("cls");
}

void ExhibitAccount(DataLib *DL)
{
	system("cls");
	int AccountQuality = 0;
	for (int Check = 1; Check < MaxAccountQuality; Check++)
	{
		if (AccountQuality == DL->UserID - 1)
		{
			system("pause");
			system("cls");
			return;
		}
		if (DL->Account[Check].AccountID == 0)
		{
			continue;
		}
		else {
			cout << to_string(Check) + "." + DL->Account[Check].AccountName << endl;
			AccountQuality++;
		}
	}
}

void UseIDFind(DataLib* DL, int id)
{
	while (true)
	{
		cout << "�����û�ID:" << endl;
		cin >> id;
		if (0 < id < MaxAccountQuality)
		{
			if (DL->Account[id].AccountID != 0)
			{
				break;
			}
		}
		cout << "�û������ڣ����������룡" << endl;
	}
	system("cls");
	cout << "�û�����" << DL->Account[id].AccountName << endl;
	cout << "�û�ID��" << DL->Account[id].AccountID << endl;
	cout << "���䣺" << DL->Account[id].EmailAddress << endl;
	cout << "ע��ʱ�䣺" << DL->Account[id].RegisterTime << endl;
	system("pause");
}

void UseNameFind(DataLib* DL, string name)
{
	int id = 0;
	while (true)
	{
		cout << "�����û���:" << endl;
		cin >> name;
		for (int Check = 1; Check < MaxAccountQuality; Check++)
		{
			if (name == DL->Account[Check].AccountName)
			{
				id = DL->Account[Check].AccountID;
				break;
			}
		}
		if (DL->Account[id].AccountID != 0)
		{
			break;
		}
		cout << "�û������ڣ����������룡" << endl;
	}
	system("cls");
	cout << "�û�����" << DL->Account[id].AccountName << endl;
	cout << "�û�ID��" << DL->Account[id].AccountID << endl;
	cout << "���䣺" << DL->Account[id].EmailAddress << endl;
	cout << "ע��ʱ�䣺" << DL->Account[id].RegisterTime << endl;
	system("pause");
}

void FindAccount(DataLib* DL)
{
	system("cls");
	int ID = 0;
	string Name;
	cout << "1.ID��ѯ" << endl;
	cout << "2.�û�����ѯ" << endl;
	cout << "0.����" << endl;
	int SeletchFindWay = 0;
	while (true)
	{
		cin >> SeletchFindWay;
		switch (SeletchFindWay)
		{
		case 1:UseIDFind(DL, ID);
			return;
		case 2:UseNameFind(DL, Name);
			return;
		case 0:
			system("pause");
			system("cls");
			return;
		default:
			break;
		}
	}
}

void CorrectAccountName(DataLib* DL, string name, int id,string path)
{
	cout << "������Ҫ���ĵ��û�����" << endl;
	cin >> name;
	for (int Check = 1; Check <= MaxAccountQuality; Check++)
	{
		if (name == DL->Account[id].AccountName)
		{
			cout << "�뵱ǰʹ���˻����ظ���" << endl;
			cout << "������Ҫ���ĵ��û�����" << endl;
			cin >> name;
			Check = 1;
		}
		if (name == DL->Account[Check].AccountName)
		{
			cout << "���û����ѱ�ʹ��" << endl;
			cout << "������Ҫ���ĵ��û�����" << endl;
			cin >> name;
			Check = 1;
		}
	}
	DL->Account[id].AccountName = name;

	std::ifstream i(path);
	nlohmann::json j;
	i >> j;

	// �޸�JSONԪ�ص�ֵ
	j["Name"] = DL->Account[id].AccountName;

	// �����ĺ��JSON����д���ļ�
	std::ofstream o(path);
	o << j.dump(4); // 4���������������������

	cout << "�޸���ɣ�" << endl;
}

void CorrectAccountPassword(DataLib* DL, string password, string password_again, int id,string path)
{
	string pwd;

	while (true)
	{
		cout << "�����뵱ǰ���룺" << endl;
		cin >> pwd;
		if (pwd == DL->Account[id].AccountPassword)
		{
			break;
		}
		cout << "�������" << endl;
	}

	cout << "������Ҫ�޸ĵ����룺" << endl;
	cin >> password;
	while (true)
	{
		cout << "�ٴ�������ȷ��:" << endl;
		cin >> password_again;
		if (password_again == password)
		{
			break;
		}
		cout << "��������Ĳ�һ�£�" << endl;
	}
	DL->Account[id].AccountPassword = password_again;

	std::ifstream i(path);
	nlohmann::json j;
	i >> j;

	// �޸�JSONԪ�ص�ֵ
	j["Password"] = DL->Account[id].AccountPassword;

	// �����ĺ��JSON����д���ļ�
	std::ofstream o(path);
	o << j.dump(4); // 4���������������������

	cout << "�޸���ɣ�" << endl;
}

void CorrectEmailAddress(DataLib* DL, string email, int id,string path)
{
	cout << "������Ҫ���ĵ����䣺" << endl;
	cin >> email;
	for (int Check = 1; Check <= MaxAccountQuality; Check++)
	{
		if (email == DL->Account[id].EmailAddress)
		{
			cout << "�뵱ǰ�������ظ���" << endl;
			cout << "������Ҫ���ĵ����䣺" << endl;
			cin >> email;
			Check = 1;
		}
		if (email == DL->Account[Check].EmailAddress)
		{
			cout << "�������Ѱ�" << endl;
			cout << "������Ҫ���ĵ����䣺" << endl;
			cin >> email;
			Check = 1;
		}
	}
	DL->Account[id].EmailAddress = email;

	std::ifstream i(path);
	nlohmann::json j;
	i >> j;

	// �޸�JSONԪ�ص�ֵ
	j["EmailAddress"] = DL->Account[id].EmailAddress;

	// �����ĺ��JSON����д���ļ�
	std::ofstream o(path);
	o << j.dump(4); // 4���������������������

	cout << "�޸���ɣ�" << endl;
}

void CorrectSafetyCheck(DataLib *DL, bool safetycheck, int id,string path)
{
	bool Select = true;

	do
	{
		cout << "�������ǹرգ���0�رգ�����1Ϊ����" << endl;
		cin >> Select;
		if (Select == false)
		{
			if (DL->Account[id].LoginAccountSafetyCheck != false)
			{
				DL->Account[id].LoginAccountSafetyCheck = false;
				cout << "�رճɹ���" << endl;

				std::ifstream i(path);
				nlohmann::json j;
				i >> j;

				// �޸�JSONԪ�ص�ֵ
				j["SafetyCheck"] = DL->Account[id].LoginAccountSafetyCheck;

				// �����ĺ��JSON����д���ļ�
				std::ofstream o(path);
				o << j.dump(4); // 4���������������������

				break;
			}
			cout << "�Ѿ��رգ�" << endl;
		}
		else {
			if (DL->Account[id].LoginAccountSafetyCheck != true)
			{
				DL->Account[id].LoginAccountSafetyCheck = true;

				std::ifstream i(path);
				nlohmann::json j;
				i >> j;

				// �޸�JSONԪ�ص�ֵ
				j["SafetyCheck"] = DL->Account[id].LoginAccountSafetyCheck;

				// �����ĺ��JSON����д���ļ�
				std::ofstream o(path);
				o << j.dump(4); // 4���������������������

				cout << "�����ɹ���" << endl;
				break;
			}
			cout << "�Ѿ�������" << endl;
		}
	} while (true);
}

void CorrectAccountInformation(DataLib* DL)
{
	system("cls");
	string Name;
	string Password, Password_Again;
	string Email;
	bool SafetyCheck = true;

	int ID = 0;
	while (true)
	{
		cout << "����Ҫ�޸ĵ��û�ID:" << endl;
		cin >> ID;
		if (0 < ID < MaxAccountQuality)
		{
			if (DL->Account[ID].AccountID != 0)
			{
				break;
			}
		}
		cout << "�û������ڣ����������룡" << endl;
	}

	int BeginFolderPosition = DL->Account[ID].AccountID / MaxFolderAccountQuality;
	int EndFolderPosition = DL->Account[ID].AccountID % MaxFolderAccountQuality;
	int BeginFilePosition = (BeginFolderPosition * MaxFolderAccountQuality) + 1;
	int EndFilePosition = BeginFilePosition + (MaxFolderAccountQuality - 1);

	string AccountJsonPosition = "./DataLib/" + to_string(BeginFilePosition) + "-" + to_string(EndFilePosition) + "/" + to_string(ID) + ".json";


	system("cls");
	cout << "1.�޸��û���" << endl;
	cout << "2.�޸�����" << endl;
	cout << "3.�޸�����" << endl;
	cout << "4.�޸İ�ȫ����" << endl;
	cout << "0.����" << endl;

	int SelectCorrectType;
	while (true)
	{
		cin >> SelectCorrectType;
		switch (SelectCorrectType)
		{
		case 1:CorrectAccountName(DL, Name, ID, AccountJsonPosition);
			return;
		case 2:CorrectAccountPassword(DL, Password, Password_Again, ID, AccountJsonPosition);
			return;
		case 3:CorrectEmailAddress(DL, Email, ID, AccountJsonPosition);
			return;
		case 4:CorrectSafetyCheck(DL, SafetyCheck, ID, AccountJsonPosition);
			return;
		case 0:
			system("pause");
			system("cls");
			return;
		default:
			break;
		}
	}
}

void removeDirectory(const fs::path& dirPath,DataLib *DL) {
	int AccountQuality = ReadDataLib(DL);
	int Quality = 0;
	try {
		if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
			fs::remove_all(dirPath);
			for (int Check = 1; Check < MaxAccountQuality; Check++)
			{
				if (Quality == AccountQuality - 1)
				{
					break;
				}
				else {
					if (DL->Account[Check].AccountID != 0)
					{
						cout << "����˺ţ�" + to_string(DL->Account[Check].AccountID) + "." + DL->Account[Check].AccountName << endl;
						DL->Account[Check].AccountID = 0;
					}
				}
			}
			std::cout << "Directory removed successfully." << std::endl;
			cout << "����ɾ����·����" << endl;
		}
		else {
			std::cout << "Directory does not exist." << std::endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void DeleteDataLib(DataLib* DL)
{
	system("cls");
	bool Ensure = true;

	do
	{
		cout << "ȷ��ɾ������0ͬ�⣬����1��ͬ�⣩" << endl;
		cin >> Ensure;
		if (Ensure == false)
		{
			break;
		}
		else {
			system("cls");
			return;
		}
	} while (true);
	cout << "ɾ����..." << endl;
	removeDirectory("./DataLib", DL);
	system("pause");
	system("cls");
}


int main()
{
	DataLib DL;
	DL.UserID = 1;

	int Quality = ReadDataLib(&DL);
	DL.UserID = Quality;



	int SelectFunction = 0;
	while (true)
	{
		CheckDataLibFolder();
		CheckAccountInformationFile();
		int Quality = ReadDataLib(&DL);
		DL.UserID = Quality;
		ShowMenu();
		cin >> SelectFunction;
		switch (SelectFunction)
		{
		case 1:AddAccount(&DL);
			break;
		case 2:DeleteAccount(&DL);
			break;
		case 3:ExhibitAccount(&DL);
			break;
		case 4:FindAccount(&DL);
			break;
		case 5:CorrectAccountInformation(&DL);
			break;
		case 6:DeleteDataLib(&DL);
			break;
		case 0:cout << "��ӭ�ٴ�ʹ�ã�" << endl;
			system("pause");
			return 0;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}