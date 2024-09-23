#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double lower = -M_PI/2;     //lower limit of integration
double upper = M_PI/2;      //upper limit of integration
int N = 100000000;          //number of points sampled
double count = 0;           //maintains a count of points that fall in the desired area (under the curve)
double area;
double x_random[100000000];
double y_random[100000000];

int main(int argc, char** argv){
    for(int i=0; i<=N-1; i++){
        x_random[i] = (double)rand()/(double)RAND_MAX;
        y_random[i] = (double)rand()/(double)RAND_MAX;
    }
    #pragma omp parallel for shared(lower, N, x_random, y_random) reduction(+:count)
    for(int i=1; i<=N; i++){
        //we sample a point in the loop
        double x = lower + M_PI*x_random[i-1];
        double y = y_random[i-1];
        //since maximum value in y is 1, there is no need to scale the sampled value
        //if this value at some x is less than cos(x), the point lies under the curve
        if(y <= cos(x)) count++;
    }
    area = count*M_PI/(double)N;
    printf("The area under the curve is: %.6f\n", area);
    return 0;
}
