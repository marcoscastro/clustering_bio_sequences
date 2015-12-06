#ifndef _DISTANCE_STRINGS_H_
#define _DISTANCE_STRINGS_H_

#include <iostream>
#include <vector>
#include <set>
#include <string>

/*
	Levenshtein distance: string metric for
	measuring the difference between two sequences.
	Levenshtein is a measure of dissimilarity.
	Levenshtein distance may also be referred to as edit distance.

	This implementation uses bottom-up dynamic programming.

	Reference:
		http://www.levenshtein.net/

	Return:
		score of dissimilarity
*/
double levenshteinDistance(std::string & s1, std::string & s2);

/*
	Needleman-Wunsch is a algorithm for global alignment pairwise.
	Needleman-Wunsch is a measure of similarity.
	Uses dynamic programming.

	References:
		https://en.wikipedia.org/wiki/Needleman–Wunsch_algorithm
		http://pt.slideshare.net/mcastrosouza/algoritmo-needlemanwunsch (in portuguese)

	Parameters:
		match
		mistmatch
		gap: score to give an insertion or deletion mutation

	Return:
		score of the alignment
*/
double nwDistance(std::string & s1, std::string & s2, double match = 1,
				  double mismatch = 0, double gap = 0);

/*
	Smith-Waterman is a algorithm for local alignment pairwise.
	Smith-Waterman is a measure of similarity.
	Uses dynamic programming.

	Parameters:
		match
		mismatch
		gap

	Return:
	   score of the alignment
*/
double swDistance(std::string & s1, std::string & s2, double match = 1,
				  double mismatch = 0, double gap = 0);

/*
	White Similarity (similarity ranking)
	reference: http://www.catalysoft.com/articles/StrikeAMatch.html
	is the same Dice's Coefficient

	word_size smaller increases sensitivity
	this word_size can be also be increased to increase
	the search speed and limit the number of matches
*/

double wsDistance(std::string & s1, std::string & s2, int word_size = 4);

/*
	LCS - longest common subsequence

	Consists in finding the longest subsequence common to two sequences
	The LCS distance between strings s1 (of length n) and s2 (of length m)
	is n + m - 2|LCS(s1,s2)|

	Uses dynamic programming approach.

	Complexity: O(m.n) - space and cost
*/
double lcsDistance(std::string & s1, std::string & s2);

/*
	Hamming distance - used for strings of equal length.
	The hamming distance is the number of positions at
	which the corresponding symbols are different.
	It measures the minimum number of substitutions required
	to change one string into the other, or the minimum number
	of errors that could have transformed one string into the other.
*/
double hammingDistance(std::string & s1, std::string & s2);

#endif
