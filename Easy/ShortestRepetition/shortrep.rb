=begin
SHORTEST REPETITION
CHALLENGE DESCRIPTION:

Write a program to determine the shortest repetition in a string.  A
string is said to have period p if it can be formed by concatenating one
or more repetitions of another string of length p. For example, the
string "xyzxyzxyzxyz" has period 3, since it is formed by 4 repetitions
of the string "xyz". It also has periods 6 (two repetitions of "xyzxyz")
and 12 (one repetition of "xyzxyzxyzxyz").

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line will contain a string of up to 80 non-blank characters. E.g.

abcabcabcabc
bcbcbcbcbcbcbcbcbcbcbcbcbcbc
dddddddddddddddddddd
adcdefg

OUTPUT SAMPLE:

Print out the smallest period of the input string. E.g.

3
2
1
7
=end

=begin
SDS posted a solution to GitHub.  I learned a lot of Ruby from it:

  def find_period(string)
    period = 0

    while (period += 1) < string.length
      next unless string.length % period == 0

      pattern = string[0...period]
      break unless string.scan(/.{#{period}}/).any? { |chunk| chunk != pattern }
    end

    period
  end

  File.open(ARGV[0]).map(&:strip).each do |string|
    puts find_period(string)
  end

However, I cannot ethically try to obfuscate that and then post it as my solution.
Plus there's more to learn.  So how aobut this, revolving around string
multiplication.

1. Otherwise, for pat_len = 2 up to half the string length
   a. copy the leftmost pat_len characters
   b. multiply them by (string length)/pat_len
   c. if the result matches the original string, then the multiplier
      from b. is the period.  Return that

2. Otherwise, return the string length as the answer.

This is going to make a lot of string temps, unlike SDS's solution
(sigh).

An aside on primes:
  If the string's length is a prime number, then its period is its
  length, unless it consists of length instances of the same letter.

  note: we should precompute primes in the range 3..80.  Use a sieve.
  note2: there's a prime library class since 1.9.x, no?
=end

def string_period( string )
  1.upto string.length - 1 do |period|
    next unless string.length % period == 0
    pattern = string[0 .. period-1] # the variables pattern and reps aren't
    reps = string.length / period   # necessary but are added for clarity
    return period if pattern * (string.length / period) == string
  end 
  return string.length
end

File.open(ARGV[0]).map(&:strip).each do |string|
  puts string_period(string)
end
