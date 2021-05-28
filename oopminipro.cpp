#include<iostream>
#include<fstream>
using namespace std;
class hotel
{
    int room_no;
    char name[30];
    char address[50];
    char phone[10];
public:
    void details();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void delete_rec(int);
};
void hotel::details()
{
 cout<<endl<<endl<<"********HOTEL RAJ********"<<endl<<endl;
 int choice;
 while (choice=5)
 {
 cout<<"\n\t1.Book room";
 cout<<"\n\t2.Customer record";
 cout<<"\n\t3.Rooms alloted";
 cout<<"\n\t4.Edit record";
 cout<<"\n\t5.Exit";
 cout<<"\n\tenter your choice:";
 cin>>choice;
 switch(choice)
        {
            case 1: add();
					break;
			case 2: display();
					break;
			case 3: rooms();
					break;
			case 4: edit();
					break;
			case 5: break;
			default:
			    {
			        cout<<"\n\tWrong choise!!";
			        cout<<"\n\tPress any key to continue";
			    }
        }
 }
}
void hotel::add()
{
	int r,flag;
	ofstream fout("Record.data",ios::app);

	cout<<"\n Enter Customer Details";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check(r);
	if(flag)
		cout<<"\n Sorry!Room is already booked";
	else
	{
		room_no=r;
		cout<<"Name: ";
		cin>>name;
		cout<<"\nAddress: ";
		cin>>address;
		cout<<"\nPhone No: ";
		cin>>phone;
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked!";
	}

	cout<<"\n Press any key to continue!";
	fout.close();
}

void hotel::display()
{
	ifstream fin("Record.data",ios::in);
	int r,flag;
	cout<<"\n Enter room no: ";
	cin>>r;

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n Customer Details";
			cout<<"\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant!";

	cout<<"\n\n Press any key to continue!";
  fin.close();
}

void hotel::rooms()
{
	ifstream fin("Record.data",ios::in);
	cout<<"\n\t\ List Of Rooms Allotted";
	cout<<"\nRoom No.\tName\tAddress\tPhone No.\n";

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		cout<<"\n"<<room_no<<"\t"<<name;
		cout<<"\t"<<address<<"\t"<<phone;
	}

	cout<<"\n\tPress any key to continue!";
	fin.close();
}

void hotel::edit()
{
	int choice,r;

	cout<<"\n EDIT MENU";
	cout<<"\n 1.Delete Customer Record";

	cout<<"\n Enter your choice: ";
	cin>>choice;

	cout<<"\n Enter room no: ";
	cin>>r;

	switch(choice)
	{
		case 1: delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice!";
	}

	cout<<"\n Press any key to continue!";

}

int hotel::check(int r)
{
	int flag=0;
	ifstream fin("Record.data",ios::in);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			flag=1;
				break;
		}
	}

	fin.close();
	return(flag);
}
void hotel::delete_rec(int r)
{
	int flag=0;
	char ch;
	ifstream fin("Record.data",ios::in);
    ofstream fout("temp.data",ios::out);

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Pone No: "<<phone;
			cout<<"\n Do you want to delete this record(y/n): ";
			cin>>ch;

			if(ch=='n')
			fout.write((char*)this,sizeof(hotel));

			flag=1;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}

	fin.close();
	fout.close();

	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant!";
	else
	{
		remove("Record.data");
		rename("temp.data","Record.data");
	}
}

int main()
{
    hotel h;
	h.details();
	return 0;
}
