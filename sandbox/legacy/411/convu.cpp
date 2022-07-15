// conv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// create random number -5 <= ran() <5
int ran()
{
	int r = 0;
	r = (rand() % 10) - 5;
	return r;
}

int main()
{
	FILE* fp_out; // output file pointer
	errno_t err_out = fopen_s(&fp_out, "C:/users/me2/documents/filter.txt", "w");

	if (err_out)
		printf("filter.txt File Open Error.  File was not opened. \n");

	int i = 0;
	int input[32] = { 0 };
	int output[32] = { 0 };

	printf("base address for input [ ] is %p \n", &input);
	printf("base address for output[ ] is %p \n", &output);

	// create data set
	for (i = 0; i <32; i++)
		if (i == 7)  // place a pulse at index = 7
			input[i] = 100;
		else input[i] = ran();  // else use small random value

	for (i = 0; i < 32; i++)
       printf(" input[%d] = %d \n",i, input[i]);

	printf("\n\n");

	for (i = 0; i < 28; i++)
	{
		// convolution kernel
	 	//                           1/2              1             1              1                    1/2
		output[i + 2] = ( input[i] >> 1) + input[i + 1] + input[i + 2] + input[i + 3] + (input[i + 4] >> 1);
		// mulitply by 1/4
		output[i + 2] = output[i + 2] >> 2;

		//Kernel values are  1/8, 1/4, 1/4, 1/4, 1/8
	}

	printf("input value [i], convolution output [i] \n\n");
	for (i = 0; i < 28; i++)
	{
		printf(" input[%d] = %d     output[%d] = %d \n", i, input[i], i, output[i]);
		fprintf_s(fp_out, "%d \t %d \t %d \n", i, input[i], output[i]);
	}

}
