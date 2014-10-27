# SUGGEST GROUPS - CodeEval Moderate challenge
# 
# CHALLENGE DESCRIPTION:
# 
# You may have noticed that a new feature was added to our web site – user
# groups. So, this challenge is about joining groups.
# 
# You are given a list of users of a social network, friends of each user,
# and groups the user participates in.
# 
# To help users find the most interesting groups, we suggest them joining
# the groups where ≥50% of their friends participate.
# 
# Your task is to write a program which finds a list of suggested groups
# for each user.
# 
# INPUT SAMPLE:
# 
# The first argument is a file that contains the information about each
# user, one user per line. The line is delimited by colon ‘:’ into three
# parts: user name, list of friends, and list of groups. The items in each
# part are delimited by comma ‘,’.
# 
# For example:
# 
# Amira:Isaura,Lizzie,Madalyn,Margarito,Shakira,Un:Driving,Mineral collecting
# Elliot:Isaura,Madalyn,Margarito,Shakira:Juggling,Mineral collecting
# Isaura:Amira,Elliot,Lizzie,Margarito,Verla,Wilford:Juggling
# Lizzie:Amira,Isaura,Verla:Driving,Mineral collecting,Rugby
# Madalyn:Amira,Elliot,Margarito,Verla:Driving,Mineral collecting,Rugby
# Margarito:Amira,Elliot,Isaura,Madalyn,Un,Verla:Mineral collecting
# Shakira:Amira,Elliot,Verla,Wilford:Mineral collecting
# Un:Amira,Margarito,Wilford:
# Verla:Isaura,Lizzie,Madalyn,Margarito,Shakira:Driving,Juggling,Mineral collecting
# Wilford:Isaura,Shakira,Un:Driving
# 
# OUTPUT SAMPLE:
# 
# Print to stdout the list of suggested groups for each user. The list of
# users and the list of groups for each user must be sorted
# alphabetically.
# 
# For example:
# 
# Isaura:Driving,Mineral collecting
# Lizzie:Juggling
# Madalyn:Juggling
# Margarito:Driving,Juggling
# Shakira:Driving,Juggling
# Un:Driving,Mineral collecting
# 
# CONSTRAINTS:
# 
# - Number of users in input data is 200.
# - Number of different groups in input data is 15.
# - There can be users that do not participate in any group.
# - Friendship is mutual (if user A is a friend with user B,
#   then user B is a friend with user A).
#
# =================================================================

# user of a social network.
# objects will be values of hash
class SN_user
  attr_reader :friends, :groups
  def initialize(friends, groups)
    # note: we don't need the name here b/c it's the hash key 
    # and this object is the hash value
    @friends = friends
    @groups = groups
  end
end # SN_user

social_network = {}

File.open(ARGV[0]).each_line do |line|
  aline = line.split(":")
  user = aline[0]
  friends = aline[1].split(',')
  groups = aline[2].chomp.split(',')
  cur_user = SN_user.new(friends, groups)
  social_network[user] = cur_user;
end

social_network.each_key do |cur_user|	  # for each user
  recs = Hash.new(0)	  # will be list of recommended groups for cur_user
  flist = social_network[cur_user].friends
  flist.each do |cur_friend|	  # for each friend
    glist = social_network[cur_friend].groups
    glist.each do |cur_friends_group|
      recs[cur_friends_group] += 1 unless social_network[cur_user].groups.include?(cur_friends_group)
    end # 
  end # f next if recs.size == 0
  threshold = (flist.size + 1) / 2
  recs.delete_if { |key, value| value < threshold }
  next if recs.size == 0
  # can we sort the hash directly, avoiding this copy to an array?
  reclist = []	  # final sorted list of recommendations for user u
		  # We create this b/c we prefer not to sort hash keys
		  # in recs, so we extract them into reclist.
  recs.each_key { |k| reclist << k }
  puts cur_user + ':' + reclist.sort.join(',')
end # u

# eof