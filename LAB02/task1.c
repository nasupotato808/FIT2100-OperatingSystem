/* File name: task1.c
 * Author: Wong Jia Xuan
 * Date: 13/8/2024
 * Description:
 * Write a C program that accepts three integers as command-line arguments, 
 * then computes the greatest common divisor (GCD) among them. 
 * For example, the GCD for integers 12, 78, and 48 is 6.
 */

# include <stdio.h>
# include <stdlib.h>

/* Function prototypes */
int gcd(int a, int b);

// Function to compute the GCD of two numbers
int gcd(int a, int b){
  int temp;
  while (b > 0){
		temp = a % b; // remainder of a/b
		a = b;
		b = temp;	
	}
	return a;
}

// Function to compute the GCD of three numbers
int gcd_of_three(int a, int b, int c) {
    return gcd(gcd(a, b), c);
}

int main(int argc, char *argv[]) {
	
	if (argc != 4){
		printf("%s", "Please only provide three numbers!\n");
	}

	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
    int num3 = atoi(argv[3]);
	
	printf("GCD of %d %d %d : %d\n", num1, num2, num3, gcd_of_three(num1, num2, num3));
	
	return 0;
}

