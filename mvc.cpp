#include <iostream>
#include <string>
#include <list>
using namespace std;

class Observer{
public:
	virtual ~Observer(){}
	virtual void update () = 0; //Pure virtual. Derived class wil inherit this method.
};


class Subject{
public:
	virtual ~Subject() {}
	virtual void notify () = 0; //Same as previous comment.
	virtual void addObserver(Observer *o) = 0;
	virtual void removeObserver(Observer *o) = 0;
};

class Model : private Subject{
public:
	void setData(const int i){data = i; notify();}
	int getData() const { return data;}
	
	virtual void addObserver(Observer *o) { observers.push_back(o);}
	virtual void removeObserver(Observer *o) { observers.remove(o);}
	virtual void notify(){
		for(Observer *observer : observers)
			observer->update();
	}

private:
	int data = 0; //C++11 initialization of data member.
	list <Observer*> observers;
};


class Controller{
public:
	Controller(Model *m) : model(m) {} //Making the inline implementation here. We do not have separated the source file.
	void increment(){
		int value = model->getData();
		value++;
		model->setData(value);	
	}
	
	void decrement(){
		int value = model->getData();
		value--;
		model->setData(value);
	}

private:
	Model *model;	
};


class View : private Observer{
public:
	View(Model *m, Controller *c){
		model = m;
		model->addObserver(this);
		controller = c;
	}
	virtual ~View() { model->removeObserver(this);}
	
	void displayTextField(int i){ cout << "Text Field: " << i << endl;}
	virtual void update(){
		int value = model->getData();
		displayTextField(value);
	}
	
	void incrementButton(){controller->increment();}
	void decrementButton(){controller->decrement();}
	
	
private:
	Model *model;
	Controller *controller;
};

void line();
void lines();

int main(){
	Model *model = new Model;
	Controller *controller = new Controller(model);
	View *view = new View(model, controller);	

	for(int i = 0; i<5; i++)
		view->incrementButton();
	line();	

	string ch;
	cout << "Make an increment or decrement?"<<endl;
	line();
	
	valid:
	cout << "For Text field increment press 'INC/inc'." << endl;
	cout << "For Text Field decrement press 'DEC/dec'." << endl;
	line();
	
	cout << "\t\tEnter your choice: "; cin >> ch;	
	if(ch == "dec" || ch == "DEC"){
		int nd = 0;
		cout  << "How many decrements you want to make? : "; cin >> nd;
		line();
		for(int i = 0; i < nd; i++)
			view->decrementButton();
		lines();
	}
	else if(ch == "inc" || ch ==  "INC"){
		int id = 0;
		cout << "How many increments you want to make? : "; cin >> id;
		line();
		for(int i =0; i <id; i++)
			view->decrementButton();
		lines();
	}
	else{
		cerr <<"\n\t\tOption not valid. Try again." << endl;
		lines();
		goto valid; 
	}
		
	return 0;
}


void line(){
	cout << endl;
}
void lines(){
	line();line();
}
