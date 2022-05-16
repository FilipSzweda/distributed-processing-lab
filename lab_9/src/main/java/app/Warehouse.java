package app;

import java.util.List;

public class Warehouse {
    Integer capacity;
    List<Ware> wares;

    public Warehouse(List<Ware> wares) {
        this.capacity = capacity;
        this.wares = wares;
    }

    public void addWare(Ware addedWare) {
        if(this.containsWare(addedWare)) {
            for (Ware ware : wares) {
                if(ware.type == addedWare.type) {
                    this.capacity += addedWare.quantity;
                    ware.quantity += addedWare.quantity;
                    break;
                }
            }
        } else {
            wares.add(addedWare);
        }
    }

    public void removeWare(Ware removedWare) {
        if(containsWare(removedWare)) {
            for (Ware ware : wares) {
                if(ware.type == removedWare.type) {
                    if(removedWare.quantity > ware.quantity) {
                        this.capacity -= ware.quantity;
                        ware.quantity = 0;
                    } else {
                        this.capacity -= removedWare.quantity;
                        ware.quantity -= removedWare.quantity;
                    }
                    break;
                }
            }
        }
    }

    public boolean containsWare(final Ware ware){
        return wares.stream().filter(w -> w.getType().equals(ware.type)).findFirst().isPresent();
    }
}
