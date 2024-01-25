/*ESHAN AHMAD
 BANK MANAGMENT SYSTEM
 */



#include<stdio.h>
#include<iostream.h>
#include<iomanip.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<fstream.h>
#include<ctype.h>
#include<string.h>
#include <limits.h>

void entrypage();

 int acc=0;
      int num;
    int x,y,cl,a,b;
class account
{
	int acno;
	char name[50];
    unsigned long int deposit;
	char type;
	char password[50];
public:
	
	char* get_password();
  char* retname();
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account

  int is_name_exists(const char* checkName) ;
};         //class ends here


int account::is_name_exists(const char* checkName) {
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return -1; // Return -1 to indicate an error
    }

    while (inFile.read((char *)(&ac), sizeof(account))) {
        // Compare the entered name with names in the file (case-insensitive)
        if (stricmp(ac.retname(), checkName) == 0) {
            inFile.close();
            return 1; // Name exists
        }
    }

    inFile.close();
    return 0; // Name does not exist
}

void account::create_account()
{
    cout << "\n\nEnter The Name of The account Holder: ";
    cin.getline(name, 50);
    if(is_name_exists(name))
    {
         cout << "Account with this name already exists. Please choose a different name.\n";
			  cout << "\nPress any key to continue...";
				getch(); // Pauses until a key is pressed
        entrypage();
        return;
        
    }
    else{
    char confirm_password[50];
    do {
        cout << "\nSet a Password for the account: ";
        cin.getline(password, sizeof(password));

        cout << "Enter password again for confirmation: ";
        cin.getline(confirm_password, 50);

        if (strcmp(password, confirm_password) != 0) {
            cout << "Passwords do not match. Try again.\n";
        }
    } while (strcmp(password, confirm_password) != 0);

    cout << "\nEnter Type of The account (C/S): ";
    cin >> type;
    type = toupper(type);
    cout<<type;
    if(type !='S' || type != 'C' || type !='s' || type != 'c' )
    {
      while(1)
      {
        if(type =='S' || type == 'C')
        {
          break;
        }
        cout<<"\nYou can only chose (C/S) ";
        cin>>type;
        type = toupper(type);
       
      }
    }
    
    cout << "\nEnter The Initial amount (>=500 for Saving and >=1000 for current): ";
    cin >> deposit;
    while(1)
    {
      if(deposit >= 500 && type == 'C')
      {break;}
      if(deposit >=1000 && type =='S')
      {
        break;
      }
      cout << "\nEnter The Initial amount (>=500 for Saving and >=1000 for current): ";
       cin >> deposit;
      
    }

    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    while (inFile.read((char *)(&ac), sizeof(account)))
    {
        acc = ac.retacno();
    }
    
    inFile.close();

    srand(time(0)); // Seed for random number generator
    acno = rand() % 10000 + 10000;
    cout << "\n\n\nAccount Created.." << "\tYOUR ACCOUNT NUMBER IS " << acno;
    }
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}

void account::modify() {
    cout << "\nAccount No. : " << acno;
    cout << "\nModify Account Holder Name : ";
    cin.ignore(); // Clears the buffer to handle previous input
    cin.getline(name, 50);

    cout << "\nModify Type of Account : ";
    cin >> type;
    cin.ignore(); // Clears the buffer to handle the '\n' character after reading 'type'
    type = toupper(type);

    cout << "\nDo you want to change the password (y/n)? ";
    char ch;
    cin >> ch;
    cin.ignore(); // Clears the buffer to handle the '\n' character after reading 'ch'

    if (tolower(ch) == 'y') {
        int password_confirmed = 0; // Using int as boolean, 0 for false
        char new_password[50];
        char confirm_password[50];

        do {
            cout << "Enter new password: ";
            cin.getline(new_password, 50);

            cout << "Confirm new password: ";
            cin.getline(confirm_password, 50);

            // Compare the new password with the confirmation password
            if (strcmp(new_password, confirm_password) == 0) {
                password_confirmed = 1; // Set to 1 for true
                // If matched, copy the new password
                strncpy(password, new_password, sizeof(password) - 1);
                password[sizeof(password) - 1] = '\0';
            } else {
                cout << "Passwords do not match. Try again.\n";
            }
        } while (password_confirmed == 0); // Loop until password_confirmed is not 0
    }
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
	
    cout << setw(10) << acno << setw(20) << name << setw(8) <<" " << type << setw(8) << deposit << setw(20) << password << endl;
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

  // For clrscr()





char* account::get_password(){ return password; }
char* account::retname(){ return name; }
//***************************************************************
//    	function declaration
//****************************************************************
int write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
void transfer_balance(int from_acc);




/**********mouse code start ***************/

       union REGS in,out;

       int callmouse()
       {
	      in.x.ax=1;
	      int86(51,&in,&out);
	      return 1;
       }
       void mouseposi(int &xpos,int &ypos,int &click)
       {
	      in.x.ax=3;
	      int86(51,&in,&out);
	      click=out.x.bx;
	      xpos=out.x.cx;
	      ypos=out.x.dx;
	}
       int mousehide()
       {
	      in.x.ax=2;
	      int86(51,&in,&out);
	      return 1;
       }
      void setposi(int &xpos,int &ypos)
      {
	     in.x.ax=4;
	     in.x.cx=xpos;
	     in.x.dx=ypos;
	     int86(51,&in,&out);
      }


/***************mouse code end **********/
/*********************graphic code start ***************/
  void entrypage()
 { clrscr();
   setcolor(RED);                           //background rectangle
   rectangle(0,0,650,450);
   setfillstyle(1,3);
   floodfill(2,2,RED);

   settextstyle(4,0,6);
   outtextxy(20,50,"Bank Management System");           //message printing

   settextstyle(3,0,3);
   outtextxy(250,250,"MADE BY :");

   setcolor(0);
   outtextxy(150,290,"           Eshan ");          //written by


    delay(3000);
    clrscr();
  void  page1();
page1();
 }

  void admin()                               //Admin page
  {          clrscr();
    setcolor(RED);
    rectangle(0,0,650,450);                     //background rectangle
    setfillstyle(1,3);
    floodfill(2,2,RED);

setcolor(15);				   // Top rectangle
    rectangle(200,100,400,180);
    setfillstyle(1,0);
    floodfill(202,101,15);

    setcolor(RED);
      settextstyle(3,0,1);
      outtextxy(250,110,"LIST OF ALL");
    outtextxy(220,140,"ACCOUNT HOLDERS");

    setcolor(15);
    rectangle(200,300,400,380);                 //Bottom rectangle
    floodfill(210,312,15);

    setcolor(RED);                           //message on buttons
    settextstyle(3,0,1);
      outtextxy(280,320,"Exit");
	cl=0;    int chk=0;
    do
	     {
		    mouseposi(x,y,cl);

   if((x>200)&&(x<400)&&(y>100)&&(y<180)&&(cl==1))
   {                       chk=1;
			display_all();
			  cout << "\nPress any key to continue...";
				getch(); // Pauses until a key is pressed
			break;
			
			

   }
    if((x>200)&&(x<400)&&(y>300)&&(y<380)&&(cl==1))
   {chk=2;
     void  exitpage();
		   exitpage();
		break;
   }

     }while(chk==0);
entrypage();
  }


 void exitpage()                                                 //last page
 {   clrscr();
    setcolor(9);
    rectangle(0,0,650,450);                //background rectangle
    setfillstyle(1,3);
    floodfill(2,2,9);

    setcolor(RED);
    settextstyle(3,0,5);
    outtextxy(240,80,"THANKS ");                 //message on screen
    outtextxy(225,125,"FOR USING");
    settextstyle(1,0,6);
    outtextxy(50,220,"BANK MANAGEMENT SYSTEM");
      delay(3000);

 }



  void page1()
  {


   clrscr();
    callmouse();
   //background

  setcolor(RED);                  //background rectangle
  rectangle(0,0,650,450);

  setfillstyle(1,3);
  floodfill(2,2,RED);

  //main interface

  setcolor(14);
  settextstyle(4,0,8);               //welcome screen
  outtextxy(130,0,"WELCOME");
  setcolor(10);
  settextstyle(1,0,3);
  outtextxy(300,90,"TO");

  setcolor(14);
  settextstyle(1,0,6);
  outtextxy(200,120,"BANK MANAGEMENT SYSTEM");


  setcolor(15);                    //customer rectangle
  rectangle(70,250,325,350);
  setfillstyle(1,0);
  floodfill(80,270,15);

   setcolor(4);
  settextstyle(1,0,4);
  outtextxy(110,270,"CUSTOMER");


  setcolor(15);
  rectangle(325,250,580,350);           //admin rectangle
  setfillstyle(1,0);
  floodfill(340,270,15);


  setcolor(4);
  settextstyle(1,0,4);
   outtextxy(400,270,"ADMIN");
   cl=0;      int chk=0;
    do
    {
		    mouseposi(x,y,cl);

   if((x>70)&&(x<325)&&(y>250)&&(y<350)&&(cl==1))
   {          chk=1;
      void page2();
		   page2();
		break;
   }
    if((x>325)&&(x<580)&&(y>250)&&(y<350)&&(cl==1))
   { chk=1;
		void  admin();
       clrscr();
		   admin();
		break;
   }

     }while(chk==0);
  }

  void page2()
  {   clrscr();
  setcolor(RED);            //background rectangle
  rectangle(0,0,650,450);
  setfillstyle(1,3);
  floodfill(2,2,RED);

  setcolor(15);                     //register rectangle
  rectangle(70,200,325,300);
  setfillstyle(1,0);
  floodfill(80,210,15);

  setcolor(RED);
  outtextxy(130,220,"REGISTER");

  settextstyle(1,0,2);
  outtextxy(150,250,"(new user)");

  setcolor(15);                      //login button
  rectangle(325,200,580,300);
  setfillstyle(1,0);
  floodfill(326,210,15);

  setcolor(RED);
  settextstyle(1,0,4);
  outtextxy(400,220,"LOGIN");
     cl=0;       int chk=0;
     delay(2000);
     do
	     { cl=0;
		    mouseposi(x,y,cl);
   if((x>70)&&(x<325)&&(y>200)&&(y<300)&&(cl==1))
   {clrscr();
      num=write_account();
	void page3();
	page3();

		chk=1;
		break;
   }
 if ((x > 325) && (x < 580) && (y > 200) && (y < 300) && (cl == 1)) {
        clrscr();

        cout << "\n\n\tEnter The account No. : "; 
        cin >> num;

        char entered_password[50];
        cout << "\tEnter Password: ";
        cin.ignore();
        cin.getline(entered_password, 50);

        account ac;
        int found = 0; // Use int instead of bool
        ifstream inFile;
        inFile.open("account.dat", ios::binary);
        if (!inFile) {
            cout << "File could not be open! Press any Key...";
            return;
        }

        while (inFile.read((char *) (&ac), sizeof(account))) {
                
            if (ac.retacno() == num && strcmp(ac.get_password(), entered_password) == 0) {
                found = 1; // Equivalent to true
                void page3();
                page3();
                break;
            }
            
        }
        if(found)
        {
          cout << "\nLogin Successful\n"; 
        }
        else
        {
          cout<<"\n Id or Password is incorrect \n";
               cout << "\nPress any key to continue to main page...";
               getch();
               entrypage();
               
        }
        inFile.close();

        if (found == 0) { // Equivalent to !found
            cout << "\nInvalid Account Number or Password\n";
			page2();
        }
    }

     }while(chk==0);

 }

 void page3()
 { clrscr();
   setcolor(4);               //make rectangle on half screen
   rectangle(0,225,650,450);
   setfillstyle(1,3);
   floodfill(10,226,4);

   setcolor(RED);               //buttons1
   rectangle(25,250,200,300);
   setfillstyle(1,0);
   floodfill(51,251,RED);
   setcolor(RED);
  settextstyle(1,0,1);
  outtextxy(35,260,"DEPOSIT");

   setcolor(RED);               //buttons2
   rectangle(475,250,625,300);
   setfillstyle(1,0);
   floodfill(501,251,RED);
     setcolor(RED);
  settextstyle(1,0,1);
  outtextxy(485,260,"Withdraw");


   setcolor(RED);               //buttons3
   rectangle(250,300,425,350);
   setfillstyle(1,0);
   floodfill(276,301,RED);
     setcolor(RED);
  settextstyle(1,0,1);
  outtextxy(260,310,"Money Transfer");


   setcolor(RED);               //buttons4
   rectangle(25,350,200,400);
   setfillstyle(1,0);
   floodfill(51,351,RED);
     setcolor(RED);
  settextstyle(1,0,1);
  outtextxy(35,360,"Modify Account");


   setcolor(RED);               //buttons5
   rectangle(475,350,625,400);
   setfillstyle(1,0);
   floodfill(501,351,RED);
     setcolor(RED);
  settextstyle(1,0,1);
  outtextxy(485,360,"Close Account");

   setcolor(RED);               //buttons6
   rectangle(250,400,425,450);
   setfillstyle(1,0);
   floodfill(410,425,RED);
     setcolor(RED);
  settextstyle(1,0,1);
  outtextxy(260,410,"Logout");
	display_sp(num);
			   int chk=0;
	 delay(1000);
     do
	     { cl=0;
		    mouseposi(x,y,cl);


   if((x>25)&&(x<200)&&(y>250)&&(y<300)&&(cl==1))
   {clrscr();
	deposit_withdraw(num, 1);

		chk=1;
		break;
   }
     if((x>475)&&(x<625)&&(y>250)&&(y<300)&&(cl==1))
   {clrscr();
		deposit_withdraw(num, 2);

		chk=1;
		break;
   }
     if((x>250)&&(x<425)&&(y>300)&&(y<350)&&(cl==1))
   {clrscr();
      transfer_balance(num);

		chk=1;
		break;
   }
     if((x>25)&&(x<200)&&(y>350)&&(y<400)&&(cl==1))
   {clrscr();
		modify_account(num);

		chk=1;
		break;
   }
     if((x>475)&&(x<625)&&(y>350)&&(y<400)&&(cl==1))
   {clrscr();
		delete_account(num);
		chk=1;
		break;
   }
    if((x>250)&&(x<425)&&(y>400)&&(y<450)&&(cl==1))
   {

		chk=2;
		entrypage();
    break;
   }


     }while(chk==0);
     if(chk==1)
     {page3();}

 }

/*****************graphic code end ***********/


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
 int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");


	entrypage() ;

	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

int write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *)&ac, sizeof(account));
	outFile.close();
	return ac.retacno();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	cout<<"\nACCOUNT DETAILS\n";

	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}


void transfer_balance(int from_acc) {
    int to_acc;
    account from_ac, to_ac;
    int transfer_amount;
    int found = 0, to_found = 0;
    long pos_from, pos_to;
    fstream File;
    char confirm;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    // Finding the 'from' account
    while(!File.eof() && found == 0) {
        pos_from = File.tellg(); // Store the position
        File.read((char *)&from_ac, sizeof(account));
        if(from_ac.retacno() == from_acc) {
            from_ac.show_account();
            found = 1;
        }
    }

    if(found == 0) {
        cout << "\n\nAccount number does not exist";
        File.close();
        cout << "\nPress any key to continue...";
				getch();
        return;
    }

    cout << "\nEnter the account number you wish to transfer to: ";
    cin >> to_acc;
    if(to_acc==from_ac.retacno())
    {
      cout << "\nYou cant tranfer to your own account";
       cout << "\nPress any key to continue...";
				getch();
        return;
    }
    // Finding the 'to' account
    File.seekg(0, ios::beg); // Go back to the start of the file
    while(!File.eof() && to_found == 0) {
        pos_to = File.tellg(); // Store the position
        File.read((char *)&to_ac, sizeof(account));
        if(to_ac.retacno() == to_acc) {
            to_ac.show_account();
            to_found = 1;
        }
    }

    if(to_found == 0) {
        cout << "\n\nAccount number to transfer to does not exist";
        File.close();
			  cout << "\nPress any key to continue...";
				getch(); // Pauses until a key is pressed
        return;
    }
   cout << "\nEnter the amount to transfer: ";    
    cin >> transfer_amount;

    // Check if the input is valid (an integer)
    if (cin.fail()) {
        cout << "Invalid input for transfer amount. Please make sure to enter only integers.\n";
        cout << "\nPress any key to continue...";
        getch();
        return;  // Exit the program with an error code
    }
    cout << "\nConfirm transfer (Y/N): ";
    cin >> confirm;
    if(toupper(confirm) == 'Y') {
        
        if(transfer_amount <= from_ac.retdeposit()) {
            from_ac.draw(transfer_amount);
            to_ac.dep(transfer_amount);

            // Update 'from' account
            File.seekp(pos_from, ios::beg);
            File.write((char *)&from_ac, sizeof(account));

            // Update 'to' account
            File.seekp(pos_to, ios::beg);
            File.write((char *)&to_ac, sizeof(account));
            
            cout << "\nTransfer complete";
        } else {
            cout << "\nNot enough balance to transfer";
        }
    } else {
        cout << "\nTransfer cancelled";

    }

    File.close();
    cout << "\nPress any key to continue...";
    getch();
}




//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==0)
	{
		File.read((char *)&ac, sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			//                           int pos=(-1)*static_cast<int>(sizeof(account));
			int pos=(-1)*(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		  }
	}
	File.close();
	if(found==0)
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
	while(inFile.read((char *) (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all() {
    clrscr();
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "=========================================================================\n";
    cout << setw(10) << "A/c no." << setw(20) << "NAME" << setw(10) << "Type" << setw(10) << "Balance" << setw(20) << "Password" << "\n";
    cout << "=========================================================================\n";

    while (inFile.read((char *) (&ac), sizeof(account))) {
        ac.report();

    }
    inFile.close();
}



//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************


void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==0)
	{
		File.read((char *) (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
        char conf;
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
        cout<<"\n are you sure you want deposit "<< amt << " amount \n Enter Y/N for for confirm or reject: ";
        cin>> conf;
        if(conf == 'Y' || conf == 'y')
        {
          ac.dep(amt);
          cout<<"\nsuccessfully deposit : "<<amt;
        }
        else{
          cout<<"\n you did't chose Y so this depoit is canceled ---";

        }
    		
			}
			if(option==2)
			{
        char conf;
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance";
				else
          {
                    
              cout<<"\n are you sure you want withdraw "<< amt << " amount \n Enter Y/N for for confirm or reject: ";
              cin>> conf;
              if(conf == 'Y' || conf == 'y')
              {
                ac.draw(amt);
                cout<<"\nsuccessfully withdrawn : "<<amt;
              }
              else{
                cout<<"\n withdrawal cancelled ---";

              }
              
              
          }
			}
			int pos=(-1)*(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write((char *) (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	 }
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


