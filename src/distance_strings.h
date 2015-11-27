#ifndef _DISTANCE_STRINGS_H_
#define _DISTANCE_STRINGS_H_

// This header implement differents string similarity and distance measures

#include <algorithm>
#include <vector>
#include <math.h>
#include <set>
#include "common.h"

/*
	Levenshtein distance: string metric for
	measuring the difference between two sequences
	Levenshtein is a measure of dissimilarity

	This implementation uses bottom-up dynamic programming.

	Reference:
		http://www.levenshtein.net/

	Return:
		score of dissimilarity
*/
int levenshteinDistance(std::string & s1, std::string & s2)
{
	int size_s1 = s1.size(), size_s2 = s2.size();
	std::vector<std::vector<unsigned int> > mat(size_s1 + 1,
			std::vector<unsigned int>(size_s2 + 1));

	mat[0][0] = 0;

	for(int i = 1; i <= size_s1; i++)
		mat[i][0] = i;
	for(int i = 1; i <= size_s2; i++)
		mat[0][i] = i;

	for(int i = 1; i <= size_s1; i++)
		for(int j = 1; j <= size_s2; j++)
			mat[i][j] = std::min(std::min(mat[i - 1][j] + 1, mat[i][j - 1] + 1),
								 mat[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));

	return mat[size_s1][size_s2];
}

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
				  double mismatch = 0, double gap = 0)
{
	int size_s1 = s1.size(), size_s2 = s2.size();
	std::vector<std::vector<double> > mat(size_s1 + 1,
										  std::vector<double>(size_s2 + 1));

	mat[0][0] = 0;

	for(int i = 1; i <= size_s1; i++)
		mat[i][0] = mat[i - 1][0] + gap;
	for(int i = 1; i <= size_s2; i++)
		mat[0][i] = mat[0][i - 1] + gap;

	for(int i = 1; i <= size_s1; i++)
	{
		for(int j = 1; j <= size_s2; j++)
			mat[i][j] = std::max(std::max(mat[i - 1][j] + gap, mat[i][j - 1] + gap),
								 mat[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? match : mismatch));
	}

	return mat[size_s1][size_s2];
}

/*
	White Similarity (similarity ranking)
	reference: http://www.catalysoft.com/articles/StrikeAMatch.html
	is the same Dice's Coefficient

	word_size smaller increases sensitivity
	this word_size can be also be increased to increase
	the search speed and limit the number of matches
*/

double wsDistance(std::string & s1, std::string & s2, int word_size = 7)
{
	std::set<std::string> s1_bigrams;
	std::set<std::string> s2_bigrams;

	int size_s1 = s1.size(), size_s2 = s2.size();

	// base case
	if(size_s1 == 0 || size_s2 == 0)
		return 0;
	else if(s1 == s2)
		return 100;

	std::string sub_str;

	// extract characters of length "word_size" from s1
	for(int i = 0; i < (size_s1 - 1); i++)
	{
		sub_str = s1.substr(i, word_size);
		if(sub_str.size() == (unsigned)word_size)
			s1_bigrams.insert(sub_str);
		else
			break;
	}

	// extract characters of length "word_size" from s2
	for(int i = 0; i < (size_s2 - 1); i++)
	{
		sub_str = s2.substr(i, word_size);
		if(sub_str.size() == (unsigned)word_size)
			s2_bigrams.insert(sub_str);
		else
			break;
	}

	int intersection = 0;

	// find the intersection between the two sets

	std::set<std::string>::iterator it;

	for(it = s2_bigrams.begin(); it != s2_bigrams.end(); it++)
		intersection += s1_bigrams.count((*it));

	int total = s1_bigrams.size() + s2_bigrams.size();

	return (((intersection * 2.0) / total) * 100);
}

/*
	LCS - longest common subsequence

	Consists in finding the longest subsequence common to two sequences
	The LCS distance between strings s1 (of length n) and s2 (of length m)
	is n + m - 2|LCS(s1,s2)|

	Uses dynamic programming approach.

	Complexity: O(m.n) - space and cost
*/
double lcsDistance(std::string & s1, std::string & s2)
{
	int len_s1 = s1.size(), len_s2 = s2.size();
	std::vector<std::vector<int> > table(len_s1 + 1, std::vector<int>(len_s2 + 1));

	for(int i = 1; i <= len_s1; i++)
	{
		for(int j = 1; j <= len_s2; j++)
		{
			if(s1[i - 1] == s2[j - 1])
				table[i][j] = table[i - 1][j - 1] + 1;
			else
				table[i][j] = std::max(table[i][j - 1], table[i - 1][j]);
		}
	}

	return (len_s1 + len_s2 - 2.0 * (table[len_s1][len_s2]));
}

#endif
