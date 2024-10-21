#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct BOOKSTAT
{
	string TITLE;
	int GENRE = 0, QTY = 0;
	double PRICE = 0;
};

void ADD(BOOKSTAT tempBOOK[], int INDEX);
void DELETE(BOOKSTAT tempBOOK[], int INDEX);
void SALES(BOOKSTAT tempBOOK[]);
void DISPLAY(BOOKSTAT tempBOOK[], int INDEX);
void SALE_SUMMARY();
void UPDATE_ARRAY(BOOKSTAT tempBOOK[]);
void UPDATE_TXT(BOOKSTAT tempBOOK[]);
int GENRE_ASSIGN();
int VALID_CODE();
double VALID_CASH();
int INVALID_66();	//use at (if) in menu, standardise invalid input(for easier coding), give warning
int END_77();	//use in looping to ask if want to continue

const string GENRE_LIBRARY[9] = { "MEDIEVEL", "MYSTERY", "ROMANCE", "HORROR", "ACTION", "FANTASY", "COMEDY", "SPORTS", "SCI-FI"};

int main()
{
	BOOKSTAT BOOKLIST[100];
	int inputMenu;

	UPDATE_ARRAY(BOOKLIST);

	do
	{
		cout << "=============================================================================================\n\n";
		cout << "[1]Add" << setw(16) << "[2]Edit List" << setw(16) << "[3]Search" << endl //MENU MAIN
			<< "[4]Sale" << setw(18) << "[5]Sale Summary" << setw(18) << "[6]Display All" << endl
			<< "[99]Close" << endl
			<< "\nSelect application to be used by entering the corresponding number: ";
		cin >> inputMenu;
		cout << endl << "=============================================================================================\n\n";

		if (inputMenu == 1)
		{
			int inputAdd;

			cout << "[1]Renew List" << setw(27) << "[2]Add to Existing List" << endl //MENU ADD
				<< "[88]Home" << endl;

			do
			{
				cin >> inputAdd;
				cout << endl;

				if (inputAdd == 1)
				{
					int startPoint, END = 551;

					for(startPoint = 0; END != 77 && startPoint < 100; startPoint++) //startPoint 0 to make new list
					{
						ADD(BOOKLIST, startPoint);
						END = END_77();
					}

					for (startPoint; startPoint < 100; startPoint++) //deletes data after end, since this is create new list
					{
						DELETE(BOOKLIST, startPoint);
					}

					UPDATE_TXT(BOOKLIST);
				}
				else if (inputAdd == 2)
				{
					int END = 551;
					for(int startPoint = 0; END != 77 && startPoint != 100; startPoint++)
					{
						if (BOOKLIST[startPoint].TITLE == "") //if data exist, don't execute, only execute if empty
						{
							ADD(BOOKLIST, startPoint);	//startPoint is now at index w/ empty data
							END = END_77();
						}
					}
					UPDATE_TXT(BOOKLIST);
				}
				else if (inputAdd == 88)
				{
					break; //breaks if, do while terminates cause 88 != 66
				}
				else
				{
					inputAdd = INVALID_66();	//standardise invalid input for easier code
				}
			} while (inputAdd == 66);
		}
		else if (inputMenu == 2)
		{
			cout << "CODE/TITLE/GENRE/QTY/PRICE:\n\n";
			for (int index = 0; index < 100; index++)
			{
				if (BOOKLIST[index].TITLE != "") //if not empty, execute
				{
					DISPLAY(BOOKLIST, index);
				}
			}

			cout << "####################-End of List-####################\n\n";

			int inputEdit;

			cout << "[1]Edit Book Info" << setw(27) << "[2]Delete Book" << endl //MENU EDIT
				<< "[88]Home" << endl;

			do
			{
				cin >> inputEdit;
				cout << endl;

				if (inputEdit == 1)
				{
					int codeInput = VALID_CODE();
					ADD(BOOKLIST, codeInput);		//use ADD function, it will overwrite existing data
					cout << "\nEdit Book Info successful!\n\n";

					UPDATE_TXT(BOOKLIST);
				}
				else if (inputEdit == 2)
				{
					int codeInput = VALID_CODE();
					DELETE(BOOKLIST, codeInput);
					cout << "Delete Book successful!\n\n";

					UPDATE_TXT(BOOKLIST);
				}
				else if (inputEdit == 88)
				{
					break;
				}
				else
				{
					inputEdit = INVALID_66();
				}

			} while (inputEdit == 66);
		}
		else if (inputMenu == 3)
		{
			int inputSearch;

			cout << "Search by:" << endl
				<< endl
				<< "[1]Title" << setw(27) << "[2]Genre" << endl //MENU SEARCH
				<< "[88]Home" << endl;
			do
			{
				cin >> inputSearch;
				cout << endl;

				if (inputSearch == 1)
				{
					string SEARCH_THIS, SEARCH_COMPARE;

					cout << "Search Title: ";		//get the title to be searched
					cin.ignore();
					getline(cin, SEARCH_THIS);

					cout << "\nCODE/TITLE/GENRE/QTY/PRICE:\n\n";

					for (int x = 0; x < SEARCH_THIS.length(); x++) //standardise to all caps, easy to compare this way
					{
						SEARCH_THIS[x] = toupper(SEARCH_THIS[x]);
					}

					for (int index = 0; index < 100; index++)	//compare each title
					{
						SEARCH_COMPARE = BOOKLIST[index].TITLE;

						for (int x = 0; x < SEARCH_COMPARE.length(); x++) //standardise to all caps
						{
							SEARCH_COMPARE[x] = toupper(SEARCH_COMPARE[x]);
						}

						if (SEARCH_THIS == SEARCH_COMPARE)		//if same, then display
						{										//if not, skip and f(x) will loop next
							DISPLAY(BOOKLIST, index);
						}
					}
					cout << "####################-Search finished-####################\n\n";
				}
				else if (inputSearch == 2)
				{
					int SEARCH_THIS;

					cin.ignore();					//GENRE_ASSIGN will get input in string and 
					SEARCH_THIS = GENRE_ASSIGN();	//give corresponding genre code to be searched

					cout << "\nCODE/TITLE/GENRE/QTY/PRICE:\n\n";

					for (int index = 0; index < 100; index++)
					{
						if (SEARCH_THIS == BOOKLIST[index].GENRE)
						{
							DISPLAY(BOOKLIST, index);
						}
					}
					cout << "####################-Search finished-####################\n\n";
				}
				else if (inputSearch == 88)
				{
					break;
				}
				else
				{
					inputSearch = INVALID_66();
				}

			} while (inputSearch == 66);
		}
		else if (inputMenu == 4)
		{
			SALES(BOOKLIST);
			UPDATE_TXT(BOOKLIST);
		}
		else if (inputMenu == 5)
		{
			cout << "Sale summary:\n\n";
			SALE_SUMMARY();
		}
		else if (inputMenu == 6)
		{
			cout << "CODE/TITLE/GENRE/QTY/PRICE:\n\n";
			for (int index = 0; index != 100; index++) //goes through whole array
			{
				if (BOOKLIST[index].TITLE != "") //if not empty, execute
				{
					DISPLAY(BOOKLIST, index);
					//cout << endl << endl;
				}
			}
			cout << "####################-End of List-####################\n\n";
		}
		else if(inputMenu == 99)
		{
			break;
			//to accepts as valid
		}
		else
		{
			cout << "Invalid input!\n\n";
		}

	} while (inputMenu != 99);

	UPDATE_TXT(BOOKLIST);

	return 0;
}

//manipulates struct at given index
void ADD(BOOKSTAT tempBOOK[], int INDEX) 
{
	cout << "Code: ";
	INDEX <= 9 ? cout << 0 << INDEX : cout << INDEX; //Standardise the book code to have two integers displayed

	cout << endl << "Title: ";	//get title
	cin.ignore();
	getline(cin, tempBOOK[INDEX].TITLE);

	tempBOOK[INDEX].GENRE = GENRE_ASSIGN();	//assign correct genre code

	do
	{
		cout << "Quantity: ";		//get quantity
		cin >> tempBOOK[INDEX].QTY;
		if (tempBOOK[INDEX].QTY <= 0)
		{
			cout << "You can't have less than one quantity of an item\nRe-enter ";
		}
	} while (tempBOOK[INDEX].QTY <= 0);

		cout << "Price: ";
		tempBOOK[INDEX].PRICE = VALID_CASH();	//gets a vaild price
}

//deletes struct at given index
void DELETE(BOOKSTAT tempBOOK[], int INDEX)
{
	tempBOOK[INDEX].TITLE = "";
	tempBOOK[INDEX].GENRE = 0;
	tempBOOK[INDEX].QTY = 0;
	tempBOOK[INDEX].PRICE = 0;
}

//get item bought, calc money, update qty and numOfCust
void SALES(BOOKSTAT tempBOOK[])
{
	char line[100];
	int CODE, END, qtyBought, trash_totalCashIn, numOfCust = 0;
	double TOTAL = 0, PAID;
	ofstream outfile;
	ifstream infile;

	infile.open("transaction_history.txt", ios::in);
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			infile >> numOfCust >> trash_totalCashIn;
		}
	}
	else
	{
		//numOfCust is default at 0
	}
	infile.close();

	numOfCust++;

	do
	{
		cout << "CODE/TITLE/GENRE/QTY/PRICE:\n\n";	//is to display all books
		for (int index = 0; index != 100; index++) //goes through whole array
		{
			if (tempBOOK[index].TITLE != "") //if not empty, execute
			{
				DISPLAY(tempBOOK, index);
			}
		}
		cout << "####################-End of List-####################\n\nEnter the book to be bought based on it's book code\n";

		do
		{
			CODE = VALID_CODE();

			if (tempBOOK[CODE].QTY == 0)
			{
				cout << "The book is either not available or already sold out! Please re-check the code for the book you're entering\n";
			}

		} while (tempBOOK[CODE].QTY == 0); //checks availability of book based on book code

		do
		{
			cout << "Quantity: ";
			cin >> qtyBought;

			if (qtyBought <= 0) //message user about wrong input for quantity being bought
			{
				cout << "You entered an illogical quantity of books being bought. Re-enter ";
			}
			else if (qtyBought > tempBOOK[CODE].QTY)
			{
				cout << "You entered more than available quantity of books being bought. Re-enter ";
			}

		} while (qtyBought <= 0 || qtyBought > tempBOOK[CODE].QTY); //if either one true - loop, checks availability amount being bought

		outfile.open("receipt_customer_" + to_string(numOfCust) + ".txt", ios::app);	//write to receipt
		outfile << tempBOOK[CODE].TITLE << setw(4) << "x" << qtyBought << setw(8) << "RM" << qtyBought * tempBOOK[CODE].PRICE << endl;
		outfile.close();

		tempBOOK[CODE].QTY = tempBOOK[CODE].QTY - qtyBought; //update that book's qty after being bought
		TOTAL += (qtyBought * tempBOOK[CODE].PRICE);		//totals up all purchase

		END = END_77();
	} while (END != 77); //asks if there is more

	cout << "##################################################################################\n\n";

	infile.open("receipt_customer_" + to_string(numOfCust) + ".txt", ios::in);	//display all bought item
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			infile.getline(line, 100);
			cout << line << endl;
		}
	}
	infile.close();

	cout << "Total: RM" << TOTAL << endl;	//here starts payment
	do
	{
		cout << "Paid amount: RM";
		cin >> PAID;
		if (PAID < TOTAL)
		{
			cout << "The paid amount is not enough\nRe-enter ";
		}
	} while (PAID < TOTAL);		//checks if paid is enough
	cout << "Change: RM" << PAID - TOTAL;

	cout << "\n\nPlease refer to receipt_customer_" + to_string(numOfCust) + ".txt to print receipt";

	cout << "\n\n##################################################################################\n\n";

	outfile.open("receipt_customer_" + to_string(numOfCust) + ".txt", ios::app);
	outfile << "\nTotal: RM" << TOTAL << "\nPaid: RM" << PAID << "\nChange: RM" << PAID - TOTAL;
	outfile.close();

	outfile.open("transaction_history.txt", ios::app); //saves transaction history
	outfile << numOfCust << " " << TOTAL << endl;
	outfile.close();
}

void DISPLAY(BOOKSTAT tempBOOK[], int INDEX)
{
	INDEX <= 9 ? cout << 0 << INDEX : cout << INDEX; //Standardise the book code to have two integers displayed
	cout << "/" << tempBOOK[INDEX].TITLE << "/" << GENRE_LIBRARY[tempBOOK[INDEX].GENRE] << "/" << tempBOOK[INDEX].QTY << "-Units/RM" << tempBOOK[INDEX].PRICE << endl << endl;
}

void SALE_SUMMARY()
{
	int temp_numOfCust = 0, DELETE;
	double temp_totalCashIn, TOTAL_SALE = 0;
	ifstream infile;
	ofstream outfile;

	infile.open("transaction_history.txt", ios::in);
	if (infile)
	{
		cout << "Customer" << setw(20) << "Total Bought\n\n";

		while (infile >> temp_numOfCust >> temp_totalCashIn)
		{
			cout << temp_numOfCust << setw(15) << "RM" << temp_totalCashIn << endl;

			TOTAL_SALE += temp_totalCashIn;
		}
	}
	infile.close();

	if (temp_numOfCust < 1)
	{
		cout << "There is no sale as of now\n";
	}
	else
	{
		cout << "\nTotal Sale as of now is RM" << TOTAL_SALE << "\n\nEnter [123] to delete this data, otherwise enter any other number\nInput: ";
		cin >> DELETE;

		if (DELETE == 123)
		{
			outfile.open("transaction_history.txt", ios::out);
			outfile << "";
			outfile.close();

			for (int x = 1; x <= temp_numOfCust; x++)
			{
				outfile.open("receipt_customer_" + to_string(x) + ".txt", ios::out);
				outfile << "";
				outfile.close();
			}

			cout << "\nData deleted\n";
		}
	}
	cout << endl;
}

void UPDATE_ARRAY(BOOKSTAT tempBOOK[])
{
	ifstream infile;

	infile.open("list_title.txt", ios::in);
	if (infile.is_open())
	{
		for (int index = 0; index < 100; index++)
		{
			getline(infile, tempBOOK[index].TITLE);
		}
	}
	infile.close();

	infile.open("list_genre_qty_price.txt", ios::in);
	if (infile.is_open())
	{
		for (int index = 0; index < 100; index++)
		{
			infile >> tempBOOK[index].GENRE >> tempBOOK[index].QTY >> tempBOOK[index].PRICE;
		}
	}
	infile.close();
}

void UPDATE_TXT(BOOKSTAT tempBOOK[])
{
	ofstream outfile;

	outfile.open("list_title.txt", ios::out);
	for (int index = 0; index < 100; index++)
	{
		outfile << tempBOOK[index].TITLE << endl;
	}
	outfile.close();

	outfile.open("list_genre_qty_price.txt", ios::out);
	for (int index = 0; index < 100; index++)
	{
		outfile << tempBOOK[index].GENRE << " " << tempBOOK[index].QTY << " " << tempBOOK[index].PRICE << endl;
	}
	outfile.close();

	outfile.open("ITEM_LIST.txt", ios::out);
	for (int index = 0; index < 100; index++)
	{
		outfile << tempBOOK[index].TITLE << "/" << GENRE_LIBRARY[tempBOOK[index].GENRE] << "/" << tempBOOK[index].QTY << "-units/RM " << tempBOOK[index].PRICE << endl << endl;
	}
	outfile.close();
}

int GENRE_ASSIGN()
{
	int tempGENRE;
	
	cout << "Genre: [0]MEDIEVEL [1]MYSTERY [2]ROMANCE [3]HORROR [4]ACTION [5]FANTASY [6]COMEDY [7]SPORTS [8]SCI-FI\n\nEnter genre based on number: ";
	cin >> tempGENRE;

	return tempGENRE;
}

//get input for code, checks code if between 0-99, if not invalid and loop
int VALID_CODE()
{
	int CODE_INPUT;

	do
	{
		cout << "Enter book code: ";
		cin >> CODE_INPUT;
		cout << endl;

		if (CODE_INPUT < 0 || CODE_INPUT > 99)
		{
			cout << "Invalid code! Re-enter book code\n";
		}

	} while (CODE_INPUT < 0 || CODE_INPUT > 99); //if either one is true, loop

	return CODE_INPUT;
}

//get input for money, checks if money logic
double VALID_CASH()
{
	double tempCASH;

	do
	{
		cout << "RM";
		cin >> tempCASH;
		if (tempCASH <= 0)
		{
			cout << "Invalid value\nRe-enter: ";
		}
	} while (tempCASH <= 0);

	return tempCASH;
}

//use at if in menu, standardise invalid input(for easier coding), give warning
int INVALID_66()
{
	int tempINPUT;
	tempINPUT = 66; //standardise for invalid to loop
	cout << "Invalid input! Re-enter input: ";
	return tempINPUT;
}

//use in looping to ask if want to continue
int END_77()
{
	int END;
	cout << "Enter [77] to end, otherwise enter any number to continue: ";
	cin >> END;
	cout << endl;
	return END;
}