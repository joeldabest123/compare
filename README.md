Joel Anderson
JEA211

Mapping shit out:

Layers:
Top layer:

Tomorrow Need to:

Design Notes:
I went with a "Big Gulp" approach for reading files. Instead of sipping the file byte-by-byte (which would suck ass), I used stat to get the exact size, malloc one giant buffer, and read the whole thing at once. This made the tokenizing process way easier because I could just move pointers around in memory and whatnot.
(The name the "Big Gulp" was too awesome not to center a large portion of my code around.)

For data structures, I used a Master Array of Linked Lists:

The Master Array: Since I didn't know how many files I'd find prior, I initialized a small array of List pointers and used a lengthenArray function with realloc to double the capacity every time it filled up. Big gulped up some heap memory and all that.

The Linked Lists: Every file gets its own list. I implemented a an alphabetical method so the words are already in order before the math even starts. This was a massive pain to write but it made the JSD comparison logic much more manageable. (It's pretty now, but you should have seen it before I made it snazzy)

Tokenizing: My tokenizer filters out everything except letters, numbers, and hyphens. It also converts everything to lowercase so "Fortnite" and "fortnite" are treated as the same word.

The Math (JSD):
I followed the Jensen-Shannon Distance formula using log2.
I used a Two-Pass approach in the jsd function.
Pass 1: Walks through File 1. If it finds a match in File 2, it does the KLD math for both. If not, it applies the "missing word" penalty to File 1.

Pass 2: Walks through File 2 to catch any words that weren't in File 1 and applies their specific penalty.
Finally, I took the square root of the mean KLD to get the actual distance.

Testing Plan (Tbh not much, I pushed this pretty damn close to the deadline :/):
Basic Tests: Created small .txt files with a random assortment of words to verify the frequency math (WFD) adds up to 1.0.
Identity Test: Compared a file against a copy of itself. The JSD result was 0.00000, proving the similarity logic is accurate.
Directory Traversal: Ran the program on nested folders with a mix of .txt and other files (like .c or .h) to make sure the recursion correctly skips hidden files (starting with .) and only tokenizes the right suffixes.
Memory Management: Ran the code through multiple files to ensure clearList was actually freeing the words, the nodes, the list containers, and the master array tray.

I learned a lot and all that jazz, but I never want to do this again :)
