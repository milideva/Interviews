# Python program to validate an Ip address

# re module provides support
# for regular expressions
import re

# Make a regular expression
# for validating an Ip-address
regex = "^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$"


	
# Define a function for
# validate an Ip addess
def check(Ip): 

	# pass the regular expression
	# and the string in search() method
	if(re.search(regex, Ip)): 
	    print('Valid Ip address ', Ip) 
		
	else: 
		print('Invalid Ip address ', Ip) 
	

# Driver Code 
if __name__ == '__main__' : 
	
	# Enter the Ip address
	Ip = "192.168.0.1"
	
	# calling run function 
	check(Ip)

	Ip = "110.234.52.124"
	check(Ip)

	Ip = "366.1.2.2"
	check(Ip)
