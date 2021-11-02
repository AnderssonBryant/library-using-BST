// Bryant Andersson (2301854706)
// LC01

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//struct data buku
struct book_info
{
    int entry;
    char author[3];
    char title;
    struct book_info *left, *right;
};

//struct data peminjam
struct borrow_data
{
	char name[20];
	struct book_info dtb;
	char date[8];
	struct borrow_data *next;
};
    
//fungsi untuk menambahkan node baru
struct book_info *newBook(int entry, char author[3], char title)
{
    struct book_info *temp = (struct book_info*)malloc(sizeof(struct book_info));
    temp->entry = entry;
    strcpy(temp->author,author);
    temp->title = title;
    temp->left = temp->right = NULL; 
    return temp;
}

struct book_info* insert(struct book_info *node, int entry, char author[3], char title) 
{ 
    if(node == NULL)
	{ 
		return newBook(entry,author,title); 
	}
    if(entry < node->entry) 
	{
        node->left  = insert(node->left,entry,author,title);
	} 
    else 
	{
        node->right = insert(node->right,entry,author,title);
	}    
} 

struct book_info * minValueNode(struct book_info* node) 
{ 
    struct book_info* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
    { 
        current = current->left; 
    }
    return current; 
} 
  
struct book_info* deleteNode(struct book_info* root, int entry) 
{ 
    if (root == NULL) return root; 

    if (entry < root->entry) 
        root->left = deleteNode(root->left, entry); 
  
    else if (entry > root->entry) 
        root->right = deleteNode(root->right, entry); 
  
    else
    { 
        if (root->left == NULL) 
        { 
            struct book_info *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            struct book_info *temp = root->left; 
            free(root); 
            return temp; 
        } 
     
        struct book_info* temp = minValueNode(root->right); 
     
        strcpy(root->author,temp->author); 
        root->entry = temp->entry;
        root->title = temp->title;
        
        root->right = deleteNode(root->right, temp->entry); 
    } 
    return root; 
} 
  
struct book_info* search(struct book_info *node, int entry) 
{ 
	if (node == NULL){ 
		return NULL;
	}
	if(node->entry == entry){
		return node;
	}	
	if (node->entry > entry){ 
		return search(node->left, entry);
    } 
	if(node->entry < entry){
		return search(node->right, entry);
    }
}

void display(struct book_info *root) 
{ 
    if (root != NULL) 
    { 
        display(root->left);
		printf("Book Entry %d\n",root->entry); 
        printf("Book Author %s\n",root->author);
		printf("Book Title %c\n",root->title); 
        display(root->right); 
    } 
}

struct borrow_data *append(struct borrow_data *head, struct book_info *book, char name[20],char date[8]) 
{
    struct borrow_data *curr, *new_queue;
    new_queue = (struct borrow_data *) malloc(sizeof(struct borrow_data));
	strcpy(new_queue->name,name);
	strcpy(new_queue->date,date); 
    new_queue->dtb.entry = book->entry;
    strcpy(new_queue->dtb.author,book->author);
    new_queue->dtb.title= book->title;
    new_queue->next = NULL;
    if(head == NULL){
        head = new_queue;
    }else{
        curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_queue;
    }
    return head;
}

void printList(struct borrow_data *head) 
{ 
	struct borrow_data *curr = head;
  	while (curr != NULL) 
  	{ 
    printf("Nama Peminjam :%s\n", curr->name);
	printf("Nomor entry buku: %d\n", curr->dtb.entry); 
    curr = curr->next; 
  	} 
}

struct borrow_data *searched(struct borrow_data *head, char name[20]) 
{ 
	struct borrow_data *curr = head;
	while (curr != NULL) 
    { 
        if (strcmp(curr->name,name) == 0)
		{ 
            return curr;
		}
        curr = curr->next; 
    } 
	return NULL;
}

void deleteNodes(struct borrow_data *head, char name[20]) 
{
    struct borrow_data *temp = head,*prev; 

	if (temp != NULL && temp->name == name) 
	{
	head = temp->next;
	free(temp);
	return;
	}

	while (temp != NULL && temp->name != name)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return;
	prev->next = temp->next;
	free(temp);
}

int main()
{
	int pilihan = -1;
	int entry,days;
	char author[3],title ,temp,name[20],date[8];
	struct book_info *root = NULL;
	struct borrow_data *head = NULL;
	struct book_info *book = NULL;
	struct borrow_data *person = NULL;
	while(pilihan != 0)
	{
		printf("\nLibary System");
		printf("\n==========================\n");
		printf("Menu:\n");
		printf("1.Input Book \n");
		printf("2.Search Book \n");
		printf("3.Borrow Book \n");
		printf("4.Return Book \n");
		printf("5.Exit\n");
		printf("Enter Your Choice:");
		scanf("%d",&pilihan);
		switch (pilihan)
		{
		case 1:
			printf("Input Book\n");
			printf("Enter Book Entry: ");
			scanf("%d",&entry);
			printf("Enter Book Author: ");
			scanf("%s",&author);
			scanf("%c",&temp);
			printf("Enter Book Title: ");
			scanf("%c",&title);
			root = insert(root,entry,author,title);
			break;
		case 2:
			printf("Search book\n");
			printf("Enter Book Entry: ");
			scanf("%d",&entry);
			book = search(root,entry);
			if (book == NULL)
			{
				printf("Book Unavailable");
			}
			else
			{
				printf("Book Found\n");
				printf("Book Entry: %d\n",book->entry);
				printf("Book Title: %c\n",book->title);
				printf("Book Author: %s\n",book->author);
			}
			break;
		case 3:
			printf("Borrow Book\n");
			printf("Available Books\n");
			display(root);
			printf("Insert Your Name: ");
			scanf("%s",&name);
			printf("Insert Today's Date[ddmmyyyy]: ");
			scanf("%s",&date);
			printf("Enter Book Entry: ");
			scanf("%d",&entry);
			book = search(root,entry);
			if (book == NULL)
			{
				printf("Book Unavailable");
			}
			else
			{
				head = append(head,book,name,date);
				root = deleteNode(root,entry);
				printf("Book Found!\n");
				printList(head);
			}
			break;
		case 4:
			printf("Return Book\n");
			printf("Data peminjam\n");
			printList(head);
			printf("Enter name: ");
			scanf("%s",&name);
			printf("Days borrowed: ");
			scanf("%d",&days);
			person = searched(head,name);
			printList(person);
			root = insert(root,person->dtb.entry,person->dtb.author,person->dtb.title);
			deleteNodes(head,name);
			printf("Books returned\n");
			printf("Rental cost %d.000\n",days);
			printf("Thank You");
			break;		
		case 5:
			return 0;
		default:
			printf("Pilihan tidak ada\n");
			break;	
		}
	}
}
