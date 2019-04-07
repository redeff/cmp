{-# LANGUAGE OverloadedStrings #-}
import qualified Data.Map.Strict as M
import Data.List
import Control.Monad

solveWith :: Integer -> [Integer] -> [Integer]
solveWith _ [] = []
solveWith a (x:xs) = r : solveWith r xs where r = div x a

solve :: [Integer] -> [Integer]
solve (a:b:xs) =
    if a /= b
    then let g = gcd a b in div a g : solveWith (div a g) (a:b:xs)
    else let x:y:xs = solve (b:xs) in y:x:y:xs

unwrap (Just a) = a

nubOrd :: (Eq a) => [a] -> [a]
nubOrd [] = []
nubOrd [a] = [a]
nubOrd (a:b:rest) = if a == b then nubOrd (b:rest) else a : nubOrd (b:rest)

problem :: [Integer] -> String
problem xs = map (\c -> unwrap $ M.lookup c mp) xs where
	mp = M.fromList $ zip (nubOrd $ sort xs) ['A'..'Z']

rec_read :: Integer -> Integer -> IO ()
rec_read 0 _ = return ()
rec_read n i = do
	getLine
	xs <- getLine
	let solved = problem $ solve $ map read $ words xs
	putStrLn ("Case #" ++ show i ++ ": " ++ solved)
	rec_read (n-1) (i+1)

main :: IO ()
main = do
	t <- getLine
	let test = read t
	rec_read test 1

