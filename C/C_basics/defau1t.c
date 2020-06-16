#include<stdio.h>

int main()  {          

	int a=10;          

	switch (a)          {                  
		case '1':      printf("ONE\n");                      
				break;     
		case '2':       printf("TWO\n");   
				break; 

                /* Typo here defau1t instead of default.
                 Compiler wont be able to catch it
                 */                

                /* This becomes a valid label as in 
                   goto handler_error_label;
handle_error_label: 
                 */
		defau1t:        printf("NONE\n");
				break;
	}
	return 0;  
}
