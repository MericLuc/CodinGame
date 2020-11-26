N = gets.to_i
V = gets.to_i
M = gets.to_i
T = {}
p = [0]*(N+1)

M.times do
    x, l, r = gets.split.map(&:to_i)
    T[x]  = [l,r]
    p[l] += 1
    p[r] += 1
end

root = p.rindex(0)
q = Queue.new
q << [root, []]
res = nil
while !q.empty?
    x,path = q.pop
    if x == V
        res = path
    end

    c = T[x]
    next if c.nil?

    q << [c[0], path + ['Left' ]]
    q << [c[1], path + ['Right']]
end
puts res.empty? ? 'Root' : res.join(' ')