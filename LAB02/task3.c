/* File name: task3.c
 * Author: Wong Jia Xuan
 * Date: 13/8/2024
 * Description:
 * Given the following struct type called UnitCode:
 * Create two variables of type UnitCode and initialise them with some appropriate values.
 * Write a C function that determines whether these two UnitCode variables are equal to each other.
 * Hint use strcmp from <string.h>
 */

 # include <stdio.h>
 # include <string.h>
 # include "task3_unit_code.h"

 int main (void){
 	// Initialise two UnitCode variables
 	UnitCode unit1 = {"FIT", 1047};
	UnitCode unit2 = {"MAT", 1047};

	if ((strcmp(unit1.FacID, unit2.FacID) == 0) && unit1.UnitID == unit2.UnitID){
		printf("This two units are same unit.\n");
	} else {
		printf("This two units are not same unit.\n");
	}
	return 0;
 }

