# IN CLASS TEST 2 PART 1 [of 3]

# This set of questions we will assign variables 
# to answer multiple choice questions
# for example, answer by assigning the variable like this:
# answer_1 = 'a'
# --------------------------------------------------------------------------------

'''QUESTION 1
What is the python keyword for defining a function? 
a) fn 
b) define
c) #define
d) def
'''
answer_1 = 'd'
# --------------------------------------------------------------------------------

'''QUESTION 2
What term refers to a variable that is passed in to a function? 
a) global variable
b) argument
c) debate
d) local variable
'''
answer_2 = 'b'
# --------------------------------------------------------------------------------

'''QUESTION 3
Which of the following operators is the 'power of' operator? 
a) ^ 
b) x
c) *
d) **
'''
answer_3 = 'd'

# --------------------------------------------------------------------------------
'''QUESTION 4
Which of these functions can be used to provide values 0,1,2,3? 
a) range(4)
b) range(3)
c) range(1,3)
d) range(0,3)
'''
answer_4 = 'a'
# --------------------------------------------------------------------------------
'''QUESTION 5
Which of the following gets the last element of a list? 
a) my_list[-1]
b) my_list[0]
c) my_list['end']
d) my_list[100000]
'''
answer_5 = 'a'

# --------------------------------------------------------------------------------
'''QUESTION 6
Which of the following is a valid dictionary in python? 
a) ['key': 'value']
b) 'key': 'value'
c) {'key': 'value'}
d) {key: value}
'''
answer_6 = 'c'

# --------------------------------------------------------------------------------
# complete the following functions by removing pass and providing an implementation.
# Note: you should NOT use input() or print() (other than for your own debugging purposes)
# Use the functions arguments as input and return values as output

# Using the argument povided, implement the function such that it returns True if the value provided is even and False if not
def is_even(n):
    
    if (n % 2==0):
        return True
    else:
        return False
    
# Using the arguments povided, implement the function such that it returns the largest of the two numbers passed in
def bigger(a, b):
    
    if (a > b):
        return a
    else:
        return b


# Using the arguments povided, implement the function such that it joins two strings together and returns the new string
# Note: you do not need to provide error handling here - assume strings are passed
def concat(a, b):
    c = a + b
    return c

# Using the arguments povided, implement the function such that it raises a to the power of b
def power_of(a, b):
    c = a ** b
    return c
