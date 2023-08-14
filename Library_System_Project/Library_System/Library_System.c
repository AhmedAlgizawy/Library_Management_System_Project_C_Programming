#include "Library_System.h"

/**
  * @brief  Check library is full.
  * @param  (My_Library) pointer to the library.
  * @retval Status of the operation.
  */
static ret_status_t Library_Full(Library_t *My_Library)
{
    if (My_Library->Book_Count == LIBRARY_MAX_SIZE )
        return LIBRARY_FULL ;
    else
        return R_OK ;
}

/**
  * @brief  Check library is empty.
  * @param  (My_Library) pointer to the library.
  * @retval Status of the operation.
  */
static ret_status_t Library_Empty(Library_t *My_Library)
{
    if (My_Library->Book_Count == ZERO )
        return LIBRARY_EMPTY ;
    else
        return R_OK ;
}

ret_status_t Library_inti(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;  /*Return Status*/

    if (!My_Library) /*Check if passed NULL to this function*/
    {
        ret = R_NOK ;
    }
    else
    {
        My_Library->Book_Ptr   = -1 ;      /*Pointer to books in the library*/
        My_Library->Book_Count = ZERO ;    /*Number of book in the library  */

        ret = R_OK ;
    }
    return ret ;
}

ret_status_t Add_Book(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;     /*Return Status*/
    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);

    if (!user_choice)  /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else   /*To operating this function*/
    {
        if (!My_Library)     /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_FULL == Library_Full(My_Library))   /*Check if Library is full*/
            {
                printf("==> Library is full !! <==\n");
                ret = R_NOK ;
            }
            else          /*If Library is not full*/
            {
                My_Library->Book_Ptr++;   /*Point to new book*/

                printf("Enter book title : ");
                fflush(stdin);          /*To clear buffer*/
                gets(My_Library->Books[My_Library->Book_Ptr].Book_Title);

                printf("Enter author name : ");
                fflush(stdin);          /*To clear buffer*/
                gets(My_Library->Books[My_Library->Book_Ptr].Author_Name);

                printf("Enter publication year : ");
                scanf("%i",&My_Library->Books[My_Library->Book_Ptr].Publication_Year);

                printf("Enter number of copies : ");
                scanf("%i",&My_Library->Books[My_Library->Book_Ptr].Number_of_copies);

                printf("Enter price : ");
                scanf("%f",&My_Library->Books[My_Library->Book_Ptr].Price);

                printf("Enter status : ");
                fflush(stdin);          /*To clear buffer*/
                gets(My_Library->Books[My_Library->Book_Ptr].Status);

                My_Library->Book_Count++;  /*Increase by one to Addition new book*/

                ret = R_OK ;
            }
        }
        if (ret)    /*If Addition new book is successfully*/
        {
            printf("==> Book Added Successfully !! <==\n");
        }
        else {}
    }

    return ret ;
}

ret_status_t Delete_Book(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;                   /*Return Status*/
    uint8 Title_Deleted_Book[MAX_TITLE_LENGTH];  /*Title of deleted book*/
    sint32 Ret_Cmp   = ZERO;                     /*Return number to indicate to compare string process*/
    sint32 Ptr_Count = ZERO ;                    /*Pointer to move on the books*/

    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);
    if (!user_choice)      /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else
    {
        if (!My_Library)    /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_EMPTY == Library_Empty(My_Library))   /*Check if Library is empty*/
            {
                printf("==> Library is empty !! <==\n");
            }
            else        /*If Library is not empty*/
            {
                printf("Enter book title : ");
                fflush(stdin);
                gets(Title_Deleted_Book);

                for (Ptr_Count = ZERO ; Ptr_Count <= My_Library->Book_Ptr ; Ptr_Count++)
                {
                    Ret_Cmp = ZERO;
                    Ret_Cmp = strcmp(Title_Deleted_Book,(My_Library->Books[Ptr_Count].Book_Title));  /*Search about title in the library*/

                    if (Ret_Cmp == ZERO)  /*If found the title book in the library*/
                    {
                        while (Ptr_Count <= My_Library->Book_Ptr)  /*To shifting remaining books in the library to avoid accrue the gap*/
                        {
                            if (Ptr_Count != My_Library->Book_Ptr) /*Check if deleted book is not exist in the end of the library*/
                            {
                                strcpy( (My_Library->Books[Ptr_Count].Book_Title), (My_Library->Books[Ptr_Count+1].Book_Title) );
                                strcpy( (My_Library->Books[Ptr_Count].Author_Name), (My_Library->Books[Ptr_Count+1].Author_Name));
                                strcpy( (My_Library->Books[Ptr_Count].Status), (My_Library->Books[Ptr_Count+1].Status)     );

                                (My_Library->Books[Ptr_Count].Publication_Year) = (My_Library->Books[Ptr_Count+1].Publication_Year);
                                (My_Library->Books[Ptr_Count].Number_of_copies) = (My_Library->Books[Ptr_Count+1].Number_of_copies);
                                (My_Library->Books[Ptr_Count].Price)            = (My_Library->Books[Ptr_Count+1].Price);
                            }
                            else {/* Nothing */}
                            Ptr_Count++;
                        }
                        My_Library->Book_Ptr--;     /*Point to the book in end of the library*/
                        My_Library->Book_Count--;   /*Decrease by one due to deleted book*/
                        ret = R_OK ;
                        break;
                    }
                    else {/* Nothing */}
                }

                if(ret)   /*If deleted book is successfully*/
                {
                    printf("==> Book Deleted Successfully !! <==\n");
                }
                else
                {
                    printf("==> Not found this title !! <==\n");
                }
            }
        }
    }

    return ret ;
}

ret_status_t Borrow_Book(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;                   /*Return Status*/
    uint8 Title_Borrow_Book[MAX_TITLE_LENGTH];   /*Title of borrow book*/
    sint32 Ret_Cmp = ZERO;                       /*Return number to indicate to compare string process*/
    sint32 Ptr_Count = ZERO ;                    /*Pointer to move on the books*/
    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);
    if (!user_choice)     /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else
    {
        if (!My_Library)     /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_EMPTY == Library_Empty(My_Library))   /*Check if Library is empty*/
            {
                printf("==> Library is empty !! <==\n");
            }
            else
            {
                printf("Enter book title : ");
                fflush(stdin);
                gets(Title_Borrow_Book);

                for (Ptr_Count = ZERO ; Ptr_Count <= My_Library->Book_Ptr ; Ptr_Count++)
                {
                    Ret_Cmp = ZERO;
                    Ret_Cmp = strcmp(Title_Borrow_Book,(My_Library->Books[Ptr_Count].Book_Title));  /*Search about title in the library*/

                    if (Ret_Cmp == ZERO)   /*If found the title book in the library*/
                    {
                        if ((My_Library->Books[Ptr_Count].Number_of_copies) == 1 )   /*Check if last copy in the library*/
                        {
                            printf("==> This is last copy of this book !! <==\n");
                        }
                        else if ((My_Library->Books[Ptr_Count].Number_of_copies) == ZERO )  /*Check if unavailable copy in the library*/
                        {
                            printf("==> A copy of this book is not available now !! <==\n");
                            ret = R_NOK;
                            return ret ;
                        }
                        else {/* Nothing */}

                        (My_Library->Books[Ptr_Count].Number_of_copies)--;
                        ret = R_OK ;
                        break;        /*If found book in the library not need continue in the loop*/
                    }
                    else {/* Nothing */}
                }

                if(ret) /*If borrowed book is successfully*/
                {
                    printf("==> Book Borrowed Successfully !! <==\n");
                }
                else
                {
                    printf("==> Not found this title !! <==\n");
                }
            }
        }
    }
    return ret ;
}

ret_status_t Buy_Book(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;                /*Return Status*/
    uint8 Title_Buy_Book[MAX_TITLE_LENGTH];   /*Title of buy book*/
    sint32 Ret_Cmp = ZERO;                    /*Return number to indicate to compare string process*/
    sint32 Ptr_Count = ZERO ;                 /*Pointer to move on the books*/
    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);
    if (!user_choice)    /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else
    {
        if (!My_Library)       /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_EMPTY == Library_Empty(My_Library))   /*Check if Library is empty*/
            {
                printf("==> Library is empty !! <==\n");
            }
            else
            {
                printf("Enter book title : ");
                fflush(stdin);
                gets(Title_Buy_Book);

                for (Ptr_Count = ZERO ; Ptr_Count <= My_Library->Book_Ptr ; Ptr_Count++)
                {
                    Ret_Cmp = ZERO;
                    Ret_Cmp = strcmp(Title_Buy_Book,(My_Library->Books[Ptr_Count].Book_Title));  /*Search about title in the library*/

                    if (Ret_Cmp == ZERO)   /*If found the title book in the library*/
                    {
                        (My_Library->Books[Ptr_Count].Number_of_copies)++;   /*Increase copy of this book*/
                        ret = R_OK ;
                        break;
                    }
                    else {/* Nothing */}
                }

                if(ret)    /*If bought book is successfully*/
                {
                    printf("==> Book bought Successfully !! <==\n");
                }
                else
                {
                    printf("==> Not found this title !! <==\n");
                }
            }
        }
    }

    return ret ;
}

ret_status_t Search_For_A_Book(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;                    /*Return Status*/
    uint16 Search_Method = ZERO ;                 /*To user choose method for searching*/
    uint8 Search_Title_Book[MAX_TITLE_LENGTH];    /*Title of book to be search*/
    uint8 Search_Author_Book[MAX_AUTHOR_LENGTH];  /*Author of book to be search*/
    sint32 Ret_Cmp = ZERO;                        /*Return number to indicate to compare string process*/
    sint32 Ptr_Count = ZERO ;                     /*Pointer to move on the books*/

    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);
    if (!user_choice)    /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else
    {
        if (!My_Library)  /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_EMPTY == Library_Empty(My_Library))  /*Check if Library is empty*/
            {
                printf("==> Library is empty !! <==\n");
            }
            else
            {
                printf("-> Please choose search method. \n");
                printf("===============================\n");
                printf("-> 1 ) Search_By_Title \n");
                printf("-> 2 ) Search_By_Author \n");
                printf("===============================\n");
                printf("\nEnter your choice : ");
                scanf("%i",&Search_Method);

                if (Search_Method == 1)
                {
                    printf("Enter book title  : ");
                    fflush(stdin);
                    gets(Search_Title_Book);

                    for (Ptr_Count = ZERO ; Ptr_Count <= My_Library->Book_Ptr ; Ptr_Count++)
                    {
                        Ret_Cmp = ZERO;
                        Ret_Cmp = strcmp(Search_Title_Book,(My_Library->Books[Ptr_Count].Book_Title)); /*Search about title in the library*/

                        if (Ret_Cmp == ZERO)    /*If found the title book in the library*/
                        {
                            printf("*******************************\n");
                            printf("Title  of Book    : %s\n",(My_Library->Books[Ptr_Count].Book_Title));
                            printf("Author of Book    : %s\n",(My_Library->Books[Ptr_Count].Author_Name));
                            printf("Number of copies  : %i\n",(My_Library->Books[Ptr_Count].Number_of_copies));
                            printf("Publication Year  : %i\n",(My_Library->Books[Ptr_Count].Publication_Year));
                            printf("Price  of Book    : %0.2fL.E\n",(My_Library->Books[Ptr_Count].Price));
                            printf("Status of Book    : %s\n",(My_Library->Books[Ptr_Count].Status));
                            ret = R_OK ;
                            break;
                        }
                        else {/* Nothing */}
                    }
                    if (!ret)
                    {
                        printf("==> Not found this title !! <==\n");
                    }

                }
                else if (Search_Method == 2)
                {
                    printf("Enter book author : ");
                    fflush(stdin);
                    gets(Search_Author_Book);

                    for (Ptr_Count = ZERO ; Ptr_Count <= My_Library->Book_Ptr ; Ptr_Count++)
                    {
                        Ret_Cmp = ZERO;
                        Ret_Cmp = strcmp(Search_Author_Book,(My_Library->Books[Ptr_Count].Author_Name));  /*Search about author in the library*/

                        if (Ret_Cmp == ZERO)  /*If found the author of book in the library*/
                        {
                            printf("*******************************\n");
                            printf("Title  of Book    : %s\n",(My_Library->Books[Ptr_Count].Book_Title));
                            printf("Author of Book    : %s\n",(My_Library->Books[Ptr_Count].Author_Name));
                            printf("Number of copies  : %i\n",(My_Library->Books[Ptr_Count].Number_of_copies));
                            printf("Publication Year  : %i\n",(My_Library->Books[Ptr_Count].Publication_Year));
                            printf("Price  of Book    : %0.2fL.E\n",(My_Library->Books[Ptr_Count].Price));
                            printf("Status of Book    : %s\n",(My_Library->Books[Ptr_Count].Status));
                            ret = R_OK ;
                            break;
                        }
                        else {/* Nothing */}
                    }
                    if (!ret)
                    {
                        printf("==> Not found this author !! <==\n");
                    }

                }
                else
                {
                    printf("==> Invalid Choice !! <==\n");
                    ret = R_NOK ;
                    return ret;
                }
            }
        }

        if(ret)    /*If searching processes is successfully*/
        {
            printf("==> Searching Processes Successfully !! <==\n");
        }
    }


    return ret ;
}

ret_status_t Search_By_Highest_Price_Book(Library_t *My_Library)
{
    ret_status_t ret    = R_NOK ;    /*Return Status*/
    float32 Max_Price   = ZERO ;     /*Max price in the library*/
    sint32 Ptr_Count    = ZERO ;     /*Pointer to move on the books*/
    sint32 Ptr_Max_Elem = ZERO ;     /*Pointer to the book of max price*/

    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);
    if (!user_choice)      /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else
    {
        if (!My_Library)   /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_EMPTY == Library_Empty(My_Library))   /*Check if Library is empty*/
            {
                printf("==> Library is empty !! <==\n");
            }
            else
            {
                printf("-> Searching about highest price. \n");
                printf("===============================\n");

                Max_Price = (My_Library->Books[Ptr_Count].Price);
                for (Ptr_Count = 1 ; Ptr_Count <= My_Library->Book_Ptr ; Ptr_Count++) /*Linear search because unsorted price of the books*/
                {
                    if (Max_Price < (My_Library->Books[Ptr_Count].Price))
                    {
                        Max_Price = (My_Library->Books[Ptr_Count].Price);
                        Ptr_Max_Elem = Ptr_Count ;
                    }
                    else {/* Nothing */}
                }          /*Print all details of highest price book*/
                printf("Title  of Book    : %s\n",(My_Library->Books[Ptr_Max_Elem].Book_Title));
                printf("Author of Book    : %s\n",(My_Library->Books[Ptr_Max_Elem].Author_Name));
                printf("Number of copies  : %i\n",(My_Library->Books[Ptr_Max_Elem].Number_of_copies));
                printf("Publication Year  : %i\n",(My_Library->Books[Ptr_Max_Elem].Publication_Year));
                printf("Price  of Book    : %0.2fL.E\n",(My_Library->Books[Ptr_Max_Elem].Price));
                printf("Status of Book    : %s\n",(My_Library->Books[Ptr_Max_Elem].Status));
                ret = R_OK ;
            }

        }
        if(ret)         /*If searching processes is successfully*/
        {
            printf("==> Searching Processes Successfully !! <==\n");
        }
        else {/* Nothing */}
    }
    return ret ;
}

ret_status_t Print_Book_Of_Library(Library_t *My_Library)
{
    ret_status_t ret = R_NOK ;  /*Return Status*/
    uint16 Count = ZERO ;
    uint16 user_choice = ZERO;

    /*If choose this function by mistake*/
    printf("Press (0) to back to menu, OR Press (1) to continue : ");
    scanf("%i",&user_choice);
    if (!user_choice)       /*If choose this function by mistake*/
    {
        ret = R_OK;
        return ret;
    }
    else
    {
        if (!My_Library)   /*Check if passed NULL to this function*/
        {
            ret = R_NOK ;
        }
        else
        {
            if (LIBRARY_EMPTY == Library_Empty(My_Library))  /*Check if Library is empty*/
            {
                printf("==> Library is empty !! <==\n");
            }
            else
            {
                printf("\n=======================================================================================================================\n");
                printf("Title%-30C",' ');
                printf("Author%-20C",' ');
                printf("Year%-10C",' ');
                printf("Copies%-8C",' ');
                printf("Price%-10C",' ');
                printf("Status\n");
                printf("=======================================================================================================================\n");
                for (Count = ZERO ; Count <= (My_Library->Book_Ptr) ; Count++)
                {
                    printf("%-35s",My_Library->Books[Count].Book_Title);
                    printf("%-26s",My_Library->Books[Count].Author_Name);
                    printf("%-14i",My_Library->Books[Count].Publication_Year);
                    printf("%-14i",My_Library->Books[Count].Number_of_copies);
                    printf("%0.2fL.E%-4C\t",My_Library->Books[Count].Price,' ');
                    printf("%-11s\n",My_Library->Books[Count].Status);
                }
            }
            ret = R_OK;
        }
    }
    return ret ;
}



