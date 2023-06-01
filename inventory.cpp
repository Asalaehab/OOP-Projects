#include <iostream>
using namespace std;
class Item
{
private:
	int ID = 0;
	string name;
	int quantity;
	int price;
	friend istream& operator>>(istream& input, Item& obj);
	friend ostream& operator<<(ostream& output, const Item& obj);
public:
	Item()
	{
		name = "no_name";
		quantity = 0;
		price = 0;
	}

	Item(string n, int q, int p)
	{
		name = n;
		quantity = q;
		price = p;
	}

	Item(const Item& ob)
	{

	}

	Item operator+=(const Item& obj)
	{
		this->quantity = (this->quantity + obj.quantity);
		return *this;
	}

	bool operator==(const Item& RHS)
	{
		if (name != RHS.name)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Item operator-=(int c)
	{
		this->quantity = this->quantity - c;
		return *this;
	}

	void setID(int ID)
	{
		this->ID = ID;
	}

	void set_name(string n)
	{
		name = n;
	}

	void set_quantity(int q)
	{
		quantity = q;
	}

	void set_price(int p)
	{
		price = p;
	}

	int getID()
	{
		return ID;
	}

	string get_name()
	{
		return name;
	}

	int get_quantity()
	{
		return quantity;
	}

	int get_price()
	{
		return price;
	}
};

istream& operator>>(istream& input, Item& obj)
{
	cout << "Please Enter Name : ";
	input >> obj.name;
	cout << "please Enter the quantity : ";
	input >> obj.quantity;
	cout << "please Enter the price : ";
	input >> obj.price;
	return input;
}

ostream& operator<<(ostream& output, const Item& obj)
{
	output << "Item Name: " << obj.name
		<< ", Item Price: " << obj.price
		<< ", Item Quantity: " << obj.quantity
		<< ", Item ID: " << obj.ID << endl;
	return output;
}

class Seller {
private:
	string name, email;
	int maxItems;
	int itemCounter;
	int ID_Search;
	Item* items;
	Item default_Obj;
	friend ostream& operator<<(ostream& output, Seller& ob);
public:
	Seller()
	{
		name = "no_name";
		email = "no_mail";
		maxItems = 0;
		itemCounter = 0;
	}

	Seller(string name, string email, int maxItems)
	{
		this->name = name;
		this->email = email;
		this->maxItems = maxItems;

		items = new Item[maxItems];
	}

	~Seller()
	{
		delete[]items;
		items = NULL;
	}

public:

	bool AddAnItem(Item obj)
	{
		// to ceack the if u can store other items or not;
		if (itemCounter == maxItems)
		{
			cout << endl << "No Storage Avaliable" << endl;
			return false;
		}

		items[itemCounter] = obj;

		cin >> items[itemCounter];

		items[itemCounter].setID(itemCounter + 1);

		// to ceack the if the two items have the same name or not;
		for (int i = 0; i < maxItems; i++)
		{
			if (items[itemCounter] == items[i] && itemCounter != i)
			{
				items[i] += items[itemCounter];
				items[i].set_quantity(items[i].get_quantity());
				cout << endl << "This Item Is Already Exist, Quantity Increased Succesfuly, Increased Quantity is: " << items[i].get_quantity() << endl;

				items[itemCounter] = obj;

				return false;
			}
		}

		itemCounter++;
		return true;
	}

	bool sellAnItem(string name, int quantity)
	{
		int counter = 0, get_Last_Index;
		for (int i = 0; i < maxItems; i++)
		{
			if (items[i].get_name() == name)
			{
				counter++;
				get_Last_Index = i;
			}
		}
		if (counter > 0)
		{
			cout << endl << "The Item Is Found, " << "The New Quantity Is : " << items[get_Last_Index].get_quantity() - quantity << endl;

			if (items[get_Last_Index].get_quantity() >= quantity)
			{
				items[get_Last_Index] -= quantity;
			}
			else
			{
				cout << endl << "There is only " << items[get_Last_Index].get_quantity() << " left for this item" << endl;
				return false;
			}
			return true;
		}
		else
		{
			cout << endl << "Item Is Not Found" << endl;
			return false;
		}
	}

	Item* printItems(int index, int choice)
	{
		if (choice == 4)
		{
			cout << items[index];
			return &items[index];
		}
		else
		{
			return &items[index];
		}
	}

	Item* find_An_Item_By_ID()
	{
		cout << endl << "PLease Enter The Items'ID: ";
		cin >> ID_Search;
		for (int i = 0; i < maxItems; i++)
		{
			if (ID_Search == items[i].getID() && ID_Search != 0)
			{
				cout << endl << "ID Is Found!" << endl;
				return &items[i];
			}
		}
		return &default_Obj;
	}

	void Print_My_Info(Seller obj)
	{
		cout << obj;
	}
};

ostream& operator<<(ostream& output, Seller& obj)
{
	output << endl << "The Seller 's name is: " << obj.name << endl
		<< "the Seller 's e_mail is: " << obj.email << endl
		<< "the capacity that he want to buy is: " << obj.maxItems << endl;
	return output;
}

int main()
{
	string name, email;
	int maxItems, choice, ID_For_Searching_On;

	cout << "Please enter your name :";
	cin >> name;
	cout << "Enter Your Email: ";
	cin >> email;
	cout << "Enter The Store Capacity : ";
	cin >> maxItems;

	Seller seller(name, email, maxItems);
	Item items, itemForSelling;

	while (true)
	{
		cout << endl;
		cout << "1. Print My Info" << endl;
		cout << "2. Add An Item" << endl;
		cout << "3. Sell An Item" << endl;
		cout << "4. Print Items" << endl;
		cout << "5. Find an Item by ID" << endl;
		cout << "6. Exit" << endl;
		cout << endl;

		cout << "choice from this options: ";
		cin >> choice;

		if (choice == 1)
		{
			seller.Print_My_Info(seller);
		}

		else if (choice == 2)
		{
			if (seller.AddAnItem(items))
			{
				cout << endl << "Item Added Succesfully" << endl;
			}
		}

		else if (choice == 3)
		{
			cin >> itemForSelling;
			seller.sellAnItem(itemForSelling.get_name(), itemForSelling.get_quantity());
		}

		else if (choice == 4)
		{
			for (int i = 0; i < maxItems; i++)
			{
				seller.printItems(i, choice);
			}
		}

		else if (choice == 5)
		{

			ID_For_Searching_On = seller.find_An_Item_By_ID()->getID();

			if (ID_For_Searching_On == 0)
			{
				cout << endl << "Can Not Find An ID" << endl;
			}
			else
			{
				for (int i = 0; i < maxItems; i++)
				{
					if (seller.printItems(i, choice)->getID() == ID_For_Searching_On)
					{
						seller.printItems(i, 4);
						break;
					}
				}
			}
		}

		else if (choice == 6)
		{
			break;
		}
	}
	return 0;
}
