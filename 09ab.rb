require 'test/unit'

# ------------------------------------------------------------------
#  Circular doubly linked list with at least one node
# ------------------------------------------------------------------
class CircleList
  def initialize(val)
    @pointer = Node.new(val)
    @pointer.next = @pointer
    @pointer.prev = @pointer
  end

  def left(n = 1)
    n.times { @pointer = @pointer.prev }
  end

  def right(n = 1)
    n.times { @pointer = @pointer.next }
  end

  # do not remove the last one please :), not implemented
  def pop
    right
    return @pointer.prev.remove
  end

  def insert(val)
    @pointer = @pointer.insert_after(val)
  end

  def inspect
    s = StringIO.new
    cur_pointer = @pointer

    loop do
      s << cur_pointer.val
      cur_pointer = cur_pointer.next
      break if cur_pointer == @pointer
      s << " > "
    end

    return s.string
  end
end

# ------------------------------------------------------------------
#  A linked node
# ------------------------------------------------------------------
class Node
  attr_accessor :next, :prev, :val

  def initialize(val)
    @val = val
    @next = nil
    @prev = nil
  end

  def insert_after(val)
    new = self.class.new(val)

    @next.prev = new
    new.next = @next
    new.prev = self
    self.next = new

    return new
  end

  def remove
    @prev.next = @next
    @next.prev = @prev

    return @val
  end
end

# ------------------------------------------------------------------
#  Precompute scores at each 23rd marble
# ------------------------------------------------------------------
TAKEN = [0]

def presimulate(max, debug: false)
  table = CircleList.new(0)

  (1..max).each do |step|
    if step % 23 == 0
      table.left(7)
      score = table.pop + step

      TAKEN << score

      puts ">>>>>>>>>>> Taking #{score}" if debug
    else
      table.right(1)
      table.insert(step)
    end

    puts table.inspect if debug
  end

  puts TAKEN.inspect if debug
end

# ------------------------------------------------------------------
#  Actual solution, find players who take each 23rd marble
# ------------------------------------------------------------------
def simulate(players, last_marble)
  scores = [0] * players

  round = 0
  while round <= last_marble
    scores[round % players] += TAKEN[round/23]
    round += 23
  end

  return scores.max
end

def solve(desc)
  /([0-9]+) players; last marble is worth ([0-9]+) points/.match(desc)
  players, last_marble = $1.to_i, $2.to_i

  players, last_marble = yield players, last_marble if block_given?

  return "high score is #{simulate(players, last_marble)}"
end


# --- devel ---
# presimulate(25, debug: true)
# exit

# --- setup ---
presimulate(10_000_000)

# --- input ---
input = File.open("09.in", "r").read.strip
puts input
puts solve(input)
puts
puts "#{input}, last marble 100x larger"
puts solve(input) { |players, last_marble| [players, last_marble*100] }
puts

# --- verify against samples in task description ---
class SamplesTest < Test::Unit::TestCase
  def test_sample0
    assert_equal("high score is 32", solve("9 players; last marble is worth 25 points"))
  end

  def test_sample1
    assert_equal("high score is 8317", solve("10 players; last marble is worth 1618 points"))
  end

  def test_sample2
    assert_equal("high score is 146373", solve("13 players; last marble is worth 7999 points"))
  end

  def test_sample3
    assert_equal("high score is 2764", solve("17 players; last marble is worth 1104 points"))
  end

  def test_sample4
    assert_equal("high score is 54718", solve("21 players; last marble is worth 6111 points"))
  end

  def test_sample5
    assert_equal("high score is 37305", solve("30 players; last marble is worth 5807 points"))
  end
end

