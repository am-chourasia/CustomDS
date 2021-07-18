#include <iostream>
#include <limits.h>
using namespace std;

// What is Segment Tree:
// It is a tree data structure used for storing information about intervals, or segments of an array. It allows answering range queries over an array effectively, while still being flexible enough to allow modifying the array.

// choose the indexing that best suits the query type : zero based for zero based query and vice-versa
// for zero based indexing of segment tree: children: 2*i+1 and 2*i+2 and parent : (i-1)/2
// for zero based indexing of segment tree: children: 2*i and 2*i+1 and parent : i/2

// Range Minimum Query Tree:
class SegmentTree
{
	int *tree;
	const int indexSystem;	 // 0-based indexing or 1-based indexing
	const int baseArraySize; // size of the array to build the segTree upon
	const int treeStart;	 // start: the staring index of the segment in consideration
	const int treeEnd;		 // end:   the ending index of the segment in consideration
	// index: the current index of the tree in consideration
	void build(int *A, int index, int start, int end)
	{
		if (start > end)
			return;
		if (start == end)
		{
			// this base statement determines what would be present at the leaf nodes
			tree[index] = A[start];
			return;
		}

		int mid = (start + end) / 2;
		build(A, 2 * index + (indexSystem == 0), start, mid);
		build(A, 2 * index + 1 + (indexSystem == 0), mid + 1, end);
		int left = tree[2 * index + (indexSystem == 0)];
		int right = tree[2 * index + 1 + (indexSystem == 0)];

		// the below statement determines the property of the tree:
		// min-tree, max-tree, sum-tree, etc.
		tree[index] = min(left, right);
	}
	int query(int index, int start, int end, int queryStart, int queryEnd)
	{
		//no overlap
		if (queryStart > end || queryEnd < start)
			return INT_MAX;
		//total overlap:
		//  queryStart .........................queryEnd
		//	________________s............e______________
		if (start >= queryStart && end <= queryEnd)
			return tree[index];
		// partial overlap
		//  ___________queryStart ......................queryEnd_____________
		//	______s....................e_____________________________________ OR
		//  _________________________________s........................e______ OR
		// 	_______s................................................e________
		int mid = (start + end) / 2;
		int left = query(2 * index + (indexSystem == 0), start, mid, queryStart, queryEnd);
		int right = query(2 * index + 1 + (indexSystem == 0), mid + 1, end, queryStart, queryEnd);
		return min(left, right);
	}
	void updateValue(int index, int start, int end, int indexToChange, int value)
	{
		// no overlap
		if (indexToChange < start || indexToChange > end)
			return;
		// complete overlap (reached the leaf node that needs to be updated)
		if (start == end)
		{
			// the logic used for update
			tree[index] = tree[index] + value;
			return;
		}
		// partial overlap
		int mid = (start + end) / 2;
		updateValue(2 * index + (indexSystem == 0), start, mid, indexToChange, value);
		updateValue(2 * index + 1 + (indexSystem == 0), mid + 1, end, indexToChange, value);
		tree[index] = min(tree[2 * index + (indexSystem == 0)], tree[2 * index + 1 + (indexSystem == 0)]);
	}
	int updateRange(int index, int start, int end, int updateStart, int updateEnd, int value)
	{
		//no overlap
		if (updateStart > end || updateEnd < start)
			return tree[index];
		// reached a leaf node:
		if (start == end)
		{
			// the logic for update
			tree[index] = tree[index] + value;
			return tree[index];
		}
		// partial overlap
		int mid = (start + end) / 2;
		int left = updateRange(2 * index + (indexSystem == 0), start, mid, updateStart, updateEnd, value);
		int right = updateRange(2 * index + 1 + (indexSystem == 0), mid + 1, end, updateStart, updateEnd, value);
		tree[index] = min(left, right);
		return tree[index];
	}

public:
	SegmentTree(const int sizeOfArray, const int indexSystem = 0) : indexSystem(indexSystem), baseArraySize(sizeOfArray), treeStart(indexSystem), treeEnd(sizeOfArray - (indexSystem == 0))
	{
		tree = new int[4 * sizeOfArray + 1];
	}
	void print()
	{
		for (int i = treeStart; i <= 4 * treeEnd + 1; i++)
			cout << tree[i] << " ";
		cout << endl;
	}
	void buildUpon(int *A)
	{
		build(A, indexSystem, treeStart, treeEnd);
	}
	int query(int queryStart, int queryEnd)
	{
		return query(indexSystem, treeStart, treeEnd, queryStart, queryEnd);
	}
	void updateValue(int indexToChange, int valueToBeAdded)
	{
		updateValue(indexSystem, treeStart, treeEnd, indexToChange, valueToBeAdded);
	}
	void updateRange(int updateRangeStart, int updateRangeEnd, int valueToBeAdded)
	{
		updateRange(indexSystem, treeStart, treeEnd, updateRangeStart, updateRangeEnd, valueToBeAdded);
	}
	~SegmentTree()
	{
		delete[] tree;
	}
};

int main()
{
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	// Sample Input:
	// 1
	// 8 4
	// 10 20 9 21 4 2 1 8
	// 1 5  2 4  3 5  4 4

	int t;
	cin >> t;
	int n, q;

	while (t--)
	{
		cin >> n >> q;
		int *A = new int[n];
		for (int i = 0; i < n; i++)
			cin >> A[i];

		SegmentTree segt(n, 0);
		segt.buildUpon(A);
		segt.print();
		// segt.updateValue(3, 20);

		while (q--)
		{
			int queryStart, queryEnd;
			cin >> queryStart >> queryEnd;
			cout << segt.query(queryStart, queryEnd) << endl;
		}

		// segt.updateRange(2, 4, 2);
		// segt.print();
		delete[] A;
	}
}