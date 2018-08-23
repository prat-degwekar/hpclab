#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main()
{
	//matrix addition here

	long double start, end, elapsed = 0.0;

	int arr1[100][100];
	int arr2[100][100];
	int c[100][100];

	#pragma omp parallel for

	for(int i=0 ; i<100; i++)
	{
		for(int j=0; j<100; j++)
		{
			arr1[i][j] = rand() % 500;
			arr2[i][j] = rand() % 500;
		}
	}

	//start = omp_get_wtime();

	int timez[] = {1,2,4,6,8,10,12,14,18,22,26,30,34,38,42,46,50,54,58,62};		//20

	int N = 100, s = 4, temp = 0;

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

    	for(int jj=0;jj<N;jj+= s)
    	{
    		#pragma omp parallel for num_threads(timez[J])

        	for(int kk=0;kk<N;kk+= s)
        	{
        		#pragma omp parallel for num_threads(timez[J])

                for(int i=0;i<N;i++)
                {
                	#pragma omp parallel for num_threads(timez[J])

                    for(int j = jj; j<((jj+s)>N?N:(jj+s)); j++)
                    {
                        temp = 0;

                        #pragma omp parallel for num_threads(timez[J])
                        
                        for(int k = kk; k<((kk+s)>N?N:(kk+s)); k++)
                        {
                            temp += arr1[i][k] * arr2[k][j];
                        }
                        c[i][j] += temp;
                    }
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