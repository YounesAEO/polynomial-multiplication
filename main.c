#include "poly.h"
#include "time.h"
#include "math.h"

int main(int argc, char *argv[]) {
    poly *A, *B, C;
    int m=13;
    int deg=10;

    if(argc == 2){
        A = init();
        B = init();
        m = atoi(argv[1]);
    }else if(argc == 3){
        A = generate((int)atoi(argv[2]));
        B = generate((int)atoi(argv[2]));
        m = atoi(argv[1]);
    }else {
        A = init();
        B = init();
    }

    printf("\n Naive : \n");
    clock_t begin = clock();
    C = mult(A, B);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n Produit sur Z : \n"); 
    degree_max(&C);
    print(&C);

    printf("\n Produit sur Z/pZ : \n"); 
    C = mod(C, m);
    degree_max(&C);
    print(&C);

    printf("\n Temps d'execution : %lf \n", time_spent);
    
    printf("\n---------------------------------------------------------------\n");
    

    printf("\n karatsuba : \n");
    begin = clock();
    C = karatsuba(*A, *B);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n Produit sur Z : \n"); 
    degree_max(&C);
    print(&C);

    printf("\n Produit sur Z/pZ : \n"); 
    C = mod(C, m);
    degree_max(&C);
    print(&C);

    printf("\n Temps d'execution : %lf \n", time_spent);
    
    printf("\n---------------------------------------------------------------\n");
    
    printf("\n Toom cook : \n");
    printf("\n Produit sur Z : \n");
    
    begin=clock();
    C = toomcook(*A, *B, m);
    end=clock();
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    degree_max(&C);
    print(&C);
    
    printf("\n Produit sur Z/pZ : \n");
    
    C = mod(C, m);
    degree_max(&C);
    print(&C);

    printf("\n Temps d'execution : %lf \n", time_spent);
		
    return EXIT_SUCCESS;
}