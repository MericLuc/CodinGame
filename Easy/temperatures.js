const n      = parseInt(readline()) ;
var   inputs = readline().split(' ');
var   res    = n > 0 ? 5526 : 0;

for (let i = 0; i < n; i++) 
{
    const t = parseInt(inputs[i]);
    res = ( Math.abs(t) == Math.abs(res) && t > 0 ) ? t : (Math.abs(t) < Math.abs(res)) ? t : res;
}

console.log(res);