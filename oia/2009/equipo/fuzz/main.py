from string import ascii_lowercase
from subprocess import Popen, PIPE, STDOUT
import random

for _ in range(1000):
    c = random.randint(2, 10)
    p = random.randint(1, 10)

    inp = str(p) + '\n' + str(c) + '\n'
    for _ in range(c):
        for _ in range(p):
            inp += random.choice(ascii_lowercase)
        inp += '\n'

    stdout_a = Popen(['./r', inp], stdout=PIPE, stdin=PIPE, stderr=STDOUT).communicate(input=bytes(inp))[0]
    stdout_b = Popen(['./w', inp], stdout=PIPE, stdin=PIPE, stderr=STDOUT).communicate(input=bytes(inp))[0]

    if stdout_a != stdout_b:
        print(inp)
        print('r\n' + stdout_a)
        print('w\n' + stdout_b)
