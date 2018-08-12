#!/usr/bin/env ruby
require 'prime'

Prime.each(100) do |p|
    for n in 1..(2*p) do
        IO.write('0.in', "#{p} #{n}\n")
        `./main < 0.in > main.out`
        `./cubic < 0.in > cubic.out`
        if IO.read('main.out') != IO.read('cubic.out') then raise end
    end
end
