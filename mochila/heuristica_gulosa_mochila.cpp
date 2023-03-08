#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct item
{
    int id;
    int valor;
    int peso;
};

int main(int argc, char **argv)
{
 
    int n = 0;
    int W = 0;

    vector<item> itens;
    vector<item> mochila;

    cin >> n >> W;
    itens.reserve(n);

    int peso, valor;
    for (int i = 0; i < n; i++)
    {
        cin >> peso;
        cin >> valor;
       itens.push_back({i, valor, peso});
    }

    sort(itens.begin(), itens.end(), [](auto &i, auto &j){ return i.valor > j.valor;});

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

    sort(mochila.begin(), mochila.end(),[](auto &i, auto &j) { return i.id < j.id; });

    for (auto &e : mochila)
    {
        cout << e.id << " ";
        cout << e.peso << " ";
        cout << e.valor << "\n";
    }

    return 0;
}
