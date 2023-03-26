#include<stdio.h>
#include<stdlib.h>
#define MAX_DEGREE 101
#define MAX_TERMS 101
typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

typedef struct {
    float coef;
    int expon;
} polynomial2;

polynomial2 terms[MAX_TERMS] = { {7,6}, {5,3}, {9,2}, {1,0}, {5,3},{2,2},{1,1},{10,0} };
int avail = 8;

polynomial poly_mul1(polynomial A, polynomial B)
{
    polynomial C = { 0 };
    C.degree = A.degree + B.degree;
    for (int i = 0; i <= A.degree; i++) {
        for (int j = 0; j <= B.degree; j++) {
            C.coef[i + j] += A.coef[i] * B.coef[j];
        }
    }
    return C;
}
void print_poly(polynomial p)
{
    for (int i = p.degree; i > 0; i--)
        printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
    printf("%3.1f \n", p.coef[p.degree]);
}

void attach(float coef, int expon)
{
    if (avail > MAX_TERMS) {
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

void poly_mul2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce)
{
    float tempcoef;
    int i, j, index;
    polynomial2 poly_terms[MAX_TERMS] = { 0 };

    for (i = As; i <= Ae; i++) {
        for (j = Bs; j <= Be; j++) {
            index = terms[i].expon + terms[j].expon;
            tempcoef = terms[i].coef * terms[j].coef;
            poly_terms[index].coef += tempcoef;
            poly_terms[index].expon = index;
        }
    }

    *Cs = avail;
    for (i = MAX_TERMS - 1; i >= 0; i--) {
        if (poly_terms[i].coef != 0) {
            attach(poly_terms[i].coef, poly_terms[i].expon);
        }
    }
    *Ce = avail - 1;
}

void print_poly2(int s, int e)
{
    for (int i = s; i <= e; i++) {
        if (terms[i].coef != 0) {
            printf("%3.1fx^%d", terms[i].coef, terms[i].expon);
            if (i != e) {
                printf(" + ");
            }
        }
    }
    printf("\n");
}

int main(void)
{
    int As = 0, Ae = 3, Bs = 4, Be = 7, Cs, Ce;
    polynomial a = { 3,{ 4, 3, 2, 1 } };
    polynomial b = { 2,{ 3, 2, 8 } };
    polynomial c;

    print_poly(a);
    print_poly(b);
    c = poly_mul1(a, b);
    printf("-------------------모든항을배열에저장-------------------\n");
    print_poly(c);

    printf("------------------------------------------------\n");
    printf("------------------------------------------------\n");

    poly_mul2(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly2(As, Ae);
    print_poly2(Bs, Be);
    printf("-------------------전역배열------------------\n");
    print_poly2(Cs, Ce);
    
    system("pause");
    return 0;
}