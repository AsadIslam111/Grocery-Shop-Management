/*
	Asad Islam
	213902054@student.green.edu.bd
	213902054, 213-DB
	Green University of Bangladesh
*/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

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


typedef struct product_info
{
    char product_name[20];
	float product_price;
	int product_count;
}
    product_info;

typedef struct products
{
	product_info * single_product;
	struct products * next_product;
}
    products;

void dashboard(products * all_products);

product_info * blank_product_info();
products * blank_products();

products * sample_products();

void screen_products(products * all_products);
void screen_cashmemo(products * all_products);


product_info * insert_product_info
  (
	char product_name[20],
	float product_price,
	int product_count
  );

products * insert_products(products * all_products, product_info * new_product);

products * add_product(products * all_products);

void search_products_by_name(products * all_products, char * product_name);
void search_products_by_pricerange(products * all_products, float min_price, float max_price);
void search_products(products * all_products);

float get_product_price(products * all_products, char * product_name);
int get_product_quantity(products * all_products, char * product_name);
void update_product_quantity(products * all_products, char * product_name, int product_count);

void sell_and_cash_memo(products * all_products);


int main()
{


	/*dashboard();*/
	products * all_products = NULL;



	dashboard(all_products);

    return 0;
}

void sell_and_cash_memo(products * all_products)
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

	printf("Customer Contact Number: ");
	gets(customer_phone);

	printf(
		"\n"
		"Number of Item: "
	);
	scanf("%d", &num_of_products);
	printf("\n\n");

	products * sold_products = NULL;

	int loop;
	for(loop = 0; loop < num_of_products; loop++){
		printf("Product Name: ");
		getchar();
		gets(product_name);

		printf("Product Quantity: ");
		scanf("%d", &product_quantity);
		product_price = get_product_price(all_products, product_name);
		product_info * sold_product_item = insert_product_info(
			product_name,
			product_price,
			product_quantity
		);
		sold_products = insert_products(sold_products, sold_product_item);
		printf("\n");
		update_product_quantity(all_products, product_name, (get_product_quantity(all_products, product_name) - product_quantity));
	}

	printf(
		"\n\n"
		" Product sold to: \n"
		"\tCustomer Name: %s\n"
		"\tCustomer Contact Number: %s\n"
		"\n",
		customer_name, customer_phone
	);

	screen_cashmemo(sold_products);
}

void screen_cashmemo(products * all_products)
{
	products * each_product = blank_products();
	each_product = all_products;
	float total_price = 0;
	printf(
		"---------------------------------------------------------------------\n"
		"SL\tProduct\t\tUnit\tUnit Price\tNet Price\n"
		"---------------------------------------------------------------------\n"
		"\n"
	);
	int sl = 0;
	if(each_product == NULL)
        {
		printf("No Product Found\n");
	    }
	while(each_product != NULL)
        {
		printf(
			"%d\t%.9s\t\t %d\t  %.2f\t\t%.2f\n",
			++sl,
			each_product -> single_product -> product_name,
			each_product -> single_product -> product_count,
			each_product -> single_product -> product_price,
			each_product -> single_product -> product_price * each_product -> single_product -> product_count
		);
		total_price = total_price + (each_product -> single_product -> product_price * each_product -> single_product -> product_count);
		each_product = each_product -> next_product;
    	}
	printf(
		"\n"
		"---------------------------------------------------------------------\n"
		"total:\t\t\t\t\t\t%.2f\n"
		"---------------------------------------------------------------------\n"
		"\n",
		total_price
	);
}

void update_product_quantity(products * all_products, char * product_name, int product_count)
{
	products * each_product = blank_products();
	each_product = all_products;

	int sl = 0;

	while(each_product != NULL)
        {
		if(strcmp(each_product -> single_product -> product_name, product_name) == 0)
            {
			each_product -> single_product -> product_count = product_count;
            }
		each_product = each_product -> next_product;
        }
}

float get_product_price(products * all_products, char * product_name)
{
	products * each_product = blank_products();
	each_product = all_products;

	int sl = 0, product_price = -1;

	while(each_product != NULL)
        {
		if(strcmp(each_product -> single_product -> product_name, product_name) == 0)
            {
			product_price = each_product -> single_product -> product_price;
            }
		each_product = each_product -> next_product;
        }

	return product_price;
}

int get_product_quantity(products * all_products, char * product_name)
{
	products * each_product = blank_products();
	each_product = all_products;

	int sl = 0, product_count = -1;

	while(each_product != NULL)
        {
		if(strcmp(each_product -> single_product -> product_name, product_name) == 0)
            {
			product_count = each_product -> single_product -> product_count;
            }
		each_product = each_product -> next_product;
        }

	return product_count;
}

void search_products(products * all_products)
{
	system("cls");
	printf(
		"--------------------\n"
		" search Product\n"
		"--------------------\n"
		"\n"
	);
	printf(
		"1. Search By Product Name\n"
		"2. Search By Price Range\n"
		"\n"
         );
	int option;
	printf("option: ");
	scanf("%d", &option);
	printf("\n");
	if(option == 1)
      {
		char search_product_name[20];
		printf("Product Name: ");
		getchar();
		gets(search_product_name);
		search_products_by_name(all_products, search_product_name);
      }
       else
      {
		float min_price, max_price;
		printf("\n NOTE:Input Range By Pressing Enter Button ");
		printf("\n Enter Price Range: ");
		scanf("%f %f", &min_price, &max_price);
		search_products_by_pricerange(all_products, min_price, max_price);
      }
}

void search_products_by_pricerange(products * all_products, float min_price, float max_price)
{
	products * each_product = blank_products();
	each_product = all_products;
	printf(
		"\n\n"
		"**Search Result**\n"
	);
	printf(
		"----------------------------------------------------------\n"
		"SL\tProduct\t\t\tPrice\t\tQuantity\n"
		"----------------------------------------------------------\n"
		"\n"
	);
	int sl = 0, product_found = 0;
	while(each_product != NULL)
      {
		if(
			(each_product -> single_product -> product_price) >= min_price
                                        &&
			(each_product -> single_product -> product_price) <= max_price
          )
	    	{
			printf(
				"%d\t%.9s\t\t\t%.2f\t\t  %d\n",
				++sl,
				each_product -> single_product -> product_name,
				each_product -> single_product -> product_price,
				each_product -> single_product -> product_count
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


void search_products_by_name(products * all_products, char * product_name)
{
	products * each_product = blank_products();
	each_product = all_products;
	printf(
		"\n\n"
		"** Search Result **\n"
	);
	printf(
		"----------------------------------------------------------\n"
		"SL\tProduct\t\t\tPrice\t\tAvailable\n"
		"----------------------------------------------------------\n"
		"\n"
	);
	int sl = 0, product_found = 0;
	while(each_product != NULL)
    {
		if(strcmp(each_product -> single_product -> product_name, product_name) == 0)
		   {
			printf(
				"%d\t%.9s\t\t\t%.2f\t\t  %d\n",
				++sl,
				each_product -> single_product -> product_name,
				each_product -> single_product -> product_price,
				each_product -> single_product -> product_count
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

products * add_product(products * all_products)
{
    char product_name[20] = "ljk";
	float product_price = 123.1;
	int product_count = 123;

	printf(
		"--------------------------\n"
		" Add Product Here\n"
		"--------------------------\n"
		"\n"
	);

	printf("Product Name: "	);
	getchar();
	gets(product_name);

	printf("Product Price: "	);
	scanf("%f", &product_price);

	printf("product count: ");
	scanf("%d", &product_count);
	// products * new_product = NULL;

	product_info * new_product_info = insert_product_info(product_name, product_price, product_count);
	// new_product -> single_product = new_product_info;
	printf(
		"\n\n"
		"** Product Added **\n"
	);

	all_products = insert_products(all_products, new_product_info);

	return all_products;
}

products * insert_products(products * all_products, product_info * new_product_info)
{
	products * new_product = blank_products();
	new_product -> single_product = new_product_info;

	products * temp = blank_products();
	temp = all_products;

	if(temp == NULL)
           {
		    all_products = new_product;
	        }
    else
	    {
		while(temp -> next_product != NULL)
            {
			temp = temp -> next_product;
	     	}
		temp -> next_product = new_product;
	    }


	return all_products;
}


product_info * insert_product_info
(
	char product_name[20],
	float product_price,
	int product_count
)

{
	product_info * new_product = blank_product_info();
	strcpy(new_product -> product_name, product_name);
	new_product -> product_price = product_price;
	new_product -> product_count = product_count;
	return new_product;
}

void screen_products(products * all_products)
{
	products * each_product = blank_products();
	each_product = all_products;
	printf("** Product Information **\n");
	printf(
		"----------------------------------------------------------\n"
		" SL\tProduct\t\t\tPrice\t\tAvailable\n "
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
			each_product -> single_product -> product_name,
			each_product -> single_product -> product_price,
			each_product -> single_product -> product_count
		);
		each_product = each_product -> next_product;
     }
}

product_info * blank_product_info()
{
	product_info * blank = (product_info *) malloc(sizeof(product_info));
	return blank;
}
products * blank_products()
{
	products * blank = (products *) malloc(sizeof(products));
	blank -> next_product = NULL;
	return blank;
}

products * sample_products()
{
	products * all_products = blank_products();
	products * sample_product1 = blank_products();
	products * sample_product2 = blank_products();
	products * sample_product3 = blank_products();

	sample_product1 -> single_product = insert_product_info("Chal", 10, 100);
	sample_product2 -> single_product = insert_product_info("Daal", 20, 200);
	sample_product3 -> single_product = insert_product_info("Dudh", 30, 300);
	sample_product3 -> single_product = insert_product_info("Dim", 30, 300);

	sample_product1 -> next_product = sample_product2;
	sample_product2 -> next_product = sample_product3;
	sample_product3 -> next_product = NULL;

	all_products = sample_product1;

	return all_products;
}


void dashboard(products * all_products)
{

	system("cls");

	printf("%s\n", CurrentTime());

	printf(
		"------------\n"
		" Dashboard\n"
		"------------\n"
                         );

	printf(
		"1. Add Product\n"
		"2. Show All Products\n"
		"3. Search product\n"
		"4. Invoice\n"
		"5. Sample Products\n"
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
		all_products = add_product(all_products);
	 }
	else if(option == 2)
	    {
		screen_products(all_products);
	    }
    else if(option == 3)
	    {
		search_products(all_products);
	    }
    else if(option == 4)
	    {
		sell_and_cash_memo(all_products);
	    }
    else if(option == 5)
	{
		printf("** Sample Product Added **\n");
		all_products = sample_products();
	}
	else if(option == 6)
	{
		printf("Exit With Respect..\n");
		exit(0);
	}

	printf(

        "Press ENTER To Continue\n");

	getch();

	dashboard(all_products);
}
