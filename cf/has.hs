itp :: [Int] -> [Int]
itp (a:b:xs) = (a + b) : (itn (b:xs))
itp _ = []

itn :: [Int] -> [Int]
itn (a:b:xs) = (a - b) : (itp (b:xs))
itn _ = []

allp :: [Int] -> Int
allp x
  | l == 1 = head x
  | even l = alln $ itp x
  | otherwise = allp $ itp x
  where
    l = length x

alln :: [Int] -> Int
alln x
  | l == 1 = head x
  | even l = allp $ itn x
  | otherwise = alln $ itn x
  where
    l = length x

r :: Bool -> Integer -> Integer -> Integer
r _ _ 0 = 1
r s n k
  | n == k = d s
  | otherwise = r s' (n - 1) k + d s' * r s' (n - 1) (k - 1)
  where
    s' :: Bool
    s' = not $ s `xor` (even n)
      where
        xor :: Bool -> Bool -> Bool
        xor True True = False
        xor a b = a || b
    d True = 1
    d False = -1

