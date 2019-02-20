require 'open3'
10000.times do
  n = rand(100) + 1
  inp = "#{n}\n"
  n.times do
    inp += "1\n"
    min = rand(10) - 50;
    max = rand(60 - min) + min
    inp += "#{min} #{max}\n"
  end

  a, aerr, astat = Open3.capture3("echo \"#{inp}\" | ./a")
  #if ! $?.success? then
  #  puts "A failed"
  #  puts inp
  #end
  b, berr, bstat = Open3.capture3("echo \"#{inp}\" | ./b")
  #if ! $?.success? then
  #  puts "B failed"
  #  puts inp
  #end

  if a != b then
    puts "Puta"
    puts inp
    puts "=========="
    puts a
    puts "=========="
    puts aerr
    puts "=========="
    puts b
    puts "=========="
    puts berr
  end
end
