#include "kernel.h"

#include "std_lib.h"





int main() {

    char buf[128];

    clearScreen();

    printString("Welcome to MengOS\n\r");

    while (1) {

        printString("$ ");

        readString(buf);

        printString(buf);

        printString("\r\n");

    }

    return 0;

}





void printString(char* str) {

    int i = 0;

    int len = strlen(str);

    for(i = 0; i < len; i++){

         interrupt(0x10, 0x0e << 8 | str[i], 0, 0, 0);

        //  if(len - 1){

        //     interrupt(0x10, 0x0e << 8 | 13, 0, 0, 0);

        //  }

    }

    // interrupt(0x10, 0x0e << 8 | 13, 0, 0, 0);

    

}

void readString(char* buf) {

    char* pointer = buf;

    char words;

    // printString("\r\n");

    while (1) {

        words = interrupt(0x16, 0, 0, 0, 0);

        if(words == '\r'){ 

            *pointer = '\0'; 

            //  printString("\r");

            break;

        }

        else if (words == '\b') { 

            if(pointer > buf){

                pointer--;

                printString("\b \b"); 

            }

        }

        else if (words >= 32 && words <= 126){ // dari spasi sampe abis

            *pointer++ = words;

            interrupt(0x10, 0x0E00 | words, 0, 0, 0); 

        }

    }

    printString("\r\n");
// interrupt(0x10, 0x0e << 8 | 10, 0, 0, 0);

}



void clearScreen(){
    int i, j;
    for(i = 0; i < 25; i++){
        for(j = 0; j < 80; j++){
            putInMemory(0xB800, 2 * (i * 80 + j), ' ');
            putInMemory(0xB800, 2 * (i * 80 + j) + 1, 0x07);
        }
    }
    // Move cursor to (0, 0)
    interrupt(0x10, 0x0200, 0, 0, 0);
}



