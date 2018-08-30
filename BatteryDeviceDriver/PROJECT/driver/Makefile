CONFIG_MODULE_SIG=y
CONFIG_MODULE_SIG_ALL=y
#CONFIG_MODULE_SIG_SHA512=y
#CONFIG_MODULE_SIG_HASH="sha1"
obj-m += my_battery_driver.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

