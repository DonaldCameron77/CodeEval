# MAGIC NUMBERS - CodeEval Moderate challenge
# CHALLENGE DESCRIPTION:
# 
# There are two wizards, one good and one evil. The evil wizard has
# captured the princess. The only way to defeat the evil wizard is to
# recite a set of magic numbers. The good wizard has given you two
# numbers, A and B. Find every magic number between A and B, inclusive.
# 
# A magic number is a number that has two characteristics:
# 
# 1. No digits repeat.
#
# 2. Beginning with the leftmost digit, take the value of the digit and move
#    that number of digits to the right. Repeat the process again using the
#    value of the current digit to move right again. Wrap back to the
#    leftmost digit as necessary. A magic number will visit every digit
#    exactly once and end at the leftmost digit.
#
# For example, consider the magic number 6231.
# 
# Start with 6. Advance 6 steps to 3, wrapping around once
# (6→2→3→1→6→2→3).
# From 3, advance to 2.
# From 2, advance to 1.
# From 1, advance to 6.
# 
# INPUT SAMPLE:
# 
# The input is a file with each line representing a test case. Each test
# case consists of two integers A and B on a line, separated by spaces.
# For all test cases 1 <= A <= B <= 10000.
# 
# 10 100
# 8382 8841
# 
# OUTPUT SAMPLE:
# 
# For each test case print all magic numbers between A and B, inclusive,
# on one line, separated by spaces. If there is no magic number between A
# and B, print -1.
# 
# 13 15 17 19 31 35 37 39 51 53 57 59 71 73 75 79 91 93 95 97
# -1
# CONSTRAINTS:
# 
# The number of test cases is 20.
# 

=begin

  Operation:

    for candidate c in A..B inclusive

      if c has any repeated digit, bail
      for each digit d in c, set d.visited = false;

      set cur_index = 0

      while true
	obtain next digit n by advancing d digits to the right (mod length of c)
	if n's index is 0
	  if all the other digits have been visited 
	    report that d is a magic number and end inner loop
	  else if n has been visited already, bail
	  else set n.visited and advance 
=end

# refactored version 2015-05-03 - minor cleanup based on new C# code

def print_magic_numbers(a, b)
  found_magic = false;

  a.upto(b) do |c|
    digits = c.to_s.split('').map(&:to_i)
    next if digits.uniq.length != digits.length # candidate has repeated digits: #{c}"

    visited = Array.new(digits.length, false)
    cur_index = 0

    loop do

      cur_index = (cur_index + digits[cur_index]) % digits.length
      break if visited[cur_index] # visiting digit position again? Not magic

      visited[cur_index] = true;

      if cur_index == 0 # decision time: circled back to leftmost digit
	break if visited.count(true) != visited.size
	print " " if found_magic  # to suppress trailing blank on last magic #
	print c
	found_magic = true;
      end
    end # loop do
  end # a upto b

  print "-1" if !found_magic
  puts

end

File.open(ARGV[0]).each_line do |line|
  input_arr = line.chomp.split
  a = input_arr[0].to_i
  b = input_arr[1].to_i
  print_magic_numbers(a, b)
end

# eof
