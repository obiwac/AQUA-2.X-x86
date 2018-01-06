
#include "scan.h"

void basic_scan(char* buffer) {
	char buff;
    uint8_t i = 0;
    uint8_t reading = 1;
    while(reading)
    {
        if(inportb(0x64) & 0x1)                 
        {
            switch(inportb(0x60))
            { 
      /*case 1:
                printf("(char)27);           Escape button
                buffer[i] = (char)27;
                i++;
                break;*/
        case 2:
                printf("1");
                buffer[i] = '1';
                i++;
                break;
        case 3:
                printf("2");
                buffer[i] = '2';
                i++;
                break;
        case 4:
                printf("3");
                buffer[i] = '3';
                i++;
                break;
        case 5:
                printf("4");
                buffer[i] = '4';
                i++;
                break;
        case 6:
                printf("5");
                buffer[i] = '5';
                i++;
                break;
        case 7:
                printf("6");
                buffer[i] = '6';
                i++;
                break;
        case 8:
                printf("7");
                buffer[i] = '7';
                i++;
                break;
        case 9:
                printf("8");
                buffer[i] = '8';
                i++;
                break;
        case 10:
                printf("9");
                buffer[i] = '9';
                i++;
                break;
        case 11:
                printf("0");
                buffer[i] = '0';
                i++;
                break;
        case 12:
                printf("-");
                buffer[i] = '-';
                i++;
                break;
        case 13:
                printf("=");
                buffer[i] = '=';
                i++;
                break;
        case 14:
                printf("\b");
                i--;
                buffer[i] = 0;
                break;
       /* case 15:
                printf("\t");          Tab button
                buffer[i] = '\t';
                i++;
                break;*/
        case 16:
                printf("q");
                buffer[i] = 'q';
                i++;
                break;
        case 17:
                printf("w");
                buffer[i] = 'w';
                i++;
                break;
        case 18:
                printf("e");
                buffer[i] = 'e';
                i++;
                break;
        case 19:
                printf("r");
                buffer[i] = 'r';
                i++;
                break;
        case 20:
                printf("t");
                buffer[i] = 't';
                i++;
                break;
        case 21:
                printf("y");
                buffer[i] = 'y';
                i++;
                break;
        case 22:
                printf("u");
                buffer[i] = 'u';
                i++;
                break;
        case 23:
                printf("i");
                buffer[i] = 'i';
                i++;
                break;
        case 24:
                printf("o");
                buffer[i] = 'o';
                i++;
                break;
        case 25:
                printf("p");
                buffer[i] = 'p';
                i++;
                break;
        case 26:
                printf("[");
                buffer[i] = '[';
                i++;
                break;
        case 27:
                printf("]");
                buffer[i] = ']';
                i++;
                break;
        case 28:
               // printf("\n");
               // buffer[i] = '\n';
                  i++;
               reading = 0;
                break;
      /*  case 29:
                printf("q");           Left Control
                buffer[i] = 'q';
                i++;
                break;*/
        case 30:
                printf("a");
                buffer[i] = 'a';
                i++;
                break;
        case 31:
                printf("s");
                buffer[i] = 's';
                i++;
                break;
        case 32:
                printf("d");
                buffer[i] = 'd';
                i++;
                break;
        case 33:
                printf("f");
                buffer[i] = 'f';
                i++;
                break;
        case 34:
                printf("g");
                buffer[i] = 'g';
                i++;
                break;
        case 35:
                printf("h");
                buffer[i] = 'h';
                i++;
                break;
        case 36:
                printf("j");
                buffer[i] = 'j';
                i++;
                break;
        case 37:
                printf("k");
                buffer[i] = 'k';
                i++;
                break;
        case 38:
                printf("l");
                buffer[i] = 'l';
                i++;
                break;
        case 39:
                printf(";");
                buffer[i] = ';';
                i++;
                break;
        case 40:
                printf("%c", (char)44);               //   Single quote (")
                buffer[i] = (char)44;
                i++;
                break;
        case 41:
                printf("%c", (char)44);               // Back tick (`)
                buffer[i] = (char)44;
                i++;
                break;
     /* case 42:                                 Left shift 
                printf("q");
                buffer[i] = 'q';
                i++;
                break;
        case 43:                                 \ (< for somekeyboards)   
                printf((char)92);
                buffer[i] = 'q';
                i++;
                break;*/
        case 44:
                printf("z");
                buffer[i] = 'z';
                i++;
                break;
        case 45:
                printf("x");
                buffer[i] = 'x';
                i++;
                break;
        case 46:
                printf("c");
                buffer[i] = 'c';
                i++;
                break;
        case 47:
                printf("v");
                buffer[i] = 'v';
                i++;
                break;                
        case 48:
                printf("b");
                buffer[i] = 'b';
                i++;
                break;               
        case 49:
                printf("n");
                buffer[i] = 'n';
                i++;
                break;                
        case 50:
                printf("m");
                buffer[i] = 'm';
                i++;
                break;               
        case 51:
                printf(",");
                buffer[i] = ',';
                i++;
                break;                
        case 52:
                printf(".");
                buffer[i] = '.';
                i++;
                break;            
        case 53:
                printf("/");
                buffer[i] = '/';
                i++;
                break;            
        case 54:
                printf(".");
                buffer[i] = '.';
                i++;
                break;            
        case 55:
                printf("/");
                buffer[i] = '/';
                i++;
                break;            
      /*case 56:
                printf(" ");           Right shift
                buffer[i] = ' ';
                i++;
                break;*/           
        case 57:
                printf(" ");
                buffer[i] = ' ';
                i++;
                break;
            }
        }
    }
    buffer[i] = 0;
	
}
