public class References {
    public static void main(String args[]) {
        References r = null;

        if (r == null) {
            System.out.println("The reference r is null for now");
        }

        r = new References();

        if (r != null) {
            System.out.println("The reference r is not null anymore");
        }
    }
}