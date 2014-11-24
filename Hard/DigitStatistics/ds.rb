=begin
DIGIT STATISTICS - CodeEval Hard challenge


CHALLENGE DESCRIPTION:

Given the numbers "a" and "n" find out how many times each digit from
zero to nine is the last digit of the number in a sequence [ a, a2, a3,
... an-1, an ] { note: they mean a**1, a**2, ... a**n }

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line of input contains two space separated integers "a" and "n"
E.g: 

2 5

OUTPUT SAMPLE:

For each line of input print out how many times the digits zero, one,
two ... nine occur as the last digit of numbers in the sequence E.g:


0: 0, 1: 0, 2: 2, 3: 0, 4: 1, 5: 0, 6: 1, 7: 0, 8: 1, 9: 0

In this example, the sequence consists of numbers 2, 4, 8, 16 and 32.
Among the last digits, the digit two occurs twice, and each of the
digits four, six and eight occurs once.

Constraints: 
1 ≤ n ≤ 1 000 000 000 000, 
2 ≤ a ≤ 9

=end

# We can't compute powers in (1 ... n) for arbitrarily large n,
# because it takes too long.  Fortunately, in the sequence
# a**1, a**2, a**n for arbitrarily large n and # 2 <= a <= 9,
# the rightmost digit of the powers cycle through
# a sequence whose length is at most 4, depending on a.

seq = [ [2, 4, 8, 6],
	[3, 9, 7, 1],
	[4, 6],
	[5],
	[6],
	[7, 9, 3, 1],
	[8, 4, 2, 6],
	[9, 1] ]

# we could compute the length of seq[a]  whenever needed,
# but let's see if it's readable doing it this way.
# Note that e.g. a == 2 will map to seq[0] and seq_len[0]

seq_len = [4, 4, 2, 1, 1, 4, 4, 2]

File.open(ARGV[0]).each_line do |line|
  inp = line.split()
  a = inp[0].to_i; n = inp[1].to_i
  counts = Array.new(10, 0)

  a_seq = seq[a - 2] # a in (2..n) but seq is 0-based
  a_seq_len = seq_len[a - 2]

  # full is the number of times each of the digits in a_seq
  # are counted when all of them are counted.
  # partial is the number of digits from 0.. to be counted
  # one more time.  E.g. n is 11 and a is 2. All the digits
  # [2, 4, 8, 6] occur twice (11/4), and the first 2 occur
  # once (11 % 4).

  full	  = n / a_seq_len
  partial = n % a_seq_len

  # we're getting digits out of a_seq, which serve as
  # indices into the counts array
  a_seq.each { |full_idx| counts[full_idx] = full }

  if partial > 0
    a_seq[0..partial-1].each { |partial_idx| counts[partial_idx] += 1 }
  end

  counts.each_index { |idx| print idx.to_s + ': ' + counts[idx].to_s +
        (idx == 9 ? '' : ', ') }
  puts
end

#end of file

