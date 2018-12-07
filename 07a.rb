require 'benchmark'
require 'set'

class SortedSet
    def pop
        x = self.first
        self.delete(x)
        x
    end
end

# 10000 times: 1.9 sec
def solve_naive(reqs)
    order = ''
    reqs = reqs.dup

    to_be_done = (reqs.map { |r| r[0] } + reqs.map{ |r| r[1] }).uniq
    while !to_be_done.empty? do
        cannot_be_done = reqs.map { |r| r[1] }.uniq

        done = (to_be_done - cannot_be_done).sort.first
        order << done

        to_be_done.delete(done)
        reqs.delete_if { |r| r[0] == done }
    end

    return order
end

# 10000 times: 0.6 sec
def solve_v2(reqs)
    order = StringIO.new

    blocked_steps = [0] * 26  # just count, assume there are no multiple edges
    blocking_steps = Array.new(26) { [] }

    reqs.each do |r|
        before = r[0].ord - 'A'.ord
        after = r[1].ord - 'A'.ord

        blocked_steps[after] += 1
        blocking_steps[before] << after
    end

    freed_steps = SortedSet.new((0...26).select { |ord| !blocking_steps[ord].empty? && blocked_steps[ord] == 0 } )

    while !freed_steps.empty? do
        ord = freed_steps.pop
        ch = ('A'.ord + ord).chr
        
        order << ch

        blocking_steps[ord].each do |blocked|
            blocked_steps[blocked] -= 1
            freed_steps << blocked if blocked_steps[blocked] == 0
        end
    end

    return order.string
end


reqs = []
File.open("07.in", "r").each_line do |l|
    /Step ([A-Z]) must be finished before step ([A-Z]) can begin/.match(l)
    reqs << [$1, $2]
end


Benchmark.bm do |b|
    b.report("Naive v1\t") do
        10000.times do
            solve_naive(reqs)
        end
    end
    puts solve_naive(reqs)

    b.report("Solution v2\t") do
        10000.times do
            solve_v2(reqs)
        end
    end
    puts solve_v2(reqs)
end
