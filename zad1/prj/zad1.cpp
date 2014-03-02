#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <windows.h>


using namespace std;

/*!
* \file
* \brief Program wczytuj�cy plik, wykonuje algorytm na pliku i por�wnuje z prawid�owym plikiem.
* Program napisany jest w jednym pliku z u�yciem funkcji.
*/

/*!
* \brief Funkcja wczytuj�ca dane do wektora z pliku.
* Funkcja otwiera plik zadany przez u�ytkownika, sprawdza czy plik zosta� otwarty,
* je�eli zosta� otwarty wczytana jest liczba elementow pliku, nastepnie wczytywane sa wszystkie
* liczby do wektora z danymi.
* \param[in] tekst - zmienna, kt�ra zostaje wprowadzona przez u�ytkownika do programu
* \param[in] dane - wektor, do kt�rego zapisywane s� wszystkie elementy pliku.
* \return (brak)
*/
void wczytywanie(const string& tekst, vector<int> &dane);

/*!
* \brief Funkcja wypisuj�ca na ekran wszystkie elementy wektora.
* Funkcja wypisuje na ekran wsyztskie elemnty z pliku na ekran w postaci wektora w kolumnie.
* \param[in] dane - wektor, w kt�rym zapisane s� wszystkie elemnty pliku.
* \return (brak)
*/
void wypisz(vector<int>&dane);

/*!
* \brief Funkcja wykonuj�ca zadany algorytm na wektorze.
* Funkcja wykonuje zadany algorytm na wektorze wejsciowym.
* W naszym przypadku wektor pomno�ony jest przez sta�� liczb� 2.
* \param[in] dane - wektor, na ktorym wykonywany jest algorytm i po wykonaniu algorytmu wektor
* jest zmieniony, dzi�ki czemu nie musimy tworzy� nowego wektora.
* \return (brak)
*/
void algorytm(vector<int>&dane);

/*!
* \brief Funkcja por�wnuj�ca dwa wektory.
* Funkcja por�wnuje dwa wektory, sprawdza czy wszystkie elemnty s� ze sob� r�wne. W ka�dym wypadku
* zwraca nam komunikat albo �e wektory poddane analizie s� jednakowe b�d� b��dne. 
* Do funkcji poddawna s� wektory jeden po wprowadzeniu z pliku i wykonaniu algorytmu oraz drugi,
* kt�ry jest ma by� sprawdzeniem czy algorytm zosta� prawid�owo wykonany.
* \param[in] dane - wektor, kt�ry jest pierwszym wprowadzonyn plikiem przez u�ytkownika i po wykanniu algorytmu.
* \param[in] poprawne - wektor, kt�ry wprowadzany jest do programu jako drugi przez u�ytkownika, kt�ry 
* ma by� sprawdzeniem poprawnosci wykonania algorytmu.
* \return (brak)
*/
void porownanie(vector<int>&dane, vector<int>&poprawne);

/*!
* \brief Funkcja zapamietuj�ca czas poczatkowy.
* Funkcja nale��ca do biblioteki "windows.h",  stoper zostaje w��czony, aby zosta� zmierzony czas wykonania 
* algorytmu w programie.
* Funkcja nale��ca do funkcji bool QueryPerformanceCounter(_out LARGE_INTEGER *IpPerformanceCount), 
* funkcja ta zwraca wartosc niezerowa je�eli w�aczenie zako�czy si� sukcesem, natomiast w przeciwnym wypadku 
* zostanie wyrzucony b��d i zwr�ci wartosc 0. Dla komputer�w multiprocesorowych nie ma znaczenia, kt�ry jest u�ywany.
*/
LARGE_INTEGER wylaczStoper();

/*!
* \brief Funkcja zapamietuj�ca czas ko�cowy.
* Funkcja nale��ca do biblioteki "windows.h",  stoper zostaje wy��czony, aby zosta� zmierzony czas wykonania 
* algorytmu w programie, poprzez odj�cie czasu pocz�tkowego od czasu ko�cowego.
* Funkcja nale��ca do funkcji bool QueryPerformanceCounter(_out LARGE_INTEGER *IpPerformanceCount), 
* funkcja ta zwraca wartosc niezerowa je�eli w�aczenie zako�czy si� sukcesem, natomiast w przeciwnym wypadku 
* zostanie wyrzucony b��d i zwr�ci wartosc 0. Dla komputer�w multiprocesorowych nie ma znaczenia, kt�ry jest u�ywany,
* mog� jedynie r�ni� si� minimalnie czasy.
*/
LARGE_INTEGER wlaczStoper();


/*!
* \brief Funkcja g��wna.
* W funkcji tej u�ywana jest komunikacja z u�ytkownikiem programu, wykonywane s� funkcje.
* Wczytany zostaje plik, kt�ry: wypisany zostje na ekran, wykonana zostaje p�tla, kt�ra mierzy 
* sredni czas wykonywania algorytmu przez program, nast�pnie u�ytkownik wprowadza drugi plik, 
* kt�ry zostaje por�wnany z wektorem na kt�rym zosta� wykonany algorytm. Na ko�cu zw�rcony
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
	
	cout << "\nProgram wykona� algorytm w srednim czasie: ";
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


 

