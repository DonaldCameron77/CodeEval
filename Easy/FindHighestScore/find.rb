# FIND THE HIGHEST SCORE - CodeEval Easy challenge
# CHALLENGE DESCRIPTION:
# 
# You decided to hold a banquet in honor of the World Art Day, where you
# invited all designers and artists that you know. During the banquet, you
# decided to find out which art movement and style the ordinary people
# like most of all, and whose works can get the highest score. To find the
# answer, you decided to hold an exhibition, where viewers will be able to
# evaluate each painting and vote for or against it. Each artist should
# create one work per each art movement.  After the exhibition, the
# participants calculated votes that they received for each painting and
# inserted them in the table. But, they could not determine which movement
# has won and whose work received the highest score, so they asked you to
# help.  You need to determine and print the highest score of each
# category in the table.
# 
# Example:
# 
#             Baroque     Surrealist  Modern
# Klimt           72          64        150
# Rembrandt      100          18         33
# Dali            13         250         -6
# MAXIMUM        100         250         150
# 
# Your job is to find the maxima of each column
# 
# INPUT SAMPLE:
# 
# The first argument is a path to a file. Each line includes a test case
# with a table. Table rows are separated by pipes '|'. All table rows
# contain scores for each category, so all lines are of an equal length.
# 
# For example:
# 
# 72 64 150 | 100 18 33 | 13 250 -6
# 10 25 -30 44 | 5 16 70 8 | 13 1 31 12
# 100 6 300 20 10 | 5 200 6 9 500 | 1 10 3 400 143
# 
# OUTPUT SAMPLE:
# 
# You need to print the highest score for each category.
# 
# For example:
# 
# 
# 100 250 150
# 13 25 70 44
# 100 200 300 400 500
# 
# CONSTRAINTS:
# 
# All lines in a test case are of an equal length.
# The number of participants can be from 2 to 10 people.
# The number of categories can be from 4 to 20.
# The number of points for one picture can be from -1000 to 1000.
# The number of test cases is 40.
# 
# ===============
# 
# Implementation: this is a snap in Ruby (I think!).
# In C++, it would be nice to have a class to handle variable
# sized two dimensional arrays (which is what we have here).

# ================

# print an array of integers, blank separated, but suppress trailing blank

def printarr(a)
  first = true
  0.upto(a.size - 1) do |i|
    print ' ' if ! first  
    print a[i]
    first = false
  end
  puts
end

# a is an array of strings representing rows of an integer array,
# with the rows separated by '|'.  This is a rectangular (i.e., not
# jagged) array.  Find the max of each column and return it as an array
# of int.

def find_column_maxima(a)
  maxarr = []

  max_index = input_index = 0

  # initialize the array of maxes to the first "row" of the input

  while a[max_index] != '|'
    maxarr[max_index] = a[input_index].to_i
    max_index += 1
    input_index += 1
    # debug
    # print max_index.to_s + " " + input_index.to_s; puts
  end

  # now we reset max_index, and increment input_index past the "|" we just
  # found.  One complication is to not fall of the end of the input array.

  max_index = 0

  while input_index < a.length
    input_index += 1 # skip over the '|'
    0.upto(maxarr.size - 1) do |m|
      cur_input = a[input_index].to_i
      # debug
      # print max_index.to_s + " " + input_index.to_s; puts
      input_index += 1
      maxarr[m] = cur_input if cur_input > maxarr[m]
    end
  end
  maxarr
end

File.open(ARGV[0]).each_line do |line|
  a = line.chomp.split
  # puts a
  maxarr = find_column_maxima(a)
  printarr(maxarr)
end

# eof
