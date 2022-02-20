#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_TREE_HT 256

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

// Mapeamento de um char para string com a sequencia de bits
map<char, string> codes;

// "Liga" um char com um valor inteiro que referente a sua frequencia
map<char, int> freq;

int comparacoesCodificacao = 0;

// Nó da arvore de Huffman
struct MinHeapNode
{
    char data;             // Caracter do no
    int freq;             // Numero de frequencia do Caracter
    MinHeapNode* left, * right;
    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode* root, string str)
{
    comparacoesCodificacao++;
    if (root == NULL)
        return;

    comparacoesCodificacao++;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// Declaramos um fila de prioridade do tipo NoMinHeap, colocamos o container com os nos, e utilizamos a funcao para comparar e
// gerar a fila de prioridade minHeap.
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
    struct MinHeapNode* left, * right, * top;
    for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++) {
        minHeap.push(new MinHeapNode(v->first, v->second));
        comparacoesCodificacao++;
    }

    comparacoesCodificacao++;
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
        comparacoesCodificacao++;
    }
    storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
    comparacoesCodificacao++;
    for (int unsigned i = 0; i < str.size(); i++) {
        freq[str[i]]++;
        comparacoesCodificacao++;
    }
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int unsigned i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL and curr->right == NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans + '\0';
}

void printCharFrequence() {
    cout << endl << "Caracter\t| Repeticoes\t| Codigo" << endl;
    auto c = codes.begin();
    for (auto f = freq.begin(); f != freq.end() && c != codes.end(); f++) {

        cout << f->first << "\t\t  " << f->second << "\t\t  " << c->second << endl;
        c++;
    }

}

//printCharCode
void printCharCode() {
    for (auto v = codes.begin(); v != codes.end(); v++)
        cout << v->first << ' ' << v->second << ' ' << endl;
}


double compressRate(string str_entrada, string str_saida) {

    double numeroBytesSaida = str_saida.length() / 8;
    //cout << endl << "str_entrada: " << str_entrada.length() << "B";
    //cout << endl << "str_saida: " << str_saida.length() / 8 << "B" << endl;
    //cout << endl << "((" << str_entrada.length() << " - " << numeroBytesSaida << "" << "/ " << str_entrada.length() << ")"<< endl;
    return ((str_entrada.length() - numeroBytesSaida) / str_entrada.length());

}

void huffmanRestart() {
    codes.clear();
    freq.clear();
    minHeap = priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>();
    comparacoesCodificacao = 0;
}

#endif // HUFFMAN_H
#pragma once
