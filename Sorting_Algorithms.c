#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define N 30000 // Individual numbers on matrix.
#define M 4 // Number of methods to run.
#define pass 20 // Number of times each method will run.

struct data{
    int Time[M];
    long Swaps[M];
};

// Unique number generator.
int getUniqueNumber(int p[N], int i);

// Methods
int straight_selection(int p[]);
int straight_insert(int p[]);
int quick_sort(int left, int right, int p[]);
int bubble_sort(int p[]);


void printToTxt(struct data *Results);
void copyMatrix(int p[],int r[]);



main()
{

    int p[N],s[N],i,diffTime,count,swaps;
    struct data Results[pass];

    time_t startTime,endTime;


    for(count=0;count<pass;count++)
    {

        printf("Running %d out of %d passes\n",count+1,pass);

        for (i=0; i<N; i++)
            p[i] = getUniqueNumber(p,i); //Generating N individual numbers and storing them in p matrix.


        copyMatrix(p,s); //Copying original matrix to s matrix to preserve it from changes.
        time(&startTime);
        swaps=bubble_sort(s);
        time(&endTime);
        diffTime = endTime - startTime;
        Results[count].Time[0] = diffTime; //Storing execution time for Bubble Sort.
        Results[count].Swaps[0] = swaps; //Storing number of swaps for Bubble Sort.

        copyMatrix(p,s);
        time(&startTime);
        swaps=straight_selection(s);
        time(&endTime);
        diffTime = endTime - startTime;
        Results[count].Time[1] = diffTime; //Storing execution time for Straight Selection.
        Results[count].Swaps[1] = swaps; //Storing number of swaps for Straight Selection.

        copyMatrix(p,s);
        time(&startTime);
        swaps=straight_insertion(s);
        time(&endTime);
        diffTime = endTime - startTime;
        Results[count].Time[2] = diffTime; //Storing execution time for Straight Insertion.
        Results[count].Swaps[2] = swaps; //Storing number of swaps for Straight Insertion.

        copyMatrix(p,s);
        time(&startTime);
        swaps=quick_sort(0,N-1,s);
        time(&endTime);
        diffTime = endTime - startTime;
        Results[count].Time[3] = diffTime; //Storing execution time for Quick Sort.
        Results[count].Swaps[3] = swaps; //Storing number of swaps for Quick Sort.

    }

    printToTxt(&Results); //Printing results to Swaps.txt and Times.txt respectively.

    printf("\nCheck the program folder for the results\n");
    getch();
}

int getUniqueNumber(int p[], int i)
{
    int x, j, found;
    do
    {
        x = rand()%32768;
        found = 0;
        j = 0;
        while (j<=i && found == 0)
        {
            if (p[j] == x)
                found = 1;
            else
                j++;
        }
    }while(found == 1);
    return x;
}

void copyMatrix(int p[],int r[])
{
     int i;
     for(i=0;i<N;i++)
         r[i] = p[i];
}

void printToTxt(struct data *Results)
{
   int count,i,j=0;
   double avgTime[4],avgSwaps[4]; //Declaring average time and changes matrices.
   FILE *times,*swaps;
   times = fopen("Times.txt","w"); //Opening Times.txt file for writing.
   swaps = fopen("Swaps.txt","w"); //Opening Swaps.txt file for writing.


    //Printing to Times.txt file

    for(i=0;i<4;i++)
        avgTime[i]=0; //Nullifying matrix fields.

    for(i=0;i<4;i++)
        avgSwaps[i]=0; //Nullifying matrix fields.

   fprintf(times,"ARRAY SIZE=%d\n",N);
   fprintf(times,"\t\tTABLE OF EXECUTION TIMES (in seconds)\n");
   fprintf(times,"\tBubble_sort \tSelection_sort \tInsertion_sort\tQuick_sort\n");
   fprintf(times,"\t===========     =============   =============   ==========\n");

    for(count=0;count<pass;count++)
    {
       for(i=0;i<4;i++)
       {
            fprintf(times,"\t%d\t",Results[count].Time[i]); //Printing times to Times.txt file.
            avgTime[i] += Results[i].Time[i]; //Summing up execution times for each method.

       }

    fprintf(times,"\n\n");
    }
    for(i=0;i<4;i++)
        avgTime[i]=avgTime[i]/pass; //Getting average time for every method.


    fprintf(times,"Avg:  %2.2f\t\t %2.2f\t\t %2.2f\t\t %2.2f\n",avgTime[0],avgTime[1],avgTime[2],avgTime[3]);
    fclose(times); //Closing Times.txt file.


/*=================================================================================================================*/
    //Printing to Swaps.txt file

    fprintf(swaps,"ARRAY SIZE=%d\n",N);
    fprintf(swaps,"\t\t\t\tTABLE OF SWAPS\n");
    fprintf(swaps,"\tBubble_sort \t  Selection_sort \t Insertion_sort\t    Quick_sort\n");
    fprintf(swaps,"\t===========\t  =============\t         =============\t     ==========\n");

    for(count=0;count<pass;count++)
    {
        for(i=0;i<4;i++)
       {
            fprintf(swaps,"\t%d\t",Results[count].Swaps[i]); // Printing number of swaps to Swaps.txt file.
            avgSwaps[i] += Results[i].Swaps[i]; //Summing up number of swaps.
       }

    fprintf(swaps,"\n\n");
    }
        for(i=0;i<4;i++)
            avgSwaps[i]=avgSwaps[i]/pass; //Getting average number of swaps.

    fprintf(swaps,"Avg:   %11.1f\t%11.1f\t\t%11.1f\t%11.1f\n",avgSwaps[0],avgSwaps[1],avgSwaps[2],avgSwaps[3]);
    fclose(swaps); //Closing Swaps.txt file.
}

int straight_selection(int p[])
{
    int i,k,j,min,swaps=0;;

    for(i=0;i<N-1;i++)
    {
        k=i;
        min=p[i];
        for(j=i+1;j<N;j++)
        {
            if(p[j]<min)
            {
                k=j;
                min=p[j];
                swaps += 1; //Counting number of swaps.
            }
        }
        p[k]=p[i] ;
        p[i]=min;
     }
return swaps;
}

int straight_insertion(int p[])
{
     int i,x,j,swaps=0;
     for (i = 1; i < N; i++)
     {
         x = p[i];
         j = i-1;
         while ((x < p[j]) && (j >= 0))
         {
               p[j+1] = p[j] ;
               j = j-1 ;
               swaps += 1; //Counting number of swaps.
         }
         p[j+1] = x ;

     }
return swaps;
}

int bubble_sort(int p[])
{
     int i,j,temp,swaps=0;

     for(i=1; i<N; i++)
         for (j=N-1; j>=i; j--)
         {
             if (p[j-1] > p[j])
             {
                temp = p[j-1];
                p[j-1] = p[j] ;
                p[j] = temp ;
                swaps += 1; //Counting number of swaps.
             }
         }
return swaps;
}

int quick_sort(int left, int right, int p[])
{
     int i, j, mid, x, temp,swaps=0;
     if (left < right)
     {
        i = left;
        j = right;
        mid = (left+right)/2;
        x = p[mid];
        while (i < j)
        {
              while (p[i] < x)
              {
                    i++;
              }
              while (p[j] > x)
              {
                    j--;
              }
              if (i < j)
              {
                 if (p[i] == p[j])
                 {
                    if (i<mid)
                       i++;
                    if (j>mid)
                       j--;
                 }
                 else
                 {
                     temp = p[i];
                     p[i] = p[j];
                     p[j] = temp;
                     swaps += 1; //Counting number of swaps.
                 }
              }
        }
        quick_sort(left,j-1,p);
        quick_sort(j+1,right,p);
     }
return swaps;
}

