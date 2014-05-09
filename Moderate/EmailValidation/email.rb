=begin EMAIL VALIDATION - CodeEval Moderate (!) challenge
VIEW CHALLENGE DESCRIPTION

CHALLENGE DESCRIPTION:

You are given several strings that may/may not be valid emails. You should write a regular expression that determines if the email id is a valid email id or not. You may assume all characters are from the english language.

INPUT SAMPLE:

Your program should accept as its first argument a filename. This file will contain several text strings, one per line. Ignore all empty lines. E.g. 

foo@bar.com
this is not an email id
admin#codeeval.com
good123@bad.com

OUTPUT SAMPLE:

Print out 'true' (all lowercase) if the string is a valid email. Else print out 'false' (all lowercase). E.g.

true
false
false
true

=end

File.open(ARGV[0]).each_line do |line|
  line.chomp!
  unless line.empty?
  
    # Layout of the pattern: match username'@'sitename'.'TLD
    # where
    # username is either a quoted string containing an otherwise-valid username,
    #   or alphanumberics + underscore (i.e., the \w pattern)
    #   optionally followed by one or more dots, plusses, or words.
    # sitename is a word, optionally preceded by 1 or more <word'.'> groups
    # TLD is a word two or more characters long, or an asterisk.  Domain
    #   should be restricted to 2-6 letters only, but we are not checking this.
    # The pattern must match from the beginning of the string to the end.
    # Note - this is simplified with respect to the RFCs 5321, 5322, & 6531.
    # Real-world validation might be better done by simply accepting the user
    # email address string as long as it contains an '@', and ensuring
    # the user can receive mail at that address.
    
    done = false;
    # First handle quotes surrounding the username.
    if line[0] == '"'
      line = line[1..-1]
      k = line.index('"') # find closing quote if any
      if line[k+1] != '@'
        puts false.to_s
        done = true
      end
      line.slice!(k)
    end
    
    unless done
      email_pattern = /\w+(\.|\+|\w+)*@(\w+\.)+(\w\w+|\*)$/
      match_pos = line =~ email_pattern
      if match_pos == 0
        puts true.to_s
      else
        puts false.to_s
      end
    end # if match_pos ...
  end # unless
end # each line


