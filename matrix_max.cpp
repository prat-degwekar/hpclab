#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main()
{
	//matrix addition here

	long double start, end, elapsed = 0.0;

	//int a[5000] = {0};
	//int b[5000] = {0};

	int arr[400][500][10] = {{{0}}};

	for(int i=0 ; i<400; i++)
	{
		for(int j=0 ; j<500; j++)
		{
			for(int k=0; k<10; k++)
				arr[i][j][k] = rand()%750;
		}
	}

	int max = INT8_MIN;

	start = omp_get_wtime();

	for(int i=0 ; i<400; i++)
	{
		for(int j=0 ; j<500; j++)
		{
			for(int k=0; k<10; k++)
			{
				if(arr[i][j][k] > max)
					max = arr[i][j][k];
			}
		}
	}

	end = omp_get_wtime();

	elapsed = end - start;

	//matrix addition end

	cout<<"no para\t"<<elapsed<<endl;

	int timez[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32, 64};	//13

	max = INT8_MIN;

	for(int j=0; j<13; j++)
	{

		start = omp_get_wtime();

		#pragma omp parallel num_threads(timez[j]) shared(max)


		{

			int private_max = max;
		
			#pragma omp parallel for num_threads(timez[j])
		
			for(int i=0 ; i<400; i++)
			{
				for(int j=0 ; j<500; j++)
				{
					for(int k=0; k<10; k++)
					{
						if(arr[i][j][k] > private_max)
							private_max = arr[i][j][k];
					}
				}
			}
		
			#pragma omp flush(max)
		
			if (private_max > max)
			{
				#pragma omp critical
				
				if (private_max > max)
					max = private_max;
		
			}
		}		
		
		end = omp_get_wtime();

		elapsed = end - start;

		//matrix addition end

		cout<<timez[j]<<"\t"<<elapsed<<endl;

	}

	return 0;
}