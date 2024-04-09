import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HeapSort {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

        int n = Integer.parseInt(reader.readLine());
        long[] array = new long[n];
        String[] input = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            array[i] = Long.parseLong(input[i]);
        }

        long counter = heapSort(array);

        writer.write(Long.toString(counter));
        writer.flush();
    }

    public static long heapSort(long[] array) {
        long counter = 0;
        int n = array.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            counter += maxHeapify(array, n, i);
        }
        for (int i = n - 1; i > 0; i--) {
            long temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            maxHeapify(array, i, 0);
        }
        return counter;
    }

    public static long maxHeapify(long[] array, int n, int i) {
        long counter = 0;
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && array[left] > array[largest]) {
            largest = left;
        }
        if (right < n && array[right] > array[largest]) {
            largest = right;
        }
        if (largest != i) {
            counter++;
            long temp = array[i];
            array[i] = array[largest];
            array[largest] = temp;
            counter += maxHeapify(array, n, largest);
        }
        return counter;
    }
}
