{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE InstanceSigs #-}

import Data.Monoid
-- data BinTree a b = Leaf a | Node b (BinTree a b) b (BinTree a b)

class (Monoid a, Monoid b) => Algebra a b where
    (-.-) :: a -> b -> b

instance Algebra (Product Integer) (Sum Integer) where
    (-.-) :: Product Integer -> Sum Integer -> Sum Integer
    a -.- b = Sum $ getProduct (a * (Product $ getSum b))

data SegTree a b i = Leaf a b (i, i) | Branch a b (i, i) (SegTree a i) (SegTree a i)

app_lazy :: Algebra a b => b -> SegTree a b i -> SegTree a b i
app_lazy k (Leaf a b i) = Leaf a (k `mappend` b) i 
app_lazy k (Branch a b i b1 b2) = Leaf a (k `mappend` b) i b1 b2

push :: Algebra a b => SegTree a b i -> SegTree a b i
push (Leaf a b i) = Leaf (a -.- b) mempty i 
push (Branch a b i b1 b2) = Branch (a -.- b) mempty i (app_lazy b b1) (app_lazy b b2)


