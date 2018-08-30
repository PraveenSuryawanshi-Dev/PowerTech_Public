import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.beans.*;
import java.awt.geom.Arc2D;
import java.awt.geom.Area;
import java.awt.geom.Ellipse2D;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.Random;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.Mixer;
import javax.sound.sampled.Mixer.Info;
import javax.swing.*;
import javax.swing.plaf.basic.BasicProgressBarUI;

public class DisplayBattery  extends Thread{

	public static Mixer mixer;
	public static Clip clip;
    private CircleProgess progressLoading1=null;
    private Client open=null;

    private final JProgressBar progress1 = new JProgressBar() {
	        @Override public void updateUI() {
	            super.updateUI();
	            setUI(new ProgressCircleBarDrawUI());
	            setBorder(BorderFactory.createEmptyBorder(25, 25, 25, 25));
	        }
	    };
	
 //JFrame splashframe
     DisplayBattery(JFrame splashframe) {
       
            splashframe.dispose();
            open = new Client ();
            open.socket ();
            String write_buffer="powerTech $:(CLIENT) CONNTECTED TO YOU NOW ...";
            open.send_message_to_server(write_buffer);
           //CREATING THREAD FOR SERVER WRITING OPERATIONS
            open.start();
    	
    	


        JFrame frame = new JFrame();
        Panel imagePanel = new Panel();
        frame.getContentPane().add(imagePanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setUndecorated(true);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setBackground(new Color(0, 0, 0, 0));
        frame.setVisible(true);
        
        
        
        
        
        
        
        // adding info panel
         InfoPanel infoPanel  = new InfoPanel(open);
         infoPanel.setBounds(270, 0, 200, 650);
         imagePanel.add(infoPanel);

        
        
        
        
        
        
        
        
      
        
        progress1.setStringPainted(true);
        progress1.setBackground(new Color(255,255,255));
		progress1.setFont(progress1.getFont().deriveFont(30f));
		progress1.setForeground(new Color(Color.OPAQUE));
		progress1.setBounds(10,0,250,300);
		imagePanel.add(progress1);
	
		
		
	       /*working set*/  
		 // CircleProgess progressLoading1= new CircleProgess(Integer.parseInt(open.getPercentage()),progress1);
	     // progressLoading1.addPropertyChangeListener(new ProgressListener(progress1));
	     // progressLoading1.execute();
            this.start();
        
        
    
    }

 public void run()
 { 
   int  old_percentage=0 , new_percentage=0;
   try
      {
       while(true)
         {   
              new_percentage=Integer.parseInt(open.getPercentage());
             
           if(old_percentage!=new_percentage)
             {
//
          old_percentage=new_percentage;        
          progressLoading1= new CircleProgess(Integer.parseInt(open.getPercentage()),progress1);
	      progressLoading1.addPropertyChangeListener(new ProgressListener(progress1));
	      progressLoading1.execute();
             }
         }
      }
   catch(Exception ex)
      {
       System.out.println(""+ex);
      }

 }
    


    public static void main(String[] args) {
         SwingUtilities.invokeLater(new Runnable() {
            public void run() {
               //new DisplayBattery();
            }
        });
    }
   

    @SuppressWarnings("serial")
    public class Panel extends JPanel {

        BufferedImage img;

        public Panel() {
            setOpaque(false);
            setLayout(null);
            /*try {
                img = ImageIO.read(getClass().getResource("image/logo_bat.png"));
            } catch (IOException ex) {
                Logger.getLogger(CircleSplashScreen.class.getName()).log(Level.SEVERE, null, ex);
            }*/
            
            
           
           
            

        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawImage(img, 0, 0, getWidth(), getHeight(), this);
        }

        @Override
        public Dimension getPreferredSize() {
            return new Dimension(500, 300);
        }
    }
    
     
    
}



class ProgressCircleBarDrawUI extends BasicProgressBarUI {
	 
    @Override public Dimension getPreferredSize(JComponent c) {
        Dimension d = super.getPreferredSize(c);
         //d.width;
        int v = Math.max(1,1);
        d.setSize(v, v);

        return d;
    }
    @Override public void paint(Graphics g, JComponent c) {
        Insets b = progressBar.getInsets(); // area for border
         progressBar.setOpaque(true);
        progressBar.setBackground(Color.WHITE);
        
        int barRectWidth  =  progressBar.getWidth()  - b.right - b.left;
        int barRectHeight =progressBar.getHeight() - b.top - b.bottom;
        if (barRectWidth <= 0 || barRectHeight <= 0) {
            return;
        }
        
        Graphics2D g2 = (Graphics2D) g.create();
        
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        double degree = 360 * progressBar.getPercentComplete();
        double sz = Math.min(barRectWidth, barRectHeight);
        double cx = b.left + barRectWidth  * .5;
        double cy = b.top  + barRectHeight * .5;
        double or = sz * .5;
        //double ir = or - 20;
        double ir = or * .5; //.8;
        Shape inner  = new Ellipse2D.Double(cx - ir, cy - ir, ir * 2, ir * 2);
        Shape outer  = new Ellipse2D.Double(cx - or, cy - or, sz, sz);
        Shape sector = new Arc2D.Double(cx - or, cy - or, sz, sz, 90 - degree, degree, Arc2D.PIE);

        Area foreground = new Area(sector);
        Area background = new Area(outer);
        Area hole = new Area(inner);
           
        foreground.subtract(hole);
        background.subtract(hole);

        // draw the track
        // g2.setPaint(new Color(0xFFFFE0));
         g2.setPaint(Color.white);//inner color
         
        
        g2.fill(background);
        
        

        g2.setPaint(progressBar.getForeground());
        g2.fill(foreground);
        g2.dispose();
         
          
        // Deal with possible text painting
        if (progressBar.isStringPainted()) {
        	
            paintString(g, b.left, b.top, barRectWidth, barRectHeight, 0, b);
        }
    }
}



////////////////////////////////////////////////////////////

class CircleProgess extends SwingWorker<String, Void> {
    //private final Random rnd = new Random();
    int current =0 ;// value
    int lengthOfTask =100;
    int stop=0;
    JProgressBar progress;
    
    public  CircleProgess(int stop ,JProgressBar progress )
    {
    	this.stop=stop;
    	this.progress=progress;
       

    }
    @Override public String doInBackground() {
    
         Random random= new Random();
        while (current <= lengthOfTask && !isCancelled()) {
            try { 
            	if(current==stop+1)
            	{
            		
            		 return "ok";
            	}
            	 if(current>=0 && current<=20)
             	{
             		   progress.setForeground(new Color(0xF6C9CC));

            		 Thread.sleep(100);
             	}
             	if(current>=21 && current<=70)
             	{

             		  progress.setForeground(new Color(0xCAE1FF));

             	}
             	if(current>=71 && current<=100)
             	{
             		progress.setForeground(new Color(0xCCFFCC));

             	}
             	
                Thread.sleep(20);
                setProgress(100 * current / lengthOfTask);
            } catch (InterruptedException ie) {
                return "Interrupted";
            }
            
            current++;
        }
        return "Done";
    }
}


class ProgressListener implements PropertyChangeListener {
    private final JProgressBar progressBar;
    ProgressListener(JProgressBar progressBar) {
        this.progressBar = progressBar;
        this.progressBar.setValue(0);
    }
    @Override public void propertyChange(PropertyChangeEvent evt) {
        String strPropertyName = evt.getPropertyName();
        if ("progress".equals(strPropertyName)) {
            progressBar.setIndeterminate(false);
            int progress = (Integer) evt.getNewValue();
            progressBar.setValue(progress);
        }
    }
}








