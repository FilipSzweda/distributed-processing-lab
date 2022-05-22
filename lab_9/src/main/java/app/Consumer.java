package app;

import java.util.Optional;
import java.util.Random;
import app.Ware.Type;

public class Consumer implements Runnable {
    Integer id;
    Warehouse warehouse;

    public Consumer(Integer id, Warehouse warehouse) {
        this.id = id;
        this.warehouse = warehouse;
    }

    public Ware consume() {
        Random random = new Random();
        Type randomizedType = Type.values()[random.nextInt(Type.values().length)];
        Integer randomizedQuantity = random.nextInt(this.warehouse.getTakenCapacity());
        return new Ware(randomizedType, randomizedQuantity);
    }

    @Override
    public void run() {
        while(!Thread.interrupted()){
            try {
                Thread.sleep(3000 + new Random().nextInt(5000));
                this.warehouse.access(Optional.empty(), Optional.of(this));
            } catch(InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
