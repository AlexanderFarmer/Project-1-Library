//Name: Alexander Farmer
//Date: 10/6/2019
//Email: alf7mq@mail.umkc.edu
//Assignment: Project 1 - Library

#include <iostream>
#include <queue>
#include <string>
#include "Date.h"
#include <vector> 



using namespace std;

//Employee class containing name,waiting & retaining time
class employee {
public:

	//Constructor
	employee(string name) { this->name = name; };

	//Getters
	string get_name() { return name; };
	int get_wait() { return waiting_time; };
	int get_retain() { return retaining_time; };
	int get_priority() { return waiting_time - retaining_time; }

	//Setters
	string set_name(string name) { this->name = name; };
	void set_wait(int& waiting) { waiting_time += waiting; };
	void set_retain(int& retain) { retaining_time += retain; };

	//Comparison for priority
	bool operator < (employee& str)
	{
		return ((waiting_time-retaining_time) > str.get_priority());
	}

private:
	string name;
	int waiting_time = 0;
	int retaining_time = 0;
};

//Book Class containing name,circulation start & end, archived status
class book {
public:

	//Constructor
	book(string name) { this->name = name; };

	//Getters
	string get_name() { return name; };
	Date get_start() { return circ_start; };
	Date get_end() { return circ_end; };
	bool is_archived() { return archived; };
	bool circulation_empty() { return circulation_list.empty(); }
	//Setters
	string set_name(string name) { this->name = name; };
	void set_start(Date entered_date) {circ_start = entered_date; };
	void set_end(Date entered_date) { circ_end = entered_date; };
	void new_reader(employee employee) { circulation_list.push(employee); };
	void change_archived() {
		if (archived == true) { archived = false; }
		else { archived = true; }
	}

	//Functions

	//Updates the queue for the book and retain/wait numbers
	void pass_employee(Date date){
		int new_time = circulation_list.front().get_wait();
		int new_date = date - circ_start;
		circ_start = date;
		circulation_list.front().set_retain((new_date));
		int new_wait = circulation_list.front().get_wait();
		circulation_list.pop();
		if (circulation_list.empty() != true)
		{
			int time = new_date + new_wait;
			circulation_list.front().set_wait(time);
		}
	
	};

	//Updates the queue before it is passed on to make sure highest priority is next
	void prioritize()
	{
		queue<employee> copy = circulation_list;
		queue<employee> new_copy;
		vector<employee> prioritized;
		int greatest = copy.front().get_priority();
		for (int i = 0; i < circulation_list.size(); i++)
		{
			prioritized.push_back(copy.front());
			copy.pop();
		}
		sort(prioritized.begin(), prioritized.end());
		circulation_list = new_copy;
		
	}


private:
	string name;
	Date circ_start;
	Date circ_end;
	bool archived = false;
	queue<employee> circulation_list;
};

//Library Class containing a list of circulated & archived books and employees using them.
class Library {

public:
	//Adds a book into circulation
	void add_book(string book_name) { 
		book circulating_book(book_name);
		circulation.push_back(circulating_book); 
	}
	//Adds an employee to the employee list
	void add_employee(string employee_name) { 
		employee circulating_employee(employee_name);
		active_employee.push_back(circulating_employee); 
	}

	//takes a book that is in the archive and begins circulating it again
	void circulate_book(string book_name, Date date) {
		for (int i = 0; i < circulation.size(); i++)
		{

			if (circulation.at(i).get_name() == book_name)
			{
				circulation.at(i).set_start(date);

				for (int j = 0; j < active_employee.size(); j++)
				{
					circulation.at(i).new_reader(active_employee.at(j));
				}
				break;
			}

		}

	}
	//Passes the book on to the next person
	void pass_on(string book_name, Date date) 
	{
		for (int i = 0; i < circulation.size(); i++)
		{

			if (circulation.at(i).get_name() == book_name)
			{
				circulation.at(i).prioritize();
				circulation.at(i).pass_employee(date);

				//If the queue for the book is empty, archives it
				if (circulation.at(i).circulation_empty())
				{
					circulation.at(i).change_archived();
					archived.push_back(circulation.at(i));
					circulation.erase(circulation.begin() + i);
				}
				break;
			}

		}
	}

private:
	vector<book> archived;
	vector<employee> active_employee;
	vector<book> circulation;
};


int main()
{	

	return 0;
}