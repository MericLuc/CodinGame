#include <bits/stdc++.h>

struct Node {
    std::set<Node*> neighbours{};
    Node() noexcept = default;
};

struct Graph { 
    std::map<std::string, Node*> nodes{};

    ~Graph() noexcept { 
        for ( auto [_, node] : nodes )
            if ( nullptr != node ) 
                delete(node);
    }

    [[maybe_unused]] Node* insert(const std::string& actorName) noexcept {
        if ( std::end(nodes) == nodes.find(actorName) )
            nodes[actorName] = new Node();
            
        return nodes.at(actorName);
    }

    void process(std::string inputStr) noexcept {

        size_t pos{ inputStr.find_first_of(':') };
        if ( std::string::npos != pos )        
            inputStr = inputStr.substr(pos + 1);

        std::istringstream iss(inputStr);
        std::string        tok;

        std::set<Node*> curActors{};
        while (std::getline(iss, tok, ',')) 
            curActors.insert(this->insert(tok.substr(1)));

        for ( auto& curactor : curActors ) 
            for ( const auto& coactor : curActors ) 
                if ( coactor != curactor )
                    curactor->neighbours.insert(coactor);
    }

    Node* getByName(const std::string& actorName) const noexcept {
        return (std::end(nodes) == nodes.find(actorName) ) ? nullptr : nodes.at(actorName);
    }
};

int main() {
    std::string actorName, movieCast;
    int         n;
    Graph       graph;

    getline(std::cin, actorName);
    std::cin >> n; std::cin.ignore();

    while( n-- && getline(std::cin, movieCast) )
        graph.process(movieCast);

    Node*                     cur    { graph.getByName(actorName) };
    Node*                     target { graph.getByName("Kevin Bacon") };
    std::deque<Node*>         queue  { cur };
    std::map<Node*, size_t>   mem    { {cur, 1} };

    if ( (nullptr == cur) || (nullptr == target) ) {
        std::cerr << "Unable to find requested actors!\n";
        return EXIT_FAILURE;
    }

    if ( cur == target ) {
        std::cout << 0 << std::endl;
        return EXIT_SUCCESS;
    }

    while ( !std::empty(queue) ) {
        cur = queue.front();
        queue.pop_front();

        if ( cur->neighbours.count(target) ) {
            std::cout << mem[cur] << std::endl;
            return EXIT_SUCCESS;
        }
        
        for ( const auto& neigh : cur->neighbours ) {
            if ( std::end(mem) != mem.find(neigh) )
                continue;
            
            mem[neigh] = mem[cur] + 1;
            queue.push_back(neigh);
        }    
    }

    std::cerr << "Unable to find a path!\n";
    return EXIT_FAILURE;
}