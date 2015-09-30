using System;

namespace PrimePalindrome
{
    class Program
    {
        static bool isPrimeUnder1k( int n )
        {
            // check if a number under 1k is prime.  We could do this faster

            // in general by precomputing the primes, but we know we're working

            // down from 1000 trying to find a palindromic one, so we probably

            // aren't going to look at very many numbers.



            int [] primes = new int [] { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
            for (int i = 0; i < primes.Length; i++) {
                if (n % primes[i] == 0) {
                    return false;
                }
            }
            return true;
        }

        public static bool IsPalindrome( int x) {
            int rev = 0;
            int i = x;
            do {
	            int r = i % 10;
	            rev = rev * 10 + r;
	            i = i / 10; 
            } while (i > 0);
            return x == rev;
        }

        static int largestPrimePalUnder1000()
        {
            // even numbers excluded and we know 999 is nonprime,
            // so start with the next smaller palindrome which is 989
            for (int candidate = 989; candidate > 2; candidate -= 2) {
                if (IsPalindrome(candidate) && isPrimeUnder1k(candidate)) {
                    return candidate;
                }
            }
            return -1; // error exit
        }

        static void Main(string[] args)
        {
            int ans = largestPrimePalUnder1000();
            if (ans == -1) {
                Console.WriteLine("Fail");
            }
            else {
                Console.WriteLine(ans);
            }
            Console.WriteLine("Press any key to exit ...");
            Console.ReadKey();
        }
    }
}
