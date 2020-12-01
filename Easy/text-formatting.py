import re

def setMajs(s):
    if not s: return ''
    txt_c = list(s)
    txt_c[0] = txt_c[0].upper()
    return ''.join(txt_c)

txt = input().lower().strip()
txt = re.sub(r'\s{2,}'         , ' '                           , txt)
txt = re.sub(r'\s?[^\s\w\d]\s?', lambda c: c.group().strip()   , txt)
txt = re.sub(r'[^\s\w\d]+'     , lambda c: c.group().strip()[0], txt)
txt = '.'.join(setMajs(s) for s in txt.split('.'))
txt = re.sub(r'[^\s\w\d]'      , lambda c: c.group() + ' '     , txt)

print(txt.strip())
