{-# LANGUAGE DeriveFunctor #-}
import Data.Set
import Control.Monad.State

data Tree a rec = Tree a [rec] deriving Functor
newtype Fix f = Fx (f (Fix f))

unFix :: Fix f -> f (Fix f)
unFix (Fx x) = x

cata :: (Functor f) => (f a -> a) -> Fix f -> a
cata alg = alg . fmap (cata alg) . unFix

ana :: (Functor f) => (a -> f a) -> a -> Fix f
ana alg = Fx . fmap (ana alg) . alg

p1 :: (Num a) => Fix (Tree a) -> Tree a (Fix (Tree a))
p1 (Fx (Tree a rec)) = Tree a' rest where
	a' = a
	child (Tree k r) = Tree (k + a) r
	rest = fmap (Fx . child . unFix) rec

type Par = (Int, Int)

p2 :: Tree Par (Fix (Tree (Int, Set Par))) -> Fix (Tree (Int, Set Par))
p2 (Tree p rec) = 

{-
process_1 :: (Num b) => Tree (a, b) -> Tree (a, b)
process_1 t = p 0 t where
	p z (Node (a, b) as) = Node (a, n) $ map (p n) as where n = b + z

process_2 :: (Num a) => Tree (a, a) -> Tree (a, Set a)


partials :: (b -> a -> b) -> (b -> Tree a -> Tree b)
partials f z (Tree a as) = Tree n (map (partials f n) as) where n = f z a

dp :: ([Tree b] -> a -> b) -> (Tree a -> Tree b)
dp f (Tree a as) = Tree (f as' a) as' where as' = map (dp f) as

p1 :: (Num b) => Tree (a, b) -> Tree (a, b)
p1 = partials (\(_, b) -> \(c, d) -> (c, b + d)) 0

p2 :: (Num a) => Tree (a, a) -> Tree a
p2 = partials (\_ -> \(a, b) -> a + b) 0

tree_rec f p (Tree a as) = Tree a (map

tree_rec f g h p t@(Tree a as) = Tree a' as' where
	p' = f t
	as' = map (tree_rec f g h p') as
	a' = g 
-}
