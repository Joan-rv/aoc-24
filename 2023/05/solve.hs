data MapEntry = MapEntry Int Int Int deriving (Show)
type Map = [MapEntry]
type Range = (Int, Int)

splitWhen :: (a -> Bool) -> [a] -> [[a]]
splitWhen f = foldr merge [[]]
  where
    merge x (ac : acc) = if f x then [] : ac : acc else (x : ac) : acc

getSeeds :: String -> [Int]
getSeeds = map read . tail . words

getSeedsRanges :: String -> [Range]
getSeedsRanges = toRanges . map read . tail . words
  where
    toRanges [] = []
    toRanges (x : l : xs) = (x, l) : toRanges xs

getMapEntries :: [String] -> Map
getMapEntries = map ((\[x, y, z] -> MapEntry x y z) . map read . words) . tail

convertMap :: Int -> Map -> Int
convertMap x m = getValue entries
  where
    entries = filter (\(MapEntry _ s l) -> x >= s && x < s + l) m
    getValue [] = x
    getValue [MapEntry d s l] = d + x - s

convertMapRange :: Range -> Map -> [Range]
convertMapRange (rs, rl) m = map mapRange entries
  where
    entries = filter (\(MapEntry _ s l) -> rs + rl >= s && rs < s + l) m
    mapRange (MapEntry d s l) = (start, end - start + 1)
      where
        start = d + max 0 (rs - s)
        end = d + l - max 0 (s + l - rs - rl)

main :: IO ()
main = do
    input <- splitWhen (== "") . lines <$> readFile "input.test"
    -- let seeds = getSeeds $ (head . head) input
    let seeds = getSeedsRanges $ (head . head) input
    let maps = map getMapEntries $ tail input
    -- print . minimum $ foldl (\s m -> map (`convertMap` m) s) seeds maps
    print $ foldl (\s m -> concatMap (`convertMapRange` m) s) seeds maps
    return ()
