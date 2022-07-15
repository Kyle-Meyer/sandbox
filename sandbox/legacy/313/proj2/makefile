FILE  = encrypt
FILE2 =	validate
FILE3 =	shift
FILE4 =	mirror

all: $(FILE)

$(FILE): $(FILE).asm
	nasm -f elf64 -l $(FILE).lst $(FILE).asm
	gcc -m64 -o $(FILE) $(FILE).o
two: $(FILE).asm $(FILE2).asm
	nasm -f elf64 -l $(FILE).lst $(FILE).asm
	nasm -f elf64 -l $(FILE2).lst $(FILE2).asm
	gcc -m64 -o $(FILE) $(FILE2).o $(FILE).o

three: $(FILE).asm $(FILE2).asm $(FILE3).asm
	nasm -f elf64 -l $(FILE).lst $(FILE).asm
	nasm -f elf64 -l $(FILE2).lst $(FILE2).asm
	nasm -f elf64 -l $(FILE3).lst $(FILE3).asm
	gcc -m64 -o $(FILE) $(FILE2).o $(FILE3).o $(FILE).o 

four: $(FILE).asm $(FILE2).asm $(FILE3).asm $(FILE4).asm
	nasm -f elf64 -l $(FILE).lst $(FILE).asm
	nasm -f elf64 -l $(FILE2).lst $(FILE2).asm
	nasm -f elf64 -l $(FILE3).lst $(FILE3).asm
	nasm -f elf64 -l $(FILE4).lst $(FILE4).asm
	gcc -m64 -o $(FILE) $(FILE2).o $(FILE3).o $(FILE4).o $(FILE).o 

run: $(FILE)
	./$(FILE) # > hello_64.out

clean: 
	rm *.o  *.lst

debug: $(FILE)
	gdb $(FILE)
