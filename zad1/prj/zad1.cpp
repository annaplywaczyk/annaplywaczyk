#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <windows.h>


using namespace std;

/*!
* \file
* \brief Program wczytuj¹cy plik, wykonuje algorytm na pliku i porównuje z prawid³owym plikiem.
* Program napisany jest w jednym pliku z u¿yciem funkcji.
*/

/*!
* \brief Funkcja wczytuj¹ca dane do wektora z pliku.
* Funkcja otwiera plik zadany przez u¿ytkownika, sprawdza czy plik zosta³ otwarty,
* je¿eli zosta³ otwarty wczytana jest liczba elementow pliku, nastepnie wczytywane sa wszystkie
* liczby do wektora z danymi.
* \param[in] tekst - zmienna, która zostaje wprowadzona przez u¿ytkownika do programu
* \param[in] dane - wektor, do którego zapisywane s¹ wszystkie elementy pliku.
* \return (brak)
*/
void wczytywanie(const string& tekst, vector<int> &dane);

/*!
* \brief Funkcja wypisuj¹ca na ekran wszystkie elementy wektora.
* Funkcja wypisuje na ekran wsyztskie elemnty z pliku na ekran w postaci wektora w kolumnie.
* \param[in] dane - wektor, w którym zapisane s¹ wszystkie elemnty pliku.
* \return (brak)
*/
void wypisz(vector<int>&dane);

/*!
* \brief Funkcja wykonuj¹ca zadany algorytm na wektorze.
* Funkcja wykonuje zadany algorytm na wektorze wejsciowym.
* W naszym przypadku wektor pomno¿ony jest przez sta³¹ liczbê 2.
* \param[in] dane - wektor, na ktorym wykonywany jest algorytm i po wykonaniu algorytmu wektor
* jest zmieniony, dziêki czemu nie musimy tworzyæ nowego wektora.
* \return (brak)
*/
void algorytm(vector<int>&dane);

/*!
* \brief Funkcja porównuj¹ca dwa wektory.
* Funkcja porównuje dwa wektory, sprawdza czy wszystkie elemnty s¹ ze sob¹ równe. W ka¿dym wypadku
* zwraca nam komunikat albo ¿e wektory poddane analizie s¹ jednakowe b¹dŸ b³êdne. 
* Do funkcji poddawna s¹ wektory jeden po wprowadzeniu z pliku i wykonaniu algorytmu oraz drugi,
* który jest ma byæ sprawdzeniem czy algorytm zosta³ prawid³owo wykonany.
* \param[in] dane - wektor, który jest pierwszym wprowadzonyn plikiem przez u¿ytkownika i po wykanniu algorytmu.
* \param[in] poprawne - wektor, który wprowadzany jest do programu jako drugi przez u¿ytkownika, który 
* ma byæ sprawdzeniem poprawnosci wykonania algorytmu.
* \return (brak)
*/
void porownanie(vector<int>&dane, vector<int>&poprawne);

/*!
* \brief Funkcja zapamietuj¹ca czas poczatkowy.
* Funkcja nale¿¹ca do biblioteki "windows.h",  stoper zostaje w³¹czony, aby zosta³ zmierzony czas wykonania 
* algorytmu w programie.
* Funkcja nale¿¹ca do funkcji bool QueryPerformanceCounter(_out LARGE_INTEGER *IpPerformanceCount), 
* funkcja ta zwraca wartosc niezerowa je¿eli w³aczenie zakoñczy siê sukcesem, natomiast w przeciwnym wypadku 
* zostanie wyrzucony b³¹d i zwróci wartosc 0. Dla komputerów multiprocesorowych nie ma znaczenia, który jest u¿ywany.
*/
LARGE_INTEGER wylaczStoper();

/*!
* \brief Funkcja zapamietuj¹ca czas koñcowy.
* Funkcja nale¿¹ca do biblioteki "windows.h",  stoper zostaje wy³¹czony, aby zosta³ zmierzony czas wykonania 
* algorytmu w programie, poprzez odjêcie czasu pocz¹tkowego od czasu koñcowego.
* Funkcja nale¿¹ca do funkcji bool QueryPerformanceCounter(_out LARGE_INTEGER *IpPerformanceCount), 
* funkcja ta zwraca wartosc niezerowa je¿eli w³aczenie zakoñczy siê sukcesem, natomiast w przeciwnym wypadku 
* zostanie wyrzucony b³¹d i zwróci wartosc 0. Dla komputerów multiprocesorowych nie ma znaczenia, który jest u¿ywany,
* mog¹ jedynie ró¿niæ siê minimalnie czasy.
*/
LARGE_INTEGER wlaczStoper();


/*!
* \brief Funkcja g³ówna.
* W funkcji tej u¿ywana jest komunikacja z u¿ytkownikiem programu, wykonywane s¹ funkcje.
* Wczytany zostaje plik, który: wypisany zostje na ekran, wykonana zostaje pêtla, która mierzy 
* sredni czas wykonywania algorytmu przez program, nastêpnie u¿ytkownik wprowadza drugi plik, 
* który zostaje porównany z wektorem na którym zosta³ wykonany algorytm. Na koñcu zwórcony
* zostaje sredni czas wykonywania algorytmu na wektorze w programie.
*/
int main()
{
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	int czas=0;
	vector<int>wec;
	cout <<"Wczytywanie pliku" << endl;
	string nazwa_pliku;
	cin >> nazwa_pliku;
	wczytywanie(nazwa_pliku, wec);
	wypisz(wec);
	for (int k=0; k<20; k++)
	{
		int roznica=0;
		wczytywanie(nazwa_pliku, wec);
		start=wlaczStoper();
		algorytm(wec);
		end=wylaczStoper();
		roznica = end.QuadPart - start.QuadPart;
		czas = czas+roznica;
	}

	cout << "\nWczytaj plik sprawdzajacy poprawnosc wykonania mnozenia:" << endl;
	string nazwa_pliku2;
	cin >> nazwa_pliku2;
	vector<int>pop;
	wczytywanie(nazwa_pliku2, pop);
	porownanie(wec,pop);
	
	cout << "\nProgram wykona³ algorytm w srednim czasie: ";
	cout <<czas/20<< "ms" <<endl;

	return 0;
}

void wczytywanie(const string& tekst, vector<int> &dane)
{
	ifstream plik(tekst.c_str());
	int liczba_elementow;
	
	if (!plik)
	{
		cerr << "Brak pliku!" << endl;
		
	}
	
	plik >> liczba_elementow;
	
	int liczba;
	
	for(int i=1; plik >> liczba; i++)
	{
		dane.push_back(liczba);
	}
	plik.close();
}

void wypisz(vector<int>&dane)
{
	for(int i=0; i<dane.size(); i++)
	{
		cout <<"W["<<i<<"]: "<< dane[i]<< endl;
	}
}

void algorytm(vector<int>&dane)
{
	for (int i=0; i<dane.size(); i++){
	dane[i]=dane[i]*2;}
}

void porownanie(vector<int>&dane, vector<int>&poprawne)
{
	/*for(int i=0; i<dane.size(); i++){*/
	
	if(dane!=poprawne)
	{
		cerr << "Pomnozone dane sa rozne z plikiem sprawdzajacym!";
		
	}
	else
	cout << "Pomnozone dane sa prawidlowe z plikiem!" << endl;
	
}

LARGE_INTEGER wlaczStoper() 
{ 
 LARGE_INTEGER start; 
 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0); 
 QueryPerformanceCounter(&start); 
 SetThreadAffinityMask(GetCurrentThread(), oldmask); 
 return start; 
} 

LARGE_INTEGER wylaczStoper() 
{ 
 LARGE_INTEGER stop; 
 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0); 
 QueryPerformanceCounter(&stop); 
 SetThreadAffinityMask(GetCurrentThread(), oldmask); 
 return stop; 
} 


 

