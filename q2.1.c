#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int INFINITY =  1000000000;

int fun_min(int x, int y);
// void floyd_v1(int * matrix, int V);
void floyd_v2(int * matrix, int V);
// void floyd_v3(int * matrix, int V);


int main()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int V,E;
    scanf("%d %d",&V,&E);

    int * matrix = (int *)malloc( V* V * sizeof(int));
    for(int i=0;i<V;++i)
    {
        for(int j=0;j<V;++j)
        {
            *(matrix + i*V + j)=INFINITY;
            if (i==j) *(matrix + i*V + j)=0;
        }
    }

    int x,y,w;
    for(int i=0;i<E;++i)
    {
        scanf("%d %d %d",&x,&y,&w);
        if (*(matrix + (x-1)*V + (y-1))>w) *(matrix + (x-1)*V + (y-1))=w;
    }

    floyd_v2(matrix,V);

    for(int i=0;i<V;++i)
    {
        for(int j=0;j<V;++j)
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


// void floyd_v1(int * matrix, int V)
// {
//     for(int k=0;k<V;++k)
//     {
//         for(int i=0;i<V;++i)
//         {
//             for(int j=0;j<V;++j)
//             {
//                 if(k==j) continue;
//                 if(k==i) continue;
//                 if( (*(matrix + k*V + j)) == INFINITY ) continue;
//                 if( (*(matrix + i*V + k)) == INFINITY ) continue;
//                 if( (*(matrix + i*V + j)) > ( (*(matrix + i*V + k) ) + ( *(matrix + k*V + j) ) ) ) 
//                     (*(matrix + i*V + j)) = ( (*(matrix + i*V + k) ) + ( *(matrix + k*V + j) ) );
//             }
//         }
//     }
// }


void floyd_v2(int * matrix, int V)
{
    register int i,j,k,kmj,imk, v;
    register int * km;
    register int * im;
    v = V;
    for(k=0;k<v;++k)
    {
        km = (matrix + k*v);
        for(i=0;i<v;++i)
        {
            im = (matrix + i*v);
            for(j=0;j+15<v;j+=16)
            {
                imk = (*(im + k));

                kmj = (*(km + j+0));
                if( (*(im + j+0)) > ( kmj + imk ) ) (*(im + j+0)) = ( kmj + imk );
                
                kmj = (*(km + j+1));
                if( (*(im + j+1)) > ( kmj + imk ) ) (*(im + j+1)) = ( kmj + imk );
                
                kmj = (*(km + j+2));
                if( (*(im + j+2)) > ( kmj + imk ) ) (*(im + j+2)) = ( kmj + imk );
                
                kmj = (*(km + j+3));
                if( (*(im + j+3)) > ( kmj + imk ) ) (*(im + j+3)) = ( kmj + imk );
                
                kmj = (*(km + j+4));
                if( (*(im + j+4)) > ( kmj + imk ) ) (*(im + j+4)) = ( kmj + imk );
                
                kmj = (*(km + j+5));
                if( (*(im + j+5)) > ( kmj + imk ) ) (*(im + j+5)) = ( kmj + imk );
                
                kmj = (*(km + j+6));
                if( (*(im + j+6)) > ( kmj + imk ) ) (*(im + j+6)) = ( kmj + imk );
                
                kmj = (*(km + j+7));
                if( (*(im + j+7)) > ( kmj + imk ) ) (*(im + j+7)) = ( kmj + imk );
                
                kmj = (*(km + j+8));
                if( (*(im + j+8)) > ( kmj + imk ) ) (*(im + j+8)) = ( kmj + imk );
                
                kmj = (*(km + j+9));
                if( (*(im + j+9)) > ( kmj + imk ) ) (*(im + j+9)) = ( kmj + imk );
                
                kmj = (*(km + j+10));
                if( (*(im + j+10)) > ( kmj + imk ) ) (*(im + j+10)) = ( kmj + imk );
                
                kmj = (*(km + j+11));
                if( (*(im + j+11)) > ( kmj + imk ) ) (*(im + j+11)) = ( kmj + imk );
                
                kmj = (*(km + j+12));
                if( (*(im + j+12)) > ( kmj + imk ) ) (*(im + j+12)) = ( kmj + imk );
                
                kmj = (*(km + j+13));
                if( (*(im + j+13)) > ( kmj + imk ) ) (*(im + j+13)) = ( kmj + imk );
                
                kmj = (*(km + j+14));
                if( (*(im + j+14)) > ( kmj + imk ) ) (*(im + j+14)) = ( kmj + imk );
                
                kmj = (*(km + j+15));
                if( (*(im + j+15)) > ( kmj + imk ) ) (*(im + j+15)) = ( kmj + imk );
            }
            while(j<v)
            {
                kmj = (*(km + j));
                imk = (*(im + k));
                if( (*(im + j)) > ( kmj + imk ) ) (*(im + j)) = ( kmj + imk );
                j++;
            }
        }
    }
}


// void FW_BLOCK(int * matrix,register int I,register int J,register int K,register int BLOCK,register int V)
// {
//     register int ii, jj, kk;
//     register int GOTILL = fun_min(V,K+BLOCK);
//     register int FH = fun_min(V, I+BLOCK);
//     register int FW = fun_min(V, J+BLOCK);
    
//     for(kk=K;kk<GOTILL;++kk)
//     {
//         for(ii=I;ii<FH;++ii)
//         {
//             register int aik = (*(matrix + ( V*(ii) ) + ( kk )));
//             for(jj=J;jj+15<FW;jj+=16)
//             {
//                 register int bkj = (*(matrix + ( V*( kk ) ) + ( jj + 0 )));
//                 register int * mm = (matrix + ( V*( ii ) ) + ( jj + 0 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 1 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 1 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 2 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 2 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 3 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 3 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 4 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 4 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 5 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 5 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 6 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 6 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 7 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 7 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 8 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 8 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 9 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 9 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 10 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 10 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 11 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 11 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 12 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 12 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 13 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 13 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 14 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 14 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
            
//                 bkj = (*(matrix + ( V*( kk ) ) + ( jj + 15 )));
//                 mm = (matrix + ( V*( ii ) ) + ( jj + 15 ));
//                 if( aik+bkj < (*(mm)) ) (*(mm))= aik + bkj;
//             }
//             while (jj<FW)
//             {
//                 register int bkj = (*(matrix + ( V*( kk ) ) + ( jj )));
//                 register int * mm = (matrix + ( V*( ii ) ) + ( jj ));
//                 if( aik+bkj < (*(mm)) )
//                     (*(mm))= aik + bkj;
//                 jj++;
//             }
            
//         }
//     }
// }

// void floyd_v3(int * matrix, int V)
// {
//     register int BLOCK=512,v = V;

//     for(register int K=0;K<v;K+=BLOCK)
//     {
//         // Diagonal update
//         FW_BLOCK(matrix,K,K,K,BLOCK,v);
        

//         // Panel Update
//         for(register int J=0;J<v;J+=BLOCK)
//         {
//             if(J!=K) 
//             {
//                 // row
//                 FW_BLOCK(matrix,K,J,K,BLOCK,v);
//                 // col
//                 FW_BLOCK(matrix,J,K,K,BLOCK,v);
//             }
//         }

//         // MinPlus Outer Product
//         for(register int I=0;I<v;I+=BLOCK)
//         {
//             if (I==K) continue;
//             for(register int J=0;J<v;J+=BLOCK)
//             {
//                 if(J!=K) 
//                 {
//                     FW_BLOCK(matrix,I,J,K,BLOCK,v);
//                 }
//             }
//         }
//     }
// }