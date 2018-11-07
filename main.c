#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <unistd.h>

/*  Screen type define
 *
 *  If you want add new screen, try following steps.
 *  1. Add new define for new screen.
 *  2. Change other define, all define should have another number.
 *  3. Change SCREEN_MAX.
 *  4. Add new screen's function(draw_~~_screen, input_~~_screen).
 *  5. Link screen and function(it is in the init_screens function).
 */
#define SCREEN_INIT 0
#define SCREEN_SIGN_UP 1
#define SCREEN_SIGN_IN 2
#define SCREEN_MENU_MEMBER 3
#define SCREEN_MENU_ADMIN 4
#define SCREEN_MAX 5

 /*  String size define
  */
#define SIZE_STUDENT_NUMBER 8
#define SIZE_PHONE_NUMBER 13

#define SIZE_BOOK_NUMBER 7
#define SIZE_ISBN 13

#define SIZE_INPUT_MAX 100

  /* String const
   */
#define STRING_CLIENT_FILE "client"
#define STRING_BOOK_FILE "book"
#define STRING_BORROW_FILE "borrow"

struct _LinkedList
{
	void *contents;
	struct _LinkedList *next;
};
typedef struct _LinkedList LinkedList;

typedef struct Client
{
	wchar_t student_number[SIZE_STUDENT_NUMBER + 1];
	wchar_t phone_number[SIZE_PHONE_NUMBER + 1];
	wchar_t *password;
	wchar_t *name;
	wchar_t *address;
} Client;

typedef struct Book
{
	wchar_t number[SIZE_BOOK_NUMBER + 1];
	wchar_t ISBN[SIZE_ISBN + 1];
	wchar_t availability;
	wchar_t *name;
	wchar_t *publisher;
	wchar_t *author;
	wchar_t *location;
} Book;

typedef struct Borrow
{
	wchar_t student_number[SIZE_STUDENT_NUMBER + 1];
	wchar_t book_number[SIZE_BOOK_NUMBER + 1];
	time_t loan_date;
	time_t return_date;
} Borrow;

struct Screens;

typedef struct Data
{
	LinkedList *clients, *books, *borrows;
	struct Screens* screens;
	Client* login_client;
	_Bool is_running;
	_Bool is_admin;
} Data;

typedef struct Screen
{
	char type;
	void(*draw)(Data const *);
	void(*input)(const wchar_t const *, Data const *);
} Screen;

typedef struct Screens
{
	Screen screens[SCREEN_MAX];
	char type;
} Screens;

/*  @brief Init client list.
 *
 *  Get client data for file and allocate client and link the list.
 *
 *  @param file_name The file name to get data.
 *  @return LinkedList* Allocated and sorted linked list.
 */
LinkedList *init_clients(const char const *file_name);
/*  @brief Init book list.
 *
 *  Get book data for file and allocate book and link the list.
 *
 *  @param file_name The file name to get data.
 *  @return LinkedList* Allocated and sorted linked list.
 */
LinkedList *init_books(const char const *file_name);
/*  @brief Init borrow list.
 *
 *  Get borrow data for file and allocate borrow and link the list.
 *
 *  @param file_name The file name to get data.
 *  @return LinkedList* Allocated and sorted linked list.
 */
LinkedList *init_borrows(const char const *file_name);

/*  @brief Create book.
 *
 *  Create book by ISBN, publisher, author, location and name.
 *  Book's number and availability are specified in this function.
 *
 *  @param name The book's name.
 *  @param publisher The book's publisher.
 *  @param author The book's author.
 *  @param ISBN The book's ISBN.
 *  @param location The book's location.
 *  @return Borrow* new borrow made by datas.
 */
Book *create_book(wchar_t *name, wchar_t *publisher, wchar_t *author, wchar_t *ISBN, wchar_t *location);
/*  @brief Create borrow.
 *
 *  Create borrow by client and book.
 *
 *  @param client The client to borrow.
 *  @param book The book to borrow.
 *  @return Borrow* new borrow made by client and book.
 */
Borrow *create_borrow(Client const *client, Book const *book);

/*  @brief Print client.
 *
 *  Print client data.
 *
 *  @param client Client pointer to print.
 *  @return void.
 */
void print_client(const Client const *client);
/*  @brief Print book.
 *
 *  Print book data.
 *
 *  @param book Book pointer to print.
 *  @return void.
 */
void print_book(const Book const *book);
/*  @brief Print borrow.
 *
 *  Print borrow data.
 *
 *  @param borrow Borrow pointer to print.
 *  @return void.
 */
void print_borrow(const Borrow const *borrow);

/*  @brief Print All clients.
 *
 *  Print all clients data using linked list.
 *
 *  @param client_list Lined list to print.
 *  @return void.
 */
void print_clients(const LinkedList const *client_list);
/*  @brief Print All books.
 *
 *  Print all books data using linked list.
 *
 *  @param book_list Lined list to print.
 *  @return void.
 */
void print_books(const LinkedList const *book_list);
/*  @brief Print All borrows.
 *
 *  Print all borrows data using linked list.
 *
 *  @param borrow_list Linked list to print.
 *  @return void.
 */
void print_borrows(const LinkedList const *borrow_list);

/*  @brief Save clients to file.
 *
 *  Save clients to file.
 *  All clients should be sorted and data in file also should be sorted.
 *
 *  @param client_list Linked list to save.
 *  @param file_name File name to save.
 *  @return void.
 */
void save_clients(const LinkedList const *client_list, const char const *file_name);
/*  @brief Save books to file.
 *
 *  Save books to file.
 *  All books should be sorted and data in file also should be sorted.
 *
 *  @param book_list Linked list to save.
 *  @param file_name File name to save.
 *  @return void.
 */
void save_books(const LinkedList const *book_list, const char const *file_name);
/*  @brief Save borrows to file.
 *
 *  Save borrows to file.
 *  All borrows should be sorted and data in file also should be sorted.
 *
 *  @param borrow_list Linked list to save.
 *  @param file_name File name to save.
 *  @return void.
 */
void save_borrows(const LinkedList const *borrow_list, const char const *file_name);

/*  @brief Insert client in the linked list.
 *
 *  Fined the current position in linked list.
 *  Create new node and add to the list.
 *  All times list should be sorted.
 *
 *  @param client_list Linked list.
 *  @param client Client to insert.
 *  @return LinkedList* Linked list's first member.
 */
LinkedList *insert_client(LinkedList const *client_list, const Client const *client);
/*  @brief Insert client in the linked list.
 *
 *  Fined the current position in linked list.
 *  Create new node and add to the list.
 *  All times list should be sorted.
 *
 *  @param client_list Linked list.
 *  @param client Client to insert.
 *  @return LinkedList* Linked list's first member.
 */
LinkedList *insert_book(LinkedList const *book_list, const Book const *book);
/*  @brief Insert client in the linked list.
 *
 *  Fined the current position in linked list.
 *  Create new node and add to the list.
 *  All times list should be sorted.
 *
 *  @param client_list Linked list.
 *  @param client Client to insert.
 *  @return LinkedList* Linked list's first member.
 */
LinkedList *insert_borrow(LinkedList const *borrow_list, const Borrow const *borrow);

/*  @brief Find client by student number.
 *
 *  Find client by student number.
 *
 *  @param client_list The client list to get client.
 *  @param student_number The client's student number.
 *  @return Client* Fined client.
 */
Client *find_client_by_student_number(const LinkedList const *client_list, const wchar_t const *student_number);
/*  @brief Find books by name.
 *
 *  Find book by name.
 *
 *  @param book_list The book list to get book.
 *  @param book_name The book name.
 *  @return LinkedList* Fined Book.
 */
LinkedList *find_books_by_name(const LinkedList const *book_list, const wchar_t const *book_name);
/*  @brief Find books by ISBN.
 *
 *  Find book by ISBN.
 *
 *  @param book_list The book list to get book.
 *  @param book_ISBN The book's ISBN.
 *  @return LinkedList* Fined Book list.
 */
LinkedList *find_books_by_ISBN(const LinkedList const *book_list, const wchar_t const *book_ISBN);
/*  @brief Find books by number.
 *
 *  Find book by number.
 *
 *  @param book_list The book list to get book.
 *  @param book_number The book's number.
 *  @return Book* Fined Book list.
 */
Book *find_book_by_number(const LinkedList const *book_list, const wchar_t const *book_number);
/*  @brief Find borrow by client and book.
 *
 *  Find borrow by client and book.
 *
 *  @param client The client to get borrow.
 *  @param book The book to get borrow.
 *  @return Borrow* Fined Borrow.
 */
Borrow *find_borrow(Client const *client, Book const *book);

/*  @brief remove client to client list.
 *
 *  Find client and remove the list.
 *  Free client, unused list memory.
 *
 *  @param client_list The client list to remove client.
 *  @param client The client will be removed.
 *  @return void.
 */
void remove_client(LinkedList const *client_list, Client const *client);
/*  @brief remove book to book list.
 *
 *  Find book and remove the list.
 *  Free book, unused list memory.
 *
 *  @param book_list The book list to remove book.
 *  @param book The book will be removed.
 *  @return void.
 */
void remove_book(LinkedList const *book_list, Book const *book);
/*  @brief remove borrow to borrow list.
 *
 *  Find borrow and remove the list.
 *  Free borrow, unused list memory.
 *
 *  @param borrow_list The borrow list to remove borrow.
 *  @param borrow The borrow will be removed.
 *  @return void.
 */
void remove_borrow(LinkedList const *borrow_list, Borrow const *borrow);

/*  @brief Free memory for list.
 *
 *  Free momory for list but, It isn't free list's member.
 *
 *  @param list Linked list to free memory.
 *  @return void.
 */
void destory_list(LinkedList *list);

/*  @brief Destory client list.
 *
 *  Save client data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param client_list Linked list, it have client data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destory_clients(LinkedList *client_list, const char const *file_name);
/*  @brief Destory book list.
 *
 *  Save book data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param book_list Linked list, it have book data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destory_books(LinkedList *book_list, const char const *file_name);
/*  @brief Destory borrow list.
 *
 *  Save borrow data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param borrow_list Linked list, it have borrow data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destory_borrows(LinkedList *borrow_list, const char const *file_name);

/*  @brief Destory client.
 *
 *  Free client's member
 *  Free client
 *
 *  @param client Client to free.
 *  @return void.
 */
void destory_client(Client const *client);
/*  @brief Destory book.
 *
 *  Free book's member
 *  Free book
 *
 *  @param book Book to free.
 *  @return void.
 */
void destory_book(Book const *book);
/*  @brief Destory borrow.
 *
 *  Free borrow's member
 *  Free borrow
 *
 *  @param borrow Borrow to free.
 *  @return void.
 */
void destory_borrow(Borrow const *borrow);

/*  @brief Init screens.
 *
 *  Allocate memory for screens.
 *  Set screen's type.
 *  Link screen's function pointer.
 *  Init type to init screen.
 *
 *  @param void.
 *  @return Screens* Initaled screens.
 */
Screens *init_screens(void);
/*  @brief Change screen.
 *
 *  Change screens's type
 *
 *  @param screens The screens to change.
 *  @param type The type to change.
 *  @return void.
 */
void change_screen(Screens const *screens, char type);
/*  @brief Clear screen.
 *
 *  Clear screen.
 *
 *  @param void.
 *  @return void.
 */
void clear_screen(void);
/*  @brief Draw screen.
 *
 *  Fine current screen by type.
 *  Call draw function linked current screen.
 *
 *  @param screens screen data.
 *  @param data program's all data.
 *  @return void.
 */
void draw_screen(Screens const *screens, Data const *data);
/*  @brief Get input data and call current function.
 *
 *  Fine current screen by type.
 *  Call input function linked current screen.
 *
 *  @param screens screen data.
 *  @param data program's all data.
 *  @return void.
 */
void input_screen(Screens *screens, Data const *data);
/*  @brief Destory screens.
 *
 *  Free memory to screens.
 *
 *  @param screens screen data.
 *  @return void.
 */
void destory_screens(Screens *screens);

/*  @brief Draw init screen.
 *
 *  Draw init screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_init_screen(Data const *data);
/*  @brief Process init screen's input data.
 *
 *  Process init screen's input data.
 *
 *  @param input input string.
 *  @param data program's all data.
 *  @return void.
 */
void input_init_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw sign up screen.
 *
 *  Draw sign up screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_sign_up_screen(Data const *data);
/*  @brief Process sign up screen's input data.
 *
 *  Process sign up screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_sign_up_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw sign in screen.
 *
 *  Draw sign in screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_sign_in_screen(Data const *data);
/*  @brief Process sign in screen's input data.
 *
 *  Process sign in screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_sign_in_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw menu member screen.
 *
 *  Draw menu member screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_menu_member_screen(Data const *data);
/*  @brief Process menu member screen's input data.
 *
 *  Process menu member screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_menu_member_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw menu admin screen.
 *
 *  Draw menu admin screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_menu_admin_screen(Data const *data);
/*  @brief Process menu admin screen's input data.
 *
 *  Process menu admin screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_menu_admin_screen(const wchar_t const *input, Data const *data);

/*   @prog Library manager
 *
 *   Library manager program for programming team project
 *  1. Init datas.
 *  2. Clear screen.
 *  3. Draw screen.
 *  4. Get input string and processing.
 *  5. If program is running, go to step 2.
 *  6. Save all data and free the memory.
 *  7. End the program.
 *
 *   @author Park Si-Yual.
 *  @recent 2018-11-03.
 */
int main(void)
{
	Data data;

	setlocale(LC_ALL, "");

	data.clients = init_clients(STRING_CLIENT_FILE);
	data.books = init_books(STRING_BOOK_FILE);
	data.borrows = init_borrows(STRING_BORROW_FILE);

	data.screens = init_screens();

	data.is_running = 1;
	while (data.is_running)
	{
		clear_screen();
		draw_screen(data.screens, &data);
		input_screen(data.screens, &data);
	}

	destory_clients(data.clients, STRING_CLIENT_FILE);
	destory_books(data.books, STRING_BOOK_FILE);
	destory_borrows(data.borrows, STRING_BORROW_FILE);

	destory_screens(data.screens);

	return 0;
}


LinkedList *init_clients(const char const *file_name) { }
LinkedList *init_books(const char const *file_name) { }
LinkedList *init_borrows(const char const *file_name) { }

Book *create_book(wchar_t *name, wchar_t *publisher, wchar_t *author, wchar_t *ISBN, wchar_t *location) {
	Book * book_p=(Book *)malloc(sizeof(Book));
	book_p->name = name;
	book_p->publisher = publisher;
	book_p->author = author;
	book_p->location = location;
	wcscpy(book_p->ISBN, ISBN);
	book_p->availability = 'Y';
	/* 도서번호는 마지막으로 등록한 책의 번호+1 이여야하는데 이 함수는 마지막으로 등록한 책의 번호를 알수 없어서 당장은 못만듬
	 * 나중에 매개변수로 데이터파일을 설정하든지 아니면 다른방법을 찾아볼거임 */
	return book_p;
}

Borrow *create_borrow(Client const *client, Book const *book) {
	Borrow * borrow_p=(Borrow *)malloc(sizeof(Borrow));
	time_t now;
	now = time(NULL);
	struct tm *t;
	t = localtime(&now);
	wcscpy(borrow_p->student_number, client->student_number);
	wcscpy(borrow_p->book_number, book->number);
	borrow_p->loan_date = now;
	if ((t->tm_wday + 30) / 7 == 0)//(t->tm_wday+30)/7==30일 뒤의 요일
		borrow_p->return_date = now + 31 * 24 * 60 * 60;
	else
		borrow_p->return_date = now + 30 * 24 * 60 * 60;
	return borrow_p;
}

void print_client(const Client const *client) { }
void print_book(const Book const *book) {
	printf("도서명 : %s \n", book->name);
	printf("출판사 : %s \n", book->publisher);
	printf("저자명 : %s \n", book->author);
	printf("ISBN : %s \n", book->ISBN);
	printf("소장처 : %s \n", book->location);
	printf("대여가능 여부 : %c \n", book->availability);
	return;
}
void print_borrow(const Borrow const *borrow) {
	struct tm * loan_, *return_;
	loan_ = localtime(&(borrow->loan_date));
	return_ = localtime(&(borrow->return_date));
	printf("도서번호 : %s \n", borrow->book_number);
	//printf("도서명 : %s \n", 이거 book데이터도 매개변수에 있어야함 도서명은 borrow에 저장 안함
	printf("대여일자 : %d년 %d월 %d일 ", loan_->tm_year + 1900, loan_->tm_mon + 1, loan_->tm_mday);
	switch (loan_->tm_wday) {
	case 0:
		printf("일요일");
		break;
	case 1:
		printf("월요일");
		break;
	case 2:
		printf("화요일");
		break;
	case 3:
		printf("수요일");
		break;
	case 4:
		printf("목요일");
		break;
	case 5:
		printf("금요일");
		break;
	case 6:
		printf("토요일");
		break;
	default:
		;
	}
	printf("\n");
	printf("반납일자 : %d년 %d월 %d일 ", return_->tm_year + 1900, return_->tm_mon + 1, return_->tm_mday);
	switch (return_->tm_wday) {
	case 0:
		printf("일요일");
		break;
	case 1:
		printf("월요일");
		break;
	case 2:
		printf("화요일");
		break;
	case 3:
		printf("수요일");
		break;
	case 4:
		printf("목요일");
		break;
	case 5:
		printf("금요일");
		break;
	case 6:
		printf("토요일");
		break;
	default:
		;
	}
	printf("\n");
	return;
}

void print_clients(const LinkedList const *client_list) {
	LinkedList * current = client_list->next;
	while (current != NULL) {
		printf("학번 : %s\n", ((Client *)current->contents)->student_number);
		printf("이름 : %s\n", ((Client *)current->contents)->name);
		printf("주소 : %s\n", ((Client *)current->contents)->address);
		printf("전화번호 : %s\n", ((Client *)current->contents)->phone_number);
		current = current->next;
	}
	return;
}

void print_books(const LinkedList const *book_list) {
	LinkedList * current = book_list->next;
	while (current != NULL) {
		printf("도서명: %s \n", ((Book *)current->contents)->name);
		printf("출판사: %s \n", ((Book *)current->contents)->publisher);
		printf("저자명: %s \n", ((Book *)current->contents)->author);
		printf("ISBN : %s \n", ((Book *)current->contents)->ISBN);
		printf("소장처: %s \n", ((Book *)current->contents)->location);
		printf("대여가능여부: %c \n", ((Book *)current->contents)->availability);
		current = current->next;
	}
	return;
}
void print_borrows(const LinkedList const *borrow_list) { }

void save_clients(const LinkedList const *client_list, const char const *file_name) { }
void save_books(const LinkedList const *book_list, const char const *file_name) { }
void save_borrows(const LinkedList const *borrow_list, const char const *file_name) { }

LinkedList *insert_client(LinkedList const *client_list, const Client const *client) {
	LinkedList * current = client_list->next;
	LinkedList * past = client_list;
	LinkedList *new_p = (LinkedList *)malloc(sizeof(LinkedList));
	int c;
	while (current != NULL) {
		c = wcscmp(((Client *)current->contents)->student_number, client->student_number);

		if (c > 0) {
			past->next = new_p;
			new_p->next = current;
			new_p->contents = (void *)client;
			break;
		}

		else if (c == 0)
		{
			printf("이미 존재하는 학번입니다");
			return client_list;
		}

		else {
			past = past->next;
			current = current->next;
		}
	}
	if (current == NULL) {
		past->next = new_p;
		new_p->next = current;
		new_p->contents = (void *)client;
	}
	return client_list;
}
LinkedList *insert_book(LinkedList const *book_list, const Book const *book) {
	LinkedList * current = book_list->next;
	LinkedList * past = book_list;
	LinkedList *new_p = (LinkedList *)malloc(sizeof(LinkedList));
	int c;
	while (current != NULL) {
		c = wcscmp(((Book *)current->contents)->ISBN, book->ISBN);

		if (c >= 0) {
			past->next = new_p;
			new_p->next = current;
			new_p->contents = (void *)book;
			break;
		}




		else {
			past = past->next;
			current = current->next;
		}
	}
	if (current == NULL) {
		past->next = new_p;
		new_p->next = current;
		new_p->contents = (void *)book;
	}
	return book_list;
}
LinkedList *insert_borrow(LinkedList const *borrow_list, const Borrow const *borrow) {
	LinkedList * current = borrow_list->next;
	LinkedList * past = borrow_list;
	LinkedList *new_p = (LinkedList *)malloc(sizeof(LinkedList));
	while (current != NULL) {
		current = current->next;
		past = past->next;
	}
	if (current == NULL) {
		past->next = new_p;
		new_p->next = current;
		new_p->contents = (void *)borrow;
	}
	return borrow_list;
}

Client *find_client_by_student_number(const LinkedList const *client_list, const wchar_t const *student_number) {
	LinkedList * current = client_list->next;
	Client * client;
	int c;
	while (current != NULL) {
		c = wcscmp(((Client *)current->contents)->student_number, student_number);
		if (c != 0)
			current = current->next;
		else {
			client = ((Client *)current->contents);
			return client;
		}
	}
	printf("일치하는 학생번호가 없습니다\n"); //current=NULL 임
	return 0;
}
LinkedList *find_books_by_name(const LinkedList const *book_list, const wchar_t const *book_name) { }
LinkedList *find_books_by_ISBN(const LinkedList const *book_list, const wchar_t const *book_ISBN) { }
Book *find_book_by_number(const LinkedList const *book_list, const wchar_t const *book_number) { }
Borrow *find_borrow(Client const *client, Book const *book) { }

void remove_client(LinkedList const *client_list, Client const *client) { }
void remove_book(LinkedList const *book_list, Book const *book) { }
void remove_borrow(LinkedList const *borrow_list, Borrow const *borrow) { }

void destory_list(LinkedList *list) { }

void destory_clients(LinkedList *client_list, const char const *file_name) { }
void destory_books(LinkedList *book_list, const char const *file_name) { }
void destory_borrows(LinkedList *borrow_list, const char const *file_name) { }

void destory_client(Client const *client) { }
void destory_book(Book const *book) { }
void destory_borrow(Borrow const *borrow) { }

Screens *init_screens(void)
{
	Screens *screens = malloc(sizeof(Screens));
	screens->type = SCREEN_INIT;

	screens->screens[SCREEN_INIT].type = SCREEN_INIT;
	screens->screens[SCREEN_INIT].draw = draw_init_screen;
	screens->screens[SCREEN_INIT].input = input_init_screen;

	screens->screens[SCREEN_MENU_ADMIN].type = SCREEN_MENU_ADMIN;
	screens->screens[SCREEN_MENU_ADMIN].draw = draw_menu_admin_screen;
	screens->screens[SCREEN_MENU_ADMIN].input = input_menu_admin_screen;

	screens->screens[SCREEN_MENU_MEMBER].type = SCREEN_MENU_MEMBER;
	screens->screens[SCREEN_MENU_MEMBER].draw = draw_menu_member_screen;
	screens->screens[SCREEN_MENU_MEMBER].input = input_menu_member_screen;

	screens->screens[SCREEN_SIGN_IN].type = SCREEN_SIGN_IN;
	screens->screens[SCREEN_SIGN_IN].draw = draw_sign_in_screen;
	screens->screens[SCREEN_SIGN_IN].input = input_sign_in_screen;

	screens->screens[SCREEN_SIGN_UP].type = SCREEN_SIGN_UP;
	screens->screens[SCREEN_SIGN_UP].draw = draw_sign_up_screen;
	screens->screens[SCREEN_SIGN_UP].input = input_sign_up_screen;

	return screens;
}
void change_screen(Screens const *screens, char type)
{
	screens->type = type;
}
void clear_screen(void)
{
	printf("\x1B[2J\x1B[1;1H");
}
void draw_screen(Screens const *screens, Data const *data)
{
	screens->screens[screens->type].draw(data)
}
void input_screen(Screens *screens, Data const *data)
{
	wchar_t input[SIZE_INPUT_MAX] = { 0 };
	wscanf(L"%s", input);

	screens->screens[screens->type].input(input, data);
}
void destory_screens(Screens *screens)
{
	if (screens != NULL)
		free(screens);
}

void draw_init_screen(Data const *data)
{
	wprintf(
		L">> 도서관 서비스 <<\n"
		L"1. 회원 가입           2. 로그인           3. 프로그램 종료\n"
		L"번호를 선택하세요: ");
}
void input_init_screen(const wchar_t const *input, Data const *data)
{
	if (input == NULL || data == NULL)
		return;
	if (data->is_admin)
		data->is_admin = 0;

	switch (input[0])
	{
	case L'1':
		change_screen(data->screens, SCREEN_SIGN_UP);
		break;
	case L'2':
		change_screen(data->screens, SCREEN_SIGN_IN);
		break;
	case L'3':
		data->is_running = 0;
		break;
	default:
		break;
	}
}

void draw_sign_up_screen(Data const *data)
{
	wprintf(
		L">> 회원 가입 <<\n"
		L"학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n"
		L"\n"
		L"학번: ");
}
void input_sign_up_screen(const wchar_t const *input, Data const *data)
{
	if (input == NULL || data == NULL)
		return;
	wchar_t input_tmp[SIZE_INPUT_MAX] = { 0 };
	wchar_t *input_p = NULL;
	size_t len = 0;

	Client *client = malloc(sizeof(Client));

	len = wcslen(input);
	input_p = malloc(sizeof(wchar_t) * (len + 1));
	wcscpy(input_p, input);
	client->student_number = input_p;

	wprintf(L"비밀번호: ");
	wscanf(L"%s", input_tmp);
	len = wcslen(input_tmp);
	input_p = malloc(sizeof(wchar_t) * (len + 1));
	wcscpy(input_p, input_tmp);
	client->password = input_p;

	wprintf(L"이름: ");
	wscanf(L"%s", input_tmp);
	len = wcslen(input_tmp);
	input_p = malloc(sizeof(wchar_t) * (len + 1));
	wcscpy(input_p, input_tmp);
	client->name = input_p;

	wprintf(L"주소: ");
	wscanf(L"%s", input_tmp);
	len = wcslen(input_tmp);
	input_p = malloc(sizeof(wchar_t) * (len + 1));
	wcscpy(input_p, input_tmp);
	client->address = input_p;

	wprintf(L"전화번호: ");
	wscanf(L"%s", input_tmp);
	len = wcslen(input_tmp);
	input_p = malloc(sizeof(wchar_t) * (len + 1));
	wcscpy(input_p, input_tmp);
	client->phone_number = input_p;

	insert_client(data->clients, client);
	save_clients(data->clients, STRING_CLIENT_FILE);
	wprintf(L"회원가입이 되셨습니다.");
	sleep(1);
	change_screen(data->screens, SCREEN_INIT);
}

void draw_sign_in_screen(Data const *data)
{
	wprintf(
		L">> 로그인 <<\n"
		L"학번: ");
}
void input_sign_in_screen(const wchar_t const *input, Data const *data)
{
	if (input == NULL || data == NULL)
		return;
	wchar_t input_tmp[SIZE_INPUT_MAX] = { 0 };

	Client *client = find_client_by_student_number(data->clients, input);

	if (client == NULL)
	{
		if (wcscmp(L"admin", input) == 0)
		{
			data->is_admin = 1;
		}
		else
		{
			wprintf(L"회원정보가 없습니다.");
			sleep(1);
			change_screen(data->screens, SCREEN_INIT);

			return;
		}
	}

	wprintf(L"비밀번호: ");
	wscanf(L"%s", input_tmp);

	if (data->is_admin)
	{
		wprintf(L"로그인이 되셨습니다.");
		sleep(1);
		change_screen(data->screens, SCREEN_MENU_ADMIN);
		return;
	}
	if (wcscmp(client->password, input_tmp) == 0)
	{
		data->login_client = client;
		wprintf(L"로그인이 되셨습니다.");
		sleep(1);
		change_screen(data->screens, SCREEN_MENU_MEMBER);
	}
	else
	{
		wprintf(L"잘못된 비밀번호입니다.");
		sleep(1);
		change_screen(data->screens, SCREEN_INIT);
	}
}

void draw_menu_member_screen(Data const *data)
{
	wprintf(
		L">> 회원 메뉴 <<\n"
		L"1. 도서 검색           2. 내 대여 목록\n"
		L"3. 개인정보 수정       4. 회원 탈퇴\n"
		L"5. 로그아웃            6. 프로그램 종료\n"
		L"\n"
		L"번호를 선택하세요: ");
}
void input_menu_member_screen(const wchar_t const *input, Data const *data)
{
	if (input == NULL || data == NULL)
		return;

	switch (input[0])
	{
	case L'6':
		data->is_running = 0;
		break;
	default:
		break;
	}
}

void draw_menu_admin_screen(Data const *data)
{
	wprintf(
		L">> 관리자 메뉴 <<\n"
		L"1. 도서 등록           2. 도서 삭제\n"
		L"3. 도서 대여           4. 도서 반납\n"
		L"5. 도서 검색           6. 회원 목록\n"
		L"7. 로그아웃            8. 프로그램 종료\n"
		L"\n"
		L"번호를 선택하세요: ");
}
void input_menu_admin_screen(const wchar_t const *input, Data const *data)
{
	if (input == NULL || data == NULL)
		return;

	switch (input[0])
	{
	case L'8':
		data->is_running = 0;
		break;
	default:
		break;
	}
}