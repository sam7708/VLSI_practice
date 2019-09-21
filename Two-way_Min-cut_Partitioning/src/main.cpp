#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include<cmath>
#include<fstream>
using namespace std;
#define SIZE 100
int Cstringtoint(string name);
int GtoBi(int gain, int maxpin);

//partial sum ==0 end
//±NAaAOaoCELLname’?|‥int (ex :C1 = 1)
int Cstringtoint(string name) {
	int x = 0;
	for (int i = 1; i<name.size(); i++) {
     int pow = 1;
     for (int j=1;j<= (name.size() - 1 - i);j++)
       pow = pow *10;
		x += (name[i] - 48)*pow;
	}
	return x;
}


//±NGAIN-EAa’?|‥bucklist index (maxpin index=0,gain=0REindex=maxpin )
int GtoBi(int gain, int maxpin) {
	int index;
	index = (maxpin - gain);
	return index;
}
const int setmax(int max) {
	const int a = max;
	return a;
}


class cell {
public:
	cell();
	void addnet(int n);
	vector<int> C_list;
	int C_name;
	int C_weight;
	bool C_side; // 0 means at left side 1 means at right side;
	bool C_lock; // 0 means unlock cell
	int C_gain;
};
cell::cell() {
	int numberofcell = 0;
}
void cell::addnet(int net) {
	C_list.push_back(net);
}

class net {
public:
	net();
	int N_name;
	void addcell(int cell);
	vector<int> N_list;
};
net::net() {
	int t = 1;
}

void net::addcell(int cell) {
	N_list.push_back(cell);
}



//§Q￥ILINKLIST °}|C?}clRE°μbucklist μ2oc
class LinkedList;    // ?°?F±Nclass LinkedList3]|‥class ListNodeaofriend,
					 // ?Y-n￥y?A§i
class ListNode {
private:
	int data;

	ListNode *next;
public:
	ListNode() :data(0), next(0){};
	ListNode(int a) :data(a), next(0) {};

	friend class LinkedList;

};

class LinkedList {
private:
	// int size;                // size?O￥I‥O°O?yLinked listaoao?×, ?D￥2-n
	ListNode * first;            // listao2A?@-Onode
	ListNode * now;				// ?o?ypickcellao|i﹐m
public:
	LinkedList() :first(0), now(0) {};
	void PrintList();           // |L￥XlistaocO|3﹐eRA
	void Push_back(int x);      // |blistao§A?U·s?Wnode

	void Delete(int x);         // §R°￡list??ao int x
	void Clear();               // §a?a|elist§R°￡

	void Reset_now();
	int Pick_onecell();
	int Pull_onecell();
};


void LinkedList::PrintList() {

	if (first == 0) {                      // |paGfirst node?u|VNULL, ai￥Ulist‥S|3﹐eRA
		cout << "List is empty.\n";
		return;
	}

	ListNode *current = first;             // ￥Ipointer *current|blist??2?°E
	while (current != 0) {                 // Traversal
		cout << "c" << current->data << endl;
		current = current->next;
	}
}

void LinkedList::Push_back(int x) {

 
	ListNode *newNode = new ListNode(x);   // 配置新的記憶體
	newNode->next = first;                 // 先把first接在newNode後面
	first = newNode;                       // 再把first指向newNode所指向的記憶體位置
	now = newNode;
}


void LinkedList::Delete(int x) {

	ListNode *current = first,
		*previous = 0;
	while (current != 0 && current->data != x) {  // Traversal
		previous = current;                       // |paGcurrent?u|VNULL
		current = current->next;                  // cI?Ocurrent->data == x
	}                                             // §Yμ2§owhile loop

	if (current == 0) {                 // list‥S|3-n§Raonode, cI?Olist?°empty
		std::cout << "There is no " << x << " in list.\n";
		// return;
	}
	else if (current == first) {        // -n§R°￡aonode-e|n|blistao?}AY
		first = current->next;          // §afirst2?‥i?U?@-Onode
		now = first;
		delete current;                 // |paGlist￥u|3?@-Onode, ‥o?ofirst’N·|?u|VNULL
		current = 0;                    // ·i?u?D3Qdelete?a, ±N‥a?u|VNULL, ￥i￥HA×§K?￡￥2-nbug
										// return;                     
	}
	else {                              // ‥a?l±!ap, list??|3±y§R°￡aonode, 
		previous->next = current->next; // |O￥Bnode?￡?°first, |1REprevious?￡?°NULL
		delete current;
		current = 0;
		// return;
	}
}


void LinkedList::Clear() {

	while (first != 0) {            // Traversal
		ListNode *current = first;
		first = first->next;
		now = 0;
		delete current;
		current = 0;
	}
}



int LinkedList::Pick_onecell() {
	if (now == 0) {
		return -1;
	}
	ListNode *current = now;
	if (current != 0) {
		now = current->next;
		return current->data;
	}

}
int LinkedList::Pull_onecell() {
	if (now == 0) {
		return -1;
	}
	ListNode *current = now;
	if (current != 0) {
		now = current->next;
		return current->data;
	}
}

void LinkedList::Reset_now() {
	now = first;
}


//bucketlist 3]cwμ2§o

int main(int argc,char** argv) {
	static map<int, int> cellindex;
	map<int, int> netindex;
	map<int, int>::iterator iter;
	LinkedList A_side;
	LinkedList B_side;

	fstream fin;
	char line[SIZE];
	fin.open(argv[1], ios::in);
	int totalcell = 0;
	int mincut = 9999;
	while (fin.getline(line, sizeof(line), '\n')) {
		totalcell++;
	}

	fin.close();
	fin.open(argv[1], ios::in);
	int cindex = 0;

	cell* Cell = new cell[120000];
	while (fin.getline(line, sizeof(line), '\n')) {
		int a = 0, weight = 0;
		string cellname, weigh;
		int x;

		for (int i = 0; i<100; i++) {
			if (line[i] == '\0') {
				break;
			}
			else if (line[i] != ' ') {
				if (a == 0)
					cellname += line[i];
				else {
					if (line[i + 1] != '\0')
						weight = ((line[i] - 48) * 10) + line[i + 1] - 48;
					else
						weight = line[i] - 48;
				}
			}
			else
				a++;
		}
		x = Cstringtoint(cellname);
		cellindex[x] = cindex;
		Cell[cindex].C_name = x;
		Cell[cindex].C_weight = weight;
		Cell[cindex].C_gain = 0;
		Cell[cindex].C_lock = 0;
		if (cindex < totalcell / 2)
			Cell[cindex].C_side = 0;
		else
			Cell[cindex].C_side = 1;


		cindex++;

	}
	fin.close();
	stringstream ss;
	int nindex = 0;
	net* Net = new net[120000];

	fin.open(argv[2], ios::in);

	while (fin.getline(line, sizeof(line), '\n')) {
		int a = 0;
		string net, cell;
		int n, c;
		for (int i = 0; i<100; i++) {
			if (line[i] == '\0') {
				break;
			}
			else if (line[i] == 'n') {
				for (int j = 1; j<10; j++) {
					if (line[i + j] == ' ') {
						ss.str("");
						ss.clear();
						ss << net;
						ss >> n;
						break;
					}
					net += line[i + j];
				}
				netindex[n] = nindex;
				Net[nindex].N_name = n;
			}
			else if (line[i] == 'c') {
				cell = "";
				for (int j = 1; j<10; j++) {
					if (line[i + j] == ' ') {
						ss.str("");
						ss.clear();
						ss << cell;
						ss >> c;
						break;
					}
					cell += line[i + j];
				}
				Net[nindex].addcell(c);
				Cell[cellindex[c]].addnet(n);

			}
		}
		nindex++;
	}

	//計算maxpin
	int maxp = 0;
	for (int i = 0; i < totalcell; i++){
   if(Cell[i].C_list.size()>maxp)
     maxp = Cell[i].C_list.size();
 }
	const int *maxpin = &maxp;


	bool firstexit = 0,gainzreo=0;
	int A_weight = 0, B_weight = 0;
	LinkedList* A_bucket = new LinkedList[*maxpin * 2 + 1];
	LinkedList* B_bucket = new LinkedList[*maxpin * 2 + 1];
	//initial bucket list(gain and weight)
	int A = 0, B = 0;
// return 0;
Initial:
	bool firstpick = 1;
	for (iter = netindex.begin(); iter != netindex.end(); iter++) {
		int ni = iter->second, A0 = 0, B0 = 0;
		for (int i = 0; i < Net[ni].N_list.size(); i++) {
			int ci = cellindex[Net[ni].N_list[i]];
			A0 += (Cell[ci].C_side == 0);
			B0 += Cell[ci].C_side;
			//cout <<  "cellname : "<<Net.N_list[ni][i] <<" "<<ci << endl;

		}
		//‥I?U?A￥??§±!§I±Ngain-E|s?Jcell?o |]?°?@cell·||3|h±onet?U3s 3I?a?~?O￥??Tgain-E
		for (int i = 0; i < Net[ni].N_list.size(); i++) {
			int ci = cellindex[Net[ni].N_list[i]];
			if (A0 == 1) 
				if (Cell[ci].C_side == 0)
					Cell[ci].C_gain++;
			if (B0 ==0  )
				if (Cell[ci].C_side == 0)
					Cell[ci].C_gain--;
			if (B0 ==1)
				if (Cell[ci].C_side == 1)
					Cell[ci].C_gain++;
			if (A0 ==0)
				if (Cell[ci].C_side == 1)
					Cell[ci].C_gain--;
		}

	}
	//cout << "重建bucket";

	for (int i = 0; i < totalcell; i++) {
		if (Cell[i].C_side == 0) {
			A_bucket[GtoBi(Cell[i].C_gain, *maxpin)].Push_back(Cell[i].C_name);
			A_weight += Cell[i].C_weight;
			A++;
		}
		else {
			B_bucket[GtoBi(Cell[i].C_gain, *maxpin)].Push_back(Cell[i].C_name);
			B_weight += Cell[i].C_weight;
			B++;
		}
	}

	float N = (float)(A_weight + B_weight) / (float)10;
	int Partial_sum = 0, Max_partial_sum = 0;
	bool save = false;
	//cout << "OUT INITIAL\n";
Pickcell:
	//cout << "ENTER PICK\n";
	
	//float N = (float)(A + B) / (float)10;
	//float r = (float)A_weight / (float)V;
	int pick = -1;
	for (int i = 0; i <= *maxpin * 2; i++) {
		while (int pickfromA = A_bucket[i].Pick_onecell()) {
			if (pickfromA == -1) {
				A_bucket[i].Reset_now();
				break;
			}
			else {
				float R = abs(A_weight - B_weight - (Cell[cellindex[pickfromA]].C_weight));
				//float R = abs(A- B - 2);
				//cout << "PICK A :" << pickfromA << " R= " << R << " N= " << N << endl;
				if (R<=N) {
					pick = pickfromA;
					A_bucket[i].Reset_now();
					break;
				}
			}
		}
		if (pick != -1) break;
		while (int pickfromB = B_bucket[i].Pick_onecell()) {
			if (pickfromB == -1) {
				B_bucket[i].Reset_now();
				break;
			}
			else {
				float R = abs(B_weight - A_weight - (Cell[cellindex[pickfromB]].C_weight * 2));
				//float R = abs(B - A - 2);
				if (R<=N) {
					pick = pickfromB;
					B_bucket[i].Reset_now();
					break;
				}
			}
		}
		if (pick != -1) break;
	}	
	
	int cii = -1;
	int oldside = Cell[cellindex[pick]].C_side;
	int Pickcell_gain = Cell[cellindex[pick]].C_gain;
	if (pick == -1) {
		if (firstpick == 1)
			goto Exit;
		else 
			goto Restore;
		
	}
	
	Partial_sum += Pickcell_gain;
	if (Partial_sum > Max_partial_sum) {
		Max_partial_sum = Partial_sum;
		save = true;
	}


	if (firstpick == 1 && Partial_sum <= 0)
		goto Exit;
	if (Partial_sum < 1) 
		goto Restore;
	
		


	firstpick = 0;
  


	Cell[cellindex[pick]].C_lock = 1;
	for (int i = 0; i < Cell[cellindex[pick]].C_list.size(); i++) {
		// Cell.C_list[cellindex[pickcell]][i] to net name
		int netname = Cell[cellindex[pick]].C_list[i];
		int A0 = 0, B0 = 0;
		for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
			int ci = cellindex[Net[netindex[netname]].N_list[j]];
			A0 += (Cell[ci].C_side == 0);
			B0 += Cell[ci].C_side;
		}

		if (Cell[cellindex[pick]].C_side == 0) {
			if (B0 == 0) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0) {
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain++;
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
					}

				}
			}
			if (B0 == 1) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0 && Cell[ci].C_side == 1) {
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain--;
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
						break;
					}

				}
			}
		}
		else {
			if (A0 == 0) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0) {
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain++;
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
					}
				}
			}
			if (A0 == 1) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0 && Cell[ci].C_side == 0) {
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain--;
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
						break;
					}

				}
			}
		}
		//cout << "A0:" << A0 << "B0:" << B0 << endl;
		if (oldside == 0) {
			A0--; B0++;
		}
		else {
			A0++; B0--;
		}
		//cout << "A0:" << A0 << "B0:" << B0 << endl;
		if (Cell[cellindex[pick]].C_side == 0) {
			if (A0 == 0) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0 && Cell[ci].C_side == 1) {
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain--;
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
					}

				}
			}
			if (A0 == 1) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0 && Cell[ci].C_side == 0) {
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain++;
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
						break;
					}
				}
			}
		}
		else {
			if (B0 == 0) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0 && Cell[ci].C_side == 0) {
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain--;
						A_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);

					}

				}
			}
			else if (B0 == 1) {
				for (int j = 0; j < Net[netindex[netname]].N_list.size(); j++) {
					int cellname = Net[netindex[netname]].N_list[j];
					int ci = cellindex[cellname];
					if (Cell[ci].C_lock == 0 && Cell[ci].C_side == 1) {
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Delete(cellname);
						Cell[ci].C_gain++;
						B_bucket[GtoBi(Cell[ci].C_gain, *maxpin)].Push_back(cellname);
						break;
					}
				}
			}
		}
	}

	// 最後才換邊 更新BUCKETLIST
	cii = cellindex[pick];
	//cout << "CHANGESIDE\n";
	if (Cell[cii].C_side == 0) {
		A_bucket[GtoBi(Cell[cii].C_gain, *maxpin)].Delete(pick);
		A_weight -= Cell[cii].C_weight;
		Cell[cii].C_side = 1;
		B_weight += Cell[cii].C_weight;

	}
	else {
		B_bucket[GtoBi(Cell[cii].C_gain, *maxpin)].Delete(pick);
		B_weight -= Cell[cii].C_weight;
		Cell[cii].C_side = 0;
		A_weight += Cell[cii].C_weight;

	}
	if (save == true) {
		A_side.Clear();
		B_side.Clear();
		for (int i = 0; i < totalcell; i++) {
			if (Cell[i].C_side == 0)
				A_side.Push_back(Cell[i].C_name);
			else
				B_side.Push_back(Cell[i].C_name);
		}
		save = false;
	}

	//cout << "OUT PICK\n";
	if (Partial_sum > 0)
		goto Pickcell;
	else
		goto Restore;

Restore: {

	Partial_sum = Max_partial_sum = 0;
	A_weight = 0;
	B_weight = 0;
	for (int i = 0; i <= *maxpin * 2; i++) {
		A_bucket[i].Clear();
		B_bucket[i].Clear();

	}
	//A_side.PrintList();
	//B_side.PrintList();
	while (int pickfromA = A_side.Pick_onecell()) {
		if (pickfromA == -1) break;
		int ci = cellindex[pickfromA];
		//cout << pickfromA << " gain is " << Cell.C_gain[ci] << endl;
		Cell[ci].C_lock = 0;
		Cell[ci].C_gain = 0;
		Cell[ci].C_side = 0;
		//cout << pickfromA << " gain is " << Cell.C_gain[ci] << endl;
	}
	while (int pickfromB = B_side.Pick_onecell()) {
		if (pickfromB == -1) break;
		int ci = cellindex[pickfromB];
		//cout << pickfromB << " gain is " << Cell.C_gain[ci] << endl;
		Cell[ci].C_lock = 0;
		Cell[ci].C_gain = 0;
		Cell[ci].C_side = 1;
		//cout << pickfromB << " gain is " << Cell.C_gain[ci] << endl;
	}
	int cut = 0;
	for (iter = netindex.begin(); iter != netindex.end(); iter++) {
		int ni = iter->second, A = 0, B = 0;
		for (int i = 0; i < Net[ni].N_list.size(); i++) {
			A += (Cell[cellindex[Net[ni].N_list[i]]].C_side == 0);
			B += (Cell[cellindex[Net[ni].N_list[i]]].C_side == 1);
		}
		if (A != 0 && B != 0) 
			cut++;
	}
	
	//cout << "OUT R\n";
	if (cut < mincut) {
		mincut = cut;
		goto Initial;
	}
	else
		goto Exit;
		
	}


	 Exit:


		 int cut = 0;
		 for (iter = netindex.begin(); iter != netindex.end(); iter++) {
			 int ni = iter->second, A = 0, B = 0;
			 for (int i = 0; i < Net[ni].N_list.size(); i++) {
				 A += (Cell[cellindex[Net[ni].N_list[i]]].C_side == 0);
				 B += (Cell[cellindex[Net[ni].N_list[i]]].C_side == 1);
			 }
			 if (A != 0 && B != 0) {
				 cut++;
			 }
		 }
		 int AT = 0, BT = 0;
		 A_side.Reset_now();
		 B_side.Reset_now();
		 while (int pickfromA = A_side.Pick_onecell()) {
			 if (pickfromA == -1) break;
			 AT++;
		 }
		 while (int pickfromB = B_side.Pick_onecell()) {
			 if (pickfromB == -1) break;
			 BT++;
		 }		 
		 fstream fp;
		 fp.open(argv[3], ios::out);//開啟檔案

		 fp << "cut_size: " << cut << endl;

		 fp << "A " << AT<<endl;
		 A_side.Reset_now();
		 B_side.Reset_now();
		 while (int pickfromA = A_side.Pick_onecell()) {
			 if (pickfromA == -1) break;
			 fp << "c" << pickfromA << endl;
		 }

		 fp << "B " << BT << endl;
		 while (int pickfromB= B_side.Pick_onecell()) {
			 if (pickfromB == -1) break;
			 fp << "c" << pickfromB << endl;
		 }


		 fp.close();//關閉檔案



		 return 0;
}




