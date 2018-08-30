import java.awt.Color;
import java.awt.Font;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JButton;
import java.awt.event.*;
import java.util.Random;

 public class InfoPanel extends JPanel implements Runnable {

       /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

   
   private  Client open=null;

   private  int percentage=0;
   private  String status=null;
   private  String vendor=null;
   private  String model=null;
   private  String serial=null;
   private  String charge_level=null;
   private  String capacity=null;
   private  String device_open=null;

        public InfoPanel(Client open)
            {
             

                this.open=open;
                Thread thread1 = new Thread(this);
                thread1.start();          

 
            }



   public  void set_percentage()
       {
           
          this.percentage=Integer.parseInt(open.getPercentage());

       } 


   public  void set_status()
       {
       this.status=open.getStatus();

          
       } 
    
   public  void  set_vendor()
      {
         this.vendor=open.getManufactureName();

       }


   public   void set_model()
       {
          this.model=open.getBatteryModel();
       }
          
   public  void set_serial()
      {
     this.serial=open.getSerialNumber();
      }


   public  void set_charge_level()
      {
      this.charge_level=open.getChargeLevel();
      }



   public  void set_capacity()
      {
          this.capacity=open.getCapacityLevel();
      }


   public  void set_device_open()
      {
        this.device_open=open.getNumberOPens();
      }
  




  












         public void run()
            {

            setOpaque(false);
            setLayout(null);
            this.setBackground(new Color(0,0,0,0));
        	this.setBackground(new Color(0,0,0,65));
  		    this.setLayout(null);
  		    this.setOpaque(true);

           
           JLabel percent = new JLabel("");
           JLabel status_label = new JLabel("");
           JLabel vendor_label = new JLabel("");
		   JLabel model_label = new JLabel("");
	       JLabel serila_label = new JLabel("");
		   JLabel capacity_label = new JLabel("");
		   JLabel dev_open_label = new JLabel("");
           JLabel capacity_l_label= new JLabel("");
           final JLabel timeLabel = new JLabel("");
           JLabel notification = new JLabel("");


	  Random  r= new Random();
      int red,green,blue;
               

          percent.setBounds(0, 0, 350, 30);
  		  this.add(percent); 
          status_label.setBounds(0, 0, 300, 90);
		  this.add(status_label);
          vendor_label.setBounds(0, 0, 300, 150);
    	    this.add(vendor_label);
          model_label.setBounds(0, 0, 300, 210);
		    this.add(model_label);	
         serila_label.setBounds(0, 0, 300, 270);
	     this.add(serila_label);
        capacity_l_label.setBounds(0, 0, 300, 390);
		this.add(capacity_l_label);  
        notification.setBounds(0, 0, 300, 450);
        dev_open_label .setBounds(0, 0, 300, 510);
	   this.add(dev_open_label );
     this.add(notification);	
      timeLabel.setBounds(0,270,300,30);
        timeLabel.setFont(new Font("",Font.BOLD,20));
            this.updateUI();
            this.add(timeLabel);

           Time time = new Time(timeLabel);
            while(true)
          { 

            
           
                             /*notification lanbel*/
                            notification.setText("       NOTIFICATION : "+""); 
						    notification.setForeground(Color.BLUE);
                           // notification.setBounds(0, 0, 300, 450);
						    //this.add(notification);	
                            /**/

                

               red=r.nextInt(255); 
			   green=  r.nextInt(255);
			   blue=  r.nextInt(255);
          /*percent label*/
                set_percentage();
            if(percentage>=0 && percentage<=20)
               {
           notification.setText("       PLUG CHARGER"); 
            
			  

               }
                if(percentage==100)
               {
          notification.setText("       UNPLUG CHARGER : "); 
               }
               if( percentage>=0 &&  percentage<=20)
             	{      

             		   percent.setForeground(Color.RED);
                      

             	}
             	if( percentage>=21 &&  percentage<=70)
             	{

             		  percent.setForeground(Color.BLUE);

             	}
             	if( percentage>=71 &&  percentage<=100)
             	{
             		percent.setForeground(Color.GREEN);

             	}
            percent.setText("       CHARGE PERCENT : "+percentage+" %");
               notification.setForeground(new Color(red,green,blue));
			   notification.updateUI();
  		    //percent.setBounds(0, 0, 350, 30);
  		    //this.add(percent);
  		   /**/ 
     




  		    
  		    /*status label*/
          set_status();
		  status_label.setText("        STATUS : "+status); 
	      status_label.setForeground(Color.BLUE);
          if(status.equals("NONE"))
          { 
          status_label.setText("        STATUS : "+"CHARGING");
          notification.setText("       NOTIFICATION : "+"CHARGER PLUGGED"); 
          status_label.setForeground(Color.GREEN);	 
          }
          if(status.equals("TRICKLE"))
          {     
          status_label.setText("        STATUS : "+"DISCHARGING");  
          status_label.setForeground(Color.RED);	    
          }else
         if(status.equals("UNKNOWN"))
          {
          status_label.setText("        STATUS : "+"CHARGING");  
          notification.setText("       NOTIFICATION : "+"CHARGER PLUGGED"); 
          status_label.setForeground(Color.GREEN);	
          }else
         if(status.equals("FAST"))
          {
          status_label.setText("        STATUS : "+"FAST CHARGING"); 
          notification.setText("       NOTIFICATION : "+"CHARGER PLUGGED");  
          status_label.setForeground(Color.GREEN);	
          }
      	  //status_label.setBounds(0, 0, 300, 90);
		  //this.add(status_label);
	     /**/
  		    
		  
		         /*vendor label*/
                set_vendor();
			    vendor_label.setText("       VENDOR : "+vendor); 
			    vendor_label.setForeground(Color.BLUE);
			    //vendor_label.setBounds(0, 0, 300, 150);
			    //this.add(vendor_label);	    
		        /**/
			    
			    
			    
			        /*model number label*/
                    set_model();
				    model_label.setText("       MODEL : "+model); 
				    model_label.setForeground(Color.BLUE);
				   // model_label.setBounds(0, 0, 300, 210);
				    //this.add(model_label);		    
		    	   /**/
				    
				       /*serial number label*/
                        set_serial();
					    serila_label.setText("       SERIAL : "+serial); 
					    serila_label.setForeground(Color.BLUE);
					   // serila_label.setBounds(0, 0, 300, 270);
					    //this.add(serila_label);
					   /**/
					    
					    
					    
					        /*capacity level  label*/
                            set_charge_level();
						    capacity_label.setText("       CHARGE LEVEL : "+charge_level); 
						    capacity_label.setForeground(Color.BLUE);
                            capacity_label.setBounds(0, 0, 300, 330);
						    this.add(capacity_label);	    
					        /**/

                         
                            /*capacity label*/
                             set_capacity();
                             capacity_l_label.setText("       CAPACITY : "+capacity); 
                             capacity_l_label.setForeground(Color.BLUE);
                             if(capacity.equals("CRITICAL"))
                                 {
                                 capacity_l_label.setForeground(Color.RED);
                                 }else
                             if(capacity.equals("LOW") )
                                 {
						         capacity_l_label.setForeground(Color.RED);
                                 }else
                            if(capacity.equals("NORMAL"))
                                 {
						         capacity_l_label.setForeground(Color.BLUE);
                                 }else
							if(capacity.equals("HIGH"))
 							     {
						         capacity_l_label.setForeground(Color.YELLOW);
 							     }else
						    if(capacity.equals("FULL"))
      							{
						         capacity_l_label.setForeground(Color.GREEN);
      							}
						    capacity_l_label.setText("       CAPACITY : "+capacity); 
                           // capacity_l_label.setBounds(0, 0, 300, 390);
						    //this.add(capacity_l_label);    
					       /**/
			    	
       

						   


 
                    
                            /**/
						    
  
                                /*device open label*/
                                set_device_open();
							    dev_open_label .setText("      DEVICE OPEN : ["+device_open+"] TIME'S"); 
							    dev_open_label .setForeground(Color.BLACK);
							   // dev_open_label .setBounds(0, 0, 300, 510);
							    //this.add(dev_open_label );
                               /**/
							    
							    
						   


			    	


			    	
          /*============= time=========================*/
            //final JLabel timeLabel = new JLabel();
             //time = new Time(timeLabel);
            timeLabel.updateUI();
          //  timeLabel.setBounds(0,270,300,30);
           // timeLabel.setFont(new Font("",Font.BOLD,20));
            this.updateUI();
            //this.add(timeLabel);
            time.run();//
            timeLabel.addMouseListener(new MouseListener(){

				@Override
				public void mouseClicked(MouseEvent e) {
					// TODO Auto-generated method stub
					open.close_client();
					System.exit(0);
				}

				@Override
				public void mouseEntered(MouseEvent e) {
					// TODO Auto-generated method stub
					try{
					

					  }
					catch(Exception ex)
					{
						System.out.println(ex);
					}

				  
					
				}

				@Override
				public void mouseExited(MouseEvent arg0) {
					// TODO Auto-generated method stub
					

				}

				@Override
				public void mousePressed(MouseEvent arg0) {
					// TODO Auto-generated method stub
					
				}

				@Override
				public void mouseReleased(MouseEvent arg0) {
					// TODO Auto-generated method stub
					
				}
            	
            });
           /*=================================================*/ 
             /*sleeping for 0.5 seconds*/
             try{
               Thread.sleep(500);
               } 
             catch(Exception ex)
             {
              System.out.println(""+ex);
             }
           /**/


           } 
           

        }

    }



