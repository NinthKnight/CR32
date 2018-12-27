public class Main {

    public static void main(String[] args) {
        StdDraw.setPenRadius(.0025);
        RedBlackBST<Integer, Integer> st;
        int species = 2;
        st = new RedBlackBST<Integer, Integer>(species);
        int[] a = { 3, 1, 9, 10};
        for (int i = 0; i < a.length; i++)
            st.put(a[i], i);

        //st.delete(3);

        StdOut.println(st);
        StdDraw.clear(StdDraw.LIGHT_GRAY);
        st.draw(.95, .0025, .008);
        StdOut.println(st.min() + " " + st.max() + " " + st.check());
        StdOut.println(st.ipl());
        StdOut.println(st.heightB());

        st.Layer();
    }
}
