#include <iostream>
#include <fstream>

#include "include/Review.h"
#include "./include/Huffman.h"

using namespace std;

void compressSet();
bool verificaBinario(string nome);
void decompressSet();
void execSeqCompress();

vector<Review> dataReview;

ofstream arqSaida;

string pathCsv;


int main(int argc, char* argv[])
{
    srand(time(NULL));

    if (!verificaBinario("tiktok_app_reviews.bin")){
        if (argv[1])
        {
            pathCsv = argv[1];
            //pathCsv = pathCsv + "/";
        }
        else
        {
            pathCsv = "";
        }

        dataReview = Review::readCsv(pathCsv);
        Review::writeBinary(dataReview.data(), dataReview.size());
    }
    huffmanRestart();
    int select;
    
    cout << "Trabalho de ED II (Parte 4)" << endl;
    cout << "(1) - Comprimir Conjunto N" << endl
        << "(2) - Descomprimir o Arquivo" << endl
        << "(3) - Executar Sequencia de Compressoes" << endl
        << "(0) - Sair" << endl;
    
    cin >> select;

    while(select != 0){
    
        switch(select){

        case 1: compressSet();
            break;

        case 2: decompressSet();
            break;

            case 3: execSeqCompress();
            break;

        case 0: exit(2);
            break;

        default: cout << "ERRO! Opcao invalida!" << endl;

        }

        cout << "Trabalho de ED II (Parte 4)" << endl;
        cout << "(1) - Comprimir Conjunto N" << endl
            << "(2) - Descomprimir o Arquivo" << endl
            << "(3) - Executar Sequencia de Compressoes" << endl
            << "(0) - Sair" << endl;

        cin >> select;

    }
   
}


bool verificaBinario(string nome)
{
    string path = "./bin/" + nome;
    fstream arq(path);
    if (arq.is_open())
    {
        arq.close();
        return true;
    }
    return false;
}


void compressSet() {
    int n;
    cout << "Digite um valor N: ";
    cin >> n;

    fstream binaryFile("./reviewsComp.bin", ios::out | ios::binary);
    string dataInput = Review::readBinaryN(n)->text;
    int tam = dataInput.length();
    string codedData;

    huffmanRestart();
    calcFreq(dataInput, tam);
    HuffmanCodes(tam);

        for (auto i : dataInput) {
            codedData += codes[i];
        }

        if (binaryFile.is_open())
        {
            for (int i = 0; i < codedData.length(); i++) {
                binaryFile.write((char*)codedData[i], sizeof(char));
            }
            binaryFile.close();
        }

    cout << "reviewsComp.bin Criado com Sucesso!" << endl;
       
}


void decompressSet() {
    fstream binaryFile("./reviewsComp.bin", ios::in | ios::binary);

    if (binaryFile.is_open())
    {
        ofstream arqSaida;
        arqSaida.open("reviewsOrig.txt");

        if (arqSaida.is_open()){
            if(minHeap.empty()){
                cout << "ERRO! Arvore Vazia" << endl;
            }
            string coded;
            char aux = ' ';
            
            //mudar EOF e tals, tamo lendo burro
            while(aux != EOF) {
                binaryFile.read((char*)aux, sizeof(char));
                coded += aux;
            }

            string decoded = decode_file(minHeap.top(), coded);
            arqSaida << decoded;
            arqSaida.close();
        }

        binaryFile.close();
    }

}


void execSeqCompress(){
    
}





