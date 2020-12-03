const data = [...new Array(+readline())].map(() => readline().split(''));
const test  = (s, a) => {
    switch (a) {
        case '(': case ')': (s[s.length-1] === '(') ? s.pop() : s.push('('); break;
        case '[': case ']': (s[s.length-1] === '[') ? s.pop() : s.push('['); break;
        case '{': case '}': (s[s.length-1] === '{') ? s.pop() : s.push('{'); break;
        case '<': case '>': (s[s.length-1] === '<') ? s.pop() : s.push('<'); break;
    }
    return s;
};

data.forEach( (data) => { console.log(data.reduce(test, []).length === 0); });