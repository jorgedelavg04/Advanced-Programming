/*
 *
 *
 * Jorge Constanzo De la Vega Carrasco A01650285
 * 02/Sept/2019
 * T2
 * Compile: gcc Multiplication.c -o multiplication -Wall -g
 * Run: ./multiplication -1 Matrix_A.txt -2 Matrix_D.txt -r Matrix_finalResult.txt
 *
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 


//Define the struct for the Matrix
typedef struct M{
    //Rows, columns and numbers inside the matrix
    int row; 
    int col; 
    float ** numbers;
} Matrix;


//Function to print the matrix
void PrintMatrix(Matrix * matrix){
    for(int i = 0; i < matrix->row; i++){
        for(int j = 0; j < matrix->col; j++){
            printf("%.2f ", (matrix->numbers)[i][j]);
        }
        //Spaces in order to make the matrix
        printf("\n");
    } printf("\n");
}

//Function for reading the files
Matrix * ReadFile(char *fileName)
{
    char numberInformation[100];
    char * num;

    //We will open the file and read it using fopen
    FILE * file = fopen(fileName, "r");

    //It will execute if fopen contains something, in case that it doesnt 
    //contain the fail it will print an error to the console
    if(file){

        //We get the numberInformation using fgets
        fgets(numberInformation, sizeof numberInformation, file);
        
        //This is the matrix that will be created in order to copy the 
        //numberInformation from the txt
        Matrix * matrix;
        matrix = (Matrix*)malloc(sizeof (Matrix));
        //Use strtol to get and declare the row and col
        matrix->row = strtol(numberInformation, &num, 10);
        matrix->col = strtol(num, &num, 10);

        //Use malloc to allocate the memory of the quantity of the characters
        matrix->numbers = (float**)malloc((matrix->row) * sizeof(float*));
        for(int i = 0; i < matrix->row; i++){
            matrix->numbers[i] = (float*)malloc((matrix->col) * sizeof(float));
        }

        //Fors that will fill the matrix. fgets will get the numberInformation from the txt,
        // and a variable num will get the numbers(numberInformation) from the txt.
        for (int i = 0; i < matrix->row; i++){
            fgets(numberInformation, sizeof numberInformation, file);
            num = numberInformation;
            for(int j = 0; j < matrix->col; j++){  
                (matrix->numbers)[i][j] = strtof(num, &num);
            }
        }

        //Print the matrix using the function done above
        printf("Matrix from: %s\n", fileName);
        PrintMatrix(matrix);
        fclose(file);
        return matrix;

    } else { //Error in case there's no file or could not be opened
        printf("Its not possible to open. Try again. %s \n", fileName);
        fclose(file);
        return NULL;
    }
}


//Main
int main(int argc, char **argv)
{
    int c;

    //Declare 3 nombreTexto in order to get the name of the txts
    char *nombreTexto1 = NULL;
    char *nombreTexto2 = NULL;
    char *nombreTexto3 = NULL;

    //Strings done in order to call the func ReadFile done above in order
    //to read the files and put them inside the txt
    Matrix *string = NULL;
    Matrix *string2 = NULL;
 
    
    //Using getopt to parse the numberInformation from the console.The flags declared are 1,2 and r
    while((c = getopt( argc, argv, "1:2:r:")) != -1 )
        switch (c)
        { 
            case '1':
                //Gets the name of the txt using optarg
                nombreTexto1 = optarg;
                //Insert nombreTexto1 in the func ReadFile in order to read them
                string = ReadFile(nombreTexto1);
                
                break;
            case '2':
                //Gets the name of the txt using optarg
                nombreTexto2 = optarg;
                //Insert nombreTexto1 in the func ReadFile in order to read them
                string2 = ReadFile(nombreTexto2);
                break;
          
            case 'r':
                //Gets the name of the txt using optarg
                nombreTexto3 = optarg;
                //There is no func in here because I decided to make the code that multiplies in 
                //the main because the declaration of the readfiles make difficult to insert them
                //in other functions outside the main.
                break;

            case '?':
              //In case that other flags were used
                printf("Please use -1 -2 or -r to run the code \n");
                break;
        }


        //If the number of col is equal to the number of row, 
        //its posible to make the multiplications. 
        if(string -> col == string2 -> row) {
          
          //Another matrix will get created, now for the finalResult that
          //will get pasted in a txrt
          Matrix * finalResult;
          finalResult = (Matrix*)malloc(sizeof (Matrix));

          finalResult->row = string->row;
          finalResult->col = string2->col;
            
         //Use malloc to allocate the memory of the quantity of the characters
          finalResult->numbers = (float**)malloc((finalResult->row) * sizeof(float*));
          for(int i = 0; i < finalResult->row; i++){
              finalResult->numbers[i] = (float*)malloc((finalResult->col) * sizeof(float));
          }
          //Fors to make the multiplication
          //First we will call for the row
          for(int i = 0; i < string->row; i++){
            //Then we will call the col.
            for(int j = 0; j < string2->col; j++){
                float sum = 0;
                //Its needed to call another for in order to make the multiplication
                for(int k = 0; k < string->col; k++){
                    //It will make the multiplication first using the numbers from row and then col
                    sum += (string->numbers)[i][k] * (string2->numbers)[k][j];
                }
                (finalResult->numbers)[i][j] = sum;
            }
          }
          //Print the matrix using the print function
          printf("finalResult Matrix: \n");
          PrintMatrix(finalResult);

          //From here, the finalResult matrix will get pasted to the txt
          //first we open the new file and put w in the fopen declaration (for writing)
          FILE *file = fopen(nombreTexto3, "w");
          //In case there is no file or there is an error open it, it will print to the console an error
          if (file == NULL) {
            printf("Error opening file!\n");
            exit(1);
          }
          //Declaring that the finalResults will get printed in a file and 
          //calling the row and col from the matrix finalResult
          fprintf(file, "%i %i\n", finalResult->row, finalResult->col);
          for(int i = 0; i < finalResult->row; i++){
            for(int j = 0; j < finalResult->col; j++){
              fprintf(file, "%f ", (finalResult->numbers)[i][j]);
            }
            //Space in order to make the col
            fprintf(file, "\n");
          }
          fclose(file);
        } else {
          //In case the n x m = n x m, cant make the multiplication, print a message. 
          printf("You cant multiply\n");
        }
    return 0;
}
