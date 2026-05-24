/*
	=================================================================================
				    	INVENTORY MANAGEMENT WITH BILLING SYSTEM
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
	 >> Project Details   :
		***************************************
		Course    : CCC-302.
		Language  : C++
		
     >> Developement Team :
		***************************************
			1. Basit Ahmad - 253896 - 2nd Sem
			
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	 >> Project Overview  :
		***************************************
			+----+----------------------------------------------------+
			| Sr.|   Details                                          |
			+----+----------------------------------------------------+
			| 1. | Login For Security.                                |
			| 2. | Different Menus for Employee,Admin,Contoller.      |
			| 3. | File Handling For The Enitre Inventory.            |
			| 4. | Credential Control For the Logins.                 |
			| 5. | System Bypass for Controlling Passwords.           |
			| 6. | Credential file handing.                           |
			| 7. | Struct based storage for items/credentials.        |
			| 8. | Bill generation with Inventory Handling.           |
			| 9. | Reciept Generation for Printing Bills.             |
			+----+----------------------------------------------------+
		
	=================================================================================
*/

#include <iostream>				//  <-------------  Basic Input/Output.
#include <conio.h>				//  <------------- 	For one Fuction _getch().
#include <chrono>				//  <-------------  For Time related Functions.
#include <thread>				//  <------------- 	For Finding the thread of execution.
#include <iomanip>				//  <-------------  Manipulation of Input/Output.
#include <cstring>				//  <-------------  Manipulation of Strings.
#include <fstream>				//  <------------- 	For File Handling.			
#include <vector>				//  <-------------  Vectors are Used in the Bills

//==========================================================
//		GLOBALS. (Structs, Variables)
//==========================================================

const std::string shopowner = "BASIT MOBILES AND COMPUTERS";					// Name of the shop which will be written in the Bill.

struct item 
{
	char ID[10];
	char name[50];
	double price;					// Price At which we Buy.
	double sellprice; 				// Price At which we Sell.
	int amount;
	char entry_date[20];
	char expirey[20];
	int lowstock;
};

struct bill_struct
{
	char ID[10];
	std::string name;
	double sellprice;
	int amountbought;
	int amountininv;
};

struct credential 
{
    char role[10];
    char username[25];				//Username.
    char userpassword[25];			//Password associated with the Username.
    char email[25];
    char dob[15];					//Just For A Place Holder. Can be replaced By ID.
};


//==========================================================
//		UTILS CLASS.
//==========================================================

class utils 
{
    public:
    	
    	void clearscreen()
    	{
    		std::cout<<"\033[2J\033[H";
		}
    	void setcolor(int color) 												//<----Used to set the color of the Output(Sinlge Line) Anscii codes.
		{
			switch(color)
			{
				case 0:
					std::cout<<"\033[30m";
					break;
				case 1:
					std::cout<<"\033[34m";
					break;
				case 2:
					std::cout<<"\033[32m";
					break;
				case 3:
					std::cout<<"\033[36m";
					break;
				case 4:
					std::cout<<"\033[31m";
					break;
				case 5:
					std::cout<<"\033[35m";
					break;
				case 6:
					std::cout<<"\033[33m";
					break;
				case 7:
					std::cout<<"\033[37m";
					break;
					
				//	
					
				case 8:  
					std::cout << "\033[90m"; 
					break;
     			case 9:  
					std::cout << "\033[94m"; 
					break;
        		case 10: 
					std::cout << "\033[92m"; 
					break;
        		case 11: 
					std::cout << "\033[96m"; 
					break;
        		case 12: 
					std::cout << "\033[91m"; 
					break;
        		case 13: 
					std::cout << "\033[95m"; 
					break;
        		case 14: 
					std::cout << "\033[93m"; 
					break;
        		case 15: 
					std::cout << "\033[97m"; 
					break;
				
				//
				
				default:
					std::cout<<"\033[0m";
			}
			return;
		}
    	
    	void pause()															//<----Used to wait for input from the user
    	{
    		std::cout<<"\n\a\t\tPress any key to continue...";
			getch();	
		}
    	
        void playSpinner(int cycles, std::string msg) 							//<----Used to PLay the animation spinner. Send cycles and message o be printed during the Animation cylces. 
		{
            setcolor(6);
            char vars[] = {'/', '-', '\\', '|', '-'};
            for (int i = 0; i < cycles; ++i) 
			{
                for (char c : vars) 
				{
                    std::cout << "\r [ " << c << " ] " << msg << "... ";
                    std::cout.flush();
                    std::this_thread::sleep_for(std::chrono::milliseconds(80));
                }
            }
            std::cout << "\r [ ? ] Done!                                                            " << std::endl;
            setcolor(7);
        }
        int getint(std::string message)											//<-------- Used to get only INT values.
		{
        	int value = 0;
        	while(true)
			{
        		
        		std::cout<< message;
        		std::cin>> value;
        		if(std::cin.fail()) 
				{
        			std::cin.clear();
        			std::cin.ignore(1000,'\n');
        			std::cout<<"\n \a[ERROR] Enter a Valid Integer value! Try Again.";	
				}
				else
				{
					break;
				}	
			}
        	return value;
		}
		double getfloat(std::string message)											//<-------- Used to get only FLOAT values.
		{
        	double value = 0.0;
        	while(true)
			{
        		
        		std::cout<< message;
        		std::cin>> value;
        		if(std::cin.fail()) 
				{
        			std::cin.clear();
        			std::cin.ignore(1000,'\n');
        			std::cout<<"\n \a[ERROR] Enter a Valid Float Value! Try Again.";	
				}
				else
				{
					break;
				}	
			}
        	return value;
		}
		void timer(int time, std::string message)
		{
			for(time ; time > 0 ; time--)
			{
				std::cout<< "\r" << message << " < " << time << " > Seconds....";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		}
		
};

//==========================================================
//		ITEM BASE CLASS. 
//==========================================================


class items
{
	private:
		
		std::string inventoryfilename = "Inventory.dat";		// <------------- File Name For Item Storage.
		
	public:
		std::string getfilename()
		{
			return inventoryfilename;
		}
		
};

//==========================================================
//		USER CLASS (Base Class for Employee, Admin). 
//==========================================================

class user
{
	private:
		items inventory;										// <------------- Abstract Class
	public:
		item i1;
		std::string inventoryfilename = inventory.getfilename();
		virtual void viewitem(item i1,int sr) = 0;
		virtual void showall() = 0;
		virtual void additem() = 0; 
		virtual void modifyitem() = 0;
		virtual void deleteitem() = 0;
		
};


//==========================================================
//		EMPLOYEE CLASS 
//==========================================================

class employee : public user
{
	public:
		
		utils u1;
		void additem(){}
		void modifyitem(){}
		void deleteitem(){}										// <------------- Undefined But Still Make the Class Concrete.
		void viewitem (item i1,int sr)												// <------------- View an Item.
		{
        	std::cout << std::left << "\t\n | " << std::setw(5)  << sr << " | " 
									<< std::setw(10) << i1.ID << " | "
                		   			<< std::setw(50) << i1.name << " | "
            << std::fixed << std::setprecision(2) << std::setw(10) << i1.sellprice << " | "
                		  			<< std::setw(10) << i1.amount << " | "
             			   			<< std::setw(20) << i1.entry_date << " | "
                   		   			<< std::setw(20) << i1.expirey << " | " << (i1.amount <= i1.lowstock ? "Low in Stock!" : ""); 
		}
		
		void showall() 
		{
			int sr = 1;
    		std::ifstream file(inventoryfilename, std::ios::binary); 				// <-------- std::ifstream = input file stream.
			
    		if(!file) 
			{
    			u1.setcolor(04);
        		std::cout << "\t \a[ERROR] File Opening Error!\n";
        		u1.pause();
        		u1.setcolor(07);
       			return;
    		}
    		
			std::cout << "\n\t <===========================================[ SHOWING CURRENT INVENTORY ]=======================================================>\n\n";
			std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    		std::cout << std::left << "\n\t"
    							   << "  | "<< std::setw(5)  << "  Sr." 
								   << "  | "<< std::setw(10) << "  ID" 
            		               << "  | "<< std::setw(50) << "  Name" 
            		               << "  | "<< std::setw(10) << "  Price" 
            		               << "  | "<< std::setw(10) << "  Amount" 
           						   << "  | "<< std::setw(20) << "  Entry Date" 
                           		   << "  | "<< std::setw(20) << "  Expiry" << " | ";
    		std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    		while(file.read(reinterpret_cast<char*>(&i1), sizeof(i1))) 
			{           	
				viewitem(i1,sr);
				sr++;
    		}
    		std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    		std::cout << "\n\n";
    		u1.pause();

    		file.close();
		}
};


//==========================================================
//		ADMIN CLASS 
//==========================================================

class admin : public user
{
	public:
		utils u1;
		
		void viewitem (item i1,int sr)												// <------------- View an Item.
		{
        	std::cout << std::left << "\n\t | " << std::setw(5)  << sr << " | " 
									<< std::setw(10) << i1.ID << " | "
                		   			<< std::setw(50) << i1.name << " | "
            << std::fixed << std::setprecision(2) << std::setw(10) << i1.sellprice << " | "
            << std::fixed << std::setprecision(2) << std::setw(10) << i1.price << " | "
                		  			<< std::setw(10) << i1.amount << " | "
             			   			<< std::setw(20) << i1.entry_date << " | "
                   		   			<< std::setw(20) << i1.expirey << " | " << (i1.amount <= i1.lowstock ? "Low in Stock!" : ""); 
		}
		
		void additem() 																// <-------------- Add A New Item In The File.
		{
			u1.setcolor(3);
			std::cout<<"\n\tADD THE ITEM INFO\n";
			std::cout<<"__________________________________________________________________\n";
			u1.setcolor(7);
			std::cout<<"\t > Enter Item ID : ";
			std::cin.ignore();
			std::cin.getline(i1.ID, 10);
			std::cout<<"\t > Enter Item Name : ";
			std::cin.getline(i1.name, 50);
			i1.price = u1.getfloat("\t > Enter Item Buying Price : ") ;
			i1.sellprice = u1.getfloat("\t > Enter Item Selling Price : ") ;
			i1.amount = u1.getint("\t > Enter Item Stock (Amount) : ");
			i1.lowstock = u1.getint("\t > Enter Low Stock Alert Value : ");
			std::cout<<"\t > Enter Item Entry Date : ";
			std::cin.ignore();
			std::cin.getline(i1.entry_date, 20);
			std::cout<<"\t > Enter Item Expirey Date : ";
			std::cin.getline(i1.expirey, 20);
			
			if(i1.expirey =="  ")
			{
				strcpy(i1.expirey,"NO EXPIREY");
			}
			
			std::ofstream file(inventoryfilename , std::ios::binary | std::ios::app);// std::ofstream = Output file stream ___ ios::binary = .dat file opener ___ ios::app = Append for file opening
			if(!file)
			{
				u1.setcolor(4);
        		std::cout << "\t \a[ERROR] File Opening Error!\n";
        		u1.pause();
        		u1.setcolor(7); 
       			return;
			}
			file.write(reinterpret_cast<const char*>(&i1), sizeof(i1) );			// Writing to the file with the help of the size of Struct item and starting address of Item struct variable i1.
			u1.setcolor(2);
			std::cout<<"__________________________________________________________________\n";
			std::cout<<"\n\n\t [DONE] Succesfully Added Item..\n";
			u1.setcolor(7);
			file.close();
			u1.pause();
		}
		
		void showall () 
		{
			int sr = 1;
    		std::ifstream file(inventoryfilename, std::ios::binary); 				// <-------- std::ifstream = input file stream.
			
    		if(!file) 
			{
    			u1.setcolor(4);
        		std::cout << "\t \a[ERROR] File Opening Error!\n";
        		u1.pause();
        		u1.setcolor(7);
       			return;
    		}
			std::cout << "\n\t\t <===========================================[ SHOWING CURRENT INVENTORY ]=======================================================>\n\n";
			std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    		std::cout << std::left << "\n\t"
    							   << " | "<< std::setw(5)  << " Sr." 
								   << " | "<< std::setw(10) << " ID" 
            		               << " | "<< std::setw(50) << " Name" 
            		               << " | "<< std::setw(10) << "Sell Price"
            		               << " | "<< std::setw(10) << " Buy Price"
            		               << " | "<< std::setw(10) << " Amount" 
           						   << " | "<< std::setw(20) << " Entry Date" 
                           		   << " | "<< std::setw(20) << " Expiry" << " | ";
    		std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    		while(file.read(reinterpret_cast<char*>(&i1), sizeof(i1))) 
			{           	
				viewitem(i1,sr);
				sr++;
    		}
    		std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    		std::cout << "\n\n";
    		u1.pause();

    		file.close();
		}
		
		item exchangevalue(item i1)													// <---------- Function for Changing the Value of any of attribute of a struct.
		{
			char attchoice;
			item i2;
						std::cout << "\t\nWhat Attribute Do You Want to Edit .\n";
						std::cout << "________________________________________________________________\n\n";
						std::cout << "\t+---------------------------------+\n";
						std::cout << "\t|      MODIFICATION PANEL         |\n";
						std::cout << "\t+=================================+\n";
						std::cout << "\t| 9. | All Attribute.             |\n";
						std::cout << "\t+----+----------------------------+\n";
						std::cout << "\t| 1. | Item ID.                   |\n";
						std::cout << "\t| 2. | Item Name.                 |\n";
						std::cout << "\t| 3. | Item Trade Price.          |\n";
						std::cout << "\t| 4. | Item Purchase Price.       |\n"; 
						std::cout << "\t| 5. | Item Quantity.             |\n";
						std::cout << "\t| 6. | Item Entry Date.           |\n";
						std::cout << "\t| 7. | Item Expirey Date.         |\n";
						std::cout << "\t| 8. | Item Low Stock Alert Value.|\n";
						std::cout << "\t+----+----------------------------+\n";
						std::cout << "\t| 0. | Save and Return.           |\n";
						std::cout << "\t+----+----------------------------+\n\n";
						
						while(true)
						{
							attchoice = u1.getint("\tEnter The Choice : ");
							switch(attchoice)
							{
							case 9:
							{
							
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								std::cout<<" > Enter new Item ID : ";
								std::cin.ignore();
								std::cin.getline(i2.ID, 10);
								std::cout<<" > Enter new Item Name : ";
								std::cin.getline(i2.name, 50);
								i1.price = u1.getfloat(" > Enter new Item Price : ") ;
								i1.amount = u1.getint(" > Enter new Item Amount Invoiced : ");
								std::cout<<" > Enter new Item Entry Date : ";
								std::cin.ignore();
								std::cin.getline(i2.entry_date, 20);
								std::cout<<" > Enter new Item Expirey Date : ";
								std::cin.getline(i2.expirey, 20);
								i1 = i2;
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 1:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								std::cout<<" > Enter new Item ID : ";
								std::cin.ignore();
								std::cin.getline(i2.ID, 10);
								strcpy(i1.ID , i2.ID);
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 2:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								std::cout<<" > Enter new Item Name : ";
								std::cin.ignore();
								std::cin.getline(i2.name, 50);
								strcpy(i1.name , i2.name);
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 3:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								i1.sellprice = u1.getfloat(" > Enter new Item Trade Price : ") ;
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 4:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								i1.price = u1.getfloat(" > Enter new Item Purchase Price : ") ;
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 5:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								i1.amount = u1.getint(" > Enter new Item Ouantity in Inventory : ");
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 6:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								std::cout<<" > Enter new Item Entry Date : ";
								std::cin.ignore();
								std::cin.getline(i2.entry_date, 20);
								strcpy(i1.entry_date , i2.entry_date);
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 7:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								std::cout<<" > Enter new Item Expirey Date : ";
								std::cin.ignore();
								std::cin.getline(i2.expirey, 20);
								strcpy(i1.expirey , i2.expirey);
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 8:
							{
								std::cout<<"\n\tADD THE NEW ITEM INFO\n";
								std::cout<<"__________________________________________\n";
								i1.lowstock = u1.getint(" > Enter new Item Low Stock Alert Value : ");
								std::cout<<"__________________________________________\n";
								std::cout<<" [DONE] > Saved Modification.\n\n";
								break;
							}
							case 0:
							{
								std::cout << " [DONE] Leaving Modification Control.\n";
								u1.playSpinner(2,"Returning to Menu.");
								break;
							}
							default:
								std::cout << " \a[ERROR] Wrong Input!\n";		
							}
							if(attchoice == 0) break;
						}
			return i1;
		}
		
		void modifyitem() 															// <----------- Modifying An Item Already in the System Files.
		{
			int sr = 1;
			item i2;
			bool found = false;
			char findID[10],choice,attchoice;
    		std::fstream file(inventoryfilename, std::ios::binary | std::ios::in | std::ios::out);
			
    		if(!file) 
			{
    			u1.setcolor(4);
        		std::cout << "\t \a[ERROR] File Opening Error!\n";
        		u1.setcolor(7);
				u1.pause();
       			return;
    		}

    		std::cout << "\n\t Enter The ID Of the item you Want to Modify : ";
    		std::cin.ignore();
    		std::cin.getline(findID, 10);

    		while(file.read(reinterpret_cast<char*>(&i1), sizeof(i1))) 
			{

			//	std::cout << "Comparing with: [" << i1.ID << "]\n";					//<-----------( If the loop doesn't work. Check By un-commenting this Line . It will tell you the flow of loop and point of termination . Making Debugging Easier. Don't ask how I Came up with this. It brings Back Harsh Memmories. 

				if(strcmp(findID, i1.ID) == 0)
				{
					std::cout << "\n\t\tCurrent Item Status\n";
					std::cout << "\t\t<======================================>\n\n";	
					std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
					std::cout << std::left << "\n\t"
    							   << " | "<< std::setw(5)  << "  Sr." 
								   << " | "<< std::setw(10) << "  ID" 
            		               << " | "<< std::setw(50) << "  Name" 
            		               << " | "<< std::setw(10) << "Sell Price"
            		               << " | "<< std::setw(10) << " Buy Price" 
            		               << " | "<< std::setw(10) << "  Amount" 
           						   << " | "<< std::setw(20) << "  Entry Date" 
                           		   << " | "<< std::setw(20) << "  Expiry" << " | " ;
	    			std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    	    		viewitem(i1, sr);
					std::cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
					
					std::cout << "\n\nDo You Want to Modify the Item? (Y/N) : ";
					charchoice:
					std::cin>>choice;
					if(choice == 'y' || choice == 'Y')
					{
						i1 = exchangevalue(i1);
						found = true;
					
						file.seekp(-(int)sizeof(i1) , std::ios::cur);
						file.write(reinterpret_cast<const char*>(&i1), sizeof(i1));
						u1.playSpinner(2,"Updating The Database.");
						u1.clearscreen();
						u1.setcolor(2);
						std::cout<<"\n____________________________________________________\n";
						std::cout<<"\n\t [SUCCESS] Item updated succesfully.\n";
						file.close();
						u1.setcolor(7);
						u1.pause();
						break;	
					
					}
					else if(choice == 'n' || choice == 'N')
					{
						std::cout << " [DONE] Leaving without Modifications.\n";
						u1.playSpinner(2,"Returning to Menu.");
						return;
					}
					else
					{
						std::cout<<"Wrong Input\n";
						goto charchoice;
					}
					
				}
				
			}
    			if(!found) 
				{
					u1.setcolor(4);
        			std::cout << "\t \a[ERROR] ID not Found!\n";
        			u1.pause();
        			u1.setcolor(7);
       				return;	
				}
		}
		
		void deleteitem()															// <------ Function to delete an item already in the System Files.
		{
			char findID[10],ch;
			bool found = false;
			std::cout << "\n\t Enter The ID Of the item you Want to Delete : ";
    		std::cin.ignore();
    		std::cin.getline(findID, 10);
			std::cout<<"  +----+-------------------------------------------+----------+\n";
			std::cout<<"  | Are you sure You Want to delete the item at ID |"<< std::setw(10) << findID  <<"|\n";
			std::cout<<"  +----+-------------------------------------------+----------+\n";
			while(true)
			{
				std::cout << "\n\t Confirm Again (Y/N) : ";
				std::cin>>ch;
				if(ch == 'y' || ch == 'Y')
				{
					std::ifstream copyfrom(inventoryfilename, std::ios::binary);
					std::ofstream copyto("temp.dat", std::ios::binary);
			
					while(copyfrom.read(reinterpret_cast<char*>(&i1), sizeof(i1)))
					{
						if(strcmp(findID, i1.ID) != 0)
						{
							copyto.write(reinterpret_cast<const char*>(&i1), sizeof(i1));	
						}
						else
						{
							found = true;
						}
					}
					
					copyfrom.close();
					copyto.close();
					
					if(!found)
					{
						u1.clearscreen();
						u1.setcolor(4);
        				std::cout << "\t \a[ERROR] ID not Found!\n";
        				u1.pause();
        				u1.setcolor(4);
	       				return;
					}
			
					remove(inventoryfilename.c_str());
					rename("temp.dat", inventoryfilename.c_str());
					
					u1.playSpinner(2,"Deleting The Record");
					u1.clearscreen();
					u1.setcolor(4);
        			std::cout << "\t [DONE] Item At [ "<<findID<<" ] Deleted Succesfully\n";
	       			u1.pause();
    	   			u1.setcolor(07);
    	   			return;
			
				}
				else if(ch == 'n' || ch == 'N')
				{
					u1.clearscreen();
					u1.setcolor(2);
					std::cout << "\t [OK] Returning Without Deletion.\n";
        			u1.setcolor(07);
					u1.pause();
					return;
				}
				else
				{
					u1.setcolor(4);
					std::cout << "\t \a[ERROR] Wrong Input.\n";
					u1.setcolor(7);
				}
			}
		}
		
};

//==========================================================
//		AUTHENTICATION CLASS. 
//==========================================================
//  	(Gets Username and Masked Password form the user and RETURNS Role of the user in the system.)
class Auth
{

	private:
		std::string credentialsfile = "Credentials.dat";
        
        std::string secretusername = "......";
        std::string secretpassword = "123456";	
        
        std::string username = "";
	public:	
		utils u1;
		
		std::string getusername()
		{
			return username;
		}
		
		std::string getpassword() 
		{
            std::string password = "";
            char ch;
            while ((ch = _getch()) != '\r') 
			{
                if (ch == '\b') 
				{
                    if (!password.empty()) 
					{
                        password.pop_back();
                        std::cout << "\b \b";
                    }
                } 
				else 
				{
                    password += ch;
                    std::cout << "*";
                }
            }
            std::cout << "\n";
            return password;
        }
		
		std::string authenticate() 
		{
        	
        	credential c1;
        	bool success = false;
        	int ch = 0;
        	
        	std::string input_username = "";
        	std::string input_password = "";
        	std::string roleinsystem = "";
        	
        	int tries = 4; 														// <--------- We Give them 5 Chances. As they have Already used one on thier first entry so 5 - 1 = 14 .
        	
        	do
			{
				do
				{
        			u1.clearscreen();
        			std::cout<<"\n\t\t+----+-----------------------------------+";
        			std::cout<<"\n\t\t| >> | Enter Your Choice for Loging in.  |";
        			std::cout<<"\n\t\t+----+-----------------------------------+";
        			std::cout<<"\n\t\t| 1. | Controller.                       |";
        			std::cout<<"\n\t\t| 2. | Admin.                            |";
        			std::cout<<"\n\t\t| 3. | Employee.                         |";
        			std::cout<<"\n\t\t+----+-----------------------------------+";
        			ch = u1.getint("\n\t\t----->");
        			if(ch == 1)
					{ 
						u1.playSpinner(1,"\t\tRedirecting to Controller Login"); 
						std::cin.ignore();
						break;
					}
        			else if(ch == 2)
					{ 
						u1.playSpinner(1,"\t\tRedirecting to Admin Login"); 
						std::cin.ignore();
						break;
					}
        			else if(ch == 3)
					{ 
						u1.playSpinner(1,"\t\tRedirecting to Employee Login");
						std::cin.ignore(); 
						break; 
					}
        			else 
					{ 
						u1.setcolor(4); 
						std::cout<<"\t\t\a Wrong Input!"; 
						u1.setcolor(7); 
						
					}
				}while(true);
				
        		u1.clearscreen();
        		
        		std::cout<<"\n\t\t\t\tLOGIN\n";
    	    	u1.setcolor(3);
				std::cout<<"\t\t______________________________________________________\n";
				std::cout<<"\t\t----> Enter Username : ";			
				getline(std::cin , input_username);
				std::cout<<"\t\t----> Enter Password : ";
				input_password = getpassword();
				u1.setcolor(7);
			
				if(input_username == secretusername && input_password == secretpassword)
				{
					u1.playSpinner(1,"Moving to Credential Control");
					return "SUPERADMIN";
				}
			
				std::ifstream file(credentialsfile, std::ios::binary);
			
				if (!file) 
				{
        	        u1.setcolor(4);
        	        std::cout << "\t\t \a[ERROR] File Opening Error!\n";
           	    	u1.setcolor(7);
					u1.pause();
         	       return "UNKNOWN";
         	   }
			
				while(file.read(reinterpret_cast<char*>(&c1), sizeof(c1)))
				{
					if(input_username == c1.username && input_password == c1.userpassword)
					{
						success = true;
						roleinsystem = c1.role;
						username = c1.username;
						u1.clearscreen();
						u1.setcolor(3);
						std::cout<<"\n\t\tLoged in Succesfully !\n";
						u1.setcolor(7);
						std::cout<<"____________________________________________________________\n\n";
						u1.setcolor(3);
						std::cout<<"\t\tLoged in as "<<roleinsystem<<"\n";
						u1.setcolor(7);
						u1.pause();
						u1.setcolor(07);
						return roleinsystem;
					}
				}
			
				if(success == false)
				{
					u1.setcolor(4);
					if(ch == 1)
					{
						std::cout << "\n\t\t \a[ERROR] Wrong Controller_Username OR Password!";
					}
					else if(ch == 2)
					{
						std::cout << "\n\t\t \a[ERROR] Wrong Admin_Username OR Password!";
					}
					else
	                {
	                	std::cout << "\n\t\t \a[ERROR] Wrong Employee_Username OR Password!";
					}
    	            std::cout << "\n\t\t\a [ALERT] You have ["<< tries <<"] attempsts Left";
        	        u1.setcolor(7);
    	            std::cout<<"\n\t\t____________________________________________________________\n";
					u1.pause();
                	tries--;
				}
			
        	}while(tries > 0);
        	
        	if(tries <= 0)
        	{
				u1.clearscreen();
				u1.setcolor(4);
				std::cout<<"\n [WARNING] System Locked ! \n";
				u1.timer(30,"Try Loging in After");
				u1.playSpinner(2,"Redirecting to Login.         ");
				return "UNKNOWN";
			}
		return "UNKNOWN";
		}
		
};

//==========================================================
//		ADMINISTRATION CLASS.(Only for the SuperAdmin.)
//==========================================================

class adminstration : public Auth
{
	private:
		std::string credentialsfile = "Credentials.dat";
	public:
		utils u1;
		std::string credentialcontrol() 
		{
            int choice = 1;
            while (choice != 0) 
			{
                u1.clearscreen();
                u1.setcolor(07);
                std::cout << "\n\n\t+--------------------------------+\n";
                std::cout << "\t|      CREDENTIAL CONTROL            |\n";
                std::cout << "\t+====================================+\n";
                std::cout << "\t| 1. |  Create Credential.           |\n";
                std::cout << "\t| 2. |  Modify Credential.           |\n";
                std::cout << "\t| 3. |  Delete Credential.           |\n";
                std::cout << "\t| 4. |  View all Credentials.        |\n";
                std::cout << "\t+----+-------------------------------+\n";
                std::cout << "\t| 0. |  Return to login.             |\n";
                std::cout << "\t+----+-------------------------------+\n\n";
                choice = u1.getint("\t----> ");
                switch (choice) 
				{
                    case 1:
                        u1.clearscreen();
                        u1.playSpinner(1, "Getting Ready For Data");
                        u1.clearscreen();
                        create_credentials();
                        u1.setcolor(07);
                        break;
                    case 2:
                        u1.clearscreen();
                        u1.playSpinner(1, "Preparing Files.");
                        u1.clearscreen();
                        change_credentials();
                        u1.setcolor(07);
                        break;
                    case 3:
                        u1.clearscreen();
                        u1.playSpinner(1, "Fetching Files From Hard Disk.");
                        u1.clearscreen();
                        delete_credentials();
                        u1.setcolor(07);
                        break;
                    case 4:
                        u1.clearscreen();
                        u1.playSpinner(1, "Accessing Database.");
                        u1.clearscreen();
                        view_credentials();
                        u1.setcolor(7);
                        break;
                    case 0:
                        return "UNKNOWN";
                    default:
                    	u1.setcolor(4);
                        std::cout << " \a[ERROR] Wrong Input!\n";
                        u1.setcolor(7);
                        break;
                }
            }
        return "UNKNOWN";
		}
        
        void view_credentials() 
		{
        	credential c1;
        	int sr = 1;
        	std::ifstream file(credentialsfile, std::ios::binary);
        	if (!file) {
                u1.setcolor(4);
                std::cout << " \a[ERROR] File Opening Error!\n";
                u1.setcolor(7);
				u1.pause();
                return;
            }
            			
			u1.clearscreen();
        	std::cout << "<===========================================[ SHOWING CURRENT CREDENTIALS ]======================================================>\n\n";
            std::cout << std::left
            		  << "| " << std::setw(5)  << "Sr."
                      << "| " << std::setw(10) << "Role"
                      << "| " << std::setw(25) << "Username"
                      << "| " << std::setw(25) << "Password"
                      << "| " << std::setw(35) << "Email"
                      << "| " << std::setw(15) << "DOB" << "|\n";
            std::cout << "================================================================================================================================\n";
        	while (file.read(reinterpret_cast<char*>(&c1), sizeof(c1))) 
			{

                  std::cout << std::left
                    		<< "| " << std::setw(5)  << sr
                            << "| " << std::setw(10) << c1.role
                            << "| " << std::setw(25) << c1.username
                            << "| " << std::setw(25) << c1.userpassword
                            << "| " << std::setw(35) << c1.email
                            << "| " << std::setw(15) << c1.dob 
							<< "|\n";
                
                sr++;
        	}
        	std::cout<<"\n\n";
        	u1.pause();
		}

        void create_credentials() {
            credential c1;
            std::string confirm_password;

            std::cout << "\n\tCREATE NEW CREDENTIAL\n";
            std::cout << "__________________________________________\n";
            
			std::cin.ignore();																// <--------- This was inside the Do-while loop BUT it caused the inputs to be eaten. And Run the loop infinitly. So Just Placed it Outside.
			do
			{
				std::cout << " > Enter a Valid Role (ADMIN/EMPLOYEE) : ";            	
				std::cin.getline(c1.role, 10);
			}
			while( strcmp(c1.role,"ADMIN") != 0 && strcmp(c1.role, "EMPLOYEE") != 0 );
			
            std::cout << " > Enter Username : ";
			std::cin.getline(c1.username, 25);
            std::cout << " > Enter Password : ";
			std::cin.getline(c1.userpassword, 25);
            while (true) 
			{
                std::cout << " > Confirm Password : ";
                confirm_password = getpassword();
                if (confirm_password == c1.userpassword) 
				{
                    break;
                }
                u1.setcolor(4);
                std::cout << " \a[ERROR] Passwords Do Not Match! Try Again.\n";
                u1.setcolor(7);
            }

            std::cout << " > Enter Email : ";
			std::cin.getline(c1.email, 25);
            std::cout << " > Enter Date of Birth : ";
			std::cin.getline(c1.dob, 15);
            std::ofstream file(credentialsfile, std::ios::binary | std::ios::app);
            if (!file) 
			{
                u1.setcolor(4);
                std::cout << " \a[ERROR] File Opening Error!\n";
                u1.setcolor(7);
				u1.pause();
                return;
            }

            file.write(reinterpret_cast<const char*>(&c1), sizeof(c1));
            file.close();
            u1.playSpinner(1,"Saving Data");
            u1.setcolor(2);
            std::cout << "\n [DONE] Credential Created Successfully!\n";
            u1.pause();
            u1.setcolor(7);
        }

        void change_credentials() 
		{
            credential c1;
            bool found = false;
            std::string edit, temp;
            char choice;

            std::cout << "\n > Enter Username to Edit : ";
            std::cin.ignore();
            getline(std::cin, edit);

            std::fstream file(credentialsfile, std::ios::binary | std::ios::in | std::ios::out);
            if (!file) 
			{
                u1.setcolor(4);
                std::cout << " \a[ERROR] File Opening Error!\n";
                u1.setcolor(7);
				u1.pause();
                return;
            }

            while (file.read(reinterpret_cast<char*>(&c1), sizeof(c1))) 
			{
                if (edit == c1.username) 
				{
                    found = true;
                    std::cout << std::left
                               << "| " << std::setw(10) << "Role"
                               << "| " << std::setw(25) << "Username"
                               << "| " << std::setw(25) << "Password"
                               << "| " << std::setw(35) << "Email"
                               << "| " << std::setw(15) << "DOB" << "|\n";
                    std::cout << "====================================================================================================================\n";
                    std::cout << std::left
                               << "| " << std::setw(10) << c1.role
                               << "| " << std::setw(25) << c1.username
                               << "| " << std::setw(25) << c1.userpassword
                               << "| " << std::setw(35) << c1.email
                               << "| " << std::setw(15) << c1.dob << "|\n";

                    std::cout << "\n Do You Want to Modify? (Y/N) : ";
                    std::cin >> choice;

                    if (choice == 'y' || choice == 'Y') 
					{
                        credential c2;

                        std::cout << " > Enter New Role : ";
                        std::cin.ignore();
						std::cin.getline(c2.role, 10);
                        std::cout << " > Enter New Username : ";
						std::cin.getline(c2.username, 25);
                        std::cout << " > Enter New Password : ";
						std::cin.getline(c2.userpassword, 25);
                        std::cout << " > Enter New Email : ";
						std::cin.getline(c2.email, 25);
                        std::cout << " > Enter New DOB (DD/MM/YYYY) : ";
						std::cin.getline(c2.dob, 15);
                        file.seekp(-(int)sizeof(c1), std::ios::cur);
                        file.write(reinterpret_cast<const char*>(&c2), sizeof(c2));

                        u1.playSpinner(2, "Updating Database");
                        u1.clearscreen();
                        u1.setcolor(2);
                        std::cout << "\n [SUCCESS] Credential Updated Successfully!\n";
                        u1.pause();
                        u1.setcolor(07);
                    } 
					else 
					{
                        std::cout << " [OK] Returning Without Changes.\n";
                        u1.pause();
                    }

                    file.close();
                    return;
                }
            }

            file.close();

            if (!found) 
			{
                u1.setcolor(4);
                std::cout << " \a[ERROR] Username Not Found!\n";
                u1.setcolor(7);
				u1.pause();
            }
        }

        void delete_credentials() 
		{
            credential c1;
            bool found = false;
            std::string deluser;
            char confirm;

            std::cout << "\n > Enter Username to Delete : ";
            std::cin.ignore();
            getline(std::cin, deluser);

            std::cout << " Are you sure you want to delete [" << deluser << "]? (Y/N) : ";
            std::cin >> confirm;

            if (confirm == 'n' || confirm == 'N') 
			{
                std::cout << " [OK] Returning Without Deletion.\n";
                u1.pause();
                return;
            }

            std::ifstream copyfrom(credentialsfile, std::ios::binary);
            std::ofstream copyto("credtemp.dat", std::ios::binary);

            if (!copyfrom) 
			{
                u1.setcolor(4);
                std::cout << " \a[ERROR] File Opening Error!\n";
                u1.setcolor(7);
				u1.pause();
                return;
            }

            while (copyfrom.read(reinterpret_cast<char*>(&c1), sizeof(c1))) {
                if (deluser != c1.username) {
                    copyto.write(reinterpret_cast<const char*>(&c1), sizeof(c1));
                } else {
                    found = true;
                }
            }

            copyfrom.close();
            copyto.close();

            if (!found) 
			{
                remove("credtemp.dat");
                u1.setcolor(4);
                std::cout << " \a[ERROR] Username Not Found!\n";
                u1.setcolor(7);
				u1.pause();
                return;
            }

            remove(credentialsfile.c_str());
            rename("credtemp.dat", credentialsfile.c_str());

            u1.playSpinner(2, "Deleting Credential");
            u1.clearscreen();
            u1.setcolor(2);
            std::cout << "\n [DONE] Credential [" << deluser << "] Deleted Successfully!\n";
            u1.setcolor(7);
			u1.pause();
        }
		
};

//==========================================================
//		BILLING CLASS.(All Bill handling)
//========================================================== 

class Bill : public items
{
	private:
		std::vector<bill_struct> bills;
		std::string filename;
		bill_struct b1;
		std::string billing_user;
		std::string userrole;
		utils u1;
		item i1;
		double TOTAL = 0.0;
	public:
	
		Bill() {filename = getfilename();}
		
		void setbilling_user(std::string billing_user, std::string userrole){ this->billing_user = billing_user; this->userrole = userrole; }
		
		void showitem (item i1,int sr)												// <------------- View an Item.
		{
        		std::cout << std::left << "\n | " 	 << std::setw(5)  << sr << " | " 
                		   							 << std::setw(30) << i1.name << " | "
				<< std::fixed << std::setprecision(2)<< std::setw(10) << i1.sellprice << " | "
				<< std::fixed << std::setprecision(2)<< std::setw(10) << i1.amount << " | \n";

		}
		void showbill()
		{
			u1.setcolor(3);
			std::cout<<"\n\t\t                     	--------{ BILL }--------                        ";
			std::cout<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~+~~~~~~~+~~~~~~~~~~~~~+";
			std::cout<<"\n\t\t| Name                                 | Amount | Price |  Sub total  |";
			std::cout<<"\n\t\t+======================================+========+=======+=============+";
			TOTAL = 0.0;
			for(auto s : bills)
			{
				std::cout<<"\n\t\t "<<std::setw(40)<< s.name <<std::setw(9)<< s.amountbought <<std::setw(8)<<std::setprecision(0)<< s.sellprice <<std::setw(14)<< s.amountbought * s.sellprice ;
				TOTAL += (s.amountbought * s.sellprice);							// Total = Total + (s.amountbought * s.sellprice)
			}
			u1.setcolor(2);
			std::cout<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~~~~+";
			std::cout<<"\n\t\t| TOTAL BILL                                            |"<<std::setw(14)<<std::setprecision(2)<<TOTAL<<"|";
			std::cout<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~~~~+";
			u1.setcolor(7);
		}
	
		bill_struct getitem()
		{
			char findID[10];
			bool found = false;
			
			u1.clearscreen();
			
			std::cin.ignore();
			std::cout << "\n\t > Enter The ID of Item you want to ADD : ";
			std::cin.getline(findID, 10);
			
			std::ifstream file(filename, std::ios::in);
			
			while(file.read(reinterpret_cast<char*>(&i1), sizeof(i1)))
			{
				//std::cout<<"1\n";		//	<<===={ Un Comment If the loop is not working. }
				if(strcmp(findID, i1.ID) == 0)
				{
					char ch = '.';
					found = true;
					std::cout << "\n <===========================================[ Bill  ]=======================================================>\n\n";
					std::cout << "\n +-------+--------------------------------+------------+------------+";
    				std::cout << std::left << "\n"
    							<< " | "<< std::setw(5)  << " Sr."  
            		            << " | "<< std::setw(30) << " Name" 
            		            << " | "<< std::setw(10) << " Price"
								<< " | "<< std::setw(10) << " Inventory"  
            		            << " | ";
    				std::cout << "\n +=======+================================+============+============+";
					showitem(i1,1);
					std::cout << " +-------+--------------------------------+------------+------------+\n";
					
					do
					{
						std::cout << "\n\t > Do You want to Add the item in the Bill (Y/N) : ";
						std::cin  >> ch;
						
						if(ch == 'y' || ch == 'Y')
						{
							if(i1.amount > 0)
							{
								strcpy(b1.ID,i1.ID), b1.name = i1.name, b1.sellprice = i1.sellprice, b1.amountininv = i1.amount;
								do
								{
									int temp;
									do
									{
										temp = u1.getint("\n\t > Enter the Amount You want to Buy : ");
									}while(temp<=0);
									if(temp>=b1.amountininv)
									{
										u1.setcolor(4);
										std::cout<<"\n\t \a[ERROR] Not Enough in stock!";
										u1.setcolor(7);
									}
									else
									{
										b1.amountbought = temp;
										   bills.push_back(b1);
										return b1;
									}
								}while(true);
							} 
							else 
							{
								u1.setcolor(4);
								std::cout << " [WARNING] Out of Stock! \n";
								u1.setcolor(7);
								u1.pause();
							}
						}
						else if(ch == 'n' || ch == 'N')
						{
							std::cout << " [DONE] Moving Back.\n";
							u1.playSpinner(1,"Accessing Module.");
							u1.clearscreen();
						}
						else
						{
							u1.setcolor(4);
							std::cout << "\t \a[ERROR] Wrong Input.\n";
							u1.setcolor(7);
						}
					}
					while(true);
				}
			}
			file.close();
			
			if(!found) 
				{
					u1.setcolor(4);
        			std::cout << "\t \a[ERROR] ID not Found!\n";
        			u1.setcolor(7);
					u1.pause();
				}
			return b1;
		}
		void removeitem()
		{
			char findID[10];
			bool found = false;
			
			u1.clearscreen();
			
			if(bills.empty() == false)
			{
				showbill();	
			}
			
			std::cin.ignore();
			std::cout << "\n\t > Enter The ID of Item you want to REMOVE : ";
			std::cin.getline(findID, 10);
			
			std::vector<bill_struct>::iterator it;
			
			for(it=bills.begin() ; it!=bills.end() ; it++)
			{
				bill_struct s = *it;
				if(strcmp(findID, s.ID) == 0)
				{
					char ch ='.';
					found = true;
					std::cout<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~+~~~~~~~+~~~~~~~~~~~~~+";
					std::cout<<"\n\t\t| Name                                 |  QTY   | Price |  Sub total  |";
					std::cout<<"\n\t\t+======================================+========+=======+=============+";
					std::cout<<"\n\t\t "<<std::setw(40)<< s.name <<std::setw(9)<< s.amountbought <<std::setw(8)<<std::setprecision(0)<< s.sellprice <<std::setw(14)<< s.amountbought * s.sellprice ;
		
					do
					{
						std::cout<<"\n\t > Do you want to Delete this Item (Y/N) : ";
						std::cin >> ch;
						if(ch == 'y' || ch == 'Y')
						{
							u1.playSpinner(1,"Deleting the Item.");
							
							bills.erase(it);
							
							u1.setcolor(2);
							std::cout<<"\n\t [DONE] Item Succesfuly Deleted!";
							u1.setcolor(7);
							return ;
						}
						else if(ch == 'n' || ch == 'N')
						{
							u1.playSpinner(1,"Leaving Without Deletion.");
							break;
						}
						else
						{
							u1.setcolor(4);
							std::cout << "\t \a[ERROR] Wrong Input.\n";
							u1.setcolor(7);
						}
					}while(true);
					
				}
				
				
			}
			
			if(!found) 
			{
				u1.setcolor(4);
        		std::cout << "\t \a[ERROR] ID not Found!\n";
       			u1.setcolor(7);
				u1.pause();
				return;
			}
			
		}
		
		void generatebill()
		{
			int choice = -1;			
			TOTAL = 0.0;
			char ch='.';
			do
			{
				
				u1.clearscreen();
				if(bills.empty() == false)
				{
					showbill();	
				}
				std::cout<<"\n\n";
				std::cout<<"\n\t\t+======================================+";
				std::cout<<"\n\t\t|         BILLING OPTIONS              |";
				std::cout<<"\n\t\t+====+=================================+";
				std::cout<<"\n\t\t| 1. | Add Item into Bill.             |";
				std::cout<<"\n\t\t| 2. | Delete Item From the Bill.      |";
				std::cout<<"\n\t\t| 3. | Generate the Bill.              |";
				std::cout<<"\n\t\t+----+---------------------------------+";
				std::cout<<"\n\t\t| 0. | Go Back.                        |";
				std::cout<<"\n\t\t+----+---------------------------------+";
				
				choice = u1.getint("\n\t\t-----> ");
				switch(choice)
				{
					case 1:
						u1.playSpinner(1, "Getting Items Ready.");
						b1 = getitem();
						break;
					case 2:
						u1.playSpinner(1, "Fetching File.");
						removeitem();
						break;
					case 3:
						std::cin.ignore();
						std::cout<<"\n\t\t\a > Are you sure You want to Finalize the Bill (Y/N) : ";
						std::cin >> ch;
						if(ch == 'Y' || ch == 'y')
						{
							
							u1.playSpinner(1,"\t\tPreparing the Final Bill.");
							showfinalbill();
						}
						else if(ch == 'n' || ch == 'N')
						{
							break;
						}
						else
						{
							u1.setcolor(4);
							std::cout << "\t \a\a[ERROR] Wrong Input.\n";
							u1.setcolor(7);
							break;
						}
						break;
					case 0:
						bills.clear();
						TOTAL = 0.0;
						break;
					default:
						u1.setcolor(4);
						std::cout<<"\n\t \a\a[ERROR] Wrong Input!";
						u1.pause();
						u1.setcolor(7);
				}
			}
			while(choice != 0);
		}
		
		void showfinalbill()
		{
			u1.clearscreen();
			
			u1.setcolor(6);
			std::cout<<"\n\n";
			std::cout<<"\n\t\t***********************************************************************";
			std::cout<<"\n\t\t\t\t"<<shopowner;
			std::cout<<"\n\t\t***********************************************************************\n";
			std::cout<<"\n\t\tBilled By : "<<billing_user<<"\t\t\t\t\t\t- "<<userrole;
			showbill();
			u1.setcolor(6);
			std::cout<<"\n";
			std::cout<<"\n\t\t***********************************************************************";
			std::cout<<"\n\t\t                      THANK YOU! FOR SHOPPING                           ";
			std::cout<<"\n\t\t***********************************************************************\n\n";
			u1.setcolor(6);
			std::cout<<"\n\t\t > Press Any key to Print receipt (0 to return) : ";
			char ch ='.';
			ch = getch();
			if(ch=='0') { return; }
			
			u1.playSpinner(1,"\t\t\tGenerating Receipt.                                      ");
			billreceipt();
			bills.clear();
			TOTAL = 0.0;
			u1.pause();
			
			return;
			
		}
		
		void filesedit()
		{
				int sr = 1;
				item i1;
				bool found = false;
				char findID[10],choice,attchoice;
    			std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
			
    		if(!file) 
			{
    			u1.setcolor(4);
        		std::cout << "\t \a\a[ERROR] Couldn't Update Inventory!\n";
        		u1.setcolor(7);
				u1.pause();
       			return;
    		}


    		for(auto s : bills)
    		{
    			while(file.read(reinterpret_cast<char*>(&i1), sizeof(i1))) 
				{

					//	std::cout << "Comparing with: [" << i1.ID << "]\n";				//<-----------( If the loop doesn't work. Check By un-commenting this Line . It will tell you the flow of loop and point of termination . Making Debugging Easier. Don't ask how I Came up with this. It brings Back Harsh Memmories. 

					if(strcmp(s.ID, i1.ID) == 0)
					{
						i1.amount = i1.amount - s.amountbought;
					
						file.seekp(-(int)sizeof(i1) , std::ios::cur);
						file.write(reinterpret_cast<const char*>(&i1), sizeof(i1));
						break;		
					}
				}
			}
			file.close();
		}
		
		void billreceipt()
		{
			std::ofstream file("Recipt.txt");
			
			if(!file)
    		{
        		u1.setcolor(4);
        		std::cout << "\n\t\t\a \a[ERROR] Could not generate receipt!\n";
        		u1.setcolor(7);
        		return;
    		}
    		
    		file<<"\n\t\t***********************************************************************";
			file<<"\n\t\t\t\t"<<shopowner;
			file<<"\n\t\t***********************************************************************\n";
			file<<"\n\t\tBilled By : "<<billing_user<<"\t\t\t\t\t\t- "<<userrole;
			file<<"\n\t\t                    ------{ BILL RECEIPT }------                      ";
			file<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~+~~~~~~~+~~~~~~~~~~~~~+";
			file<<"\n\t\t| Name                                 |   QTY  | Price |  Sub total  |";
			file<<"\n\t\t+======================================+========+=======+=============+";
			for(auto s : bills)
			{
				file<<"\n\t\t "<<std::left<<std::setw(40)<< s.name <<std::setw(9)<< s.amountbought <<std::setw(8)<< s.sellprice <<std::setw(14)<< s.amountbought * s.sellprice ;
			}
			file<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~~~+";
			file<<"\n\t\t| TOTAL BILL                                            |"<<std::setw(13)<<TOTAL<<"|";
			file<<"\n\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~~~+";
			file<<"\n";
			file<<"\n\t\t***********************************************************************";
			file<<"\n\t\t                      THANK YOU! FOR SHOPPING                           ";
			file<<"\n\t\t***********************************************************************\n\n";
			
			filesedit();
    		
		}
		
		
};

//==========================================================
//		LOGIC CLASS.(For handling Main Menu and Inputs)
//========================================================== 

class logic
{
	private:
		user* currentuser;
		std::string currentrole = "UNKNOWN";
		std::string username = "";
	public:
		utils u1;
		Bill b1;
		
		logic(std::string currentrole,std::string username)
		{ 
			this->currentrole = currentrole; 
			this->username = username;
			setuser(); 
		}
		
		void setuser()
		{
			if(currentrole == "ADMIN")
			{
				currentuser = new admin;
			}
			else
			{
				currentuser = new employee;
			}
		}
		int mainmenu(std::string userrole)
		{	
			u1.clearscreen();
			
			int choice=-1;
			std::cout<<"\t\nSelect the Menu\n";
			std::cout<<"_______________________________________\n\n";
			std::cout<<"  +===========================================+\n";
			std::cout<<"  |                MAIN MENU                  |\n";
			std::cout<<"  +===========================================+\n";
			std::cout<<"  | 1. |   View All Item in Inventory.        |\n";
			std::cout<<"  | 2. |   Generate a Bill.                   |\n";
			std::cout<<"  +----+--------------------------------------+\n";
			
			if(currentrole == "ADMIN")
			{
			std::cout<<"  | 3. |    Add a new Item in Inventory.      |\n";
			std::cout<<"  | 4. |    Edit an Existing Item.            |\n";
			std::cout<<"  | 5. |    Remove an Item.                   |\n";
			std::cout<<"  +----+--------------------------------------+\n";
			}
			  
			std::cout<<"  | 9. |    Go back to login.                 |\n";
			std::cout<<"  | 0. |    Exit the Software.                |\n";
			std::cout<<"  +----+--------------------------------------+\n";
			choice = u1.getint("-->");

				switch(choice)
				{
					case 1:
						u1.clearscreen();
						std::cout<<"+--------------------------------------------------------+\n";
						std::cout<<"| [VIEW] Preparing to View Items in The Inventory.       |\n";
						std::cout<<"+--------------------------------------------------------+\n";
						u1.playSpinner(5,"Fetching Data");
						u1.clearscreen();
						currentuser->showall();
						u1.setcolor(7);
						break;
					case 2:
						u1.clearscreen();
						std::cout<<"+--------------------------------------------------------+\n";
						std::cout<<"| 2. | [BILL] Generate a Bill.                           |\n";
						std::cout<<"+--------------------------------------------------------+\n";
						u1.playSpinner(1," > Getting Ready");
						u1.clearscreen();
						b1.setbilling_user(username, currentrole);
						b1.generatebill();
						u1.setcolor(7);
						break;	
					case 3:
						if(currentrole == "ADMIN") 
						{
							u1.clearscreen();
							std::cout<<"+--------------------------------------------------------+\n";
							std::cout<<"| [ADDING] Preparing to Add a new Item in The Inventory. |\n";
							std::cout<<"+--------------------------------------------------------+\n";
							u1.playSpinner(3," > Getting Ready");
							u1.clearscreen();
							currentuser->additem();
							u1.setcolor(7);
						}
						else
						{
							std::cout<<" \a[ERROR] Wrong Input.!\n";
						}
						break;
					case 4:
						if(currentrole == "ADMIN") 
						{
							u1.clearscreen();
							std::cout<<"+------------------------------------------------------------+\n";
							std::cout<<"| [EDITING] Preparing to Modify a new Item in The Inventory. |\n";
							std::cout<<"+------------------------------------------------------------+\n";
							u1.playSpinner(4," > Fetching Data From Hard Drive.");
							u1.setcolor(07); 
							u1.clearscreen();
							currentuser->modifyitem();
							u1.setcolor(07); 
						}
						else
						{
							std::cout<<" \a[ERROR] Wrong Input.!\n";
						}
						break;
					case 5:
						if(currentrole == "ADMIN") 
						{
							u1.clearscreen();
							std::cout<<"+------------------------------------------------------------+\n";
							std::cout<<"| [DELETING] Preparing to Delete an Item from the Inventory. |\n";
							std::cout<<"+------------------------------------------------------------+\n";
							u1.playSpinner(4," > Checking User's Permissions.");
							u1.setcolor(07);
							u1.clearscreen();    
							currentuser->deleteitem();
							u1.setcolor(07);
						}
						else
						{
							u1.setcolor(4);
							std::cout<<" \a[ERROR] Wrong Input.!\n";
							u1.setcolor(7);
						}
						break;
					case 9:
						u1.playSpinner(2," >  [LOGOUT]  LOGING OUT  .....");
						break;
					case 0:
						u1.setcolor(3);
						std::cout<<" [EXITING] ..... \n";
						break;
					default:
						u1.setcolor(4);
						std::cout<<" \a[ERROR] Wrong Input.!\n";
						u1.setcolor(7);
				}
				return choice;
		}
};

//==========================================================
//		THE MAIN FUCNTION.
//==========================================================

int main()
{
	int choice;
	std::string userrole = "UNKNOWN";
	std::string username = "UNKNOWN";
	
	//	_____________________________________________________________________________________
	//		Instantiating All the Classes. / Creating the Objects of Neccassary Classes
	Auth login;
	adminstration superadmin;
	
	do
	{
		
		userrole = login.authenticate();
		username = login.getusername();
		if(userrole == "EMPLOYEE" || userrole == "ADMIN")
		{
			logic l1(userrole,username); 
			do
			{
				choice = l1.mainmenu(userrole);
			}
			while(choice != 0 && choice != 9);
			
			if(choice == 9)
			{
				userrole = "UNKNOWN";
			}
			else
			{
				break;
			}
			
		}
		else if(userrole == "SUPERADMIN")
		{
			userrole = superadmin.credentialcontrol();
		}
		
	}
	while(userrole == "UNKNOWN");
	

}