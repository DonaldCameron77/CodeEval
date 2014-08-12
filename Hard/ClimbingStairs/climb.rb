#  CLIMBING STAIRS - CodeEval Easy challenge
# 
# CHALLENGE DESCRIPTION:
# 
# You are climbing a stair case. It takes n steps to reach to the top.
# Each time you can either climb 1 or 2 steps. In how many distinct ways
# can you climb to the top?
# 
# INPUT SAMPLE:
# 
# Your program should accept as its first argument a path to a filename.
# Each line in this file contains a positive integer which is the total
# number of stairs.  Ignore all empty lines. E.g.
# 
# 10
# 20
# 
# OUTPUT SAMPLE:
# 
# Print out the number of ways to climb to the top of the staircase. E.g.
# 
# 89
# 10946
# 
# Constraints: 
# The total number of stairs is <= 1000
# */
# 
# /* Isn't this just Moderate/DecodeNumbers with the bother of ensuring
#    you don't branch if the 2-digit number used is > 26?
# 
#    Note: the number of ways the digits 1 and 2 can be combined to
#    sum to n is the nth Fibonacci number!!
#
#    Note2: the values computed will overflow a Fixnum or
#    C++ long long (the latter as implemented by clang++/llvm on OSX

memo = [0, 1, 2]

File.open(ARGV[0]).each_line do |line|
  n = line.to_i
  while n >=  memo.size do
    msize = memo.size
    memo.push( memo[msize - 1] + memo[msize - 2] )
  end # while
  puts memo[n]
end

# EOF
