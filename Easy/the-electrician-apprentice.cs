using System.Collections.Generic;
using System.Linq;
using System;

class Solution {
    static void Main(string[] args) {
        var equipments = new List<Equipent>();

        var N = int.Parse(Console.ReadLine());
        for ( var i = 0; i < N; i++ ) {
            var inputs    = Console.ReadLine().Split(' ');
            var equipment = new Equipent() { Name = inputs[0] };
            equipments.Add(equipment);

            foreach ( var s in inputs.Skip(1) ) {
                if (s == "=" || s == "-") {
                    equipment.SwitchMode = s;
                } 
                else {
                    allSwitches[s] = false;
                    equipment.AddSwitch(s);
                }
            }
        }

        var A = int.Parse(Console.ReadLine());
        for (var i = 0; i < A; i++) ToggleSwitch(Console.ReadLine());

        foreach (var circuit in equipments) Console.WriteLine($"{circuit.Name} is {(circuit.On ? "ON" : "OFF")}");
    }

    static readonly Dictionary<string, bool> allSwitches = new Dictionary<string, bool>();
    static void ToggleSwitch(string id) => allSwitches[id] = !allSwitches[id];

    class Equipent {
        public string Name;
        readonly List<List<string>> switches = new List<List<string>>();

        public bool On => switches.All(_ => _.Any(id => allSwitches[id]));

        string mode;
        public string SwitchMode {
            get { return mode; }
            set { if ((mode = value) == "=") switches.Add(new List<string>()); }
        }

        public void AddSwitch(string id) {
            if (mode == "-") switches.Add(new List<string>() { id });
            else switches.Last().Add(id);
        }
    }

    static void Main_Alternative(string[] args) {
        var switches   = new Dictionary<string, bool>();
        var equipments = new List<string[]>();

        var C = int.Parse(Console.ReadLine());
        for (var i = 0; i < C; i++) {
            equipments.Add(Console.ReadLine().Split(' '));
        }

        var A = int.Parse(Console.ReadLine());
        for (var i = 0; i < A; i++) {
            var sw = Console.ReadLine();
            switches[sw] = !(switches.TryGetValue(sw, out bool v) && v);
        }

        foreach ( var eq in equipments ) {
            bool? allOn = null;
            for ( var i = 1; i < eq.Length; ) {
                var on = (eq[i] == "-");
                if ( on ) {
                    while (++i < eq.Length && eq[i] != "-" && eq[i] != "=")
                        on &= (switches.TryGetValue(eq[i], out bool v) && v);
                } 
                else {
                    while (++i < eq.Length && eq[i] != "-" && eq[i] != "=")
                        on |= (switches.TryGetValue(eq[i], out bool v) && v);
                }
                if (!allOn.HasValue) allOn = on; else allOn &= on;
            }
            Console.WriteLine($"{eq[0]} is {(allOn.Value ? "ON" : "OFF")}");
        }
    }
}