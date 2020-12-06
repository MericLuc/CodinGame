import java.util.*;
import java.io.*;
public class Solution {
    static int N;
    static int[] v;
    static int consecutive=2;
    static int value[][];
    static String path[][];
    static int checks=0;
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        consecutive = sc.nextInt();
        v = new int[N];
        value = new int[N+1][consecutive];
        path = new String[N][consecutive];
        for (int i=0; i<N; i++) {
            v[i] = sc.nextInt();
        }
        String val1 = maximum(0,consecutive);
        String val2 = maximum(1,consecutive);
        String optimal = val2;
        if (value[0][consecutive-1]>value[1][consecutive-1]) {
            optimal = val1;
        }
        System.out.println(optimal.substring(0,optimal.length()-1));
        System.err.println(checks);
    }
    
    public static String maximum(int cnt,int left) {
        left--;
        if (cnt >= N) {return "";}
        else if (value[cnt][left] != 0) {return path[cnt][left];}
        checks++;
        String skip_1 = maximum(cnt+2,consecutive);
        String best = skip_1;
        int val = 0;
        if (left>0) {
            String next = maximum(cnt+1,left);
            if (cnt>N-3 || value[cnt+1][left-1]>value[cnt+2][consecutive-1]) {best = next; val = value[cnt+1][left-1];}
            else {val = value[cnt+2][consecutive-1];}
        }
        else {
            String skip_2 = maximum(cnt+3,consecutive);
            if (cnt>N-3) {best = ""; val = 0;}
            else if (value[cnt+3][consecutive-1]>value[cnt+2][consecutive-1]) {best = skip_2; val = value[cnt+3][consecutive-1];}
            else {val = value[cnt+2][consecutive-1];}
        }
        best = (cnt+1)+">"+best;
        value[cnt][left] = v[cnt]+val;
        path[cnt][left] = best;
        System.err.println("max["+cnt+"]["+left+"] = "+value[cnt][left]);
        return best;
    }
}