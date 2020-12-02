const m2nums   = _ => readline().split(' ').map(Number);
const [xA, yA, xB, yB] = m2nums();
const getY     = (x, [a, b, c]) => b === 0 ? 1 : -((a * x + c) / b);
const getYs    = (a) => [getY(xA, a), getY(xB, a)];
const redByMin = (a) => a.every(n => n % Math.min(...a) === 0) ? a.map(e => e / Math.min(...a)) : a;
const sameSign = (a) => a[0] < 0 ? a.map(n => -1 * n) : a;

var eqs = [...new Array(+readline())]
    .map(m2nums)
    .map(redByMin)
    .map(sameSign)
    .map(e => e.toString())
    .map(e => e.split(',').map(Number))
    .filter(( t={}, a=> !(t[a]=a in t) ));

let cntA = 0, cntB = 0;

eqs.map(getYs).forEach(([_yA, _yB]) => {
    if (yA === _yA || yB === _yB) { print('ON A LINE'); quit(); }
    if (yA > _yA)                 { cntA++;                     }
    if (yB > _yB)                 { cntB++;                     }
})

print( (cntA % 2) === (cntB % 2) ? 'YES' : 'NO');