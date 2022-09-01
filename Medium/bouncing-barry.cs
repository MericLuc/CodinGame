using System;
using System.Linq;
using System.Collections.Generic;

class Solution
{
    static void Main()
    {
        var dirs  = Console.ReadLine().Split(" ").ToList();
        var nbs   = Console.ReadLine().Split(" ").Select(int.Parse).ToList();
        var moves = new (int, int)[] {(0, 1), (0, -1), (1, 0), (-1, 0)};

        var on = new HashSet<(int, int)>();
        (int, int) pos = (0, 0);

        for (int dir = 0; dir < dirs.Count; dir++) {
            for (int i = 0; i < nbs[dir]; i++) {
                var vec = moves["NSEW".IndexOf(dirs[dir])];
                pos = (pos.Item1 + vec.Item1, pos.Item2 + vec.Item2);

                if (on.Contains(pos)) on.Remove(pos);
                else                  on.Add   (pos);
            }
        }

        if (on.Count == 0) {
            Console.WriteLine(".");
            return;
        }

        int xMin = on.Min(a => a.Item1), xMax = on.Max(a => a.Item1), 
            yMin = on.Min(a => a.Item2), yMax = on.Max(a => a.Item2);

        for (int i = yMax; i >= yMin; i--) {
            for (int j = xMin; j <= xMax; j++)
                Console.Write(on.Contains((j, i)) ? "#" : ".");
            Console.WriteLine();
        }
    }
}