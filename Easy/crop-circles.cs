using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Solution
{
    static void Main(string[] args)
    {
        string[] instructions = Console.ReadLine().Split(' ');
        string   alphabet     = "abcdefghijklmnopqrstuvwxyz";
        bool[,]  map          = new bool[19, 25];

        for     ( int i = 0; i < 19; i++ )
        {
            for ( int j = 0; j < 25; j++ )
            {
                map[i, j] = true;
            }
        }

        foreach ( var inst in instructions )
        {
            string cpy  = inst;
            int    code = 0;

            if      ( cpy.StartsWith("PLANTMOW") ) { code = 2; cpy = cpy.Replace("PLANTMOW", ""); }
            else if ( cpy.StartsWith("PLANT")    ) { code = 1; cpy = cpy.Replace("PLANT", ""); }
            
            int x = alphabet.IndexOf(cpy[0]);
            int y = alphabet.IndexOf(cpy[1]);
            int r = int.Parse(cpy.Substring(2));
            
            for     ( int i = 0; i < 19; i++ )
            {
                for ( int j = 0; j < 25; j++ )
                {
                    if ( (i - x) * (i - x) + (j - y) * (j - y) <= r * r / 4 )
                    {
                        switch (code)
                        {
                            case 0: map[i, j] = false;      break;
                            case 1: map[i, j] = true;       break;
                            case 2: map[i, j] = !map[i, j]; break;
                            default: break;
                        }
                    }
                }
            }
        }

        for     ( int j = 0; j < 25; j++ )
        {
            for ( int i = 0; i < 19; i++ )
            {
                Console.Write(map[i, j] ? "{}" : "  ");
            }
            Console.WriteLine();
        }
    }
}