#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

int INFINITY =  1000000000;

int fun_min(int x, int y);
void floyd_v2(int * matrix, int V);

void floyd_v1(int * matrix, int V);

int main()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int V,E;
    scanf("%d %d",&V,&E);

    int * matrix = (int *)malloc( V* V * sizeof(int));
    int i,j;
    for(i=0;i<V;++i)
    {
        for(j=0;j<V;++j)
        {
            *(matrix + i*V + j)=INFINITY;
            if (i==j) *(matrix + i*V + j)=0;
        }
    }

    int x,y,w;
    for(i=0;i<E;++i)
    {
        scanf("%d %d %d",&x,&y,&w);
        if (*(matrix + (x-1)*V + (y-1))>w) *(matrix + (x-1)*V + (y-1))=w;
    }

    floyd_v1(matrix,V);

    for(i=0;i<V;++i)
    {
        for(j=0;j<V;++j)
        {
            printf("%d ",(*(matrix + i*V + j)));
        }
        printf("\n");
    }

    free(matrix);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + 1e-9*(end.tv_nsec - start.tv_nsec);
    printf("Total time: %lf\n",time_taken);
    return 0;
}

int fun_min(int x, int y)
{
    return (x>y)?y:x;
}


void floyd_v1(int * matrix, int V)
{
    register int i,j,k;
    for(k=0;k<V;++k)
    {
        #pragma omp parallel for private(i, j) shared(matrix,V) 

        for(i=0;i<V;++i)
        {
            register int* im = (matrix + i*V);
            register int* km = (matrix + k*V);
            for(j=0;j<V;++j)
            {
                if( (*(km + j)) == INFINITY ) continue;
                if( (*(im + k)) == INFINITY ) continue;
                if( (*(im + j)) > ( (*(im + k) ) + ( *(km + j) ) ) )
                    (*(im + j)) = ( (*(im + k) ) + ( *(km + j) ) );
            }
        }
    }
}

