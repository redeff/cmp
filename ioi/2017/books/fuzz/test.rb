require 'timeout'

tim = 0
1000000.times do 
    tim += 1
    n = 5000
    a = Array (0..n - 1)
    a = a.shuffle
    
    s = rand n
    # s = 0

    inp = "#{n} #{s} \n"
    a.each do |x|
        inp += "#{x} "
    end

    inp += "\n"

    #  

    # puts "started"

    # begin
    #     status = Timeout::timeout(1000) {
    #         t1 = Time.now
    #         ans_prog = `echo "#{inp}" | ./prog`
    #         t2 = Time.now

    #         puts t2 - t1
    #     }
    # rescue
    #     puts "#{n} #{s}"
    #     a.each do |x|
    #         print "#{x} "
    #     end
    #     puts ""
    # end
    `echo "#{inp}" > lulu.in`
    ans_prog = `echo "#{inp}" | ./prog`
    ans_old = `echo "#{inp}" | ./old`

    if ans_prog != ans_old
        puts inp
    end

    # if ans_prog != ans_old
    #     puts "#{n} #{s}"
    #     a.each do |x|
    #         print "#{x} "
    #     end
    #     puts ""
    #     puts "#{ans_prog} #{ans_old}"
    # end

    if tim % 100 == 0
        puts "completed #{tim}"
    end
end


