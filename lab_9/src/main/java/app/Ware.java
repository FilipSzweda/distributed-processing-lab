package app;

public class Ware {
    Type type;
    Integer quantity;

    public enum Type {
        Type_A, Type_B, Type_C, Type_D, Type_E, Type_F, Type_G;
    }

    public Ware(Type type, Integer quantity) {
        this.type = type;
        this.quantity = quantity;
    }

    public Type getType() {
        return type;
    }

    public Integer getQuantity() { return quantity; }
}
