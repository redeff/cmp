#!/usr/bin/env python3
import random
from subprocess import Popen, PIPE
import time

# outp = subprocess.check_output("./prog", stdin=)
for k in range(1, 100):
    s = '' 
    n = random.randint(2, 100000)
    s = s + str(n) + "\n"

    for i in range(n - 1):
        # s = s + str(random.randint(0, i)) + " "
        s = s + str(i) + " "

    s = s + "\n"

    for i in range(n):
        s = s + str(random.randint(0, 1)) + " "
        # s = s + str(1) + " "

    s = s + "\n"

    # print(s)

    p = Popen(['./prog'], stdin=PIPE, stdout=PIPE, stderr=PIPE)

    start_time = time.time()
    outp, err = p.communicate(s.encode())
    elapsed = time.time() - start_time

    print(outp.decode())
    print(elapsed)

    if elapsed > 2.5:
        with open('4.in', 'a') as out:
            out.write(s)
            break
