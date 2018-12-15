data RecTree : Nat -> (Nat -> Type) -> Type where
  Empty : RecTree Z rec
  Branch : rec n -> rec n -> RecTree (S n) rec

{-
data Dummy : Nat -> Type -> Type -> Type where
  Build : (n : Nat) -> Dummy n
  -}

data Tree : Nat -> Type -> Type -> Type where
  Tree' : a -> RecTree n (\t => (b, (Tree t a b))) -> Tree n a b

infixr 7 *$
interface (Monoid add, Monoid mul) => Algebra add mul where
  (*$) : b -> a -> a

-- test : Algebra a b => a -> a -> b -> b -> (b, b)
-- test a a' b b' = ((a <+> a') *$ (b <+> b'), ((a <+> a') *$ b) <+> ((a <+> a') *$ b'))

test : Algebra add mul => add -> add -> mul -> add
test a a' b = b *$ (a <+> a')


Algebra Int Int


{-
data Node : (Type -> Type -> Type -> Type) -> Type -> Type -> Type -> Type where
  Node rec a b n = Node
data Node rec a b n = Node' b (rec n a b)
data Tree n a b = Tree' a (
  RecTree (
    Node Tree a b))
    -}
{-
data Tree a b = Tree' a (RecTree (b, (Tree a b)))

infixr 7 -.-

interface (Monoid op, Monoid val) => Algebra op val where
  --   Rules of algebra:
  --   a -.- (b <> c) == (a -.- b) <> (a -.- c)
  (-.-) : op -> val -> val 
  -}

main : IO ()
main = putStrLn "Hello World"
