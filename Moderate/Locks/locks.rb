# LOCKS - CodeEval Moderate challenge
# CHALLENGE DESCRIPTION:
# 
# There are "n" unlocked rooms located in a row along a long corridor.
# 
# A security guard starts at the beginning of the corridor, passes by and
# locks the lock of every second door(2, 4, 6 ...). If a lock was open, it
# now becomes closed, if it was closed, it stays closed. He then returns
# to the beginning of the corridor and switches the lock to the opposite
# position on every third door(3, 6, 9 ...): if the door's lock was open
# before, he close it and vice versa. This algorithm (first every second
# door's lock is closed; then every third door's lock is switched to the
# opposite position) repeats "m"-1 times.
# 
# On his last pass (the "m" one), only the last door's lock must be
# switched without any additional actions.
# 
# Your job is to determine how many doors have been left unlocked.
# 
# INPUT SAMPLE:
# 
# Your program should accept as its first argument a path to a filename.
# 
# Each line of input contains 2 integer - n - number of locks and m - how
# many times to repeat actions:
# 
# 3 1
# 100 100
#
# OUTPUT SAMPLE:
# 
# For each line of input print out how many door are left unlocked: # 
# 2
# 50
# ===========================================================

# A brute-force solution with debug output reveals that the doors
# will have a repeating pattern.
# 
# The exception is when m - repetition count - is 1, in which case
# only the rightmost door will be locks, so that the number unlocked
# is n - number of doors/locks - minus 1.
#
# Otherwise (m >= 2), complete groups of 6 doors (not counting the
# first) will ahve the following pattern:
#
#       if n is even, 1 1 1 0 0 0
#       if n is odd,  1 0 1 0 0 0
#
# The final group of 1 to 6 locks have the same pattern, save for the
# rightmost lock being flipped on the last pass.  Rather than compute
# this, a pair of arrays exhaustively enumerates the number of unlocked
# doors when there are 1 to 6 remaining, and the number of repetitions m
# is odd or even

File.open(ARGV[0]).each_line do |line|
  a = line.split.map(&:to_i)
  nlocks = a[0]  # see comment below on 1-based indexing
  nreps = a[1]
  # this is the number of zeroes not including the final grouping
  # of up to 6 locks.
  if nreps == 1
    puts (nlocks - 1).to_s
  else
    # number of groups * (3 unlocked if even # of locks, otherwise 4)
    unlocked_count = 1 + ((nlocks - 2) / 6)*(nreps.even? ? 3 : 4)
    # now account for the final group.  We subtract off the first lock
    # and any/all complete groups of doors, starting with the 2nd door.
    left_over = nlocks - 1 - ((nlocks-2)/6)*6
    # account for the partial pattern of 6 with the rightmost lock flipped
    final_open = []
    if nreps.even?
      final_open = [1, 1, 1, 0, 1, 2]
    else
      final_open = [1, 0, 2, 1, 2, 3]
    end
    unlocked_count += final_open[left_over - 1]
    puts unlocked_count.to_s
  end
end # File

# EOF
