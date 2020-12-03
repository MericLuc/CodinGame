import java.util.*;
import java.io.*;
import java.math.*;

class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        String st = "";
        while (in.hasNext()) {
            try {
                String tmp = in.next();
                int    num = in.next().length();
                int    bin = tmp.equals("0") ? 1 : 0;

                if (tmp.equals("000")) {System.out.println("INVALID"); return; }
                for (int i = 0; i < num; i++) {st += ""+bin; }
            }
            catch (Exception e) {System.out.println("INVALID"); return;}
        }
        if (st.length() % 7 != 0) {System.out.println("INVALID"); return;}
        String res = "";
        while (st.length() > 0) {
            String cur = st.substring(0,7);
            st         = st.substring(7);
            char   cnt = (char)Integer.parseInt("0"+cur,2);
            res       += cnt;
        }
        System.out.println(res);
    }
}