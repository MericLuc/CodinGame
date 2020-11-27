// Code adapted from the user "[4G]" (mine did not use regEx)

import java.util.*;
import java.util.regex.*;

class Solution {
    public static void main(String args[]) {
        Scanner in             = new Scanner(System.in);
        Pattern p1             = Pattern.compile("(\\([^()\\[\\]]+\\)|\\[[^()\\[\\]]+\\])");
        Pattern p2             = Pattern.compile("(\\w+)");
        Map<String, int[]> map = new HashMap<>();
        String  p              = "";
        int     gen            = 1001;
        int     N              = in.nextInt();
        for (int i = 0; i < N; i++) { map.put(in.next(), new int[]{in.nextInt(), 1}); }
        in.nextLine();
        String c = in.nextLine();

        while(!p.equals(c)) {
            p = c;
            Matcher m1 = p1.matcher(c);
            while(m1.find()) {
                boolean s     = m1.group(1).startsWith("(");
                Matcher sub   = p2.matcher(m1.group(1));
                String  ncode = "HSH" + gen++;
                int[]   nV = {s?0:1, s?1:0};
                while(sub.find()) {
                    int[] pV = map.get(sub.group(1));
                    if ( s ) {
                        nV[0]  = nV[0] * pV[1] + nV[1] * pV[0];
                        nV[1] *= pV[1]; 
                    }
                    else {
                        nV[1]  = nV[1] * pV[0] + nV[0] * pV[1];
                        nV[0] *= pV[0]; 
                    }
                }
                int d1 = nV[0], d2 = nV[1];
                while(d2 > 0) {
                    int tmp = d1 % d2;
                    d1 = d2;
                    d2 = tmp;
                }
                map.put(ncode, new int[] {nV[0]/d1, nV[1]/d1});
                c = c.replaceFirst(m1.group(1).replaceAll("([()\\[\\]])", "\\\\$1"), ncode);
            }
        }
        System.out.println(String.format("%.1f", 1.0 * map.get(c)[0] / map.get(c)[1]));
    }
}