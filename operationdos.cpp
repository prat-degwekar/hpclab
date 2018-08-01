#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main()
{
	//matrix addition here

	long double start, end, elapsed = 0.0;

	int a[5000] = {0};
	int b[5000] = {0};

	/*#pragma omp parallel for

	for(int i=0 ; i<1000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			arr1[i][j] = rand() % 500;
			arr2[i][j] = rand() % 500;
		}
	}*/

	start = omp_get_wtime();

	for(int i=0 ; i<5000 ; i++)
		{
			//arr1[i][j] = arr1[i][j] + arr2[i][j];
			a[i] = (i+1)*1.0;
			b[i] = (i+1)*2.0;
		}

	end = omp_get_wtime();

	elapsed = end - start;

	//matrix addition end

	cout<<"no para\t"<<elapsed<<endl;

	int timez[] = {1,2,4,6,8,10,12,14,18,20,24,28,36,40};	//14

	for(int j=0; j<14; j++)
	{

		start = omp_get_wtime();

		#pragma omp parallel for num_threads(timez[j])

		for(int i=0 ; i<5000 ; i++)
		{
			//arr1[i][j] = arr1[i][j] + arr2[i][j];
			a[i] = (i+1)*1.0;
			b[i] = (i+1)*2.0;
		}

		end = omp_get_wtime();

		elapsed = end - start;

		//matrix addition end

		cout<<timez[j]<<"\t"<<elapsed<<endl;

	}

	return 0;
}