# include <stdio.h>
/* Function prototypes */
int add (int x, int y, int z);
int subtract (int x, int y, int z);
int multiply (int x, int y, int z);
int modulus (int x, int y, int z);



int main (void) {
        /* declaration of local variables */
        int num1, num2, num3; //numbers

        printf("Please enter three numbers (integer.\nNumber1: ");
        scanf("%d", &num1);
        printf("Number2: ");
        scanf("%d", &num2);
        printf("Number3: ");
        scanf("%d", &num3);

        printf("Addition: %d\n", add(num1, num2, num3));
	printf("Subtraction: %d\n", subtract(num1, num2, num3));
	printf("Multiplication: %d\n", multiply(num1, num2, num3));
	
	if (num2 != 0 && num3 != 0){
		printf("Modulus:%d\n",modulus(num1, num2, num3));
	}
	else{
		printf("Modulus cannot be performed! Check num2 and num3");
	}
	


}

/* function definitions */
// Function to add three numbers
int add (int x, int y, int z) {
        return (x + y + z);
}

// Function to subtract three numbers
int subtract (int x, int y, int z){
        return (x - y - z);
}

// Function to multiply three numbers
int multiply (int x, int y, int z){
        return ( x * y * z);
}

// Function to do modulus
int modulus (int x, int y, int z){
        return ((x % y) % z);
}
   
