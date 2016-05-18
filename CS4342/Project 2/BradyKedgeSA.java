import java.util.Random;

public class BradyKedgeSA {


    public static void Anneal(double[][] points, double[][] clusters, double minChange) {
        double Temp = 1000;
        double min = 0.1;
        double cool = 0.003;
        int iterations = 0;

        int[] labels = null;

        System.out.println("Cluster length: " + clusters.length);
        System.out.println("Points Length: " + points.length);

        boolean changed = true;

        while (Temp > min) {
            labels = assignCluster(points, clusters);
            double[][] newClusters = new double[clusters.length][2];

            //new cluster positions
            for (int i = 0; i < clusters.length; i++) {
                double[] mean = new double[2];
                int count = 0;
                for (int j = 0; j < points.length; j++) {
                    if (labels[j] == i) {
                        mean[0] += points[j][0];
                        mean[1] += points[j][1];
                        count++;
                    }
                }
                newClusters[i][0] = mean[0] / (double)count;
                newClusters[i][1] = mean[1] / (double)count;
            }

            changed = false;

            //Check if any of the clusters changed
            for (int i = 0; i < clusters.length; i++) {
                if (distance(clusters[i], newClusters[i]) >= minChange) {
                    Temp *= 1 - cool;
                }
            }

            iterations += 1;

            clusters = newClusters;

        }

        // Print out the points belonging to each cluster
        System.out.println("FINISHED");
        //System.out.println(clusters.length);
        System.out.println("Iterations: " + iterations);
        System.out.println();


            // Print out points belonging to each cluster
            System.out.print("Cluster 1 points: ");
            for (int i = 0; i < points.length; i++) {
                if (labels[i] == 1) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
            }
            System.out.println();
            System.out.print("Cluster 2 points: ");
            for (int i = 0; i < points.length; i++) {
                if (labels[i] == 2) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
            }
            System.out.println();
            System.out.print("Cluster 3 points: ");
            for (int i = 0; i < points.length; i++) {
                if (labels[i] == 3) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
            }



        System.out.println();

    }

    private static int[] assignCluster(double[][] points, double[][] clusters) {
        //Initialize clusters
        int[] labels = new int[points.length];
        Random r = new Random();


        //Randomly assigns point to cluster
        for(int i = 0; i < points.length; i++)
        {
            for(int j = 0; j < clusters.length; j++)
            {
                labels[i] = r.nextInt((3 - 1) + 1) + 1;
            }
        }

        return labels;
    }

    //Euclid method
    private static double distance(double[] a, double[] b) {
        return Math.sqrt(Math.pow(a[0]-b[0], 2) + Math.pow(a[1]-b[1], 2));
    }

    public static void main(String [ ] args) {

        Random rand = new Random();

        double[][] points = new double[100][100];


        //Fill points
        for(int i = 0; i < points.length; i++)
        {
            for(int j = 0; j < points[i].length; j++)
            {
                points[i][j] = rand.nextInt((100 - 1) + 1) + 1;
            }
        }

        // Initial cluster points in (x,y) format
        double[][] k3 = {{20,10}, {15,90}, {85, 36}};
        int K3 = 1;

        // Call Anneal
        Anneal(points, k3, 0.0001f);



        System.out.println();
    }
}
