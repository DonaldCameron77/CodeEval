# FIND MIN - CodeEval Hard challenge
# CHALLENGE DESCRIPTION:
# 
# Credits: This problem appeared in the Facebook Hacker Cup 2013 Hackathon. 
# 
# After sending smileys, John decided to play with arrays. Did you know
# that hackers enjoy playing with arrays? John has a zero-based index
# array, m, which contains n non-negative integers. However, only the
# first k values of the array are known to him, and he wants to figure out
# the rest. 
# 
# John knows the following: for each index i, where k <= i < n, m is the
# minimum non-negative integer which is *not* contained in the previous
# *k* values of m. 
# 
# For example, if k = 3, n = 4 and the known values of m are [2, 3, 0], he
# can figure out that m[3] = 1. John is very busy making the world more
# open and connected, as such, he doesn't have time to figure out the rest
# of the array. It is your task to help him. Given the first k values of
# m, calculate the nth value of this array. (i.e. m[n - 1]).Because the
# values of n and k can be very large, we use a pseudo-random number
# generator to calculate the first k values of m. Given positive integers
# a, b, c and r, the known values of m can be calculated as follows:
# 
#     m[0] = a
#     m = (b * m[i - 1] + c) % r, 0 < i < k
#     
# INPUT SAMPLE:
# 
# Your program should accept as its first argument a path to a filename.
# Each line in this file contains 6 comma separated positive integers
# which are the values of n,k,a,b,c,r in order. E.g.
# 
# 78,51,3,5,5,51230
# 186,75,68,16,539,312
# 137,135,48,17,461,512
# 98,22,6,30,524,100
# 46,18,7,11,9,46
# 
# OUTPUT SAMPLE:
# 
# Print out the nth element of m for each test case e.g.
# 
# 26
# 34
# 1
# 6
# 12
# 

File.open(ARGV[0]).each_line do |line|
  inp_arr = line.chomp.split(',').map(&:to_i)
  n = inp_arr[0]  # number of elements in m
  k = inp_arr[1]  # we know the first k values
  a = inp_arr[2]  # a, b, c, & r are used to compute
  b = inp_arr[3]  # the first k values
  c = inp_arr[4]
  r = inp_arr[5]

  m = Array.new(n)
  m[0] = a;
  1.upto(k-1) do |x|
    m[x] = (b * m[x-1] + c) % r
  end

  k.upto(n-1) do |y|
    0.upto(k) do |val|
      if !m[y - k .. y - 1].include?(val)
	m[y] = val;
	break
      end
    end
  end

  puts m[n-1]

end # File open

# eof
