#include<stdio.h>
#include<stdlib.h>


int main()


{
 int num_decimal, mil, mil_1, centena, centena_1, dezena, dezena_1;
 system("color f1"); 
 printf("Digite o numero em decimal: ");
 scanf("%d", &num_decimal);
 printf("\nO Numero em romano eh: ");
       
     
       mil = num_decimal / 1000;
       mil_1 = num_decimal % 1000;
       switch (mil)
         {
              case 1: printf("M"); 
                       break;
              case 2: printf("MM");
                        break;
              case 3: printf("MMM");
                        break;
              
          }
       centena = mil_1/100;
       centena_1 = mil_1%100;
      
        switch(centena)
        {
              case 1: printf("C");
                   break;
              case 2: printf("CC");
                   break;
              case 3: printf("CCC");
                   break;       
              case 4: printf("CD");
                   break;
              case 5: printf("D");
                   break;
              case 6: printf("DC");
                   break;
              case 7: printf("DCC");
                   break;
              case 8: printf("DCCC");
                   break;
              case 9: printf("CM");
                   break;
      
       }
        dezena = centena_1/10;
        dezena_1 = centena_1%10;
       
        switch(dezena)
        {
              case 1: printf("X");
                   break;
              case 2: printf("XX");
                   break;
              case 3: printf("XXX");
                   break;       
              case 4: printf("XL");
                   break;
              case 5: printf("L");
                   break;
              case 6: printf("LX");
                   break;
              case 7: printf("LXX");
                   break;
              case 8: printf("LXXX");
                   break;
              case 9: printf("XC");
                   break;
           }
                     
        switch (dezena_1)
         {
               case 1: printf("I");
                   break;
              case 2: printf("II");
                   break;
              case 3: printf("III");
                   break;       
              case 4: printf("IV");
                   break;
              case 5: printf("V");
                   break;
              case 6: printf("VI");
                   break;
              case 7: printf("VII");
                   break;
              case 8: printf("VIII");
                   break;
              case 9: printf("IX");
                   break;
         }
system("pause>>null"); 
return 0;
}
