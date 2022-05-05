
/* ***************************************************
 * Asad Islam
 * asadulshakib10@gmail.com
 * 213902054, 213DB, Green University of Bangladesh

 * ***************************************************
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


char * CurrentTime()
{

 time_t time_function = time(NULL);
    struct tm *time_pointer = localtime(&time_function);

    char temp[51];
    strftime(temp, sizeof(temp), "%c", time_pointer);

    char * current_time = (char *) malloc(sizeof(char));
    strcpy(current_time, temp);

    return (char *) current_time;
}


/** =-==-=-==-=-==-=-==-=-==-=-==-=-==-=
    - - - - - - structures - - - - - -
    =-==-=-==-=-==-=-==-=-==-=-==-=-==-=*/

typedef struct product
{
	char product_name[20];
	float product_price;
	int product_count;
} product;

typedef struct products{
	product * product;
	struct products * next_product;
} products;


/* =-==-=-==-=-==-=-==-=-==-=-==-=-==-=
  - - - - - - prototypes - - - - - -
 =-==-=-==-=-==-=-==-=-==-=-==-=-==-=*/

product		* BlankProduct();
products 	* BlankProducts();
// ---------
product		* InsertIntoProduct(char product_name[20], float product_price,int product_count);
products	* InsertIntoProducts(products * all_products, product * chk);
// ---------
products	* AddSampleProducts();
products	* AddProduct(products * all_products);
// ---------
float	GetProductPrice(products * all_products, char * product_name);
int		GetProductQuantity(products * all_products, char * product_name);
void	UpdateProductQuantity(products * all_products, char * product_name, int product_count);
// ---------
void	SearchProductsByName(products * all_products, char * product_name);
void	SearchProductsByPricerange(products * all_products, float min_price, float max_price);
void	SearchProducts(products * all_products);
// ---------
void	ScreenSellingProducts(products * all_products);
void	SellAndCashMemo(products * all_products);
// ---------
char	* RecordFile();
FILE	* CreateRecordFile(char * file_name);
void	RecordIntoFile(char * data, char * file_name);
void	RecordProductIntoFile(char * product_name, float product_price, int product_count);

products 	* RefreshDatabase();
// ---------
void	ScreenProducts(products * all_products);
void	Dashboard(products * all_products);



/* =-==-=-==-=-==-=-==-=-==-=-==-=-==-=
//  - - - - - - functions - - - - - -
// =-==-=-==-=-==-=-==-=-==-=-==-=-==-=*/

product * BlankProduct()
{
	product * blank = (product *) malloc(sizeof(product));

	return blank;
}

products * BlankProducts(){
	products * blank = (products *) malloc(sizeof(products));
	blank -> next_product = NULL;

	return blank;
}

// -------------

product * InsertIntoProduct(
	char product_name[20],
	float product_price,
	int product_count
)
{
	product * chk = BlankProduct();
	strcpy(chk -> product_name, product_name);
	chk -> product_price = product_price;
	chk -> product_count = product_count;

	return chk;
}

products * InsertIntoProducts(products * all_products, product * product)
{
	products * chk = BlankProducts();
	chk -> product = product;

	products * temp = BlankProducts();
	temp = all_products;

	if(temp == NULL)
	{
		all_products = chk;
	}
	else
	{
		while(temp -> next_product != NULL)
		{
			temp = temp -> next_product;
		}
		temp -> next_product = chk;
	}

	return all_products;
}

// -------------

products * AddSampleProducts(){
	products * all_products = BlankProducts();
	products * sample_product1 = BlankProducts();
	products * sample_product2 = BlankProducts();
	products * sample_product3 = BlankProducts();
	products * sample_product4 = BlankProducts();

	sample_product1 -> product = InsertIntoProduct("Chal", 50, 100);
	sample_product2 -> product = InsertIntoProduct("Dal", 100, 200);
	sample_product3 -> product = InsertIntoProduct("Dudh", 150, 300);
	sample_product4 -> product = InsertIntoProduct("Kola", 150, 300);

	RecordProductIntoFile("Chal", 50, 100);
	RecordProductIntoFile("Dal", 10, 200);
	RecordProductIntoFile("Dudh", 150, 300);
	RecordProductIntoFile("Kola", 150, 300);

	sample_product1 -> next_product = sample_product2;
	sample_product2 -> next_product = sample_product3;
	sample_product3 -> next_product = sample_product4;
	sample_product4 -> next_product = NULL;

	all_products = sample_product1;

	return all_products;
}

products * AddProduct(products * all_products)
{
	char product_name[20] = "";
	float product_price = 1.1;
	int product_count = 1;

	printf(
		"---------------\n"
		" Add Product \n"
		"---------------\n"
		"\n"
	);

	printf(
		"Product Name: "
	);
	getchar();
	gets(product_name);

	printf(
		"Product Price: "
	);
	scanf("%f", &product_price);

	printf(
		"Product Count: "
	);
	scanf("%d", &product_count);

	product * product = InsertIntoProduct(product_name, product_price, product_count);
	printf(
		"\n\n"
		"Product Added\n"
	);

	all_products = InsertIntoProducts(all_products, product);
	RecordProductIntoFile(product_name, product_price, product_count);

	printf(
		"Do You Want To Add More? - Y/N\n"
	);

	char answer;
	answer = getch();

	if(answer == 'y')
	{
		system("cls");
		AddProduct(all_products);
	}

	return all_products;
}

// -------------

float GetProductPrice(products * all_products, char * product_name)
{
	products * each_product = BlankProducts();
	each_product = all_products;

	int sl = 0, product_price = -1;

	while(each_product != NULL)
	{
		if(strcmp(each_product -> product -> product_name, product_name) == 0)
		{
			product_price = each_product -> product -> product_price;
		}
		each_product = each_product -> next_product;
	}

	return product_price;
}

int GetProductQuantity(products * all_products, char * product_name)
{
	products * each_product = BlankProducts();
	each_product = all_products;

	int sl = 0, product_count = -1;

	while(each_product != NULL)
	{
		if(strcmp(each_product -> product -> product_name, product_name) == 0)
		{
			product_count = each_product -> product -> product_count;
		}
		each_product = each_product -> next_product;
	}

	return product_count;
}

void UpdateProductQuantity(products * all_products, char * product_name, int product_count)
{
	products * each_product = BlankProducts();
	each_product = all_products;

	int sl = 0;

	while(each_product != NULL)
	{
		if(strcmp(each_product -> product -> product_name, product_name) == 0)
		{
			each_product -> product -> product_count = product_count;
		}
		each_product = each_product -> next_product;
	}
}

// -------------

void SearchProductsByName(products * all_products, char * product_name)
{
	products * each_product = BlankProducts();
	each_product = all_products;
	printf(
		"\n\n"
		"Search Result:\n"
	);
	printf(
		"----------------------------------------------------------\n"
		"SL\tProduct\t\t\tPrice\t\tAvailable\n"
		"----------------------------------------------------------\n"
		"\n"
	);
	int sl = 0, product_found = 0;
	while(each_product != NULL){
		if(strcmp(each_product -> product -> product_name, product_name) == 0)
		{
			printf(
				"%d\t%.9s\t\t\t%.2f\t\t  %d\n",
				++sl,
				each_product -> product -> product_name,
				each_product -> product -> product_price,
				each_product -> product -> product_count
			);
			product_found = 1;
		}
		each_product = each_product -> next_product;
	}
	if(product_found == 0)
	{
		printf("No Product Found\n");
	}
}

void SearchProductsByPricerange(products * all_products, float min_price, float max_price)
{
	products * each_product = BlankProducts();
	each_product = all_products;
	printf(
		"\n\n"
		"Search Result\n"
	);
	printf(
		"----------------------------------------------------------\n"
		"SL\tProduct\t\t\tPrice\t\tQuantity\n"
		"----------------------------------------------------------\n"
		"\n"
	);
	int sl = 0, product_found = 0;
	while(each_product != NULL){
		if(
			(each_product -> product -> product_price) >= min_price &&
			(each_product -> product -> product_price) <= max_price
		){
			printf(
				"%d\t%.9s\t\t\t%.2f\t\t  %d\n",
				++sl,
				each_product -> product -> product_name,
				each_product -> product -> product_price,
				each_product -> product -> product_count
			);
			product_found = 1;
		}

		each_product = each_product -> next_product;
	}
	if(product_found == 0){
		printf("No Product Found\n");
	}
}

void SearchProducts(products * all_products)
{
	system("cls");
	printf(
		"--------------------\n"
		" Search Products\n"
		"--------------------\n"
		"\n"
	);
	printf(
		"1. Search By Product Name\n"
		"2. Search By Price Range\n"
		"\n"
	);
	int option;
	printf("Option: ");
	scanf("%d", &option);
	printf("\n");
	if(option == 1){
		char search_product_name[20];
		printf("Product Name: ");
		getchar();
		gets(search_product_name);
		SearchProductsByName(all_products, search_product_name);
	}else{
		float min_price, max_price;
		printf("Set Range Of Price: ");
		scanf("%f %f", &min_price, &max_price);
		SearchProductsByPricerange(all_products, min_price, max_price);
	}
}

// -------------

void ScreenSellingProducts(products * all_products){
	products * each_product = BlankProducts();
	each_product = all_products;
	float total_price = 0;
	printf(
		"---------------------------------------------------------------------\n"
		"SL\tProduct\t\tUnit\tUnitprice\tNetprice\n"
		"---------------------------------------------------------------------\n"
		"\n"
	);
	int sl = 0;
	if(each_product == NULL)
	{
		printf("No Products Found\n");
	}
	while(each_product != NULL){
		printf(
			"%d\t%.9s\t\t %d\t  %.2f\t\t%.2f\n",
			++sl,
			each_product -> product -> product_name,
			each_product -> product -> product_count,
			each_product -> product -> product_price,
			each_product -> product -> product_price * each_product -> product -> product_count
		);
		total_price = total_price + (each_product -> product -> product_price * each_product -> product -> product_count);
		each_product = each_product -> next_product;
	}
	printf(
		"\n"
		"---------------------------------------------------------------------\n"
		"Total:\t\t\t\t\t\t%.2f\n"
		"---------------------------------------------------------------------\n"
		"\n",
		total_price
	);
}

void SellAndCashMemo(products * all_products)
{
	char customer_name[20];
	char customer_phone[15];
	char product_name[20];
	int product_quantity;
	int num_of_products;
	int sl = 1;
	float product_price;

	printf("Customer Name: ");
	getchar();
	gets(customer_name);

	printf("Contact: ");
	gets(customer_phone);

	printf(
		"\n"
		"Number Of Products: "
	);
	scanf("%d", &num_of_products);
	printf("\n\n");

	products * sold_products = NULL;

	int loo;
	for(loo = 0; loo < num_of_products; loo++){
		printf("Product Name: ");
		getchar();
		gets(product_name);

		printf("Product Quantity: ");
		scanf("%d", &product_quantity);
		product_price = GetProductPrice(all_products, product_name);
		product * sold_product_item = InsertIntoProduct(
			product_name,
			product_price,
			product_quantity
		);
		sold_products = InsertIntoProducts(sold_products, sold_product_item);
		printf("\n");
		UpdateProductQuantity(all_products, product_name, (GetProductQuantity(all_products, product_name) - product_quantity));
	}

	printf(
		"\n\n"
		"Product Sold To: \n"
		"\tCustomer Name: %s\n"
		"\tContact: %s\n"
		"\n",
		customer_name, customer_phone
	);

	ScreenSellingProducts(sold_products);
}

char * RecordFile(){
	return "RecordFile.txt";
}

// -------------

FILE * CreateRecordFile(char * file_name){
	FILE * RecordFile = fopen(file_name, "a+");
	if(RecordFile == NULL){
        puts("Sorry! Cant open file");
        // StopProcessing();
        exit(1);
    }
	return RecordFile;
}

void RecordIntoFile(char * data, char * file_name){
	FILE * pointr = CreateRecordFile(file_name);
	fputs(data, pointr);
	fclose(pointr);
}

void RecordProductIntoFile(char * product_name, float product_price, int product_count)
{
	char * string_product_price = (char *) malloc(sizeof(char));
	char * string_product_count = (char *) malloc(sizeof(char));

	itoa(product_price, string_product_price, 10);
	itoa(product_count, string_product_count, 10);

	RecordIntoFile(product_name, RecordFile());
	RecordIntoFile(",", RecordFile());

	RecordIntoFile(string_product_price , RecordFile());
	RecordIntoFile(",", RecordFile());

	RecordIntoFile(string_product_count, RecordFile());
	RecordIntoFile("\n", RecordFile());
}

void ScreenFromRecordFile(){
	FILE * pointr = CreateRecordFile(RecordFile());
	char test[123];

	printf("$$- products information from database\n");
	printf(
		"----------------------------------------------------------\n"
		"Sl\tProduct\t\tPrice\t\tAvailable\n"
		"----------------------------------------------------------\n"
		"\n"
	);

	int sl = 1;
	while(fgets(test, 123, pointr)){
		int chk1;
		printf("%d\t", sl++);
		for(chk1 = 0; chk1 < strlen(test); chk1++){
			if(test[chk1] == ','){
				printf("\t\t");
			}else{
				printf("%c", test[chk1]);
			}

		}
	}
	fclose(pointr);
}

products * RefreshDatabase()
{
	products * all_products = NULL;
	FILE * pointr = CreateRecordFile(RecordFile());
	char each_line[123];

	int sl = 1;

	char * str_product_name = (char *) malloc(sizeof(char));
	char * str_product_price = (char *) malloc(sizeof(char));
	char * str_product_count = (char *) malloc(sizeof(char));

	while(fgets(each_line, 123, pointr))
	{
		int chk1, chk12, chk13, chk14;

		for(int temp = 0; temp < 15; temp++)
		{
			str_product_name[temp] = '\0';
			str_product_price[temp] = '\0';
			str_product_count[temp] = '\0';
		}
		int commacount = 0;
		for(chk1 = 0, chk12 = 0, chk13 = 0, chk14 = 0; chk1 < strlen(each_line); chk1++)
		{
			if(each_line[chk1] != ',' && commacount < 1){
				str_product_name[chk12++] = each_line[chk1];
			}

			if(each_line[chk1] == ',')
			{
				commacount++;
			}
			if(commacount < 2)
			{

				if(each_line[chk1] >= 48 && each_line[chk1] <= 57)
				{
					str_product_price[chk13++] = each_line[chk1];
				}
			}
			if(commacount >= 2 && each_line[chk1] != '\n'){
				if(each_line[chk1] >= 48 && each_line[chk1] <= 57)
				{
					str_product_count[chk14++] = each_line[chk1];
				}
			}
		}

		float product_price =  atof(str_product_price);
		int product_count =  atoi(str_product_count);


		product * product = InsertIntoProduct(
			str_product_name,
			product_price,
			product_count
		);
		all_products = InsertIntoProducts(all_products, product);
	}

	fclose(pointr);

	return all_products;
}

// -------------

void ScreenProducts(products * all_products)
{
	products * each_product = BlankProducts();
	each_product = all_products;
	printf("$$- Products Information Here\n");
	printf(
		"----------------------------------------------------------\n"
		"SL\tProduct\t\t\tPrice\t\tAvailable\n"
		"----------------------------------------------------------\n"
		"\n"
	);
	int sl = 0;
	if(each_product == NULL){
		printf("No Products Found\n");
	}
	while(each_product != NULL)
	{
		printf(
			"%d\t%.9s\t\t\t%.2f\t\t  %d\n",
			++sl,
			each_product -> product -> product_name,
			each_product -> product -> product_price,
			each_product -> product -> product_count
		);
		each_product = each_product -> next_product;
	}
}

void Dashboard(products * all_products)
{
	all_products = RefreshDatabase();
	system("cls");

printf("%s\n", CurrentTime());	
	
	printf(
		"------------\n"
		" Dashboard\n"
		"------------\n"
	);

	printf(
		"1. Add Product\n"
		"2. Show All Product\n"
		"3. Search Product\n"
		"4. Invoice\n"
		"5. Sample Product\n"
		// "6. show all products from database\n"
		"6. Exit\n"
	);

	int option;
	printf(
		"\n"
		"Choose Your Option: "
	);
	scanf("%d", &option);

	system("cls");

	if(option == 1)
	{
		all_products = AddProduct(all_products);
	}
	else if(option == 2)
	{
		all_products = RefreshDatabase();
		ScreenProducts(all_products);
	}
	else if(option == 3)
	{
        SearchProducts(all_products);
	}
	else if(option == 4)
	{
		SellAndCashMemo(all_products);
	}
	else if(option == 5)
	{
		printf("Sample Product Added\n");
		all_products = AddSampleProducts();
	}
	// else if(option == 6){
	// 	ScreenFromRecordFile();
	// }
	else if(option == 6){
		printf("Thank You For Choosing Us\n");
		exit(0);
	}

	printf("\nPress Any Key To Continue\n");
	getch();
	// Sleep(1000);
	Dashboard(all_products);
}


// =-==-=-==-=-==-=-==-=-==-=-==-=-==-=
//  - - - - - - main funcn - - - - - -
// =-==-=-==-=-==-=-==-=-==-=-==-=-==-=

int main()
{
	products * all_products = NULL;
	Dashboard(all_products);

	return 0;
}
