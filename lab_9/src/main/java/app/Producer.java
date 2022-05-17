package app;

import java.util.Random;

public class Producer implements Runnable {
    Warehouse warehouse;

    public Producer(Warehouse warehouse) {
        this.warehouse = warehouse;
    }

    public void produce() {
        // randomize enum type
        // randomize quantity
    }

    @Override
    public void run() {
        while(!Thread.interrupted()){
            try {
                this.produce();
                Thread.sleep(1000);
            } catch(InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
