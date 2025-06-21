mapN :: Int -> (a -> a) -> [a] -> [a]
mapN 0 _ xs = xs
mapN _ _ [] = []
mapN n f (x : xs) = f x : mapN (n - 1) f xs

parseLine :: String -> ([Int], [Int])
parseLine line = convert $ break (== '|') $ tail $ dropWhile (/= ':') line
  where
    convert (left, right) = (toList left, toList $ tail right)
    toList = map read . words

countWinning :: ([Int], [Int]) -> Int
countWinning (_, []) = 0
countWinning (wins, x : rest) = if x `elem` wins then 1 + countWinning (wins, rest) else countWinning (wins, rest)

getPoints :: Int -> Int
getPoints 0 = 0
getPoints 1 = 1
getPoints n = 2 * getPoints (n - 1)

duplicateCardsFqs' :: [Int] -> [Int] -> [Int]
duplicateCardsFqs' [] _ = []
duplicateCardsFqs' (s : ss) (fq : fqs) = fq : duplicateCardsFqs' ss newFqs
  where
    newFqs = mapN s (+ fq) fqs

duplicateCardsFqs :: [Int] -> [Int]
duplicateCardsFqs scores = duplicateCardsFqs' scores $ replicate (length scores) 1

main :: IO ()
main = do
    input <- lines <$> readFile "input"
    print . sum . duplicateCardsFqs $ map (countWinning . parseLine) input
    pure ()
