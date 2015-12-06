'''
	Implementation of the ODIN method

	ODIN = Outlier Detection using Indegree Number
	ODIN is a kNN outlier method
	ODIN uses kNN graph

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

def get_K_lesser_items(K, items):
	return heapq.nsmallest(K, items)

def build_knn_graph(dataset, dists, N, K):
	
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

		# get K smallest distances from index_point to other objects from dataset
		K_smallest_distances = get_K_lesser_items(K, dists_neighbors)

		# who are K nearest neighbors?
		for neighbor in range(N):
			if(index_point != neighbor):
				if(index_point > neighbor):
					if(dists[(neighbor, index_point)] in K_smallest_distances):
						list_adjacency[index_point].append(neighbor)
				else:
					if(dists[(index_point, neighbor)] in K_smallest_distances):
						list_adjacency[index_point].append(neighbor)

	# in degrees of objects
	in_degree = {}

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

	T = 0.05 # threshold

	for i in in_degree:
		# calculates the outlyingess of "i"
		outlyingess = 1.0 / (in_degree[i] + 1)
		# checks if "i" is outlier
		if(outlyingess <= T):
			print('%d is outlier, in degree: %d' % (i, in_degree[i]))



def show_dataset(dataset):
	print('\n'.join(str(d) for d in dataset))


if __name__ == "__main__":
	
	N = 500 # number of the data points
	K = 3 # number of neighbors

	# generates N datapoints, each datapoint contains N elements
	# the numbers of each datapoint are between 1 e N
	dataset = [[int(N * random.random() + 1) for i in range(N)] for i in range(N)]

	dists = {}
	
	# calculates the euclidean distances between the pairs
	for i in range(N):
		for j in range(i + 1, N):
			dists[(i, j)] = distance.euclidean(dataset[i], dataset[j])

	build_knn_graph(dataset, dists, N, K)