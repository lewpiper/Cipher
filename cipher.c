//Cipher Lab
//Lew Piper III | Palomar ID 011263249

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Function prototypes and global variables
void processFile();
void cipher(char* buffer, int bufferlen, int shiftlen);
void outputCode(char* buffer, int bufferlen);
FILE *fpread;
FILE *fpwrite;

char filebuffer[1000];
int filebufferlen = 0;

//Main Function
int main(int argc, char *argv[]) {
	fpwrite = fopen("csis.txt", "w");
	
	processFile();
	cipher(filebuffer, filebufferlen, 13);
	outputCode(filebuffer, filebufferlen);
	
	fclose(fpwrite);
	return 0;
}

//Read in the file and process it
void processFile() {
	int c;
	filebufferlen = 0;
	
	//Open file for reading
	if(!(fpread = fopen("Congress.txt", "r"))){
		printf("File %s could not be opened. \n", "Congress.txt");
		fprintf(fpwrite,"File %s could not be opened. \n", "Congress.txt");
		exit(1);
	}
	
	//Read until end of the file and only include letters in alphabet convert to upper case and store in filebuffer array then incriment filebufferlen index
	while ((c = getc(fpread)) != EOF) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			//Convert to uppercase
			c = toupper(c);
			//Add to filebuffer array and incriment the counter filebufferlen
			filebuffer[filebufferlen++] = c;
		}
	}
}

//Cipher characters
void cipher(char* buffer, int bufferlen, int shiftlen) {
	//For loop that shifts the characters in the array accordingly if outside of the bounds shift the array 
    for (int i = 0; i < bufferlen; ++i) {
		//Assign to a temp variable p
		char p = buffer[i];
		//Find the integer number of the location of the letter p with relation to A the first letter
		char c = (p - 'A');
		//Shift c by the shift length passed in
		c += shiftlen;
		//Check if this is outside the bound of the alphabet and if so subtract 26 and add the remainder to A to get the new letter
		if (c >= 26)
			c -= 26;
		c += 'A';
		//Place c back into the buffer array now shifted
		buffer[i] = c;
	}
}

//Output characters with format
void outputCode(char* buffer, int bufferlen) {
	int j = 0, index = 0;
	
	//For loop to cycle through string and print contents with logic for sets of five char and groups of ten then return 
	for (int i = 0; i < bufferlen; ++i){
		if (j == 4) {
			printf("%c", buffer[i]);
			fprintf(fpwrite,"%c", buffer[i]);
			printf(" ");
			fprintf(fpwrite," ");
			j = 0;
			index++;
			if (index == 10) {
				printf("\n");
				fprintf(fpwrite,"\n");
				index = 0;
			}
		} else {
			printf("%c", buffer[i]);
			fprintf(fpwrite,"%c", buffer[i]);
			j++;
		}
	}		
}