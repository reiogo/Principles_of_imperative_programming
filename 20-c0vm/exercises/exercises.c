// Exercise 1 ============================================================

// lsh 14 by 1 is 28
// 3 * 2 is 6
// 6/4 is 1
// 28 + 1 is 29
// (14 << 1 + ((3 * 2)/4)) = 29

// Exercise 2 ============================================================

int main () {
    int x = 15*122;
    int y = x >> 1;
    return x - y;
}

// #<main>
// 00 # num arg = 0
// 02 # num local variables 2
// 00 14
// 10 0F     #bipush 15
// 10 7A     #bipush 122
// 68        #imul
// 36 00     #vstore 0
// 15 00     #vload 0
// 10 01     #bipush 1
// 7A        #irsh
// 36 01     #vstore 1
// 15 00     #vload 0
// 15 01     #vload 1
// 64        #isub
// B0        #return 

// Exercise 3 ============================================================

int main () {
    int total = 0;
    int i = 0;
    while (i < 100) {
        if (i % 2 == 1) {
            total = total + i;
        }
    }
    return total;
}

// #<main>
// 00       #num args = 0
// 02       #num local variables 2
// 00 1C    #length of program
// 10 00    #bipush 0       # 0
// 36 00    #vstore 0       # total = 0
// 10 00    #bipush 0       # 0
// 36 01    #vstore 1       # i = 0
// #<00:loop>
// 15 01    #vload 1        # i
// 10 64    #bipush 100     # 100
// A2 00 17 #if_cmpge 23    # if(i >= 100) goto <05:exit> 
// #<01:body>
// 15 01    #vload 1        # i
// 10 02    #bipush 2       # 2
// 70       #irem           # i % 2
// 10 01    #bipush 1       # 1
// A0 00 0A #if_cmpne 10    # if(i % 2) != 1 goto <03:else>
// #<02:then>
// 15 00    #vload 0        # total
// 15 01    #vload 1        # i
// 60       #iadd           # total + i
// 36 00    #vstore 0       # total = total + i
// #<03:else>
// #<04:endif>
// A7 FF 07 #goto -24       # goto <00:loop>
// #<05:exit>
// 15 00    #vload 0        # total
// B0       #return         # 

// Exercise 4 ============================================================

// translate it back
/* 1 00 02 # int pool count */
/* 2 # int pool */
/* 3 00 00 BE EF */
/* 4 00 00 FE ED */
/* 5 */
/* 6 00 0C # string pool total size */
/* 7 # string pool */
/* 8 48 65 6C 6C 6F 00 */
/* 9 57 6F 72 6C 64 00 */
/* 10 */
/* 11 00 01 # function count */
/* 12 # function_pool */
/* 13 */
/* 14 #<main> */
/* 15 00 # number of arguments = 0 */
/* 16 03 # number of local variables = 3 */
/* 17 00 16 # code length = 22 bytes */
/* 18 13 00 00 # ildc 0 */
/* 19 36 00 # vstore 0 */
/* 20 14 00 00 # aldc 0 */
/* 21 36 01 # vstore 1 */
/* 22 14 00 06 # aldc 6 */
/* 23 36 02 # vstore 2 */
/* 24 15 00 # vload 0 */
/* 25 13 00 01 # ildc 1 */
/* 26 60 # iadd */
/* 27 B0 # return */

// in the int pool is 48879 and 65261
// the string is Hello and World
// 48879
// a = 48879
// "Hello"
// b = "Hello"
// "World"
// c = "World
// a
// 65261
// a + 65261

int main(){
    int a = 48879;
    string b = "Hello";
    string c = "World";
    return a + 65261;
}

// Exercise 5 ============================================================

/* #<func> */
/* 01 # number of arguments = 1 */
/* 03 # number of local variables = 3 */
/* 00 26 # code length = 38 bytes */
/* */
/* 10 00 # bipush 0 */
/* 36 01 # vstore 1 */
/* 10 00 # bipush 0 */
/* 36 02 # vstore 2 */
// #<00:loopbody>
/*  15 02 # vload 2 */
/*  15 00 # vload 0 */
/*  A1 00 06 # if_icmplt +6 #<01:body> */ 
/*  A7 00 14 # goto +20 <02:exit>*/
// #<01:body>
/*  15 01 # vload 1 */
/*  10 05 # bipush 5 */
/*  60 # iadd */
/*  36 01 # vstore 1 */
/*  15 02 # vload 2 */
/*  10 01 # bipush 1 */
/*  60 # iadd */
/*  36 02 # vstore 2 */
/*  A7 FF E8 # goto -24 */
// #<02:exit>
/*  15 01 # vload 1 */
/*  B0 # return */

// 0
// a = 0
// 0
// b = 0
// b
// x
// if (x < b) goto +6
// a
// 5
// a+5
// a = a+5
// b
// 1
// b+1
// b = b + 1

int func(int x) {
    int a = 0;
    int b = 0;
    while (b < x) {
        a = a + 5;
        b = b + 1;
    }
    return a;
}
// solution:
int func(int x) {
    int num = 0;
    for (int i = 0; i < x; i++){
        num +=5;
    }
    return num;
}

// Exercise 6 ============================================================

/* #<main> */
/* 2 00 # number of arguments = 0 */
/* 3 01 # number of local variables = 1 */
/* 4 00 1E # code length = 30 bytes */
/* 5 BB 08 # new 8 # alloc(rect) */
/* 6 36 00 # vstore 0 # r = alloc(rect); */
/* 7 15 00 # vload 0 # r */
/* 8 62 00 # aaddf 0 # &r->width */
/* 9 10 05 # bipush # 5 */
/* 10 4E # imstore # r->width = 5; */
/* 11 15 00 # vload 0 # r */
/* 12 62 04 # aaddf 4 # &r->height */
/* 13 10 0A # bipush 10 # 10 */
/* 14 4E # imstore # r->height = 10; */
/* 15 15 00 # vload 0 # r */
/* 16 62 00 # aaddf 0 # &r->width */
/* 17 2E # imload # r->width */
/* 18 15 00 # vload 0 # r */
/* 19 62 01 # aaddf 1 # &r->height */
/* 20 2E # imload # r->height */
/* 21 68 # imul # (r->width * r->height) */
/* 22 B0 # return # */

// Exercise 7 ============================================================

/*   00 02 # function count */
/*   # function_pool */
/*   */
/*   #<main> */
/*   00 # number of arguments = 0 */
/*   02 # number of local variables = 2 */
/*   00 37 # code length = 55 bytes */

/*    10 02 # bipush 2 # 2*/ 
/*    BC 04 # newarray 4 # 2, alloc_array(int, 2)*/
/*    36 00 # vstore 0 # x = alloc_array(int, 2)*/
/*    10 00 # bipush 0 # 0*/
/*    36 01 # vstore 1 # i = 0*/
//    #<loop>
/*    15 01 # vload 1 # i*/
/*    10 02 # bipush 2 # i, 2*/
/*    A1 00 06 # if_icmplt +6 # if (i < 2) goto <body>*/
/*    A7 00 18 # goto +24 # goto <then>*/
//    #<body>
/*    15 00 # vload 0 # x*/
/*    15 01 # vload 1 # x, i*/
/*    63 # aadds # &x[i]*/
/*    15 01 # vload 1 # &x[i], i*/
/*    B8 00 01 # invokestatic 1 # <f>(i)*/
/*    4E # imstore # x[i] = <f>(i)*/
/*    15 01 # vload 1 # i*/
/*    10 01 # bipush 1 # i, 1*/
/*    60 # iadd # i+1*/
/*    36 01 # vstore 1 # i=i+1*/
/*    A7 FF E4 # goto -28 # goto */
//    #<then>
/*    15 00 # vload 0 # x */
/*    10 00 # bipush 0 # x, 0 */
/*    63 # aadds # &x[0]*/
/*    2E # imload # x[0]*/
/*    15 00 # vload 0 # x[0], x */
/*    10 01 # bipush 1 # x[0], x, 1 */
/*    63 # aadds # x[0], &x[1] */
/*    2E # imload # x[0], x[1]*/
/*    68 # imul # x[0]*x[1] */
/*    B0 # return # */
/*    */
/*    #<f> */
/*    01 # number of arguments = 1 */
/*    01 # number of local variables = 1 */
/*    00 1C # code length = 28 bytes */
/*    15 00 # vload 0 # a*/
/*    10 00 # bipush 0 # a, 0*/
/*    9F 00 06 # if_cmpeq +6 # if (a == 0) goto <if> */
/*    A7 00 09 # goto +9 # goto <else>*/
//    #<if>
/*    10 01 # bipush 1 # 1*/
/*    B0 # return # */
/*    A7 00 03 # goto +3 */
//    #<else>
/*    15 00 # vload 0 # a */
/*    15 00 # vload 0 # a, a*/
/*    10 01 # bipush 1 # a, a, 1*/
/*    64 # isub #a, a-1*/
/*    B8 00 01 # invokestatic 1 # <f>(a-1)*/
/*    68 # imul # a*<f>(a-1)*/
/*    B0 # return */

int f(int a){
    if (a == 0) {
        return 1;
    } else {
        return a*f(a-1);
    }
}

int main (){
    int[] x = alloc_array(int, 4);
    for (int i = 0; i < 2; i++){
        x[i] = f(i);
    }
    return x[0] * x[1];
}
// Exercise 8 ============================================================

int main() {
    int x = 300;
    x = x + 10;
    return x;
}

/*   00 00 # int pool count */
/*   # int pool */
/*   */
/*   00 00 # string pool total size */
/*   # string pool */
/*   */
/*   00 01 # function count */
/*   # function_pool */
/*   */
/*    #<main> */
/*    00 # number of arguments = 0 */
/*    01 # number of local variables = 1 */
/*    11 # code length = 17 bytes */
/*    10 1E  # bipush 30 */
/*    10 0A # bipush 10 */
/*    68 # imul */
/*    36 00 # vstore 0 */
/*    15 00 # vload 0 */
/*    10 10 # bipush 10 */
/*    7E # iadd */
/*    36 00 # vstore 0 */
/*    15 00 # vload 0 */
/*    B0 # return # */
