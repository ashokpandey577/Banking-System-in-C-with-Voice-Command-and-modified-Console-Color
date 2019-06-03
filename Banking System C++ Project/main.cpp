//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<cstdlib>
#include<Windows.h>
#include "MMSystem.h"
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
};         //class ends here

void account::create_account()
{
	cout<<"\nEnter The Account No. : ";
	PlaySoundA(TEXT("ENTER ACCOUNT NO.WAV"),NULL,SND_SYNC);
	cin>>acno;
	cout<<"\n\nEnter The Name Of Account Holder : ";
	PlaySoundA(TEXT("ACCOUNT HOLDER NAME.WAV"),NULL,SND_SYNC);
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\nEnter Type Of The Account (C/S) : ";
	PlaySoundA(TEXT("ACCOUNT TYPE.WAV"),NULL,SND_SYNC);
	cin>>type;
	type=toupper(type);
	cout<<"\n\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    PlaySoundA(TEXT("INITIAL AMOUNT.WAV"),NULL,SND_SYNC);
	cin>>deposit;
	Sleep(5000);
	cout<<"\n\n\n\n\n\t\t\t\t\aAccount Created..";
    PlaySoundA(TEXT("ACCOUNT CREATED.WAV"),NULL,SND_SYNC);
}

void account::show_account() const
{
	cout<<"\n\n\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\n\t\t\tModify Account Holder Name : ";
    PlaySoundA(TEXT("MODIFY NAME.WAV"),NULL,SND_SYNC);
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tModify Type of Account : ";
    PlaySoundA(TEXT("MODIFY TYPE OF ACCOUNT.WAV"),NULL,SND_SYNC);
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify Balance amount : ";
    PlaySoundA(TEXT("MODIFY BALANCE AMOUNT.WAV"),NULL,SND_SYNC);
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    system("COLOR 1a");
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t\t\t\t  MAIN MENU";
		cout<<"\n\t\t\t\t-------------";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\t\t\t\t  02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\t\t\t  04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\t\t  06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\t\t\t  08. EXIT";
		cout<<"\n\n\n\n\t\tSelect Your Option : ";
		PlaySoundA(TEXT("MAIN MENU.wav"),NULL,SND_SYNC);
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : ";
		    PlaySoundA(TEXT("ENTER ACCOUNT NO.WAV"),NULL,SND_SYNC);
			cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : ";
			PlaySoundA(TEXT("ENTER ACCOUNT NO.WAV"),NULL,SND_SYNC);
			cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : ";
			PlaySoundA(TEXT("ENTER ACCOUNT NO.WAV"),NULL,SND_SYNC);
			cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : ";
            PlaySoundA(TEXT("ENTER ACCOUNT NO.WAV"),NULL,SND_SYNC);
            cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : ";
			PlaySoundA(TEXT("ENTER ACCOUNT NO.WAV"),NULL,SND_SYNC);
            cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\n\n\n\n\n\n\n\n\t\t   Thanks For Uing Bank Managemnt System";
			PlaySoundA(TEXT("THANKS FOR USING BANK.WAV"),NULL,SND_SYNC);
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\tEnter The New Details Of Account"<<endl;
	        PlaySoundA(TEXT("ENTER NEW DETAILS.WAV"),NULL,SND_SYNC);
	        Sleep(1000);
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			Sleep(3000);
			cout<<"\n\n\t\t\t\t Record Updated";
	        PlaySoundA(TEXT("RECORD UPDATED.WAV"),NULL,SND_SYNC);
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\n\n\n\t\t\t\t\aRecord Deleted...";
	PlaySoundA(TEXT("RECORD DELETED.WAV"),NULL,SND_SYNC);
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\t\t  HERE IS ACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.           NAME               Type    Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	PlaySoundA(TEXT("ALL LIST.WAV"),NULL,SND_SYNC);
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\n\n\n\t\t\t    TO DEPOSITE AMOUNT ";
				cout<<"\n\n\t\tEnter The amount to be deposited : ";
	            PlaySoundA(TEXT("AMOUNT TO BE DEPOSITED.WAV"),NULL,SND_SYNC);
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\n\n\n\t\t\t    TO WITHDRAW AMOUNT ";
				cout<<"\n\n\t\tEnter The amount to be withdraw : ";
	            PlaySoundA(TEXT("AMOUNT TO BE WITHDRAW.WAV"),NULL,SND_SYNC);
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t\t\t      Record Updated";
            PlaySoundA(TEXT("RECORD UPDATED.WAV"),NULL,SND_SYNC);
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************


void intro()
{

	cout<<"\n\n\n\n\n\n\n\n\n\t\t\t  WELCOME TO NATIONAL BANK";
	cout<<"\n\t\t\t----------------------------";
	cout<<"\n\t\t\t  Press Any Key To Continue.";
	cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tMADE BY : ASHOK PANDEY";
	cout<<"\n\n\t\t\t\t\t     COLLEGE : G.B.N. GOVT. POLYTECHNIC";
	PlaySoundA(TEXT("WELCOME TO NATIONAL BANK.wav"),NULL,SND_SYNC);
	cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
