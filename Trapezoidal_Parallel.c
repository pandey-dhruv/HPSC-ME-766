#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv){
    double x0 = -1*M_PI/2;
    double xN = M_PI/2;
    int N = 2000000000;
    double interval = (xN - x0)/N;
    double integration = cos(x0) + cos(xN);
    #pragma omp parallel for shared(x0, interval) reduction(+:integration)
    for(int i=1; i<=N-1; i++){
        double xk = x0 + i*interval;
        integration = integration + 2*cos(xk);
    }
    integration = integration*(interval/2);
    printf("The value of the integration is: %.10f", integration);
    printf("\n");
    return 0;
}