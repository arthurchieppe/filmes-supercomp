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

int main(int argc, char **argv) {
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

    sort(filmes.begin(), filmes.end(), [](auto &i, auto &j)
         { return i.h_fim < j.h_fim; });

    for (auto &el : filmes) {
        cout << el.h_inicio << " " << el.h_fim << " " << el.cat << "\n";
    }

    return 0;
}