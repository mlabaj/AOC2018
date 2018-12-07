def solve_a(pts)
  area_of = [0] * pts.count

  xs = pts.map { |p| p[0] }
  ys = pts.map { |p| p[1] }

  xmin, xmax = xs.minmax
  ymin, ymax = ys.minmax

  xmin -= 1
  xmax += 1
  ymin -= 1
  ymax += 1

  (xmin..xmax).each do |x|
    (ymin..ymax).each do |y|
      pt = closest(x, y, pts)
      area_of[pt] += 1 if pt
    end
  end

  # remove everything on bounding box = infinites
  (xmin..xmax).each do |x|
    [ymin, ymax].each do |y|
      pt = closest(x, y, pts)
      area_of[pt] = -1 if pt
    end
  end
  [xmin, xmax].each do |x|
    (ymin..ymax).each do |y|
      pt = closest(x, y, pts)
      area_of[pt] = -1 if pt
    end
  end

  return area_of.max
end

def closest(x, y, pts)
  dists = pts.map { |px, py| (px-x).abs + (py-y).abs }
  mindist = dists.min

  return dists.count(mindist) > 1 ? nil : dists.index(mindist)
end

def solve_b(pts)
  xs = pts.map { |p| p[0] }
  ys = pts.map { |p| p[1] }

  point = [xs.sum/xs.count, ys.sum/ys.count]
  area = correct_dist(point, pts)
  last_area = [-1, -1]

  left = point[0]-1
  right = point[0]+1
  top = point[1]-1
  bottom = point[1]+1

  loop do
    last_area[0] = last_area[1]
    last_area[1] = area

    while point[0] < right
      point[0] += 1
      area += correct_dist(point, pts)
    end
    right += 1
    while point[1] > top
      point[1] -= 1
      area += correct_dist(point, pts)
    end
    top -= 1
    while point[0] > left
      point[0] -= 1
      area += correct_dist(point, pts)
    end
    left -= 1
    while point[1] < bottom
      point[1] += 1
      area += correct_dist(point, pts)
    end
    bottom += 1

    # since one iteration is not a complete spiral loop, wait until area isn't increased in at last two iterations
    return area if last_area[0] == area
  end
end

def correct_dist(point, pts)
  puts "Checking #{point[0]} #{point[1]}"
  dists = pts.map { |px, py| (px-point[0]).abs + (py-point[1]).abs }

  return dists.sum <= 10_000 ? 1 : 0
end

points = []
File.open("06.in", "r").each_line do |l|
  /([0-9]+), ([0-9]+)/.match(l)
  points << [$1.to_i, $2.to_i]
end

puts solve_a(points)
puts solve_b(points)
