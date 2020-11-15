public class MultipleMethods {
    public void some_method() {
        System.out.println("Some method output");
    }

    public void print(String s) {
        System.out.println(s);
    }

    public static void main(String args[]) {
        MultipleMethods m = new MultipleMethods();

        m.some_method();
        m.print("This is the nJVM");
    }
}
