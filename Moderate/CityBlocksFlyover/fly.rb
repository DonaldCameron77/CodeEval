=begin
CITY BLOCKS FLYOVER - CodeEval Moderate challenge
CHALLENGE DESCRIPTION:

In our city we need to know how many blocks were impacted by a
helicopter flying over our city. In our city, all of the blocks are
rectangular. They are separated by N number of straight horizontal
avenues that run East-West and M number of straight vertical streets
which run North-South. A helicopter took off at the South-West corner of
the city and flew directly to the farthest North-East corner. Your
challenge is to determine how many city blocks it flew over? 

You will be given two lists, the first one is for streets and the second
one is for avenues. Each avenue and each street is represented by a
distance D to itself from the helicopter's starting point. E.g. 
   
On the first diagram the streets and the avenues are represented by the
following lists:

(0,1,3,4,6) for streets
(0,1,2,4) for avenues

The blocks the helicopter has flown over are colored dark grey. 

The inner region of each small rectangle is a city block. Rectangles'
borders are not considered as a part of a block. 

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename.
Each line in this file is one test case. Each test case will contain a
list of distances for streets and a list of distances for avenues. Each
list is in a brackets and the distances are separated by comma. The
lists themselves are separated by a single whitespace. E.g.

(0,2,4,8,10,13,14,18,22,23,24,33,40,42,44,47,49,53,55,63,66,81,87
,91) (0,147,220)
(0,1,2,4) (0,1,3,4,5)
(0,1,3,4,6) (0,1,2,4)

OUTPUT SAMPLE:

For each set of input print out the number of blocks the helicopter has
flown over. E.g.


24
6
5

Constraints: 

N, M are in range [1, 100] 
D is in range [1, 1000]
=end

# An important point is that there are no streets or avenues that don't
# "go through", i.e., they all go from one side of the grid to the other
# uninterrupted.  This is implied by the simplicity of the input data,
# but still is worth noting, as it allows a simplified approach


def print_array(arr)
  arr.each { |elem| print elem.to_s + " " }
  puts
end

while (line = gets) do
  sx, sy = line.chomp.split
# now have coordinates x0..xn, y0..ym as strings
  # convert coordinate strings to arrays of int
  ax = sx[1..-2].split(',').map{ |elem| elem.to_i }
  ay = sy[1..-2].split(',').map{ |elem| elem.to_i }
  
  slope = 1.0 * (ay[-1] - ay[0]) / (ax[-1] - ax[0])
  blocks = 0 
  
  # We look at one rectangle at a time, in row-major order.
  # We're assured the line lies in the interval (x_ix..x_ix+1),
  # and we ask if its lowest point in that interval is less
  # than the top of the rectangle (ay[y_ix+1]), and if its
  # highest point is greater than the bottom of the rectangle
  # (ay[y_ix].
  ay[0..-2].each_index do |y_ix|
    ax[0..-2].each_index do |x_ix|
      blocks += 1 if slope * ax[x_ix] < ay[y_ix + 1] &&
		    slope * ax[x_ix + 1] > ay[y_ix]
    end
  end 

  puts blocks
  
end

# eof
