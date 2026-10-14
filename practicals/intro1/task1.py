from testlib import *
# Task 1

# Integers: 

# pass the value 42 to the function
test_value_1(42)
# pass the value 0 to the function
test_value_2(0)
# pass the value 
# Two Billion One Hundred Forty-Seven Million 
# Four Hundred Eighty-Three Thousand
#  Six Hundred Forty-Seven:
test_value_3(2147483647)

# Floats: 

# pass the value 1.1
test_value_4(1.1)
# pass the function 0.001
test_value_5(0.001)
# pass the value of pi to 4 decimal places
test_value_6(3.1416)

# Strings: 

# pass the function the string hello
test_value_7("hello")

# pass the function the string Hello
test_value_8("Hello")

# pass the function the string 'hello world!'
test_value_9('hello world!')

# Booleans:

# pass the boolean value true 
test_value_10(True)
# pass the boolean value false 
test_value_11(False)

# Lists: 

# pass a list containing numbers 1 - 5
test_value_12([1,2,3,4,5])

# pass a list containing three integers with the value of one
test_value_13([1,1,1])

# pass a list with the strings 'hello' 'world' '!'
# nb: there should be no spaces and the list should be 3 elements long...
test_value_14(["hello","world","!"])

# Tuples:

# pass a tuple that contains the name 'ben' and the age 25
# this should be represented as a tuple with a string and integer value
test_value_15(("ben",25))

# pass a tuple that represents the origin on a graph using decimal values
test_value_16((0.0,0.0))

# Dictionary: 

# Create a dictionary that contains the name 'ben' and the age 25
# this should be contain approriate keys and values of a string and integer respectively
test_value_17({"name": "ben", "age": 25})

x = False
print(not x)