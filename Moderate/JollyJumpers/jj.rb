=begin

JOLLY JUMPERS - CodeEval Moderate challenge

CHALLENGE DESCRIPTION:

Credits: Programming Challenges by Steven S. Skiena and Miguel A. Revilla 

A sequence of n > 0 integers is called a jolly jumper if the absolute
values of the differences between successive elements take on all
possible values 1 through n - 1. eg.  1 4 2 3 is a jolly jumper, because
the absolute differences are 3, 2, and 1, respectively. The definition
implies that any sequence of a single integer is a jolly jumper. Write a
program to determine whether each of a number of sequences is a jolly
jumper.

INPUT SAMPLE:

1 4 2 3

Your program should accept as its first argument a path to a filename.
Each line in this file is one test case. Each test case will contain an
integer n < 3000 followed by n integers representing the sequence. The
integers are space delimited.

OUTPUT SAMPLE:

For each line of input generate a line of output saying 'Jolly' or 'Not jolly'.

=end

File.open(ARGV[0]).each_line do |line|
  inp_arr = line.split.map(&:to_i)
  count = inp_arr[0]
  inp_arr.shift

  # For k = 0 .. count -2,
  # we compute the absolute difference diff between inp_arr[k] and inp_arr[k+1].
  # If diff is 0 or > count - 1 (> = count), or we see any diff more
  # than once, then the number is not a jolly jumper
  # The diffs array is [0..count], but diffs[0] is not used

  diffs = Array.new(count, 0) # using as Bool array with values 0 & 1
  # value of 1 at diffs[k] implies we've seen that difference before

  jolly_jumper = true

  0.upto(count - 2) do |idx|
    cur_diff = (inp_arr[idx] - inp_arr[idx + 1]).abs
    if (cur_diff == 0) || (cur_diff > count - 1) || (diffs[cur_diff] != 0)
      jolly_jumper = false
      break;
    end
    diffs[cur_diff] = 1
  end

  puts jolly_jumper ? 'Jolly' : 'Not jolly'
end

#end of file

