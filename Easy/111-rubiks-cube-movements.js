function flatten(a) { return Array.prototype.concat(...a); }

const dir = "'", rl = 'x', ud = 'y';
const [r, f1, f2] = [readline().split(' '), readline(), readline()];
const rubik       = [['R', 'L'], ['U', 'D'], ['F', 'B']];

const rotate = rot => {
    let [[x, y], k] = rot[0] === rl ? [[1, 2], 1] : rot[0] === ud ? [[0, 2], 2] : [[0, 1], 0];
    if (rot[1] === dir) { k = rot[0] === rl ? 2 : rot[0] == ud ? 0 : 1; }
    const [X, Y]         = rubik[k];
    rubik[k]             = [Y, X];
    [rubik[x], rubik[y]] = [rubik[y], rubik[x]];
};

r.forEach(rot => { rotate(rot); });

const start = [['R', 'L'], ['U', 'D'], ['F', 'B']];
const face  = (face) => flatten(start)[flatten(rubik).indexOf(face)];
print(face(f1));
print(face(f2));