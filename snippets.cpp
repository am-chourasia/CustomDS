//for finding the factor of x:
for(int i=1 ; i*i<=x ; i++){
    if(x%i == 0){
        v.push_back(i);
        if(i*i != x)	// eliminating double insertion for perfect squares
            v.push_back(x/i);
    }
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

//for x power n modulo
ll modpow(ll x, ll n, ll m) {
	if (n == 0) return 1%m;
	ll u = modpow(x,n/2,m);
	u = (u*u)%m;
	if (n%2 == 1) u = (u*x)%m;
	return u;
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