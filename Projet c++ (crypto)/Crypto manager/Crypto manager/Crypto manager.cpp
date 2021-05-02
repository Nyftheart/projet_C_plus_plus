//***************************************************************
//                  librairie
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//                   class du projet
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//information de l'utilisateur
	void show_account() const;	//affichage des comptes
	void modify();	//modification des comptes
	void dep(int);	//modification de la somme du compte
	void draw(int);	//test de la somme
	void report() const;	//mise en forme des info
	int retacno() const;	//retour du numéro de compte
	int retdeposit() const;	//retour de la somme du compte
	char rettype() const;	//retour la crypto
};

void account::create_account()
{
	cout << "\nEntrez le compte No. :";
	cin >> acno;
	cout << "\n\nEntrez le nom du propriétaire : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter Type de compte (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter Entrez un montant initiale(>=500 pour épargne et >=1000 pour courant ) : ";
	cin >> deposit;
	cout << "\n\n\nCompte crée.";
}

void account::show_account() const
{
	cout << "\nCompte No. : " << acno;
	cout << "\nNom du propriétaire du compte : ";
	cout << name;
	cout << "\nType de compte : " << type;
	cout << "\nBalance : " << deposit;
}


void account::modify()
{
	cout << "\nComptee No. : " << acno;
	cout << "\nModifier le proriétaire du compte : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModifier type de compte : ";
	cin >> type;
	type = toupper(type);
	cout << "\nModifier Balance : ";
	cin >> deposit;
}


void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
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
//    		fontion de mise en place
//****************************************************************
void write_account();	//enregistrement du compte
void display_sp(int);	//détaille réduit
void modify_account(int);	//modification 
void delete_account(int);	// supprétion
void display_all();		// fontion détaille du compte
void deposit_withdraw(int, int); //fontion ajout ou retraie
void intro();	//ecran titre

//***************************************************************
//				corp du programe
//****************************************************************


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tMENU PRINCIPAL";
		cout << "\n\n\t01. NOUVEAU COMPTE";
		cout << "\n\n\t02. DEPOSER MONTANT";
		cout << "\n\n\t03. RETIRER MONTANT";
		cout << "\n\n\t04. VOIR BALANCE";
		cout << "\n\n\t05. VOIR COMPTES";
		cout << "\n\n\t06. FERMER UN COMPTE";
		cout << "\n\n\t07. MODIFIER UN COMPTE";
		cout << "\n\n\t08. SORTIE";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tEntrer le compte No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEntrer le compte No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEntrer le compte No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEntrer le compte No. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tEntrer le compte No. : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\tMerci d'utiliser nos services";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}


//***************************************************************
//    	Lecture de fichier 
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	Lecture de ligne spesifique
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Le fichier n'a pas pu être ouvert ! Appuyez pour continuer...";
		return;
	}
	cout << "\nDETAILS COMPTE\n";

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nCe compte n'existe pas.";
}


//***************************************************************
//    	modification du fichier
//****************************************************************

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Le fichier n'a pas pu être ouvert ! Appuyez pour continuer...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nEntrez les nouveaux paramètres du compte" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Mis à jour";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Fichier introuvable. ";
}

//***************************************************************
//    	suppression d'une ligne
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Le fichier n'a pas pu être ouvert ! Appuyez pour continuer...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tSupprimé.";
}

//***************************************************************
//    	affichage du fichier
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Le fichier n'a pas pu être ouvert ! Appuyez pour continuer...";
		return;
	}
	cout << "\n\n\t\tPROPRIETAIRES COMPTES\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	retiré ou déposer sur un compte
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Le fichier n'a pas pu être ouvert ! Appuyez pour continuer...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tDEPOSER UN MONTANT ";
				cout << "\n\nEntrez un montant à déposer";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tRETIRER UN MONTANT ";
				cout << "\n\nEntrez un montant à retirer";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Fonds insuffisant.";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Mis à jour.";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Fichier introuvable. ";
}


//***************************************************************
//    	page t'entette
//****************************************************************


void intro()
{
	cout << "\n\n\n\t  CRYPTO";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cout << "\n\n\n\nFAIT PAR : Alexandre Kramer / Yann Henno";
	cout << "\n\nECOLE : Pour ynov";
	cin.get();
}

//***************************************************************
//    			fin projet
//***************************************************************
