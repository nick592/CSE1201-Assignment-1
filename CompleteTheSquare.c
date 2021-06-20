/*
    Name: Nicholas Evelyn
    USI: 1035375
    Course: CSE1201

    Overall approach: 
    Since C's printf() function has format specifiers that can tell if a numeric type is positive
    or negative, I decided to let printf() do a lot of the heavy lifting rather than coming up with my
    own logic to do this. So, the equations are being printed to the screen mostly by manipulating printf()
    and doing some minor computations.
	The program is designed to cater for situations where a is greater than 1, or where a is negative. 
	It does not cater for imaginary numbers or situations where a = 0. 
    The result of the function is the same as what you would get if rewrote the roots of the equation from surd/radical form to decimal form. 
	Note that the '^' symbol in this program means square (to the power of 2)

    The basic algorithm I used for this sub-task was:

    If a in ax^2 + bx + c == 1, then:
    1. get a, b, c values from the user
    Example: 1 -6 7 would correspond to the equation x^2 - 6x + 7

    2. print the equation in the form (ax + b/2)^2 - (b/2)^2 + c = 0
    Example: (x - 3)^2 - 9 + 7 = 0

    3. add -(b/2)^2 to c
    Example: (x - 3)^2 - 2 = 0

    4. Get x^2 term alone on one side of the equation
    Example: (x - 3)^2 = 2

    5. Square root both sides of the equation
    Example: x - 3 = + or - root(2)

    6. Solve for x
    Example: x = 3 + root(2) or x = 3 - root(2)

    ---

    If a in ax^2 + bx + c is less than zero or greater than 1 then:
    1. get a, b, c values from the user
    Example: -2 -12 -9 would correspond to the equation -2x^2 - 12x -9 = 0

    2. Factor out a from the equation. Remember factoring out a number is the same as dividing by 
    that number. So we must divide each term of the equation by a.
    Example: -2(x^2 + 6x + 4.5) = 0

    3. Put the equation in the form: a[(x + b/2)^2 + c - (b/2)^2]
    Example: -2[(x + 3)^2 + 4.5 - 9]

    4. Add c to -(b/2)^2
    Example: -2[(x + 3)^2 - 4.50] = 0 since 4.5 - 9 = -4.5

    5. Get x^2 term alone on one side of the equation by adding or subtracting to both sides
    of the equation.
    Note: the x^2 term is everything in the parenthesis. Remember to ignore the 'a' coefficient
    Example: (x + 3)^2 = 4.5

    6. Square root both sides of the equation.
    Example: x + 3 = plus or minus root(4.5)

    7. Get x term alone on one side of the equation
    Example: x = -3 plus or minus root(4.5)

*/

#include <stdio.h>
#include <math.h>

// If a != 1.0 for ax^2 + bx + c, then the "aIsNotOne" function will be called.
void aIsNotOne(float, float, float);

// If a == 1.0 for ax^2 + bx + c ,then the "aEqualsOne" function will be called.
// Note, the process for completing the square is slightly different for cases where a > 1 from when a == 1.
//This is why we're taking two different approaches.
void aEqualsOne(float, float, float);

int main(void) {

    float a, b, c;
    char choice; 

    while (1) {

        // accept a, b, c of quadratic in form ax^2 + bx + c
        printf("\nEnter a, b, c in that order: \n");
        scanf("%f %f %f", &a, &b, &c);

        if (a == 1.0) {
            aEqualsOne(a, b, c);
        }

        else if (a == 0) {
            printf("\n a cannot be 0");
        }

        else {
            aIsNotOne(a, b, c);
        }

        printf("\nDo you have more calculations to make? (y/n) ");
        fflush(stdin);
        scanf("%c", &choice);

        if (choice == 'y') {
            continue;
        }

        else {
            printf("\nBye!");
            break;
        }

    }
    
    return 0;

}

void aEqualsOne(float a, float b, float c) {

    float halfB, minusHalfBSquared, root1, root2;

    // Display initial equation based on a, b and c values that the user entered
    // Note that the '+' sign before .1f gives us the sign of the value
    // If the number is positive, then we will get a plus sign. If it is negative, we get a - sign.
    printf("\nYour equation: %.0fx^2 %+.1fx %+.1f = 0\n", a, b, c);

    // Rewrite in form (a + b/2)^2 - (b/2)^2 + c = 0
    halfB = b * 0.5; // calculate b/2
    minusHalfBSquared = -1 * pow(halfB, 2); // calculate -(b/2) ^ 2 
    printf("\nStep 1: (%.0fx %+.2f)^2 %+.2f %+.2f = 0", a, halfB, minusHalfBSquared, c); 

    // Simplify values outside the brackets. This means (b/2)^2 will be added to c
    c = c + minusHalfBSquared;
    printf("\nStep 2: (%.0fx %+.2f)^2 %+.2f = 0", a, halfB, c);

    // We want c to be on the other side of the equal sign, so we will flip the 
    // sign of c by multiplying it by -1 and then bring it to the right hand side of the equation
    c = c * -1; 
    printf("\nStep 3: (%.0fx %+.2f)^2 = %+.2f", a, halfB, c);

    // We now want to get rid of the squared terms on the left-hand side of the equation. 
    // Therefore, we must square root both sides of the equation. Note that finding the square root
    // of any number gives us positive and negative values
    printf("\nStep 4: %.0fx %+.2f = + or - root(%.2f)", a, halfB, c);

    // At this point, we want only the x on the left hand side of the equation, so we need to bring halfB
    // to the right hand side of the equation and flip its sign
    halfB = -1 * halfB;
    printf("\nStep 5: %.0fx = %.2f + root(%.2f) or %.2f - root(%0.2f)", a, halfB, c, halfB, c);

    // Compute the roots. Make sure to account for both the postive and negative square roots
    root1 = halfB + sqrt(c);
    root2 = halfB - sqrt(c);
    printf("\nThe first root is: %.2f\n", root1);
    printf("The second root is: %.2f\n", root2);
}

void aIsNotOne(float a, float b, float c) {

    float halfB, minusHalfBSquared, root1, root2;

    // Display initial equation based on a, b and c terms that the user entered
    printf("\nYour equation: %.0fx^2 %+.2fx %+.2f = 0\n", a, b, c);

    // Factor out a. Remember factoring out a number is the same as dividing // by that number. So, if we factor out a from the entire equation,
    // each term of the equation must be divided by a
    b = b / a;
    c = c / a;
    printf("Step 1 => Factor out %+.1f from the equation: %.0f(x^2 %+.1fx %+.1f) = 0\n", a, a, b, c);

    // Rewrite in form a(x + b/2)^2 - (b/2)^2 + c
    halfB = b / 2;
    minusHalfBSquared = -1 * pow(halfB, 2.0);
    printf("Step 2: %.0f[(x %+.2f)^2 %+.2f %+.2f] = 0", a, halfB, c, minusHalfBSquared);

    // Simplify values outside the brackets. This means (b/2)^2 will be added to c
    c = c + minusHalfBSquared;
    printf("\nStep 3: %.0f[(x %+.2f)^2 %+.2f] = 0", a, halfB, c);

    // Add or subtract c on both sides
    c = c * -1; // Multiplying by -1 will flip the sign of c, which is what we want since c is going to the other side of the equal sign.
    printf("\nStep 4: (x %+.2f)^2 = %+.2f", halfB, c);

    // We now want to get rid of the squared terms on the left-hand side of the equation. 
    // Therefore, we must square root both sides of the equation. Note that finding the square root
    // of any number gives us positive and negative values
    printf("\nStep 5: x %+.2f = + or - root(%.2f)", halfB, c);

    // At this point, we want only the x on the left hand side of the equation, so we need to bring halfB
    // to the right hand side of the equation and flip its sign
    halfB = -1 * halfB;
    printf("\nStep 6: x = %.2f + root(%.2f) or %.2f - root(%0.2f)", halfB, c, halfB, c);

    // Compute the roots. Make sure to account for both the postive and negative square roots
    root1 = halfB + sqrt(c);
    root2 = halfB - sqrt(c);
    printf("\nThe first root is: %.2f\n", root1);
    printf("The second root is: %.2f\n", root2);
}
