// Solution from DPAmar

xor = (a,b)=>
{
	var res = '';
	for(var i=0; i<a.length; i++)
		res += (parseInt(a[i], 16) ^ parseInt(b[i], 16)).toString(16)
	return res;
}

console.log(xor(xor(readline(),readline()),readline()).replace(/../g, x=>String.fromCharCode(parseInt(x,16))))