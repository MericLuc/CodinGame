ra = _ => readline().split(' ').map(Number);
i = +readline(mB = ra(opB = ra()));

const b  = mB, op = opB, size = b.length;
N = b[i];

for (b[i++] = 0; N-- > 0; i = i % (2*size-1)) { (i < size) ? b[i++]++ : op[i++ - size]++ }

rpl = arr => arr.join(' ').replace(/(\d)$/, '[$1]');
print(rpl(op)); 
print(rpl(b));
if (i == b.length) print('REPLAY');