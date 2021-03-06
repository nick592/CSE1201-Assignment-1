/*
    Name: Nicholas Evelyn
    USI: 1035375
    Course: CSE1201
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void) {

    // srand is a pseudo-random generator function, meaning it is generated by a traceable algorithm and is therefore not truly random. It will return the same sequence of numbers unless the "seed" value is changed. The seed can be considered as the starting point of the random number generation algorithm. If you pass time(NULL) to srand(), it will use the computer's internal clock to constantly generate a new seed value, allowing you to have unique random values.
    srand(time(NULL));

    // Declare the necessary variables

    int totalPoints, i, circlePoints = 0;
    double estimatedPi, distance, xCoords, yCoords;

    // Accept the number of points to be created.
    // This will represent the total number of points within the square.
    printf("\nEnter the number of points that should be generated (try a number greater than 7000): ");
    scanf("%d", &totalPoints);

    // Generate N number of points where N is a user-inputted value
    for(i = 0; i < totalPoints; i++) {
		
		/*
        Generate random x & y co-ordinates between 0 and 1
        x and y coordinates make up a single point within the square and are decimal values.
        We are generating values between 0 and 1 because when we square them, add them and find the square root of them, we don't want the result
		of these operations to be greater than 2, which is what we assume to be the area of the square if the radius is 1.
		The way this works is that we get a random number, cast it to be a double then divide it by the maximum random number cast as a double.
		We add 1 to the maximum random value because we want 1.0 to be included when generating the random numbers between 0 and 1.
		*/
        xCoords = (double)rand() / (double)((unsigned)RAND_MAX + 1);
        yCoords = (double)rand() / (double)((unsigned)RAND_MAX + 1);
		
		/*
    	Use the distance formula to determine the distance between a randomly generated point from the center of the circle. 
		We're assuming the center of the circle is at point (0, 0). 
        The formula is: square root((change in x) ^ 2 + (change in y) ^ 2)
        Since our origin is assumed to be (0, 0) then we just need to find x^2 and y^2 since (x - 0)^2 = x^2 and (y - 0)^2 = y^2
        */
        distance = sqrt((xCoords * xCoords) + (yCoords * yCoords));

        /* If the distance of a point is less than 1 (the length of the radius), then it is considered to have fallen within the circle 
		and we can increment the circle counter variable by one.
		*/
        if (distance <= 1) {
            circlePoints++;
        }

        /*
		Finally, once we have counted our total number of points that have fallen within the circle, 
		we can use the formula: 4 x (points in the circle / points in the square) to estimate the value of pi.
		*/
        estimatedPi = 4 * ((float) circlePoints / (float) totalPoints);

    }

    printf("Estimated value of pi after %d iterations: %f", totalPoints, estimatedPi);

    return 0;
}
