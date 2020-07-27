This assignment emulates the PageRank algorithm that Google uses to rank its search results. With "walkers" as sitegoers, my program runs a certain # of simulations, weighting pages based on the amount of times they are visited. These pages are all part of a directed graph, which can be visualized in the example images. In this assignment, I had extensive practice with objects/classes, file I/O, and stringstreams. Running this program consists of passing in txt files that are formatted as follows:

1: Number of webpages in the file

2: pageid_0

3: <TAB> Page URL

4: <TAB> Page Rank

5: <TAB ids of hyperlinked webpages (outgoing links separated by spaces).


Instructions:

Compile: make

Run: ./pagerank <input text file (Ex. graph_4.txt)> <output text file (Ex. graph_4_out.txt)> <# of Walkers> <# of Simulations>
