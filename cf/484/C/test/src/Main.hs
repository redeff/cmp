import Data.Permute
import Data.Array.IArray

-- 5-permute
-- #         #         #
-- A B C D E F G H I J K L
-- A F K B G L C H D I E J
--
-- 0 1 2 3 4 5 6 7 8 9 A B
-- 0 5 A 1 6 B 2 7 3 8 4 9

weird_sorting :: Int -> Int -> [Int]
weird_sorting k d =
  let idx = do {
    i <- [0..d-1];
    takeWhile (< k) (map (\x -> x * d + i) [0, 1..]) } in
  idx

cycle1 :: [a] -> [a]
cycle1 (x:xs) = xs ++ [x]

shift_permute :: Int -> Int -> Int -> Permute 
shift_permute n k d = 
  let idx = weird_sorting k d in
  listPermute n $ cycle1 (idx ++ [k..n-1])
{-
shift_permute_inv :: Int -> Int -> Int -> Permute
shift_permute_inv n d k = inverse $ listPermute n $ shift_permutation n d k

perComp :: Permute -> Permute -> Permute
perComp a b = listPermute (size a) $ map (\x -> at a x) (Data.Permute.elems b)

perExp :: Int -> Permute -> Permute
perExp 0 per = permute (size per)
perExp 1 per = per
perExp 2 per = perComp per per
perExp n per
  | evenness == 0 = perExp 2 (perExp (n `div` 2) per)
  | evenness == 1 = perComp per (perExp (n - 1) per) 
  where evenness = n `mod` 2

{-
perExp' :: Int -> Permute -> Permute
perExp' p per = runST do
  let n = size per
  arr <- newArray (0, n-1) False :: ST s (STArray s Int Bool)
  final <- newArray (0, n-1) 0 :: ST s (STArray s Int Bool)
  fold () (map (\x -> do
    done <- readArray arr x
    if done
      then return
      else 

  ) [0..n-1])
-}
-}
perExp' :: Int -> Permute -> Permute
perExp' p per = listPermute n $ Data.Array.IArray.elems arr
  where 
    arr :: Array Int Int
    arr = array (0, n-1) idxPairs
    n :: Int
    n = size per
    idxPairs :: [(Int, Int)]
    idxPairs = map rotateCycles (cycles per) >>= id
    rotateCycles :: [Int] -> [(Int, Int)]
    rotateCycles xs = zip xs $ take (length xs) $ drop p $ cycle xs

main :: IO ()
main = do
  print (show (shift_permute 30 12 5))
  -- print $ show $ perExp 6 (shift_permute_inv 30 12 5)
  print $ show $ perExp' 0 (shift_permute 30 12 5)
  print $ show $ perExp' 1 (shift_permute 30 12 5)
  print $ show $ perExp' 2 (shift_permute 30 12 5)
  print $ show $ perExp' 6 (shift_permute 30 12 5)

