require 'open3'

1000.times do
    n = rand(100) + 11
    t = rand(100) + 11
    s = rand(n) + 1
    e = rand(n) + 1
    inp = "#{n} #{t} #{s} #{e}\n"
    t.times do
        inp += "#{rand(n) + 1} #{rand(n) + 1} #{rand(10000)}\n"
    end

    stdout, stderr, status = Open3.pipeline(["echo", inp], ["./prog"])
    if true
        puts stdout
        puts stderr
        outs status
        # puts inp
        puts stderr
        `echo \"#{inp}\" > tmp.in`
        # puts 'lalala'
    end
end
