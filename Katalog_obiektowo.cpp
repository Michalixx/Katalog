#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <winbase.h>

using namespace std;

string rekordy[10000][5]; // 0 numer 1 kolor 2 rozmiar 3 stan 4 miejsce
int i = 0;



void Start()
{
	string user;
	cout << "Podaj swoj identyfikator: ";
	cin >> user;
	fstream log;
	log.open("log.txt", ios::out | ios::app);
	SYSTEMTIME st;
    GetSystemTime(&st);
	log << "Uzytkownik: " << user << " Data: " << st.wDay << "." << st.wMonth << "." << st.wYear << "  " << st.wHour+1 << ":" << st.wMinute << endl;
	log.close();
}

void AddLogI(int S)
{
	fstream log;
	log.open("log.txt", ios::out | ios::app);
	log << S << endl;
	log.close();
}


void AddLogS(string S)
{
	fstream log;
	log.open("log.txt", ios::out | ios::app);
	log << S << endl;
	log.close();
}

void OdczytZPliku()
{
	fstream plik;
	plik.open("katalog.txt");
		while(!plik.eof())
		{
			plik >> rekordy[i][0];
			plik >> rekordy[i][1]; 
			plik >> rekordy[i][2];
			plik >> rekordy[i][3];
			plik >> rekordy[i][4];
			i++;
		}
	plik.close();
}

void Zapisz()
{
		ofstream zapis;
				zapis.open("katalog.txt");
				for(int j = 0; j < i; j++)
					{
						zapis << rekordy[j][0] << "  ";
						zapis << rekordy[j][1] << "  "; 
						zapis << rekordy[j][2] << "  ";
						zapis << rekordy[j][3] << "  ";
						zapis << rekordy[j][4];
						if(j < i-1) zapis << endl;
						else;
					}
					zapis.close();
				return;}

string IntToString(int a)
{
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

void WyswietlRekord(int z)
{
	cout << rekordy[z][0] << "   " << rekordy[z][1] << "   " << rekordy[z][2] << "   "  << rekordy[z][3] << "   " << rekordy[z][4] << endl;
}

void WyswietlStan()
{
	system("cls");
	cout << "NUMER   KOLOR   ROZMIAR   STAN   MIEJSCE" << endl;
	for (int q = 0; q < i; q++)
	{
		WyswietlRekord(q);
	}
	system("pause");
}

void WyszukajNumer(string numer)
{
	for (int q = 0; q < i; q++)
	{
		if(numer == rekordy[q][0])
		{
			WyswietlRekord(q);
		}
	}
}

void WyszukajRozmiar(string rozmiar)
{
	for (int q = 0; q < i; q++)
	{
		if(rozmiar == rekordy[q][2])
		{
			WyswietlRekord(q);
		}
	}
}

void WyszukajMiejsce(string miejsce)
{
	for (int q = 0; q < i; q++)
	{
		if (miejsce == rekordy[q][4]) WyswietlRekord(q);
	}
}

void WyszukajNumerKolor(string numer, string kolor)
{
		for (int q = 0; q < i; q++)
	{
		if(numer == rekordy[q][0] && kolor == rekordy[q][1])
		{
			WyswietlRekord(q);
		}
	}
}

void WyszukiwarkaMenu()
{
	system("cls");
	cout << "1. Wyszukaj po numerze" << endl;
	cout << "2. Wyszukaj po rozmiarze" << endl;
	cout << "3. Wyszukaj po miejscu" << endl;
	cout << "4. Wyszukaj po numerze i kolorze" << endl;
	int a;
	cin >> a;
	AddLogI(a);
	if (a != 1 && a!=2 && a!=3 && a!=4) return;
	cout << "Wpisz wyszukiwana fraze: ";
	string wysz;
	string wysz1;
	cin >> wysz;
	AddLogS(wysz);
	if (a == 4) 
	{
	cin >> wysz1;
	AddLogS(wysz1);
}
	switch(a)
	{
		case 1: WyszukajNumer(wysz);
			break;
		case 2: WyszukajRozmiar(wysz);
			break;
		case 3: WyszukajMiejsce(wysz);
			break;
		case 4: WyszukajNumerKolor(wysz, wysz1); break;
		default: cout << "blad" << endl;
	}
	system("pause");
}

void ZmianaStanu()
{
	system("cls");
	string numer, kolor, rozmiar;
	cout << "Podaj numer: ";
	cin >> numer;
	AddLogS(numer);
	cout << "Podaj kolor: ";
	cin >> kolor;
	AddLogS(kolor);
	cout << "Podaj rozmiar: ";
	cin >> rozmiar;
	AddLogS(rozmiar);
	bool test = false;
	for (int t = 0; t < i; t++)
	{
		if(numer == rekordy[t][0] && rekordy[t][1] == kolor && rozmiar == rekordy[t][2])
		{
			test = true;
			cout << "Oto znaleziony rekord:" << endl;
			WyswietlRekord(t);
			cout << "1. Dodaj stan\n2. Zmniejsz stan" << endl;
			int q;
			cin >> q;
			AddLogI(q);
			int stan = atoi(rekordy[t][3].c_str());
			if(q == 1)
			{
				cout << "Ile dodac?" << endl;
				int ile;
				cin >> ile;
				AddLogI(ile);
				stan += ile;
				rekordy[t][3] = IntToString(stan); // STRING TO INT
				cout << "Dodanie powiodlo sie" << endl;
			 }
			 else if (q == 2)
			 {
			 	cout << "Ile odjac?" << endl;
			 	int ile;
			 	cin >> ile;
			 	AddLogI(ile);
			 	if (ile <= stan)
			 	{
			 		stan -= ile;
			 		rekordy[t][3] = IntToString(stan);
			 		cout << "Odjecie powiodlo sie" << endl;
				 }
				 else 
				 {
				 	cout << "Operacja nie powiodla sie. Podana ilosc jest wieksza od aktualnego stanu produktu" << endl;
				 }
			  } 
			  else 
			  {
			  	cout << "Wybrano nieistniejaca wartosc" << endl;
			  }
			  t=i;
		}
	}
	if (!test) cout << "Nie znaleziono rekordu o podanych parametrach" << endl;
	Zapisz(); system("pause");
}

void DodajRekord()
{
	system("cls");
	string numer, kolor, rozmiar, stan, miejsce;
	cout << "Podaj numer: ";
	cin >> numer;
	AddLogS(numer);
	cout << "Podaj kolor: ";
	cin >> kolor;
	AddLogS(kolor);
	cout << "Podaj rozmiar: ";
	cin >> rozmiar;
	AddLogS(rozmiar);
	for (int t = 0; t < i; t++)
		{
			if (rekordy[t][0] == numer && rekordy[t][1] == kolor && rekordy[t][2] == rozmiar)
			{
				WyswietlRekord(t);
				cout << "Taki rekord juz istnieje.\n1.Dodaj stan do tego rekordu\n2.Przenies ten rekord" << endl;
				int a;
				cin >> a;
				AddLogI(a);
				if (a == 1)
				{
					cout << "Ile sztuk dodac?: ";
					int ile;
					cin >> ile;
					AddLogI(ile);
					int stan = atoi(rekordy[t][3].c_str());
					stan += ile;
					rekordy[t][3] = IntToString(stan);
					cout << "Operacja sie powiodla" << endl;
					system("pause");
					return;
				}
				else if (a == 2)
				{
					int stan = atoi(rekordy[t][3].c_str());
					cout << "Podaj nowe miejsce: ";
					string nmiejsce;
					cin >> nmiejsce;
					AddLogS(nmiejsce);
					cout << "Podaj ile sztuk dokladasz: ";
					int ile;
					cin >> ile;
					AddLogI(ile);
					stan += ile;
					rekordy[t][3] = IntToString(stan);
					rekordy[t][4] = nmiejsce;
					cout << "Operacja sie powiodla" << endl;
					system("pause");
					return;
				}
				else 
				{
					cout << "Wybrano bledna opcje" << endl;
					return;
				}
			}
		}
		cout << "Podaj stan: ";
	cin >> stan;
	AddLogS(stan);
	cout << "Podaj miejsce: ";
	cin >> miejsce;
	AddLogS(miejsce);
	cout << "Dodac wpisany rekord?\n1.TAK\n2.NIE\n";
	int w;
	cin >> w;
	AddLogI(w);
	if (w==1)
	{
		rekordy[i][0] = numer;
		rekordy[i][1] = kolor;
		rekordy[i][2] = rozmiar;
		rekordy[i][3] = stan;
		rekordy[i][4] = miejsce;
		i++;
		cout << "Dodanie rekordu powiodlo sie" << endl;
	}
	else
	cout << "Anulowano dodawanie rekordu" << endl;
	Zapisz(); system("pause");
}

void PrzygotujListe()
{
	system("cls");
	cout << "Wpisz numer rekordu, jezeli chcesz zakonczyc wprowadz 0" << endl;
	string numer;
	cin >> numer;
	AddLogS(numer);
	ofstream druk;
	druk.open("druk.txt");
	while (numer!="0")
	{
		bool test = false;
		int temp = 0;
		string kolor, rozmiar;
		cout << "Podaj kolor: ";
		cin >> kolor;
		AddLogS(kolor);
		cout << "Podaj rozmiar: ";
		cin >> rozmiar;
		AddLogS(rozmiar);
		for (int t = 0; t < i; t++)
		{
			if (rekordy[t][0] == numer && rekordy[t][1] == kolor && rekordy[t][2] == rozmiar)
			{
				temp = t;
				test = true;
				cout << "Oto znaleziony rekord: " << endl;
				WyswietlRekord(t);
			}
		}
		if (test)
		{
			int stan = atoi(rekordy[temp][3].c_str());
			cout << "Ile sztuk zabierzesz?: ";
			int ile;
			cin >> ile;
			AddLogI(ile);
			if(ile <= stan)
			{
				druk << rekordy[temp][0] << "   " << rekordy[temp][1] << "   "  << rekordy[temp][2] << "   Przed: "  << rekordy[temp][3] << "   Do zabrania: " << ile << "   Po: " << stan-ile << "   " << rekordy[temp][4] << endl;
				stan -= ile;
				rekordy[temp][3] = IntToString(stan);
				cout << "Operacja powiodla sie" << endl;
			}
			else cout << "Nie ma tyle produktu na stanie." << endl;
		}
		else cout << "Nie znaleziono takiego rekordu." << endl;
		Zapisz(); system("pause");
		cout << "Podaj kolejny numer, jezeli chcesz zakonczyc wpisz 0: ";
		cin >> numer;
		AddLogS(numer);
	}
}

void ZmienMiejsce()
{
	system("cls");
	string numer, kolor, rozmiar;
	cout << "Podaj numer: ";
	cin >> numer;
	AddLogS(numer);
	cout << "Podaj kolor: ";
	cin >> kolor;
	AddLogS(kolor);
	cout << "Podaj rozmiar: ";
	cin >> rozmiar;
	AddLogS(rozmiar);
	for (int t = 0; t < i; t++)
	{
		if(numer == rekordy[t][0] && rekordy[t][1] == kolor && rozmiar == rekordy[t][2])
		{
			cout << "Aktualne miejsce to: " << rekordy[t][4] << endl;
			cout << "Podaj nowe miejsce: ";
			cin >> rekordy[t][4];
			AddLogS(rekordy[t][4]);
			cout << "Operacja sie powiodla" << endl;
			system("pause");
			return;
		}
	}
	cout << "Nie znaleziono takiego rekordu." << endl;
	system("pause");
}




void UzupelnijWZ()
{
	fstream ww;
	ww.open("wynikwz.txt");
	string a;
		string numer;
		string kolor;
		string rozmiar;
	while (!ww.eof())
	{
		
		ww >> a;
		while (a != "A" && !ww.eof())
		{
			rozmiar = a;
			for (int t=0; t < i; t++)
			{
				if (numer == rekordy[t][0] && kolor == rekordy[t][1] && rozmiar == rekordy[t][2])
				{
					cout << numer << " " << kolor << " " << rozmiar << " " << rekordy[t][3] << endl;
					cout << "Ile zabralas?: ";
					int y;
					cin >> y;
					AddLogI(y);
					int stan = atoi(rekordy[t][3].c_str());
					if (stan < y) 
					{
						cout << "Pomyliles sie, sprobuj ponownie." << endl;
						t--;
					}
					else
					{
						stan -= y;
						rekordy[t][3] = IntToString(stan);
						cout << "Powiodlo sie." << endl;
						t = i;
					}
				}
			}
			ww >> a;
			ww >> a;
			ww >> a;
		}
		ww >> numer;
		ww >> kolor;
	}
	cout << "Zaktualizowano stan" << endl;
	ww.close();
	ofstream www;
	www.open("wynikwz.txt");
	www.close();
	Zapisz(); system("PAUSE");
}

void Menu()
{
	system("cls");
	cout << "MENU:\n____________________\n";
	cout << "1. Wyswietl stan\n";
	cout << "2. Wyszukaj\n";
	cout << "3. Zmiana stanu\n";
	cout << "4. Dodaj rekord\n";
	cout << "5. Zmien miejsce\n";
	cout << "6. Przygotuj liste\n";
	cout << "7. Przygotuj Wzetke\n";
	cout << "8. Uzupelnij Wzetke\n";
	cout << "0. Wyjscie\n";
}

bool SprawdzWczytanie(string S)
{
	bool t = false;
	for (int z = 0; z < S.length(); z++)
	{
		if (S[z] == '0'){
		}
		else if (S[z] == '1'){
		}
		else if (S[z] == '2'){
		}
		else if (S[z] == '3'){
		}
		else if (S[z] == '4'){
		}
		else if (S[z] == '5'){
		}
		else if (S[z] == '6'){
		}
		else if (S[z] == '7'){
		}
		else if (S[z] == '8'){
		}
		else if (S[z] == '9'){
		}
		else if (S[z] == '-'){
			t = true;
		}
		else return false;
	}
	if (t) return true;
	else
	return false;
}



void Wczytaj()
{
	fstream test;
	test.open("kopiawz.txt");
	fstream wz;
	wz.open("wynikwz.txt"); 
	int ii;
	cout << "Podaj ile pol masz na wzetce: ";
	cin >> ii;
	AddLogI(ii);
	string pomoc[ii][2];
	int u = 0;
	while (!test.eof())
	{
		string a;
		test >> a;
		if (SprawdzWczytanie(a))
		{
			string g;
			test >> g;
			test >> g;
			test >> g;
			if(g[0] != '0')
			{
			string a1, a2;
			a1 = "xxxxx";
			a2 = "xxxxx";
			a1[0] = a[0];
			a1[1] = a[1];
			a1[2] = a[2];
			a1[3] = a[3];
			a1[4] = a[4];
			a2[0] = a[6];
			a2[1] = a[7];
			a2[2] = a[8];
			a2[3] = a[9];
			a2[4] = a[10];
			pomoc[u][0] = a1;
			pomoc[u][1] = a2;
			u++;
		}
		}
	}
	for (int r = 0; r <u; r++)
	{
		wz << "A " << pomoc[r][0] << "     " << pomoc[r][1] << endl << endl;
	for (int q = 0; q < i; q++)
	{
		if(pomoc[r][0] == rekordy[q][0] && pomoc[r][1] == rekordy[q][1])
		{
			wz << rekordy[q][2] << "     " << rekordy[q][3] << "     " << rekordy[q][4] << endl;
		}
	}
	wz << endl  << endl;
}
	wz.close();
	ofstream r;
	r.open("kopiawz.txt");
	r.close();
	cout << "Wzetka zostala przygotowana" << endl;
	system("PAUSE");
}



main()
{
	Start();
	OdczytZPliku();
	Menu();
	int n;
	cin >> n;
	while (n!=0)
	{
		AddLogS("_______");
		AddLogI(n);
		switch(n)
		{
		case 1:WyswietlStan(); break;
		case 2:WyszukiwarkaMenu();  break;
		case 3:ZmianaStanu(); break;
		case 4:DodajRekord(); break;
		case 5:ZmienMiejsce(); break;
		case 6:PrzygotujListe(); break;
		case 7:Wczytaj(); break;
		case 8:UzupelnijWZ(); break;
			}
		Menu();
		cin >> n;
	}
	
}
