/* File name: task1.c
 * Author: Wong Jia Xuan
 * Date: 30/7/2024
 */

# include <stdio.h>
# include <string.h>

# define MAX_LEN 20 // the maximum number of characters for each string is 20

int main (void){
	char firstName[MAX_LEN + 1]; // 1 for '/0' 
	char lastName[MAX_LEN + 1];

	// Get first name from input
	printf("Enter your first name: ");
	scanf("%20s", firstName);

	// Get last name from input
	printf("Enter your last name: ");
	scanf("%20s", lastName);

	// Print initials
	printf("Your initials: %c.%c.\n", firstName[0], lastName[0]);
	return 0;
}
