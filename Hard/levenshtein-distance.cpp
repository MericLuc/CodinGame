#include <bits/stdc++.h>

int levenshteinDistance(const std::string& s1, const std::string& s2) {
  std::vector< std::vector<int> > m( s2.size() + 1, 
                                     std::vector<int>(s1.size() + 1, 0) );  
    
    for ( int i = 1; i <= s1.size(); i++ ) { m[0][i] = i; }
    for ( int j = 1; j <= s2.size(); j++ ) { m[j][0] = j; }
    
    for     ( int i = 1; i <= s1.size(); i++ )
        for ( int j = 1; j <= s2.size(); j++ ) { 
            int subCost = (s1[i-1] == s2[j-1]) ? 0 : 1; 
            m[j][i] = std::min( subCost + m[j-1][i-1],
                                std::min( 1 + m[j-1][i], 1 + m[j][i-1] ) );
        }
  return m[s2.size()][s1.size()];
}

int main() {
    std::string w1,w2;
    getline(std::cin, w1);
    getline(std::cin, w2);
    std::cout << levenshteinDistance(w1, w2 ) << std::endl;
}