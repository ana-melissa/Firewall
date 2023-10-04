Ana Melissa

Prof. Long

12/3/2021

CSE 13S Fall 2021


# Assignment 7: The Great Firewall of Santa Cruz:
## Bloom Filters, Linked Lists, Binary Trees, and Hash Tables

This word filtering program performs as a firewall. This program filters out and reports bad words parsed from stdin. This program will read in a user's input and detect and report any bad speak words and oldspeak words with their newspeak translation. This program not only uses a Bloom filter, but also a hash table to ensure that the user's input is goodspeak, and to ensure that the badspeak is actually badspeak. 

# Build
	- banhammer.c
	- bf.c        bf.h
	- bst.c       bst.h
	- bv.c        bv.h
	- ht.c        ht.h
	- node.c      node.h
	- parser.c    parser.h
	- speck.c     speck.h
	- salts.h
	- messages.h
	- Makefile

Run these commands to build the program:
---
$make clean
---
$make format
---
$make all
---

# Running Program: banhammer

To run the program, run the command below:

		./banhammer [-hs] [-t size] [-f size]

		-h         Program usage and help.
		-s         Print program statistics.
		-t size    Specify hash table size (default: 2^16).
		-f size    Specify Bloom filter size (default: 2^20).


# Output

If the user wanted the statistics (-s) the ouput will contain:
		
		The average binary search tree size.
		The average binary search tree height.
		The average branches traversed.
		The hash table load.
		The Bloom filter load.


If the user entered oldspeak words and bad words, the program will output this message, the specific bad words, and the newspeak translations for the oldspeak words:

		Dear beloved citizen of the GPRSC ,

		We have some good news , and we have some bad news.
		The good news is that there is bad news. The bad news is that you will
		be sent to joycamp and subjected to a week -long destitute existence.
		This is the penalty for using degenerate words , as well as using
		oldspeak in place of newspeak. We hope you can correct your behavior.
		Your transgressions , followed by the words you must think on:
		
		bad words
		oldspeak word/words -> newspeak word/words


If the user entered bad words with no newspeak translation, the program will output this message and the specific bad words the user used:

		Dear beloved citizen of the GPRSC ,

		You have been caught using degenerate words that may cause
		distress among the moral and upstanding citizens of the GPSRC.
		As such , you will be sent to joycamp. It is there where you will
		sit and reflect on the consequences of your choice in language.
	
		Your transgressions:
		
		bad words


If the user only entered oldspeak words, the program will output this message and the newspeak translation for each oldspeak word:

		Dear beloved citizen of the GPRSC ,
		
		We recognize your efforts in conforming to the language standards
		of the GPSRC. Alas , you have been caught uttering questionable words
		and thinking unpleasant thoughts. You must correct your wrongspeak
		and badthink at once. Failure to do so will result in your deliverance
		to joycamp.

		Words that you must think on:

		oldspeak word/words -> newspeak word/words












