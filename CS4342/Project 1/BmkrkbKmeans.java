import java.util.Random;

public class BmkrkbKmeans {


    public static void kMeans(double[][] points, double[][] clusters, double minChange, int Kval) {
        int[] labels = null;

        boolean changed = true;

        while (changed) {
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
                    changed = true;
                    break;
                }
            }

            clusters = newClusters;
        }

        // Print out the points belonging to each cluster
        System.out.println();

        if(Kval == 1) {
            System.out.println("K = 2 clusters:");
            System.out.println("Cluster 1 centroid at (" + clusters[0][0] + "," + clusters[0][1] + ")");
            System.out.println("Cluster 2 centorid at (" + clusters[1][0] + "," + clusters[1][1] + ")");
            //System.out.println("Cluster[2] at (" + result.clusters[2][0] + "," + result.clusters[2][1] + ")");
            System.out.println();

            // Print out points belonging to each cluster
            System.out.print("Cluster 1 points: ");
            for (int i = 0; i < points.length; i++) {
                if (labels[i] == 0) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
            }
            System.out.println();
            System.out.print("Cluster 2 points: ");
            for (int i = 0; i < points.length; i++) {
                if (labels[i] == 1) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
            }
        }



        System.out.println();

        if(Kval == 2){
        System.out.println("K = 4 clusters:");
        System.out.println("Cluster 1 centroid at (" + clusters[0][0] + "," + clusters[0][1] + ")");
        System.out.println("Cluster 2 centroid at (" + clusters[1][0] + "," + clusters[1][1] + ")");
        System.out.println("Cluster 3 centroid at (" + clusters[2][0] + "," + clusters[2][1] + ")");
        System.out.println("Cluster 4 centroid at (" + clusters[3][0] + "," + clusters[3][1] + ")");
        System.out.println();

        // Print out points belonging to each cluster
        System.out.print("Cluster 1 points: ");
        for (int i = 0; i < points.length; i++) {
            if (labels[i] == 0) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
        }
        System.out.println();

        System.out.print("Cluster 2 points: ");
        for (int i = 0; i < points.length; i++) {
            if (labels[i] == 1) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
        }
        System.out.println();

        System.out.print("Cluster 3 points: ");
        for (int i = 0; i < points.length; i++) {
            if (labels[i] == 2) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
        }
        System.out.println();

        System.out.print("Cluster 4 points: ");
        for (int i = 0; i < points.length; i++) {
            if (labels[i] == 3) System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
        }

        }


        System.out.println();

    }

    private static int[] assignCluster(double[][] points, double[][] clusters) {
        //Initialize clusters
        int[] labels = new int[points.length];

        // Find the cluster closest to this points and
        // assign it as the new cluster label
        for (int i = 0; i < points.length; i++) {
            double minDistance = Double.MAX_VALUE;
            for (int j = 0; j < clusters.length; j++) {
                double distance = distance(points[i], clusters[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    labels[i] = j;
                }
            }
        }

        return labels;
    }

    //Euclid method
    private static double distance(double[] a, double[] b) {
        return Math.sqrt(Math.pow(a[0]-b[0], 2) + Math.pow(a[1]-b[1], 2));
    }

    public static void main(String [ ] args) {

        Random rand = new Random(15);

        double[][] points = new double[20][20];

        for(int i = 0; i < points.length; i++)
        {
            for(int j = 0; j < points[i].length; j++)
            {
                points[i][j] = rand.nextInt((100 - 1) + 1) + 1;
            }
        }

        // Initial cluster points in (x,y) format
        double[][] k1 = {{30,56}, {20,75}};
        double[][] k2 = {{20,10}, {15,90}, {85, 36}, {76,90}};
        int K1 = 1;
        int K2 = 2;

        // Print numbers to search
        int count = 0;
        System.out.print("points: ");
        for (int i = 0; i < points.length; i++) {
            System.out.print("(" + points[i][0] + "," + points[i][1] + "), ");
            count++;
        }
        System.out.println("\n" + count + " total");

        // Call K-means algorithm
        kMeans(points, k1, 0.0001f, K1);
        kMeans(points, k2, 0.0001f, K2);

        System.out.println();
    }
}
