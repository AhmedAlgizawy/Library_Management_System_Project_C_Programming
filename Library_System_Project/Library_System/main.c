#include <stdio.h>
#include <stdlib.h>
#include "Library_System.h"

Library_t Library;

int main()
{
    ret_status_t Ret = R_NOK;
    uint8 UserChoice = ZERO ;

    Ret = Library_inti(&Library);
    if (R_NOK==Ret)
    {
        printf("Library failed to be initialized !! \n");

    }
    else
    {
        printf("-> Hello to Library management system. \n");
        printf("-> Choose a number for the operation you want to be perform. \n");
        printf("\n===============================\n");
        printf("-> 1 ) Add Book. \n");
        printf("-> 2 ) Delete Book. \n");
        printf("-> 3 ) Borrow Book. \n");
        printf("-> 4 ) Buy Book. \n");
        printf("-> 5 ) Print Book. \n");
        printf("-> 6 ) Search for a book. \n");
        printf("-> 7 ) Searching by highest price. \n");
        printf("-> 8 ) Exit from application \n");
        printf("===============================\n");

        while(1)
        {
            printf("\nUserChoice : ");
            scanf("%i", &UserChoice);

            switch (UserChoice)
            {
            case 1:
                Ret = Add_Book(&Library);
                break;

            case 2:
                Ret = Delete_Book(&Library);
                break;

            case 3:
                Ret = Borrow_Book(&Library);
                break;

            case 4:
                Ret = Buy_Book(&Library);
                break;

            case 5:
                Ret = Print_Book_Of_Library(&Library);
                break;

            case 6:
                Ret = Search_For_A_Book(&Library);
                break;

            case 7:
                Ret = Search_By_Highest_Price_Book(&Library);
                break;

            case 8:
                printf("Exit from application. \n");
                exit(0);
                break;

            default:
                printf("User Choice out of range !!\n");
                break;
            }
        }
    }
    return 0;
}
