let grid     = [...new Array(8)].map(() => readline().split(''));
const [c, m] = readline().split(' ');

const getIdx = (char) => [char[1] - 1, char.charCodeAt(0) - 97];
const [x, y] = getIdx(m);

const mirror = (p) => {
    let m = p.join('').match(/BW+(?=b)|bW+(?=B)|WB+(?=w)|wB+(?=W)/g);
    return m ? m.reduce((s, p) => s + p.length - 1, 0) : 0;
};

const checkDirs = (x, y) => 
    mirror(grid[y])                          +
    mirror(grid.map((a) => a[x]))            +
    mirror(grid.map((a, i) => a[x - y + i])) +
    mirror(grid.map((a, i) => a[x + y - i]));

const save = grid[x][y];
grid[x][y] = c.toLowerCase();
const c    = checkDirs(y, x);
grid       = grid.join();
const tks  = {W: grid.match(/W/gi).length, B: grid.match(/B/gi).length};

tks[c]    += c;
tks[c === 'W' ? 'B' : 'W'] -= c;

console.log( save !== '-' ? 'NOPE' : 
                c !== 0 ? `${tks.W} ${tks.B}` : 'NULL' );