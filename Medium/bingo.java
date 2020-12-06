import java.util.*;
import java.io.*;
import java.math.*;
import java.util.stream.Collectors;

class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        if (in.hasNextLine()) { in.nextLine(); }

        List <Card> cards = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            String row = in.nextLine();
            List<Integer> l1 = Arrays.stream(row.split(" ")).map((x)
                -> Integer.parseInt(x)).collect(Collectors.toList());
            row = in.nextLine();
            List<Integer> l2 = Arrays.stream(row.split(" ")).map((x)
                -> Integer.parseInt(x)).collect(Collectors.toList());
            row = in.nextLine();
            List<Integer> l3 = Arrays.stream(row.split(" ")).map((x)
                -> Integer.parseInt(x)).collect(Collectors.toList());
            row = in.nextLine();
            List<Integer> l4 = Arrays.stream(row.split(" ")).map((x)
                -> Integer.parseInt(x)).collect(Collectors.toList());
            row = in.nextLine();
            List<Integer> l5 = Arrays.stream(row.split(" ")).map((x)
                -> Integer.parseInt(x)).collect(Collectors.toList());
            List<Integer> cl = new ArrayList<Integer>();
            cl.add(l1.get(0));cl.add(l2.get(0));cl.add(l3.get(0));cl.add(l4.get(0));cl.add(l5.get(0));
            List<Integer> c2 = new ArrayList<Integer>();
            c2.add(l1.get(1));c2.add(l2.get(1));c2.add(l3.get(1));c2.add(l4.get(1));c2.add(l5.get(1));
            List<Integer> c3 = new ArrayList<Integer>();
            c3.add(l1.get(2));c3.add(l2.get(2));c3.add(l3.get(2));c3.add(l4.get(2));c3.add(l5.get(2));
            List<Integer> c4 = new ArrayList<Integer>();
            c4.add(l1.get(3));c4.add(l2.get(3));c4.add(l3.get(3));c4.add(l4.get(3));c4.add(l5.get(3));
            List<Integer> c5 = new ArrayList<Integer>();
            c5.add(l1.get(4));c5.add(l2.get(4));c5.add(l3.get(4));c5.add(l4.get(4));c5.add(l5.get(4));
            List<Integer> d1 = new ArrayList<Integer>();
            d1.add(l1.get(0));d1.add(l2.get(1));d1.add(l3.get(2));d1.add(l4.get(3));d1.add(l5.get(4));
            List<Integer> d2 = new ArrayList<Integer>();
            d2.add(l1.get(4));d2.add(l2.get(3));d2.add(l3.get(2));d2.add(l4.get(1));d2.add(l5.get(0));
            cards.add(new Card(l1,l2,l3,l4,l5,cl,c2,c3,c4,c5,d1,d2));
        }
        String row = in.nextLine();
        List<Integer> calls = Arrays.stream(row.split(" ")).map((x)
                -> Integer.parseInt(x)).collect(Collectors.toList());
        Integer min = 100;
        
        Integer cartonPlein = 200;
        for(Card carte : cards){
            Integer max = 0;
            int minLine = carte.completeLine(carte.l1,calls);
            max = getMax(minLine, max);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.l2,calls);
            max = getMax(minLine, max);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.l3,calls);
            max = getMax(minLine, max);
            min = getMin(minLine, min);
            minLine= carte.completeLine(carte.l4,calls);
            max = getMax(minLine, max);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.l5,calls);
            max = getMax(minLine, max);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.cl,calls);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.c2,calls);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.c3,calls);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.c4,calls);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.c5,calls);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.d1,calls);
            min = getMin(minLine, min);
            minLine = carte.completeLine(carte.d2,calls);
            min = getMin(minLine, min);
            
            if(cartonPlein > max){
                cartonPlein = max;
            }
        }

        System.out.println(min);
        System.out.println(cartonPlein);
    }
    
    public static Integer getMax(Integer value, Integer max){
        if(value > max){ return value; }
        return max;
    }
    public static Integer getMin(Integer value, Integer min){
        if(value < min){ return value; }
        return min;
    }
    
    static class Card {
        public List<Integer> l1;
        public List<Integer> l2;
        public List<Integer> l3;
        public List<Integer> l4;
        public List<Integer> l5;
        public List<Integer> cl;
        public List<Integer> c2;
        public List<Integer> c3;
        public List<Integer> c4;
        public List<Integer> c5;
        public List<Integer> d1;
        public List<Integer> d2;
        
        public Card (List<Integer> l1, List<Integer> l2, List<Integer> l3,
            List<Integer> l4, List<Integer> l5,List<Integer> cl, List<Integer> c2, List<Integer> c3,
            List<Integer> c4, List<Integer> c5, List<Integer> d1, List<Integer> d2){
                this.l1 = l1;
                this.l2 = l2;
                this.l3 = l3;
                this.l4 = l4;
                this.l5 = l5;
                this.cl = cl;
                this.c2 = c2;
                this.c3 = c3;
                this.c4 = c4;
                this.c5 = c5;
                this.d1 = d1;
                this.d2 = d2;
            }

        public Integer completeLine(List<Integer> l1,List<Integer> calls){
            int numero = 0;
            if(l1.contains(0)){ numero = 1; }
            int numbersCall = 0;
            for(Integer number : calls){
                numbersCall++;
                if(l1.contains(number)){
                    numero++;
                    if(numero == 5){ break; }
                }
            }
            return numbersCall;
        }
    }
}