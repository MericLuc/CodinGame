const pts = [...new Array(+readline())]
    .map((_) => {
        const [x, y] = readline().split(' ').map(Number);
        return {x: x, y: y};
    });

let res = 0;

for     (let i = 0;   i < pts.length-1; i++) {
        const p1 = pts[i];
    for (let j = i+1; j < pts.length;   j++) {
        const p2 = pts[j];
        const dx = p2.x - p1.x;
        const dy = p2.y - p1.y;
        if (
            (p1.x === p2.x && p1.y === p2.y)                           ||
            (dx < 0 || dy < 0)                                         ||
            (!pts.some((e) => e.x === p2.x - dy && e.y === p2.y + dx)) ||
            (!pts.some((e) => e.x === p1.x - dy && e.y === p1.y + dx)  ||
            (dx === 0 && p1.x - dy < p2.x) 
            )
        ) continue;
        res++;
    }
}

console.log(res);