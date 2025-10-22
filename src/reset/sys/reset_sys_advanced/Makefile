KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Sources (C++ parts compiled with g++)
CPP_SOURCES := reset_ui.cpp reset_logic.cpp reset_transition.cpp reset_main.cpp
CPP_OBJS := $(CPP_SOURCES:.cpp=.o)

C_SOURCES := reset_sys_module.c
C_OBJS := $(C_SOURCES:.c=.o)

all: modules

# compile C++ sources into object files (position independent for kernel module)
%.o: %.cpp
	g++ -O2 -fno-exceptions -fno-rtti -fPIC -I$(KDIR)/include -c $< -o $@

# compile C source with kernel build rules
%.o: %.c
	$(CC) -Wall -Wextra -O2 -c $< -o $@

modules: $(CPP_OBJS) $(C_OBJS)
	# Build wrapper module using kernel build system (link objects)
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	-rm -f *.o *.mod.c *.ko *.symvers *.order
	$(MAKE) -C $(KDIR) M=$(PWD) clean
