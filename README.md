# TMLN1

## Compile

* mkdir build
* cd build
* cmake ..
* make

The project is now ready

## Launch 

* ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin (create the binary dictionry, might take some time)
* ./TextMiningApp /path/to/dict.bin (start the command mode)
    * approx n word (with n a number, will give all the word at the n distance of "word")
    * Can be use with pipe
        * echo "approx 0 test" | ./TextMiningApp /path/to/dict.bin ()
        * echo "approx 1 test" | ./TextMiningApp /path/to/dict.bin
        * echo "approx 2 test" | ./TextMiningApp /path/to/dict.bin
        * echo "approx 0 test\napprox 1 test\napprox 2 test\napprox 3 test\napprox 4 test" | ./TextMiningApp /path/to/dict.bin
    * Can be use with file
        * cat test.txt | ./TextMiningApp /path/to/dict.bin

## Documentation
Documentation with doxygen is available :

* doxygen DoxygenConfig 
* firefox (or chromium) doc/html/index.html

## Warning

The program didn't respect the RAM limitation. To use the program their are a dict.bin in the directory input/
at the root. It's the serialize dictonary of the words in the file words.txt (in the input/ directory too)

## Design choice (Question 1)

For this project, I build a Trie to compute all my dictionary. I use that structure because is easy to implement and fast to use.
Then I serialize this trie in a binary file. For this I transform each node in binary with a particular patern
* First, the number of the children map, so I can know the number of child
* Second, the character of the trie's node
* Third, the frequency if is a word of the dictionary, if not, then the frequency equals zero
* Forth, the offset of the end of the children map, so we can jump at the reading
This 4 parts in repeted for each node, even for the root node that is used as sentry.
For the reading part because I know exacly the size in the file, I can navigate easly in the file to get data.

## Tests (Question 2)

Not so many test have been performed. My main focus was the exact output as the ref. So I create some test to compare the output of
my program and the ref. To do that I just put the output in 2 separate files and compare them. For the RAM limitation of 512Mo, I use
"htop" to see the memory used by the process. So I know that the creation of the dictionary use more than 512Mo, that why the dictionary
is at the root and named "dict.bin". To know if the program is efficient, I run it in a loop during 10 second then divide the number
of loop performed. So I could know the number of querry by second.

## Correction by distance ? (Question 3)

The 4 operations used in the D-L distance cover 80% for the human misspellings. The 20% is not covered. A good correction need a contexte to
perform. With the distance with a dictionary there no context, so the correction is less good. Another problem apears when they are more than 1
error in the word.

## Data Structure (Question 4)

As said before, I use a trie in this project. Each nodes has the frequency for the word, and if the node isn't the end of a word, the frequency
is equal to 0. The nodes has a map of their children, the key is the char to access at the node, and the value, is the node. It's a tree base
structure, and it's realy easy to use and create.


## Autonomous distance (Question 5)

The distance can be predict in function of the length of the word with the minimun 1 unit of distance. It could be, for exemple, the
quarter of the word's size. If we choose the same size for all the words, on small words the correction can give a completly new word,
and for big word, a not useful correction. Or can be smarter and use machine learning to know the good distance.

## Upgrade (Question 6)

To give an upgrade to the program, I can change the trie for a patricia trie. This trie is a bit faster because if a node as only one child
the two nodes merge to create a single node. I can optimize my code to not exceed the 512Mo of RAM. Moreover the binary dictionary is very big
(3 times bigger than the original file), so I can compress the size of the data, or use a smaller implementation, or both. The search alogrith
is a recursive function, so I can transform it to be a iterative function.

## State of the art (Question 7)

To be as good as the state of the art, I need a better data structure, a better serialization, a better reader. I need to implement automatically
the search in a text editor. 
