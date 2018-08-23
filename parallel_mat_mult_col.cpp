#include <iostream>
#include <omp.h>
#include <cstdlib>

#define M 100
#define N 100
#define L 100

using namespace std;

int main()
{
	//matrix addition here

	long double start, end, elapsed = 0.0;

	int arr1[100 * 100];
	int arr2[100 * 100];
	int res[100 * 100];

	#pragma omp parallel for

	for(int i=0 ; i<100; i++)
	{
		for(int j=0; j<100; j++)
		{
			arr1[i * 100 + j] = rand() % 500;
			arr2[i * 100 + j] = rand() % 500;
		}
	}

	//start = omp_get_wtime();

	int timez[] = {1,2,4,6,8,10,12,14,18,22,26,30,34,38,42,46,50,54,58,62};		//20

	for( int J=0 ; J<20; J++)
	{

		start = omp_get_wtime();

		#pragma omp parallel for num_threads(timez[J])

		//matrix multiplication comes here

		/*for (int i = 0; i < 100; i++)
    	{
    		#pragma omp parallel for num_threads(timez[J])

    	    for (int j = 0; j < 100; j++)
    	    {

    	        C[i][j] = 0;

    	        //#pragma omp parallel for num_threads(timez[j])

    	        for (int k = 0; k < 100; k++)
    	        {
    	        	//#pragma omp parallel for num_threads(timez[j])

    	            C[i][j] += arr1[i][k] * arr2[k][j];
    	        }
    	    }
    	}*/

    	for (int i = 0; i < 100; i++) 
    	{
        	for (int j = 0; j < 100; j++) 
        	{
            	res[j * M + i] = 0;

            	for (int k = 0; k < 100; k++) 
            	{
                	res[j * M + i] += arr1[k * M + i] * arr2[j * L + k];
            	}
        	}
    	}

		//matrix multiplication end

		end = omp_get_wtime();

		elapsed = end - start;

		

		cout<<timez[J]<<"\t"<<elapsed<<endl;

	}

	return 0;
}