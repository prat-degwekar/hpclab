#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <fstream>

using namespace std;

int main()
{
	//matrix addition here

	long double start, end, elapsed = 0.0;

	ifstream redfile("red.txt");
	ifstream bluefile("blue.txt");
	ifstream greenfile("green.txt");

	int red[384][512] = {{0}};
	int green[384][512] = {{0}};
	int blue[384][512] = {{0}};

    //accept values here

    for(int i=0 ; i<384; i++)
    {
        for(int j=0 ; j<512 ; j++)
        {
            redfile>>red[i][j];
            greenfile>>green[i][j];
            bluefile>>blue[i][j];
        }
    }

	start = omp_get_wtime();

	/*for(int i=0 ; i<5000 ; i++)
		{
			//arr1[i][j] = arr1[i][j] + arr2[i][j];
			a[i] = (i+1)*1.0;
			b[i] = (i+1)*2.0;
		}*/
    for(int i=1; i<383; i++)
    {
        for(int j=1; j<511; j++)
        {
            int temp = red[i-1][j] + red[i-1][j-1] + red[i-1][j+1];
            temp += red[i][j-1] + red[i][j] + red[i][j+1];
            temp += red[i+1][j-1] + red[i+1][j] + red[i+1][j+1];
            temp /= 9;
            red[i][j] = temp;

            temp = green[i-1][j] + green[i-1][j-1] + green[i-1][j+1];
            temp += green[i][j-1] + green[i][j] + green[i][j+1];
            temp += green[i+1][j-1] + green[i+1][j] + green[i+1][j+1];
            temp /= 9;
            green[i][j] = temp;

            temp = blue[i-1][j] + blue[i-1][j-1] + blue[i-1][j+1];
            temp += blue[i][j-1] + blue[i][j] + blue[i][j+1];
            temp += blue[i+1][j-1] + blue[i+1][j] + blue[i+1][j+1];
            temp /= 9;
            blue[i][j] = temp;
        }
    }

	end = omp_get_wtime();

	elapsed = end - start;

	//matrix addition end

	cout<<"no para\t"<<elapsed<<endl;

	//int timez[] = {1, 2, 4, 6, 8, 12, 16, 20, 24, 28, 32};	//11

	start = omp_get_wtime();

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for(int i=1; i<383; i++)
        	{
           		for(int j=1; j<511; j++)
            	{
                	int temp = red[i-1][j] + red[i-1][j-1] + red[i-1][j+1];
                	temp += red[i][j-1] + red[i][j] + red[i][j+1];
                	temp += red[i+1][j-1] + red[i+1][j] + red[i+1][j+1];
                	temp /= 9;
                	red[i][j] = temp;
            	}
        	}
        }

        #pragma omp section
        {
        	for(int i=1; i<383; i++)
        	{
        		for(int j=1; j<511; j++)
        		{

                	temp = green[i-1][j] + green[i-1][j-1] + green[i-1][j+1];
                	temp += green[i][j-1] + green[i][j] + green[i][j+1];
                	temp += green[i+1][j-1] + green[i+1][j] + green[i+1][j+1];
                	temp /= 9;
                	green[i][j] = temp;
                }
            }
        }

        #pragma omp section
        {
        	for(int i=1; i<383; i++)
        	{
        		for(int j=1; j<511; j++)
        		{

                	temp = blue[i-1][j] + blue[i-1][j-1] + blue[i-1][j+1];
                	temp += blue[i][j-1] + blue[i][j] + blue[i][j+1];
	                temp += blue[i+1][j-1] + blue[i+1][j] + blue[i+1][j+1];
                	temp /= 9;
                	blue[i][j] = temp;
            	}
        	}
        }
	}

	end = omp_get_wtime();

	elapsed = end - start;

	//matrix addition end

	cout<<"elapsed time : "<<elapsed<<endl;
	
	return 0;
}
