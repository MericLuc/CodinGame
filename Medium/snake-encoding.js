var N = parseInt(readline());
var X = parseInt(readline());

var arr = [];
var idx = [];
var m   = [];

for ( var i = 0; i < N; i++ ) { arr[i]= readline(); idx[i]= []; }

for     ( var i = 0; i < N; i++ ) {
    for ( var j = 0; j < N; j++ ) {
        var index = ((j+(j+1)%2)*N + ((j%2==0)? -1 : 1)*i+ (j%2));
        idx[i][j] = index;
        m[index]  = arr[i][j];
    }
}

for     ( var i = 0; i < N; i++ ) {
    var res='';
    for ( var j = 0; j < N; j++ ) {
        var index = idx[i][j] -X;
        index = index % (N*N);
        if( index <= 0 ) index+= N*N
        res += m[index];
    }
    print(res);
}