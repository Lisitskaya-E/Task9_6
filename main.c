#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
void swap(float *a, float *b)
{
    float t  =*a;
    *a=*b;
    *b= t;
}
void func(float **a,int n,int i)
{
    int j=i;
    float m;
    m=fabs(a[i][i]);
    for(int k=i+1; k<n; k++)
    {
        if(fabs(a[k][i])>m)
        {
            j=k;
            m=fabs(a[k][i]);
        }
    }
    float t;
    for(int k=0; k<2*n; k++)
    {
        swap(&a[i][k], &a[j][k]);
    }
    for(int k=i; k<n; k++)
    {
        if(a[k][i])
        {
            for(j=i+1; j<2*n; j++)
            {
                a[k][j]=1.0*(a[k][j]/a[k][i]);
            }
            a[k][i]=1;
        }
    }
    for(int k=i+1; k<n; k++)
    {
        if(a[k][i])
        {
            for(j=0; j<2*n; j++)
            {
                a[k][j]-=a[i][j];
            }
        }
    }
    if(i<n-1)
    {
        func(a,n,i+1);
    }
}
void func2(float **a,int n,int i)
{
    for(int j=i+1; j<n; j++)
    {
        if(a[i][j])
        {
            for(int k=j+1; k<2*n; k++)
            {
                a[i][k]-=a[j][k]*a[i][j];
            }
            a[i][j]=0;
        }
    }
    if(i<n-2)
    {
        func2(a,n,i+1);
    }
}
int main()
{
    setlocale(LC_ALL,"Rus");
    float **a, **b;
    int n;
    printf("Введите количество переменных:\n");
    scanf("%d",&n);
    printf("Введите матрицу:\n");
    a=(float**)malloc(n*sizeof(float*));
    b=(float**)malloc(n*sizeof(float*));

    for(int i=0; i<n; i++)
    {
        a[i]=(float*)malloc((2*n)*sizeof(float));
        b[i]=(float*)malloc((n)*sizeof(float));

        for(int j=0; j<n; j++)
        {
            scanf("%f", &a[i][j]);
            b[i][j]=a[i][j];


        }
        for(int j=n; j<2*n; j++)
        {
            if(j-i==n)
            {
                a[i][j]=1;
            }
            else
            {
                a[i][j]=0;
            }
        }
    }

    printf("\nОбратная матрица:\n");
    func(a, n, 0);
    func2(a,n,0);

    for(int i=0; i<n; i++)
    {
        for(int j=n; j<2*n; j++)
        {
            printf("%f ",a[i][j]);

        }
        printf("\n");
    }
    printf("Перемноженные матрицы:\n");
    float c[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j]=0;
            for(int k = 0; k < n; k++)
            {

                c[i][j] += b[i][k] * a[k][j+n];

            }
            printf("%f ", c[i][j]);
        }
        printf("\n");
    }


    return 0;
}
