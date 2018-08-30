/*EXECUTION  FILE*/
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<pthread.h>




void *on_splash_screen(void *args)
{
system("java CircleSplashScreen");
}


void *on_file_reader(void *args)
{
system("sudo ./reader");
return NULL;
}



void *on_server(void *args)
{

system("sudo ./server");
return NULL;
}



int main()
{
pthread_t server_thread=NULL ,reader_thread=NULL,splash_thread=NULL;
printf("\n=============================== ACTIVATING APPLICATION ==========================\n");



printf("powerTech $:INSERTING BATTERY DEVICE DRIVER MODULE TO KERNEL.\n");
system("sudo insmod my_battery_driver.ko");
printf("powerTech $:MODULE INSERTED SUCCESSFULLY TO KERNEL.\n");




printf("powerTech $:EXECUTING DEVICE FILE READER...\n");
pthread_create(&reader_thread,NULL,on_file_reader,NULL);
printf("powerTech $:DEVICE READING STARTED...\n");

printf("powerTech $:EXECUTING SERVER...\n");
pthread_create(&server_thread,NULL,on_server,NULL);
printf("powerTech $:SERVER IS READY TO START...\n");



sleep(15);

printf("powerTech $:INVOVKING  powerTech [ FRONTEND ] AND EXECUTING CLIENT...\n");
printf("SPLASH SCREEN INVOKING.\n");
pthread_create(&splash_thread,NULL,on_splash_screen,NULL);
printf("SPLASH SCREEN IS READY NOW..");
printf("powerTech $:APPLICATION IS READY TO START...\n");

printf("============================== APPLICATION ACTIVATED SUCCESSFULLY =================\n"); 

pthread_join(reader_thread,NULL);
pthread_join(server_thread,NULL);
pthread_join(splash_thread,NULL);
printf("\n=================================== GOOD BYE !!! ==================================\n"); 



  	
return 1;
}
