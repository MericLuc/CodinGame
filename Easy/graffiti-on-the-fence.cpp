#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct stInterval
{
    int m_start;
    int m_end  ;
    
    stInterval(int p_st = 0, int p_ed = 0):
        m_start(p_st),
        m_end  (p_ed)
        { }
    
    bool interLaps(const stInterval& p_other) const 
    { 
        return ( ( (p_other.m_end   >= m_start) && (p_other.m_end   <= m_end) ) ||
                 ( (p_other.m_start >= m_start) && (p_other.m_start <= m_end) ) ||
                 ( (p_other.m_start <= m_start) && (p_other.m_end   >= m_end) ) ||
                 ( (p_other.m_start >= m_start) && (p_other.m_end   <= m_end) ) );
    }
    
    void print(void) const
    {
        cout << m_start << " " << m_end << endl;
    }
    
    stInterval& operator+=(const stInterval& p_other)
    {
        if (this == &p_other ) { return *this; }
        
        m_start = p_other.m_start < m_start ? p_other.m_start : m_start;
        m_end   = p_other.m_end   > m_end   ? p_other.m_end   : m_end  ;
        
        return *this;
    }
};

int main()
{
    int    st         ,   ed;
    int    totalLength,   reportsNumber;
    cin >> totalLength >> reportsNumber; cin.ignore();
    
    stInterval           curInterval;
    map<int, stInterval> states;

    for (int i = 0; i < reportsNumber; i++) 
    {
        cin >> curInterval.m_start 
            >> curInterval.m_end; cin.ignore();
            
        for ( auto  l_it  = states.begin();
                    l_it != states.end  (); ) 
        {
            if ( l_it->second.interLaps(curInterval) )
            {
                curInterval += l_it->second;
                l_it         = states.erase(l_it);
            }
            else
            {
                ++l_it;
            }
        }
        
        states[ curInterval.m_start ] = curInterval;
    }

    if ( (states.size()      == 1              ) &&
         (states.find(0)     != states.end()   ) &&
         (states.at(0).m_end == totalLength    ) )
    {
        cout << "All painted" << endl;
    }
    else
    {
        if ( states.begin()->first > 0 )
        {
            cout << 0 << " " << states.begin()->first << endl;
        }
        
        for ( auto l_it  = states.begin();
                   l_it != states.end();
                   l_it++ ) 
        {
            auto l_it2 = next(l_it,1);
            if( (l_it2 != states.end()) &&
                ( l_it2->second.m_start != l_it->second.m_end) )
            {
                cout << l_it->second.m_end << " " << l_it2->second.m_start << endl;
            }
        }
        
        if ( states.rbegin()->second.m_end < totalLength )
        {
            cout << states.rbegin()->second.m_end << " " << totalLength << endl;
        }
    }
}