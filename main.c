/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int
main ()
{
  int n = 10;
  int fib = 1;
  int prev = 1;
  int temp = 0;
  for (int i = 0; i < n; i++)
    {
      if (i == 0 || i == 1)
	{
	  printf ("1 ");
	}
      else
	{
	  temp = fib;
	  fib += prev;
	  prev = temp;
	  printf ("%d ", fib);
	}
    }

  return 0;
}
