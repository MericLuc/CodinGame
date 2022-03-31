from datetime import datetime

def print_validity(str):
    if len(str) != 10 or str[0] == '0' or not str.isdigit():
        return print('INVALID SYNTAX')
    lll, x, ddmmyy = str[:3], str[3], str[4:]

    try:
        datetime.strptime(ddmmyy, "%d%m%y")
    except ValueError:
        return print('INVALID DATE')

    tmp = sum(int(d) * int(m) for d, m in zip(str, '3790584216')) % 11

    if tmp == 10:
        print_validity(f'{int(lll) + 1}0{ddmmyy}')
    elif int(x) != tmp:
        print(f'{lll}{tmp}{ddmmyy}')
    else:
        print('OK')

for _ in range(int(input())): 
    print_validity(input())