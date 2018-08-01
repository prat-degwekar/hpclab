#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main()
{
	//matrix addition here

	long double start, end, elapsed = 0.0;

	int arr1[1000][1000];
	int arr2[1000][1000];

	#pragma omp parallel for

	for(int i=0 ; i<1000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			arr1[i][j] = rand() % 500;
			arr2[i][j] = rand() % 500;
		}
	}

	start = omp_get_wtime();

	int timez[] = {1,2,4,6,8,10,12,14,18,22,26,30,34,38,42,46,50,54,58,62};		//20

	for( int j=0 ; j<20; j++)
	{

		#pragma omp parallel for

		for(int i=0 ; i<1000 ; i++)
		{
			#pragma omp parallel for
			for(int j=0; j<1000; j++)
				arr1[i][j] = arr1[i][j] + arr2[i][j];
		}

		end = omp_get_wtime();

		elapsed = end - start;

		//matrix addition end

		cout<<timez[j]<<"\t"<<elapsed<<endl;

	}

	return 0;
}