#include <bits/stdc++.h>

int
main()
{
    int         N;
    std::string ships;
    std::cin >> N;
    std::cin.ignore();

    while (N--) {
        getline(std::cin, ships);
        std::vector<std::stack<char>> stacks{};

        std::for_each(
          std::begin(ships), std::end(ships), [&stacks](const auto& c) {
              if (auto l_stack =
                    std::find_if(std::begin(stacks),
                                 std::end(stacks),
                                 [&](auto& st) { return c <= st.top(); });
                  std::end(stacks) != l_stack) {
                  l_stack->push(c);
              } else {
                  stacks.emplace_back(std::stack<char>({ c }));
              }
          });
        std::cout << std::size(stacks) << "\n";
    }
}