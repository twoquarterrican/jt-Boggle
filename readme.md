My version of the game Boggle.  

Assignment from Stanford's CS106X C++ course, available at <a href="http://www.stanford.edu/class/cs106x/">www.stanford.edu/class/cs106x</a>.  The starter files given there do not work very well on my machine, so I wrote this in Qt without the starter files.  Qt is a set of libraries for C++.  It does a lot of memory management for you.

The search in the board for words is recursive.  The main point of this assignment was to practice recursion, but for me it also turned into an introduction to Qt.

In addition, I had to recreate the lexicon class.  This is a data structure for storing a list of words.  The structure is a tree whose vertices are labeled with a letter and an array of pointers to other vertices.  A lexicon is a tree of such vertices, and a word is in the lexicon if and only if there is a path from the root outward in the tree spelling out the given word.  This makes lookup very efficient.
