/* File name: task2.c
 * Author: Wong Jia Xuan
 * Date: 30/7/2024
 * Description:
 * Write a C program that asks users to enter their first name and last name. 
 * The program then displays the initial of the users based on the 
 * first letter of the first and last names. 
 * You may assume the maximum number of characters for each string is 20.
 */

# include <stdio.h>
# include <string.h>

# define MAX_LEN 20 // the maximum number of characters for each string is 20

int main(void) {
    char first_name[MAX_LEN + 1]; // 0 to 19 is char, 20 is null terminator, depends on the len or the number of character
    char last_name[MAX_LEN + 1];

    // Get first name from input
    printf("Enter your first name: ");
    scanf("%20s", first_name);

    // Get last name from input
    printf("Enter your last name: ");
    scanf(" %20s", last_name);

    // Print initials
    printf("Your initials: %c.%c.\n", first_name[0], last_name[0]);

    return 0;
}
