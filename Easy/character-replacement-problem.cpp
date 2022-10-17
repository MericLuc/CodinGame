#include <bits/stdc++.h>

template < typename T >
class Graph {
private:
    struct Node { 
        Node(T val) noexcept : _val{ val } {}
        const T  _val;
        Node*    _next{ nullptr };
    };

public:
    typedef enum { OK, IGNORED, ERROR } STATUS;

    Graph() noexcept = default;
    ~Graph() noexcept { 
        std::for_each( std::begin(_repl), std::end(_repl), [](auto& it){
            if ( nullptr != it.second ) {
                delete(it.second);
                it.second = nullptr;
            }
        });
        _repl.clear();
    }

    [[maybe_unused]] STATUS insert(const T& from, const T& to) noexcept {        
        if ( from == to ) return IGNORED;
        
        if ( auto it{ _repl.find(to)  }; std::end(_repl) == it ) { _repl[to]   = new Node(to);   }
        if ( auto it{ _repl.find(from)}; std::end(_repl) == it ) { _repl[from] = new Node(from); }

        Node* nFrom{ _repl[from] }, *nTo{ _repl[to] };

        if ( nullptr != nFrom->_next ) return ERROR;

        nFrom->_next = nTo;
        return _integrityCheck( nFrom );
    }

    T get(const T& from) noexcept { 
        if ( std::end(_repl) == _repl.find(from) )
            return from;

        auto ret{ _repl[from] };
        while ( nullptr != ret->_next )
            ret = ret->_next;
        return ret->_val; 
    }

private:
    STATUS _integrityCheck(Node* n) noexcept {
        Node* start{ n }, *cur{ n };
        if ( nullptr == start ) return ERROR;

        while ( nullptr != cur->_next ) 
            if ( cur = cur->_next; cur == start )
                return ERROR;
        return OK;
    }
private:
    std::map<T, Node*> _repl;
};

int main()
{
    std::string       replacements, cur;
    getline(std::cin, replacements);

    std::vector<std::string> multiline{ ++std::istream_iterator<std::string>(std::cin),
                                          std::istream_iterator<std::string>() };

    Graph<char> graph;
    std::stringstream ss(replacements);
    while (getline(ss, cur, ' ')) {
        if ( (2 != std::size(cur)) || (Graph<char>::STATUS::ERROR == graph.insert(cur[0], cur[1]))) {
            std::cout << "ERROR\n";
            return EXIT_FAILURE;
        }
    }

    std::for_each( std::begin(multiline), std::end(multiline), [&graph](auto& line){
        std::for_each( std::begin(line), std::end(line), [&graph](auto& c){
            c = graph.get(c);
        });
        std::cout << line << '\n';
    });
}