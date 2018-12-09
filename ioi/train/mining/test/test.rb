
10000.times do
    n = rand(5) + 2
    edges = []
    for i in 1..(n-1) do
        k = rand(i-1) + 1

        a = Array.new(i) do |x|
            x
        end.shuffle.take(k).map do |x|
            edges.push [i, x]
        end
    end

    puts "#{edges.length}"

    for e in edges do
        puts "#{e.first + 1} #{e.last + 1}"
    end

end

puts "0"
