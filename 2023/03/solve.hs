import Data.Char

type Position = (Int, Int)

splitBy :: (a -> Bool) -> [a] -> [[a]]
splitBy f xs = case dropWhile f xs of
    [] -> []
    xs' -> w : splitBy f xs''
      where
        (w, xs'') = break f xs'

gridGet :: [[a]] -> (Int, Int) -> a
gridGet grid (x, y) = (grid !! y) !! x

neighbourPositions :: [[a]] -> Position -> [Position]
neighbourPositions grid (x, y) = filter isValid [(x + dx, y + dy) | dx <- [-1 .. 1], dy <- [-1 .. 1]]
  where
    isValid (x, y) = x >= 0 && y >= 0 && y < length grid && x < length (head grid)

gridNeighbours :: [[a]] -> Position -> [a]
gridNeighbours grid pos = map (gridGet grid) $ neighbourPositions grid pos

listIndexed :: [a] -> [(a, Int)]
listIndexed = zipWith (\i c -> (c, i)) [0 ..]

rowNumbers :: [Char] -> [(Int, [Int])]
rowNumbers row = map ((\(str, xs) -> (read str, xs)) . unzip) (splitBy (\(c, _) -> not $ isDigit c) $ listIndexed row)

gridNumbers :: [([Char], Int)] -> [(Int, [Position])]
gridNumbers [] = []
gridNumbers ((row, y) : rows) = map (\(n, xs) -> (n, [(x, y) | x <- xs])) (rowNumbers row) ++ gridNumbers rows

findAdjacent :: [[Char]] -> [Int]
findAdjacent grid = map fst $ filter isValid $ gridNumbers $ listIndexed grid
  where
    isValid (n, poss) = any (any isSymbol . gridNeighbours grid) poss
    isSymbol c = c /= '.' && not (isDigit c)

gearPositions :: [[Char]] -> [Position]
gearPositions grid = filter (\pos -> gridGet grid pos == '*') positions
  where
    positions = [(x, y) | x <- [0 .. length (head grid) - 1], y <- [0 .. length grid - 1]]

adjacentNumbers :: [[Char]] -> Position -> [Int]
adjacentNumbers grid pos = map fst $ filter isAdjacent $ gridNumbers $ listIndexed grid
  where
    isAdjacent (_, poss) = any (isNext pos) poss
    isNext (x, y) (x', y') = abs (x - x') <= 1 && abs (y - y') <= 1

-- validGears :: [[Char]] -> [[Int]]
validGears grid = filter (\x -> length x == 2) $ map (adjacentNumbers grid) $ gearPositions grid

main :: IO ()
main = do
    contents <- readFile "input"
    print . sum $ findAdjacent $ lines contents
    print . sum $ map product $ validGears $ lines contents
    return ()
