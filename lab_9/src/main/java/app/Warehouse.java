package app;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Warehouse {
    Integer capacity;
    List<Ware> wares = new ArrayList<>();;

    public Warehouse(Integer capacity) {
        this.capacity = capacity;
    }

    public synchronized void access(Optional<Producer> producer, Optional<Consumer> consumer) {
        if(producer.isPresent()) {
            this.producerAccess(producer.get());
        }
        else if (consumer.isPresent()) {
            this.consumerAccess(consumer.get());
        }
    }

    public void consumerAccess(Consumer consumer) {
        Ware consumedWare = consumer.consume();
        if(this.containsWare(consumedWare)) {
            this.removeWare(consumer.id, consumedWare);
        }
    }

    public void producerAccess(Producer producer) {
        Integer freeCapacity = this.getFreeCapacity();
        if(freeCapacity > 0) {
            Ware producedWare = producer.produce(freeCapacity);
            this.addWare(producer.id, producedWare);
        }
    }

    public void addWare(Integer id, Ware addedWare) {
        if(this.containsWare(addedWare)) {
            for (Ware ware : this.wares) {
                if(ware.type == addedWare.type) {
                    System.out.println("Producer ID " + id + " produced: " + addedWare.getType()
                            + " times " + addedWare.getQuantity());
                    ware.quantity += addedWare.quantity;
                    break;
                }
            }
        } else {
            System.out.println("Producer ID " + id + " produced: " + addedWare.getType()
                    + " times " + addedWare.getQuantity());
            this.wares.add(addedWare);
        }
    }

    public void removeWare(Integer id, Ware removedWare) {
        if(containsWare(removedWare)) {
            for (Ware ware : this.wares) {
                if(ware.type == removedWare.type) {
                    if(removedWare.quantity > ware.quantity) {
                        System.out.println("Consumer ID " + id + " consumed: " + ware.getType()
                                + " times " + ware.getQuantity());
                        ware.quantity = 0;
                    } else {
                        System.out.println("Consumer ID " + id + " consumed: " + removedWare.getType()
                                + " times " + removedWare.getQuantity());
                        ware.quantity -= removedWare.quantity;
                    }
                    break;
                }
            }
        }
    }

    public boolean containsWare(final Ware ware) {
        return this.wares.stream().filter(w -> w.getType().equals(ware.type)).findFirst().isPresent();
    }

    public Integer getTakenCapacity() {
        Integer takenCapacity = 0;
        for (Ware ware : this.wares) {
            takenCapacity += ware.quantity;
        }
        return takenCapacity;
    }

    public Integer getFreeCapacity() {
        return this.capacity - this.getTakenCapacity();
    }
}
