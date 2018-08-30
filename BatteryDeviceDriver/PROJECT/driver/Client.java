/*
NAME : PRAVEEN SURYAWANSHI (453) && PRIYANKA BORKAR (410)
class for Client.java
*/

import java.net.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.Color;

public class Client extends Thread
{

  private String server_name = "localhost";
  private int port = 5000;
  private Socket client=null;
  private BufferedReader br=null;
  private String BUFFER=null;
  private StringTokenizer token=null;
  private String    numberOpens=""+0;
  private String    b_percentage=""+0;
  private String    b_charge_level=""+0;
  private String    b_tech="UKNOWN";
  private String    b_model_name=null;
  private String    b_manufacture_name="UKNOWN";
  private String    b_serial_number="UKNOWN";
  private String    b_health="UKNOWN";
  private String    b_capacity_level="UKNOWN";
  private String    b_status="UKNOWN";
  private String    b_chargetype="UKNOWN";

  

  /*CREATING SOCKET */
  public void socket()
  {
    try
    {
      br = new BufferedReader (new InputStreamReader (System.in));
      System.out.println ("powerTech $:CONNECTING TO" + server_name + " ON PORT " +
			  port);
      client = new Socket (server_name, port);
      System.out.println ("powerTech $:JUST CONNECTED " + client.getRemoteSocketAddress ());
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }




  /*SENDING  MESSAGE TO SERVER */
  public void send_message_to_server (String message)
  {
    try
    { 
      PrintStream out = new PrintStream (client.getOutputStream());
      out.println (message);
      out.flush();
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }








  /*READING MESSAGE FROM SERVER */
  public void read_message_from_server ()
  {
    byte []b;
    try
    {
    // BufferedReader sin = new BufferedReader (new InputStreamReader (client.getInputStream ()));
DataInputStream sin= new DataInputStream(client.getInputStream());
    while (true)
      {

	String s = sin.readUTF();
	if (s != null)
	  {
	    System.out.print ("SERVER : " + s + "\n");
	    //screen.OperationsOnGui(s);
	  }
    }
  }
    catch (Exception ex)
    {
      System.out.println(""+ex);
    }
  }







  /* CLOSING THE CLIENT CONNECTION */
  public void close_client ()
  {
    try
    {

      client.close ();
      System.out.println("powerTech $:CONNECTION CLOSED..");
       //exi(0);
    }
    catch (Exception ex)
    {
      ex.printStackTrace ();
    }
  }

public void Tokenize_incoming_data()
{
   	  token=new StringTokenizer(BUFFER," ");
	  numberOpens=token.nextToken();
      b_percentage=token.nextToken();
      b_charge_level=token.nextToken();
      b_tech=token.nextToken();
      b_model_name=token.nextToken()+" "+token.nextToken();
      b_manufacture_name=token.nextToken()+" "+token.nextToken();
      b_serial_number=token.nextToken();
      b_health=token.nextToken();
      b_capacity_level=token.nextToken();
      b_status=token.nextToken();
      b_chargetype=token.nextToken();

	  System.out.println("BATTERY_DEVICE_OPEN  = "+numberOpens);
	  System.out.println("BATTERY_PERCENTAGE  = "+b_percentage);	
	  System.out.println("BATTERY_CHARGE_LEVEL  = "+b_charge_level);
      System.out.println("BATTERY_TECHNOLOGY  = "+b_tech);
  	  System.out.println("BATTERY_MODEL  = "+b_model_name);
  	  System.out.println("BATTERY_MANUFACTURE NAME : "+b_manufacture_name);
 	  System.out.println("BATTERY_SERIAL NUMBER  = "+b_serial_number);
      System.out.println("BATTERY_HEALTH  = "+b_health);
      System.out.println("BATTERY_CAPACITY  = "+b_capacity_level);
      System.out.println("BATTERY_STATUS  = "+b_status);
      System.out.println("BATTERY_CHARGETYPE  = "+b_chargetype);

         
}




/*returns the status of battery*/
String getStatus()
{
return b_status;
}




/* returns the capacity of battery*/
String getCapacityLevel()
{
return b_capacity_level;
}



/*returns the serial number of battery*/
String getSerialNumber()
{
return b_serial_number;
}





/*returns manufacturer name of  battery*/
String getManufactureName()
{
return b_manufacture_name;
}




/*returns the battery model */
String getBatteryModel()
{
return b_model_name;
}




/*returns the charge level of battery*/
String getChargeLevel()
{
return b_charge_level;
}





/*return the number of times the device deriver open the driver*/
String getNumberOPens()
{
return numberOpens;
}



/*returns the charge in percentage of battery*/
String getPercentage()
{

return b_percentage;
}


  public void run()
 {
     try
   {
 Communication_read_from_server();
   }
 catch(Exception ex)
   {
 System.out.println(""+ex);
   }
 }







  /*reading data from server*/
 public void Communication_read_from_server()
 {
     try{
  BUFFER=null;
  BufferedReader sin = new BufferedReader (new InputStreamReader (client.getInputStream ()));

    while(true){

         BUFFER=sin.readLine();
         System.out.println("powerTech $:CLIENT: RECEIVED PACKET : "+BUFFER);
         Tokenize_incoming_data();
         Thread.sleep(1000);     

    }
}
catch(Exception ex)
 {
 ex.printStackTrace();
 }
 
}









    public static void main (String[]args)
  {

    try
    {
          Client open = new Client ();
          open.socket ();
        //  open.Task_to_do ();
          String write_buffer="powerTech $:CONNTECTED TO YOU NOW ...";
          open.send_message_to_server(write_buffer);

        //CREATING THREAD FOR SERVER WRITING OPERATIONS
          open.Communication_read_from_server();



    } catch (Exception e)
    {
      e.printStackTrace ();
    }
  }
}
