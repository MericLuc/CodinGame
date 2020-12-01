const R = parseInt(readline()); 
const V = parseInt(readline());
const robbers = Array.from({ length: R }).fill(0);

for (let i = 0; i < V; ++i) {
  const inputs = readline().split(' '); 
  const C = parseInt(inputs[0]); 
  const N = parseInt(inputs[1]);
  const time = Math.pow(10, N) * Math.pow(5, C - N);
  robbers.sort((a, b) => a - b);
  robbers[0] += time;
}
print(Math.max(...robbers));