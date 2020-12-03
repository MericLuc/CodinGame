const exprs = [...Array(+readline())].map(() => readline().match(/[\(\)\[\]\{\}\<\>]/g).join(''));
const reg = [/\(\)|\{\}|\[\]|<>/g, /([(){}[\]<>])\1/, /\)\(|\}\{|\]\[|></];

exprs.forEach(expr => {
  let sum = 0;
  for (let i = 0; i < reg.length; ++i) {
    const r = expr.replace(reg[i], '');
    if (r !== expr) { expr = r; sum += i; i = -1; }
  }
  console.log(expr.length ? -1 : sum);
});