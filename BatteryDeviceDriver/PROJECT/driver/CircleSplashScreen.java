import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.imageio.ImageIO;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.Mixer;
import javax.sound.sampled.Mixer.Info;
import javax.swing.*;
import java.util.Random;

public class CircleSplashScreen {

	public static Mixer mixer;
	public static Clip clip;
	private  JFrame frame;
	private  ImagePanel imagePanel;


    public CircleSplashScreen() {
    	

    	
    	
    	
        frame = new JFrame();
        JLabel loading = new JLabel("loading");
	    loading.setBounds(20,480,300,20);
        JLabel title = new JLabel("powerTech");
	    title.setBounds(50,0,300,30);
        title.setBackground(Color.BLACK);
        imagePanel = new ImagePanel(frame,loading,title);
		imagePanel.add(title);
        imagePanel.add(loading);
        frame.getContentPane().add(imagePanel);
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setUndecorated(true);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setBackground(new Color(0, 0, 0));
        frame.setVisible(true);
        
        
       
        
        
        
        
        Info[] mixifos=AudioSystem.getMixerInfo();
    	mixer= AudioSystem.getMixer(mixifos[0]);
    	DataLine.Info datainfo= new DataLine.Info(Clip.class,null);
    	try
    	{
    		clip =(Clip)mixer.getLine(datainfo);
    		URL soundurl = CircleSplashScreen.class.getResource("sound/electric.wav");
    		AudioInputStream as=AudioSystem.getAudioInputStream(soundurl);
    		clip.open(as);
    		clip.start();
    	}
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    	}
    	
    }
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new CircleSplashScreen();
            }
        });
    }
   

    @SuppressWarnings("serial")
    public class ImagePanel extends JPanel implements Runnable {

        BufferedImage  img, img1,img2,img3,img4;
        private JFrame frame;
       
        private JLabel title,loading;

        public ImagePanel(JFrame frame , JLabel loading ,JLabel title) {
        	this.frame=frame;
            this.loading=loading;
        	this.title=title;
            //setOpaque(false);
           // setLayout(new GridBagLayout());
            this.setLayout(null);
            new Thread(this).start();
          

        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawImage(img, 0, 0, getWidth(), getHeight(), this);
        }

        @Override
        public Dimension getPreferredSize() {
            return new Dimension(300, 500);
        }

		@Override
		public void run() {
			// TODO Auto-generated method stub
			
	         try {
			 Font font1=  new Font("",Font.CENTER_BASELINE,15);
			 loading.setForeground(Color.BLACK);
			 loading.setText("powerTech");
		     loading.setFont(font1);
             
             Font font2=  new Font("",Font.BOLD,30);
             title.setBackground(Color.BLACK);
             title.setFont(font2);
             this.add(title);

          
                     img1 = ImageIO.read(getClass().getResource("image/1.png"));
                     img2= ImageIO.read(getClass().getResource("image/2.png"));
                     img3 = ImageIO.read(getClass().getResource("image/3.png"));
                     img4= ImageIO.read(getClass().getResource("image/4.png"));

		      	 int i=0;

			 
				  
				    while(i!=15)
				    { 

				     Thread.sleep(300);
                     img=img1;
                     title.setForeground(Color.BLACK);
					 loading.setText("LOADING .....");
	                 this.updateUI();

	                  Thread.sleep(600);
                      title.setForeground(Color.RED);
                      img=img2;
				      loading.setText("LOADING ..........");
	                this.updateUI();
	              
	                 Thread.sleep(400);
                     title.setForeground(Color.GREEN);
                       img=img3;
					loading.setText("LOADING ...............");
	                this.updateUI();
	                
	                Thread.sleep(150);
                     title.setForeground(Color.GREEN);
                     img=img4;
		             loading.setText("LOADING .........................");
	                 this.updateUI();
	                i++;
				    }

                     loading.setForeground(Color.BLUE);
		             loading.setText("      LOADING COMPLETED.");
                     this.updateUI();
				     Thread.sleep(5000);  
				    //call new next Frame--	
                     new DisplayBattery(frame);	          
                
	                
	            } catch (Exception ex) {
	                Logger.getLogger(CircleSplashScreen.class.getName()).log(Level.SEVERE, null, ex);
	            }
			
		}
    }
}

