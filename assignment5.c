//Kelly Pitts 09098321
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void convert(char *word1, char *word2);
void counter(char *searchword, char *originalword);
FILE *infile;

char search1[50], search2[50], search1copy[50], search2copy[50];
char filename[50], line[1000][500], linecopy[1000][500];
int linecount, i, j, len[100];
int main() {
	printf("Enter the first word: ");		//Asking user for the 2 search words and file name
	gets(search1);
	printf("Enter the second word: ");
	gets(search2);
	printf("Enter the name of the text file: ");
	gets(filename);
	infile = fopen(filename, "r");							//opening the file and checking it exists.
	if (infile == NULL) {
		printf("ERROR: cannot open %s", filename);
		exit(27);
	}
	i = 0;
	linecount = 0;													//counting how many lines are in the file.
	while (fgets(line[i], 120, infile) != NULL) {		//reading all lines from the file.
		strcpy(linecopy[i], line[i]);							//each line is a whole string.
		len[i] = strlen(line[i]);								//creating an array that knows the lenght of each line.
		for (j = 0; j < len[i]; j ++) {						//converting the copied line to all lowercase.
			linecopy[i][j] = tolower(linecopy[i][j]);
		}
		linecount ++;
		i ++;
	}
	convert(search1, search1copy);								//Calling functions
	counter(search1copy, search1);
	convert(search2, search2copy);
	printf("\n\n");
	counter(search2copy, search2);
}
void convert(char *word1, char *word2) {					//converts the 2 search words to lowercase
	int len1;
	i = 0;
	len1 = strlen(word1);
	while (i < len1) {
		word2[i] = tolower(word1[i]);
		i++;
	}
}

void counter(char *searchword, char *originalword) {	
	int wordcount, count, len2, k;		//counts the number of occurences each search word appears in the file.
	wordcount = 0;	
	count = 0;
	k = 0;
	len2 = strlen(searchword);
	for (i = 0; i < linecount; i ++) {	//will loop through every line.
		for (j = 0; j < len[i]; j ++) {	//loops through every letter line by line.
			if (searchword[k] != linecopy[i][j]) {
					count = 0;
			}
			//this section checks that the index of the search word is the same letter 
			//as the index of the word in the file, if each letter matches and
			//the next character is a space '.' or '\n', it will add 1 to the total word count.
			if (searchword[k] == linecopy[i][j]) {								
				count ++;																
				if ((count == len2) && ((linecopy[i][j+1] == ' ') || 		
													(linecopy[i][j+1] == '.') || (linecopy[i][j+1] == '\n'))) {
					wordcount ++;
					if (wordcount == 1) {
						printf("\nThe word '%s' first appears in line %d which is:\n", originalword, i+1);
						printf("%s", line[i]);
					}
					count = 0;
				}
			}
			k ++;
			if ((linecopy[i][j] == ' ') || (linecopy[i][j] == '.') || (linecopy[i][j] == '\n')) {
				k = 0;
			}
		}
	}
	if (wordcount > 0) {
		printf("\nThe word '%s' appears %d times in the file.", originalword, wordcount);
	} else {
		printf("\nThe word '%s' does not appear in the file.", originalword);
	}
}