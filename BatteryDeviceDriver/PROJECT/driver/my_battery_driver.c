/**
 * @file   MY_BATTERY_DRIVER.c
 * @author  PRAVEEN SURYAWANSHI (453) && PRIYANKA BORKAR (410)
 * @date   
 * @version 0.1
 */

/*INCLUDEING REQUIRED HEADER FOR THE DERIVER*/
#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <asm/uaccess.h> 
#include<linux/power_supply.h>   //header for the power supply suppoer




/*DEFINING THE REQUIRED MACCROS*/
#define  DEVICE_NAME "ebbchar"    // The device will appear at /dev/ebbchar using this value
#define  CLASS_NAME  "ebb"        // The device class -- this is a character device driver






MODULE_LICENSE("GPL");            // The license type -- this affects available functionality
MODULE_AUTHOR("PRAVEEN & PRIYANKA");    // The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux char driver for the BATTERY DEVICE INFORMATION");  ///< The description -- see modinfo
MODULE_VERSION("0.1");            // A version number to inform users



/*INTIALIZING REQUIRED VARIABLES*/
static int    majorNumber;                  // Stores the device number -- determined automatically
static char   message[2000] = {0};           // Memory for the string that is passed from userspace
static short  size_of_message;              // Used to remember the size of the string stored
static int    numberOpens = 0;              // Counts the number of times the device is opened
static struct class*  ebbcharClass  = NULL; // The device-driver class struct pointer
static struct device* ebbcharDevice = NULL; // The device-driver device struct pointer








/*==============DEFINIFING REQUITED VARIABLE===================================*/
char name[]= "BAT0";
int   b_percentage=0;
int   b_charge_level=0;
char  b_tech[30]={"UNKNOWN"};
char  b_model_name[30]={"UNKNOWN"};
char  b_manufacture_name[30]={"UNKNOWN"};
char  b_serial_number[30]={"UNKNOWN"};	
char  b_health[30]={"UNKNOWN"};
char  b_capacity_level[30]={"UNKNOWN"};
char  b_status[30]={"UNKNOWN"};
char  b_chargetype[30]={"UNKNOWN"};

int result = 0;

struct power_supply *psy;
union power_supply_propval battery;

 
 
/*==============================================================================*/


// The prototype functions for the character driver -- must come before the struct definition
static int     battery_open(struct inode *, struct file *);
static int     battery_release(struct inode *, struct file *);
static ssize_t battery_read(struct file *, char *, size_t, loff_t *);
static ssize_t battery_write(struct file *, const char *, size_t, loff_t *);





/** char devices usually implement open, read, write and release calls , callback functions for file operations
 */
static struct file_operations fops =
{
   .open = battery_open,
   .read = battery_read,
   .write = battery_write,
   .release = battery_release,
};







/**  The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init battery_init(void)
{
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER: IINTIALIZING THE LKM DRIVERn");

   // Try to dynamically allocate a major number for the device -- more difficult but worth it
   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0)
   {
      printk(KERN_ALERT "BATTERY_DEVICE_DRIVER : FAILED TO REGISTER THE MAJOR NUMBER\n");
      return majorNumber;
   }
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER: REGISTERED CORRECTLY WITH MAJOR NUMBBER %d\n", majorNumber);






   // Register the device class
   ebbcharClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(ebbcharClass)){                // Check for error and clean up if there is
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "BATTERY_DEVICE_DRIVER : FAILED TO REGISTER THE DEVICE CLASS\n");
      return PTR_ERR(ebbcharClass);          // Correct way to return an error on a pointer
   }
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER: REGISTERED CORRECTLY WITH DEVICE CLASS ");




   // Register the device driver
   ebbcharDevice = device_create(ebbcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(ebbcharDevice)){               // Clean up if there is an error
      class_destroy(ebbcharClass);           // Repeated code but the alternative is goto statements
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "BATTERY_DEVICE_DRIVER : FAILED TO CREATE DEVICE\n");
      return PTR_ERR(ebbcharDevice);
   }
     printk(KERN_INFO "BATTERY_DEVICE_DRIVER: DEVICE CREATED SUCCESSFULLY !!!! ");// Made it! device was initialized



   return 0;
}








/** The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit battery_exit(void)
{
   device_destroy(ebbcharClass, MKDEV(majorNumber, 0));     // remove the device
   class_unregister(ebbcharClass);                          // unregister the device class
   class_destroy(ebbcharClass);                             // remove the device class
   unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER: GOOD BYE I AM DEAD!!!\n");
}








/**  The device open function that is called each time the device is opened
 *  This will only increment the numberOpens counter in this case.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int battery_open(struct inode *inodep, struct file *filep)
{
   numberOpens++;
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER: DEVICE HAS BEEN OPENED %d TIMES(s)\n", numberOpens);
   return 0;
}








/** This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t battery_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
   int error_count = 0;
   // copy_to_user has the format ( * to, *from, size) and returns 0 on success
   

   error_count = copy_to_user(buffer, message, size_of_message);

   if (error_count==0){            // if true then have success
      printk(KERN_INFO "BATTERY_DEVICE_DRIVER: SENT %d CHARACTER TO THE USERS\n", size_of_message);
      return (size_of_message=0);  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "BATTERY_DEVICE_DRIVER:FAILED %d  TO SEND CHARACTERS TO THE USERS\n", error_count);
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}







/** @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed in the const char buffer
 *  @param offset The offset if required
 */
static ssize_t battery_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
 




/*================CREATING POWER SUPPLY  OBJECT=================================*/
psy = power_supply_get_by_name(name);
/*==============================================================================*/





/*================= INITIALIZING POWER SUPPLY SCOPE=============================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_SCOPE,&battery);
if(!result) 
{
    printk(KERN_INFO "POWER SUPPLY SCOPE : %d\n",battery.intval);
  if(battery.intval==POWER_SUPPLY_SCOPE_UNKNOWN)
      {
           strcpy(b_chargetype,"SCOPE_UNKNOW");
           printk(KERN_INFO "POWER SUPPLY SCOPE IS : SCOPE_UNKNOWN");
      }
else
if(battery.intval==POWER_SUPPLY_SCOPE_SYSTEM)
      {
           strcpy(b_chargetype,"SCOPE_SYSTEM");
           printk(KERN_INFO "POWER SUPPLY SCOPE IS : SCOPE_SYSTEM");
      }
else
if(battery.intval==POWER_SUPPLY_SCOPE_DEVICE)
      {
           strcpy(b_chargetype,"SCOPE_DEVICE");
           printk(KERN_INFO "POWER SUPPLY SCOPE IS : SCOPE_DEVICE");
      }
/*============================================================================== */
}






/*================INTIALIZING POWER SUPPLY CAPICITY=============================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_CAPACITY_LEVEL,&battery);
if(!result) 
{
    printk(KERN_INFO "CAPACITY : %d\n",battery.intval);
  if(battery.intval==POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL)
      {
           strcpy(b_capacity_level,"CRITICAL");
            printk(KERN_INFO "CAPACITY : CRITICAL ");
      }else
if(battery.intval==POWER_SUPPLY_CAPACITY_LEVEL_LOW)
      {
           strcpy(b_capacity_level,"LOW");
            printk(KERN_INFO "CAPACITY : LOW ");
      }else
if(battery.intval==POWER_SUPPLY_CAPACITY_LEVEL_NORMAL)
      {
           strcpy(b_capacity_level,"NORMAL");
            printk(KERN_INFO "CAPACITY : NORMAL ");
      }else
if(battery.intval==POWER_SUPPLY_CAPACITY_LEVEL_HIGH)
      {
           strcpy(b_capacity_level,"HIGH");
            printk(KERN_INFO "CAPACITY : HIGH ");
      }else
if(battery.intval==POWER_SUPPLY_CAPACITY_LEVEL_FULL)
      {
           strcpy(b_capacity_level,"FULL");
            printk(KERN_INFO "CAPACITY : FULL ");
      }
}
/*==============================================================================*/





/*====================INTIALZING STATUS OF BATTERY==============================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_STATUS,&battery);
if(!result) 
{
    printk(KERN_INFO "STATUS : %d\n",battery.intval);
  if(battery.intval==POWER_SUPPLY_CHARGE_TYPE_NONE)
      {
           strcpy(b_status,"NONE");
      printk(KERN_INFO "STATUS : CHARGE TYPE NONE ");
      }else
if(battery.intval==POWER_SUPPLY_CHARGE_TYPE_TRICKLE)
      {
           strcpy(b_status,"TRICKLE");
           printk(KERN_INFO "STATUS : CHARGE TYPE TRICKLE ");
      }else
if(battery.intval==POWER_SUPPLY_CHARGE_TYPE_UNKNOWN)
      {
           strcpy(b_status,"UNKNOWN");
      printk(KERN_INFO "STATUS : CHARGE TYPE UNKNOWN ");
      }else
if(battery.intval==POWER_SUPPLY_CHARGE_TYPE_FAST)
      {
           strcpy(b_status,"FAST");
      printk(KERN_INFO "STATUS : CHARGE TYPE FAST ");
      }
  
}
/*==============================================================================*/





/*=================RETREIVING CHARGE  IN PERCENTAGE============================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_CAPACITY,&battery);
if(!result) {
    printk(KERN_INFO "CHARGE PERCENTAGE : %d\n",battery.intval);
    b_percentage=battery.intval;
}
/*==============================================================================*/





/*==================CHARGE FULL=================================================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_CHARGE_FULL,&battery);
if(!result) {
    printk(KERN_INFO "CHARGE LEVEL : %d\n",battery.intval);
    b_charge_level=battery.intval;
}
/*==============================================================================*/





/*========================= RETREIVING MODEL NAME===============================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_MODEL_NAME,&battery);
if(!result) {
    printk(KERN_INFO "MODEL NAME : %s\n",battery.strval);
    strcpy(b_model_name,battery.strval);
}
/*==============================================================================*/







/*====================RETRIVING MANUFACTURER NAME===============================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_MANUFACTURER,&battery);
if(!result) {
    printk(KERN_INFO "MANUFACTURER : %s\n",battery.strval);  
     strcpy(b_manufacture_name,battery.strval);
}
/*==============================================================================*/






/*================== RETRIVING MODEL NAME=======================================*/
result = psy->get_property(psy,POWER_SUPPLY_PROP_SERIAL_NUMBER,&battery);
if(!result) {
    printk(KERN_INFO "SERIAL NUMBER : %s\n",battery.strval);
    strcpy(b_serial_number,battery.strval);
}
/*==============================================================================*/




/*====================== RETREIVING TECHNOLOGYY USED============================
result = psy->get_property(psy,POWER_SUPPLY_PROP_TECHNOLOGY,&battery);
if(!result) {
    printk(KERN_INFO "TECHNOLOGY : %d\n",battery.intval);

    if(battery.intval==POWER_SUPPLY_TECHNOLOGY_NiMH)
      {
           strcpy(b_tech,"NIMH");
      }else
 if(battery.intval==POWER_SUPPLY_TECHNOLOGY_LION)
      {
           strcpy(b_tech,"LION");
      }else
 if(battery.intval==POWER_SUPPLY_TECHNOLOGY_LIPO)
      {
           strcpy(b_tech,"LIPO");
      }else
 if(battery.intval==POWER_SUPPLY_TECHNOLOGY_LiFe)
      {
           strcpy(b_tech,"LIFE");
      }else
 if(battery.intval==POWER_SUPPLY_TECHNOLOGY_NiCd)
      {
           strcpy(b_tech,"NICD");
      }else
 if(battery.intval==POWER_SUPPLY_TECHNOLOGY_LiMn)
      {
           strcpy(b_tech,"LIMN");
      }
      else
       {
          strcpy(b_tech,"CANT_DETECT_TECHNOLOGY");
       }
}
==============================================================================*/



/*================= RETREVING  HEALTH==========================================
result = psy->get_property(psy,POWER_SUPPLY_PROP_HEALTH,&battery);
if(!result) {
    printk(KERN_INFO "HEALTH : %d\n",battery.intval);
    if(battery.intval==POWER_SUPPLY_HEALTH_GOOD)
     {
       strcpy(b_health,"GOOD_HEALTH");
      printk(KERN_INFO "HEALTH : GOOD ");
     }else
 if(battery.intval==POWER_SUPPLY_HEALTH_OVERHEAT)
     {
       strcpy(b_health,"OVER_HEATED");
      printk(KERN_INFO "HEALTH : OVER HEATED ");
     }else
 if(battery.intval==POWER_SUPPLY_HEALTH_DEAD)
     {
       strcpy(b_health,"HEALTH_DEAD");
      printk(KERN_INFO "HEALTH : HEALTH DEAD ");
     }else
 if(battery.intval==POWER_SUPPLY_HEALTH_OVERVOLTAGE)
     {
       strcpy(b_health,"OVER_VOLTAGE");
      printk(KERN_INFO "HEALTH : OVER_VOLTAGE ");
     }else
 if(battery.intval==POWER_SUPPLY_HEALTH_UNSPEC_FAILURE)
     {
       strcpy(b_health,"UNSPECIFIED_POWER_FAILURE");
      printk(KERN_INFO "HEALTH : UNSPECIFIED POWER FAILURE ");
     }else
 if(battery.intval==POWER_SUPPLY_HEALTH_COLD)
     {
       strcpy(b_health,"COLD");

      printk(KERN_INFO "HEALTH : COLD ");
     }else
 if(battery.intval==POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE)
     {
       strcpy(b_health,"WATCHDOG_TIME_EXPIRE");
      printk(KERN_INFO "HEALTH : WATCH TIME EXPIRE ");
     }else
  if(battery.intval==POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE)
     {
       strcpy(b_health,"SAFETY_TIME_EXPIRE");
      printk(KERN_INFO "HEALTH : SAFETY TIME EXPIRE ");
     }else
     {
      strcpy(b_health,"CANT_DETECT_HEALTH");
      printk(KERN_INFO "HEALTH : CANT DETECT HEALTH ");
     }
 }
==============================================================================*/

  
 sprintf(message,
         "%d %d %d %s %s %s %s %s %s %s %s",
      numberOpens,
      b_percentage,
      b_charge_level,
      b_tech,
      b_model_name,
      b_manufacture_name,
      b_serial_number,
      b_health,
      b_capacity_level,
      b_status,
      b_chargetype
      );

 //strcat(buffer,s); 
  //sprintf(message, "%d,%d)",chargenow.intval,chargefull.intval);  
 // appending received string with its length
   size_of_message = strlen(message);
   
                 // store the length of the stored message
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER: RECEIVED %d  CHARACTER FROM THE USER\n", len);
   return len;
}







/** @brief The device release function that is called whenever the device is closed/released by
 *  the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int battery_release(struct inode *inodep, struct file *filep)
{
   printk(KERN_INFO "BATTERY_DEVICE_DRIVER : DEVICE SUCCESSFULLY CLOSED\n");
   return 0;
}







/**  A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(battery_init);
module_exit(battery_exit);
