#include <bits/stdc++.h>

static constexpr const char
            *roundStartStr { "Round %d\n" }, 
            *roundMidStr   { "----------\n" },
            *roundEndStr   { "##########\n" },
            *actionStr     { "%d %s(s) attack(s) %d %s(s) dealing %d damage\n%d unit(s) perish\n" },
            *winStr        { "%s won! %d unit(s) left\n" };

struct Stack { 
    static constexpr size_t BUFF_LEN{ 21 }; 
    char                    name[BUFF_LEN];
    int                     amount, health, damage, total;
    Stack() { 
        scanf("%20[^;];%d;%d;%d\n", name, &amount, &health, &damage); 
        total = amount * health;
    };
};

int main() {
    int                  turn{ 0 };
    std::array<Stack, 2> s;

    while( ++turn ) {
        fprintf(stdout, roundStartStr, turn );

        for ( int i{ 0 }; i < 2; ++i ) {
            Stack& att{ s[i % 2] }, &def{ s[(i + 1) % 2] };
            int   dmg       = att.amount * att.damage;
            int   newTotal  = std::max(0, def.total - dmg);
            int   newAmount = ceil(((float)newTotal)/def.health);
            int   dead      = std::min(def.amount, def.amount - newAmount);

            fprintf(stdout, actionStr, att.amount, att.name, def.amount, def.name, dmg, dead );
            fprintf(stdout, "%s", (( 0 == i ) ? roundMidStr : roundEndStr) );

            def.amount = std::max(0, def.amount - dead);
            def.total  = std::max(0, def.total - dmg);

            if ( def.amount == 0 ) {
                fprintf(stdout, winStr, att.name, att.amount );
                return EXIT_SUCCESS;
            }
        }
    }
}