#include <bits/stdc++.h>

using namespace std;

class Pt {
    public:
        int x, y;
        Pt( int p_x = 0, int p_y = 0 ) : x(p_x), y(p_y) {}

        friend bool operator< (const Pt& p1, const Pt& p2) { return ( p1.x == p2.x ) ? (p1.y < p2.y) : ( p1.x < p2.x ) ; }
        friend bool operator==(const Pt& p1, const Pt& p2) { return p1.x == p2.x && p1.y == p2.y; }
        friend bool operator!=(const Pt& p1, const Pt& p2) { return !(p1 == p2);                  }
};

bool inRange( Pt cur, const vector<string>& v )
{
    return ( ( cur.x >= 0 && cur.x < v.size   () ) &&
             ( cur.y >= 0 && cur.y < v[0].size() ) );
}

bool checkL( Pt from, const Pt& me, const vector<string>& v )
{
    set<Pt> pos, rem;
    int     cmpt(1);
    bool    keep(false);

    for ( int i = from.y -1; i >= 0; i--, cmpt++ )
    {
        for ( int j = from.x-cmpt; j <= from.x+cmpt; j++ ) 
        {
            Pt cur({j, i});
            if ( !inRange(cur, v ) ) { continue; }
            if ( v[cur.x][cur.y] != '.' && cur != me ) { rem.insert( cur ); }
            else                                       { pos.insert( cur ); }

            if ( cur == me ) { keep = true; }
        }
    }

    if ( !keep ) { return false; }

    for ( auto& it : rem )
    {
        int cmpt(0);
        if ( it.x < from.x ) 
        {
            for     ( int i = it.y; i >= 0; i--, cmpt++          )
                for ( int j = it.x - cmpt; j <= it.x; j++        ) 
                {
                    Pt pt(j,i);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else if ( it.x > from.x ) 
        {
            for     ( int i = it.y; i >= 0; i--, cmpt++          )
                for ( int j = it.x; j <= it.x + cmpt; j++        ) 
                {
                    Pt pt(j,i);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else
        {
            for     ( int i = it.y; i >= 0; i--                 )
            {
                    Pt pt(it.x,i);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
            }
        }
    }

    return pos.count(me);
}

bool checkR( Pt from, const Pt& me, const vector<string>& v )
{
    set<Pt> pos, rem;
    int     cmpt(1);
    bool    keep(false);
    for ( int i = from.y +1; i < v[0].size(); i++, cmpt++ )
    {
        for ( int j = -cmpt; j <= cmpt; j++ ) 
        {
            Pt cur({from.x+j, i});
            if ( !inRange(cur, v ) ) { continue; }
            if ( v[cur.x][cur.y] != '.' && cur != me ) { rem.insert( cur ); }
            else                                       { pos.insert( cur ); }

            if ( cur == me ) { keep = true; }
        }
    }

    if ( !keep ) { return false; }

    for ( auto& it : rem )
    {
        int cmpt(0);
        if ( it.x < from.x ) 
        {
            for     ( int i = it.y; i < v[0].size(); i++, cmpt++ )
                for ( int j = it.x - cmpt; j <= it.x; j++        ) 
                {
                    Pt pt(j,i);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else if ( it.y > from.y ) 
        {
            for     ( int i = it.y; i < v[0].size(); i++, cmpt++ )
                for ( int j = it.x; j <= it.x + cmpt; j++        ) 
                {
                    Pt pt(j,i);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else
        {
            for     ( int i = it.y; i < v[0].size(); i++         )
            {
                    Pt pt(it.x,i);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
            }
        }
    }

    return pos.count(me);
}

bool checkU( Pt from, const Pt& me, const vector<string>& v )
{
    set<Pt> pos, rem;
    int     cmpt(1);
    bool    keep(false);

    for ( int i = from.x -1; i >= 0; i--, cmpt++ )
    {
        for ( int j = -cmpt; j <= cmpt; j++ ) 
        {
            Pt cur({i, from.y + j});
            if ( !inRange(cur, v ) ) { continue; }
            if ( v[cur.x][cur.y] != '.' && cur != me ) { rem.insert( cur ); }
            else                                       { pos.insert( cur ); }

            if ( cur == me ) { keep = true; }
        }
    }

    if ( !keep ) { return false; }

    for ( auto& it : rem )
    {
        int cmpt(0);
        if ( it.y < from.y ) 
        {
            for     ( int i = it.x; i >= 0; i--, cmpt++       )
                for ( int j = it.y - cmpt; j <= it.y; j++     ) 
                {
                    Pt pt(i,j);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else if ( it.y > from.y ) 
        {
            for     ( int i = it.x; i >= 0; i--, cmpt++       )
                for ( int j = it.y; j <= it.y + cmpt; j++     ) 
                {
                    Pt pt(i,j);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else
        {
            for     ( int i = it.x; i >= 0; i--               )
            {
                Pt pt(i,it.y);
                if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                pos.erase( pt );
            }
        }
    }

    return pos.count(me); 
}

bool checkD( Pt from, const Pt& me, const vector<string>& v )
{
    set<Pt> pos, rem;
    int     cmpt(1);
    bool    keep(false);

    for ( int i = from.x +1; i < v.size(); i++, cmpt++ )
    {
        for ( int j = from.y-cmpt; j <= from.y + cmpt; j++ ) 
        {
            Pt cur({i, j});
            if ( !inRange(cur, v ) ) { continue; }
            if ( v[cur.x][cur.y] != '.' && cur != me ) { rem.insert( cur ); }
            else                                       { pos.insert( cur ); }

            if ( cur == me ) { keep = true; }
        }
    }

    if ( !keep ) { return false; }

    for ( auto& it : rem )
    {
        int cmpt(0);
        if ( it.y < from.y ) 
        {
            for     ( int i = it.x; i < v.size(); i++, cmpt++ )
                for ( int j = it.y - cmpt; j <= it.y; j++     ) 
                {
                    Pt pt(i,j);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else if ( it.y > from.y ) 
        {
            for     ( int i = it.x; i < v.size(); i++, cmpt++ )
                for ( int j = it.y; j <= it.y + cmpt; j++     ) 
                {
                    Pt pt(i,j);
                    if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                    pos.erase( pt );
                }
        }
        else
        {
            for     ( int i = it.x; i < v.size(); i++         )
            {
                Pt pt(i,it.y);
                if ( inRange(pt, v) && v[pt.x][pt.y] == 'Y' ) { return false; }
                pos.erase( pt );
            }
        }
    }

    return pos.count(me);
}

main() {
    int H, W, cmpt(0); cin >> H >> W; cin.ignore();
    istream_iterator<string> it(cin), eos;
    vector<string>           v (it, eos);
    Pt                       me;

    for ( auto& str : v ) { cerr << str << endl; }
    for     ( int i = 0; i < v.   size(); i++ ) 
        for ( int j = 0; j < v[0].size(); j++ ) { if ( v[i][j] == 'Y' ) { me = Pt(i,j); } }

    for ( int i = 0; i < v.size(); i++ ) 
    {
        for ( int j = 0; j < v[0].size(); j++ ) 
        {
            switch( v[i][j] )
            {
                case '<': if( checkL( {i,j}, me, v ) ) { cmpt++; } break;
                case '>': if( checkR( {i,j}, me, v ) ) { cmpt++; } break;
                case '^': if( checkU( {i,j}, me, v ) ) { cmpt++; } break;
                case 'v': if( checkD( {i,j}, me, v ) ) { cmpt++; } break;
                default: break;
            }
        }
    }
    cout << cmpt << endl;
}