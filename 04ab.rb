log = []

File.open("04.in", "r") do |f|
	log = f.readlines.sort
end

guards = {}
guard = ""
minute = 0

log.each do |l|
	if /\[.*\] Guard \#([0-9]+) begins shift/.match(l)
		guard = $1.to_i
		minute = 0
		if guards[guard] == nil
			guards[guard] = Array.new(60, 0)
		end
		next
	end
	/\[.*:([0-9][0-9])\] (falls asleep|wakes up)/.match(l)
	new_minute = $1.to_i
	state = ($2 == "wakes up") ? 1 : 0
	((minute)..(new_minute-1)).each do |m|
		guards[guard][m] += state
	end
	minute = new_minute
end

# guards.each do |g|
#	puts g.inspect
#	puts g[1].sum
# end

puts "STRATEGY 1 / most sleeping guard"

mostsleep = guards.max_by { |id, slp| slp.sum }
puts mostsleep.inspect

mostminute = mostsleep[1].rindex(mostsleep[1].max)
puts mostminute.inspect

puts mostsleep[0]*mostminute


puts
puts "STRATEGY 2 / most asleep minute"

mostguard = guards.max_by { |id, slp| slp.max }
puts mostguard.inspect

mostminute = mostguard[1].rindex(mostguard[1].max)
puts mostminute.inspect

puts mostguard[0]*mostminute
