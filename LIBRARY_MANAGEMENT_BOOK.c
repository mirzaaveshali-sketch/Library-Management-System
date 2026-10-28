#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct book{
	int id;
	char title[50];
	char author[50];
	int isIssued; // o for available, 1 for issued
	
};

void addbook(){
	struct book newbook;
	FILE *file = fopen("library.dat","ab");
	
	printf("enter book id:");
	scanf("%d",&newbook.id);
	
	getchar();
	
	printf("Enter book title:");
	fgets(newbook.title,50,stdin);
	
	printf("enter author name:");
	fgets(newbook.author,50,stdin);
	
	newbook.isIssued = 0;
	
	fwrite(&newbook,sizeof(struct book),1,file);
	   fclose(file);
	
	printf("book added successfully! \n");
}

void displaybooks()
{
    struct book myBook;

    FILE *file = fopen("library.dat", "rb");

    while (fread(&myBook,sizeof(struct book), 1, file))
    {
        printf("ID: %d\nTitle: %sAuthor: %sStatus: %s\n\n",
               myBook.id,
               myBook.title,
               myBook.author,
               myBook.isIssued ? "issued" : "available");
    }

    fclose(file);
}


void issueBook()
{
    struct book myBook;
    int bookID, found = 0;

    FILE *file = fopen("library.dat", "rb+");

    printf("Enter Book ID to Issue: ");
    scanf("%d", &bookID);

    while (fread(&myBook, sizeof(struct book), 1, file) == 1)
    {
        if (myBook.id == bookID && myBook.isIssued == 0)
        {
            myBook.isIssued = 1;

			fseek(file, -sizeof(struct book), SEEK_CUR);

            fwrite(&myBook, sizeof(struct book), 1, file);

            printf("Book issued successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found or already issued.\n");
    }

    fclose(file);
}

void returnbook()
{
    struct book myBook;
    int bookID, found = 0;

    FILE *file = fopen("library.dat", "rb+");

    printf("Enter book ID to Return: ");
    scanf("%d", &bookID);

    while (fread(&myBook, sizeof(struct book), 1, file) == 1)
    {
        if (myBook.id == bookID && myBook.isIssued == 1)
        {
            myBook.isIssued = 0;

            fseek(file, -sizeof(struct book), SEEK_CUR);

            fwrite(&myBook, sizeof(struct book), 1, file);

            printf("Book returned successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Invalid book ID or book is not issued.\n");
    }

    fclose(file);
}

int main()

{
	
	int choice;
	
	while (1){
		printf("\nLibrary Management System \n");
		printf("1. Add Book \n");
		printf("2. Display All Books \n");
		printf("3. Issue Book \n");
		printf("4. Return Book \n");
		printf("5.Exit\n");
		printf("Enter your choice:");
		scanf("%d",&choice);
		
		switch(choice){
			case 1:addbook();
				break;
			case 2:displaybooks();
				break;
			case 3:issueBook();
				break;
			case 4:returnbook();
				break;
			case 5:exit(0);
			default: printf("Invalid choice!\n");
		}
	}
    return 0;
}




