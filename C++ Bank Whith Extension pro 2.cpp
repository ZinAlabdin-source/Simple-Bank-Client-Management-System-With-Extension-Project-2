#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <limits>
using namespace std;
const string F_Name = "ZDFile.txt";
const string Separator = "#//#";
struct St_Clients_Info
{
    string Account_Number;
    string Pin_Code;
    string Account_Name;
    string Phone_Number;
    double Account_Balance = 0.0;
    bool Mark_For_Delete = false;
};
enum En_Menue_Option
{
    Show_All_Clients = 1,
    Add_New_Client = 2,
    Delete_Client = 3,
    Update_Client_Info = 4,
    Find_Client = 5,
    Transactions_Menue = 6,
    Exit = 0
};
enum En_Transactions_Menu_Screen
{
    Deposit = 1,
    Withdraw = 2,
    Total_Balance = 3,
    Main_Menue = 0
};
string Read_User_Input(string Message)
{
    string User_Input;
    cout << Message;
    getline(cin >> ws, User_Input);
    return User_Input;
}
string Read_Optional_Input(string Message)
{
    string Op_Input;
    cout << Message;
    getline(cin, Op_Input);
    return Op_Input;
}
double Safe_String_To_Double(const string& Str)
{
    try { return stod(Str); }
    catch (...) { return 0.0; }
}
vector<string> Split_String(string Txt)
{
    vector<string> V_String;
    short Position = 0;
    string Single_Word;
    while ((Position = Txt.find(Separator)) != string::npos)
    {
        Single_Word = Txt.substr(0, Position);
        if (!Single_Word.empty())
            V_String.push_back(Single_Word);
        Txt.erase(0, Position + Separator.length());
    }
    if (!Txt.empty())
        V_String.push_back(Txt);
    return V_String;
}
St_Clients_Info Convert_Line_To_Record(string Line)
{
    St_Clients_Info Client;
    vector<string> V_String = Split_String(Line);
    if (V_String.size() >= 5)
    {
        Client.Account_Number = V_String[0];
        Client.Pin_Code = V_String[1];
        Client.Account_Name = V_String[2];
        Client.Phone_Number = V_String[3];
        Client.Account_Balance = stod(V_String[4]);
    }
    return Client;
}
string Convert_Record_To_Line(St_Clients_Info& Client)
{
    string Line;
    Line += Client.Account_Number + Separator;
    Line += Client.Pin_Code + Separator;
    Line += Client.Account_Name + Separator;
    Line += Client.Phone_Number + Separator;
    Line += to_string(Client.Account_Balance);
    return Line;
}
vector<St_Clients_Info> Load_All_Clients()
{
    vector<St_Clients_Info> V_All_Clients;
    fstream ZDFile;
    ZDFile.open(F_Name, ios::in);
    if (ZDFile.is_open())
    {
        string Line;
        while (getline(ZDFile, Line))
        {
            V_All_Clients.push_back(Convert_Line_To_Record(Line));
        }
        ZDFile.close();
    }
    return V_All_Clients;
}
void Save_All_Clients(vector<St_Clients_Info>& V_All_Clients)
{
    fstream ZDFile;
    ZDFile.open(F_Name, ios::out);
    if (ZDFile.is_open())
    {
        for (St_Clients_Info& C : V_All_Clients)
        {
            if (!C.Mark_For_Delete)
                ZDFile << Convert_Record_To_Line(C) << endl;
        }
        ZDFile.close();
    }
}
void Sort_Clients_By_Account_Number(vector<St_Clients_Info>& V_All_Clients)
{
    for (size_t i = 0; i < V_All_Clients.size(); i++)
    {
        for (size_t j = i + 1; j < V_All_Clients.size(); j++)
        {
            if (V_All_Clients[i].Account_Number > V_All_Clients[j].Account_Number)
            {
                St_Clients_Info Temp = V_All_Clients[i];
                V_All_Clients[i] = V_All_Clients[j];
                V_All_Clients[j] = Temp;
            }
        }
    }
}
bool Find_Client_By_Account_Number(const string& AccNum, vector<St_Clients_Info>& V_All_Clients, St_Clients_Info& Out_Client)
{
    for (St_Clients_Info& C : V_All_Clients)
    {
        if (C.Account_Number == AccNum)
        {
            Out_Client = C;
            return true;
        }
    }
    return false;
}
bool Is_Account_Number_Exist(const string& AccNum, vector<St_Clients_Info>& V_All_Clients)
{
    St_Clients_Info Exist;
    return Find_Client_By_Account_Number(AccNum, V_All_Clients, Exist);
}
void Print_Client_Info_For_Table(St_Clients_Info& Clients_Info)
{
    cout << "| " << left << setw(15) << Clients_Info.Account_Number;
    cout << "| " << left << setw(10) << Clients_Info.Pin_Code;
    cout << "| " << left << setw(25) << Clients_Info.Account_Name;
    cout << "| " << left << setw(15) << Clients_Info.Phone_Number;
    cout << "| " << left << setw(12) << Clients_Info.Account_Balance;
}
void Print_Client_Info_For_Total_Balances_Table(St_Clients_Info& Clients_Info)
{
    cout << "| " << left << setw(15) << Clients_Info.Account_Number;
    cout << "| " << left << setw(25) << Clients_Info.Account_Name;
    cout << "| " << left << setw(12) << Clients_Info.Account_Balance;
}
void Show_All_Clients_Table()
{
    vector<St_Clients_Info> V_All_Clients = Load_All_Clients();
    Sort_Clients_By_Account_Number(V_All_Clients);
    cout << "==========================================================================================\n";
    cout << "\n\t\t\tClient List (" << V_All_Clients.size() << ") Client(s)\n";
    cout << "\n==========================================================================================\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(25) << "Client Name";
    cout << "| " << left << setw(15) << "Phone Number";
    cout << "| " << left << setw(12) << "Balance" << "\n";
    cout << "\n==========================================================================================\n";
    if (V_All_Clients.size() == 0)
    {
        cout << "\n\a\t\t\t!!! No Clients Available In the System !!!\n";
        cout << "\n==========================================================================================\n";
    }
    else
    {
        for (St_Clients_Info& C : V_All_Clients)
        {
            Print_Client_Info_For_Table(C);
            cout << endl;
        }
        cout << "==========================================================================================\n";
    }
}
void Print_Client_Card(const St_Clients_Info& Client)
{
    cout << "\n======================================\n";
    cout << "\n\tClient Details Screen\t\n";
    cout << "\n======================================\n\n";
    cout << left << setw(20) << "Account Number: " << Client.Account_Number << "\n";
    cout << left << setw(20) << "Pin Code: " << Client.Pin_Code << "\n";
    cout << left << setw(20) << "Name: " << Client.Account_Name << "\n";
    cout << left << setw(20) << "Phone: " << Client.Phone_Number << "\n";
    cout << left << setw(20) << "Balance: " << Client.Account_Balance << "\n";
    cout << "\n======================================\n";
}
St_Clients_Info Get_Client_Data_From_User(string AccNum)
{
    St_Clients_Info Client;
    Client.Account_Number = AccNum;
    Client.Pin_Code = Read_User_Input("Enter Pin Code: ");
    Client.Account_Name = Read_User_Input("Enter Name: ");
    Client.Phone_Number = Read_User_Input("Enter Phone Number: ");
    string Str_Account_Balance = Read_User_Input("Enter Account Balance: ");
    Client.Account_Balance = Safe_String_To_Double(Str_Account_Balance);
    return Client;
}
void Add_New_Clients()
{
    char Add_More = 'Y';
    do
    {
        vector<St_Clients_Info> V_All_Clients = Load_All_Clients();
        string AccNum;
        do
        {
            AccNum = Read_User_Input("Enter Account Number: ");
            if (Is_Account_Number_Exist(AccNum, V_All_Clients))
                cout << "\n\aClient With Account Number (" << AccNum << ") Already Exists!,Please Enter A Different One.\n";
            else
                break;
        } while (true);

        St_Clients_Info New_Client = Get_Client_Data_From_User(AccNum);
        V_All_Clients.push_back(New_Client);

        Sort_Clients_By_Account_Number(V_All_Clients);
        Save_All_Clients(V_All_Clients);

        cout << "\n\aClient Added Successfully.\n";
        cout << "\nDo You Want To Add Another Client ? [Y/N]: ";
        cin >> Add_More;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (toupper(Add_More) == 'Y');
}
void Mark_Client_For_Delete(const string& AccNum, vector<St_Clients_Info>& V_All_Clients)
{
    for (St_Clients_Info& C : V_All_Clients)
    {
        if (C.Account_Number == AccNum)
        {
            C.Mark_For_Delete = true;
            return;
        }
    }
}
bool Delete_Client_By_Account_Number(string AccNum, vector<St_Clients_Info>& V_All_Clients)
{
    St_Clients_Info Client;
    if (Find_Client_By_Account_Number(AccNum, V_All_Clients, Client))
    {
        Print_Client_Card(Client);
        cout << "\aAre You Sure You Want To Delete This Client? [Y/N]: ";
        char Answer;
        cin >> Answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(Answer) == 'Y')
        {
            Mark_Client_For_Delete(AccNum, V_All_Clients);
            Sort_Clients_By_Account_Number(V_All_Clients);
            Save_All_Clients(V_All_Clients);
            cout << "\nClient Deleted Successfully.\n";
            return true;
        }
        else
        {
            cout << "\n!!! Deletion Cancelled !!!.\n";
            return false;
        }
    }
    else
    {
        cout << "\aClient With Account Number (" << AccNum << ") Not Found.\n";
        return false;
    }
}
bool Update_Client_By_Account_Number(string AccNum, vector<St_Clients_Info>& V_All_Clients)
{
    St_Clients_Info Client;
    if (!Find_Client_By_Account_Number(AccNum, V_All_Clients, Client))
    {
        cout << "\a\n!!! Client With Account Number (" << AccNum << ") Not Found !!!\n";
        return false;
    }

    Print_Client_Card(Client);
    cout << "\aAre You Sure You Want To Update This Client ? [Y/N]: ";
    char Answer;
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(Answer) != 'Y')
    {
        cout << "\n!!! Update Cancelled !!! .\n";
        return false;
    }

    string Input;
    cout << "Leave Field Empty To Keep Old Value.\n";

    Input = Read_Optional_Input("New Pin Code [" + Client.Pin_Code + "]: ");
    if (!Input.empty()) Client.Pin_Code = Input;

    Input = Read_Optional_Input("New Name [" + Client.Account_Name + "]: ");
    if (!Input.empty()) Client.Account_Name = Input;

    Input = Read_Optional_Input("New Phone [" + Client.Phone_Number + "]: ");
    if (!Input.empty()) Client.Phone_Number = Input;

    Input = Read_Optional_Input("New Balance [" + to_string(Client.Account_Balance) + "]: ");
    if (!Input.empty())
    {
        double New_Balance;
        bool Valid_Balance = false;
        do {
            try {
                size_t Pos;
                New_Balance = stod(Input, &Pos);
                if (Pos != Input.length()) throw invalid_argument("Trailing Characters");
                Valid_Balance = true;
            }
            catch (...) {
                cout << "\a\nInvalid Balance. Enter A Valid Number [ Or Press Enter To Keep Old ]: ";
                getline(cin, Input);
                if (Input.empty()) {
                    New_Balance = Client.Account_Balance;
                    Valid_Balance = true;
                }
            }
        } while (!Valid_Balance);
        Client.Account_Balance = New_Balance;
    }
    
    for (St_Clients_Info& C : V_All_Clients)
    {
        if (C.Account_Number == AccNum)
        {
            C = Client;
            break;
        }
    }

    Sort_Clients_By_Account_Number(V_All_Clients);
    Save_All_Clients(V_All_Clients);
    cout << "\nClient Updated Successfully.\n";
    return true;
}
void Show_Client_Card_By_Account_Number()
{
    vector<St_Clients_Info> V_All_Clients = Load_All_Clients();
    string AccNum = Read_User_Input("Enter Account Number To View : ");
    St_Clients_Info Client;
    if (Find_Client_By_Account_Number(AccNum, V_All_Clients, Client))
        Print_Client_Card(Client);
    else
        cout << "\aClient With Account Number (" << AccNum << ") Not Found.\n";
}
void Print_Header(string Header)
{
    cout << "\n================================================\n";
    cout << "\n\t" << Header << "\t\n";
    cout << "\n================================================\n\n";
}
bool Deposit_To_Account_Balance(string AccNum, vector<St_Clients_Info>& V_All_Clients)
{
    St_Clients_Info Clients;
    if (!Find_Client_By_Account_Number(AccNum, V_All_Clients, Clients))
    {
        cout << "\a\n!!! Client With Account Number (" << AccNum << ") Not Found !!!\n";
        return false;
    }

    Print_Client_Card(Clients);

    double Deposit_Value;
    string User_Input;
    bool Valid = false;
    do {
        User_Input = Read_User_Input("Enter Deposit Amount [ 0 to cancel ]: ");
        Deposit_Value = Safe_String_To_Double(User_Input);
        if (Deposit_Value == 0)
        {
            cout << "\n! Deposit Canceled.\n";
            return false;
        }
        if (Deposit_Value <= 0)
        {
            cout << "\a\n!!! Amount Must Be Greater Than Zero!!!\n";
        }
        else
        {
            Valid = true;
        }
    } while (!Valid);

    cout << "\n\aAre You Sure You Want To Perform This Transaction ? [Y/N]: ";
    char Answer;
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(Answer) != 'Y')
    {
        cout << "\n!!! Deposit Canceled !!!.\n";
        return false;
    }

    for (St_Clients_Info& C : V_All_Clients)
    {
        if (C.Account_Number == AccNum)
        {
            C.Account_Balance += Deposit_Value;
            cout << "\a\nDone Successfully ,[ New Balance: " << C.Account_Balance << " ].\n";
            break;
        }
    }
    Sort_Clients_By_Account_Number(V_All_Clients);
    Save_All_Clients(V_All_Clients);
    return true;
}
bool Withdraw_To_Account_Balance(string AccNum, vector<St_Clients_Info>& V_All_Clients)
{
    St_Clients_Info Clients;
    if (!Find_Client_By_Account_Number(AccNum, V_All_Clients, Clients))
    {
        cout << "\a\n!!! Client With Account Number (" << AccNum << ") Not Found !!!\n";
        return false;
    }

    Print_Client_Card(Clients);

    double Withdraw_Value;
    string User_Input;
    bool Valid = false;
    do {
        User_Input = Read_User_Input("Enter Withdraw Amount [ 0 to cancel ]: ");
        Withdraw_Value = Safe_String_To_Double(User_Input);
        if (Withdraw_Value == 0)
        {
            cout << "\n!!! Withdraw Canceled !!!.\n";
            return false;
        }
        if (Withdraw_Value <= 0)
        {
            cout << "\a\nAmount Must Be Greater Than Zero.\n";
        }
        else if (Withdraw_Value > Clients.Account_Balance)
        {
            cout << "\a\n!!! Amount Exceeds The Balance. You Can Withdraw Up To: " << Clients.Account_Balance << "\n";
        }
        else
        {
            Valid = true;
        }
    } while (!Valid);

    cout << "\n\aAre You Sure You Want To Perform This Transaction ? [Y/N]: ";
    char Answer;
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(Answer) != 'Y')
    {
        cout << "\n! Withdraw Canceled.\n";
        return false;
    }

    for (St_Clients_Info& C : V_All_Clients)
    {
        if (C.Account_Number == AccNum)
        {
            C.Account_Balance -= Withdraw_Value;
            cout << "\a\nDone Successfully , [ New Balance: " << C.Account_Balance << "].\n";
            break;
        }
    }
    Sort_Clients_By_Account_Number(V_All_Clients);
    Save_All_Clients(V_All_Clients);
    return true;
}
void Show_Total_Balances()
{
    double Total_Balances = 0.0;
    vector<St_Clients_Info> V_All_Clients = Load_All_Clients();
    Sort_Clients_By_Account_Number(V_All_Clients);
    cout << "==========================================================================================\n";
    cout << "\n\t\t\tClient List (" << V_All_Clients.size() << ") Client(s)\n";
    cout << "\n==========================================================================================\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(25) << "Client Name";
    cout << "| " << left << setw(12) << "Balance" << "\n";
    cout << "\n==========================================================================================\n";
    if (V_All_Clients.size() == 0)
    {
        cout << "\n\a\t\t\t!!! No Clients Available In the System !!!\n";
        cout << "\n==========================================================================================\n";
    }
    else
    {
        for (St_Clients_Info& C : V_All_Clients)
        {
            Total_Balances += C.Account_Balance;
            Print_Client_Info_For_Total_Balances_Table(C);
            cout << endl;
        }
        cout << "==========================================================================================\n";
        cout << "\n\t\t\t\t Total Balances = " << Total_Balances << "\n\n";
    }
}
void Print_Main_Menu()
{
    cout << "\n=========================================\n\n";
    cout << "\t   Main Menu Screen \n";
    cout << "\n=========================================\n";
    cout << "\t[1] Show All Clients\n";
    cout << "\t[2] Add New Client\n";
    cout << "\t[3] Delete A Client\n";
    cout << "\t[4] Update A Client\n";
    cout << "\t[5] Find A Client\n";
    cout << "\t[6] Transactions Menu\n";
    cout << "\t[0] Exit\n";
    cout << "=========================================\n";
}
void Print_Transactions_Menu_Screen()
{
    cout << "\n=========================================\n\n";
    cout << "\t   Transactions Menu Screen \n";
    cout << "\n=========================================\n";
    cout << "\t[1] Deposit \n";
    cout << "\t[2] Withdraw \n";
    cout << "\t[3] Total Balance \n";
    cout << "\t[0] Main Menu\n";
    cout << "=========================================\n";
}
En_Menue_Option Read_Valid_Option()
{
    int Option;
    do
    {
        cout << "\nChoose An Option [ 0 - 6 ]: ";
        cin >> Option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\a!!! Invalid Input! Please Enter A Number !!!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (Option >= 0 && Option <= 6)
            return static_cast<En_Menue_Option>(Option);
        else
            cout << "\n\a!!! Invalid Option ! , Please Choose Between [ 0 And 6 ] !!!\n";
    } while (true);
}
En_Transactions_Menu_Screen Read_Valid_Option_For_Transactions()
{
    int Option;
    do
    {
        cout << "\nChoose An Option [ 0 - 3 ]: ";
        cin >> Option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\a!!! Invalid Input! Please Enter A Number !!!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (Option >= 0 && Option <= 3)
            return static_cast<En_Transactions_Menu_Screen>(Option);
        else
            cout << "\n\a!!! Invalid Option ! , Please Choose Between [ 0 And 3 ] !!!\n";
    } while (true);
}
void Execute_Option_For_Transaction_Menue(En_Transactions_Menu_Screen Choice)
{
    system("cls");
    vector<St_Clients_Info> V_All_Clients;
    string AccNum;

    switch (Choice)
    {
    case Deposit:
        V_All_Clients = Load_All_Clients();
        Print_Header("Deposit Screen");
        AccNum = Read_User_Input("Enter Account Number: ");
        Deposit_To_Account_Balance(AccNum, V_All_Clients);
        break;
    case Withdraw:
        V_All_Clients = Load_All_Clients();
        Print_Header("Withdraw Screen");
        AccNum = Read_User_Input("Enter Account Number: ");
        Withdraw_To_Account_Balance(AccNum, V_All_Clients);
        break;
    case Total_Balance:
        V_All_Clients = Load_All_Clients();
        Show_Total_Balances();
        break;
    case Main_Menue:
        break;
    }
}
void Run_Transactions_Menu()
{
    En_Transactions_Menu_Screen Choice;
    do {
        system("cls");
        Print_Transactions_Menu_Screen();
        Choice = Read_Valid_Option_For_Transactions();
        Execute_Option_For_Transaction_Menue(Choice);
        if (Choice != Main_Menue)
        {
            cout << "\nPress Enter To Return To Transactions Menu...";
            cin.get();
        }
    } while (Choice != Main_Menue);
}
void Execute_Option(En_Menue_Option Choice)
{
    system("cls");
    vector<St_Clients_Info> V_All_Clients;
    string AccNum;

    switch (Choice)
    {
    case Show_All_Clients:
        Show_All_Clients_Table();
        break;
    case Add_New_Client:
        Print_Header("Add New Client Screen");
        Add_New_Clients();
        break;
    case Delete_Client:
        V_All_Clients = Load_All_Clients();
        Print_Header("Delete Client Screen");
        AccNum = Read_User_Input("Enter Account Number To Delete: ");
        Delete_Client_By_Account_Number(AccNum, V_All_Clients);
        break;
    case Update_Client_Info:
        V_All_Clients = Load_All_Clients();
        Print_Header("Update Client Screen");
        AccNum = Read_User_Input("Enter Account Number To Update: ");
        Update_Client_By_Account_Number(AccNum, V_All_Clients);
        break;
    case Find_Client:
        Print_Header("Find Client Screen");
        Show_Client_Card_By_Account_Number();
        break;
    case Transactions_Menue:
        Run_Transactions_Menu();
        break;
    case Exit:
        Print_Header("Exiting The System , Goodbye ! :-)");
        break;
    }
}
int main()
{
    En_Menue_Option Choice;

    do
    {
        system("cls");
        Print_Main_Menu();
        Choice = Read_Valid_Option();
        Execute_Option(Choice);
        if (Choice != Exit)
        {
            cout << "\nPress Enter To Return To Main Menu...";
            cin.get();
        }
    } while (Choice != Exit);
    system("pause>0");
    return 0;
}