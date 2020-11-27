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
        string in    = Console.ReadLine();
        string types = Console.ReadLine();

        int N        = int.Parse(Console.ReadLine());
        var dexp     = DeserializeExp(in, types);
        var items    = new List<Dictionary<string, dynamic>>();

        for (int i = 0; i < N; i++)
        {
            string ROW = Console.ReadLine();

            Dictionary<string, dynamic> item = new Dictionary<string, dynamic>();

            foreach (string block in ROW.Split(','))
            {
                var o = block.Split(':');
                item.Add(o[0], o[1]);
            }

            items.Add(item);
        }

        IOrderedEnumerable<Dictionary<string, dynamic>> sorted = null;

        for (int i = 0; i < dexp.Count(); i++)
        {
            var sp = dexp.ElementAt(i);
            if (i == 0)
            {
                if (sp.IsDescending) { sorted = items.OrderByDescending(a => DynamicKeySelector(a, sp)); }
                else { sorted = items.OrderBy(a => DynamicKeySelector(a, sp)); }
            }
            else
            {
                if (sp.IsDescending) { sorted = sorted.ThenByDescending(a => DynamicKeySelector(a, sp)); }
                else { sorted = sorted.ThenBy(a => DynamicKeySelector(a, sp)); }
            }
        }

        foreach (var s in sorted)
            Console.WriteLine(s.FirstOrDefault(o => o.Key == "id").Value);

    }

    static dynamic DynamicKeySelector(Dictionary<string, dynamic> a, SortingParameter sp)
    {
        var v = a.FirstOrDefault(o => o.Key == sp.PropName).Value;

        if      (sp.TypeName.Equals("string")) { return Convert.ToString(v); }
        else if (sp.TypeName.Equals("int")   ) { return Convert.ToInt32 (v); }
        else { throw new ApplicationException($"type {sp.TypeName} not recognized"); }
    }

    static IEnumerable<SortingParameter> DeserializeExp(string source, string t)
    {
        string[] types = t.Split(',');
        List<SortingParameter> res = new List<SortingParameter>();

        while (true)
        {
            int    next = source.IndexOfAny(new char[] { '+', '-' }, 1);
            string arg  = source.Substring(0, next == -1 ? source.Length : next);

            res.Add(new SortingParameter(arg.Substring(1), types[res.Count], arg[0].Equals('-')));

            if (next == -1) { break; }

            source = source.Substring(next);
        }

        return res;
    }

    public class SortingParameter
    {
        public SortingParameter(string propName, string typeName, bool isDescending)
        {
            PropName     = propName;
            IsDescending = isDescending;
            TypeName     = typeName;
        }

        public string PropName     { get; private set; }
        public bool   IsDescending { get; private set; }
        public string TypeName     { get; private set; }
    }

}