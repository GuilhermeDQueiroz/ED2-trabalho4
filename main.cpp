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

#define M 3

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (!verificaBinario("tiktok_app_reviews.bin"))
    {
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

    while (select != 0)
    {

        switch (select)
        {

        case 1:
            compressSet();
            break;

        case 2:
            decompressSet();
            break;

        case 3:
            execSeqCompress();
            break;

        case 0:
            exit(2);
            break;

        default:
            cout << "ERRO! Opcao invalida!" << endl;
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

void compressSet()
{
    int n;
    cout << "Digite um valor N: ";
    cin >> n;

    fstream binaryFile("./reviewsComp.bin", ios::out | ios::binary);
    auto dataInput = Review::readBinaryN(n);
    string codedData;

    for (int i = 0; i < n; i++)
    {
        auto text = dataInput[i].text;

        huffmanRestart();
        calcFreq(text, text.length());
        HuffmanCodes(text.length());

        for (auto i : text)
        {
            codedData += codes[i];
        }

        if (binaryFile.is_open())
        {
            binaryFile.write((char *)&codedData, sizeof(codedData));
        }
        else
        {
            cout << "Erro! Arquivo fechado..." << endl;
        }
    }

    binaryFile.close();
    cout << "reviewsComp.bin Criado com Sucesso!" << endl;
}

void decompressSet()
{
    fstream binaryFile("./reviewsComp.bin", ios::in | ios::binary);

    if (binaryFile.is_open())
    {
        ofstream arqSaida;
        arqSaida.open("reviewsOrig.txt");

        if (arqSaida.is_open())
        {
            if (minHeap.empty())
            {
                cout << "ERRO! Arvore Vazia" << endl;
            }
            string coded;
            char aux = ' ';

            while (aux != EOF)
            {
                binaryFile.read((char *)aux, sizeof(char));
                coded += aux;
            }

            string decoded = decode_file(minHeap.top(), coded);
            arqSaida << decoded;
            arqSaida.close();
        }

        binaryFile.close();
    }
}

void execCompressAux(int n, double *somaTaxaComp, double *somaComp, int leva)
{
    huffmanRestart();

    string coded, decoded, text = Review::readBinaryN(n)->text;
    calcFreq(text, text.length());
    HuffmanCodes(text.length());

    for (auto i : text)
    {
        coded += codes[i];
    }

    double taxaComp = compressRate(text, coded) * 100;
    cout << "Taxa de Compressao da Leva: " << leva << " = " << taxaComp << endl;

    *somaTaxaComp += taxaComp;
    *somaComp += codeComps;
}

void execSeqCompress()
{
    string coded, decoded, text;
    double somaComp = 0, somaTaxaComp = 0;

    for (int i = 0; i < M; i++)
    {
        execCompressAux(1000, &somaTaxaComp, &somaComp, i + 1);
    }

    ofstream arqSaida;
    arqSaida.open("reviewsComp.txt");

    arqSaida << "Media TaxaComp: " << somaTaxaComp / 3 << endl;
    arqSaida << "Media SomaComp: " << somaComp / 3 << endl;

    somaComp = 0;
    somaTaxaComp = 0;

    for (int i = 0; i < M; i++)
    {
        execCompressAux(5000, &somaTaxaComp, &somaComp, i + 1);
    }

    arqSaida << "Media TaxaComp: " << somaTaxaComp / 3 << endl;
    arqSaida << "Media SomaComp: " << somaComp / 3 << endl;

    somaComp = 0;
    somaTaxaComp = 0;

    for (int i = 0; i < M; i++)
    {
        execCompressAux(10000, &somaTaxaComp, &somaComp, i + 1);
    }

    arqSaida << "Media TaxaComp: " << somaTaxaComp / 3 << endl;
    arqSaida << "Media SomaComp: " << somaComp / 3 << endl;

    somaComp = 0;
    somaTaxaComp = 0;

    for (int i = 0; i < M; i++)
    {
        execCompressAux(100000, &somaTaxaComp, &somaComp, i + 1);
    }

    arqSaida << "Media TaxaComp: " << somaTaxaComp / 3 << endl;
    arqSaida << "Media SomaComp: " << somaComp / 3 << endl;

    somaComp = 0;
    somaTaxaComp = 0;

    for (int i = 0; i < M; i++)
    {
        execCompressAux(1000000, &somaTaxaComp, &somaComp, i + 1);
    }

    arqSaida << "Media TaxaComp: " << somaTaxaComp / 3 << endl;
    arqSaida << "Media SomaComp: " << somaComp / 3 << endl;
    arqSaida.close();
}
