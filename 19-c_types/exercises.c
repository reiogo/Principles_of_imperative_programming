// Exercise 1 ==============================================================

short x;
unsigned int y;
x = (unsigned short) x;
y = (unsigned int) x;

// or
short x;
unsigned int y = (unsigned int) (unsigned short) x;

// Exercise 2 ==============================================================

/* Assume that char is 1 byte, short is 2 bytes, and int is 4 bytes, */
/* as well as gcc implementation of casting, where going to a smaller */ 
/* size just truncates the bits to fit. */

/* int x = -15122; whose bit pattern is 0xFFFFC4EE. */
/* -15122 0xC4EE (short)x */
/* 4294952174 0xFFFFC4EE (unsigned int)x */
/* 50414 0xC4EE (unsigned short)x */
/* -18 0xFFEE (short)(signed char)x */

// Exercise 3 ==============================================================

/*Find the implementation defined casts. Assume that a char is 1 byte, a */
/* short is 2 bytes, an int is 4 bytes, and a long is 8 bytes */

/* int x = 15122; 0x0000C4EE */
/* char c = (char)x; 0xEE This one*/
/* unsigned short s = x; 0x00EE */ 
/* unsigned int y = x; 0x000000EE*/
/* long l = (long)x; 0x00000000000000EE*/
/* unsigned long k = (unsigned int)x; 0x00000000000000EE */
/* uint64_t z = x; 0x00000000000000EE */

// Exercise 4 ==============================================================

/* For the integers 1, 3, 6, */
/* 10, and 12, what would the function return? */
char *month_to_string(int month) {
    char *month_string;
    switch (month) {
        case 1:
            month_string = "January";
            break;
        case 2:
            month_string = "February";
            break;
        case 3:
            month_string = "March";
        case 4:
            month_string = "April";
            break;
        case 5:
            month_string = "May";
            break;
        case 6:
            month_string = "June";
            break;
        case 7:
            month_string = "July";
            break;
        case 8:
            month_string = "August";
            break;
        case 9:
            month_string = "September";
            break;
        case 10:
            month_string = "October";
        case 11:
            month_string = "November";
        case 12:
            month_string = "December";
        default:
            month_string = "Invalid Month";
    }
    return month_string;
}

//January, March, June, October, December
// Solution: You got me. October and December return Invalid Month
