#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#pragma GCC optimize "O3,omit-frame-pointer,inline,unroll-loops"

struct Node
{
    int val;
    int sum;

    Node(): val(0), sum(0) {}
};

/*!
 * @brief Binary Search in the precomputed
 * array to find the required index that
 * splits the number of digits fairly
 */
int BinSearch(std::vector<Node>& p_arr, 
              int                p_idxSt,
              int                p_idxEd,
              int                p_val  )
{
    int low  = p_idxSt;
    int high = p_idxEd;
    int mid  = 0;

    while ( low <= high )
    {
        mid = (low + high)/2;
        if      ( p_val == p_arr[mid].sum )
        {
            return mid;
        }
        else if ( p_val < p_arr[mid].sum )
        {
            high = mid -1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return high;
}

/*!
 * @brief Lookup function to quickly get 
 * the number of digits of an input.
 */
int digits(long in)
{
    if      ( in >= 10000000  )
    {
        return 8;
    }
    else if ( in >= 1000000   )
    {
        return 7;
    }
    else if ( in >= 100000    )
    {
        return 6;
    }
    else if ( in >= 10000     )
    {
        return 5;
    }
    else if ( in >= 1000      )
    {
        return 4;
    }
    else if ( in >= 100       )
    {
        return 3;
    }
    else if ( in >= 10        )
    {
        return 2;
    }
    else 
    {
        return 1;
    }

    return 0;
}

int main()
{
    int               NTests; /*!< Number of tests                */
    int               st, ed; /*!< Range of pages to be annotated */
    std::vector<Node> dgts(10000001, Node());

    // -- Precompute the data in a vector -- //
    int l_res = 0;
    for ( int i = 1; i < 10000001; i++ )
    {
        dgts[i].val = digits(i);
        l_res      += dgts[i].val;
        dgts[i].sum = l_res;
    }

    // -- Actually perform the tests -- //
    std::cin >> NTests; std::cin.ignore();
    while( NTests-- )
    {
        long long NTotal = 0;

        std::cin >> st >> ed; std::cin.ignore();
        
        NTotal = dgts[ed].sum + dgts[st].val - dgts[st].sum;
        NTotal /= 2;
        NTotal += dgts[st-1].sum;

        l_res = BinSearch(dgts,
                  st,
                  ed,
                  NTotal);

        std::cout << l_res << std::endl;
    }
}