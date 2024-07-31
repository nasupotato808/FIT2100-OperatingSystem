/* File name: task3.c
 * Author: Wong Jia Xuan
 * Date: 30/7/2024
 * Description:
 * Write a C program that reads the dimensions (radius and height as integers) of a cylinder.
 * The program then computes and prints the surface area and the volume of the cylinder, with
 * two decimal places of precision.
 */

# include <stdio.h>

#define PI 3.14159265358979323846

int main (void){
	int radius;
	int height;

	double surface_area;
	double volume;

	// Get the radius from input
	printf("Please enter radius: ");
	scanf("%d", &radius);
	
	// Get the height from input
	printf("Please enter height: ");
	scanf("%d", &height);

	// Compute surface area
	// surface area = 2 pi r ^2 + 2 pi r h
	surface_area = 2 * PI * radius * radius + 2 * PI * radius * height;

	// Compute volume
	// Volume = pi r^2 h
	volume = PI * radius * radius * height;

	// Print results with two decimal places of precision
	printf("Surface Area: %.2f\n", surface_area);
	printf("Volume: %.2f\n", volume);

	return 0;
}
