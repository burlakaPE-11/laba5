#include <stdio.h>
#include <stdlib.h>

int writeToBin(FILE *fPointer,int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    for(i = 0; i<=N; i++)
    {
        n++;
        y=x1*2;
        fwrite(&x1,sizeof(int),1,fPointer);
        fwrite(&y,sizeof(int),1,fPointer);
        if(x1==x2)
        {
            break;
        }
        x1+=delta;
    }
   fclose(fPointer);
   return n;
}

void readFromBin(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("Bin File (result.bin) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("-------------------------------------------------\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("-------------------------------------------------\n");
    for(i = 1; i < n+1;i++)
    {
        fread(&x,sizeof(int),1,fPointer);
        fread(&y,sizeof(int),1,fPointer);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    fclose(fPointer);
}

int writeToTxt(FILE *fPointer,int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    for(i = 0; i<=N; i++)
    {
        n++;
        y=x1*2;
        fprintf(fPointer,"%d %d\n",x1,y);
        if(x1>=x2)
        {
            return n;
        }
        x1+=delta;
    }
    fclose(fPointer);
    return n;
}

void readFromTxt(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("Txt File (result.txt) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("-------------------------------------------------\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("-------------------------------------------------\n");
    for(i = 1; i < n+1;i++)
    {
        fscanf(fPointer,"%d",&x);
        fscanf(fPointer,"%d",&y);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    fclose(fPointer);
}


int ** memoryAllocation(int rows, int cols)
{
    int i = 0;
    int **matrix = (int **)malloc(rows*sizeof(int *));
    for( i = 0; i < rows; i++)
    {
      matrix[i] = (int *)malloc(cols*sizeof(int));
    }
    return matrix;
}

void saveResultToArray(FILE *fPointer,int n)
{
   int i,j,k;
   int **arr = (int **)malloc(n*sizeof(int*));
   for( i = 0; i < n; i++)
   {
      arr[i] = (int *)malloc(2*sizeof(int));
   }
   printf("Array content :\n");
   for(i = 0;i<n;i++)
   {
       for(j = 0;j<2;j++)
       {
           fscanf(fPointer,"%d",&k);
           arr[i][j] = k;
       }
   }
   for(i = 0;i<n;i++)
   {
       for(j = 0;j<1;j++)
       {
            printf("x: %d \ty: %d\n",arr[i][j],arr[i][j+1]);
       }
   }
   for(i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int main()
{
    printf("my function F(x) = x*2\n");
    unsigned int N,delta,n;
    int x1,x2;
    char group[50];
    FILE *fInput;
    FILE *fReadTxt, *fWriteTxt;
    FILE *fReadBin, *fWriteBin;

    fInput = fopen("input.dat","r");
    if(fInput == NULL)
    {
        printf("Can't open file\n");
        return 0;
    }

    fscanf(fInput,"%s%d%d%u%u",&group,&x1,&x2,&N,&delta);
    fclose(fInput);
    printf("group = %s\n",group);
    printf("x1 = %d\n",x1);
    printf("x2 = %d\n",x2);
    printf("N = %u\n",N);
    printf("step = %u\n",delta);

    fWriteTxt = fopen("result.txt","w");
    n = writeToTxt(fWriteTxt,x1,x2,N,delta);
    fclose(fWriteTxt);

    fReadTxt  = fopen("result.txt","r");
    readFromTxt(fReadTxt,n,x1,x2);
    fclose(fReadTxt);

    fWriteBin = fopen("result.bin","wb");
    n = writeToBin(fWriteBin,x1,x2,N,delta);
    fclose(fWriteBin);

    fReadBin  = fopen("result.bin","rb");
    readFromBin(fReadBin,n,x1,x2);
    fclose(fReadBin);

    fReadTxt  = fopen("result.txt","r");
    saveResultToArray(fReadTxt,n);
    fclose(fReadTxt);
    return 0;
}
