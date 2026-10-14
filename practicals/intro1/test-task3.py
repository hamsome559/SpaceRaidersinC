import unittest
from task3 import *

class TestFunctions(unittest.TestCase):

    def test_add(self):
        self.assertEqual(add(2, 3), 5)

    def test_subtract(self):
        self.assertEqual(subtract(5, 3), 2)

    def test_multiply(self):
        self.assertEqual(multiply(2, 3), 6)

    def test_divide(self):
        self.assertEqual(divide(6, 3), 2)
        with self.assertRaises(ValueError):
            divide(6, 0)

    def test_square(self):
        self.assertEqual(square(4), 16)

    def test_is_even(self):
        self.assertTrue(is_even(4))
        self.assertFalse(is_even(3))

    def test_factorial(self):
        self.assertEqual(factorial(5), 120)
        with self.assertRaises(ValueError):
            factorial(-1)

    def test_reverse_string(self):
        self.assertEqual(reverse_string("hello"), "olleh")

    def test_count_vowels(self):
        self.assertEqual(count_vowels("hello"), 2)

    def test_concatenate_strings(self):
        self.assertEqual(concatenate_strings("hello", " world"), "hello world")

    def test_find_max(self):
        self.assertEqual(find_max([1, 2, 3]), 3)
        with self.assertRaises(ValueError):
            find_max([])

    def test_find_min(self):
        self.assertEqual(find_min([1, 2, 3]), 1)
        with self.assertRaises(ValueError):
            find_min([])

    def test_sort_list(self):
        self.assertEqual(sort_list([3, 1, 2]), [1, 2, 3])

    def test_remove_duplicates(self):
        self.assertEqual(remove_duplicates([1, 2, 2, 3]), [1, 2, 3])

    def test_is_palindrome(self):
        self.assertTrue(is_palindrome("racecar"))
        self.assertFalse(is_palindrome("hello"))

    def test_fibonacci(self):
        self.assertEqual(fibonacci(5), 5)
        with self.assertRaises(ValueError):
            fibonacci(-1)

    def test_count_words(self):
        self.assertEqual(count_words("Hello world"), 2)

    def test_to_uppercase(self):
        self.assertEqual(to_uppercase("hello"), "HELLO")

    def test_to_lowercase(self):
        self.assertEqual(to_lowercase("HELLO"), "hello")

unittest.main()