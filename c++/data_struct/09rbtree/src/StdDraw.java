/**
 * Created by Halo on 2018/12/26.
 */
/*************************************************************************
 *  Compilation:  javac StdDraw.java
 *  Execution:    java StdDraw
 *
 *  Standard graphics library.
 *  Todo
 *  ----
 *    -  Add support for gradient fill, etc.
 *
 *  Remarks
 *  -------
 *    -  don't use AffineTransform for rescaling since it inverts
 *       images and strings
 *    -  careful using setFont in inner loop within an animation -
 *       it can cause flicker
 *
 *  To generate javadoc
 *  -------------------
 *  javadoc -nodeprecated -nodeprecatedlist -notree -noindex -nohelp -nonavbar StdDraw.java
 *
 *************************************************************************/

import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.ImageIO;


/**
 *  <i>Standard draw</i>. Our class StdDraw provides a basic capability for
 *  creating drawings with your programs. It uses a simple graphics model that
 *  allows you to create drawings consisting of points, lines, and curves
 *  in a window on your computer and to save the drawings to a file.
 *  <p>
 *  For documentation, see Section 1.5 of <i>Introduction to Programming in Java: An Interdisciplinary Approach, Spring 2007 preliminary version</i> and
 *  <a href="http://www.cs.princeton.edu/introcs/15inout">http://www.cs.princeton.edu/introcs/15inout</a>
 */
public final class StdDraw implements ActionListener, MouseListener, MouseMotionListener, KeyListener {

    // pre-defined colors
    public static final Color BLACK      = Color.BLACK;
    public static final Color BLUE       = Color.BLUE;
    public static final Color CYAN       = Color.CYAN;
    public static final Color DARK_GRAY  = Color.DARK_GRAY;
    public static final Color GRAY       = Color.GRAY;
    public static final Color GREEN      = Color.GREEN;
    public static final Color LIGHT_GRAY = Color.LIGHT_GRAY;
    public static final Color MAGENTA    = Color.MAGENTA;
    public static final Color ORANGE     = Color.ORANGE;
    public static final Color PINK       = Color.PINK;
    public static final Color RED        = Color.RED;
    public static final Color WHITE      = Color.WHITE;
    public static final Color YELLOW     = Color.YELLOW;

    // default colors
    private static final Color DEFAULT_PEN_COLOR   = BLACK;
    private static final Color DEFAULT_CLEAR_COLOR = WHITE;

    // current pen color
    private static Color penColor;

    // default canvas size is SIZE-by-SIZE
    private static final int DEFAULT_SIZE = 512;
    private static int width  = DEFAULT_SIZE;
    private static int height = DEFAULT_SIZE;

    // default pen radius
    private static final double DEFAULT_PEN_RADIUS = 0.002;

    // current pen radius
    private static double penRadius;

    // show we draw immediately or wait until next show?
    private static boolean defer = false;

    // boundary of drawing canvas, 5% border
    private static final double BORDER = 0.05;
    private static final double DEFAULT_XMIN = 0.0;
    private static final double DEFAULT_XMAX = 1.0;
    private static final double DEFAULT_YMIN = 0.0;
    private static final double DEFAULT_YMAX = 1.0;
    private static double xmin, ymin, xmax, ymax;

    // default font
    private static final Font DEFAULT_FONT = new Font("SansSerif", Font.PLAIN, 16);

    // current font
    private static Font font;

    // double buffered graphics
    private static BufferedImage offscreenImage, onscreenImage;
    private static Graphics2D offscreen, onscreen;

    // singleton for callbacks: avoids generation of extra .class files
    private static StdDraw std = new StdDraw();

    // the frame for drawing to the screen
    private static JFrame frame;

    // mouse state
    private static boolean mousePressed = false;
    private static double mouseX = 0;
    private static double mouseY = 0;

    // keyboard state
    private static Character lastKeyTyped = null;

    // not instantiable
    private StdDraw() { }


    // static initializer
    static { init(); }

    /**
     * Set the window size to w-by-h pixels
     *
     * @param w the width as a number of pixels
     * @param h the height as a number of pixels
     * @throws a RunTimeException if the width or height is 0 or negative.
     */
    public static void setCanvasSize(int w, int h) {
        if (w < 1 || h < 1) throw new RuntimeException("width and height must be positive");
        width = w;
        height = h;
        init();
    }

    // init
    private static void init() {
        if (frame != null) frame.setVisible(false);
        frame = new JFrame();
        offscreenImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        onscreenImage  = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        offscreen = offscreenImage.createGraphics();
        onscreen  = onscreenImage.createGraphics();
        setXscale();
        setYscale();
        offscreen.setColor(DEFAULT_CLEAR_COLOR);
        offscreen.fillRect(0, 0, width, height);
        setPenColor();
        setPenRadius();
        setFont();
        clear();

        // add antialiasing
        RenderingHints hints = new RenderingHints(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        hints.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
        offscreen.addRenderingHints(hints);

        // frame stuff
        ImageIcon icon = new ImageIcon(onscreenImage);
        JLabel draw = new JLabel(icon);

        draw.addMouseListener(std);
        draw.addMouseMotionListener(std);

        frame.setContentPane(draw);
        frame.addKeyListener(std);    // JLabel cannot get keyboard focus
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);            // closes all windows
        // frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);      // closes only current window
        frame.setTitle("Standard Draw");
        frame.setJMenuBar(createMenuBar());
        frame.pack();
        frame.setVisible(true);
    }

    // create the menu bar (changed to private)
    private static JMenuBar createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("File");
        menuBar.add(menu);
        JMenuItem menuItem1 = new JMenuItem(" Save...   ");
        menuItem1.addActionListener(std);
        menuItem1.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
                Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        menu.add(menuItem1);
        return menuBar;
    }


    /*************************************************************************
     *  User and screen coordinate systems
     *************************************************************************/

    /**
     * Set the X scale to be the default
     */
    public static void setXscale() { setXscale(DEFAULT_XMIN, DEFAULT_XMAX); }
    /**
     * Set the Y scale to be the default
     */
    public static void setYscale() { setYscale(DEFAULT_YMIN, DEFAULT_YMAX); }
    /**
     * Set the X scale (a border is added to the values)
     * @param min the minimum value of the X scale
     * @param max the maximum value of the X scale
     */
    public static void setXscale(double min, double max) {
        double size = max - min;
        xmin = min - BORDER * size;
        xmax = max + BORDER * size;
    }
    /**
     * Set the Y scale (a border is added to the values)
     * @param min the minimum value of the Y scale
     * @param max the maximum value of the Y scale
     */
    public static void setYscale(double min, double max) {
        double size = max - min;
        ymin = min - BORDER * size;
        ymax = max + BORDER * size;
    }

    // helper functions that scale from user coordinates to screen coordinates and back
    private static double  scaleX(double x) { return width  * (x - xmin) / (xmax - xmin); }
    private static double  scaleY(double y) { return height * (ymax - y) / (ymax - ymin); }
    private static double factorX(double w) { return w * width  / Math.abs(xmax - xmin);  }
    private static double factorY(double h) { return h * height / Math.abs(ymax - ymin);  }
    private static double   userX(double x) { return xmin + x * (xmax - xmin) / width;    }
    private static double   userY(double y) { return ymax - y * (ymax - ymin) / height;   }


    /**
     * Clear the screen with the default color, white
     */
    public static void clear() { clear(DEFAULT_CLEAR_COLOR); }
    /**
     * Clear the screen with the given color. Calls show().
     * @param color the Color to make the background
     */
    public static void clear(Color color) {
        offscreen.setColor(color);
        offscreen.fillRect(0, 0, width, height);
        offscreen.setColor(penColor);
        show();
    }

    /**
     * Set the pen size to the default
     */
    public static void setPenRadius() { setPenRadius(DEFAULT_PEN_RADIUS); }
    /**
     * Set the pen size to the given size
     * @param r the radius of the pen
     * @throws RuntimeException if r is negative
     */
    public static void setPenRadius(double r) {
        if (r < 0) throw new RuntimeException("pen radius must be positive");
        penRadius = r * DEFAULT_SIZE;
        BasicStroke stroke = new BasicStroke((float) penRadius, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
        offscreen.setStroke(stroke);
    }

    /**
     * Set the pen color to the default which is BLACK.
     */
    public static void setPenColor() { setPenColor(DEFAULT_PEN_COLOR); }
    /**
     * Set the pen color to the given color. The available pen colors are
     BLACK, BLUE, CYAN, DARK_GRAY, GRAY, GREEN, LIGHT_GRAY, MAGENTA,
     ORANGE, PINK, RED, WHITE, and YELLOW.
     * @param color the Color to make the pen
     */
    public static void setPenColor(Color color) {
        penColor = color;
        offscreen.setColor(penColor);
    }

    /**
     * Set the font to be the default for all string writing
     */
    public static void setFont() { setFont(DEFAULT_FONT); }
    /**
     * Set the font as given for all string writing
     * @param f the font to make text
     */
    public static void setFont(Font f) { font = f; }


    /*************************************************************************
     *  Drawing geometric shapes.
     *************************************************************************/

    /**
     * Draw a line from (x0, y0) to (x1, y1)
     * @param x0 the x co-ord of the starting point
     * @param y0 the y co-ord of the starting point
     * @param x1 the x co-ord of the destination point
     * @param y1 the y co-ord of the destination point
     */
    public static void line(double x0, double y0, double x1, double y1) {
        offscreen.draw(new Line2D.Double(scaleX(x0), scaleY(y0), scaleX(x1), scaleY(y1)));
        show();
    }

    /**
     * Draw one pixel at (x, y)
     * @param x the x co-ord of the pixel
     * @param y the y co-ord of the pixel
     */
    private static void pixel(double x, double y) {
        offscreen.fillRect((int) Math.round(scaleX(x)), (int) Math.round(scaleY(y)), 1, 1);
    }

    /**
     * Draw a point at (x, y)
     * @param x the x co-ord of the point
     * @param y the y co-ord of the point
     */
    public static void point(double x, double y) {
        double xs = scaleX(x);
        double ys = scaleY(y);
        double r = penRadius;
        // double ws = factorX(2*r);
        // double hs = factorY(2*r);
        // if (ws <= 1 && hs <= 1) pixel(x, y);
        if (r <= 1) pixel(x, y);
        else offscreen.fill(new Ellipse2D.Double(xs - r/2, ys - r/2, r, r));
        show();
    }

    /**
     * Draw circle of radius r, centered on (x, y); degenerate to pixel if small
     * @param x the x co-ord of the center of the circle
     * @param y the y co-ord of the center of the circle
     * @param r the radius of the circle
     * @throws RuntimeException if the radius of the circle is negative
     */
    public static void circle(double x, double y, double r) {
        if (r < 0) throw new RuntimeException("circle radius can't be negative");
        double xs = scaleX(x);
        double ys = scaleY(y);
        double ws = factorX(2*r);
        double hs = factorY(2*r);
        if (ws <= 1 && hs <= 1) pixel(x, y);
        else offscreen.draw(new Ellipse2D.Double(xs - ws/2, ys - hs/2, ws, hs));
        show();
    }

    /**
     * Draw filled circle of radius r, centered on (x, y); degenerate to pixel if small
     * @param x the x co-ord of the center of the circle
     * @param y the y co-ord of the center of the circle
     * @param r the radius of the circle
     * @throws RuntimeException if the radius of the circle is negative
     */
    public static void filledCircle(double x, double y, double r) {
        if (r < 0) throw new RuntimeException("circle radius can't be negative");
        double xs = scaleX(x);
        double ys = scaleY(y);
        double ws = factorX(2*r);
        double hs = factorY(2*r);
        if (ws <= 1 && hs <= 1) pixel(x, y);
        else offscreen.fill(new Ellipse2D.Double(xs - ws/2, ys - hs/2, ws, hs));
        show();
    }

    /**
     * Draw an arc of radius r, centered on (x, y), from angle1 to angle2 (in degrees).
     * @param x the x co-ord of the center of the circle
     * @param y the y co-ord of the center of the circle
     * @param r the radius of the circle
     * @param angle1 the starting angle. 0 would mean an arc beginning at 3 o'clock.
     * @param angle2 the angle at the end of the arc. For example, if
     *        you want a 90 degree arc, then angle2 should be angle1 + 90.
     * @throws RuntimeException if the radius of the circle is negative
     */
    public static void arc(double x, double y, double r, double angle1, double angle2) {
        if (r < 0) throw new RuntimeException("arc radius can't be negative");
        while (angle2 < angle1) angle2 += 360;
        double xs = scaleX(x);
        double ys = scaleY(y);
        double ws = factorX(2*r);
        double hs = factorY(2*r);
        if (ws <= 1 && hs <= 1) pixel(x, y);
        else offscreen.draw(new Arc2D.Double(xs - ws/2, ys - hs/2, ws, hs, angle1, angle2 - angle1, Arc2D.OPEN));
        show();
    }

    /**
     * Draw squared of side length 2r, centered on (x, y); degenerate to pixel if small
     * @param x the x co-ord of the center of the square
     * @param y the y co-ord of the center of the square
     * @param r radius is half the length of any side of the square
     * @throws RuntimeException if r is negative
     */
    public static void square(double x, double y, double r) {
        if (r < 0) throw new RuntimeException("square side length can't be negative");
        double xs = scaleX(x);
        double ys = scaleY(y);
        double ws = factorX(2*r);
        double hs = factorY(2*r);
        if (ws <= 1 && hs <= 1) pixel(x, y);
        else offscreen.draw(new Rectangle2D.Double(xs - ws/2, ys - hs/2, ws, hs));
        show();
    }

    /**
     * Draw a filled square of side length 2r, centered on (x, y); degenerate to pixel if small
     * @param x the x co-ord of the center of the square
     * @param y the y co-ord of the center of the square
     * @param r radius is half the length of any side of the square
     * @throws RuntimeException if r is negative
     */
    public static void filledSquare(double x, double y, double r) {
        if (r < 0) throw new RuntimeException("square side length can't be negative");
        double xs = scaleX(x);
        double ys = scaleY(y);
        double ws = factorX(2*r);
        double hs = factorY(2*r);
        if (ws <= 1 && hs <= 1) pixel(x, y);
        else offscreen.fill(new Rectangle2D.Double(xs - ws/2, ys - hs/2, ws, hs));
        show();
    }

    /**
     * Draw a polygon with the given (x[i], y[i]) coordinates
     * @param x an array of all the x co-ordindates of the polygon
     * @param y an array of all the y co-ordindates of the polygon
     */
    public static void polygon(double[] x, double[] y) {
        int N = x.length;
        GeneralPath path = new GeneralPath();
        path.moveTo((float) scaleX(x[0]), (float) scaleY(y[0]));
        for (int i = 0; i < N; i++)
            path.lineTo((float) scaleX(x[i]), (float) scaleY(y[i]));
        path.closePath();
        offscreen.draw(path);
        show();
    }

    /**
     * Draw a filled polygon with the given (x[i], y[i]) coordinates
     * @param x an array of all the x co-ordindates of the polygon
     * @param y an array of all the y co-ordindates of the polygon
     */
    public static void filledPolygon(double[] x, double[] y) {
        int N = x.length;
        GeneralPath path = new GeneralPath();
        path.moveTo((float) scaleX(x[0]), (float) scaleY(y[0]));
        for (int i = 0; i < N; i++)
            path.lineTo((float) scaleX(x[i]), (float) scaleY(y[i]));
        path.closePath();
        offscreen.fill(path);
        show();
    }



    /*************************************************************************
     *  Drawing images.
     *************************************************************************/

    // get an image from the given filename
    private static Image getImage(String filename) {

        // to read from file
        ImageIcon icon = new ImageIcon(filename);

        // try to read from URL
        if ((icon == null) || (icon.getImageLoadStatus() != MediaTracker.COMPLETE)) {
            try {
                URL url = new URL(filename);
                icon = new ImageIcon(url);
            } catch (Exception e) { /* not a url */ }
        }

        // in case file is inside a .jar
        if ((icon == null) || (icon.getImageLoadStatus() != MediaTracker.COMPLETE)) {
            URL url = StdDraw.class.getResource(filename);
            if (url == null) throw new RuntimeException("image " + filename + " not found");
            icon = new ImageIcon(url);
        }

        return icon.getImage();
    }

    /**
     * Draw picture (gif, jpg, or png) centered on (x, y). Calls show().
     * @param x the center x co-ord of the image
     * @param y the center y co-ord of the image
     * @param s the name of the image/picture, i.e. "ball.gif"
     * @throws RuntimeException if the image's width or height are negative
     */
    public static void picture(double x, double y, String s) {
        Image image = getImage(s);
        double xs = scaleX(x);
        double ys = scaleY(y);
        int ws = image.getWidth(null);
        int hs = image.getHeight(null);
        if (ws < 0 || hs < 0) throw new RuntimeException("image " + s + " is corrupt");

        offscreen.drawImage(image, (int) Math.round(xs - ws/2.0), (int) Math.round(ys - hs/2.0), null);
        show();
    }

    /**
     * Draw picture (gif, jpg, or png) centered on (x, y).
     * Rescaled to w-by-h. Degenerates to pixel if small. Calls show().
     * @param x the center x co-ord of the image
     * @param y the center y co-ord of the image
     * @param s the name of the image/picture, i.e. "ball.gif"
     * @param w the width of the image
     * @param h the height of the image
     */
    public static void picture(double x, double y, String s, double w, double h) {
        Image image = getImage(s);
        double xs = scaleX(x);
        double ys = scaleY(y);
        double ws = factorX(w);
        double hs = factorY(h);
        if (ws <= 1 && hs <= 1) pixel(x, y);
        else {
            offscreen.drawImage(image, (int) Math.round(xs - ws/2.0),
                    (int) Math.round(ys - hs/2.0),
                    (int) Math.round(ws),
                    (int) Math.round(hs), null);
        }
        show();
    }


    /*************************************************************************
     *  Drawing text.
     *************************************************************************/

    /**
     * Write the given text string in the current font, center on (x, y).
     * Calls show().
     * @param x the center x co-ord of the text
     * @param y the center y co-ord of the text
     * @param s the text
     */
    public static void text(double x, double y, String s) {
        offscreen.setFont(font);
        FontMetrics metrics = offscreen.getFontMetrics();
        double xs = scaleX(x);
        double ys = scaleY(y);
        int ws = metrics.stringWidth(s);
        int hs = metrics.getDescent();
        offscreen.drawString(s, (float) (xs - ws/2.0), (float) (ys + hs));
        show();
    }

    /**
     * Display on screen and pause for t milliseconds.
     * Calling this method means that the screen will NOT be redrawn
     * after each line(), circle(), or square(). This is useful when there
     * are many methods to call to draw a complete picture.
     * @param t number of milliseconds
     */
    public static void show(int t) {
        defer = true;
        onscreen.drawImage(offscreenImage, 0, 0, null);
        frame.repaint();
        try { Thread.currentThread().sleep(t); }
        catch (InterruptedException e) { System.out.println("Error sleeping"); }
    }


    /**
     * Display on-screen;
     * calling this method means that the screen WILL be redrawn
     * after each line(), circle(), or square(). This is the default.
     */
    public static void show() {
        if (!defer) onscreen.drawImage(offscreenImage, 0, 0, null);
        if (!defer) frame.repaint();
    }


    /*************************************************************************
     *  Save drawing to a file.
     *************************************************************************/

    /**
     * Save to file - suffix must be png, jpg, or gif.
     * @param filename the name of the file with one of the required suffixes
     */
    public static void save(String filename) {
        File file = new File(filename);
        String suffix = filename.substring(filename.lastIndexOf('.') + 1);

        // png files
        if (suffix.toLowerCase().equals("png")) {
            try { ImageIO.write(offscreenImage, suffix, file); }
            catch (IOException e) { e.printStackTrace(); }
        }

        // need to change from ARGB to RGB for jpeg
        // reference: http://archives.java.sun.com/cgi-bin/wa?A2=ind0404&L=java2d-interest&D=0&P=2727
        else if (suffix.toLowerCase().equals("jpg")) {
            WritableRaster raster = offscreenImage.getRaster();
            WritableRaster newRaster;
            newRaster = raster.createWritableChild(0, 0, width, height, 0, 0, new int[] {0, 1, 2});
            DirectColorModel cm = (DirectColorModel) offscreenImage.getColorModel();
            DirectColorModel newCM = new DirectColorModel(cm.getPixelSize(),
                    cm.getRedMask(),
                    cm.getGreenMask(),
                    cm.getBlueMask());
            BufferedImage rgbBuffer = new BufferedImage(newCM, newRaster, false,  null);
            try { ImageIO.write(rgbBuffer, suffix, file); }
            catch (IOException e) { e.printStackTrace(); }
        }

        else {
            System.out.println("Invalid image file type: " + suffix);
        }
    }


    /**
     * @deprecated
     * Open a save dialog when the user selects "Save As" from the menu
     */
    public void actionPerformed(ActionEvent e) {
        FileDialog chooser = new FileDialog(StdDraw.frame, "Use a .png or .jpg extension", FileDialog.SAVE);
        chooser.setVisible(true);
        String filename = chooser.getFile();
        if (filename != null) {
            StdDraw.save(chooser.getDirectory() + File.separator + chooser.getFile());
        }
    }


    /*************************************************************************
     *  Mouse interactions.
     *************************************************************************/

    /**
     * Is the mouse being pressed?
     * @return true or false
     */
    public static boolean mousePressed() { return mousePressed; }

    /**
     * Where is the mouse?
     * @return the value of the X co-ord of the mouse
     */
    public static double mouseX() { return mouseX; }

    /**
     * Where is the mouse?
     * @return the value of the Y co-ord of the mouse
     */
    public static double mouseY() { return mouseY; }

    /** @deprecated
     */
    public void mouseClicked(MouseEvent e) { }

    /** @deprecated
     */
    public void mouseEntered(MouseEvent e) { }

    /** @deprecated
     */
    public void mouseExited(MouseEvent e) { }

    /**
     * @deprecated
     */
    public void mousePressed(MouseEvent e) {
        mouseX = StdDraw.userX(e.getX());
        mouseY = StdDraw.userY(e.getY());
        mousePressed = true;
    }

    /**
     * @deprecated
     */
    public void mouseReleased(MouseEvent e) { mousePressed = false; }

    /**
     * @deprecated
     */
    public void mouseDragged(MouseEvent e)  {
        mouseX = StdDraw.userX(e.getX());
        mouseY = StdDraw.userY(e.getY());
    }

    /**
     * @deprecated
     */
    public void mouseMoved(MouseEvent e) {
        mouseX = StdDraw.userX(e.getX());
        mouseY = StdDraw.userY(e.getY());
    }


    /*************************************************************************
     *  Keyboard interactions.
     *************************************************************************/

    /**
     * Has the user typed a key?
     * @return true if the user has typed a key, false otherwise
     */
    public static boolean hasNextKeyTyped() { return lastKeyTyped != null; }

    /**
     * What is the next key that was typed by the user?
     * @return the next key typed
     */
    public static char nextKeyTyped() {
        char c = lastKeyTyped;
        lastKeyTyped = null;
        return c;
    }

    /**
     * @deprecated
     */
    public void keyTyped(KeyEvent e) {
        lastKeyTyped = e.getKeyChar();
    }

    /** @deprecated
     */
    public void keyPressed(KeyEvent e) { }

    /** @deprecated
     */
    public void keyReleased(KeyEvent e) { }




    /** @deprecated
     */
    // test client
    public static void main(String[] args) {
        StdDraw.square(.2, .8, .1);
        StdDraw.filledSquare(.8, .8, .2);
        StdDraw.circle(.8, .2, .2);

        StdDraw.setPenColor(StdDraw.MAGENTA);
        StdDraw.setPenRadius(.02);
        StdDraw.arc(.8, .2, .1, 200, 45);

        // draw a blue diamond
        StdDraw.setPenRadius();
        StdDraw.setPenColor(StdDraw.BLUE);
        double[] x = { .1, .2, .3, .2 };
        double[] y = { .2, .3, .2, .1 };
        StdDraw.filledPolygon(x, y);

        // text
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.text(0.2, 0.5, "black text");
        StdDraw.setPenColor(StdDraw.WHITE);
        StdDraw.text(0.7, 0.8, "white text");
    }

}
