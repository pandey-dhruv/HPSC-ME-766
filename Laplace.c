/*
*******************************************************************
* Laplace Serial Version
*
* T is initially 0.0
* Boundaries are as follows

*             T = 0              
*     |-------------------| 0    
*     |                   |      
*  T  |                   |      
*  =  |                   |  T   
*  0  |                   |      
*     |                   |      
*     |                   |      
*     |                   |      
*     |-------------------| 100  
*     0                 100
*
* Use Central Differencing Method
*
*Modified by Shiva Gopalakkrishnan, NPS...2010
*Modified by  John Urbanic,  PSC.... 2008;
* From the original Fortran version by Sushell Chitre, R Reddy, PSC 1994
*
******************************************************************   */

#define NC       1000                   /* Number of Cols        */
#define NR       1000                   /* Number of Rows        */
#define NITER    1000                   /* Max num of Iterations */
#define MAX(x,y) ( ((x) > (y)) ? x : y )

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

void initialize( float t[NR+2][NC+2] );
void set_bcs   ( float t[NR+2][NC+2]);
void calculate( float t[NR+2][NC+2], float told[NR+2][NC+2]);
void print_trace( float t[NR+2][NC+2], int iter);


int main( int argc, char **argv ){
  
  int        niter;                    /* iter counter  */

  float      t[NR+2][NC+2];            /*temperature */
  float      told[NR+2][NC+2];         /* previous temperature*/
  double    start, end;                /* timiing */
  int        i, j, iter;

    
  initialize(t);                      /* Set initial guess to 0 */

  set_bcs(t);                         /* Set the Boundary Conditions */

  for( i=0; i<=NR+1; i++ )            /* Copy the values into told */
    for( j=0; j<=NC+1; j++ )
      told[i][j] = t[i][j];


  niter=1000;
  if( niter>NITER ) niter = NITER;
 
 
  /*----------------------------------------------------------*
    |       Do Computation on grid for Niter iterations    |
    *----------------------------------------------------------*/

  for( iter=1; iter<=niter; iter++ ) {
  

    calculate(t,told);
    /*   Periodically print some test Values   */
    if( (iter%100) == 0 ) {
      print_trace( t, iter );
    }

  }  /* End of kernal */
}    /* End of Program   */



/********************************************************************
 *								    *
 * Initialize all the values to 0. as a starting value              *
 *								    *
 ********************************************************************/

void initialize( float t[NR+2][NC+2] ){

  int        i, j, iter;
	  
  for( i=0; i<=NR+1; i++ )
    for ( j=0; j<=NC+1; j++ )
      t[i][j] = 0.0;
}



/********************************************************************
 *								    *
 * Set the values at the boundary.  Values at the boundary do not   *
 * change throughout the execution of the program		    *
 *								    *
 ********************************************************************/

void set_bcs( float t[NR+2][NC+2]){

  int i, j;

  for( i=0; i<=NR+1; i++){
    t[i][0] = 0.0;
    t[i][NC+1] = (100.0/NR)*i;
  }

  for( j=0; j<=NC+1; j++){
    t[0][j] = 0.0;
    t[NR+1][j] = (100.0/NR)*j;
  }

}


void calculate( float t[NR+2][NC+2], float told[NR+2][NC+2] ){
 
  int i,j;

#pragma omp parallel for private(i,j)
  for( i=1; i<=NR; i++ )     
    for( j=1; j<=NC; j++ )
      t[i][j] = 0.25 * ( told[i+1][j] + told[i-1][j] +
			 told[i][j+1] + told[i][j-1] );


#pragma omp parallel for private(i,j)
  for( i=0; i<=NR+1; i++ )       /* Copy for next iteration  */        
    for( j=1; j<=NC; j++ )
      told[i][j] = t[i][j];




}



/********************************************************************
 *								    *
 * Print the trace only in the bottom corner where most action is   *
 *								    *
 ********************************************************************/

void print_trace( float t[NR+2][NC+2], int iter ){

  int joff, i;
  joff=0;
    printf("\n---------- Iteration number: %d ------------\n", iter);

    for(i=NR-10; i<=NR; i++){
      printf("%15.8f", t[i][joff+i]);
    }

  return;
}
