def add(a, b):
    return a + b
    
    
def subtract(a, b):
    return a - b

def multiply(a, b):
    return a * b

def divide(a, b):
    if b == 0:
        raise ValueError("dividing by 0 is impossible")
    return a/b

def square(n):
    return n ** 2

def is_even(n):
    return n % 2 == 0

def factorial(n):
    if n < 0:
        raise ValueError("negatives cannot be a fraction")
    fact = 1
    for i in range(1, n+1 ):
        fact *= i
    return fact

def reverse_string(s):
    return s[::-1]
    

def count_vowels(s):
    vowels = {'a', 'e', 'i', 'o', 'u'}
    return sum(1 for char in s.lower() if char in vowels)

def concatenate_strings(s1, s2):
    return s1 + s2

def find_max(lst):
    return max(lst)

def find_min(lst):
    return min(lst)

def sort_list(lst):
    return sorted(lst)

def remove_duplicates(lst):
    return list(dict.fromkeys(lst))

def is_palindrome(s):
    s = s.lower()
    return s == s[::-1]

def fibonacci(n):
    if n < 0:
        raise ValueError("n must be a positive number")
    elif n == 0:
        return 0
    elif n == 1:
        return 1

    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b


 

def count_words(s):
    return len(s.split())

def to_uppercase(s):
    return s.upper()

def to_lowercase(s):
    return s.lower()
