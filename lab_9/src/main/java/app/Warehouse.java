package app;

import java.util.ArrayList;
import java.util.List;

public class Warehouse {
    Integer capacity;
    List<Ware> wares = new ArrayList<>();;

    public Warehouse(Integer capacity) {
        this.capacity = capacity;
    }

    public void addWare(Ware addedWare) {
        if(this.containsWare(addedWare)) {
            for (Ware ware : this.wares) {
                if(ware.type == addedWare.type) {
                    ware.quantity += addedWare.quantity;
                    break;
                }
            }
        } else {
            this.wares.add(addedWare);
        }
    }

    public void removeWare(Integer id, Ware removedWare) {
        if(containsWare(removedWare)) {
            for (Ware ware : this.wares) {
                if(ware.type == removedWare.type) {
                    if(removedWare.quantity > ware.quantity) {
                        System.out.println("Consumer ID" + id + " consumed: " + ware.getType()
                                + " times " + ware.getQuantity());
                        ware.quantity = 0;
                    } else {
                        System.out.println("Consumer ID" + id + " consumed: " + removedWare.getType()
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
