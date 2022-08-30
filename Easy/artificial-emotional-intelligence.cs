using System;
using System.Linq;

class Solution
{
    static void Main()
    {
        var vowels     = "aeiouy".ToCharArray();
        var consonants = "bcdfghjklmnpqrstvwxz".ToCharArray();
        var adjList    = new string[] {"adaptable", "adventurous", "affectionate", "courageous", "creative", "dependable", "determined", "diplomatic", "giving", "gregarious", "hardworking", "helpful", "hilarious", "honest", "non-judgmental", "observant", "passionate", "sensible", "sensitive", "sincere"};
        var goodList   = new string[] {"love", "forgiveness", "friendship", "inspiration", "epic transformations", "wins"};
        var badList    = new string[] {"crime", "disappointment", "disasters", "illness", "injury", "investment loss"};
        
        var name    = Console.ReadLine();
        var vInName = name.ToLower().ToCharArray().Where(_ => vowels.Contains(_)).ToArray();
        var cInName = name.ToLower().ToCharArray().Where(_ => consonants.Contains(_)).Distinct().ToArray();
        if (cInName.Length < 3 || vInName.Length < 2)
            Console.WriteLine($"Hello {name}.");
        else
        {
            Console.WriteLine($"It's so nice to meet you, my dear {adjList[Array.IndexOf(consonants, cInName[0])]} {name}.");
            Console.WriteLine($"I sense you are both {adjList[Array.IndexOf(consonants, cInName[1])]} and {adjList[Array.IndexOf(consonants, cInName[2])]}.");
            Console.WriteLine($"May our future together have much more {goodList[Array.IndexOf(vowels, vInName[0])]} than {badList[Array.IndexOf(vowels, vInName[1])]}.");
        }
    }
}