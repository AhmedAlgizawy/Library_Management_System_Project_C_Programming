#ifndef _LIBRARY_SYSTEM_H
#define _LIBRARY_SYSTEM_H

#include "Platform_Types.h"

#define LIBRARY_MAX_SIZE  100
#define MAX_TITLE_LENGTH  100
#define MAX_AUTHOR_LENGTH 100
#define MAX_STATUS_LENGTH 50

typedef struct Book{
    sint8   Book_Title[MAX_TITLE_LENGTH];
    sint8   Author_Name[MAX_AUTHOR_LENGTH];
    sint8   Status[MAX_STATUS_LENGTH];
    uint32  Publication_Year;
    uint32  Number_of_copies;
    float32 Price;
} Book_t;

typedef struct Library{

    Book_t Books[LIBRARY_MAX_SIZE];
    sint32 Book_Ptr;
    uint32 Book_Count;

}Library_t;

typedef enum Ret_Status {
    R_NOK,
    R_OK,
    LIBRARY_FULL,
    LIBRARY_EMPTY
}ret_status_t;

/**
  * @brief  initialize the library pointer and library count.
  * @param  (My_Library) pointer to the library.
  * @retval Status of initialization process
  */
ret_status_t Library_inti(Library_t *My_Library);

/**
  * @brief  Add book to the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of Addition process.
  */
ret_status_t Add_Book(Library_t *My_Library);

/**
  * @brief  Delete book from the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of remove process.
  */
ret_status_t Delete_Book(Library_t *My_Library);

/**
  * @brief  Borrow book from the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of function operation.
  */
ret_status_t Borrow_Book(Library_t *My_Library);

/**
  * @brief  Buy book to the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of function operation.
  */
ret_status_t Buy_Book(Library_t *My_Library);

/**
  * @brief  Search about specific book in the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of function operation.
  */
ret_status_t Search_For_A_Book(Library_t *My_Library);

/**
  * @brief  Search about highest price of specific book in the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of function operation.
  */
ret_status_t Search_By_Highest_Price_Book(Library_t *My_Library);

/**
  * @brief  Print all books in the library.
  * @param  (My_Library) pointer to the library.
  * @retval Status of function operation.
  */
ret_status_t Print_Book_Of_Library(Library_t *My_Library);
#endif // _LIBRARY_SYSTEM_H
