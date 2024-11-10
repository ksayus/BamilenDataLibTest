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
	cout << "1.添加用户" << endl;
	cout << "2.删除用户" << endl;
	cout << "3.显示用户" << endl;
	cout << "4.查找用户" << endl;
	cout << "5.修改用户数据" << endl;
	cout << "6.格式化数据库" << endl;
	cout << "0.退出数据库" << endl;
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
	time(&nowtime); //获取1970年1月1日0点0分0秒到现在经过的秒数
	tm* NowTime = localtime(&nowtime); //将秒数转换为本地时间,年从1900算起,需要+1900,月为0-11,所以要+1
	return NowTime;
}

void CheckDataLibFolder()
{
	string DataLibFolderPosition = "./DataLib";
	if (_access(DataLibFolderPosition.c_str(), 0) == -1)
	{
		cout << "数据库不存在，创建中..." << endl;
		int datalibfolderposition = _mkdir(DataLibFolderPosition.c_str());
		cout << "创建完成！" << endl;
	}
	else {
		cout << "文件夹存在" << endl;
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
			cout << "文件夹不存在，创建中..." << endl;
			int folderposition = _mkdir(FolderPosition.c_str());
			cout << "创建完成！" << endl;
		}
		else {
			cout << "文件夹存在" << endl;
		}
		if (Folder == FolderQuality)
		{
			LastEndQuality = EndQuality + TheRestQuality;
			string FolderPosition = "./DataLib/" + to_string(BeginQuality) + "-" + to_string(LastEndQuality);
			if (_access(FolderPosition.c_str(), 0) == -1)
			{
				cout << "文件夹不存在，创建中..." << endl;
				int folderposition = _mkdir(FolderPosition.c_str());
				cout << "创建完成！" << endl;
			}
			else {
				cout << "文件夹存在" << endl;
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
					cout << "没有该用户。" << endl;
				}
				else {
					cout << "读取文件中..." << endl;
					// 读取JSON文件到字符串
					std::string json_str((std::istreambuf_iterator<char>(ReadAccountJson)), std::istreambuf_iterator<char>());
					// 解析JSON字符串
					nlohmann::json j = nlohmann::json::parse(json_str, nullptr, false);
					
					DL->Account[Check].AccountID = j["ID"];
					DL->Account[Check].AccountName = j["Name"];
					DL->Account[Check].EmailAddress = j["EmailAddress"];
					DL->Account[Check].AccountPassword = j["Password"];
					DL->Account[Check].RegisterTime = j["Register"];
					DL->Account[Check].LoginAccountSafetyCheck = j["SafetyCheck"];
					AccountQuality++;
					cout << "读取完成！" << endl;
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
					cout << "没有该用户。" << endl;
				}
				else {
					cout << "读取文件中..." << endl;
					// 读取JSON文件到字符串
					std::string json_str((std::istreambuf_iterator<char>(ReadAccountJson)), std::istreambuf_iterator<char>());
					// 解析JSON字符串
					nlohmann::json j = nlohmann::json::parse(json_str, nullptr, false);

					DL->Account[Check].AccountID = j["ID"];
					DL->Account[Check].AccountName = j["Name"];
					DL->Account[Check].EmailAddress = j["EmailAddress"];
					DL->Account[Check].AccountPassword = j["Password"];
					DL->Account[Check].RegisterTime = j["Register"];
					DL->Account[Check].LoginAccountSafetyCheck = j["SafetyCheck"];
					AccountQuality++;
					cout << "读取完成！" << endl;
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
		cout << "用户数量已达上限，无法添加！" << endl;
		return;
	}

	string Name;
	string Password, Password_Again;
	string Email;

	cout << "请输入用户名：" << endl;
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
			cout << "账号邮箱重复，请重新输入" << endl;
			cin >> Name;
			Check = 1;
		}
		else {
			Check++;
		}
	}

	cout << "请输入密码：" << endl;
	cin >> Password;
	while (true)
	{
		cout << "再次输入密码以确认：" << endl;
		cin >> Password_Again;
		if (Password_Again == Password)
		{
			break;
		}
		cout << "两次输入的不一致，请重新输入：" << endl;
	}

	cout << "请输入邮箱：" << endl;
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
			cout << "账号邮箱重复，请重新输入" << endl;
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
		cout << "用户json文件创建成功！" << endl;
	}
	else {
		cout << "用户json文件创建失败！" << endl;
	}


	cout << "添加完成！" << endl;
	system("pause");
	system("cls");
}

void DeleteAccount(DataLib *DL)
{
	int SelectAccountID = 0;
	string Password;
	cout << "输入你要删除的用户的ID：" << endl;
	cin >> SelectAccountID;
	while (true)
	{
		if (0 < SelectAccountID < MaxAccountQuality)
		{
			if (DL->Account[SelectAccountID].AccountID == 0)
			{
				cout << "用户不存在，请重新输入!" << endl;
				cout << "输入你要删除的用户的ID：" << endl;
				cin >> SelectAccountID;
			}
			else {
				break;
			}
		}
	}	

	while (true)
	{
		cout << "输入密码以确认：" << endl;
		cin >> Password;
		if (Password == DL->Account[SelectAccountID].AccountPassword)
		{
			break;
		}
		cout << "密码错误，请重新输入！" << endl;
	}

	bool Ensure = true;

	do
	{
		cout << "确认删除？（0同意，大于1不同意）" << endl;
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

	cout << "删除中..." << endl;
	DL->Account[SelectAccountID].AccountID = 0;

	int BeginFolderPosition = DL->UserID / MaxFolderAccountQuality;
	int EndFolderPosition = DL->UserID % MaxFolderAccountQuality;
	int BeginFilePosition = (BeginFolderPosition * MaxFolderAccountQuality) + 1;
	int EndFilePosition = BeginFilePosition + (MaxFolderAccountQuality - 1);

	string FolderPosition = "./DataLib/" + to_string(BeginFilePosition) + "-" + to_string(EndFilePosition) + "/" + to_string(SelectAccountID) + ".json";

	// 删除文件
	try {
		// 检查文件是否存在
		if (fs::exists(FolderPosition)) {
			// 删除文件
			fs::remove(FolderPosition);
			std::cout << "文件已删除" << std::endl;
			cout << "删除完成！" << endl;
		}
		else {
			std::cout << "文件不存在" << std::endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "错误: " << e.what() << std::endl;
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
		cout << "输入用户ID:" << endl;
		cin >> id;
		if (0 < id < MaxAccountQuality)
		{
			if (DL->Account[id].AccountID != 0)
			{
				break;
			}
		}
		cout << "用户不存在，请重新输入！" << endl;
	}
	system("cls");
	cout << "用户名：" << DL->Account[id].AccountName << endl;
	cout << "用户ID：" << DL->Account[id].AccountID << endl;
	cout << "邮箱：" << DL->Account[id].EmailAddress << endl;
	cout << "注册时间：" << DL->Account[id].RegisterTime << endl;
	system("pause");
}

void UseNameFind(DataLib* DL, string name)
{
	int id = 0;
	while (true)
	{
		cout << "输入用户名:" << endl;
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
		cout << "用户不存在，请重新输入！" << endl;
	}
	system("cls");
	cout << "用户名：" << DL->Account[id].AccountName << endl;
	cout << "用户ID：" << DL->Account[id].AccountID << endl;
	cout << "邮箱：" << DL->Account[id].EmailAddress << endl;
	cout << "注册时间：" << DL->Account[id].RegisterTime << endl;
	system("pause");
}

void FindAccount(DataLib* DL)
{
	system("cls");
	int ID = 0;
	string Name;
	cout << "1.ID查询" << endl;
	cout << "2.用户名查询" << endl;
	cout << "0.返回" << endl;
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
	cout << "请输入要更改的用户名：" << endl;
	cin >> name;
	for (int Check = 1; Check <= MaxAccountQuality; Check++)
	{
		if (name == DL->Account[id].AccountName)
		{
			cout << "与当前使用账户名重复。" << endl;
			cout << "请输入要更改的用户名：" << endl;
			cin >> name;
			Check = 1;
		}
		if (name == DL->Account[Check].AccountName)
		{
			cout << "此用户名已被使用" << endl;
			cout << "请输入要更改的用户名：" << endl;
			cin >> name;
			Check = 1;
		}
	}
	DL->Account[id].AccountName = name;

	std::ifstream i(path);
	nlohmann::json j;
	i >> j;

	// 修改JSON元素的值
	j["Name"] = DL->Account[id].AccountName;

	// 将更改后的JSON数据写回文件
	std::ofstream o(path);
	o << j.dump(4); // 4是缩进级别，用于美化输出

	cout << "修改完成！" << endl;
}

void CorrectAccountPassword(DataLib* DL, string password, string password_again, int id,string path)
{
	string pwd;

	while (true)
	{
		cout << "请输入当前密码：" << endl;
		cin >> pwd;
		if (pwd == DL->Account[id].AccountPassword)
		{
			break;
		}
		cout << "密码错误！" << endl;
	}

	cout << "请输入要修改的密码：" << endl;
	cin >> password;
	while (true)
	{
		cout << "再次输入以确认:" << endl;
		cin >> password_again;
		if (password_again == password)
		{
			break;
		}
		cout << "两次输入的不一致！" << endl;
	}
	DL->Account[id].AccountPassword = password_again;

	std::ifstream i(path);
	nlohmann::json j;
	i >> j;

	// 修改JSON元素的值
	j["Password"] = DL->Account[id].AccountPassword;

	// 将更改后的JSON数据写回文件
	std::ofstream o(path);
	o << j.dump(4); // 4是缩进级别，用于美化输出

	cout << "修改完成！" << endl;
}

void CorrectEmailAddress(DataLib* DL, string email, int id,string path)
{
	cout << "请输入要更改的邮箱：" << endl;
	cin >> email;
	for (int Check = 1; Check <= MaxAccountQuality; Check++)
	{
		if (email == DL->Account[id].EmailAddress)
		{
			cout << "与当前绑定邮箱重复。" << endl;
			cout << "请输入要更改的邮箱：" << endl;
			cin >> email;
			Check = 1;
		}
		if (email == DL->Account[Check].EmailAddress)
		{
			cout << "此邮箱已绑定" << endl;
			cout << "请输入要更改的邮箱：" << endl;
			cin >> email;
			Check = 1;
		}
	}
	DL->Account[id].EmailAddress = email;

	std::ifstream i(path);
	nlohmann::json j;
	i >> j;

	// 修改JSON元素的值
	j["EmailAddress"] = DL->Account[id].EmailAddress;

	// 将更改后的JSON数据写回文件
	std::ofstream o(path);
	o << j.dump(4); // 4是缩进级别，用于美化输出

	cout << "修改完成！" << endl;
}

void CorrectSafetyCheck(DataLib *DL, bool safetycheck, int id,string path)
{
	bool Select = true;

	do
	{
		cout << "开启还是关闭？（0关闭，大于1为开）" << endl;
		cin >> Select;
		if (Select == false)
		{
			if (DL->Account[id].LoginAccountSafetyCheck != false)
			{
				DL->Account[id].LoginAccountSafetyCheck = false;
				cout << "关闭成功！" << endl;

				std::ifstream i(path);
				nlohmann::json j;
				i >> j;

				// 修改JSON元素的值
				j["SafetyCheck"] = DL->Account[id].LoginAccountSafetyCheck;

				// 将更改后的JSON数据写回文件
				std::ofstream o(path);
				o << j.dump(4); // 4是缩进级别，用于美化输出

				break;
			}
			cout << "已经关闭！" << endl;
		}
		else {
			if (DL->Account[id].LoginAccountSafetyCheck != true)
			{
				DL->Account[id].LoginAccountSafetyCheck = true;

				std::ifstream i(path);
				nlohmann::json j;
				i >> j;

				// 修改JSON元素的值
				j["SafetyCheck"] = DL->Account[id].LoginAccountSafetyCheck;

				// 将更改后的JSON数据写回文件
				std::ofstream o(path);
				o << j.dump(4); // 4是缩进级别，用于美化输出

				cout << "开启成功！" << endl;
				break;
			}
			cout << "已经开启！" << endl;
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
		cout << "输入要修改的用户ID:" << endl;
		cin >> ID;
		if (0 < ID < MaxAccountQuality)
		{
			if (DL->Account[ID].AccountID != 0)
			{
				break;
			}
		}
		cout << "用户不存在，请重新输入！" << endl;
	}

	int BeginFolderPosition = DL->Account[ID].AccountID / MaxFolderAccountQuality;
	int EndFolderPosition = DL->Account[ID].AccountID % MaxFolderAccountQuality;
	int BeginFilePosition = (BeginFolderPosition * MaxFolderAccountQuality) + 1;
	int EndFilePosition = BeginFilePosition + (MaxFolderAccountQuality - 1);

	string AccountJsonPosition = "./DataLib/" + to_string(BeginFilePosition) + "-" + to_string(EndFilePosition) + "/" + to_string(ID) + ".json";


	system("cls");
	cout << "1.修改用户名" << endl;
	cout << "2.修改密码" << endl;
	cout << "3.修改邮箱" << endl;
	cout << "4.修改安全设置" << endl;
	cout << "0.返回" << endl;

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
						cout << "清除账号：" + to_string(DL->Account[Check].AccountID) + "." + DL->Account[Check].AccountName << endl;
						DL->Account[Check].AccountID = 0;
					}
				}
			}
			std::cout << "Directory removed successfully." << std::endl;
			cout << "老子删库跑路咯！" << endl;
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
		cout << "确认删除？（0同意，大于1不同意）" << endl;
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
	cout << "删除中..." << endl;
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
		case 0:cout << "欢迎再次使用！" << endl;
			system("pause");
			return 0;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}