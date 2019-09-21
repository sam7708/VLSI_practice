#include <iostream>
#include <string>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <math.h>
#include <stack>
#include <time.h>  // time(), C++ 為 ctime

using namespace std;

int idealX;
int totalarea = 0;
float initialratio = 0;
int initialarea = 0;
int PointA = 4, PointB = 8;
int flag = 0;
int nblock;

int StoI(string s) {
	int t = 1, num = 0;
	for (int i = 0; i < s.size(); i++) {
		if (int(s[i]) < 58 && int(s[i]) >= 48) {
			for (int j = s.size() - 1; j >= i; j--) {
				if (int(s[j]) < 48)
					j = j;
				else {
					num += (int(s[j]) - 48)*t;
					t = t * 10;
				}
			}
			return num;
		}
	}
}

void rand(int Num, vector<int> &vect)
{
	vector<int> temp;
	for (int i = 0; i < Num; ++i)
	{
		temp.push_back(i + 1);
	}

	random_shuffle(temp.begin(), temp.end());

	//for (int i = 0; i < temp.size(); i++)
	//cout << temp[i] << " ";

	vect = temp;
}

float Cost(int maxX, int maxY, float Alpha) {
	float a = (float)maxX / (float)maxY;
	float b = (float)maxY / (float)maxX;
	float ratio = (a >= b)*b + (a < b)*a;
	float ratiocost = (1 - Alpha)*(ratio / initialratio);
	float areacost = ((float)(maxX*maxY) / (float)initialarea)* Alpha;
	float cost = ratiocost + areacost;
	return  cost;
}

float Ratio(int maxX, int maxY) {
	float a = (float)maxX / (float)maxY;
	float b = (float)maxY / (float)maxX;
	float ratio = (a >= b)*b + (a < b)*a;
	return ratio;

}

void SimulatedAnnealing(int maxx, int maxy, int stage, int) {

}

class BinaryTree;
class sb {
public:
	int w;
	int h;
	bool R;
	void New(int, int, int);
	void Rotate();
	friend class BinaryTree;
};
void sb::New(int X, int Y, int r) {
	w = X;
	h = Y;
	R = r;
}
void sb::Rotate() {
	int temp;
	temp = w;
	w = h;
	h = temp;
	if (R == 0)
		R = 1;
	else
		R = 0;
}
class terimal {
public:
	int X;
	int Y;
	int P;
	void New(int pin, int x, int y);
};
void terimal::New(int pin, int x, int y) {
	X = x;
	Y = y;
	P = pin;
}
class TreeNode {
private:
	TreeNode * leftchild;
	TreeNode *rightchild;
	TreeNode *parent;
	int data;
	int x_r, x_l, y_l, y_h, X, Y, R;
public:
	TreeNode() :leftchild(0), rightchild(0), parent(0), data(0), x_r(0), x_l(0), X(0), Y(0), R(0) {};
	TreeNode(int s, int x, int y, int r) :leftchild(0), rightchild(0), parent(0), data(s), X(x), Y(y), R(r) {};
	friend class BinaryTree;
};
class BinaryTree {
private:
	TreeNode * Victom();
	TreeNode* Insertpoint();
public:
	TreeNode * root;
	int Max_x, Max_y;
	int Contour[5000];
	BinaryTree();

	;
	// Binary tree function
	void InsertLevelorder(int data, int x, int y);
	void DeleteNode(int data);
	void InsertNode(int data, int x, int y, int r);
	void RenewXY();
	TreeNode* FindBlock(int data);
	// Disturb function
	void Disturb(int data);
	void Swap(int data1, int data2);
	void Rotate(int data);
	//Output function
	void Levelorder();
	void Outputfile();
	void Inorder(TreeNode *current);

	void Copy(TreeNode *Root, TreeNode* Back);
	void DeleteTree();

};
//leval order 搜尋樹 回傳第一個超出邊界且沒有child的block
TreeNode* BinaryTree::Victom() {

	vector<TreeNode*> s;
	std::queue<TreeNode*> q;
	q.push(this->root);                     // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		//std::cout << current->data << " x:" << current->x_l << " " << current->x_r << std::endl;
		if (current->leftchild == NULL && current->rightchild == NULL)
			s.push_back(current);
		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
	}
	return s[rand() % s.size()];
}
TreeNode* BinaryTree::Insertpoint() {
	vector<TreeNode*> s;
	std::queue<TreeNode*> q;
	q.push(this->root);                     // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		//std::cout << current->data << " x:" << current->x_l << " " << current->x_r << std::endl;
		if (current->leftchild == NULL || current->rightchild == NULL)
			s.push_back(current);
		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
	}
	return s[rand() % s.size()];


}
BinaryTree::BinaryTree() {
	root = 0;
	Max_x = 0;
	Max_y = 0;
	for (int i = 0; i < 5000; i++)
		Contour[i] = 0;
}
void BinaryTree::InsertLevelorder(int data, int x, int y) {
	if (root == 0) {
		root = new TreeNode(data, x, y, 0);
		return;
	}
	std::queue<TreeNode*> q;
	TreeNode *current = root;
	while (current) {
		if (current->leftchild != NULL) {               // current的leftchild沒有空位
			q.push(current->leftchild);                // 將其推進queue中
		}
		else {                                          // current的leftchild有空位
			TreeNode *new_node = new TreeNode(data, x, y, 0);   // 建立新的node, 將字母放在這裡
			new_node->parent = current;
			current->leftchild = new_node;
			break;
		}
		if (current->rightchild != NULL) {             // current的rightchild沒有空位
			q.push(current->rightchild);               // 將其推進queue中
		}
		else {                                          // current的rightchild有空位
			TreeNode *new_node = new TreeNode(data, x, y, 0);   // 建立新的node, 將字母放在這裡
			new_node->parent = current;
			current->rightchild = new_node;
			break;
		}
		current = q.front();
		q.pop();
	}
}

void BinaryTree::RenewXY() {
	for (int i = 0; i < 5000; i++)
		Contour[i] = 0;
	std::queue<TreeNode*> q;
	TreeNode *current = root;
	current->x_l = 0;
	current->x_r = current->X;
	current->y_l = 0;
	current->y_h = current->Y;
	for (int i = 0; i < current->X; i++)
		Contour[i] = current->Y;
	Max_x = current->X;
	Max_y = current->Y;
	q.push(this->root);
	while (!q.empty()) {
		current = q.front();
		q.pop();
		if (current != root) {
			if (current->parent->leftchild == current) {
				current->x_l = current->parent->x_r;
				current->x_r = current->parent->x_r + current->X;
				int maxy = Contour[current->x_l];
				for (int i = current->x_l; i < current->x_r; i++) {
					if (maxy < Contour[i])
						maxy = Contour[i];
				}
				current->y_l = maxy;
				current->y_h = maxy + current->Y;
				for (int i = current->x_l; i < current->x_r; i++) {
					if (Contour[i] < current->y_h)
						Contour[i] = current->y_h;
				}
				if (current->x_r > Max_x)
					Max_x = current->x_r;
				if (current->y_h > Max_y)
					Max_y = current->y_h;
			}
			else if (current->parent->rightchild == current) {
				current->x_l = current->parent->x_l;
				current->x_r = current->parent->x_l + current->X;
				int maxy = Contour[current->x_l];
				for (int i = current->x_l; i < current->x_r; i++) {
					if (maxy < Contour[i])
						maxy = Contour[i];
				}
				current->y_l = maxy;
				current->y_h = maxy + current->Y;
				for (int i = current->x_l; i < current->x_r; i++) {
					if (Contour[i] < current->y_h)
						Contour[i] = current->y_h;
				}
				if (current->x_r > Max_x)
					Max_x = current->x_r;
				if (current->y_h > Max_y)
					Max_y = current->y_h;

			}
		}

		if (current->leftchild != NULL)
			q.push(current->leftchild);
		if (current->rightchild != NULL)
			q.push(current->rightchild);

	}
}

void BinaryTree::Inorder(TreeNode *current) {
	if (current) {                          // if current != NULL
		Inorder(current->leftchild);        // L
											//std::cout << current->data << " x:" << current->x_l << " " << current->x_r << std::endl;   // V
		Inorder(current->rightchild);       // R
	}
}

void BinaryTree::Levelorder() {

	std::queue<TreeNode*> q;
	q.push(this->root);                     // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		//std::cout << current->data << " x:" << current->x_l << " " << current->x_r << std::endl;

		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
	}
}

void BinaryTree::Outputfile() {
	fstream fp;
	fp.open("result5.rpt", ios::out);
	fp << "100 500" << endl;
	std::queue<TreeNode*> q;
	q.push(this->root);                     // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting


		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		//std::cout << current->data << " x:" << current->x_l << " " << current->x_r  << "y: " << current->y_l << " " << current->y_h << std::endl;
		fp << current->data << " " << current->x_l << " " << current->y_l << " " << (current->x_r - current->x_l) << " " << (current->y_h - current->y_l) << " 0" << endl;
		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
	}
}

void BinaryTree::Disturb(int data) {
	TreeNode* A = FindBlock(data);
	int x = A->X, y = A->Y, r = A->R;
	DeleteNode(data);
	InsertNode(data, x, y, r);



}
void BinaryTree::Swap(int data1, int data2) {
	if (data1 == data2)
		return;
	TreeNode* A = FindBlock(data1);
	TreeNode* B = FindBlock(data2);

	swap(A->X, B->X);
	swap(A->Y, B->Y);
	//	swap(A->x_l, B->x_l);
	//	swap(A->x_r, B->x_r);
	//	swap(A->y_l, B->y_l);
	//	swap(A->y_h, B->y_h);
	swap(A->R, B->R);
	swap(A->data, B->data);
}



void BinaryTree::Rotate(int data) {
	TreeNode* A = FindBlock(data);
	swap(A->X, A->Y);
	A->R = (A->R == 0) * 1;
}
TreeNode* BinaryTree::FindBlock(int block) {
	std::queue<TreeNode*> q;
	q.push(this->root);                     // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		if (current->data == block)
			return current;
		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
	}
}

void BinaryTree::DeleteNode(int data) {

	TreeNode *delete_node = FindBlock(data);
	TreeNode *parent = delete_node->parent;
	//cout << "P: "<<parent <<" "<< delete_node ->data <<" "<< root->data<<endl;


	//cout << "Data " << data << " " << delete_node->data << " " << parent->data << "CHILDdata : " << delete_node->leftchild << " " << delete_node->rightchild;
	if (delete_node == root) {

		TreeNode* victom = Victom();
		victom->leftchild = delete_node->leftchild;
		victom->rightchild = delete_node->rightchild;
		if (victom->parent->leftchild == victom)
			victom->parent->leftchild = NULL;
		else
			victom->parent->rightchild = NULL;
		delete_node->leftchild->parent = victom;
		delete_node->rightchild->parent = victom;
		victom->parent = NULL;
		root = victom;
		delete(delete_node);
		delete_node = 0;

	}
	//CASE 1 要刪除的沒有chile
	else {
		//cout << "CASE1";
		if (delete_node->leftchild == NULL && delete_node->rightchild == NULL) {
			if (parent->leftchild == delete_node)
				parent->leftchild = NULL;
			else if (parent->rightchild == delete_node)
				parent->rightchild = NULL;
			delete_node->parent = 0;
			delete(delete_node);
			delete_node = 0;
		}
		//CASE 2 要刪除的只有一個child
		else if ((delete_node->leftchild == NULL && delete_node->rightchild) || (delete_node->leftchild  && delete_node->rightchild == NULL)) {
			//cout << "CASE2";
			if (delete_node->leftchild) {
				if (parent->leftchild == delete_node)
					parent->leftchild = delete_node->leftchild;
				else if (parent->rightchild == delete_node)
					parent->rightchild = delete_node->leftchild;
				delete_node->leftchild->parent = parent;
			}
			else if (delete_node->rightchild) {
				if (parent->leftchild == delete_node)
					parent->leftchild = delete_node->rightchild;
				else if (parent->rightchild == delete_node)
					parent->rightchild = delete_node->rightchild;
				delete_node->rightchild->parent = parent;
			}
			delete(delete_node);
			delete_node = 0;
		}
		//CASE 3 要刪除的節點有兩個child
		else {
			//cout << "CASE3";
			TreeNode* victom = Victom();
			if (victom->parent == delete_node) {
				if (delete_node->leftchild == victom) {
					victom->rightchild = delete_node->rightchild;
					delete_node->rightchild->parent = victom;
				}

				else {
					victom->leftchild = delete_node->leftchild;
					delete_node->leftchild->parent = victom;
				}
				if (delete_node->parent->leftchild == delete_node)
					delete_node->parent->leftchild = victom;
				else
					delete_node->parent->rightchild = victom;
				victom->parent = parent;
				delete(delete_node);
				delete_node = 0;

			}
			else {
				if (parent->leftchild == delete_node)
					parent->leftchild = victom;
				else
					parent->rightchild = victom;
				if (victom->parent->leftchild == victom)
					victom->parent->leftchild = NULL;
				else
					victom->parent->rightchild = NULL;
				victom->parent = parent;
				victom->leftchild = delete_node->leftchild;
				delete_node->leftchild->parent = victom;
				victom->rightchild = delete_node->rightchild;
				delete_node->rightchild->parent = victom;
				delete(delete_node);
				delete_node = 0;
			}
		}
	}
}
void BinaryTree::InsertNode(int data, int x, int y, int r) {
	TreeNode* insertpoint = Insertpoint();
	TreeNode* newnode = new TreeNode(data, x, y, r);
	if (insertpoint->leftchild == NULL)
		insertpoint->leftchild = newnode;
	else
		insertpoint->rightchild = newnode;
	newnode->parent = insertpoint;
	//cout << newnode->parent << endl;
}

void BinaryTree::Copy(TreeNode* oldnode, TreeNode* newnodeparent) {

	if (oldnode) {
		if (oldnode->parent == NULL) {
			TreeNode* newnode = new TreeNode(oldnode->data, oldnode->X, oldnode->Y, oldnode->R);
			root = newnode;
			newnodeparent = newnode;
		}
		else {
			TreeNode* newnode = new TreeNode(oldnode->data, oldnode->X, oldnode->Y, oldnode->R);
			if (oldnode->parent->leftchild == oldnode)
				newnodeparent->leftchild = newnode;
			else
				newnodeparent->rightchild = newnode;
			newnode->parent = newnodeparent;
			newnodeparent = newnode;
		}
		Copy(oldnode->leftchild, newnodeparent);
		Copy(oldnode->rightchild, newnodeparent);
	}
}

void BinaryTree::DeleteTree() {
	std::queue<TreeNode*> q;
	q.push(this->root);                     // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
		delete(current);
	}
	Max_x = 0;
	Max_y = 0;
	for (int i = 0; i < 5000; i++)
		Contour[i] = 0;
}


int main(int argc,char** argv) {
	char ch[50];
	srand(time(NULL));

	// read block file record number of block and terimals and cordiate of blocks 
	int nterminals;
	ifstream fin("n300.blocks");

	sb* Sb = new sb[300];
	while (!fin.eof()) {
		fin >> ch;
		if (ch[0] == 'N' && ch[3] == 'H') {
			fin >> ch;
			fin >> ch;
			//cout << "New softblock " << StoI(ch) << endl;
			//sb* Sb = new sb[StoI(ch)];
			nblock = StoI(ch);
			cout << nblock;

		}
		else if (ch[0] == 'N' && ch[3] == 'T') {
			fin >> ch;
			fin >> ch;
			//cout << "NumTerminals :" << StoI(ch) << endl;
			nterminals = StoI(ch);
		}
		else if (ch[0] == 's') {
			int index = StoI(ch);
			//cout << "softblock " << StoI(ch) << endl;
			fin >> ch;
			fin >> ch;
			fin >> ch;
			fin >> ch;
			fin >> ch;
			fin >> ch;
			fin >> ch;
			//cout << "X " << StoI(ch) << endl;
			int X = StoI(ch);
			fin >> ch;
			//cout << "Y " << StoI(ch) << endl;
			int Y = StoI(ch);
			Sb[index].New(X, Y, 0);
			totalarea += (X*Y);
		}
		//cout << ch << endl
	}

	idealX = sqrt(totalarea*1.15);
	cout << idealX << totalarea << endl;
	fin.close();
	fin.open("n300.pl", ios::in);
	string s = "";
	terimal* tm = new terimal[nterminals];
	while (fin.getline(ch, sizeof(ch), '\n')) {
		//cout << ch << endl;
		int order = 0, pin, x, y;
		for (int i = 0; i < sizeof(ch); i++) {
			//cout << ch[i];
			if (ch[i] == NULL) {
				y = StoI(s);
				s = "";
				//cout << pin << " " << x << " " << y << endl;
				tm[pin - 1].New(pin, x, y);
				order = 0;
				break;
			}
			if (ch[i] > 47) {
				s += ch[i];
			}
			else {
				if (order == 0)
					pin = StoI(s);
				else if (order == 1)
					x = StoI(s);
				order++;
				s = "";
			}
		}

	}


	//隨機建造10棵樹比較大小

	vector<int> random;
	BinaryTree  K;
	int area = 999999, goodtree;

	for (int i = 0; i < nblock; i++) {
		K.InsertLevelorder(i, Sb[i].w, Sb[i].h);
	}
	K.RenewXY();
	/*
	for (int i = 0; i < 10; i++) {
	rand(100, random);
	for (int j = 0; j < 100; j++) {
	//T[i].InsertLevelorder(random[j] - 1, Sb[random[j]-1].w, Sb[random[j]-1].h);
	T[i].InsertLevelorder(random[j] - 1, Sb[random[j] - 1].w, Sb[random[j] - 1].h);
	}
	T[i].RenewXY();
	//cout << T[i].Max_x * T[i].Max_y << endl;
	if (T[i].Max_x * T[i].Max_y < area) {

	area = T[i].Max_x * T[i].Max_y;
	goodtree = i;
	}
	cout << "AREA " << area << endl;
	}
	*/
	//選出好的tree 設定initial值供cost function使用
	BinaryTree BestTree;
	BestTree.Copy(K.root, NULL);
	BestTree.RenewXY();
	//cout << K.root << BestTree.root;

	float  a = (float)K.Max_x / (float)K.Max_y;
	float  b = (float)K.Max_y / (float)K.Max_x;
	float alpha = 0, beta = 1, gama = 0;
	float cost = 999999;
	float range = 1.5;
	initialratio = (a >= b)*b + (a < b)*a;
	initialarea = K.Max_x*K.Max_y;
	PointA = 4;
	PointB = 9;
	int count = 0;
	int ds = 0;
	while (idealX < K.Max_x || idealX < K.Max_y) {
		int r = rand() % 15;
		if (r <= PointA) {
			K.Swap(rand() % nblock, rand() % nblock);
			ds++;
		}
		else if (r <= PointB) {
			K.Rotate(rand() % nblock);
			ds++;
		}
		else {
			K.Disturb(rand() % nblock);
			ds++;
		}
		K.RenewXY();
		//float costnow = alpha * 35 * pow(((K.Max_x / K.Max_y) - 1) * 10, 2) + beta * (K.Max_x + K.Max_y) * 10 + 3000*max((K.Max_x-idealX),0);
		float costnow = alpha * 35 * pow(((K.Max_x / K.Max_y) - 1) * 10, 2) + beta * (K.Max_x + K.Max_y) * 10 + ((K.Max_x - idealX)<0)*(idealX - K.Max_x) * 100 * (gama == 0) + gama * ((K.Max_y - idealX)<0)*(idealX - K.Max_y)*pow(10, (idealX - K.Max_y));

		if (cost == 100000)
			cout << "CCC " << costnow << endl;
		if (costnow <= cost) {
			cost = costnow;
			BestTree.DeleteTree();
			BestTree.Copy(K.root, NULL);
			BestTree.RenewXY();
			//cout << "1 "<< K.Max_x << " " << K.Max_y << " " << costnow << " " << pow(((K.Max_x / K.Max_y) - 1) * 10, 2) << " " << (K.Max_x + K.Max_y) << endl;
		}
		else if (costnow > cost*range) {
			K.DeleteTree();
			K.Copy(BestTree.root, NULL);
			K.RenewXY();
			//cout << "2 " << K.Max_x << " " << K.Max_y << " " << costnow << " " << pow(((K.Max_x / K.Max_y) - 1) * 10, 2) << " " << (K.Max_x + K.Max_y) << endl;
		}
		if (K.Max_x<idealX * 2 && K.Max_y<idealX * 2 && flag == 0) {

			alpha = 0;
			beta = 1;
			flag = 1;
			range = 1.25;
			K.Outputfile();
			PointA = 6;
			PointB = 10;
			cost = alpha * 35 * pow(((K.Max_x / K.Max_y) - 1) * 10, 2) + beta * (K.Max_x + K.Max_y) * 10 + ((K.Max_x - idealX)<0)*(idealX - K.Max_x) * 100;

		}
		else if (K.Max_x + K.Max_y <= idealX * 2 * 1.4 &&abs(K.Max_x - K.Max_y)<150 && flag == 1) {
			cost = costnow;
			alpha = idealX * 0.005;
			beta = 1;
			flag = 2;
			range = 1.1;
			PointA = 7;
			PointB = 12;
			K.Outputfile();
			cost = alpha * 35 * pow(((K.Max_x / K.Max_y) - 1) * 10, 2) + beta * (K.Max_x + K.Max_y) * 10 + ((K.Max_x - idealX)<0)*(idealX - K.Max_x) * 100;
			cout << "STATE 2\n";
			system("pause");
		}
		else if (K.Max_x + K.Max_y <= idealX * 2 * 1.15 && flag == 2) {
			cost = costnow;
			alpha = idealX * 0.003;
			beta = 1;
			flag = 3;
			range = 1.1;
			PointB = 13;
			gama = 0;
			cost = alpha * 35 * pow(((K.Max_x / K.Max_y) - 1) * 10, 2) + beta * (K.Max_x + K.Max_y) * 10 + ((K.Max_x - idealX)<0)*(idealX - K.Max_x) * 100 * (gama == 0) + gama * ((K.Max_y - idealX)<0)*(idealX - K.Max_y)*pow(10, (idealX - K.Max_y));
			cout << "STATE 3\n";
			system("pause");
		}
		else if (K.Max_x <= idealX * 1.105 && K.Max_y <= idealX * 1.105 && flag == 3) {
			cost = costnow;
			alpha = idealX * 0.003;
			beta = 1;
			flag = 4;
			range = 1.1;
			PointB = 12;

			gama = 0.5;
			cost = alpha * 35 * pow(((K.Max_x / K.Max_y) - 1) * 10, 2) + beta * (K.Max_x + K.Max_y) * 10 + ((K.Max_x - idealX)<0)*(idealX - K.Max_x) * 100 * (gama == 0) + gama * ((K.Max_y - idealX)<0)*(idealX - K.Max_y)*pow(10, (idealX - K.Max_y));
			cout << "STATE 4\n";
			system("pause");
		}
		if (count % 10000 == 0) {
			cout << flag << "3 " << K.Max_x << " " << K.Max_y << " " << costnow << " " << pow(((K.Max_x / K.Max_y) - 1) * 10, 2) << " " << (K.Max_x + K.Max_y) << " " << count << " " << ds << endl;
		}

		if (count == 500000)
			K.Outputfile();
		if (count == 5000000)
			K.Outputfile();
		count++;
	}



	float BestCost = Cost(K.Max_x, K.Max_y, 0.2);
	cout << BestCost;
	K.Outputfile();
	cout << "Inita: " << initialarea << "Initr: " << initialratio << endl;


	// read pl file

}