type Two a = Two a a
two a = Two a a

type Inner a = Inner a Int (Two (Treap a)) deriving Eq
type Treap a = Maybe (Inner a) deriving Eq

single :: (Ord a) => a -> Treap a
single a = Just $ Inner a 1 (two Nothing)

merge :: Two Treap -> Treap
merge (Two Nothing a) = a
merge (Two a Nothing) = a
merge (Two (Just a) (Just b)) = 
