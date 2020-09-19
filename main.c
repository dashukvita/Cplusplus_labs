#include <stdio.h>
#include <stdlib.h>

#define M 1

void createNewArray(int [], int);
void printArray(int [], int);
void sortBubble(int [], int );
int binarySearch(int [],int, int);
void createNewMatrix(int [][M], int);
void printMatrix(int [][M], int);
void transposeMatrix(int [][M], int);

int main()
{
    int size_m = M;
    int arr[size_m];
    int matrix[size_m][size_m];
    int a, result;

    printf ("Create new Array: \n");
    createNewArray(arr, size_m);
    printArray(arr, size_m);

    printf ("\nSorting array: \n");
    sortBubble(arr, size_m);
    printArray(arr, size_m);

    printf ("\nBinary search: \n");
    printf ("Enter the number to search:  ");
    scanf("%d", &a);
    result = binarySearch(arr, size_m, a);
    if (result != -1) printf("We found element %d in %d cell.\n", a, result);
    else printf("There is no element in the array.\n");

    printf ("\nCreate new Matrix: \n");
    createNewMatrix(matrix, size_m);
    printMatrix(matrix, size_m);

    printf ("Transpose matrix: \n");
    transposeMatrix(matrix, size_m);
    printMatrix(matrix, size_m);

    return 0;
}

void createNewArray(int mas[], int size_m)
{
    int i;
    for (i = 0; i < size_m; i++)
        mas[i] = rand() % 100 + 1;
}

void printArray(int mas[], int size_m)
{
    int i;
    for (i = 0; i < size_m; i++)
    {
        printf("%d ", mas[i]);
    }
    printf("\n");
}

void sortBubble(int mas[], int size_m)
{
    int i,j,temp;
    for (i= size_m-1; i>=0; i--)
        for (j=0; j<i; j++)
            if (mas[j]>mas[j+1])
                {
                    temp=mas[j], mas[j]=mas[j+1], mas[j+1]=temp;
                }
}

int binarySearch(int mas[],int size_m, int search_m)
{
    int  low, high, mid;
    low = 0;
    high = size_m - 1;
    while ( low <= high)
    {
        mid = (low+high)/2;
        if (search_m < mas[mid])  high = mid - 1;
        else if (search_m > mas[mid]) low = mid + 1;
        else return mid;
    } return -1;
}

void createNewMatrix(int matrix[][M], int size_m)
{
    int i,j;
    for (i = 0; i < size_m; i++)
      for (j = 0; j < size_m; j++)
        matrix[i][j] = rand() % 100 + 1;
}

void printMatrix(int matrix[][M], int size_m)
{
    int i,j;
    for (i = 0; i < size_m; i++)
    {
        for (j = 0; j < M; j++)
      {
          printf("\t%d ", matrix[i][j]);
      }
      printf("\n");
    }

}
void transposeMatrix(int matrix[][M], int size_m)
{
    int i,j,temp;
    for (i = 0; i < size_m-1; i++)
      for (j = i+1; j < M; j++)
        temp=matrix[i][j], matrix[i][j]=matrix[j][i], matrix[j][i]=temp;
}
