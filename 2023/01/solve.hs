import Data.Char
import Data.Text(pack, unpack, replace)

wordDigit :: String -> [Char]
wordDigit [] = []
wordDigit ('1':xs) = '1':wordDigit xs
wordDigit ('2':xs) = '2':wordDigit xs
wordDigit ('3':xs) = '3':wordDigit xs
wordDigit ('4':xs) = '4':wordDigit xs
wordDigit ('5':xs) = '5':wordDigit xs
wordDigit ('6':xs) = '6':wordDigit xs
wordDigit ('7':xs) = '7':wordDigit xs
wordDigit ('8':xs) = '8':wordDigit xs
wordDigit ('9':xs) = '9':wordDigit xs
wordDigit ('0':xs) = '0':wordDigit xs
wordDigit ('o':'n':'e':xs) = '1':wordDigit ('n':'e':xs)
wordDigit ('t':'w':'o':xs) = '2':wordDigit ('w':'o':xs)
wordDigit ('t':'h':'r':'e':'e':xs) = '3':wordDigit ('h':'r':'e':'e':xs)
wordDigit ('f':'o':'u':'r':xs) = '4':wordDigit ('o':'u':'r':xs)
wordDigit ('f':'i':'v':'e':xs) = '5':wordDigit ('i':'v':'e':xs)
wordDigit ('s':'i':'x':xs) = '6':wordDigit ('i':'x':xs)
wordDigit ('s':'e':'v':'e':'n':xs) = '7':wordDigit ('e':'v':'e':'n':xs)
wordDigit ('e':'i':'g':'h':'t':xs) = '8':wordDigit ('i':'g':'h':'t':xs)
wordDigit ('n':'i':'n':'e':xs) = '9':wordDigit ('i':'n':'e':xs)
wordDigit ('z':'e':'o':'o':xs) = '9':wordDigit ('e':'r':'o':xs)
wordDigit (x:xs) = wordDigit xs

getCal :: [Char] -> Int
getCal line = read [head nums,last nums]
    where nums = wordDigit line

main :: IO ()
main = do
    contents <- readFile "input"
    print . sum . map getCal $ lines contents
