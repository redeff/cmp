{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE InstanceSigs #-}

import Data.Monoid
import Data.Semigroup

class (Monoid a, Monoid b) => Algebra a b where
    (-.-) :: a -> b -> a

instance Algebra (Sum Integer) (Product Integer) where
    a -.- b = Sum $ (getSum a) * (getProduct b)


data Tree rec = Empty | Branch rec rec deriving Show
data Interval a = Interval a a deriving Show
data SegTree a b i = Tree (Node a b i) (Tree (SegTree a b i)) deriving Show
data Node a b i = Node a b (Interval i) deriving Show
data CompInt = Disjoint | Contained | Partial deriving Show

disjoint :: Ord a => Interval a -> Interval a -> CompInt
disjoint (Interval i j) (Interval i' j') =
    if i <= i' && j' <= j
        then Contained
        else if j < i' || j' < i
            then Disjoint
            else Partial

push :: Algebra a b => SegTree a b i -> SegTree a b i
push (Tree (Node a b i) rest) = Tree (Node (a -.- b) mempty i) $ case rest of
    Empty -> Empty
    Branch t d -> Branch (p t) (p d)
    where
        p (Tree (Node x y z) rest) = Tree (Node x (b <> y) z) (rest)

tra :: (Ord i, Semigroup k, Algebra a b) =>
    (SegTree a b i -> k) -> (SegTree a b i -> k) -> Interval i -> SegTree a b i -> k
tra f g i stree = case disjoint i j of
    Disjoint -> g stree'
    Contained -> f stree'
    Partial -> case rest of
        Empty -> g stree'
        Branch b1 b2 -> (tra f g i b1) <> (tra f g i b2)
    where stree' @ (Tree (Node a b j) rest) = push stree


query :: (Algebra a b, Ord i) => Interval i -> SegTree a b i -> a
query = tra (\(Tree (Node a _ _) _ ) -> a) (\_ -> mempty)


instance (Algebra a b, Ord i) => Semigroup (SegTree a b i) where
     t1 <> t2 = Tree (Node (a1 <> a2) mempty (Interval lo hi)) (Branch stree1 stree2)
         where
            stree1@(Tree (Node a1 _ (Interval lo _)) _) = push t1
            stree2@(Tree (Node a2 _ (Interval _ hi)) _) = push t2

update :: (Algebra a b, Ord i) => b -> Interval i -> SegTree a b i -> SegTree a b i
update b' = tra (\(Tree (Node a b i) rest) -> (Tree (Node a (b' <> b) i) rest)) id


log_join :: Semigroup k => [k] -> k
log_join [k] = k
log_join [k, l] = k <> l
log_join xs@(k:ks) = (log_join $ take (len `div` 2) xs) <> (log_join $ drop (len `div` 2) xs)
    where len = length xs

from_list :: (Algebra a b, Ord i) => [(a, i)] -> SegTree a b i
from_list = log_join . map convert
    where convert (a, i) = Tree (Node a mempty (Interval i i)) Empty


normal :: [Integer] -> SegTree (Sum Integer) (Product Integer) Integer
normal = from_list . (flip zip) [0,1..] . map Sum

