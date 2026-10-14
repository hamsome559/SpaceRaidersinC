# MOCK TEST

# This set of questions we will assign variables 
# to answer multiple choice questions
# for example, answer by assigning the variable like this:
# answer_1 = 'a'
# --------------------------------------------------------------------------------

'''QUESTION 1
Which Python data type is used to represent a sequence of characters? 
a) Integer 
b) Float
c) String
d) Boolean
'''
answer_1 = 'c'
# --------------------------------------------------------------------------------

'''QUESTION 2
Which of the following creates the variable x and assigns it to 10? 
a) x += 5
b) x = 10
c) x == 11
d) wrong = 10
'''
answer_2 = 'b'
# --------------------------------------------------------------------------------

'''QUESTION 3
Which Python data type is used toa true or flase value? 
a) Integer 
b) Float
c) String
d) Boolean
'''
answer_3 = 'd'

# --------------------------------------------------------------------------------
'''QUESTION 4
Which operator is used for assignment (assigning a variable)? 
a) = 
b) ==
c) !=
d) >=
'''
answer_4 = 'a'
# --------------------------------------------------------------------------------
'''QUESTION 5
Which operator is used for comparison (comparing two values to see if they are equal)? 
a) = 
b) ==
c) !=
d) >=
'''
answer_5 = 'b'

# --------------------------------------------------------------------------------
'''QUESTION 6
Which of the following is not an expression? 
a) 5 + 5 
b) x
c) len(lst)
d) if(True):
'''
answer_6 = 'd'

# --------------------------------------------------------------------------------
# This question requires you to return values from the following test functions
# replace 'pass' with 'return value' where value is the correct literal value

# return the value 42 to the function
def test_value_1():
    return 42

# return the value 1.1
def test_value_2():
    return 1.1

# return the boolean value true 
def test_value_3():
    return True

# return the function the string hello
def test_value_4():
    return "hello"

# return a list containing three integers with the value of 1
def test_value_5():
    list = [1,1,1]
    return list
# --------------------------------------------------------------------------------

# complete the following function such that it returns the result of adding arguments a and b
def add(a, b):
    return a + b
    
# complete the following function such that it returns the result of subtracting arguments a and b
def subtract(a, b):
    return a - b

# complete the following function such that it returns the result of multiplying arguments a and b
def multiply(a, b):
    return a * b

# complete the following function such that it returns the result of dividing arguments a and b
# i did an exception as an optional to try and relearn it.
def divide(a, b):
    try:
        result = a/b 
        return result
    except ZeroDivisionError:
        raise ZeroDivisionError("Zero Division Error")


# --------------------------------------------------------------------------------
# implement the fizz buzz function - values are input into the argument n
# Return 'Fizz' if n is divisible by 3, 'Buzz' if n is divisible by 5,
# 'FizzBuzz' if n is divisible by both, and the string representation of n otherwise
# Dont forget to return not print!
def fizz_buzz(n):
    if (n % 3 == 0 and n % 5 == 0):
        return "FizzBuzz"
    elif (n % 3 == 0):
        return "Fizz"
    elif (n % 5 == 0):
        return "Buzz"
    else:
        return str(n)


# --------------------------------------------------------------------------------
# take a list of numbers in and sort them smallest to largest
# create and throw exceptions for being passed values that arent numbers
def sort_list(lst):
   try:
       sortedlist = sorted(lst)
       return sortedlist
   except ValueError:
       raise ValueError("This list contains a non-numerical number")
