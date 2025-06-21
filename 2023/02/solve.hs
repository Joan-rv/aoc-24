splitAtFirst :: (Eq a) => a -> [a] -> ([a], [a])
splitAtFirst x = fmap (drop 1) . break (x ==)

tuplify2 :: [String] -> (Int, String)
tuplify2 [x, y] = (read x, y)

mapTuple3 :: (a -> b) -> (a, a, a) -> (b, b, b)
mapTuple3 f (a1, a2, a3) = (f a1, f a2, f a3)

tupleAdd3 :: (Int, Int, Int) -> (Int, Int, Int) -> (Int, Int, Int)
tupleAdd3 (a1, a2, a3) (b1, b2, b3) = (a1 + b1, a2 + b2, a3 + b3)

tupleMul3 :: (Num a) => (a, a, a) -> a
tupleMul3 (a1, a2, a3) = a1 * a2 * a3

wordsWhen :: (Char -> Bool) -> String -> [String]
wordsWhen p s = case dropWhile p s of
    "" -> []
    s' -> w : wordsWhen p s''
      where
        (w, s'') = break p s'

getRound round = map (tuplify2 . words) $ wordsWhen (== ',') round

getGames :: String -> (Int, [[(Int, String)]])
getGames line = (read $ words id !! 1, rounds)
  where
    (id, rest) = splitAtFirst ':' line
    rounds = map getRound $ wordsWhen (== ';') rest

isValidShow :: (Int, String) -> Bool
isValidShow (n, "red") = n <= 12
isValidShow (n, "green") = n <= 13
isValidShow (n, "blue") = n <= 14

isValidRound :: [(Int, String)] -> Bool
isValidRound = all isValidShow

isValidGame :: (Int, [[(Int, String)]]) -> Bool
isValidGame (id, rounds) = all isValidRound rounds

minCubesRound :: [(Int, String)] -> (Int, Int, Int)
minCubesRound [] = (0, 0, 0)
minCubesRound ((n, "red") : xs) = tupleAdd3 (n, 0, 0) $ minCubesRound xs
minCubesRound ((n, "green") : xs) = tupleAdd3 (0, n, 0) $ minCubesRound xs
minCubesRound ((n, "blue") : xs) = tupleAdd3 (0, 0, n) $ minCubesRound xs

minCubesGame :: (Int, [[(Int, String)]]) -> (Int, Int, Int)
minCubesGame (id, rounds) = mapTuple3 maximum $ unzip3 $ map minCubesRound rounds

main :: IO ()
main = do
    contents <- readFile "input"
    let games = map getGames $ lines contents
    print $ sum $ map (tupleMul3 . minCubesGame) games
    return ()
