#@copyright : Mohamed Nagy

TCH=arm-none-eabi-
OPT=-mcpu=cortex-m3 -gdwarf-2 -g
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
Project_Name=TestLab_1

all: $(Project_Name).bin $(Project_Name).hex
	@echo "==================Build is done=================="
	
%.o: %.c
	$(TCH)gcc.exe $(OPT) $(INCS) -c  $< -o $@
	
%.o: %.s
	$(TCH)as.exe $(OPT) $< -o $@
	
$(Project_Name).elf: $(OBJ) $(AsOBJ) 
	$(TCH)ld.exe -T LinkerScript.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	cp $@ $(Project_Name).axf
	
$(Project_Name).bin: $(Project_Name).elf
	$(TCH)objcopy.exe -O binary $< $@
	
$(Project_Name).hex: $(Project_Name).elf
	$(TCH)objcopy.exe -O ihex $< $@
	
clean_all:
	rm *.o *.elf *.axf *.bin *.hex *.map 
	@echo "==================All Clean=================="

clean:
	rm *.elf *.axf *.bin *.hex *.map 
	@echo "==================Clean=================="