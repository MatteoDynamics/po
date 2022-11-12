#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#define SIZE 500;
void filtr(double *,double *);
void read_length(int*, char*);
double function(double *, double *, double *, double *, int);
void dziedzina(double *,double *);
double wsp(double*);
void funkcja(double *,double l, double p, double *, int);
void drukuj(double *,int );
void szum_prawd(double *, double *, int ,double *);
void zapis(double *, int, char *);
double ampp();
double random_number(double *a);
int tab_rozmiar();
double *dynamic_tab(int );
void odczyt(double *, int *);
void save_or_not(int*);
void welcome(int *);
void next_menu(int *);
void next_menu3(int *);
void filtred(double *,double*,int *rozmiar);
void merge_sort(double * filtr_tab, int *rozmiar);
void merge_s_r(double * filtr_tab,int l,int r);
void merge_s_arr(double * filtr_tab,int l,int m, int r);

int main()
{
    int save = 0;int menu1=0;int menu2=0;int menu3 = 0;double l = 0; double p = 0; double wspol1[3]; int time;double *wynik;int rozmiar;double amp1;double r;double *wynik_z;
    double *filter_tab;
    setlocale( LC_ALL, "polish_poland" );
    welcome(&menu1);
    switch(menu1)
{
    case 1:
    {
        printf("You choose generating new function\n");

        rozmiar = tab_rozmiar();
        wynik = dynamic_tab(rozmiar);
        wynik_z = dynamic_tab(rozmiar);

        dziedzina(&l,&p);

        wsp(wspol1);

        funkcja(wspol1,l,p,wynik,rozmiar);
        
        save_or_not(&save);
        if (save == 1)
        { 
            zapis(wynik,rozmiar,"essa.csv");
        }
        save=0;
        next_menu(&menu2);
        
    
        switch(menu2)
        {
           case 1: 
           {
                amp1 = ampp();
                szum_prawd(wynik,wynik_z,rozmiar,&amp1);
                save_or_not(&save);
                if(save = 1)
                {
                     zapis(wynik_z,rozmiar,"essa.csv");
                     printf("SAVED!");
                }
           }
           case 2:
           {
            filtred(wynik,filter_tab,&rozmiar);
           }
           case 3:
           {
            welcome(&menu1);
           }
        }break;
        
            
        }
    case 2:
    {
        read_length(&rozmiar, "essa.csv");
        printf("rozmiar === %d", rozmiar);
        wynik = dynamic_tab(rozmiar);
        printf("YOU CHOOSE READ FROM FILE\n");
        odczyt(wynik,&rozmiar);
        filtred(wynik,filter_tab,&rozmiar);
    }
    break;
    
    
        
    case 3:
    {
    printf("quiting\n");
    free(wynik);
    free(wynik_z);
    printf("zwolniono pamiec\n");
    }break;
}
    
}



void dziedzina(double *x, double *y)
{
    int ok=0;
    printf("Podaj liczbe l\n");
    ok = scanf("%lf", &*x);
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit ;
    }
    printf("Podaj liczbe p\n");
    ok = scanf("%lf", &*y); 
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit ;
    }
}

double wsp(double *wspol1)
{
    printf("Podaj wspolczynniki a,b i c: \n");
    int ok=0;
     for(int i =0 ; i<3 ; i++)
    {
        ok = scanf("%lf",&wspol1[i]);
    }
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit ;
    }
    
return 0;
}

void funkcja(double *wsp,double l, double p, double *wynik, int rozmiar)
{
    double xy = (p-l)/rozmiar;
    for (int i = 0; i<rozmiar ; i++)
    {
        double z = xy*i;
        wynik[i] = (wsp[0]*sqrt(l+z)) * sin(wsp[1]*(l+z)+wsp[2]);
    }
}

void print(double wynik[],int rozmiar)
{
    for (int i =0 ; i<rozmiar ; i++)
    {
    printf("y[%d] = %lf\n",i, wynik[i]);
    }
}

void print2(double wynik[],double wynik_z[],int rozmiar)
{
     for (int i =0 ; i<rozmiar ; i++)
    {
    printf("y[%d] = %lf\n",i, wynik_z[i]);
    }
}


//         ZAPIS DO PLIKU        //


void zapis(double *wynik, int rozmiar, char *filename)
{

    FILE *plik;
    plik = fopen(filename, "w+");
    if (plik == 0)
    {
        return ;
    }
    for(int i=0; i<rozmiar ; i++)
    {
        fprintf(plik,"%lf\n",wynik[i]);
    }
    fclose(plik);
}

double ampp()
{
    double amp;
    printf("podaj amp:  ");
    scanf ("%lf", &amp);
    return amp;
}
double random_number(double *amp1)
{

    double r;
    srand ( time ( NULL));
    r = (double)rand()/RAND_MAX*(2*(*amp1))-(*amp1);
    return r;
}
void szum_prawd(double wynik[],double wynik_z[], int rozmiar, double *amp1)
{
    double a;
    printf ("Podaj wartosc progowa prawdopodobienstwa:  \n");
    scanf("%lf",&a);
    for (int i=0; i<rozmiar; i++)
    {
        int rand1 = rand()%100+1;
        if (rand1<a)
        wynik_z[i] = wynik[i] + ((double)rand()/RAND_MAX*2.0*(double)(*amp1/2)-(double)(*amp1/2));
        else
        wynik_z[i] = wynik[i];
    }

}
int tab_rozmiar()
{
printf("\nPodaj wielkosc tablicy wynikowej:   \n");
int a;
scanf("%d",&a);
if(a>500)
    {
        printf("\nWrong data, maximum size of array is 500 EXIT!\n");
        return tab_rozmiar() ;
    }

return a;
}
double *dynamic_tab(int rozmiar)
{
    double *wynik = calloc(rozmiar,sizeof(double));
    return wynik;
}
void odczyt(double *wynik, int *rozmiar)
{
    int records=0;
   FILE* file;
	file = fopen("C:\\Users\\Matteo\\PycharmProjects\\essa.csv", "r");

	if (file == NULL) {
		printf("\nNie udalo sie otworzyc pliku");
	}
	setlocale(LC_ALL, "polish_poland");

	for (int i = 0; i < *rozmiar; i++)
		fscanf(file, "%lf\n", &(*(wynik + i)));

	setlocale(LC_ALL, "C");

	fclose(file);
	for(int i=0; i<*rozmiar; i++)
	{
		printf("y[%d]= %lf\n", i, wynik[i]);
	}

}
void welcome(int *menu1)
{
printf("\n1) GENERATE NEW FUNCTION\n2) READ FUNCTION\n3) QUIT");
int ok = scanf("%d",&(*menu1));
if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit ;
    }
}
void save_or_not(int *zapis)
{
    printf("1) SAVE FILE\n 2) DO NOT SAVE FILE");
    int ok = scanf("%d", &(*zapis));
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit ;
    }


}

void next_menu(int *menu2)
{
    printf("************************\n1) NOISE THE FUNCTION\n2) FILTER THE FUNCTION\n3) GO BACK MENU\n");
    int ok = scanf("%d",&(*menu2));
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit;
        
    }
    
}

/*int read_length(int * rozmiar, char NazwaPliku[]) 
{
	FILE* plik;
	plik = fopen(NazwaPliku, "r");

	if (plik == NULL) {
		printf("\nNie udalo sie otworzyc pliku");
	}
    fseek(plik,0L,SEEK_END);
    *rozmiar = ftell(plik);
    *rozmiar = (*rozmiar-33)/10;
    printf("\n rozmiar = %d\n", *rozmiar);
}
*/
void read_length(int* rozmiar, char NazwaPliku[]) {
	FILE* excel;
	excel = fopen(NazwaPliku, "r");

	if (excel == NULL) {
		printf("\nNie udalo sie otworzyc pliku");
	}
	setlocale(LC_ALL, "polish_poland");

	char chr;
	int wiersze = 0;
	chr = getc(excel);
	while (chr != EOF)
	{
		if (chr == 10)
		{
			wiersze = wiersze + 1;
		}
		chr = getc(excel);
	}

	printf("\nwiersze=%d", wiersze);

	setlocale(LC_ALL, "C");

	fclose(excel);

	*rozmiar = wiersze;
}
void filtred(double *wynik, double* filtr_tab, int *rozmiar)
{
    double probki[5];
    int okno = 5;
    filtr_tab = calloc(*rozmiar, sizeof(double));
    for(int i =0; i< *rozmiar; i++)
    filtr_tab[i] = wynik[i];
    for (int i =0; i<*rozmiar-3; i++)
    {
        for(int p=0; p< okno; p++)
        {
        probki[p] = wynik[p+i];
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<okno-1; j++)
            {
                if(probki[j]> probki[j+1])
                {
                double temp=probki[j];
                probki[j]= probki[j+1];
                probki[j+1] = temp;  
            }
        }
        }
        //for(int i=0;i<5;i++)printf("probka2[%d] = %lf\n", i , probki[i]);
     *(filtr_tab+2+i) = *(probki+2);   
    }//for(int i=0;i<okno;i++)printf("probka[%d] = %lf", i , probki[i]);

    
        


 /*   double probki[5];
 int okno=5;
 filtr_tab = calloc(*rozmiar, sizeof(double));
 for (int j=0 ; j< *rozmiar ; j++)
 {
    filtr_tab[j]= wynik[j];
    for(int i = 0; i<okno ; i++)
        probki[i]= wynik[j+i];
        for(int j=0;j<okno;j++)
        {
        for(int i =0; i< okno; i++)
        {
            if (probki[j] > probki[j+1])
            {
                double temp=probki[j];
                probki[j]= probki[j+1];
                probki[j+1] = temp;
            }
        }
        
        }
    filtr_tab[2+j] = probki[2];
 }*/

for(int i = 0; i <*rozmiar; i++)
 printf("test[%d] = %lf\n",i, filtr_tab[i]);

}