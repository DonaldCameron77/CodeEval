
###################################################################
#
# CodeEval 'Easy' challenge - Beautiful Strings
#
# 
# BEAUTIFUL STRINGS
# CHALLENGE DESCRIPTION:
# 
# Credits: This problem appeared in the Facebook Hacker Cup 2013
# Hackathon. 
# 
# When John was a little kid he didn't have much to do. There was no
# internet, no Facebook, and no programs to hack on. So he did the only
# thing he could... he evaluated the beauty of strings in a quest to
# discover the most beautiful string in the world. 
# 
# Given a string s, little Johnny defined the beauty of the string as the
# sum of the beauty of the letters in it. The beauty of each letter is an
# integer between 1 and 26, inclusive, and no two letters have the same
# beauty. Johnny doesn't care about whether letters are uppercase or
# lowercase, so that doesn't affect the beauty of a letter. (Uppercase 'F'
# is exactly as beautiful as lowercase 'f', for example.) 
# 
# You're a student writing a report on the youth of this famous hacker.
# You found the string that Johnny considered most beautiful. What is the
# maximum possible beauty of this string?
# 
# INPUT SAMPLE:
# 
# Your program should accept as its first argument a path to a filename.
# Each line in this file has a sentence. E.g.
# 
# ABbCcc
# Good luck in the Facebook Hacker Cup this year!
# Ignore punctuation, please :)
# Sometimes test cases are hard to make up.
# So I just go consult Professor Dalves
# 
# OUTPUT SAMPLE:
# 
# Print out the maximum beauty for the string. E.g.
# 
# 152
# 754
# 491
# 729
# 646
# 
###########################################################

def compute_max_beauty( hash )
  max_beauty = 0
  cur_beauty_mult = 26
  arr = hash.sort_by { |letter, count| count }
  arr.reverse_each do |entry|
    max_beauty += cur_beauty_mult * entry[1]
    cur_beauty_mult -= 1
  end
  max_beauty
end

File.open(ARGV[0]).each_line do |line|
  line.downcase!
  char_hash = Hash.new(0)
  # puts "next line : #{line}"
  line.each_char do |char|
    if char =~ /[a-z]/
      char_hash[char] += 1
    end
  end
  puts compute_max_beauty( char_hash )
end

# eof
