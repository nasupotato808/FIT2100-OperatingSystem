/* File name: task2.c
 * Author: Wong Jia Xuan
 * Date: 13/8/2024
 * Description:
 * Write a C function that accepts an unsorted array of integers and 
 * the length of the array as arguments. 
 * The function should then compute the average value 
 * of all the numbers, and return the number closest to the average by
 * returning a pointer to that closest element. 
 * The function prototype is given as follows:
 */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// return a pointer to that cloeset element among the array
int *find_closest_to_average (int the_array[], int num_elements){
	// base case: num_elements is 0
	if (num_elements == 0){
		return NULL;
	}
	
	// Calculate sum of the array elements
	int sum = 0;
	for (int i = 0; i < num_elements; i++){
		sum += the_array[i];
	}
	
	// Calculate the average
	double avg = (double)sum / num_elements; //prevent truncate
	//printf("%d\n",avg);

	// Find the closest element to the average
	// Initialise with the first element in the array
	int* closest_ptr = &the_array[0];
	double min_diff = fabs(the_array[0] - avg);
	

	for (int i = 1; i < num_elements; i++){
		double diff = fabs(the_array[i] - avg);

		if (diff < min_diff){
			min_diff = diff;
			closest_ptr = &the_array[i];
		}
	}
	return closest_ptr;
}
int main(int argc, char *argv[]){
	int arr[] = {12, 23, 48, 5, 7};
	int num_elements = sizeof(arr) / sizeof(arr[0]);

	int* closest = find_closest_to_average(arr, num_elements);

	if (closest != NULL){
		printf("The element closest to the average is %d\n", *closest);
	} else {
		printf("The array is empty.\n");
	}

	return 0;
}

