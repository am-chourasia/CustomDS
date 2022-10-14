class DSU
{
	vector<int> parent;
	int noOfComponents;
public:
	DSU(int n){
		parent.resize(n, -1);
		noOfComponents = n;
	}
	// performing union of two nodes a and b
	void merge(int a, int b)
	{
		int parentA = getParent(a);
		int parentB = getParent(b);
		if(abs(parentA) > abs(parentB)){ 
		// parent of b should be a
			parent[parentA] += parent[parentB];
			parent[parentB] = parentA;
			noOfComponents--;
		} 
		else{
		// parent of a should be b
			parent[parentB] += parent[parentA];
			parent[parentA] = parentB;
			noOfComponents--;
		}
	}
	int getParent(int e){
		while(parent[e] > 0){
			e = parent[e];
		}
		return e;
	}
	int getNoOfComponents(){
		return noOfComponents;
	}
};

class DSU
{
	int connected;
	vector<int> par, sz;
public:
	DSU(int n) 
	{
		par = sz = vector<int> (n + 1, 0);
		for(int i = 1; i <= n; i++)
			par[i] = i, sz[i] = 1;
		connected = n;
	}

	int getPar(int u)
	{
		while(u != par[u])
		{
			par[u] = par[par[u]];
			u = par[u];
		}
		return u;
	}

	int getSize(int u)
	{
		return sz[getPar(u)];
	}

	void unite(int u, int v)
	{
		int par1 = getPar(u), par2 = getPar(v);

		if(par1 == par2)
			return;

		connected--;

		if(sz[par1] > sz[par2])
			swap(par1, par2);

		sz[par2] += sz[par1];
		sz[par1] = 0;
		par[par1] = par[par2];
	}
};