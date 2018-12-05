#pragma once
#include <iostream>
#include <string>

using namespace std;

class Node
{
	public:
		int Coefficient;
		int Exponent;
		Node * Next;

		Node()
		{
			Next=NULL;
		}
};

class Linked_List
{
	public:
		Node * h_ptr;
		Node * trav_ptr;

		Linked_List()
		{
			h_ptr=NULL;
			trav_ptr=NULL;
		}

		void Insert(int coeff, int exp);
		void Add(Linked_List List2);
		void Subtract(Linked_List List2);
		Linked_List Multiply(Linked_List List2);
		void Display();
};

Linked_List Linked_List::Multiply(Linked_List List2)
{
	Linked_List Result;
	trav_ptr=h_ptr;
	List2.trav_ptr=List2.h_ptr;
	
	while(List2.trav_ptr!=NULL)
	{
		trav_ptr=h_ptr;
		while(trav_ptr!=NULL)
		{
			Result.Insert(List2.trav_ptr->Coefficient*trav_ptr->Coefficient,List2.trav_ptr->Exponent+trav_ptr->Exponent);
			trav_ptr=trav_ptr->Next;
		}

		List2.trav_ptr=List2.trav_ptr->Next;
	}

	return Result;
}

void Linked_List::Subtract(Linked_List list2)
{
	Linked_List Result;
	list2.trav_ptr=list2.h_ptr;
	while(list2.trav_ptr!=NULL)
	{
		list2.trav_ptr->Coefficient*=-1;
		list2.trav_ptr=list2.trav_ptr->Next;
	}

	Add(list2);
}

void Linked_List::Display()
{
	this->trav_ptr=h_ptr;
	while(trav_ptr!=NULL)
	{
		if(trav_ptr->Coefficient == 0)
		{
			trav_ptr = trav_ptr->Next;
		}

		else if(trav_ptr->Next != NULL && trav_ptr->Next->Coefficient>0)
		{
			cout<< trav_ptr->Coefficient << "x^" << trav_ptr->Exponent <<"+";
			trav_ptr=trav_ptr->Next;
		}

		else if(trav_ptr->Next != NULL && trav_ptr->Next->Coefficient < 0)
		{
			cout<< trav_ptr->Coefficient << "x^" << trav_ptr->Exponent;
			trav_ptr=trav_ptr->Next;
		}

		else
		{
			cout<< trav_ptr->Coefficient << "x^" << trav_ptr->Exponent;
			trav_ptr=trav_ptr->Next;
		}
	}

	cout << endl << endl;
}

void Linked_List::Add(Linked_List List2)
{
	if(this->h_ptr==NULL || List2.h_ptr==NULL)
	{
		cout << "List is empty!" << endl;
		return;
	}

	Node * trav1=this->h_ptr;
	Node * trav2=List2.h_ptr;

	while(trav1!=NULL && trav2!=NULL)
	{
		if(trav1->Exponent == trav2->Exponent)
		{
			trav1->Coefficient+=trav2->Coefficient;
			trav1=trav1->Next;
			trav2=trav2->Next;
		}

		else if(trav1->Exponent < trav2->Exponent)
		{
			trav1=trav1->Next;
		}

		else if(trav1->Exponent > trav2->Exponent)
		{
			this->Insert(trav2->Coefficient, trav2->Exponent);
			trav2=trav2->Next;
		}
	}
	
	while(trav2!=NULL)
	{
		this->Insert(trav2->Coefficient,trav2->Exponent);
		trav2=trav2->Next;
	}


}

void Linked_List::Insert(int coeff, int exp)
{
	if(coeff==0)
	{
		cout<<"Zero Coefficiant is not allowed"<<endl;
		return;
	}

	Node * NewNode=new Node;
	Node * Prev=NULL;
	NewNode->Next=NULL;
	NewNode->Coefficient=coeff;
	NewNode->Exponent=exp;
	
	if(h_ptr==NULL)
	{	
		h_ptr=NewNode;
	}

	else
	{
		trav_ptr=h_ptr;
		while(trav_ptr!=NULL)
		{
			if(trav_ptr->Exponent == NewNode->Exponent)
			{
				trav_ptr->Coefficient+=coeff;
				return;
			}

			else if(trav_ptr->Exponent < NewNode->Exponent)
			{
				Prev=trav_ptr;
				trav_ptr=trav_ptr->Next;
			}

			else if(trav_ptr->Exponent > NewNode->Exponent)
			{
				if(Prev==NULL)
				{
					h_ptr=NewNode;
					NewNode->Next=trav_ptr;
				}

				else
				{
					Prev->Next=NewNode;
					NewNode->Next=trav_ptr;
				}

				return;
			}
			
		}

		Prev->Next=NewNode;

	}
}

int main()
{
	Linked_List List1;
	Linked_List List2;
	Linked_List List3;
	Linked_List List4;
	Linked_List List5;
	Linked_List List6;

	//For Addition
	List1.Insert(2,3);
	List1.Insert(4,2);
	List1.Insert(2,4);
	List2.Insert(4,5);
	List2.Insert(2,4);
	List1.Add(List2);
	cout << "Added list:" << endl;
	List1.Display();
	
	//For Subtraction
	List3.Insert(3,3);
	List3.Insert(7,5);
	List3.Insert(8,4);
	List3.Insert(10,2);
	List4.Insert(1,3);
	List4.Insert(9,5);
	List4.Insert(4,4);
	List3.Subtract(List4);
	cout << "Subtracted List:" << endl;
	List3.Display();

	//For Multiplication
	Linked_List List7;
	List5.Insert(5,3);
	List5.Insert(6, 2);
	List6.Insert(2,2);
	List6.Insert(6,6);
	List6.Insert(5,4);
	List7 = List5.Multiply(List6);
	cout << "Multiplied List:" << endl;
	List7.Display();
	
	cout << endl;
	system("pause");
	return 0;
}

/* NOTE: In addition the two lists that are being added are 2x^3 + 4x^2 + 2x^4 and 4x^5 + 2x^4.
In subtraction the two lists that are being subtracted are 3x^3 + 7x^5 + 8x^4 + 10x^2 and x^3 + 9x^5 + 4x^4 + 9x^2.
In multiplication the two lists that are being multiplied are 5x^3 + 6x^2 and 2x^2 + 6x^6 + 5x^4.
*/
