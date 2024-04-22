#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
using namespace std;
#define nullptr 0

template <typename T>
class Node;

template <typename T>
ostream& operator<<(ostream& out, Node<T>* node);

template <typename T>
class Stack;

//4.19
//���⹦�ܣ� ��������tch�� stu    topk����    ����getclass����list��ȷ��T���� 
//�Ż��˵��� ����>><<   ���ݲ�ͬnode�漰��ͬ������ʾ 
//ÿ�β����ɹ����л���ʱ��
//ʹ���ļ�������Ϣ 
//���� 
//����choice����Ҫ�س� 



// ����һ���ڵ��࣬ģ��ʵ��
//ʹ��ʱ��Node<student>ȷ��T����Node<student>(obj)��ʼ��data
//���� student obj("zhang", "20101", 95);  new_node = new Node<student>(obj); 

//4.20
//����ʱ�ļ�����      get
//��ѡ���������������ȡ��enter�� get
//Node<T>���޲�Ĭ�Ϲ��캯��    get
//Node<T>�ĸ�ֵ���캯��    get
//student ranking��ʼ��   
//ȥ����ʼʱ���ɹ�list" 		get
//��ȡ�ļ��ܻ���һ���� 		get
//���ļ���ȡ�����ݲ�����ȷ��������  get 

//4.22
//  

template <typename T>
class Node {
	public:
	T data;
	Node<T>* prev;
	Node<T>* next;
	
	Node(const T& data) : data(data), next(nullptr),prev(nullptr) {}
	Node(T* data):data(*data),next(nullptr),prev(nullptr){}
	Node():next(nullptr),prev(nullptr){}
	Node operator=(Node n) 
	{
		prev = n.prev;
		next = n.next;
		data = n.data;
		return *this;
	}
	~Node() {

	}
};

// ����һ��������
template <typename T>
class List{
protected:
	Node<T>* head;
	Node<T>* tail;
	static int count;		//ͳ����Ķ������ 

public:
	List() : head(nullptr) , tail(nullptr){
		char* fname = "TchData.txt";
		ifstream pf;
		if (T::getclas()=="Student")
		{
			fname = "StuData.txt";
		}
		try
		{
			pf.open(fname);
			if(!pf)
			{
				throw "��"+string(fname)+"ʧ��" ;
			}
		}
		catch(string err)
		{
			cerr<<err<<endl;
			cerr<<"���Զ��½� "<<fname<<endl;
		}
		
//		Node<T>* tmp = head;
//		while(tmp)
//		{
//			cout<<"tmp="<<tmp;
//	    	pf.seekp(0, std::ios::end);
//			head->data.fwrite(pf);
//			head = head->next;
//			delete tmp;	
//			tmp = head;	
//		}
		int _count;
		pf>>_count;
		count=_count;
		for(int i = _count; i>0;i--)
		{
			T t;
			t.fread(pf);
			Node<T>* new_obj = new Node<T>(t);
			//�ж�new_objΪTch����Stu 

			//��new_obj������ȷλ�� 
			cout<<fname<<"  new_obj: "<<new_obj<<endl;
			if(head==nullptr)
			{
				head = tail = new_obj;
			}
			else
			{
				new_obj->prev = tail;
				tail->next = new_obj;
				tail = new_obj;
			}
			
		}
		pf.close();
		cout<<"�ɹ�����"<<fname<<endl;
	}
	~List() {		
	clear();
}

// ������ݵ�����
void add()
{
	string base = "����";
	int rk=1;//����ranking 
	if(T::getclas()=="Student") 
	{
		base = "�÷�";
	}
	//addͬʱ����list����head��tail �Ӵ�С 
	string _name, _id;
	int _score;
	cout<<"���������� id "<<base<<":>";
	cin>>_name>>_id>>_score;
	T* new_obj = new T(_name, _id, _score);
	Node<T>* new_node = new Node<T>(*new_obj);
	if (head!=nullptr)
	{
	//list��Ϊ�� 
		//�ҵ���һ����new_nodeС�Ľڵ㣬������ǰ�� 
		bool error = true;
		if (new_node->data.gets()>=head->data.gets())
		{
			//new_obj��head����new_objΪhead
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
		else if(tail->data.gets()>=new_node->data.gets())
		{
			//��ʱnew_obj<tail,new_tail����tail���棬����tail
			 tail->next = new_node;
			 new_node->prev = tail;
			 tail = tail->next;
		}
		else
		{
			//new_objӦ�����м�
			 Node<T>* tmp = head;
			 while (tmp)
			 {
			 	if(tmp->data.gets()<=new_node->data.gets())
			 	{
			 		new_node->next = tmp;
			 		new_node->prev = tmp->prev; 
			 		tmp->prev->next = new_node;
			 		tmp->prev = new_node;
			 		error = false;
			 		break;
				}
			 	tmp = tmp->next;
			 }
			 if (error)
			 cout<<"add�쳣�˳����Ҳ������ʲ���λ��"<<endl;
		}
//		tail->next = new_node;
//		tail = tail->next;

	}
	else
	{
	//listΪ�� 
		tail = head = new_node;
		rk = 1;
	}
	//Ϊ���ڵ�����
	if(T::getclas()=="Student")
	{
		Node<T>* tmp = head; 
		while(tmp)
		{
			tmp->data.ranking = rk;
			tmp = tmp->next;
			rk++;
		}
	}	
	count +=1;
}

// ������ݵ�����
void add(Node<T>* new_node)
{
//	new_node->prev = new_node->next = nullptr;
	
	if(new_node==nullptr)
	{
		cout<<"�����û��ɾ����Ա��Ϣ"<<endl;
		return;
	}
	new_node->next = nullptr;
	string base = "����";
	int rk=1;//����ranking 
	if(T::getclas()=="Student") 
	{
		base = "�÷�";
	}
	//addͬʱ����list����head��tail �Ӵ�С 
//	string _name, _id;
//	int _score;
//	cout<<"���������� id "<<base<<":>";
//	cin>>_name>>_id>>_score;
//	T* new_obj = new T(_name, _id, _score);
//	Node<T>* new_node = new Node<T>(*new_obj);
	if (head!=nullptr)
	{
	//list��Ϊ�� 
		//�ҵ���һ����new_nodeС�Ľڵ㣬������ǰ�� 
		bool error = true;
		if (new_node->data.gets()>=head->data.gets())
		{
			//new_obj��head����new_objΪhead
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
		else if(tail->data.gets()>=new_node->data.gets())
		{
			//��ʱnew_obj<tail,new_tail����tail���棬����tail
			 tail->next = new_node;
			 new_node->prev = tail;
			 tail = tail->next;
		}
		else
		{
			//new_objӦ�����м�
			 Node<T>* tmp = head;
			 while (tmp)
			 {
			 	if(tmp->data.gets()<=new_node->data.gets())
			 	{
			 		new_node->next = tmp;
			 		new_node->prev = tmp->prev; 
			 		tmp->prev->next = new_node;
			 		tmp->prev = new_node;
			 		error = false;
			 		break;
				}
			 	tmp = tmp->next;
			 }
			 if (error)
			 cout<<"add�쳣�˳����Ҳ������ʲ���λ��"<<endl;
		}
//		tail->next = new_node;
//		tail = tail->next;

	}
	else
	{
	//listΪ�� 
		tail = head = new_node;
		rk = 1;
	}
	//Ϊ���ڵ�����
	if(T::getclas()=="Student")
	{
		Node<T>* tmp = head; 
		while(tmp)
		{
			tmp->data.ranking = rk;
			tmp = tmp->next;
			rk++;
		}
	}	
	cout<<"�ɹ��ָ���Ϣ!"<<endl;
	count +=1;
}

// ɾ�������е�����
void remove(Stack<T>* stack)
{
	string _id;
	bool is_found = false; 
	cout<<"������Ҫɾ���ߵ�id:"<<endl;
	cin>>_id;
	Node<T>* tmp = head;
	while (tmp)
	{
		if(tmp->data.getid()==_id)
		{
			if(tmp==head)
			{
				head = head->next;
			}
			else if(tmp==tail)
			{
				tail = tail->prev;
			}
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			cout<<"�ɹ�ɾ������"<<endl;
			is_found = true;
			break;
		}
		tmp = tmp->next;
	}
	if(!is_found)
	{
		cout<<"ɾ��ʧ�ܣ�û�д�id��Ա��Ϣ"<<endl;
		return;
	}
	else
	{
		if(T::getclas()=="Student")
		{
			stack->Push(tmp);
		}
		else
		{
			stack->Push(tmp);
		}
	}
	count--;
	
}

// ��ѯ�����е�����
bool find()
{
	bool is_found = false;
	string _id;
	cout<<"�����뱻��ѯ��id��"<<endl;
	cin>>_id;
	Node<T>* tmp = head;
	while (tmp)
	{
		if (tmp->data.getid()==_id)
		{
			cout<<"���ҳɹ�����Ϣ���£�"<<endl;
			tmp->data.show();
			is_found = true;
			break;
		}
		tmp = tmp->next;
		cout<<"tmp=" <<tmp<<endl;
	}
	if(!is_found)
	{
		cout<<"����ʧ�ܣ�û�д�id��Ա��Ϣ"<<endl;
	}
}

void change()
{
	bool is_found = false;
	string _name, _id, old_id;
	int _score, _age;
	again:
	cout<<"�����뱻�޸���ԭ����id��"<<endl;
	cin>>old_id;
	Node<T>* tmp = head;
	while(tmp)
	{
		if(tmp->data.getid()==old_id)
		{
			cout<<"���ҳɹ�������ԭ����Ϣ����"<<endl;
			tmp->data.show();
			is_found = true;
			break;
		}
		tmp = tmp->next;
	}
	if(!is_found)
	{
		cout<<"����ʧ�ܣ�û�д�id��Ա��Ϣ"<<endl;
		goto again; 
	}
	cout<<"�������µ����� id �÷�/���� ����"<<endl;
	cin>>_name>>_id>>_score>>_age;
	tmp->data.set(_name, _id, _score, _age);
}

// �������
void clear()
{
	char* fname = "TchData.txt";
	if (T::getclas()=="Student")
	{
		fname = "StuData.txt";
	}
	ofstream pf(fname);
	if(!pf)
	{
		cout<<"��"<<fname<<"ʧ��"<<endl;
		exit(1);
	}
	pf<<count<<endl;
	
	cout<<"�ɹ�����" +T::getclas() +"������"<<fname<<":"<<endl;
	while(head)
	{
		cout<<head;
		// ��д��λ������Ϊ�ļ�ĩβ
    	pf.seekp(0, std::ios::end);
		head->data.fwrite(pf);
		Node<T>* tmp = head;
		head = head->next;
		delete tmp;		
	}
	cout<<endl;
	tail = nullptr;
	pf.close();
//	cout<<"�ɹ�����"+T::getclas()+"list"<<endl; 
}

 void getall() 
 {
 	cout<<"\n             �ܹ���"<<getcount()<<"��"<<endl;
 	if (T::getclas()=="Student")
 	{
 		cout<<"������"<<"\tѧ�ţ�"<<"\t�÷�"<<"\t����:"<<"\t����"<<endl;
	 }
	 if(T::getclas()=="Teacher")
	 {
	 	cout<<"������"<<"\t���䣺"<<"\t���ţ�"<<"\t���ʣ�"<<endl;
	 }
	 
	 Node<T>* tmp = head;
	 while(tmp)
	 {
//	 	tmp->data.show(true);
		cout<<tmp;
	 	tmp = tmp->next;
	 }
 }
 
 //������������Ҫ�����Ա��Ϣ 
void topk()
{
	int choice = 0;
	int begin = 0, end = 0;
	string base = "����" ;
	if(T::getclas()=="Student")
	{
		base = "����"; 
	}
	cout<<"����topk"; 
	cout<<"��ѡ�񵼳����ݣ���1����������  ��2�� ����"<<base<<"����"<<endl; 
	cin>>choice;
	cout<<"����������"<<endl;
	cin>>begin>>end;
	//������Ϣ�� 
	if (T::getclas()=="Student")
 	{
 		cout<<"������"<<"\tѧ�ţ�"<<"\t�÷�"<<"\t����:"<<"\t����"<<endl;
	}
	else if(T::getclas()=="Teacher")
	{
	 	cout<<"������"<<"\t���䣺"<<"\t���ţ�"<<"\t���ʣ�"<<endl;
	}
	if(choice==1)
	{
		//�������䵼�� 
		int ranking = 0;
		Node<T>* tmp = head;
		while(tmp)
		{
			ranking++;
			if (ranking>=begin&&ranking<=end)
			{
				tmp->data.show(true);
			}
			tmp = tmp->next;
		}
	}
	else if(choice==2)
	{
		//����score/wages���䵼�� 
		Node<T>* tmp = head;
		while(tmp) 
		{
			if(tmp->data.gets()>=begin&&tmp->data.gets()<=end)
			{
				tmp->data.show(true);
			}
			tmp = tmp->next;
		}
	}
	
	cout<<"�ѵ���ȫ��������������Ա��Ϣ"<<endl;
}


 
 
int getcount()
{
	return count;
}

};

template <typename T>
int List<T>::count = 0;

class Person{
	protected:
		string name;
		int age;
	public:
		Person(string _name, int _age){
			name = _name;
			age = _age;
		}
		virtual void show(bool less=false) =0;
};

// ����ѧ���ͽ�ʦ��
class Student:virtual public Person {
	template <typename T>
	friend class List;
	protected:
		std::string id;	//	ѧ�� 
		int score;
		int ranking;
		static string clas;
	public:
		Student(string _name="����ѧ��", string _id = "δ��id", int _score = 0, int _age=0) :Person(_name, _age) {
			id = _id;
			score = _score;
			if(_age==0)
			{
				//δ����Ĭ��18 
				age = 18;
			}
		}
		string _id(){return id;}//����find 

		void show(bool less=false);//Ĭ����ϸ��Ϣ 
		void set(string _name, string _id, int _score, int _age);//ȱʡ������������Ϊ�ֲ������ͳ�Ա������ ��Ϊ����Ĭ��ֵҪ����ʱȷ���������Ա�;ֲ�����Ҫ����ʱ����ȷ����ȫ�ֱ����;�̬�����ɱ���ʱȷ�� 
		string getid(){
			return id;
		}
		static string getclas(){
			return clas;
		}
		int gets()
		{
			return score;
		}
		void fread(ifstream& pf)
		{
			pf>>name>>id>>score>>ranking>>age;
		}
		void fwrite(ofstream& pf)
		{
			pf<<name<<"\t\t"<<id<<"\t\t"<<score<<"\t\t"<<ranking<<"\t\t"<<age<<"\t\t"<<endl;
		}
		Student operator=(Student s)
		{
			name = s.name;
			id = s.id;
			score = s.score;
			age = s.age;
			return *this;
		}
};

//string Student::clas = "Student";
string Student::clas = "Student";
//string Teacher::clas = "Teacher";

void Student::show(bool less)
{
	if(less){
		cout<<name<<"\t"<<id<<"\t"<<score<<"\t"<<ranking<<"\t"<<age<<endl;
	}
	else{
		cout<<"������"<<name<<"\tѧ�ţ�"<<id<<"\t�÷�\t"<<score<<"\t����:\t"<<ranking<<"\t����"<<age<<endl;
	}
}
 
void Student::set(string _name, string _id, int _score, int _age)
{
	Person::name = _name;
	Person::age = _age;
	id = _id;
	score = _score;
	
}

class Teacher:virtual public Person{
	template <typename T>
	friend class List;
	protected:
		string id;
		int wages;
		int ranking;
		static string clas;
	public:
		Teacher(string _name="������ʦ", string _id="δ��id", int _age=0, int _wages=0) :Person(_name, _age) {id = _id; if(_wages==0) wages = _age*98+(_age+3423)%13*50;}
		void show(bool less=false);
		void set(string _name, string _id, int _age, int _wages);	
		string getid(){
			return id;
		}
		static string getclas()
		{
			return clas;
		}
		int gets()
		{
			return wages;
		}
		void fread(ifstream& pf)
		{
			pf>>name>>id>>wages>>age; 
		}
		
		void fwrite(ofstream& pf)
		{
			cout<<"����fwrite"<<endl;
			pf<<name<<"\t\t"<<id<<"\t\t"<<wages<<"\t\t"<<age<<"\t\t"<<endl;
		}
		Teacher operator=(Teacher t)
		{
			name = t.name;
			id = t.id;
			wages = t.wages;
			age = t.age;
			return *this;
		}
};

string Teacher::clas = "Teacher";

void Teacher::show(bool less)
{
	if (less)
		cout<<name<<"\t"<<age<<"\t"<<id<<"\t"<<wages<<endl;
		
	else
		cout<<"������"<<name<<"\t���䣺"<<age<<"\t���ţ�"<<id<<"\t���ʣ�"<<wages<<endl;
}

void Teacher::set(string _name, string _id, int _wages, int _age)
{
	name = _name;
	age = _age;
	id = _id;
	wages = _wages;
}

void menu_begin();
void menu_tch();
void menu_stu();

//����ʹ��cout���Node 
template <typename T>
ostream& operator<<(ostream& out, Node<T>* node)
{
	node->data.show(true);
	return out;
}

//����ջ 
template <typename T>
class Stack:public List<T>{
	protected:
		Node<T>* tail;
		static int count;
	public:
		Stack():tail(nullptr){
		}
		bool Push(Node<T>*);
		Node<T>* Pop();
		void show();
};

template<typename T>
int Stack<T>::count = 0; 

template<typename T>
bool Stack<T>::Push(Node<T>* node)
{
	node->next = nullptr;
	node->prev = nullptr;
	if(tail==nullptr)
	{
		tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail = tail->next;
	}
	count++;
	return true;
}

template<typename T>
Node<T>* Stack<T>::Pop(){
	if(tail==nullptr)
	{
		return nullptr;
	}
	Node<T>* ret = tail;
	tail = tail->prev;
	count--;
	return ret;
}

template<typename T>
void Stack<T>::show()
{
	Node<T>* tmp = tail;
	cout<<T::getclas()<<"ջ�й���"<<count<<"����,��Ϣ����"<<endl;
	while (tmp)
	{
		tmp->data.show();
		tmp = tmp->prev;
	}
	cout<<endl;
}

//������� 
template <typename T>
class Queue:public List<T>{
	private:
		Node<T>* head;
		Node<T>* tail;
		static int count;
	public:
		Queue():tail(nullptr),head(nullptr){
		}
		bool Push(Node<T>* node);
		Node<T>* Pop();
}; 
//Push 
template <typename T>
bool Queue<T>::Push(Node<T>* node)
{
	node->prev = node->next = nullptr;
	if(tail==nullptr)//QueueΪ�� 
	{
		head=tail=node;
	}
	else//Queue��Ϊ�� 
	{
		node->prev = tail;
		tail->next = node;
		tail = tail->next;
	}
	count++;
}
//Pop
template <typename T>
Node<T>* Queue<T>::Pop()
{
	Node<T>* ret = nullptr;
	if(head==tail)//ͷβָ��ͬһ�ڵ� 
	{
		cout<<"����Ϊ�գ��޷�ȡ��"<<endl;
	}
	else
	{
		ret = head;
		head = head->next;
	}
	count--;
	ret->prev = ret->next = nullptr;
	return ret;
}

template<typename T>
int Queue<T>::count = 0;

int main()
{
	List<Student>* StuList = new List<Student>;
	List<Teacher>* TchList = new List<Teacher>;
	Stack<Student>* StuStack = new Stack<Student>;
	Stack<Teacher>* TchStack = new Stack<Teacher>;
	int choice = 1;
	do
	{
		menu_begin();
		choice = _getch()-48;
		cout<<choice<<endl;
		if (choice==1)
		{
			//��ʦ������Ϣϵͳ 
			int choice_tch = 1;
			do{
				menu_tch();
				choice_tch = _getch()-48;
				cout<<choice_tch<<endl;
				switch (choice_tch)
				{
					case 0:
						cout<<"�ɹ��˳���ʦ��Ϣ����ϵͳ\n���������"<<endl;
						break;
					case 1:
						TchList->add();
						break;
					case 2:
						TchList->remove(TchStack);
						break;
					case 3:
						TchList->find();
						break;
					case 4:
						TchList->change();
						break;
					case 5:
						TchList->getall();
						break;
					case 6:
						TchList->topk();
						break;
					case 7:
						TchStack->show();
						break;
					case 8:
						TchList->add(TchStack->Pop());
						break;
					default:
						cout<<"��������������"<<endl;
						break;
				}
				if(choice_tch>=1&&choice_tch<=8)cout<<"�����ɹ�!\n(���������)"<<endl;
				_getch();
				
			}while(choice_tch);
		}
		else if(choice==2)
		{
			//ѧ��������Ϣϵͳ 
			int choice_stu = 1;
			do{
				menu_stu();
				choice_stu = _getch()-48;
				cout<<choice_stu<<endl;
				switch (choice_stu)
				{
					case 0:
						cout<<"�ɹ��˳�ѧ����Ϣ����ϵͳ\n���������"<<endl;
						break;
					case 1:
						StuList->add();
						break;
					case 2:
						StuList->remove(StuStack);
						break;
					case 3:
						StuList->find();
						break;
					case 4:
						StuList->change();
						break;
					case 5:
						StuList->getall();
						break;
					case 6:
						StuList->topk();
						break;
					case 7:
						StuStack->show();
						break;
					case 8:
						StuList->add(StuStack->Pop());
						break;
					default:
						cout<<"��������������"<<endl;
						break;
				}				
				if(choice_stu>=1&&choice_stu<=8)cout<<"�����ɹ�!\n(���������)"<<endl;
				_getch();
			}while(choice_stu);
		}
		else
		{
			if(choice!=0)cout<<"��������������"<<endl;
		}
	}while(choice);
	cout<<"�ɹ��˳�ϵͳ\n"<<endl;
	StuStack->show();
	TchStack->show();
	delete StuList;
	delete TchList;
//	delete StuStack;
//	delete TchStack;
	return 0;
}

void menu_stu()
{
	cout<<endl<<"-------------��ӭ����ѧ����Ϣ����ϵͳ-------------"<<endl;
	cout<<"1.����ѧ����Ϣ" <<endl;
	cout<<"2.ɾ��ѧ����Ϣ"<<endl;
	cout<<"3.����ѧ����Ϣ"<<endl; 
	cout<<"4.�޸�ѧ����Ϣ"<<endl;
	cout<<"5.����ȫ��ѧ����Ϣ"<<endl;
	cout<<"6.�Զ��嵼������Ҫ��ѧ����Ϣ"<<endl;
	cout<<"7.�鿴���ɾ��ѧ����Ϣ"<<endl;
	cout<<"8.�ָ���ɾ��ѧ����Ϣ"<<endl; 
	cout<<"0.�˳�ѧ����Ϣ����ϵͳ"<<endl;
	cout<<"--------------------------------------------------"<<endl;
	cout<<"��ѡ�����:>";
}

void menu_tch()
{
	cout<<endl<<"-------------��ӭ������ʦ��Ϣ����ϵͳ-------------"<<endl;
	cout<<"1.������ʦ��Ϣ" <<endl;
	cout<<"2.ɾ����ʦ��Ϣ"<<endl;
	cout<<"3.���ҽ�ʦ��Ϣ"<<endl; 
	cout<<"4.�޸Ľ�ʦ��Ϣ"<<endl;
	cout<<"5.����ȫ����ʦ��Ϣ"<<endl;
	cout<<"6.�Զ��嵼����ʦ��Ϣ"<<endl;
	cout<<"7.�鿴���ɾ����ʦ��Ϣ"<<endl;
	cout<<"8.�ָ���ɾ����ʦ��Ϣ"<<endl; 
	cout<<"0.�˳���ʦ��Ϣ����ϵͳ"<<endl;
	cout<<"--------------------------------------------------"<<endl;
	cout<<"��ѡ�����:>";
}

void menu_begin()
{
	cout<<endl<<"-------------��ӭ������Ա��Ϣ����ϵͳ-------------"<<endl;
	cout<<"1.��ʦ" <<endl;
	cout<<"2.ѧ��"<<endl;
	cout<<"0.�˳�ϵͳ"<<endl; 
	cout<<"--------------------------------------------------"<<endl;
	cout<<"��ѡ���������:>";
}


