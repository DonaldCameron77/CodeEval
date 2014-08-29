#
# MORSE CODE - CodeEval Easy challenge
# 
# CHALLENGE DESCRIPTION:
# 
# You have received a text encoded with Morse code and want to decode it.
# 
# INPUT SAMPLE:
# 
# Your program should accept as its first argument a path to a filename.
# Input example is the following:
# 
# .- ...- ..--- .-- .... .. . -.-. -..-  ....- .....
# -... .... ...--
# 
# Each letter is separated by a space char, each word is separated by 2 space chars.
# 
# OUTPUT SAMPLE:
# 
# Print out decoded words. E.g.
# 
# AV2WHIECX 45
# BH3
# 
# You program has to support letters and digits only.
# 

morse_map = {
   ".-"	   =>  'A',
   "-..."  =>  'B',
   "-.-."  =>  'C',
   "-.."   =>  'D',
   "."	   =>  'E',
   "..-."  =>  'F',
   "--."   =>  'G',
   "...."  =>  'H',
   ".."	   =>  'I',
   ".---"  =>  'J',
   "-.-"   =>  'K',
   ".-.."  =>  'L',
   "--"	   =>  'M',
   "-."	   =>  'N',
   "---"   =>  'O',
   ".--."  =>  'P',
   "--.-"  =>  'Q',
   ".-."   =>  'R',
   "..."   =>  'S',
   "-"	   =>  'T',
   "..-"   =>  'U',
   "...-"  =>  'V',
   ".--"   =>  'W',
   "-..-"  =>  'X',
   "-.--"  =>  'Y',
   "--.."  =>  'Z',
   ".----" =>  '1',
   "..---" =>  '2',
   "...--" =>  '3',
   "....-" =>  '4',
   "....." =>  '5',
   "-...." =>  '6',
   "--..." =>  '7',
   "---.." =>  '8',
   "----." =>  '9',
   "-----" =>  '0'
}


File.open(ARGV[0]).each_line do |line|
  words = line.chomp!.gsub('  ', '|').split('|')
  words.each do |word|
    word.split.each { |morse| print morse_map[morse] }
    print ' '
  end
  puts
end

# eof
