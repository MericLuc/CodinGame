// From Yatech

using System;
using System.Linq;

class Solution
{
    static void Main(string[] args)
    {
        int N = int.Parse(Console.ReadLine());

        foreach (var frames in Enumerable.Range(0, N).Select(_ => Console.ReadLine().Split()))
            Console.WriteLine(string.Join(" ", GetScores(frames)));
    }

    private static int[] GetScores(string[] frames)
    {
        var scores = new int[10];
        var nextBallsToAdd = new int[10];

        void AddToPrevious(int frame, int score)
        {
            for (int i = frame - 2; i < frame; i++)
            {
                if (i >= 0 && nextBallsToAdd[i] > 0)
                {
                    scores[i] += score;
                    nextBallsToAdd[i]--;
                }
            }
        }

        for (int i = 0; i < frames.Length; i++)
        {
            foreach ((var score, var nextBalls) in frames[i].Select(pins => GetResult(pins, scores[i])))
            {
                AddToPrevious(i, score);
                nextBallsToAdd[i] = nextBalls;
                scores[i] += score;
            }
        }

        for (int i = 1; i < scores.Length; i++)
            scores[i] += scores[i - 1];

        return scores;
    }

    private static (int score, int nextBalls) GetResult(char pins, int score) => pins switch
    {
        'X' => (10, 2),
        '/' => (10 - (score % 10), 1),
        '-' => (0, 0),
        _ => (int.Parse($"{pins}"), 0)
    };
}