#include "poly.h"


poly* init()
{
	int i;
  int w;
	poly *P = (poly*)malloc(sizeof(poly));  //Alloue de la mémoire pour la structure

	printf("Entrez le degre de P :  ");
	scanf("%d", &(P->degree));

	P->coeff = (int*)calloc((P->degree+1), sizeof(int));     // Alloue degree+1 case de int

	for (i=0; i <= P->degree; i++)       // Demande les valeurs des coéfficients à l'utilisateur
	{
		printf("Entrez le coef de degre %d de P :", i);
		scanf("%d",&w);
        P->coeff[i]=w;
	}
	return P;       // Renvoie ce nouveau polynome
}

poly mult(poly *P1, poly *P2)
{
	int i,j;
	poly P3;
    P3 = create(P1->degree + P2->degree);      // Alloue la mémoire pour le polynome produit

	for (i = 0; i <= P1->degree;i++)
	{
		for (j = 0; j <= P2->degree; j++)
		{
			P3.coeff[i+j] += P1->coeff[i] * P2->coeff[j];       // Multiplie les coéfficients en tenant compte de leur degré
		}
	}

	return P3;      // Renvoie ce polynome
}

void print(poly *P)
{
	int i;

	printf("\nLe polynome est : \n");
  printf("[");
	for (i = 0; i <= P->degree; i++)     // Pour chaque 0 <= i <= degree
	{
		printf(" %d, ", P->coeff[i], i);       // Affiche le coéfficients du degree i
	}
  printf("]");
}

int i = 0;
poly karatsuba(poly A,poly B){
  int n;
  n= (A.degree>B.degree) ? A.degree:B.degree;

  // if (n == 0){
    
  //   poly r = create(n);
  //   r.coeff[n] = A.coeff[n]*B.coeff[n];
  //   return r;
  // }

  // if(n == 0) exit(0);

  // if(n % 2 != 0){
  //     n++;
  //     if(A.degree>B.degree){
  //         A.degree++;
  //         A.coeff = (int*) realloc(A.coeff,(A.degree+1)*sizeof(int));
  //         A.coeff[A.degree-1] = 0;
  //     }else{
  //         B.degree++;
  //         B.coeff = (int*) realloc(B.coeff,B.degree*sizeof(int));
  //         B.coeff[B.degree-1] = 0;
  //     }
  // }
  // Si le degré polynome de plus haut degré est inférieur ou égale à deux alors on appelle la multiplication standard
  if (n < 3) return mult(&A, &B);
  n = (n/2);  // On divise le degré par deux
  poly A0,A1,B0,B1,R1,R0,R2,R,x;

  A0 = firstpart(A,n);        // On recupère la première moitiée du polynome 1
  A1 = lastpart(A,n);     // On recupère la dernière moitiée du polynome 1

  B0 = firstpart(B,n);        // On recupère la première moitiée du polynome 2
  B1 = lastpart(B,n);     // On recupère la dernière moitiée du polynome 1

  R1 = karatsuba(add(A0,A1),add(B0,B1));
  R0 = karatsuba(A0, B0);
  R2 = karatsuba(A1, B1);

  x = add(negative(R0), negative(R2));
  R1 = add(R1,x);

  R1 = shift(R1, n+1);      // On corrige le décalage causé par la séparation en deux des polynomes
  R2 = shift(R2, 2*n+2);

  R = add(R0,R1);
  R = add(R,R2);

  return R;      // On renvoie
  }

  poly firstpart(poly p, int k)
  {
  poly r;
  int i;

  if (k<=0)
  {
    r = create(0);
    return r;
  }

  r = create(k);      // On créer un nouveau polynome de degré k
  for (i=0; i<=k && i<=p.degree; i++)
  {
    r.coeff[i] = p.coeff[i];     // On recopie les k premiers coéfficients dans ce nouveau polynome
  }

  return r;      // On renvoie ce polynome
  }

  poly lastpart(poly p,int k)
  {
  poly r;
  int i;

  if (k<0)
  {
    r = create(0);
    return r;
  }

  r = create(p.degree-k-1);       // On créer un nouveau polynome de degré k-1
  for (i = 0; i < p.degree-k && i<=p.degree; i++)
  {
    r.coeff[i] = p.coeff[i+k+1];       // On recopie les k-1 derniers coéfficients dans ce nouveau polynome
  }

  return r;     // On renvoie ce polynome

  }

  poly shift(poly p, int k)
  {
  int i;
  poly r;

  r = create(p.degree +k);     // On créer un nouveau polynome dont le degré est augmenté de k par rapport au polynome original

  for (i=0; i <= p.degree ;i++)
    r.coeff[k+i]=p.coeff[i];        // On décalle les coéfficients d'un degré k

  return r;      // On renvoie ce polynome
  }

  poly add(poly p,poly q)
  {
  int i;
  poly r;

  if (p.degree>=q.degree)  i=p.degree;
  else i=q.degree;

  r = create(i);      // On créer un nouveau polynome dont le degré équivaut celui du polynome de plus haut degré

  for (i=0; i <= r.degree;i++)        // Pour chaque i inférieur à ce degré on additionne les coéfficients
  {
      if (i <= p.degree && i <= q.degree)
          r.coeff[i] = p.coeff[i] + q.coeff[i];
      else if (i <= p.degree)
          r.coeff[i] = p.coeff[i];
      else
          r.coeff[i] = q.coeff[i];
  }

  return r;
  }

  poly negative(poly p)
  {
  int i;
  poly r;
  r = create(p.degree);   // On créer un nouveau polynome de même degré
  for (i = 0; i <= r.degree; i++)
  {
    r.coeff[i] = -1 * p.coeff[i];       // Pour chaque coéfficient on prend l'opposé
  }
  return r;     // On renvoie ce polynome
  }

  void degree_max(poly * p)
  {
  int i = p->degree;
  while (p->coeff[i] == 0 && i>0)       // Tant que les coéfficients sont nuls, on diminue le degré du polynome
  {
      p->degree--;
      i--;
  }
  }

  poly create(int degree)
  {
    poly A;
    A.coeff = (int *)calloc(sizeof(int), (size_t) (degree + 1));     // On alloue degree + 1 int dans la mémoire
    A.degree = degree;        // Le degré de ce nouveau polynome est degre
    return A;       // On renvoie ce polynome
  }

  poly* generate(int degree)
  {
    poly *P = (poly*)malloc(sizeof(poly));
    P->degree = degree;
    
    P->coeff = (int*)calloc((P->degree+1), sizeof(int));
    
    for(int i=0; i<=degree; i++){
      P->coeff[i] = rand()%degree;
    }

    return P;
  }

poly scalarMul(poly p,int x)
  {
  poly r;
  r = create(p.degree);      // On créer un nouveau polynome dont le degré équivaut celui du polynome de plus haut degré

  for (int i=0; i <= r.degree;i++)        // Pour chaque i inférieur à ce degré on additionne les coéfficients
  {
      r.coeff[i] = x*p.coeff[i];
  }

  return r;
  }

poly scalarDiv(poly p,int x)
  {
  poly r;
  r = create(p.degree);      // On créer un nouveau polynome dont le degré équivaut celui du polynome de plus haut degré

  for (int i=0; i <= r.degree;i++)        // Pour chaque i inférieur à ce degré on additionne les coéfficients
  {
      r.coeff[i] = x/p.coeff[i] + 1;
  }

  return r;
  }

int gcdExtended(int a, int b, int* x, int* y)
{
	if (a == 0)
	{
		*x = 0, *y = 1;
		return b;
	}

	int x1, y1;
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

int inverse(int a, int m){
  int x, y;
	int g = gcdExtended(a, m, &x, &y);
	if (g != 1){
    return 0;
  }else {
    return (x % m + m) % m;
  }
  
}


poly firstpart2(poly p, int k)
  {
  poly r;
  int i;

  if (k<=0)
  {
    r = create(0);
    return r;
  }

  r = create(k-1);      // On créer un nouveau polynome de degré k
  for (i=0; i<k && i<=p.degree; i++)
  {
    r.coeff[i] = p.coeff[i];     // On recopie les k premiers coéfficients dans ce nouveau polynome
  }

  return r;      // On renvoie ce polynome
  }

poly lastpart2(poly p,int k)
{
poly r;
int i;

if (k<0)
{
  r = create(0);
  return r;
}

r = create(p.degree-k);       // On créer un nouveau polynome de degré k-1
for (i = 0; i <= p.degree-k && i<=p.degree; i++)
{
  r.coeff[i] = p.coeff[i+k];       // On recopie les k-1 derniers coéfficients dans ce nouveau polynome
}

return r;     // On renvoie ce polynome

}

poly mod(poly A, int m){
  poly r;
  r = create(A.degree);
  for(int i = 0; i<=A.degree; i++){
    r.coeff[i] = (A.coeff[i] % m + m ) % m;
  }

  return r;
}


poly toomcook(poly A, poly B, int m){
  int n;
  n= (A.degree>B.degree) ? A.degree:B.degree;

  if (n<3){
    return karatsuba(A,B);
  }
  
  int k1 = n/3;
  int k2 = 2*n/3;
  
  poly Ai,Bi,A0,A1,A2,B0,B1,B2,C0,C1,C2,C3,C4,C,t1,t2,v0,v1,v01,v2,vinf;
  
  Ai = firstpart2(A,k2);
  A2 = lastpart2(A,k2);
  A0 = firstpart2(Ai,k1);
  A1 = lastpart2(Ai,k1);

  Bi = firstpart2(B,k2);
  B2 = lastpart2(B,k2);
  B0 = firstpart2(Bi,k1);
  B1 = lastpart2(Bi,k1);

  v0 = toomcook(A0,B0, m);
  v1 = toomcook(add(A1,add(A0,A2)), add(B1,add(B0,B2)), m);
  v01 = toomcook(add(add(A0,A2),negative(A1)), add(add(B0,B2),negative(B1)), m);
  v2 = toomcook(add(A0, add(scalarMul(A1,2),scalarMul(A2,4))),add(B0, add(scalarMul(B1,2),scalarMul(B2,4))), m);
  vinf = toomcook(A2,B2, m);

  t1 = add(scalarMul(add(add(scalarMul(v0,3),scalarMul(v01,2)),v2), inverse(6,m)),scalarMul(negative(vinf),2));
  t2 = scalarMul(add(v1, negative(v01)), inverse(2,m));

  C0 = v0;
  C1 = add(v1, negative(t1));
  C2 = add(t2, add(negative(v0),negative(vinf)));
  C3 = add(t1,negative(t2));
  C4 = vinf;
  
  C1 = shift(C1, k1+1);    // On corrige le décalage causé par la séparation en deux des polynomes
  C2 = shift(C2, 2*k1+2);
  C3 = shift(C3, 3*k1+3);
  C4 = shift(C4, 4*k1+4);

  C = add(C0,add(C1, add(C2,add(C3,C4))));

  return C;
}