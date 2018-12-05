# 6.3 s


# Ruby Regexp doesn't seem to support \U and \l, so create all aA, Aa to zZ, Zz pairs
rstr = ""
('a'..'z').each do |l|
    rstr << '|' unless l == 'a'
    rstr << "#{l}#{l.upcase}|#{l.upcase}#{l}"
end
REACT_REGEXP = Regexp.new(rstr)

def react(str)
    ret = str.dup
    while ret.gsub!(REACT_REGEXP, '') do; end
    ret
end

str = File.read("05.in")
str.strip!

str = react(str)
puts "Reacted to: "
puts str.length

puts "Min length after one unit removal: "
puts ('a'..'z').map { |l| react(str.gsub(/#{l}/i, '')).length }.min
