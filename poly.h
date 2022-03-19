#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"

// Representation par coefficients d'un polynome
typedef struct poly_t {
  int degree;
  int * coeff;
}poly;

// Fonctions concernant la representation "coefficients"
//----------------------------------------------------------------------------------------------------------------------

// Initialise un polynome sous la representation "coefficients"
poly* init();

// Multiplie deux polynomes sous la representation "coefficients" : O(n^2)
poly mult(poly *, poly *);

// Affiche les coefficients d'un polynome sous la representation "coefficients"
void print(poly *P);

// Multiplie deux polynomes sous la representation "coefficients" en utilisant Karatsuba : O(n^log(3))
poly karatsuba(poly ,poly);

// Recupere les k premiers coefficients d'un polynome sous la representation "coefficients"
poly firstpart(poly, int);

// Recupere les k derniers coefficients d'un polynome sous la representation "coefficients"
poly lastpart(poly,int );

// Multiplie le polynome sous la representation "coefficients" par x^k
poly shift(poly ,int );

// Additionne deux polynomes sous la representation "coefficients"
poly add(poly , poly );

// Renvoie l'oppose d'un polynome sous la representation "coefficients"
poly negative(poly );

// Reduit le degre d'un polynome sous la representation "coefficients" en supprimant les coefficients inutiles
void degree_max(poly *);

// On créer un polynome de degré k
poly create(int );

// implementation de division euclidienne etendue
int gcdExtended(int, int, int*, int*);

// calcule l'inverse modulaire d'un entier
int inverse(int, int);

poly mod(poly, int);

poly* generate(int);
// Multiplie deux polynomes sous la representation "coefficients" en utilisant Toom-Cook : O(n^log(5)/log(3))
poly toomcook(poly, poly, int);
