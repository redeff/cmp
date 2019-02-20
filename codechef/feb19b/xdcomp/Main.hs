import Data.Bits
import Data.Int
import Data.Graph
import Data.Tree
import Data.Array
import Control.Monad
import Data.Semigroup

ka :: Int64
ka = 10^9 + 7

mo :: Int64 -> Int64
mo x = x `mod` (10^9 + 7)

acc :: (Semigroup a) => Tree a -> Tree a
acc (Node a xs) = Node (foldl (<>) a [x | Node x _ <- xs']) xs' where
	xs' = map acc $ xs

rev :: (Semigroup a) => Tree a -> Tree a
rev (Node a xs) = Node (foldl (<>) a [x | Node x _ <- xs]) xs' where
	xs' = map rev $ xs

filt :: (a -> Bool) -> Tree a -> Forest a
filt p (Node n xs) = if p n then [Node n xs'] else xs' where
	xs' = xs >>= filt p

data Xor = Xor Int64
get :: Xor -> Int64
get (Xor a) = a

lift :: (Int64 -> Int64 -> Int64) -> Xor -> Xor -> Xor
lift f a b = Xor $ f (get a) (get b)

instance Semigroup Xor where
	(<>) = lift xor

instance Monoid Xor where
	mempty = Xor 0

process_zero :: Int -> [Int64] -> [(Int, Int)] -> Tree Int64
process_zero n weis ass = fmap (arr !) tree where
	arr = listArray bounds weis
	tree = case dff $ buildG bounds ass of
		[x] -> x
		_ -> error "Not a Tree"
	bounds = (0, n - 1)

process_one :: Int64 -> Tree Int64 -> Forest Bool
process_one i = (map $ fmap (==0))
	. (map $ fmap get)
	. (map $ rev)
	. filt (\(Xor x) -> (x == 0) || (x == i))
	. acc
	. fmap Xor

data Ways = Ways Int64 Int64
instance Semigroup Ways where
	(Ways a1 a2) <> (Ways b1 b2) = Ways (mo c1) (mo c2) where
		c1 = (mo $ a1 * b1) + (mo $ a1 * b2) + (mo $ a2 * b1)
		c2 = (mo $ a2 * b1) + (mo $ a2 * b2) + (mo $ a1 * b1)

make :: Bool -> Ways
make True = Ways 0 1
make False = Ways 1 0

process_two :: Tree Bool -> Int64
process_two t = x where
	Node (Ways x _) _ = acc $ fmap make t

process :: Int -> Int64 -> [Int64] -> [(Int, Int)] -> Int64
process n x weis ass = process_two tree where
	[tree] = process_one x all
	all = process_zero n weis ass

line_as :: (Read a) => IO [a]
line_as = do
	line <- getLine
	return $ map read $ words line


main :: IO ()
main = do
	[n', x] <- line_as :: IO [Int64]
	let n = fromIntegral n'
	weis <- line_as :: IO [Int64]

	ass' <- forM (take (n-1) $ repeat ())  (\_ -> do
		[u, v] <- line_as
		return [(u-1, v-1), (v-1, u-1)]) :: IO [[(Int, Int)]]
	let ass = join ass'
	let res = process n x weis ass
	putStrLn $ show res
