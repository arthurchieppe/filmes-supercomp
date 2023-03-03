#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct filme
    {
        int h_inicio;
        int h_fim;
        int cat;
    };

int main(int argc, char **argv)
{
    vector<filme> filmes;
    vector<filme> programacao;
    vector<int> categorias;

    int n_filmes = 0;
    int n_cat = 0;
    int temp = 0;

    cin >> n_filmes >> n_cat;
    filmes.reserve(n_filmes);

    for (int i = 0; i < n_cat; i++) {
        cin >> temp;
        categorias.push_back(temp);
    }

    int h_inicio, h_fim, cat;
    for (int i = 0; i < n_filmes; i++) {
        cin >> h_inicio >> h_fim >> cat;
        filmes.push_back({h_inicio, h_fim, cat});
    }

    







    
    programacao.reserve(n);

    int peso, valor;
    for (int i = 0; i < n; i++)
    {
        cin >> peso;
        cin >> valor;
        itens.push_back({i, valor, peso});
    }

    sort(itens.begin(), itens.end(), [](auto &i, auto &j)
         { return i.valor > j.valor; });

    peso = 0;
    valor = 0;

    for (auto &el : itens)
    {
        if (el.peso + peso <= W)
        {
            mochila.push_back(el);
            peso += el.peso;
            valor += el.valor;
        }
    }

    sort(mochila.begin(), mochila.end(), [](auto &i, auto &j)
         { return i.id < j.id; });

    for (auto &e : mochila)
    {
        cout << e.id << " ";
        cout << e.peso << " ";
        cout << e.valor << "\n";
    }

    return 0;
}