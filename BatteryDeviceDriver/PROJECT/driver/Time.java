
import java.util.Calendar;
import java.util.Random;
import java.awt.Color;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import javax.swing.JLabel;

 class Time  {

	 private JLabel l;
	 private int red=0,green=0,blue=0;
	 private Random r;
	 private DateFormat df;
	 Calendar cal;
	 
   Time(JLabel l )
   {
	   this.l=l;
	    r= new Random();
	   
	   df=new SimpleDateFormat("HH:mm:ss");



	  
	 
   }
   
    public void run()
   {
    	   
			   red= r.nextInt(255); 
			   green=  r.nextInt(255);
			   blue=  r.nextInt(255);
		        cal= Calendar.getInstance();
	
			     l.setText("          "+df.format(cal.getTime()));
			     l.setForeground(new Color(red,green,blue));
			     l.updateUI();

		
	   
   }
	
}
