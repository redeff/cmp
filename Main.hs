primes = 2 : primes'
  where isPrime (p:ps) n = p*p > n || n `rem` p /= 0 && isPrime ps n
        primes' = 3 : filter (isPrime primes') [5, 7 ..]

fofize n = n - p
  where
    p = last $ takeWhile ((>=) n) primes

isFofo 0 = False
isFofo 1 = True
isFofo n = isFofo (fofize n)

fofos n = map isFofo [1..n]

quad n = filter (\((a, b), (c, d)) -> not (a || b || c || d)) $ zip (zip fs (True : True : True : fs)) $ zip (True : fs) (True : True : fs)
  where
    fs = fofos n
