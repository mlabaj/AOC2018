require 'set'

class SortedSet
    def pop
        x = self.first
        self.delete(x)
        x
    end
end

def solve(reqs)
    order = ''
    reqs = reqs.dup

    time = 0
    workers_free = SortedSet.new(0..4)
    to_be_done = (reqs.map { |r| r[0] } + reqs.map{ |r| r[1] }).uniq
    assembly = SortedSet.new

    while to_be_done.any? || assembly.any? do
        cannot_be_done = reqs.map { |r| r[1] }.uniq
        can_be_done = to_be_done - cannot_be_done

        if workers_free.any? && can_be_done.any?
            # assign work
            doing = can_be_done.sort.first
            worker = workers_free.pop

            assembly << [time + 60 + (doing.ord - 'A'.ord + 1), doing, worker]
            to_be_done.delete(doing)
        else
            # advance time
            (time, done, worker) = assembly.pop

            workers_free << worker
            reqs.delete_if { |r| r[0] == done }

            order << done
        end
    end

    puts order
    puts "#{time} sec"
end

reqs = []
File.open("07.in", "r").each_line do |l|
    /Step ([A-Z]) must be finished before step ([A-Z]) can begin/.match(l)
    reqs << [$1, $2]
end


solve(reqs)
