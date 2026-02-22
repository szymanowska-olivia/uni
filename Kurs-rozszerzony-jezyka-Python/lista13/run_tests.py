from tests.test_classes import *
import unittest

def run_tests():
    s1 = unittest.TestLoader().loadTestsFromTestCase(TestFriendsDB)
    alltests = unittest.TestSuite([s1])
    unittest.TextTestRunner(verbosity=3).run(alltests)

if __name__ == "__main__":
    run_tests()