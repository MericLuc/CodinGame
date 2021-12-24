#pragma GCC optimize("-O3,inline,omit-frame-pointer,unroll-loops")

#include <bits/stdc++.h>

bool is_in_group(const std::string &s1, const std::string &s2) {
  int x=0;
  std::vector<int> f1(26),f2(26);
  for(const auto& c : s1) f1[c - 97]++;
  for(const auto& c : s2) f2[c - 97]++;
  for(int i=0; i<26; i++) x += std::min(f1[i],f2[i]);
  return x < 3;
}

int main() {
    int N, ret{0}; std::cin >> N; std::cin.ignore();

    std::vector<std::string> data(N);
    for ( auto& word : data ) {
        getline(std::cin, word);
        std::transform(std::begin(word), 
                       std::end(word), 
                       std::begin(word), 
                       [](const auto& c) { return tolower(c); });
    }

    std::vector<std::vector<int>> lst(N);
    std::set<std::pair<int, int>> matches;

    for ( int i = 0; i < N; ++i )
        for ( int j = i + 1; j < N; ++j )
            if ( is_in_group(data.at(i), data.at(j)) ) {
                lst[i].push_back(j); 
                matches.insert({ i, j });
                lst[j].push_back(i); 
                matches.insert({ j, i });
            }

    std::for_each(std::begin(lst), 
                  std::end(lst), 
                  [n = 0](auto& g) mutable { g.push_back(n++); });

    std::vector<int> bag;
    std::function<void(std::vector<int>&)> merge;

    const auto select = [&](auto& g) {
        bag.push_back(g.back());
        g.pop_back();
        merge(g);
        bag.pop_back();
    };

    merge = [&](const auto& g) {
        std::vector<int> gn(g.size());

        gn.erase(std::copy_if(std::begin(g), 
                              std::end(g), 
                              std::begin(gn), [&](auto n) { 
                                  return matches.count({ bag.back(), n }); 
                                }), 
                            end(gn));

        if (    (gn.size() == 0)
             || (bag.size() + gn.size() <= ret) // optim
           ) { ret = std::max<int>(ret, bag.size()); return; }

        while ( gn.size() ) select(gn);
    };

    for ( auto g : lst ) select(g);

    std::cout << ret << "\n";
}
