#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototype to count words in a file
int count_words(FILE *file);

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file specified by the command-line argument for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Call the function to count words in the file
    int word_count = count_words(file);
    
    // Print the word count to the screen
    printf("The file contains %d words\n", word_count);

    // Close the file
    fclose(file);
    return 0;
}

// Function to count words in a file
int count_words(FILE *file) {
    /* YOUR CODE HERE*/
    // Initialise any variables that you will use in the function
	int count = 0;
    int word_flag = 0; // a flag to indicate if we are inside a word
	char c;
    // Read characters from the file until the end of the file (EOF).
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            if (word_flag) {
                // end of the word
                word_flag = 0;
                count++;
            }
        } else {
            // in a word
            word_flag = 1;
        }
    }

    // You can count the number of space characters that are in the document
    // You can safely assume, there will not be any double (or more) spaces between words.
    // Do not forget to the last word if the file does not end with a space.
    if (word_flag) {
        count++;
    }
    // Return the total word count
    return count;
}



