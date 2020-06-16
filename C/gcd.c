// Iterative algorithm 
#include <stdio.h>

int gcd (int a, int b)  { 
 int temp; 

 while (b) { 
	temp = a % b; 
	a = b; 
	b = temp; 
 } 
 return(a); 
} 

int main() { 

 printf("\nGCD(%2d,%2d) = [%d]", 6,4, gcd(6,4)); 

 printf("\nGCD(%2d,%2d) = [%d]", 4,6, gcd(4,6)); 

 printf("\nGCD(%2d,%2d) = [%d]", 3,17, gcd(3,17)); 

 printf("\nGCD(%2d,%2d) = [%d]", 17,3, gcd(17,3)); 

 printf("\nGCD(%2d,%2d) = [%d]", 1,6, gcd(1,6)); 

 printf("\nGCD(%2d,%2d) = [%d]", 10,1, gcd(10,1)); 

 printf("\nGCD(%2d,%2d) = [%d]", 10,6, gcd(10,6)); 

 printf("\nGCD(%2d,%2d) = [%d]", 10, 30, gcd(10,30));

 printf("\n");
 }
