/* 
 *
 * 01-Basic_C
 * Jorge C De la Vega C - A01650285
 * 22/08/2019
 *
 *
 * Instructions:
 * Fill an array of size 30 with random numbers in the range from 1 to 100
 * Ask the user for a number in the same range
 * Compute the difference between the user provided number and each of the numbers in the array.
 * That is, subtract the new number minus the element in the array.
 * Write the distances into a text file called: differences.txt, with each distance in a separate
 * row.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    //Declare array of 30 elements
	int arr[30];
    
    //Declare Random numbers
	srand(time(NULL));
	rand();
    //Declare n for number that will be scanned
	int n;
    //Declare the txt file
	FILE *f = fopen("differences.txt", "w");

    //Ask for number and scan
	printf("Write a number in the range from 1 to 100\n");
	scanf("%d", &n);

    //In case of entering a number less than 1, or greater than 100,
    //the program will ask again for a number
	while(n < 1 || n > 100){
		printf("Your number should be in the range from 1 to 100\n");
		scanf("%d", &n);
	}
    
    //If the txt fails to open, it will print an error into the console
	if (f == NULL){    
		printf("Error opening file!\n");
    	exit(1);
	}
    
    //For going from 0 to 29, filling the 30 spots in the array
	for (int i = 0; i < 30; ++i)
	{
        //Randoms get created, since the range is 1 to 100,
        //we will add a +1 (if not,the range will be 0 to 100)
		int r = rand() % 100 + 1;
		arr[i] = r;
        
        //Substracting the number given by the user (n) with the number inside the array (r)
		int num = n - r;
    
        //Prints (first one for the console, second for the txt) 
		printf("Number %d - %d (random number from arrayIndex (%d)): %d\n", n, r, i+1, num);
		fprintf(f, "Number %d - %d (random number from arrayIndex (%d)): %d\n", n, r, i+1, num);
	}
    
	fclose(f);
    
}

