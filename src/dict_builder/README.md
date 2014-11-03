**Introduction**  
This is a tool that builds a "dictionary of common strings". More precisely, it picks some set of substrings from given text files and then writes them one by one to a dictionary. So, the dictionary is just some huge string.  
After that, one can make a "delta" file, that encodes our file in respect of the fact that decoder of our file knows the dictionary. That is why, the dictionary should be similar to all given files (in some sense).  
  
**How does it work?**  
Our goal is to find some set of substrings that maximize the  
  
  ![equation](http://latex.codecogs.com/png.latex?%5Csum_%7Bs%20%5Cin%20Dict%7D%20%5Cfrac%7BDocsOccursIn%28s%29%20%5Ccdot%20%28len%28s%29%20-%203%29%7D%7Blen%28s%29%7D)  
    
under some constraints, namely  
1. If we took a substring, we are not allowed to take a subtring of this substring  
2. ![equation](http://latex.codecogs.com/png.latex?DocsOccursIn%28s%29%20%3E%201%2C%20len%28s%29%20%3E%20threshold).  
3. Sum over taken substrings' lengths is not greater than some constant.  
  
To find such strings we use data structure named 'suffix automaton' (more detailed explanation here http://www.cs.nyu.edu/~mohri/pub/nfac.pdf, in russian: http://e-maxx.ru/algo/suffix_automata).  
Briefly saying, suffix automaton is the smallest automaton accepting all suffixes of a string. Also, it is a directed acyclic graph with characters on the edges. It's proved that such automaton contains O(len(s)) nodes.
  
Let's build the suffix automaton for the string ![equation](http://latex.codecogs.com/png.latex?s_1%20%5C%23%20s_2%20%5C%23%20...%20%5C%23%20s_k) - concatenated documents separated by '#' (or some another character does not occur in the documents). Every string (without '#') allowed by automaton is a substring of some document (the opposite fact is also true). Now we want to compute a 'DocsOccursIn' for each node in our automaton. For that do the following: build another automaton for each document (say, the i-th) and traverse common automaton (the first) and current automaton (automaton for i-th doc, the second) 'simultaneously'. More detailed explanation: our function (say, `dfs`) takes two parameters - `node1` and `node2` from the first and the second automaton respectively. ALso, one needs to increace the 'node1.DocsOccursIn' counter by 1. After that one has to call `dfs` from all nodes `to1` and `to2` corresponding to the same character written on the edges from `node1` ans `node2` respectively. In other words, the following must be satisfied: ![equation](http://latex.codecogs.com/png.latex?%28node_1%2C%20to_1%29%20%5Cin%20E%2C%20%28node2%2C%20to_2%29%20%5Cin%20E%2C%20MarkOnEdge%28node_1%2C%20to_1%29%20%3D%20MarkOnEdge%28node_2%2C%20to_2%29).  
  
So we can calculate `DocsOccursIn` for each node. We are going to solve the very last problem - do not take a substring of taken substring. It can be solved by simple dynamic programming on graph: we just calculate `MaxRatingThroughSubstrings` and `MaxRatingThroughUpbstrings` for each node. For instance, the first value for some node can be evaluated via all incoming edges and all incoming suffix links (if you even briefly read above articles, you would understand everything).  
  
In the last part of solution we just sort all survived substring by their rating and pick them until we reach the limit on the dictionary size.  
  
Time complexity is `O(sum_length_documents)` with relatively small constant.
