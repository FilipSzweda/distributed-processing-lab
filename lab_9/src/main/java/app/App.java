package app;

public class App {
    public static void main(String[] args) {
        Integer producersNumber = 3;
        Integer consumersNumber = 3;
        Warehouse warehouse = new Warehouse(1000);
        for(int producerID = 0; producerID < producersNumber; producerID++){
            Thread thread = new Thread(new Producer(producerID, warehouse));
            thread.start();
        }
        for(int consumerID = 0; consumerID < consumersNumber; consumerID++){
            Thread thread = new Thread(new Consumer(consumerID, warehouse));
            thread.start();
        }
    }
}
