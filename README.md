# Clustering of Biological Sequences

Two parameters are required: number of clusters and fasta file.								

Command example 1:								

	my_executable <number_of_clusters> <fasta_file>								

	my_executable 3 my_file.fasta								

Optional parameters:								

	[max_iterations] -> maximum of iterations, default is 100.								

	[comparison_method] -> method to compare strings, default is LCS.								

		Methods available:								

		LD -> levenshtein distance (edit distance)								

		NW -> Needleman-Wunsch (optimal global alignment)								

		SW -> Smith-Waterman (optimal local alignment)								

		WS -> White-Similarity or Dice's Coefficient (similarity ranking)								

		LCS -> Longest Common Subsequence								

		HAMMING -> Hamming distance (only for strings of equal length)								

Command example 2:								

	my_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method]								

	my_executable 3 my_file.fasta 50 NW								

Observation: KMeans++ is used for default.								

You do not want to use the KMeans++? Try this for example:								

	my_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus]								

	my_executable 3 my_file_fasta 50 NW 0								

	my_executable 3 my_file_fasta 50 NW 1								

The number 0 indicates that you not will use KMeans++.								
The number 1 indicates that KMeans++ will be used.								

You want to use the hybrid clustering? Try this:								

	my_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus] [uses_hybrid]							   	

	my_executable 3 my_file.fasta 50 NW 0 1							   	


Contact: mcastrosouza@live.com :: https://twitter.com/mcastrosouza
