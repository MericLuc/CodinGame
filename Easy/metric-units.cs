using System;
using System.Text.RegularExpressions;

class Solution
{
    private static string[] units = { "km", null, null, "m", "dm", "cm", "mm", null, null, "um" };

    static void Main(string[] args)
    {
        var expr = Regex.Match(Console.ReadLine(), @"(\d+\.?\d*)(\w+) \+ (\d+\.?\d*)(\w+)");

        var i1 = Array.IndexOf(units, expr.Groups[2].Value);
        var i2 = Array.IndexOf(units, expr.Groups[4].Value);
        var v1 = double.Parse(expr.Groups[1].Value);
        var v2 = double.Parse(expr.Groups[3].Value);

        var (sum, unit) = i1 < i2
            ? (v1 * Math.Pow(10, i2 - i1) + v2, expr.Groups[4].Value)
            : (v2 * Math.Pow(10, i1 - i2) + v1, expr.Groups[2].Value);

        Console.WriteLine($"{sum:0.####}{unit}");
    }
}