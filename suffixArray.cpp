// Suffix array construction in O(L log^2 L) time.  Routine for
// computing the length of the longest common prefix of any two
// suffixes in O(log L) time.

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

class SuffixArray {
  const int L;
  string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;
  vector<int> RankArray;
  vector<int> SA;
  vector<int> LCP;
public:
  SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
    for (int i = 0; i < L; i++) P[0][i] = L==1 ? i : int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++) 
        M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++) 
        P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
    } 
    RankArray = P.back();
  }

  vector<int> getRankArray() { return RankArray; }
  vector<int> getSuffixArray() {
      if( !SA.empty())
        return SA;
      SA.resize(L, 0);
      for(int i=0; i<RankArray.size(); i++){
          SA[RankArray[i]] = i;
      }
      return SA;
  }
  vector<int> getLCP()
  {
    if(!LCP.empty())
      return LCP;
    int n=s.size(),k=0;
    LCP.resize(L, 0);
    for(int i=0; i<n; i++, k?k--:0)
    {
        if(RankArray[i]==n-1) {k=0; continue;}
        int j=SA[RankArray[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        LCP[RankArray[i]]=k;
    }
    return LCP;
  } 

  // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if (i == j) return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
      if (P[k][i] == P[k][j]) {
        i += 1 << k;
        j += 1 << k;
        len += 1 << k;
      }
    }
    return len;
  }
};

int main() {

  std::cout<<"Enter the string: ";
  string s;
  getline(cin>>ws, s);
  SuffixArray suffix(s);
  vector<int> sa = suffix.getSuffixArray();
  vector<int> lcp = suffix.getLCP();
  cout<<"SA : ";
  for (int i = 0; i < sa.size(); i++) 
    cout << sa[i] << " ";
  cout << endl;
  cout<<"LCP : ";
  for (int i = 0; i < lcp.size(); i++) 
      cout << lcp[i] << " ";
    cout << endl;
}