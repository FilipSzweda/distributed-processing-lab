package app;

import java.util.Random;
import app.Ware.Type;

public class Producer implements Runnable {
    Integer id;
    Warehouse warehouse;

    public Producer(Integer id, Warehouse warehouse) {
        this.id = id;
        this.warehouse = warehouse;
    }

    public Ware produce(Integer freeCapacity) {
        Random random = new Random();
        Type randomizedType = Type.values()[random.nextInt(Type.values().length)];
        Integer randomizedQuantity = random.nextInt(freeCapacity);
        System.out.println("Producer ID" + id + " produced: " + randomizedType + " times " + randomizedQuantity);
        return new Ware(randomizedType, randomizedQuantity);
    }

    @Override
    public void run() {
        while(!Thread.interrupted()){
            try {
                Integer freeCapacity = this.warehouse.getFreeCapacity();
                if(freeCapacity > 0) {
                    Ware producedWare = this.produce(freeCapacity);
                    this.warehouse.addWare(producedWare);
                }
                Thread.sleep(3000 + new Random().nextInt(5000));
            } catch(InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
