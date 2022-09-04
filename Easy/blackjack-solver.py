points = { 'J':10, 'Q':10, 'K':10, 'A':0 }

def value_cards(cards):
    res=0
    for c in cards:
        if c.isdigit(): res += int(c)
        else:           res += points[c]
    for c in cards:
        if c=='A':
            if res > 10: res += 1
            else:        res += 11
    return res

bank=input().split()
bc=value_cards(bank)
hand=input().split()
hc=value_cards(hand)

if ((hc<bc or hc>21) and bc<=21) or (hc==bc==21 and len(hand)>2 and len(bank)==2) : print('Bank')
elif hc==21 and len(hand)==2 and (bc!=21 or len(bank)>2): print('Blackjack!')
elif hc==bc: print('Draw')
else: print('Player')
