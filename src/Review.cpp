#include "../include/Review.h"

using namespace std;

vector<Review> Review::readCsv(string path)
{
    string arquivo = path + "tiktok_app_reviews.csv";
    fstream arq(arquivo);
    if (arq.is_open())
    {

        string line, word;
        vector<Review> dataSet;
        string object[5];

        int c = 0;

        //Descartar cabe�alho
        getline(arq, line);

        while (getline(arq, line))
        {
            // Transforma a string em stringstream
            stringstream ss(line);

            //Loop com a quantidade de colunas do csv
            for (int j = 0; j < 5; j++)
            {
                getline(ss, word, ',');

                object[j] = word;
            }

            // Montar objeto
            try
            {
                Review review = Review::builder(object);
                dataSet.push_back(review);
            }
            catch (const exception &e)
            {
                c++;
            }
        }

        // Fechar arquivo
        arq.close();

        //retorna o dataset
        return dataSet;
    }
    else
    {
        cout << "Falha ao abrir arquivo" << endl;
        exit(-1);
    }
}

void Review::writeBinary(Review *data, int n)
{
    fstream binaryFile("./tiktok_app_reviews.bin", ios::out | ios::binary);
    if (binaryFile.is_open())
    {

        int tamBlock = sizeof(Review) * n;

        binaryFile.write((char *)data, tamBlock);

        binaryFile.close();
    }
    else
    {
        cout << "Falha ao abrir arquivo" << endl;
    }
}

Review *Review::readBinaryN(int n)
{
    Review *data = new Review[n];
    Review *review = new Review;

    fstream binaryFile("./tiktok_app_reviews.bin", ios::in | ios::binary);
    if (binaryFile.is_open())
    {
        int nRegisters = sizeArq(binaryFile) / sizeof(Review);

        for (int i = 0; i < n; i++)
        {

            // Gera um numero aleatorio menor que o numero de registros
            int nRandom = rand() % nRegisters;

            // Ajusta o ponteiro de leitura para o registro de indice aleatorio
            binaryFile.seekp(nRandom * sizeof(Review));

            // Realiza a leitura de registro
            binaryFile.read((char *)review, sizeof(Review));

            data[i] = *review;
        }
        return data;
    }
    else
    {
        cout << "Falha na abertura do arquivo" << endl;
        exit(-1);
    }
}

/*Review* Review::accessBinaryI(int i) {
    Review* review = new Review;

    fstream binaryFile("./tiktok_app_reviews.bin", ios::in | ios::binary);
    if (binaryFile.is_open())
    {
        binaryFile.seekp(i * sizeof(Review));

        // Realiza a leitura de registro
        binaryFile.read((char*)review, sizeof(Review));

        return review;
    }
    else
    {
        cout << "Falha na abertura do arquivo" << endl;
        exit(-1);
    }

}
*/

int Review::sizeArq(fstream &arq)
{
    arq.seekg(0, arq.end);
    int tam = arq.tellg();
    arq.seekg(0);
    return tam;
}

Review Review::builder(string *object)
{
    Review review = Review();
    review.id = object[0];
    review.text = object[1];
    review.upvotes = stoi(object[2]);
    review.app_version = object[3];
    review.posted_date = object[4];

    return review;
}

void Review::printElement()
{
    cout << this->id << " , ";
    cout << this->text << " , ";
    cout << this->upvotes << " , ";
    cout << this->app_version << " , ";
    cout << this->posted_date << endl;
}

void Review::writeElementTxt(Review *data, int n)
{
    ofstream arqSaida;
    arqSaida.open("ReviewArqSaida.txt");

    if (arqSaida.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            arqSaida << "linha: " << i + 1 << endl;
            arqSaida << data[i].id << " , ";
            arqSaida << data[i].text << " , ";
            arqSaida << data[i].upvotes << " , ";
            arqSaida << data[i].app_version << " , ";
            arqSaida << data[i].posted_date << endl;
        }

        arqSaida.close();
    }
    else
    {
        cout << "Erro ao abrir arquivo de sa�da" << endl;
    }
}