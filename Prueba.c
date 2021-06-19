#include<stdio.h>
#include<stdlib.h>

// ------------------------------------- //
// -- GeneraciÃ³n del vector de tiempo -- //
// ------------------------------------- //

double* genTiempo(double ti, double tf, int N);

// -- Entrada(s) -- //

double ti=1;
double tf=2;
int N=4;
double h=1/3;

double (*x_in)(double);
//
double escalon(double);
// ------------ //
// -- EDO #1 -- //
// ------------ //
double edo(double t, double x, double x_in_valor);

// ---------------------------- //
// -- EDOs - MÃ©todo de Euler -- //
// ---------------------------- //
void euler(double *px, double h, double* pt, int N, double(*edo)(double t, double x, double x_in_valor), 
    double(*x_in)(double t));

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

int main() {

    /*  ----------------------
        -- Vector de tiempo --
        ----------------------
    */
    double ti;
    double tf;
    unsigned int N;
    double h = (tf - ti) / N;

    double t[N], x[N];
    double *pt = &t[0];
    double *px = &x[0];

    pt = genTiempo(ti, tf, N);

    *(px + 0) = 1.0;

    euler(px, h, pt, N, edo, x_in);

}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------- //
// -- GeneraciÃ³n del vector de tiempo -- //
// ------------------------------------- //
double *genTiempo(double ti, double tf, int N) {
    double *t = malloc(N*sizeof(double));
    double h = (tf - ti) / N;
    for(int i = 0; i < N; i++) {
        *(t + i) = ti + i*h;
    }
    return t;
}

// ---------------------------- //
// -- EDOs - MÃ©todo de Euler -- //
// ---------------------------- //
void euler(double *px, double h, double *pt, int N, double (*edo)(double, double, double), 
    double(*x_in)(double t)) {
    // x[0] = x0
    // x[i+1] = x[i] + h * edo(t[i], x[i], x_in[i]), para i = 0, ..., (N-1)
    double temp1 = 0.0;
    double temp2 = 0.0;
    for(int i = 0; i < N; i++) {
        temp1 = (*x_in)(*(pt + i));
        temp2 = (*edo)(*(pt + i), *(px + i), temp1);
        *(px + i + 1) = *(px + i) + (h * temp2);
    }
}
