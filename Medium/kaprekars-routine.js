let num = (n1 = readline());
let res = [];

do {
    res.push(num);
    num = ( parseInt(num.split('').sort((a,b) => b-a).join('')) - 
            parseInt(num.split('').sort((a,b) => a-b).join('')))
            .toString().padStart(n1.length, 0);
} while( res.indexOf(num) < 0 );

console.log(res.splice(res.indexOf(num)).join(' '));