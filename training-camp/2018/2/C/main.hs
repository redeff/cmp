import Data.Maybe

data Queue a = Queue [a] [a] deriving Show

queuePush :: a -> Queue a -> Queue a
queuePush t (Queue xs ys) = (Queue (t:xs) ys) 

queuePop :: Queue a -> Maybe (a, Queue a)
queuePop (Queue [] []) = Nothing
queuePop (Queue xs (y:ys)) = Just (y, Queue xs ys)
queuePop (Queue xs []) = queuePop (Queue [] $ reverse xs)

queueFromList :: [a] -> Queue a
queueFromList xs = Queue [] xs

queueEmpty (Queue [] []) = True
queueEmpty _ = False


data Tree a = Tree a (Queue (Tree a)) deriving Show
data MergeList a = MergeList a (Queue (Tree (Maybe a))) deriving Show

maybeTreeMerge :: Tree a -> Tree a -> Tree a
maybeTreeMerge (Tree x xs) t = Tree x $ queuePush t xs

treeMerge :: MergeList a -> Tree (Maybe a) -> MergeList a
treeMerge (MergeList x xs) t = MergeList x $ queuePush t xs

mergeListMerge :: MergeList a -> MergeList a -> MergeList a
mergeListMerge m (MergeList a q) = treeMerge m $ Tree (Just a) q

mergeListPop :: MergeList a -> (a, Maybe (MergeList a))
mergeListPop (MergeList x xs) = (x, rearrange (Tree Nothing xs))
    where
        rearrange :: Tree (Maybe a) -> Maybe (MergeList a)
        rearrange (Tree (Just x) xs) = Just (MergeList x xs)
        rearrange (Tree Nothing xs) = do
            (left, p) <- queuePop xs
            if queueEmpty p
            then rearrange left
            else
                let right = Tree Nothing p in
                rearrange $ maybeTreeMerge left right


mergeListFromList :: [a] -> MergeList a
mergeListFromList [x] = MergeList x (queueFromList [])
mergeListFromList (x:xs) = MergeList x $ queueFromList $ [Tree (Just a) rec]
    where
        MergeList a rec = mergeListFromList xs

data Ds a = Ds a (MergeList a)
fromList xs = Ds (last xs) (mergeListFromList xs)
pop (Ds a b) = (a', fmap (Ds a) b')
    where (a', b') = mergeListPop b
top (Ds a b) = a
merge (Ds a b) (Ds a' b') = Ds a' (mergeListMerge b b')


group :: (a -> a -> Bool) -> [a] -> [[a]]
group _ [] = []
group _ [x] = [[x]]
group f (x:xs) =
    if f x (head $ head xs')
    then (x : head xs') : tail xs'
    else [x] : xs'
    where
        xs' = group f xs

solve :: [Int] -> Int
solve xs = iter ascending_parts
    where
        ascending_parts = map fromList (group (<) xs)
        iter :: Ord a => [Ds a] -> Int
        iter [_] = 0 
        iter (x:xs) = 1 + (iter
            $ map (foldl1 merge)
            $ group (\a b -> top a < (fst . pop) b)
            $ catMaybes
            $ Just x : (map (snd . pop) xs))

main = do
    getLine
    line <- getLine
    k <- pure $ fmap read $ words line
    print $ solve k 
