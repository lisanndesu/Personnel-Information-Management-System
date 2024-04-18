#include <iostream>
#include <cstring>
using namespace std;
#define nullptr 0

//���⹦�ܣ� ��������tch�� stu    topk����    ����getclass����list��ȷ��T���� 

// ����һ���ڵ��࣬ģ��ʵ��
//ʹ��ʱ��Node<student>ȷ��T����Node<student>(obj)��ʼ��data
//���� student obj("zhang", "20101", 95);  new_node = new Node<student>(obj); 
template <typename T>
class Node {
	public:
	T data;
	Node<T>* prev;
	Node<T>* next;
	
	Node(const T& data) : data(data), next(nullptr) {}
	~Node() {
		if (next != nullptr) {
		delete next;
		}
	}
};

// ����һ��������
template <typename T>
class List {
private:
	Node<T>* head;
	Node<T>* tail;
	static int count;		//ͳ����Ķ������ 

public:
	List() : head(nullptr) , tail(nullptr){}
	~List() {
		cout<<"����list����"<<endl;
	clear();
}

// ������ݵ�����
void add()
{
	//addͬʱ����list����head��tail �Ӵ�С 
	string _name, _id;
	int _score;
	cout<<"���������� id �÷�/���䣺"<<endl;
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
			 		new_node->prev = tmp;
			 		new_node->next = tmp->next; 
			 		tmp->next->prev = new_node;
			 		tmp->next = new_node;
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
	}
	count +=1;
}

// ɾ�������е�����
void remove()
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
			delete tmp;
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
	while(head)
	{
		Node<T>* tmp = head->next;
		delete head;
		head = tmp;
	}
	tail = nullptr;
	cout<<"�ɹ�����list"<<endl; 
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
	 	tmp->data.show(true);
	 	tmp = tmp->next;
	 }
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
	private:
		std::string id;	//	ѧ�� 
		int score;
		int ranking;
		static string clas;
	public:
		Student(string _name, string _id, int _score, int _age=18) :Person(_name, _age) {
			id = _id;
			score = _score;
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
	private:
		string id;
		int wages;
		static string clas;
	public:
		Teacher(string _name, string _id, int _age) :Person(_name, _age) {id = _id; wages = _age*98+(_age+3423)%13*50;}
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


int main()
{
	List<Student>* StuList = new List<Student>;
	List<Teacher>* TchList = new List<Teacher>;
	int choice = 1;
	do
	{
		menu_begin();
		cin>>choice;
		if (choice==1)
		{
			int choice_tch = 1;
			do{
				menu_tch();
				cin>>choice_tch;
				switch (choice_tch)
				{
					case 0:
						cout<<"�ɹ��˳���ʦ��Ϣ����ϵͳ"<<endl;
						break;
					case 1:
						TchList->add();
						break;
					case 2:
						TchList->remove();
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
					default:
						cout<<"��������������"<<endl;
						break;
				}
				if(choice_tch>=1&&choice_tch<=5)cout<<"�����ɹ�"<<endl;
				
			}while(choice_tch);
		}
		else if(choice==2)
		{
			int choice_stu = 1;
			do{
				menu_stu();
				cin>>choice_stu;
				switch (choice_stu)
				{
					case 0:
						cout<<"�ɹ��˳�ѧ����Ϣ����ϵͳ"<<endl;
						break;
					case 1:
						StuList->add();
						break;
					case 2:
						StuList->remove();
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
					default:
						cout<<"��������������"<<endl;
						break;
				}				
				if(choice_stu>=1&&choice_stu<=5)cout<<"�����ɹ�"<<endl;
			}while(choice_stu);
		}
		else
		{
			if(choice!=0)cout<<"��������������"<<endl;
		}
	}while(choice);
	cout<<"�ɹ��˳�"<<endl;
	return 0;
}

void menu_stu()
{
	cout<<endl<<"******************��ӭ����ѧ����Ϣ����ϵͳ*****************"<<endl;
	cout<<"��ѡ�������"<<endl;
	cout<<"1.����ѧ����Ϣ" <<endl;
	cout<<"2.ɾ��ѧ����Ϣ"<<endl;
	cout<<"3.����ѧ����Ϣ"<<endl; 
	cout<<"4.�޸�ѧ����Ϣ"<<endl;
	cout<<"5.����ȫ��ѧ����Ϣ"<<endl;
	cout<<"0.�˳�ѧ����Ϣ����ϵͳ"<<endl;
}

void menu_tch()
{
	cout<<endl<<"******************��ӭ������ʦ��Ϣ����ϵͳ*****************"<<endl;
	cout<<"��ѡ�������"<<endl;
	cout<<"1.������ʦ��Ϣ" <<endl;
	cout<<"2.ɾ����ʦ��Ϣ"<<endl;
	cout<<"3.���ҽ�ʦ��Ϣ"<<endl; 
	cout<<"4.�޸Ľ�ʦ��Ϣ"<<endl;
	cout<<"5.����ȫ����ʦ��Ϣ"<<endl;
	cout<<"0.�˳���ʦ��Ϣ����ϵͳ"<<endl;
}

void menu_begin()
{
	cout<<endl<<"******************��ӭ������Ա��Ϣ����ϵͳ*****************"<<endl;
	cout<<"��ѡ���������"<<endl;
	cout<<"1.��ʦ" <<endl;
	cout<<"2.ѧ��"<<endl;
	cout<<"0.�˳�ϵͳ"<<endl; 
}

