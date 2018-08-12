#!/usr/bin/env ruby

1000.times do
    n = rand(10)
    File.open '0.in', 'w' do |file|
        file.write "#{n}\n"
        n.times do
            a = rand(10)
            b = rand(10)
            file.write "#{a} #{b}\n"
        end
    end

    `./main < 0.in > main.out`
    `./quad < 0.in > quad.out`

    main_out = IO.read 'main.out'
    quad_out = IO.read 'quad.out'
    if main_out != quad_out then raise end
end
