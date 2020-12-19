#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int item=1,count=0,result,i,num,total=0,choice=1,discount,vir=0;
    int a[50]={0};
    char desc[50],percent='%';
    char nll[]={"0"};                                               //used in string compare to determine whether user’s input is 0
    float price,subtotal=0,tdiscount,cash;
    FILE *fc;
    FILE *fd;
    fc=fopen("food.txt","a+");
    fscanf(fc,"%d %s %f",&num,desc,&price);
    if(num!=1)                                                                     //determine whether there is any food item in food.txt
      fprintf(fc,"1 BigM 10.40\n2 Cheeseburger 9.45\n");      //if there is none, print two default food items
fclose(fc);
    while(item!=0)
    {
        printf("\nWELCOME TO RESTAURANT MAC C - Main Menu\n\n[1] Add new food items\n\n[2] Take order\n\nEnter ITEM CODE (0 to quit): ");
        scanf("%d",&item);
        choice=1;
        if(item<0||item>2)
           printf("\nItem code not available. Please reenter.\n\n"); //prompt user to re-enter input if it is unavailable
        if(item==1)
        {
            fc=fopen("food.txt","r");
            printf("\nWELCOME TO RESTAURANT MAC C - Add Menu\n\n");
            printf("ITEM CODE        DESCRIPTION            PRICE (RM)\n");
            count=0;
            while(!feof(fc))
            {
                fscanf(fc,"%d %s %f",&num,desc,&price);                     //display all the food items inside food.txt
                if(num==count+1)
                {
                    printf("%-16d %-19s       %-6.2f\n\n",num,desc,price);
                    count++;                                                 //determine how many food items are available in food.txt
                }
            }
            fclose(fc);
            fc=fopen("food.txt","a");                                //enable the user to add in new food items into food.txt
            printf("Enter description (0 to Main Menu) : ");
            scanf("%s",desc);
            result=strcmp(nll,desc);                                                 //if user's input==0, quit to MAIN MENU
            if(result!=0)
            {
            printf("\nEnter price(RM) : ");
            scanf("%f",&price);
            fprintf(fc,"%d %s %.2f\n",count+1,desc,price);     //print new food item together with price into food.txt
            printf("\n%-17d%-26s%.2f\n\n",count+1,desc,price);
            count+=2;
            }
            while(result!=0)                                                          //user input: 0 to quit
            {
                printf("Enter ITEM CODE (0 to quit): ");
                scanf("%s",desc);
                result=strcmp(nll,desc);                          //determine whether the user input is 0 using string compare
                if (result!=0)
                {
                    printf("\nEnter price(RM) : ");
                    scanf("%f",&price);
                    fprintf(fc,"%d %s %.2f\n",count,desc,price);
                    printf("\n%-17d%-26s%.2f\n\n",count,desc,price);
                    count++;
                }

            }
            fclose(fc);
        }
        if(item==2)
        {
            fc=fopen("food.txt","r");
            fd=fopen("Invoice.txt","a");                             //open new text file named Invoice.txt to store the receipt
            printf("\nWELCOME TO RESTAURANT MAC C - Take Order\n\n");
            printf("ITEM CODE        DESCRIPTION         PRICE (RM)\n\n");
            total=0;
            while(!feof(fc))                                                           //scan and print all the food items in food.txt
            {
                fscanf(fc,"%d %s %f",&num,desc,&price);
                if(num==total+1)
                {printf("%-16d %-20s %-6.2f\n\n",num,desc,price);
                total++;}                                                          //act as counter to determine total number of food item
            }
            fclose(fc);
            while(choice!=100)                                                         //if user's input==100, quit to MAIN MENU
            {
                    while(choice!=100)
                  {
                    printf("Enter ITEM CODE (0 to Quit, 100 for Main Menu) : ");
                    scanf("%d",&choice);
                    if(choice==0&&vir==0)
                        printf("First item code cannot be 0.\n");                       //ensure the first user input is not "0"
                    else if(choice==0||choice==100)
                        break;
                    else if(choice>0&&choice<total+1)
                        {a[choice-1]++;                                                              //save the user input in form of array
                        vir++;}
                    else
                        printf("ITEM CODE not available. Try again.\n");       //prompt user to re-enter if its unavailable
                  }
            if (choice!=100&&vir!=0)                                                  //skip the program if the first user input is "0"
            {
            fc=fopen("food.txt","r");
            printf("Enter Discount (%c)            : ",percent);
            scanf("%d",&discount);
            printf("\n\n\t\tINVOICE RESTAURANT MAC C\n");
            printf("-----------------------------------------------------------\n\n");
            printf("ITEM CODE  DESCRIPTION    PRICE (RM)  QUANTITY    TOTAL(RM)\n\n");
            fprintf(fd,"\n\n\t\tINVOICE RESTAURANT MAC C\n");
            fprintf(fd,"-----------------------------------------------------------\n\n");
            fprintf(fd,"ITEM CODE  DESCRIPTION    PRICE (RM)  QUANTITY    TOTAL(RM)\n\n");
            for(i=0;i<total;i++)
            {
               fscanf(fc,"%d %s %f",&num,desc,&price);
               if(a[i]!=0)                                                                //do not print the food item if its quantity is 0
               {printf("%d          %-16s%-6.2f %9d %13.2f\n\n",num,desc,price,a[i],a[i]*price);
               fprintf(fd,"%d          %-16s%-6.2f %9d %13.2f\n\n",num,desc,price,a[i],a[i]*price);}
               subtotal=subtotal+a[i]*price;                                   //calculate the subtotal for all the customer's order
            }
            fclose(fc);
            printf("-----------------------------------------------------------\n\n");
            printf("Subtotal before Discount             %-10.2f\n\n",subtotal);
            fprintf(fd,"-----------------------------------------------------------\n\n");
            fprintf(fd,"Subtotal before Discount             %-10.2f\n\n",subtotal);
            tdiscount=subtotal*discount/100;                                               //calculating total discount
            printf("Discount(%-2d%c)                        %-10.2f\n\n",discount,percent,tdiscount);
            printf("-----------------------------------------------------------\n\n");
            printf("TOTAL                                %-10.2f\n\n",subtotal-tdiscount);
            printf("CASH TENDERED                      : ");
            scanf("%f",&cash);
            fprintf(fd,"Discount(%-2d%c)                        %-10.2f\n\n",discount,percent,tdiscount);
            fprintf(fd,"-----------------------------------------------------------\n\n");
            while (cash<(subtotal-tdiscount))            //continuously to prompt user to enter cash if it's not sufficient
            {
                printf("Your cash is insufficient.\n");
                printf("CASH TENDERED                      : ");
                scanf("%f",&cash);
            }
            fprintf(fd,"TOTAL                                %-10.2f\n\n",subtotal-tdiscount);
            fprintf(fd,"CASH TENDERED                      : %.2f",cash);
            printf("\nCHANGE                             : %-10.2f\n\n",cash-subtotal+tdiscount);
            printf("PRINTING OUT RECEIPT...\n\n");
            fprintf(fd,"\nCHANGE                             : %-10.2f\n\n",cash-subtotal+tdiscount);
            fprintf(fd,"PRINTING OUT RECEIPT...\n\n");
            fclose(fd);
            choice=1;
            for(i=0;i<50;i++)
            a[i]=0;                                                                 //reset the all the values in array = 0
            vir=0;
            }
        }
        }
    }
    return 0;
}
