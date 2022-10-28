#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops","unsafe-math-optimizations","no-trapping-math")

#include <bits/stdc++.h>

namespace env {

namespace {
class Column;

template < typename T >
class IDataObj {
public:
    IDataObj(T* l = nullptr, 
             T* r = nullptr, 
             T* u = nullptr, 
             T* d = nullptr) noexcept : _l{l}, _r{r}, _u{u}, _d{d} {}
    virtual ~IDataObj() noexcept = default;

    virtual void remove (void) noexcept = 0;
    virtual void restore(void) noexcept = 0;
    virtual void erase  (void) noexcept = 0;

public:
    T* _l, *_r, *_u, *_d;
};

class Node : public IDataObj<Node> {
public:
    Node(int     row = -1,
         Column* col = nullptr,
         Node*   l   = nullptr,
         Node*   r   = nullptr, 
         Node*   u   = nullptr,
         Node*   d   = nullptr) noexcept : IDataObj<Node>(l,r,u,d), _row{row}, _col{col} { }

    virtual void remove (void) noexcept override;
    virtual void restore(void) noexcept override;
    virtual void erase  (void) noexcept override;

public:
    Column*  _col; // Head
    int      _row;
};

class Column : public IDataObj<Column> {
public:
    Column(Column* l = nullptr, Column* r = nullptr) noexcept : 
        IDataObj<Column>(l, r) { } 

    virtual void remove (void) noexcept override;
    virtual void restore(void) noexcept override;
    virtual void erase  (void) noexcept override;

public:
    Node _head; // Head
    int  _size; // Number of ones in the column, used for branching optimization
};

void Node::remove (void) noexcept { 
            _u->_d = _d;
            _d->_u = _u;
            --_col->_size;
}

void Node::restore(void) noexcept { 
    _u->_d = this;
    _d->_u = this;
    ++_col->_size;
}

void Node::erase  (void) noexcept {
    remove ();

    _l->_r = _r;
    _r->_l = _l;
}

void Column::remove (void) noexcept {
    _l->_r = _r;
    _r->_l = _l;

    for     ( auto ccell{ _head._d  }; ccell != &_head; ccell = ccell->_d )
        for ( auto rcell{ ccell->_r }; rcell != ccell;  rcell = rcell->_r )
            rcell->remove();
}

void Column::restore(void) noexcept {
    for     ( auto ccell{ _head._u  }; ccell != &_head; ccell = ccell->_u )
        for ( auto rcell{ ccell->_l }; rcell != ccell;  rcell = rcell->_l )
            rcell->restore ();

    _l->_r = this;
    _r->_l = this;
}

void Column::erase  (void) noexcept {
    remove();

    _l->_r = _r;
    _r->_l = _l;    
}

} // anonymous

class Problem { 
public:
    typedef std::stack<int> Solution; // A solution is a combinaison of rows 
public:
    virtual std::vector<Solution> solve(void) noexcept = 0;
};

class DLX : public Problem {
public:
    DLX(const std::vector<bool>& data, size_t R, size_t C) noexcept;
    virtual ~DLX() noexcept = default;

    auto zeros(void) noexcept { return (_head._r == &_head) && (_head._l == &_head); }

    std::vector<Solution> solve(void) noexcept override;
    Column* toto() noexcept { return col_select(); }
protected:
    void    col_remove (Node* n) noexcept;
    void    col_restore(Node* n) noexcept;
    Column* col_select (void   ) noexcept; /*!< Select a column using Knuth's heuristic */
    
    void _solve() noexcept;
    
private:
    Column                         _head;
    std::vector<Column>            _cols;
  std::vector<Node  >            _nodes;

    std::vector<Problem::Solution> _solutions;
    Problem::Solution              _curSol;
};

DLX::DLX(const std::vector<bool>& data, size_t R, size_t C) noexcept { 
    if ( 0 == R || 0 == C || std::size(data) != R * C ) return;

    _cols .resize( C     );
    _nodes.resize( R * C );

    _head       ._r = &_cols[0    ];
    _head       ._l = &_cols[C - 1];
    _cols[0    ]._l = &_head       ;
    _cols[C - 1]._r = &_head       ;

    for ( auto i{ 0 }; i < C - 1; ++i ) {
        _cols[i    ]._r = &_cols[i + 1];
        _cols[i + 1]._l = &_cols[i    ];
    }

    for ( auto i{ 0 }; i < C; ++i ) _cols[i]._size = R;

    for     ( auto i{ 0 }, k{ 0 }; i < R; ++i      ) {
        for ( auto j{ 0 };         j < C; ++j, ++k ) {

            if ( k < C            ) _cols[j]._head._d = &_nodes[k];
            if ( k >= (R - 1) * C ) _cols[j]._head._u = &_nodes[k];

            _nodes[k]._row = i;
            _nodes[k]._col = &_cols[j];

            _nodes[k]._l = ( 0     == k % C ) ? &_nodes[k + C - 1] : &_nodes[k - 1];
            _nodes[k]._r = ( C - 1 == k % C ) ? &_nodes[k - C + 1] : &_nodes[k + 1];
            _nodes[k]._u = ( k < C          ) ? &_cols [j]._head   : &_nodes[k - C];
            _nodes[k]._d = ( k >= (R-1) * C ) ? &_cols [j]._head   : &_nodes[k + C];
        }
    }

    for     ( auto i{ 0 }, k{ 0 }; i < R; ++i      )
        for ( auto j{ 0 };         j < C; ++j, ++k )
            if ( !data[k] ) _nodes[k].erase();
}

void     DLX::col_remove (Node* n) noexcept { n->_col->remove(); }

void     DLX::col_restore(Node* n) noexcept { n->_col->restore(); }

Column*  DLX::col_select (void) noexcept {
    auto ret{ _head._r };
    for ( auto cdt{ ret->_r }; &_head != cdt; cdt = cdt->_r ) {
        if ( cdt->_size < ret->_size )
            ret = cdt;
    }
    return ret;
}

void DLX::_solve() noexcept {
    // Apply DLX algorithm (recursive, non-deterministic)
    if ( zeros() ) { // success
        _solutions.emplace_back(_curSol);
        return;
    }

    auto curCol{ col_select() };
    if ( 0 == curCol->_size ) // failure
        return;

    // The recursive dance
    curCol->remove();
    for     ( auto cRow{ curCol->_head._d}; &curCol->_head != cRow; cRow = cRow->_d ) {
        for ( auto cCol{ cRow->_r        }; cRow != cCol;           cCol = cCol->_r ) {
            cCol->_col->remove();
            _curSol.push( cCol->_row );
        }

        _solve();

        for ( auto cCol{ cRow->_l        }; cRow != cCol;           cCol = cCol->_l ) {
            cCol->_col->restore();
            _curSol.pop();
        }
    }
    curCol->restore();
}

std::vector<Problem::Solution> DLX::solve(void) noexcept {
    _solutions.clear();
    _solve();
    return _solutions;
}

}

namespace ExactCover {

typedef enum { LatinSquares } Application; 

std::unique_ptr<env::Problem> generate(const std::vector<std::string>& inputs,
                                       ExactCover::Application         app = LatinSquares ) noexcept {
     
    if ( Application::LatinSquares != app ) 
        return nullptr;
    
    // Initial adjacency matrix dimensions ( without constraints )
    auto N{ std::size(inputs) }, rows{ N * N * N }, cols{ 3 * N * N };
  
    // Constraints ( non-zero nodes on provided inputs )
    auto authRows{ std::vector<int>(rows, 1) }, authCols{ std::vector<int>(cols, 1) };

    for     ( auto i{ 0 }; i < N; ++i ) {
        for ( auto j{ 0 }; j < N; ++j ) {
            auto val{ inputs[i][j] - '0' };
            if ( 0 == val ) continue; // No constraint on the node

            for ( auto k{ 0 }; k < N; ++k ) {
                authRows[i * N * N + j * N + k      ] = 0;
                authRows[i * N * N + k * N + val - 1] = 0;
                authRows[k * N * N + j * N + val - 1] = 0;
            }

            authCols[i * N + j                  ] = 0;
            authCols[N * N + i * N + val - 1    ] = 0;
            authCols[2 * N * N + j * N + val - 1] = 0;
            
        }
    }

    auto R{ 0 }, C{ 0 };
    for (auto i{ 0 }; i < rows; ++i ) authRows[i] = authRows[i] ? R++ : -1;
    for (auto i{ 0 }; i < cols; ++i ) authCols[i] = authCols[i] ? C++ : -1;

    auto adj{ std::vector<bool>(R * C, false) };

    for         ( auto i{ 0 }; i < N; ++i ) {
        for     ( auto j{ 0 }; j < N; ++j ) {
            for ( auto k{ 0 }; k < N; ++k ) {
                auto r{ i * N * N + j * N + k };
                if ( -1 == authRows[r] ) continue;
                auto c1{ i * N + j }, c2{ N * N + i * N + k }, c3{ 2 * N * N + j * N + k };
                if (authCols[c1] != -1) adj[authRows[r] * C + authCols[c1]] = true;
                if (authCols[c2] != -1) adj[authRows[r] * C + authCols[c2]] = true;
                if (authCols[c3] != -1) adj[authRows[r] * C + authCols[c3]] = true;
            }
        }
    }

    return std::make_unique<env::DLX>(adj, R, C);
}

}

int main() {
    std::cin.ignore(std::numeric_limits<int32_t>::max(), '\n');
    auto matrix{ ExactCover::generate({ std::istream_iterator<std::string>(std::cin),
                                        std::istream_iterator<std::string>()}) };

    std::cout << std::size(matrix->solve()) << '\n';
}