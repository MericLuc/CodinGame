#include <bits/stdc++.h>

template< class T >
class BST {

private:
    T                    m_val;
    std::unique_ptr<BST> m_lft;
    std::unique_ptr<BST> m_rht;

public:
    BST(T val) : m_val(val), m_lft(nullptr), m_rht(nullptr) {}

    BST& insert(T val) {
          if      ( val < m_val )
          {
              if ( !m_lft ) { m_lft = std::unique_ptr<BST>(new BST(val)); }
              else        { m_lft->insert(val);                         }
          }
          else if ( val > m_val )
          {
              if ( !m_rht ) { m_rht = std::unique_ptr<BST>(new BST(val)); }
              else        { m_rht->insert(val);                         }
          }
      return *this;
    }

    void insert( const std::vector<T>& val ) { for ( auto it : val ) { insert(it); } }

    void inOrder(BST* cur, std::vector<T>& m) {
        if ( cur )
        {
            inOrder    (cur->m_lft.get(), m);
            m.push_back(cur->m_val         );
            inOrder    (cur->m_rht.get(), m);
        }
    }

    void preOrder(BST* cur, std::vector<T>& m) {
        if ( cur ) 
        { 
            m.push_back(cur->m_val); 
            preOrder( cur->m_lft.get(), m);
            preOrder( cur->m_rht.get(), m);
        }
    }

    void postOrder(BST* cur, std::vector<T>& m) {
        if ( cur ) 
        {
            postOrder( cur->m_lft.get(), m);
            postOrder( cur->m_rht.get(), m);
            m.push_back(cur->m_val); 
        }
    }

    void levelOrder(BST* tree, std::vector<T>& m) {
        std::queue<BST*> stk({tree});

        while( !stk.empty() )
        {
            BST* cur = stk.front();
            stk.pop();

            if ( cur )
            {
                m.push_back( cur->m_val       );
                stk.push   ( cur->m_lft.get() );
                stk.push   ( cur->m_rht.get() );
            }
        }
    }

    void inOrderTraverse   (BST *tree) {
        std::vector<T> m;
        inOrder(tree, m);
        std::cout << toString(m) << std::endl;
    }

    void preOrderTraverse  (BST *tree) {
        std::vector<T> m;
        preOrder(tree, m);
        std::cout << toString(m) << std::endl;
    }

    void postOrderTraverse (BST *tree) {
        std::vector<T> m;
        postOrder(tree, m);
        std::cout << toString(m) << std::endl;
    }

    void levelOrderTraverse(BST* tree) {
        std::vector<T> m;
        levelOrder(tree, m);
        std::cout << toString(m) << std::endl;
    }

    std::string toString(const std::vector<T>& v, std::string delim = " " ) {
        std::stringstream ss;
        std::copy( std::begin(v), std::end(v), std::ostream_iterator<T>(ss, delim.c_str()) );
        std::string l_ret( ss.str() );

        return l_ret.size() > delim.size() ? std::string(l_ret.begin(), l_ret.end()-delim.size() ) : l_ret;
    }
};

int main() {
    int n, v1; std::cin >> n;
    std::vector<int> v(n,0);
    for (int i = 0; i < n; i++) { std::cin >> v[i];  }

    BST<int> bst(v[0]);
    bst.insert(v);

    bst.preOrderTraverse  (&bst);
    bst.inOrderTraverse   (&bst);
    bst.postOrderTraverse (&bst);
    bst.levelOrderTraverse(&bst);
}