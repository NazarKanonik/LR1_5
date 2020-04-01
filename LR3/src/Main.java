import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class Main {
    private static final int VNUMB = 6;

    public static void main(String[] args) throws FileNotFoundException {
        int[][] matrix = readFile("lab3_Kanonik.txt");
        for (int flow = 0; ; ) {

            int df = find(matrix, new boolean[matrix.length], 0, 5, Integer.MAX_VALUE);

            if (df == 0) {

                System.out.println();
                System.out.println("---------------------");
                System.out.print("Значення максимальної суми: ");
                System.out.println(flow);
                System.out.println("KN-416, Kanonik Nazar");
                System.out.println("---------------------");
                return;
            }
            flow += df;
        }
    }

    static public int[][] readFile(String path) throws FileNotFoundException {
        File f = new File(path);
        FileReader reader = new FileReader(f);
        Scanner scanner = new Scanner(reader);
        int data[][] = new int[VNUMB][VNUMB];
        String line;
        String array[];
        for (int i = 0; i < VNUMB; i++) {
            line = scanner.nextLine();
            array = line.split(",");
            for (int j = 0; j < VNUMB; j++) {
                data[i][j] = Integer.valueOf(array[j]);
            }
        }
        return data;
    }

    static private int find(int[][] cap, boolean[] vis, int u, int t, int f) {
        if (u == t) {

            System.out.println("Кінець, перехід до : " + f);
            System.out.println("---------------------");
            return f;
        }

        vis[u] = true;
        for (int v = 0; v < vis.length; v++)
            if (!vis[v] && cap[u][v] > 0) {
                int df = find(cap, vis, v, t, Math.min(f, cap[u][v]));
                if (df > 0) {
                    cap[u][v] -= df;
                    System.out.println(u + " => " + v + ": " + cap[u][v]);
                    cap[v][u] += df;
                    System.out.println(u + " <= " + v + ": " + cap[v][u]);
//                    System.out.printf("(%d,%d):%d\n",u,v,cap[u][v]);
                    return df;
                }
            }
        return 0;
    }
}

