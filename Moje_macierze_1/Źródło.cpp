#include <iostream>
#include <cstdlib>
//#include <ctime>
using namespace std;

void wyswTab(double** T1, int roz)                         // kod z zajec
{
	for (int i = 0; i < roz; i++)
	{
		for (int j = 0; j < roz; j++)
		{
			cout << T1[i][j] << "\t";
		}
		cout << "\n";
	}
}

void mnozW(double** T1, int roz, double war, int nr)
{
	for (int i = 0; i < roz; i++)
	{
		T1[nr][i] = war * T1[nr][i];
	}
}

void dodajW(double** T1, int roz, int nr1, int nr2)
{
	for (int i = 0; i < roz; i++)
	{
		T1[nr1][i] = T1[nr1][i] + T1[nr2][i];
	}
}

//---------------------------------------------------------
void zaokr(double** T1, double** T2, int roz);
void odejW(double** T1, int roz, double var, int i, int j);

void elGauss(double** T1, double** T2, int roz)
{
	double tym;
	                                                      // zera pod przek¹tn¹
	for (int j = 0; j < roz - 1; j++)
	{
		for (int i = j + 1; i < roz; i++)
		{
			tym = -T1[j][j] / T1[i][j];

			mnozW(T1, roz, tym, i);
			mnozW(T2, roz, tym, i);

			dodajW(T1, roz, i, j);
			dodajW(T2, roz, i, j);
		}
	}

	zaokr(T1, T2, roz);
	                                                // zera nad przek¹tn¹
	for (int i = roz - 1; i > 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			tym = T1[i][i] * T1[j][i];

			odejW(T1, roz, tym, i, j);
			odejW(T2, roz, tym, i, j);
		}
	}

	zaokr(T1, T2, roz);

}
//-------------------------------------------------------------------------------

int main()
{
    int wymiar;
	do
	{
	cout << "Podaj rozmiar macierzy : " ;
	cin >> wymiar;
	} while (wymiar < 1);

	
	double ** G1 = new double *[wymiar];              // tworzenie tablic dynamicznych
	double ** G2 = new double *[wymiar];

	
	for (int i = 0; i < wymiar; i++)                 // wymiar
	{
		G1[i] = new double[wymiar];
		G2[i] = new double[wymiar];
	}
 //================================================

		for (int i = 0; i < wymiar; i++)                                // Macierz A
		{
			for (int j = 0; j < wymiar; j++)
			{
				cout << "Podaj element " << i + 1 << "," << j + 1 << ": ";
				cin >> G1[i][j];
			}
		}
	

	for (int i = 0; i < wymiar; i++)                              // Macierz jednostkowa
	{
		for (int j = 0; j < wymiar; j++)
		{
			if (i == j)
			{
				G2[i][j] = 1;
			}
			else
			{
				G2[i][j] = 0;
			}
		}
	}

	cout << "Podana macierz" << endl;
	wyswTab(G1, wymiar);

	cout << endl << "Macierz jednostkowa " << endl;
	wyswTab(G2, wymiar);
//==========================================================

	elGauss(G1, G2, wymiar);

	if (G1[0][0] != 1)
	{
		cout << endl << "Brak macierzy odwrotnej ---> macierz osobliwa " << endl << endl;
	}
	else
	{
		
		cout << endl << endl << "Macierz odwrotna" << endl;
		wyswTab(G2, wymiar);
		cout << endl;
	}


	//=================================== zwalnianie pamieci
	for (int i = 0; i < wymiar; i++)
	{
		delete[] G1[i];
		delete[] G2[i];
	}

	delete[] G1;
	delete[] G2;

	system("pause");
	return 0;
}


void zaokr(double** T1, double** T2, int roz)
{
	for (int i = 0; i < roz; i++)
	{
		double pomoc;
		pomoc = T1[i][i];								//wartosc na przekatnej 
		for (int j = 0; j < roz; j++)
		{

			if (abs(T1[i][j]) < 1e-10)					//zaokr¹gla b³ad
			{
				T1[i][j] = 0;
			}



			T1[i][j] = T1[i][j] / pomoc;					// dzielenie wierszy zeby na przekatnej bylo 1
			T2[i][j] = T2[i][j] / pomoc;
		}
	}
}


void odejW(double** T1, int roz, double var, int i, int j)
{
	for (int k = roz - 1; k >= 0; k--)
	{
		T1[j][k] = T1[j][k] - var * T1[i][k];
	}
}