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
    switch(menu1)                   //MENU1 
            //-----------------------------------------------------------          
    {
        case 1:
        {
            printf("\nYou choose generating new function\n");

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
                printf("\nsaved_function!\n\n");
            }
            save=2;
                                                                                                        //MENU2  
                                                                            //---------------------------------------------------------------      
            do
            {
                next_menu(&menu2);
                switch(menu2)
                {
                    case 1:                                                 
                    {
                        amp = amplitude();                                              // AMPLITUDE
                        noise_probability(array_function,array_noised,size,&amp);       // GENERATING NOISE
                        save_or_not(&save);                                             // SAVE
                        if(save = 1)
                        {
                            save_function(array_noised,size,"essa.csv");
                            printf("SAVED!");
                        }
                        save=2;
                    }break;

                    case 2:                                      
                    {
                        filtered_function(array_function,filter_tab,&size);             // SIGNAL FILTERING
                        save_or_not(&save);                                             // SAVE
                        if (save == 1)
                        {
                            save_function(filter_tab,size,"essa.csv");
                        }
                        save=2;
                    }break;
                    case 3:
                    {                                                                   //FREEING SPACE AFTER ALOCATED MEMORY
                        printf("quiting\n");
                        free(array_function);
                        free(array_noised);
                        free(filter_tab);
                        printf("free memory!\n");
                    }break;
                }
            } while(menu2==1 || menu2==2);      
                                                                            //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                                                                                        //END MENU2

        }break;
        case 2:                                                             //READ FROM FILE
        {
            read_length(&size, "essa.csv");
            //  printf("size === %d", size);
            array_function = dynamic_tab(size);                             //ALOCATING SPACE FOR ARRAYS
            array_noised = dynamic_tab(size);
            filter_tab = dynamic_tab(size);
            printf("YOU CHOOSE READ FROM FILE\n");
            read_function(array_function,&size);                            //READING FROM FILE
            //for (int i=0; i <size ; i++)
               // printf("odczyt[%d] = %0.3lf", i , array_function[i]);
            do                                                              
            {
                next_menu(&menu2);                                          //MENU 2 UNTILL QUIT
                switch(menu2)   
                {
                    case 1:
                    {
                        amp = amplitude();
                      //  printf("amp = %d", amp);
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
                        printf("\nquiting\n");
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
    printf("\ntype left border: ");
    ok = scanf("%lf", &*x);
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return field(x,y);
    }
    printf("\ntype right border: ");
    ok = scanf("%lf", &*y);
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return field(x,y);
    }
}

double coefficient(double *wspol1)
{
    printf("\nType in coefficients: ");
    int ok=0;
    for(int i =0 ; i<3 ; i++)
    {
        ok = scanf("%lf",&wspol1[i]);
    }
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return coefficient(wspol1);
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
    printf("\npodaj amp: ");
    int ok = scanf ("%lf", &amp);
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return amplitude() ;
    }
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
    printf ("\ntype in probability percentage: ");
    int ok = scanf("%lf",&a);
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return noise_probability(array_function,array_noised,size,amp);
    }
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
    printf("\ntype in size of array: ");
    int a;
    int ok = scanf("%d",&a);
    if(a>500 || a<5 || ok!=1)
    {
        printf("\nWrong data, maximum size of array is 500 and minimum is 5, type again!\n");
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
    printf("\n1) GENERATE NEW FUNCTION\n2) READ FUNCTION\n3) QUIT\n");
    int ok = scanf("%d",&(*menu1));
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return welcome(menu1) ;
    }
}

void save_or_not(int *save)
{
    printf("\n1) SAVE FILE\n2) DO NOT SAVE FILE\n");
    int ok = scanf("%d", &(*save));
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return save_or_not(save);
    }


}

void next_menu(int *menu2)
{
    printf("************************\n1) NOISE THE FUNCTION\n2) FILTER THE FUNCTION\n3) GO BACK MENU\ntype: ");
    int ok = scanf("%d",&(*menu2));
    if(ok!=1)
    {
        printf("\nWrong data, type again!\n");
        return next_menu(menu2);

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

void read_length(int* size, char filename[])
{
    FILE* plik;
    plik = fopen(filename, "r");
    if (plik == NULL) 
    {
        printf("\ncouldnt open the file\n");
    }
    setlocale(LC_ALL, "polish_poland");
    char typo;int row= 0;
    typo = getc(plik);
    while (typo != EOF)
    {
        if (typo==10)
        {
            row = row + 1;
        }
        typo = getc(plik);
    }

    //printf("\nwiersze=%d", wiersze);

    setlocale(LC_ALL, "C");

    fclose(plik);

    *size = row;
}

void filtered_function(double *array_function, double* filtr_tab, int *size)
{
    double probes[5];
    int window = 5;
    for(int i =0; i< *size; i++)
        filtr_tab[i] = array_function[i];
    for (int i =0; i<*size-3; i++)
    {
        for(int p=0; p< window; p++)
        {
            probes[p] = array_function[p+i];
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<window-1; j++)
            {
                if(probes[j]> probes[j+1])
                {
                    double temp=probes[j];
                    probes[j]= probes[j+1];
                    probes[j+1] = temp;
                }
            }
        }
        //for(int i=0;i<5;i++)printf("probka2[%d] = %lf\n", i , probes[i]);
        *(filtr_tab+2+i) = *(probes+2);
    }//for(int i=0;i<okno;i++)printf("probka[%d] = %lf", i , probes[i]);

   // for(int i = 0; i <*size; i++)
       // printf("test[%d] = %lf\n",i, filtr_tab[i]);
       printf("\nFILTERED!\n");

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