/**********************************************************                                                                                       
 * mywc.c                                                                                                              
 * count the number of words in file                                                                                                    
 * Author: Yaokun Zhang                                                                                                                           
 * Date Created: Sep 1, 2017                                                                                                                      
 * Last Modified by: Yaokun Zhang                                                                                                                 
 * Date Last Modified: Sep 7, 2017                                                                                                                
 * Assignment: Lab2                                                                                                                      
 * Part of: C335 assignment                                                                                                                       
 */
#include<stdio.h>
int main(void){
int c;
int count_Lines;
int count_Words;
int count_Char = 0;

while((c = getchar()) != EOF){
	if(c == '\n'){
		count_Lines++;
	}if(c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\f' || c == '\v'){
		count_Words++;
	}
	count_Char++;
}
	printf("%d ", count_Lines);
	printf("%d ", count_Words);
	printf("%d\n", count_Char);
}
