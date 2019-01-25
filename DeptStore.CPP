
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<iomanip.h>
#include<string.h>


void main();
void main_menu();
class user
{
      char userid[30],password[30];
      public:
	     void print();
	     int compare(char[],char[]);
}up;

void user::print()
 {
   cout<<userid<<" "<<password;
 }
int user ::compare(char u[30],char p[30])

 {

    if(strcmp(userid,u)==0 && strcmp(password,p)==0)
     return 1;
    return 0;
 }
class product
{
 int pno;
 char name[50],category[20];
  float price,qty,tax,dis;
 public:
	int productID();
	void create_product()
	{
	 pno=productID();
	 cout<<"\n\nPlease Enter The Name of The Product ";
	 gets(name);
	 cout<<"Please Enter The Category(clothes/shoes/watches)";
	 gets(category);
	 cout<<"\n\nPlease Enter The Quantity of The Product ";
	 cin>>qty;
	 cout<<"\nPlease Enter The Price of The Product ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%) ";
	 cin>>dis;
	 }
	void modify_product()
	{
	  int qt;

	 cout<<"\n\nPlease Enter The Quantity of The Product ";
	 cin>>qt;
	 qty=qty+qt;
	 cout<<"\nPlease Enter The Price of The Product ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%) ";
	 cin>>dis;
	 }

	void show_product()
	{
	 cout<<"\nThe Product No. of The Product : "<<pno;
	 cout<<"\nThe Name of The Product : ";
	 puts(name);
	 cout<<"\nCategory of the product : "<<category;
	 cout<<"\nThe Quantity of Product: "<<qty;
	 cout<<"\nThe Price of The Product : "<<price;
	 cout<<"\nDiscount : "<<dis;
	 }

  int  retpno()
  {return pno;}

  float retprice()
  {return price;}

  float retqty()
  {return qty;}

  char* retname()
  {return name;}

  char* retcategory()
  {return category;}
  int retdis()
  {return dis;}

  void setqty(int val)
  { qty=val;}

};         //class ends here



 fstream fp;
 product pr;

 //code to generate product id
	 int product::productID()
	 {
	  int pn=0;
	  product p;
	  fstream f;
	  f.open("item.dat",ios::in);
	  if(f.read((char*)&p,sizeof(product)))
	  {
	    pn=p.retpno();
	    while(f.read((char*)&p,sizeof(product)))
	    {
	      pn=p.retpno();
	    }
	  }

	  f.close();
	  return pn+1;
	 }

//    	function to write in file

void write_product()
   {
    fp.open("item.dat",ios::out|ios::app);
    pr.create_product();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\nThe Product with Product No. "<<pr.retpno()<<" Has Been Created ";
    getch();
   }
//    	function to read all records from file
void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("item.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 pr.show_product();
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();
    getch();
}
//    	function to read specific record from file
void display_sp(int n)
{
    int flag=0;
    fp.open("item.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()==n)
		{
		 clrscr();
		 pr.show_product();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nrecord not exist";
    getch();
}
//    	function to modify record of file
void modify_product()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Product No. of The Product ";
    cin>>no;
    fp.open("item.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product)) && found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.show_product();
		    cout<<"\nPlease Enter The New Details of Product"<<endl;
		    pr.modify_product();
		    int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}
//    	function to delete record of file
void delete_product()
   {
    int no;
    clrscr();
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete ";
    cin>>no;
    fp.open("item.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()!=no)
		{
		 fp2.write((char*)&pr,sizeof(product));
		 }
	 }
    fp2.close();
    fp.close();
    remove("item.dat");
    rename("Temp.dat","item.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }
//    	function to display all products price list

    void menu()
    {
     clrscr();
     fp.open("item.dat",ios::in);
     if(!fp.read((char*)&pr,sizeof(product)))
     {
       cout<<"product out of stock";
       cout<<"\n\n\nback to main menu ....";
       getch();
       fp.close();
       main_menu();
     }
     fp.seekg(0);
     cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"=====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tQuantity\tPRICE\n";
	  cout<<"=====================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retqty()<<"\t\t"<<pr.retprice()<<endl;
	}
     fp.close();
}
//    	function to place order and generating bill for Products

   void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='n';
    char found='n';
    menu();
    cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 //fp.open("Shop.dat",ios::in);
	 fp.open("item.dat",ios::in|ios::out|ios::binary);
	 cout<<"\n\nEnter The Product No. Of The Product : ";
	 cin>>order_arr[c];
	 int qt,pos;
	 while(fp.read((char*)&pr,sizeof(product)))
	 {
	   if(pr.retpno()==order_arr[c])
	   {
	     pos=-1*sizeof(pr);
	     qt=pr.retqty();
	     found='y';
	     break;
	   }
	 }
	 if(found=='n')
	 {
	   cout<<"Invalid Product No. Please Re-try"<<endl;

	   fp.close();
	   return;

	 }
	 if(qt==0)
	 {
	   cout<<"Sorry No Stock in hand for this product, purchase it later"<<endl;
	   return;
	 }

	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 if(quan[c]>qt)
	 {
	   cout<<"Invalid Quantity Re-try"<<endl;

	   quan[c]=0;
	   fp.close();
	   return;

	 }
	 int nqty=qt-quan[c];

	 pr.setqty(nqty);
	 fp.seekp(pos,ios::cur);

	 fp.write((char*)&pr,sizeof(product));
	 fp.close();


	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";getch();clrscr();
      cout<<"\n\n********************************INVOICE************************\n";
      cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
      for(int x=0;x<=c;x++)
	{
		 fp.open("item.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
    getch();
    }

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
 clrscr();
  cout<<setw(46)<<"~~~~~~~WELCOME~~~~~~~";
  cout<<"\n\n\t\t\t~~~~~~~~~~~SUPER MARKET~~~~~~~~~ "<<endl<<endl;
  int flag=0;
      char u[30],p[30],user[30],password[30],c;

      cout<<"\nUSERID:::";
      gets(u);
      cout<<"\npassword::";
      gets(p);
      ifstream file2("passwd.dat");
      while(!file2.eof())
      {
	file2>>user;
	file2>>password;

	if(strcmp(u,user)==0 && strcmp(p,password)==0)
	  {
	     file2.close();
	     flag=1;
	     cout<<"\n login successful!!";
	     getch();
	     break;
	  }

	  }

	if(flag==0)
	 {
	 cout<<"\n failed!!";
	 getch();
	 }
	 else{
	      cout<<"\nenter any key to continue";
	     getch();
	     main_menu();
	    }

	  }


//    	ADMINSTRATOR MENU FUNCTION
void admin_menu()
{
  clrscr();
  char ch2;
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\n\t1.CREATE PRODUCT";
  cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
  cout<<"\n\n\t3.QUERY ";
  cout<<"\n\n\t4.MODIFY PRODUCT";
  cout<<"\n\n\t5.DELETE PRODUCT";
  cout<<"\n\n\t6.VIEW PRODUCT MENU";
  cout<<"\n\n\t7.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
  ch2=getche();
  switch(ch2)
  {
    case '1': clrscr();
	      write_product();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;
	       clrscr();
	       cout<<"\n\n\tPlease Enter The Product No. ";
	       cin>>num;
	       display_sp(num);
	       break;
      case '4': modify_product();break;
      case '5': delete_product();break;
      case '6': menu();
		getch();
		admin_menu();
      case '7': main_menu(); break;
      default:cout<<"\a";admin_menu();
   }
   admin_menu();
}
//    	THE MAIN FUNCTION OF PROGRAM
void main_menu()
{
  char ch;
  do
    {
	  clrscr();
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getch();
	  switch(ch)
	  {
		 case '1': clrscr();
			   place_order();

			   getch();
			   break;
		  case '2': admin_menu();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');
}

void main()
{
  intro();

}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
















