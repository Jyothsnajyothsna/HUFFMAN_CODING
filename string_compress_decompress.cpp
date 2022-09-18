#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#define max 120
using namespace std;

//Tree Node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

//Function to allocate a new tree node
Node *getNode(char ch,int freq,Node *left,Node *right)
{
	Node *node = new Node();
	
	node->ch=ch;
	node->freq=freq;
	node->left=left;
	node->right=right;

	return node;
}

//Comparision object to be used to order the heap
struct comp
{
   bool operator()(Node *l,Node *r)
   {
	//highest priority item has lowest frequency
	return l->freq > r->freq;
   }
};

//traverse the Huffman Tree and store Huffman codes
//in map
void encode(Node *root,string str,unordered_map<char,string> &huffmanCode)
{
   	if(root==nullptr)
    	return;

  //found a leaf node
  if(!root->left && !root->right)
  {
        huffmanCode[root->ch] = str;
  }

  encode(root->left,str +"0" , huffmanCode);
  encode(root->right,str+ "1" , huffmanCode);
}
void decode(Node* root,int &top_index,string str)
{
    if(root == nullptr)
    {
        return;
    }
    //found a leaf Node
    if(!root->left && !root->right)
    {
        cout<< root->ch;
        return;
    }
    top_index++;
    if(str[top_index] =='0')
    decode(root->left ,top_index,str);
    else
    decode(root->right,top_index,str);
}

//Build huffman tree 
void buildHuffmanTree(string text)
{
    //count frequency of appearance of each character
    //and store it in a map
    unordered_map<char , int>freq;
    for(char ch: text)
    {
         freq[ch]++;
    }
	
	//create a priority queue to store leaf nodes of huffman tree

	priority_queue<Node *, vector<Node *>,comp> pq;

	//create  a leaf node for each character and add it to the priority queue
	for(auto pair:freq)
	{
		pq.push(getNode(pair.first,pair.second,nullptr,nullptr));
	}

	//do it till there is more than one node in the queue
      while (pq.size()!=1)

	{
	    
     //remove the two nodes of highest priority
  	//lowest frequency from the queue
	Node *left = pq.top();
	pq.pop();
	Node *right = pq.top();
	pq.pop();

	//create a new internal node with these two nodes as children
	// and with frequency equal to the sum of two nodes frequencies 
	//add the new node to the priority queue
	
	int sum = left->freq + right->freq;
	pq.push(getNode('\0',sum,left,right));
}

	//node stores pointer to root of huffman codes;
	Node *root = pq.top();

	//traverse the huffman tree and store huffman code in map
	unordered_map<char,string>huffmanCode;
	encode(root," ",huffmanCode);

	cout<<"Huffman codes are :\n"<<'\n';
	for(auto pair:huffmanCode)
	{
		cout<<pair.first<<"--"<<pair.second<<'\n';
	}

	cout<<"\nOriginal string was :\n"<< text << '\n';

	//encoded string
	string str =" " ;
	for(char ch:text)
	{
		str +=huffmanCode[ch];
	}

	cout<<"\nEncoded String :\n"<<str << '\n';
	
	//traverse the huffmann tree again and this time
	//decode the encoded string
	int top_index = -1;
	cout<<"\nDecoded string is:\n";
	while (top_index < (int)str.size() - 2)
	{
	    decode(root, top_index, str);
	}
}
	int main()
	{
	    string text="Fixed length code: Each code has the same number of bits. Advantage: easy to encode";
   
	    buildHuffmanTree(text);
	    
	    return 0;
	}



