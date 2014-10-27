# 
# HAPPY NUMBERS - CodeEval Easy challenge
# CHALLENGE DESCRIPTION:
# 
# A happy number is defined by the following process. Starting with any
# positive integer, replace the number by the sum of the squares of its
# digits, and repeat the process until the number equals 1 (where it will
# stay), or it loops endlessly in a cycle which does not include 1. Those
# numbers for which this process ends in 1 are happy numbers, while those
# that do not end in 1 are unhappy numbers.
# 
# INPUT SAMPLE:
# 
# The first argument is the pathname to a file which contains test data,
# one test case per line. Each line contains a positive integer. E.g.
# 
# 1
# 7
# 22
# 
# OUTPUT SAMPLE:
# 
# If the number is a happy number, print out 1. If not, print out 0. E.g
# 
# 1
# 1
# 0
# 

=begin # debug
def print_arr(str, arr)
  first = true;
  print str + " "
  arr.each do |i|
    print ", " unless first
    first = false
    print i.to_s
  end
  puts
end
=end

File.open(ARGV[0]).each_line do |line|
  # cur = line.chomp
  cur = line
  happy_arr = Array.new(1, cur.to_i)
  # puts "======================="
  # puts "input = " + cur
  loop do
    # print_arr("start of loop - Happy Array = ", happy_arr)
    digits = cur.to_s.split(//)
    # print "digits = "; puts digits.to_s
    cur = digits.inject(0) { | sum, digit | sum + digit.to_i ** 2 }
    # puts "in loop - cur = " + cur.to_s
    if cur == 1
      puts 1
      break 
    elsif happy_arr.include?(cur)
      puts 0
      break
    else
      happy_arr << cur
    end
  end
end

# eof
