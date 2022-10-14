//for x power n modulo
ll modpow(ll x, ll n, ll m) {
    if (n == 0) return 1%m;
    ll u = modpow(x,n/2,m);
    u = (u*u)%m;
    if (n%2 == 1) u = (u*x)%m;
    return u;
}

//for finding the factor of x:
for(int i=1 ; i*i<=x ; i++){
    if(x%i == 0){
        v.push_back(i);
        if(i*i != x)	// eliminating double insertion for perfect squares
            v.push_back(x/i);
    }
}

// Graph:
    std::vector<std::vector<int>> graph(n, vector<int>());
    for(int i=0; i< size_as_required; i++){
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

// for finding nCr:
long long C(int n, int r) {
    if(r > n - r) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//for tokenising string
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

//for trimming trailing spaces from a string
size_t endpos = str.find_last_not_of(" \t");
size_t startpos = str.find_first_not_of(" \t");
if( std::string::npos != endpos )
{
    str = str.substr( 0, endpos+1 );
    str = str.substr( startpos );
}
else {
    str.erase(std::remove(std::begin(str), std::end(str), ' '), std::end(str));
}


// for removing adjacent duplicates from a string:
auto i = unique(s.begin(), s.end());
s.resize(i-s.begin());


//to check if a number is prime:
bool isPrime(ll n)
{
    ll i,root;
    if(n==2 || n==3)
		return true;
    if (n%2 == 0 || n%3 == 0)
        return false;
    root = (ll)sqrt(n);
    for (i=5; i<=root; i+=6){
        if (n%i == 0)
            return false;
        if ((n+2)%i == 0)
            return false;
    }
    return true;
}

// to check if a number if a perfect square
bool isPerfectSquare(long double x)
{
    if (x >= 0) {
        long long sr = sqrt(x);
        return (sr * sr == x);
    }
    return false;
}

//for faster log2 of integer type
int log2(int x) 
{ 
    int res = 0; 
    while (x >>= 1) 
        res++; 
    return res; 
} 

//minimum swaps to sort the array containing ONLY PERMUTATION OF NUMBERS 1 to n
int n, arr[maxx];
int visited[maxx];
int cycle = 0;

void dfs (intt v) {
    visited[v] = 1;
    if (visited[arr[v]]) cycle ++;
    else dfs (arr[v]);
}

for (int i = 1; i <= n; i++)
    if (!visited[i])
        dfs (i);
ans = n - cycle;

// OR for number of cycles in the minimum swap case:
for(int i = 0; i < n; i++)
{
    if(used[i] == 1) continue;
    int j = i;
    while(used[j] == 0)
    {
        used[j] = 1;
        j = q[j];
    }
    ans++;
}

// DSU
class DSU{
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n){
        parent = vector<int>(n,-1);
        rank = vector<int>(n,1);
    }
    int find(int i) {
        if (parent[i] == -1)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unify(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

// manacher's algorithm for longest pallindromic string in s -> O(n):
string longestPalindrome(string s) {
    int n = s.size();
    vector<int> odd(n);     // odd length pallindrome around i;
    vector<int> even(n);     // even length pallindrome around i;
    
    int k = 0, l=0, r = -1;
    for(int i=0; i<n; i++){
        k = (i>r) ? 1 : min(odd[l+(r-i)], (r-i)+1);
        // for odd length pallindrome, the i'th character itself is a pallindrome, so default               value of k is taken 1 and for even it's taken 0;
        while(i-k >=0 && i+k < n && s[i-k]==s[i+k])
            k++;
        odd[i] = k--;       // postorder for counting the i'th character itself
        if(i+k > r){
            l = i-k;
            r = i+k;
        }
    }
    k = 0, l = 0, r = -1;
    for(int i=0; i<n; i++){
        k = (i>r) ? 0 : min(even[l+(r-i)+1], (r-i)+1);
        while(i-k-1 >=0 && i+k < n && s[i-k-1]==s[i+k])
            k++;
        even[i] = k--;
        if(i+k > r){
            l = i-k-1;
            r = i+k;
        }
    }
    
    int meven = max_element(even.begin(), even.end()) - even.begin();
    int modd  = max_element(odd.begin(), odd.end()) - odd.begin();
    if(2*odd[modd]-1 > 2*even[meven]){
        return s.substr(modd-(odd[modd]-1), 2*odd[modd]-1);
    }
    return s.substr(meven-even[meven], 2*even[meven]);
}