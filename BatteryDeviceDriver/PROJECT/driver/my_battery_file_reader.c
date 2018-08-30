/**
NAME : PRAVEEN SURESH SURYAWANSHI  ( 453 )&& PRIYANKA   BORKAR (410)

BATTERY INFORMATION READER PROGRAM FROM  USERSPACE KERNEL  i.e /dev/ebchar  DEVICE.
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define BUFFER_LENGTH 2000       //size of buffer
#define PATH "/dev/ebbchar"
#define BAT_INFO "bat_info.txt"
static char receive[BUFFER_LENGTH];     // the receive buffer from LKM

char  s_devices[4];
char  s_percentage[4];
char  s_charge_level[4];

char b_tech[30];
char b_model_name[30];
char b_manufacture_name[30];
char b_serial_number[30];
char b_health[30];
char b_capacity_level[30];
char b_status[30];
char b_charge_type[30];

char modelname_1[10];
char manufacture_1[10];
int tok_cnt=0;
int cnt=0;
int ret, fd , file_fd;
char stringToSend[]="SEND ME BATTERY INFORMATION";









/*WRITING INFORMAATION INTO bat_info.txr*/
void write_to_bat_info()
{
  
  ret = write(file_fd,receive, strlen(receive)); // Send the string to the LKM
   if (ret < 0)
   {
      perror("powerTech $:ERROR :FAILED TO WRITE MESSAGE TO DEVICE KERNEL..\n");
      return ;
   }
  lseek(file_fd,0,SEEK_SET);
}






/*DISPLAYING BTTERY INFORMATION*/
void display_battery_info()
{  

  

 printf("\npowerTech $:DISPLAY KERNEL INFORMTION : %d\n",cnt);
 cnt++;
 printf("\n==============BATTERY INFORMATION========\n");
 printf("\nOPEND FOR :( %s )TIMES",s_devices);
 printf("\nBATTERY PERCENTAGE :  %s ",s_percentage);
 printf("\nBATTERY CHARGE LEVEL:  %s ",s_charge_level);
 printf("\nBATTERY TECHNOLOGY USED : %s ",b_tech);
 printf("\nBATTERY MODEL NAME : %s",b_model_name);
 printf("\nBATTERY MANUFACTURE NAME : %s",b_manufacture_name);
 printf("\nBATTERY SERIAL NUMBER : %s ",b_serial_number);
 printf("\nBATTERY HEALTH : %s ",b_health);
 printf("\nBATTERY CAPACITY LEVEL : %s ",b_capacity_level);
 printf("\nBATTERY STATUS: %s ",b_status);
 printf("\nBATTERY CHARGE TYPE : %s ",b_charge_type);
printf("\n===========================================\n");

}






/*C CODE FOR GETTING INFORAMTION FROM /dev/ebbchar*/
int get_information_of_battery(){



   

    /*CODE FOR OPENING.. BATTERY INFORMATION WRITING  TO bat_info.txt*/
    file_fd=open(BAT_INFO,O_WRONLY);
   if(file_fd==-1)
    {
   printf("powerTech $:ERROR: IN OPENING  bat_info \n"); 
  return errno;
    }


    
   
  /**/

   /*CODE FOR FILE OPENING CODE FROM  /dev/ebbchar USING open READ & WRITE MODE*/
   printf("powerTech $:STARTING THE DEVICE KERNEL...\n");
   fd = open(PATH, O_RDWR);             // Open the device with read/write access
   if (fd < 0){
      perror("powerTech $:ERROR :FAILED TO OPEN DEVICE KERNEL... \n");
      return errno;
   }
   /**/




   
   while(1){
    /*CODE FOR SENDING THE STRING TO THE KERNEL MODULE*/
    ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
   if (ret < 0){
      perror("powerTech $:FAILED TO WRITE THE MESSAGE TO DEVICE KERNEL...\n");
      return errno;
   }



   /*CODE FOR READING THE DATA FROM DEVICE*/
   printf("powerTech $:READING FROM THE DEVICE KERNEL\n");
   ret = read(fd, receive,strlen(receive));        // Read the response from the LKM
   if (ret < 0){
      perror("powerTech $:ERROR : FAILED TO READ MESSAGE FROM DEVICE KERNEL\n");
      return errno;
   }
   printf("\n powerTech $: RECEIVED PACKET FROM KERNEL  : %s \n", receive);

    
		tok_cnt = sscanf(receive,"%s %s %s %s %s %s %s %s %s %s %s %s %s",
s_devices,
s_percentage,
s_charge_level,
b_tech,
b_model_name,
modelname_1,
b_manufacture_name,
manufacture_1,
b_serial_number,
b_health,
b_capacity_level,
b_status,
b_charge_type);
strcat(b_model_name,modelname_1);
strcat(b_manufacture_name,manufacture_1);


 if(tok_cnt!=13)
 {
 printf("powerTech $:ERROR : ERROR IN READING FROM KERNEL...\n");
 exit(0);
 }



 display_battery_info();
 write_to_bat_info();
 bzero(&receive,sizeof(receive));
 sleep(5);


}


  /* C CODE FOR CLOSING THE FILE*/
   printf("powerTech $:CLOSING THE FILE  READING DESCRIPTOR FROM KERNEL...\n");
   close(fd);
   close(file_fd);
   return 0;
}





int main()
{
 get_information_of_battery();
 return 1;
}
