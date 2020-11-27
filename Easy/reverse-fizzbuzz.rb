f  = []
b  = []
n  = gets.to_i
st = nil
(1..n).each do |i|
    line = gets.chomp
    f << i if line.include?('Fizz')
    b << i if line.include?('Buzz')
    if st.nil? and line.to_i != 0
        cur = line.to_i
        st  = cur - i
    end
end
fizz = f.size==1 ? f[0]+st : f[1]-f[0]
buzz = b.size==1 ? b[0]+st : b[1]-b[0]

puts [fizz,buzz]*' '