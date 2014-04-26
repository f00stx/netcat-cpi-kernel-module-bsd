# Declare Name of kernel module
KMOD    =  netcatbsd 

# Enumerate Source files for kernel module
SRCS    = netcatbsd.c

# Include kernel module makefile
.include <bsd.kmod.mk>
