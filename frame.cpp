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

//4.19
//额外功能： 导出所有tch， stu    topk功能    根据getclass可在list中确定T的类 
//优化菜单， 重载>><<   根据不同node涉及不同输入提示 
//每次操作成功后有缓冲时间
//使用文件保存信息 
//排名 
//输入choice不需要回车 



// 定义一个节点类，模板实现
//使用时先Node<student>确定T，后Node<student>(obj)初始化data
//例如 student obj("zhang", "20101", 95);  new_node = new Node<student>(obj); 

//4.20
//构造时文件读入
//简化选择操作次数（尽量取消enter）
//Node<T>的无参默认构造函数    get
//Node<T>的赋值构造函数    get
//student ranking初始化   
//去掉开始时”成功list" 
//读取文件总会多读一个人
//从文件读取的数据不能正确加入链表  get 

template <typename T>
class Node {
	public:
	T data;
	Node<T>* prev;
	Node<T>* next;
	
	Node(const T& data) : data(data), next(nullptr) {}
	Node(T* data):data(*data),next(nullptr){}
	Node():next(nullptr){}
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

// 定义一个链表类
template <typename T>
class List {
private:
	Node<T>* head;
	Node<T>* tail;
	static int count;		//统计类的对象个数 

public:
	List() : head(nullptr) , tail(nullptr){
		cout<<"进入list（）"<<endl; 
		char* fname = "TchData.txt";
		if (T::getclas()=="Student")
		{
			fname = "StuData.txt";
		}
		ifstream pf(fname);
		if(!pf)
		{
			cout<<"打开"<<fname<<"失败"<<endl;
			exit(1);
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
		while(!pf.eof())
		{
			T t;
			t.fread(pf);
			Node<T>* new_obj = new Node<T>(t);
			//判断new_obj为Tch还是Stu 

			//将new_obj放入正确位置 
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
			
			count++;
		}
		pf.close();
		cout<<"成功清理list"<<endl; 
	}
	~List() {		
	clear();
}

// 添加数据到链表
void add()
{
	string base = "工资";
	if(T::getclas()=="Student") 
	{
		base = "得分";
	}
	//add同时保持list有序：head到tail 从大到小 
	string _name, _id;
	int _score;
	cout<<"请输入姓名 id "<<base<<":>";
	cin>>_name>>_id>>_score;
	T* new_obj = new T(_name, _id, _score);
	Node<T>* new_node = new Node<T>(*new_obj);
	if (head!=nullptr)
	{
	//list不为空 
		//找到第一个比new_node小的节点，插在其前面 
		bool error = true;
		
		if (new_node->data.gets()>=head->data.gets())
		{
			//new_obj比head大，令new_obj为head
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
			
		}
		else if(tail->data.gets()>=new_node->data.gets())
		{
			//此时new_obj<tail,new_tail插在tail后面，更新tail
			 tail->next = new_node;
			 new_node->prev = tail;
			 tail = tail->next;
			 
		}
		else
		{
			//new_obj应该在中间
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
			 cout<<"add异常退出，找不到合适插入位置"<<endl;
		}
//		tail->next = new_node;
//		tail = tail->next;

	}
	else
	{
	//list为空 
		tail = head = new_node;
	}
	count +=1;
}

// 删除链表中的数据
void remove()
{
	string _id;
	bool is_found = false; 
	cout<<"请输入要删除者的id:"<<endl;
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
			cout<<"成功删除此人"<<endl;
			is_found = true;
			break;
		}
		tmp = tmp->next;
	}
	if(!is_found)
	{
		cout<<"删除失败，没有此id人员信息"<<endl;
		return;
	}
	count--;
	
}

// 查询链表中的数据
bool find()
{
	bool is_found = false;
	string _id;
	cout<<"请输入被查询者id："<<endl;
	cin>>_id;
	Node<T>* tmp = head;
	while (tmp)
	{
		if (tmp->data.getid()==_id)
		{
			cout<<"查找成功，信息如下；"<<endl;
			tmp->data.show();
			is_found = true;
			break;
		}
		tmp = tmp->next;
		cout<<"tmp=" <<tmp<<endl;
	}
	if(!is_found)
	{
		cout<<"查找失败，没有此id人员信息"<<endl;
	}
}

void change()
{
	bool is_found = false;
	string _name, _id, old_id;
	int _score, _age;
	again:
	cout<<"请输入被修改人原来的id："<<endl;
	cin>>old_id;
	Node<T>* tmp = head;
	while(tmp)
	{
		if(tmp->data.getid()==old_id)
		{
			cout<<"查找成功，此人原来信息如下"<<endl;
			tmp->data.show();
			is_found = true;
			break;
		}
		tmp = tmp->next;
	}
	if(!is_found)
	{
		cout<<"查找失败，没有此id人员信息"<<endl;
		goto again; 
	}
	cout<<"请输入新的姓名 id 得分/工资 年龄"<<endl;
	cin>>_name>>_id>>_score>>_age;
	tmp->data.set(_name, _id, _score, _age);
}

// 清空链表
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
		cout<<"打开"<<fname<<"失败"<<endl;
		exit(1);
	}
	
	while(head)
	{
		cout<<"head="<<head;
		    // 将写入位置设置为文件末尾
    	pf.seekp(0, std::ios::end);
		head->data.fwrite(pf);
		Node<T>* tmp = head;
		head = head->next;
		delete tmp;		
	}
	tail = nullptr;
	pf.close();
	cout<<"成功清理list"<<endl; 
}

 void getall() 
 {
 	cout<<"\n             总共有"<<getcount()<<"人"<<endl;
 	if (T::getclas()=="Student")
 	{
 		cout<<"姓名："<<"\t学号："<<"\t得分"<<"\t排名:"<<"\t年龄"<<endl;
	 }
	 if(T::getclas()=="Teacher")
	 {
	 	cout<<"姓名："<<"\t年龄："<<"\t工号："<<"\t工资："<<endl;
	 }
	 
	 Node<T>* tmp = head;
	 while(tmp)
	 {
//	 	tmp->data.show(true);
		cout<<tmp;
	 	tmp = tmp->next;
	 }
 }
 
 //导出所有满足要求的人员信息 
void topk()
{
	int choice = 0;
	int begin = 0, end = 0;
	string base = "工资" ;
	if(T::getclas()=="Student")
	{
		base = "分数"; 
	}
	cout<<"进入topk"; 
	cout<<"请选择导出依据：（1）排名区间  （2） 具体"<<base<<"区间"<<endl; 
	cin>>choice;
	cout<<"请输入区间"<<endl;
	cin>>begin>>end;
	//顶部信息栏 
	if (T::getclas()=="Student")
 	{
 		cout<<"姓名："<<"\t学号："<<"\t得分"<<"\t排名:"<<"\t年龄"<<endl;
	}
	else if(T::getclas()=="Teacher")
	{
	 	cout<<"姓名："<<"\t年龄："<<"\t工号："<<"\t工资："<<endl;
	}
	if(choice==1)
	{
		//排名区间导出 
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
		//具体score/wages区间导出 
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
	
	cout<<"已导出全部符合条件的人员信息"<<endl;
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

// 定义学生和教师类
class Student:virtual public Person {
	private:
		std::string id;	//	学号 
		int score;
		int ranking;
		static string clas;
	public:
		Student(string _name="无名学生", string _id = "未定id", int _score = 0, int _age=0) :Person(_name, _age) {
			id = _id;
			score = _score;
			if(_age==0)
			{
				//未传参默认18 
				age = 18;
			}
		}
		string _id(){return id;}//用于find 

		void show(bool less=false);//默认详细信息 
		void set(string _name, string _id, int _score, int _age);//缺省函数参数不可为局部变量和成员变量， 因为参数默认值要编译时确定，但类成员和局部变量要运行时才能确定，全局变量和静态变量可编译时确定 
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
			pf<<name<<"\t"<<id<<"\t"<<score<<"\t"<<ranking<<"\t"<<age<<"\t"<<endl;
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
		cout<<"姓名："<<name<<"\t学号："<<id<<"\t得分\t"<<score<<"\t排名:\t"<<ranking<<"\t年龄"<<age<<endl;
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
		Teacher(string _name="无名教师", string _id="未定id", int _age=0, int _wages=0) :Person(_name, _age) {id = _id; if(_wages==0) wages = _age*98+(_age+3423)%13*50;}
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
			pf<<name<<"\t"<<id<<"\t"<<wages<<"\t"<<age<<"\t"<<endl;
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
		cout<<"姓名："<<name<<"\t年龄："<<age<<"\t工号："<<id<<"\t工资："<<wages<<endl;
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

//可以使用cout输出Node 
template <typename T>
ostream& operator<<(ostream& out, Node<T>* node)
{
	node->data.show(true);
	return out;
}



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
						cout<<"成功退出教师信息管理系统"<<endl;
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
					case 6:
						TchList->topk();
						break;
					default:
						cout<<"输入有误，请重试"<<endl;
						break;
				}
				if(choice_tch>=1&&choice_tch<=6)cout<<"操作成功!\n(任意键继续)"<<endl;
				_getch();
				
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
						cout<<"成功退出学生信息管理系统"<<endl;
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
					case 6:
						StuList->topk();
						break;
					default:
						cout<<"输入有误，请重试"<<endl;
						break;
				}				
				if(choice_stu>=1&&choice_stu<=6)cout<<"操作成功!\n(任意键继续)"<<endl;
				_getch();
			}while(choice_stu);
		}
		else
		{
			if(choice!=0)cout<<"输入有误，请重试"<<endl;
		}
	}while(choice);
	cout<<"成功退出"<<endl;
	delete StuList;
	delete TchList;
	return 0;
}

void menu_stu()
{
	cout<<endl<<"-------------欢迎来到学生信息管理系统-------------"<<endl;
	cout<<"1.新增学生信息" <<endl;
	cout<<"2.删除学生信息"<<endl;
	cout<<"3.查找学生信息"<<endl; 
	cout<<"4.修改学生信息"<<endl;
	cout<<"5.导出全体学生信息"<<endl;
	cout<<"6.自定义导出符合要求学生信息"<<endl;
	cout<<"0.退出学生信息管理系统"<<endl;
	cout<<"--------------------------------------------------"<<endl;
	cout<<"请选择操作:>";
}

void menu_tch()
{
	cout<<endl<<"-------------欢迎来到教师信息管理系统-------------"<<endl;
	cout<<"1.新增教师信息" <<endl;
	cout<<"2.删除教师信息"<<endl;
	cout<<"3.查找教师信息"<<endl; 
	cout<<"4.修改教师信息"<<endl;
	cout<<"5.导出全部教师信息"<<endl;
	cout<<"6.自定义导出教师信息"<<endl;
	cout<<"0.退出教师信息管理系统"<<endl;
	cout<<"--------------------------------------------------"<<endl;
	cout<<"请选择操作:>";
}

void menu_begin()
{
	cout<<endl<<"-------------欢迎来到人员信息管理系统-------------"<<endl;
	cout<<"1.教师" <<endl;
	cout<<"2.学生"<<endl;
	cout<<"0.退出系统"<<endl; 
	cout<<"--------------------------------------------------"<<endl;
	cout<<"请选择操作对象:>";
}

