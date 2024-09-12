#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char** argv){
    double lower = -M_PI/2;     //lower limit of integration
    double upper = M_PI/2;      //upper limit of integration
    int N = 10000000;           //number of points sampled
    double count = 0;           //maintains a count of points that fall in the desired area (under the curve)

    for(int i=1; i<=N; i++){
        //we sample a point in the loop
        double x = lower + M_PI*(double)rand()/(double)RAND_MAX;
        double y = rand()/(double)RAND_MAX;
        //since maximum value in y is 1, there is no need to scale the sampled value
        //if this value at some x is less than cos(x), the point lies under the curve
        if(y <= cos(x)) count++;
    }
    double area = count*M_PI/(double)N;
    printf("The area under the curve is: %.6f\n", area);
    return 0;
}
