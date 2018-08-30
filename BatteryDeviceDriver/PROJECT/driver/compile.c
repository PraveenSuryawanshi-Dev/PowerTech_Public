#include<stdio.h>


int main()
{

system("cc execute.c -lpthread -o execute");
printf("\n\n\033[034m ============================================*** COMPILING***================================================================\n");
printf("powerTech $ :COMPILING...\n\n");



/*C CODE FOR COMPILING BATTERY DEVICE DRIVER*/
printf("\033[033m ************************************************************************\n");
sleep(1);
printf("\033[032m powerTech $ :COMPILING BATTERY DEVICE DRIVER NOW...\n");
if(system("make clean && make")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE BATTERY DRIVER GOOD BYE!!!\n");
return 0;
}
printf("\033[032m powerTech $ :DEVICE DRIVER COMPILED SUCCESSFULLY !!!\n");
printf("\033[033m ************************************************************************\n");
/**/




/*C CODE FOR COMPILING BATTERY FILE READER */
printf("\033[033m ************************************************************************\n");
sleep(1);
printf("\033[032m powerTech $ :COMPILING BATTERY FILE READER NOW...\n");
if(system("cc -o reader my_battery_file_reader.c")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE BATTERY FILE READER GOOD BYE!!!\n");
return 0;
}
printf("\033[032m powerTech $ :BATTERY FILE READER COMPILED SUCCESSFULLY !!!\n");
printf("\033[033m ************************************************************************\n");
/**/




/*C CODE FOR COMPILING SERVER*/
printf("\033[033m ************************************************************************\n");
sleep(1);
printf("\033[032m powerTech $ :COMPILING SERVER NOW...\n");
if(system("cc -o server server.c")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE SERVER GOOD BYE!!!\n");
return 0;
}
printf("\033[032m powerTech $ :SERVER COMPILED SUCCESSFULLY !!!\n");
printf("\033[033m ************************************************************************\n");
/**/




/* C CODE FOR COMPILING CLIENT*/
printf("\033[033m ************************************************************************\n");
sleep(1);
printf("\033[032m powerTech $ :COMPILING CLIENT NOW...\n");
if(system("javac Client.java")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE CLIENT GOOD BYE!!!\n");
return 0;
}
printf("\033[032m powerTech $ :CLIENT COMPILED SUCCESSFULLY !!!\n");
printf("\033[033m ************************************************************************\n");


/* C CODE FOR FRONT END JAVA*/
printf("\033[033m ************************************************************************\n");
sleep(1);
printf("\033[032m powerTech $ :COMPILING FRONT END NOW...\n");
if(system("javac Time.java")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE FROTN END GOOD BYE!!!\n");
return 0;
}
if(system("javac DisplayBattery.java")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE FROTN END GOOD BYE!!!\n");
return 0;
}
if(system("javac CircleSplashScreen.java")==-1)
{
printf("\033[031m powerTech $ :ERROR: UNABLE TO COMPILE FROTN END GOOD BYE!!!\n");
return 0;
}

printf("\033[032m powerTech $ :FRONTEND COMPILED SUCCESSFULLY !!!\n");
printf("\033[033m ************************************************************************\n");

/**/


printf("\033[032m powerTech $ :COMPILATION COMPLETED !!!\n");
printf(" \033[034m===================================*** COMPILIED SUCCESSFULLY ***==============================================================\n\n");




return 1;
}
