#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>



/*
Note: Input file has to be in the same format ;
*/

/* main function */
void main()
{

  char mnemonic[15][15]={"LDA","STA","LDCH","STCH","ADD","SUB","MUL","DIV","J","JSUB"};

  char arr[10],ad[10],for_label[10],for_opcode[10],for_operand[10],for_symbol_table[10],ch,file_name[15],arr1[15];

  int string,for_diff,for_diff1,j,for_addr,for_addr1,addr,length,arr_len,fin_address,previous_addr,x=0;

  int loct_counter=0x0,begin,s,c=0x0,l=0,a=0;

  char code[15][15]={"00","0C","50","54","28","29","3A","3B","3E","3F"};

/* file pointer */
  FILE *file_pointer1,*file_pointer2,*file_pointer3,*file_pointer4;

//printf("ENTER FILE NAME  : \n");

//scanf("%s",&file_name);

  file_pointer1 = fopen("mediator.txt","w");

  file_pointer3 = fopen("input.txt","r");

 printf("\n\n\t\t\tINPUT FILE:\n\n");

  ch=fgetc(file_pointer3);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(file_pointer3);
  }
 rewind(file_pointer3);
 
printf("\n\nStarting For Pass 1 ");

file_pointer2=fopen("symbol_table.txt","w");
  fscanf(file_pointer3,"%s%s%s%X",for_label,for_opcode,for_operand,&for_addr);
    if(strcmp(for_operand,"START")==0)
    {
            begin=for_addr;
            loct_counter=begin;
            previous_addr=loct_counter;
            c=for_addr;
        fprintf(file_pointer1,"%s\t%s\t%X\n",for_opcode,for_operand,for_addr);
    }
    else
        loct_counter=0x0;
fscanf(file_pointer3,"%s%s%s",for_label,for_opcode,for_operand);
while(strcmp(for_opcode,"END")!=0)
  {
      if(strcmp(for_label,"**")!=0)
        fprintf(file_pointer2,"%s\t%X\n",for_label,loct_counter);

        if(strcmp(for_opcode,"BYTE")==0)
            {
                fprintf(file_pointer1,"%X\t%s\t%s\t%s\t\n",for_addr,for_label,for_opcode,for_operand);
                length=strlen(for_operand);
                for_addr+=length-3;
                loct_counter+=length-3;
            }
            else if(strcmp(for_opcode,"RESB")==0)
           {
                fprintf(file_pointer1,"%X\t%s\t%s\t%s\n",for_addr,for_label,for_opcode,for_operand);
                for_addr+=(atoi(for_operand));
                loct_counter+=(atoi(for_operand));
           }
    else if (strcmp(for_opcode,"RESW")==0)
    {
        fprintf(file_pointer1,"%X\t%s\t%s\t%s\n",for_addr,for_label,for_opcode,for_operand);
        for_addr+=(3*(atoi(for_operand)));
         loct_counter+=(3*(atoi(for_operand)));
    }
   else
   {
      fprintf(file_pointer1,"%X\t%s\t%s\t%s\n",for_addr,for_label,for_opcode,for_operand);
       for_addr+=3;
       loct_counter+=3;
   }
   fscanf(file_pointer3,"%s%s%s",for_label,for_opcode,for_operand);
  }
  fprintf(file_pointer1,"%X\t%s\t%s\t%s\n",for_addr,for_label,for_opcode,for_operand);
  s=for_addr;
  fclose(file_pointer1);
  fclose(file_pointer2);
  fclose(file_pointer3);
    printf("\n\nINTERMEDIATE FILE  : AFTER ADRESSING \n\n\t");
  file_pointer1=fopen("mediator.txt","r");
  ch=fgetc(file_pointer1);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(file_pointer1);
  }
  fclose(file_pointer1);
  printf("\n\nTHE LENGTH OF THE PROGRAM IS : %X",s-c);
//ADDRESSING DONE IN mediator FILE;
//AFTER ADDRESING :
printf("\n\nSYMBOL TABLE CREATED");
  printf("\n\n\t\t\tSYMBOL TABLE :\n\n");
  file_pointer2=fopen("symbol_table.txt","r");
  ch=fgetc(file_pointer2);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(file_pointer2);
  }
fclose(file_pointer2);
printf("\n\nEND OF PASS 1");
printf("\n\nSTART OF PASS 2 ");
 file_pointer1 = fopen("otp.txt","w");
  file_pointer2 = fopen("symbol_table.txt","r");
  file_pointer3 = fopen("mediator.txt","r");
  file_pointer4 = fopen("object_code.txt","w");

  fscanf(file_pointer3,"%s%s%s",for_label,for_opcode,for_operand);

  while(strcmp(for_opcode,"END")!=0)
  {
   previous_addr=for_addr;
   fscanf(file_pointer3,"%X%s%s%s",&for_addr,for_label,for_opcode,for_operand);
  }

  fin_address=for_addr;
  fclose(file_pointer3);

 file_pointer3=fopen("mediator.txt","r");

  fscanf(file_pointer3,"%s%s%s",for_label,for_opcode,for_operand);
  if(strcmp(for_opcode,"START")==0)
  {
   fprintf(file_pointer1,"\t%s\t%s\t%s\n",for_label,for_opcode,for_operand);
   fprintf(file_pointer4,"H^%s^00%s^00%X\n",for_label,for_operand,fin_address);
   fscanf(file_pointer3,"%X%s%s%s",&for_addr,for_label,for_opcode,for_operand);
   string=for_addr;
   for_diff=previous_addr-string;
    fprintf(file_pointer4,"T^00%X^%X",for_addr,for_diff);
  }
  while(strcmp(for_opcode,"END")!=0)
  {
   if(strcmp(for_opcode,"BYTE")==0)
   {
    fprintf(file_pointer1,"%X\t%s\t%s\t%s\t",for_addr,for_label,for_opcode,for_operand);
    length=strlen(for_operand);
    arr_len=length-3;
    fprintf(file_pointer4,"^");
    for(j=2;j<(arr_len+2);j++)
    {
     itoa(for_operand[j],ad,16);
     fprintf(file_pointer1,"%s",ad);
     fprintf(file_pointer4,"%s",ad);
    }
    fprintf(file_pointer1,"\n");
   }
   else if(strcmp(for_opcode,"WORD")==0)
   {
    length=strlen(for_operand);
    itoa(atoi(for_operand),arr,10);
    fprintf(file_pointer1,"%X\t%s\t%s\t%s\t00000%s\n",for_addr,for_label,for_opcode,for_operand,arr);
    fprintf(file_pointer4,"^00000%s",arr);
   }
   else if((strcmp(for_opcode,"RESB")==0)||(strcmp(for_opcode,"RESW")==0))
    fprintf(file_pointer1,"%X\t%s\t%s\t%s\n",for_addr,for_label,for_opcode,for_operand);
   else
   {
    while(strcmp(for_opcode,mnemonic[x])!=0)
     x++;
    if(strcmp(for_operand,"COPY")==0)
     fprintf(file_pointer1,"%X\t%s\t%s\t%s\t%s0000\n",for_addr,for_label,for_opcode,for_operand,code[x]);
    else
    {
     rewind(file_pointer2);
     fscanf(file_pointer2,"%s%X",for_symbol_table,&addr);
      while(strcmp(for_operand,for_symbol_table)!=0)
       fscanf(file_pointer2,"%s%X",for_symbol_table,&addr);
     fprintf(file_pointer1,"%X\t%s\t%s\t%s\t%s%X\n",for_addr,for_label,for_opcode,for_operand,code[x],addr);
     fprintf(file_pointer4,"^%s%X",code[x],addr);
    }
   }
   fscanf(file_pointer3,"%X%s%s%s",&for_addr,for_label,for_opcode,for_operand);
  }
  fprintf(file_pointer1,"%X\t%s\t%s\t%s\n",for_addr,for_label,for_opcode,for_operand);
  fprintf(file_pointer4,"\nE^00%X",string);
  printf("\n\n\tINTERMEDIATE FILE IS COVERTED INTO OBJECT CODE");
printf("\n\nEnding For pass 2");
  fclose(file_pointer1);
  fclose(file_pointer2);
  fclose(file_pointer3);
  fclose(file_pointer4);
  printf("\n\n\t\t\tOUTPUT FILE :\n\n");
  file_pointer1=fopen("otp.txt","r");
  ch=fgetc(file_pointer1);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(file_pointer1);
  }
  printf("\n\n Object Code File :\n\n");
  file_pointer4=fopen("object_code.txt","r");
  ch=fgetc(file_pointer4);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(file_pointer4);
  }
  fclose(file_pointer1);
  fclose(file_pointer3);
  fclose(file_pointer4);
}
