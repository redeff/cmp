
ex :: Integer -> Integer -> Integer -> Integer
ex n e p = if e == 0 then 1 else (t * res * res) `mod` p where
	t = if e `mod` 2 == 1 then n else 1
	res = ex n (e `div` 2) p

inv :: Integer -> Integer -> Integer
inv n p = ex n (p-2) p

block :: Integer
block = 3
facts = map (\x -> product [block * x + 1 .. block * (x + 1)]) [0..]

fact :: Integer -> Integer -> Integer
fact n p = (pr * rest) `mod` p where
	d = n `div` block
	pr = product (map (`mod` p) $ take (fromInteger $ n `div` block) facts)
	rest = product $ map (`mod` p) [d * block + 1 .. n]

f n p = (w * inv (fact (p - n - 1) p) p) `mod` p where
	w = if (p - n) `mod` 2 == 0 then 1 else p-1

dotimes :: Integer -> IO ()
dotimes 0 = do
	return ()
dotimes n = do
	s <- getLine
	let g = (map read $ words s) :: [Integer]
	putStrLn $ show $ f (g !! 0) (g !! 1)
	dotimes (n-1)

main :: IO ()
main = do
	s <- getLine
	let n = read s :: Integer
	dotimes n
	-- putStrLn s
