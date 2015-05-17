# GRONSFELD CIPHER
# CHALLENGE DESCRIPTION:
# 
# You are given a key and an enciphered message. The message was enciphered with the following vocabulary:
# 
#  !"#$%&'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
# Note: The first symbol is space.
# 
# Your task is to decipher the message that was enciphered with the
# Gronsfeld cipher using the given key.
# 
# The Gronsfeld cipher is a kind of the Vigenère cipher and is similar to
# the Caesar cipher. The only difference is that in the Caesar cipher,
# each character is shifted along by the same number, while in the
# Gronsfeld cipher, each character has its own number of shifts. It means
# that the length of key for the Gronsfeld cipher must be the same as the
# length of the message. But since it is difficult to remember such a key,
# especially if the message is long, the key of the message is repeated
# until it has the same length as the message.
# 
# For example:
# 
# For the word "EXALTATION" and the key "31415", the ciphertext is the following:
# 
#   EXALTATION
#   3141531415
# 
#   Enciphering the first letter:
#   'E' + 3 -> 'H'
# 
# Accordingly, enciphered message is the following:
# 
# HYEMYDUMPS
# 
# INPUT SAMPLE:
# 
# The first argument is a file with different test cases (there are
# possible test cases with spaces at enciphered message). Each test case
# contains a key and an enciphered message separated by semicolon.  For
# example:
# 
# 
# 31415;HYEMYDUMPS
# 45162;M%muxi%dncpqftiix"
# 14586214;Uix!&kotvx3
# 
# OUTPUT SAMPLE:
# 
# Print to stdout a deciphered message.
# For example:
# 
# EXALTATION
# I love challenges!
# Test input.
# 
# CONSTRAINTS:
# 
# To decode a message, use the following alphabet:
#   ' !"#$%&\'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
# 
# The number of test cases is 40.
# 

Charset = ' !"#$%&\'()*+,-./0123456789:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'

# find c's index in the Charset string,
# decrement the index by offset,
# and ensure it wraps around properly

# c is the current character from the encrypted message.
# offset is distance to travel backwards (perhaps wrapping around)
# in the given character set to decode the character

def charmap( c, offset )
  start_index = Charset.index(c)
  finish_index = start_index - offset
  if finish_index < 0
    finish_index = Charset.length + finish_index
  end
  return Charset[finish_index]
end

File.open(ARGV[0]).each_line do |line|
  a = line.chomp.split(';')
  key = a[0]
  msg = a[1]
  key_index = 0;
  0.upto(msg.length - 1) do |x|
    letter = charmap(msg[x], key[key_index].ord - '0'.ord)
    key_index = (key_index + 1) % key.length
    print letter
  end
  puts
end

# eof

