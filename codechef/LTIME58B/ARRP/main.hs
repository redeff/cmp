import Data.Array
import Data.List

partial_sum_array :: [Int] -> Array Int Bool
partial_sum_array xs = res
    where
        res = listArray (0, s) (take s (repeat False)) // zip partial_sums (repeat True)

        s :: Int
        s = sum xs

        partial_sums :: [Int]
        partial_sums = foldl (\ns -> \n -> (head ns + n) : ns) [0] xs  

test_case :: [Int] -> String
test_case xs = res
    where
        n :: Int
        n = length xs

        s :: Int
        s = sum xs

        res :: String
        res = intercalate "" (map (\t -> if t then "1" else "0") work_list)

        work_list :: [Bool]
        work_list = map works [1..n]

        works :: Int -> Bool
        works k = ((s `mod` k) == 0) && (all is_partial_sum $ map (\x -> x * (s `div` k)) [0..k])

        {--
        partial_sums :: [Int]
        partial_sums = foldl (\ns -> \n -> (head ns + n) : ns) [0] xs  

        partial_sums_array :: Array Int Bool
        partial_sums_array = listArray (0, s) (take s (repeat False)) // zip partial_sums (repeat True) 
        --}
        partial_sums_array = partial_sum_array xs

        is_partial_sum :: Int -> Bool
        is_partial_sum k = partial_sums_array ! k

-- main = putStrLn $ test_case [1, 1, 1, 1] ++ test_case [1, 4, 2, 3, 5]
main = do
    t <- read >>= getLine
