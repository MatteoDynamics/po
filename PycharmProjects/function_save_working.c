#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#define SIZE 500;
void filtr(double * , double *);
void read_length(int* , char*);
void field(double * , double *);
double coefficient(double*);
void function_generating(double * , double , double , double * , int);
void noise_probability(double * , double *, int , double *);
void save_function(double * , int , char *);
double amplitude();
double random_number(double *);
int tab_rozmiar();
double *dynamic_tab(int );
void read_function(double * , int *);
void save_or_not(int*);
void welcome(int *);
void next_menu(int *);
void filtered_function(double * , double* , int *);
/*
void merge_sort(double * filtr_tab, int *);
void merge_s_r(double * filtr_tab,int l,int r);                 //MERGE SORT UPDATE UPCOMMING
void merge_s_arr(double * filtr_tab,int l,int m, int r);
*/

int main()
{
    int save = 0 ; int menu1=0 ; int menu2=0 ; int menu3 = 0 ; double left = 0 ; double right = 0;     
    double wspol1[3]; int time ; int size ; double amp ; double r;
    double *filter_tab ; double *array_noised ; double *array_function;
    setlocale( LC_ALL, "polish_poland" );                   // POLISH NOTATION SAVE IN EXCEL
    
    welcome(&menu1);
    switch(menu1)
{
    case 1:
    {
        printf("You choose generating new function\n");

        size = tab_size();
        array_function = dynamic_tab(size);
        array_noised = dynamic_tab(size);
        filter_tab = dynamic_tab(size);

        field(&left,&right);

        coefficient(wspol1);

        function_generating(wspol1,left,right,array_function,size);
        
        save_or_not(&save);
        if (save == 1)
        { 
            save_function(array_function,size,"essa.csv");
            printf("saved_function!\n");
        }
        save=2;
        do
        {
        next_menu(&menu2);
        switch(menu2)
        {
           case 1: 
           {
                amp = amplitude();
                printf("amp = %d", amp);
                noise_probability(array_function,array_noised,size,&amp);
                save_or_not(&save);
                if(save = 1)
                {
                     save_function(array_noised,size,"essa.csv");
                     printf("SAVED!");
                }
                save=2;
           }break;
           
           case 2:                                      // SIGNAL FILTERING
           {
            filtered_function(array_function,filter_tab,&size);                 
            save_or_not(&save);
            if (save == 1)
        { 
            save_function(filter_tab,size,"essa.csv");
        }
        save=2;
           }break;
           case 3:
            {
                printf("quiting\n");
                free(array_function);
                free(array_noised);
                printf("free memory!\n");
            }break;
        }
        } while(menu2==1 || menu2==2);
        
            
    }break;
    case 2:
    {
        read_length(&size, "essa.csv");
      //  printf("size === %d", size);
        array_function = dynamic_tab(size);
        array_noised = dynamic_tab(size);
        filter_tab = dynamic_tab(size);
        printf("YOU CHOOSE READ FROM FILE\n");
        read_function(array_function,&size);
        for (int i=0; i <size ; i++)
        printf("odczyt[%d] = %0.3lf", i , array_function[i]);
        do
        {
        next_menu(&menu2);
        switch(menu2)
        {
           case 1: 
           {
                amp = amplitude();
                printf("amp = %d", amp);
                noise_probability(array_function,array_noised,size,&amp);
                save_function(array_noised,size,"essa.csv");
           }break;
           
           case 2:                                      // SIGNAL FILTERING
           {
            filtered_function(array_function,filter_tab,&size);
            save_function(filter_tab,size,"essa.csv");
           }break;
           case 3:
            {
                printf("quiting\n");
                free(array_function);
                free(array_noised);
                free(filter_tab);
                printf("free memory!\n");
            }break;
        }
        } while(menu2==1 || menu2==2);
        //filtered_function(array_function,filter_tab,&size);
    }
    break;
    
    
        
    case 3:
    {
    printf("quiting\n");
    free(array_function);
    free(array_noised);
    free(filter_tab);
    printf("free memory!\n");
    }break;
}
}




void field(double *x, double *y)
{
    int ok=0;
    printf("type left border:   \n");
    ok = scanf("%lf", &*x);
    if(ok!=1)
    {
        printf("Wrong data, EXIT!\n");
        exit ;
    }
    printf("type right border:  \n");
    ok = scanf("%lf", &*y); 
    if(ok!=1)
    {
        printf("Wrong data, EXIT!\n");
        exit ;
    }
}

double coefficient(double *wspol1)
{
    printf("Type in coefficients:   \n");
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

void function_generating(double *coefficient,double left, double right, double *array_function, int size)
{
    double xy = (right-left)/size;
    for (int i = 0; i<size ; i++)
    {
        double z = xy*i;
        array_function[i] = (coefficient[0]*sqrt(left+z)) * sin(coefficient[1]*(left+z)+coefficient[2]);
    }
}

void print(double array_function[],int size)
{
    for (int i =0 ; i<size ; i++)
    {
    printf("y[%d] = %lf\n",i, array_function[i]);
    }
}

void print2(double array_function[],double array_noised[],int size)
{
     for (int i =0 ; i<size ; i++)
    {
    printf("y[%d] = %lf\n",i, array_noised[i]);
    }
}


//         ZAPIS DO PLIKU        //


void save_function(double *array_function, int size, char *filename)
{

    FILE *plik;
    plik = fopen(filename, "w+");
    if (plik == 0)
    {
        return ;
    }
    for(int i=0; i<size ; i++)
    {
        fprintf(plik,"%lf\n",array_function[i]);
    }
    fclose(plik);
}

double amplitude()
{
    double amp;
    printf("podaj amp:  ");
    scanf ("%lf", &amp);
    return amp;
}

double random_number(double *amp)
{

    double r;
    srand ( time ( NULL));
    r = (double)rand()/RAND_MAX*(2*(*amp))-(*amp);
    return r;
}

void noise_probability(double array_function[],double array_noised[], int size, double *amp)
{
    double a;
    printf ("type in probability percentage:  \n");
    scanf("%lf",&a);
    for (int i=0; i<size; i++)
    {
        int rand1 = rand()%100+1;
        if (rand1<a)
        array_noised[i] = array_function[i] + ((double)rand()/RAND_MAX*2.0*(double)(*amp/2)-(double)(*amp/2));
        else
        array_noised[i] = array_function[i];
    }

}

int tab_size()
{
printf("\ntype in size of array:   \n");
int a;
scanf("%d",&a);
if(a>500)
    {
        printf("\nWrong data, maximum size of array is 500 EXIT!\n");
        return tab_size() ;
    }

return a;
}

double *dynamic_tab(int size)
{
    double *array_function = calloc(size,sizeof(double));
    return array_function;
}

void read_function(double *array_function, int *size)
{
    int records=0;
   FILE* file;
	file = fopen("C:\\Users\\Matteo\\PycharmProjects\\essa.csv", "r");

	if (file == NULL) {
		printf("\ncouldnt open the file\n");
	}
	setlocale(LC_ALL, "polish_poland");                                                             // POLISH NOTATION READ IN EXCEL

	for (int i = 0; i < *size; i++)
		fscanf(file, "%lf\n", &(*(array_function + i)));

	setlocale(LC_ALL, "C");                                                                         // POLISH NOTATION READ IN EXCEL

	fclose(file);
	//for(int i=0; i<*size; i++)
	//{
	//	printf("y[%d]= %lf\n", i, array_function[i]);
	//}

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

void save_or_not(int *save)
{
    printf("1) SAVE FILE\n 2) DO NOT SAVE FILE");
    int ok = scanf("%d", &(*save));
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit ;
    }


}

void next_menu(int *menu2)
{
    printf("************************\n1) NOISE THE FUNCTION\n2) FILTER THE FUNCTION\n3) GO BACK MENU\ntype: ");
    int ok = scanf("%d",&(*menu2));
    if(ok!=1)
    {
        printf("Wrong data, EXIT!");
        exit;
        
    }
    
}

/*int read_length(int * size, char NazwaPliku[]) 
{
	FILE* plik;
	plik = fopen(NazwaPliku, "r");
	if (plik == NULL) {
		printf("\nNie udalo sie otworzyc pliku");
	}
    fseek(plik,0L,SEEK_END);
    *size = ftell(plik);
    *size = (*size-33)/10;
    printf("\n size = %d\n", *size);
}
*/

void read_length(int* size, char NazwaPliku[]) 
{
	FILE* excel;
	excel = fopen(NazwaPliku, "r");

	if (excel == NULL) {
		printf("\ncouldnt open the file\n");
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

	//printf("\nwiersze=%d", wiersze);

	setlocale(LC_ALL, "C");

	fclose(excel);

	*size = wiersze;
}

void filtered_function(double *array_function, double* filtr_tab, int *size)
{
    double probki[5];
    int okno = 5;
    for(int i =0; i< *size; i++)
    filtr_tab[i] = array_function[i];
    for (int i =0; i<*size-3; i++)
    {
        for(int p=0; p< okno; p++)
        {
        probki[p] = array_function[p+i];
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

for(int i = 0; i <*size; i++)
 printf("test[%d] = %lf\n",i, filtr_tab[i]);

}
 /*   double probki[5];
 int okno=5;
 filtr_tab = calloc(*size, sizeof(double));
 for (int j=0 ; j< *size ; j++)
 {
    filtr_tab[j]= array_function[j];
    for(int i = 0; i<okno ; i++)
        probki[i]= array_function[j+i];
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
