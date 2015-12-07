'''
	Implementation of the ODIN method

	ODIN = Outlier Detection using Indegree Number
	ODIN is a kNN outlier method
	ODIN uses kNN graph

	In ODIN, the outliers are defined using k-nearest neighbour (kNN) graph

	References:
		kNN graph: https://en.wikipedia.org/wiki/Nearest_neighbor_graph
		ODIN method: http://cs.joensuu.fi/~villeh/35400978.pdf

	Why detection of the outliers?
		1) eliminate outliers
		2) cluster the data using any method

	Author: Marcos Castro
'''

import random, heapq
from scipy.spatial import distance
from collections import defaultdict

list_adjacency = defaultdict(list)

'''
	dataset: set of datapoints
	dists: euclidean distances
	N: number of datapoints
	K: K nearest neighbors
	T: indegree threshold (detection outlier)
'''
def build_knn_graph(dataset, dists, N, K, T = 0.9):
	
	K_dists = []

	for index_point in range(N):

		dists_neighbors = []

		# build the list of distances of the neighboors of the index_point
		for neighbor in range(N):
			if(index_point != neighbor):
				if(index_point > neighbor):
					dists_neighbors.append(dists[(neighbor, index_point)])
				else:
					dists_neighbors.append(dists[(index_point, neighbor)])

		# get K smallest distance from index_point to other objects from dataset
		K_smallest_distance = heapq.nsmallest(K, dists_neighbors)[-1]

		# who are the K nearest neighbors?
		for neighbor in range(N):
			if(index_point != neighbor):
				if(index_point > neighbor):
					if(dists[(neighbor, index_point)] <= K_smallest_distance):
						list_adjacency[index_point].append(neighbor)
				else:
					if(dists[(index_point, neighbor)] <= K_smallest_distance):
						list_adjacency[index_point].append(neighbor)

	in_degree = {} # in degrees of objects

	for obj in range(N):
		in_degree[obj] = 0
		# search for "obj" in the lists of adjacency of the others objects
		for other_obj in range(N):
			if(obj != other_obj):
				# checks if obj is in list adjacency of "other_obj"
				for item in list_adjacency[other_obj]:
					if(obj == item):
						# adds in degree of "obj"
						in_degree[obj] += 1

	count_outliers = 0 # counter outliers

	for i in in_degree:

		# calculates outlyingess of "i"
		outly = 1.0 / (in_degree[i] + 1)

		# checks if "i" is a outlier comparing "outly" with threshold "T"
		if(outly > T):
			count_outliers += 1
			print('datapoint %d is outlier, outly: %.2f' % (i, outly))

	print('\nTotal outliers: %d' % count_outliers)



def show_dataset(dataset):
	print('\n'.join(str(d) for d in dataset))


if __name__ == "__main__":
	
	N = 1500 # number of the data points
	K = 11 # number of nearest neighbors

	K = int(0.01 * N) # K is 1% of N

	# generates N datapoints, each datapoint contains N elements
	# the numbers of each datapoint are between 1 e N
	dataset = [[int(N * random.random() + 1) for i in range(N)] for i in range(N)]

	dists = {} # euclidean distances
	
	# calculates the euclidean distances between the pairs
	for i in range(N):
		for j in range(i + 1, N):
			dists[(i, j)] = distance.euclidean(dataset[i], dataset[j])

	# build kNNG (kNN graph) for detection outliers
	build_knn_graph(dataset, dists, N, K, 0.89)

	print('K: %d' % K)