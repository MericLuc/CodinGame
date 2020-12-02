import java.util.*;
import java.io.*;

class Solution {
    public static void main(String args[]) {
        Scanner in  = new Scanner(System.in);
        int     N   = in.nextInt();
        String  c[] = new String[N]; in.nextLine();
        
        for (int i = 0; i < N; i++) { c[i] = in.nextLine().toUpperCase(); }
        for (int i = 0; i < N; i++) {
            if (c[i].indexOf('C')==-1) { continue; }
            for (int j = 0; j < c[i].length()-2; j++) {
                if (c[i].substring(j,j+2).equals("CH")) {
                    int b = Integer.parseInt(""+c[i].charAt(j+2));
                    try { b += Integer.parseInt(""+c[i-1].charAt(j+1)); } catch (Exception e) {}
                    try { b += Integer.parseInt(""+c[i+1].charAt(j+1)); } catch (Exception e) {}
                    try { b += Integer.parseInt(""+c[i].charAt(j-2)  ); } catch (Exception e) {}
                    try { b += Integer.parseInt(""+c[i].charAt(j+4)  ); } catch (Exception e) {}
                    
                    if (b!=4) { System.out.println("INVALID"); return; }
                    j+=5;
                }
            }
        }
        System.out.print("VALID");
    }
}