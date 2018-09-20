

/**********************************************************                   
 * hw3.c                                                                     
 * main                                                                     
 * Author: Yaokun Zhang
 * Username: yaokzhan                                                    
 * Date Created: Oct 28, 2017                                     
 * Last Modified by: Yaokun Zhang                                              
 * Date Last Modified: Oct 28, 2017                                          
 * Assignment: HW3                                                      
 * Part of: C335 assignment                                   
 */
#include <stdio.h>
#define Rm(x) (((x) >> 3) & 7) //macro
#define Rdn(x) ((x) & 7) //macro
#define op(x) (((x) >> 6) & 15) //macro
#define Rd(x) ((x) & 7) //macro
#define Rn(x) (((x) >> 3) & 7) //macro
#define Rmc(x) (((x) >> 6) & 7) //macro
#define opc(x) (((x) >> 9) & 1) //macro
int main(){
  printf(".text\n");
  printf(".syntax unified\n");
  printf(".thumb\n");

  int inst, rest;
  int opc, rn, rd;
  char *regnames[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
  char *opname[] = {"ands","eors","lsls","lsrs","asrs","adcs","sbcs","rors","tsts","rsbs","cmps","cmns","orrs","muls","bics","mvns"};
  char *opcname[] = {"adds", "subs"};

  while(scanf("%x", &inst) == 1){
    rest = inst >> 10; //get rest of data 
    switch(rest){
    case 6: // if it's 000110
      printf("\t%s %s,%s,%s\n", opcname[opc(inst)], regnames[Rd(inst)],regnames[Rn(inst)],regnames[Rmc(inst)]);
      break;
    case 16: //if it's 010000
      printf("\t%s %s,%s\n", opname[op(inst)], regnames[Rdn(inst)],regnames[Rm(inst)]);
    }
  }
  return 0;
}
    
