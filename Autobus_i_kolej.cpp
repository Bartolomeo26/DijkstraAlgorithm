
#include <iostream>
#include <vector>
#include <limits.h>
#define INF 2147483547
using namespace std;

void DijkstraForBuses(int n, vector<vector<int>>& macierz, vector<vector<int>> macierzK, int s, int biletA, int biletK)
{
    vector<vector<int>> dijkstra_table(n+1, vector<int>(n+1));
    
    int mini=INT_MAX;
    int index = 0, indexn = 0, counter = 0;
    for (int i = 1; i <= n; i++)
    {
        if (macierzK[s][i] == biletK)
        {
            counter++;   //szukamy ile jest polaczen kolejowych w pierwszym wierszu, gdyż tylko one są potencjalną JEDNĄ przesiadką do innego miasta
        }
    }
   
    for (int i = 0; i <= counter; i++)
    {
        for (int j = 1; j <= n; j++)
        {   
            
            if (i == 0)
                dijkstra_table[i][j] = macierzK[s][j]; //przypisanie do pierwszego wiersza dijkstry odleglosci jakie dziela źródło od każdego wierzchołka
            else if(i!=0)
            {
                if (j == s)
                    dijkstra_table[i][j] = 0;//wierzchołek nie może sam dojść do siebie
                if (j == index)
                {
                    dijkstra_table[i][j] = 0; //wierzchołek, którego najkrótszy dystans już znamy nie przyda się później,
                                              //więc zerujemy dystans, by nie przeszkadzał
                }
                else if (dijkstra_table[i-1][index] + macierzK[index][j] < dijkstra_table[i - 1][j])
                {
                    dijkstra_table[i][j] = dijkstra_table[i-1][index] + macierzK[index][j]; //nastapila przesiadka
                    if (macierz[s][j] != biletK && dijkstra_table[i][j]==2*biletK) //jezeli nie ma bezposredniego polaczenia kolejowego ORAZ 
                                                                                   //polaczenie kolejowe do danego miejsca to dwukrotnosc ceny biletu kolejowego - a więc JEDNA przesiadka, to dodajemy autobusowe
                    {
                        macierz[s][j] = biletA; 
                        macierz[j][s] = biletA;
                    }
                }
                else
                {
                    dijkstra_table[i][j] = dijkstra_table[i - 1][j]; //przepisanie wartosci z gory
                }

            }
            if (dijkstra_table[i][j] < mini && dijkstra_table[i][j]!=0) //szukanie najmniejszej wartosci w wierszu
            {
                mini = dijkstra_table[i][j]; indexn = j;
            }
        }
        index = indexn; //zabieg zastosowany po to, żeby jednoczesnie móc korzystać z indexu wiersza poprzedniego,
                        //ale też móc liczyć index wiersza obecnego, który będzie potrzebny do następnej pętli
        
        mini = INT_MAX;
        
    }
    


}

void DijkstraAlgorithm(vector<vector<int>> macierz, int s, int n)
{
    vector<vector<int>> dijkstra_table(n + 1, vector<int>(n + 1)); //tabelka do dijkstry
    int* closestDistance = new int[n+1];
    closestDistance[s] = 0;
    int mini = INT_MAX;
    int index = 0, indexn = 0, counter=0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
          
            if (i == 0) //przypisanie do pierwszego wiersza dijkstry odleglosci jakie dziela źródło od każdego wierzchołka
                dijkstra_table[i][j] = macierz[s][j];
            
            else if(i!=0)
            {
                if (j == s)
                    dijkstra_table[i][j] = 0; //wierzchołek nie może sam dojść do siebie
                if (j == index)
                {
                    dijkstra_table[i][j] = 0; //wierzchołek, którego najkrótszy dystans już znamy nie przyda się później, więc zerujemy dystans, by nie przeszkadzał
                }
                else if (dijkstra_table[i - 1][index] + macierz[index][j] < dijkstra_table[i - 1][j]) //okazuje sie ze do danego wierzchołka można dotrzeć ze źródła szybciej niż zakładaliśmy
                {
                    dijkstra_table[i][j] = dijkstra_table[i-1][index] + macierz[index][j];
                    
                }
                else
                { 
                    dijkstra_table[i][j] = dijkstra_table[i - 1][j]; //jesli nie nastapily zadne zmiany - przepisanie wartosci z gory
                }

            }
            if (dijkstra_table[i][j] < mini && dijkstra_table[i][j] != 0) //szukanie najmniejszej wartosci w wierszu
            {
                mini = dijkstra_table[i][j]; indexn = j; 
            }
            if (dijkstra_table[i][j] != 0) { counter++; }
        }
        closestDistance[indexn] = dijkstra_table[i][indexn]; //najmniejsza wartosc w danym wierszu, to najmniejszy dystans jaki dzieli źródło, a dany wierzchołek docelowy
        if (counter == 1) //jezeli w dijkstrze zostala tylko jedna liczba inna niż zero, to nie ma sensu kontynuować algorytmu
        {
            break;
        }
        counter = 0;
        
        index = indexn; //zabieg zastosowany po to, żeby jednoczesnie móc korzystać z indexu wiersza poprzedniego,
                        //ale też móc liczyć index wiersza obecnego, który będzie potrzebny do następnej pętli
        mini = INT_MAX; 
        
        

    }
   
    for (int i = 1; i <= n; i++)
    {
        cout << closestDistance[i] << endl;
    }
}

int main()
{
    int n, pary, poczatek, cenaK, cenaA;
    int miasto1, miasto2, cena;
    cin >> n >> pary >> poczatek >> cenaK >> cenaA;
    vector<vector<int>> macierz_sasiedztwa(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> macierz_sasiedztwaK(n+1, vector<int>(n+1, INF));
    
    for (int i = 0; i < pary; i++)
    {
        cin >> miasto1 >> miasto2;
        macierz_sasiedztwa[miasto1][miasto2]=cenaK;
        macierz_sasiedztwa[miasto2][miasto1]=cenaK;
    }
    for (int i = 1; i <= n; i++)
    {
        macierz_sasiedztwa[i][i] = 0; //nie da sie dojsc z wierzcholka do tego samego wierzchołka
    }
    
    macierz_sasiedztwaK = macierz_sasiedztwa; //przypisanie do kopii, która przez cały program pozostanie 
                                              //od tego momentu niezmienna, wiec mozna na niej non-stop operować w funkcji dla busów
   for(int i=1; i<=n; i++)
    DijkstraForBuses(n, macierz_sasiedztwa, macierz_sasiedztwaK, i, cenaA, cenaK); //wykonanie dla kazdego miasta dijkstry, by sprawdzic gdzie potrzebne jest polaczenie autobusowe
   
    DijkstraAlgorithm(macierz_sasiedztwa, poczatek, n); //ostateczna dijkstra
    
    
}

