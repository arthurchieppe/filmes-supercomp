#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct filme {
    int h_inicio;
    int h_fim;
    int cat;
};

bool is_available(filme &el, bool (&timetable)[24], vector<int> &categorias) {
    if (el.h_inicio > el.h_fim)
        return false;
    if (categorias[el.cat - 1] == 0)
        return false;
    for (int i = el.h_inicio; i < el.h_fim; i++) {
        if (timetable[i] == true)
            return false;
    }
    return true;
}

void print_filmes(vector<filme> &filmes) {
    for (auto &el : filmes) {
        cout << el.h_inicio << " " << el.h_fim << " " << el.cat << "\n";
    }
}

int main(int argc, char **argv) {
    vector<filme> filmes;
    vector<filme> programacao;
    vector<int> categorias;

    bool timetable[24] = {false};

    int n_filmes = 0;
    int n_cat = 0;
    int temp = 0;
    long unsigned int allowed_number_movies = 0;

    cin >> n_filmes >> n_cat;
    filmes.reserve(n_filmes);

    for (int i = 0; i < n_cat; i++) {
        cin >> temp;
        categorias.push_back(temp);
        allowed_number_movies += temp;
    }

    int h_inicio, h_fim, cat;
    for (int i = 0; i < n_filmes; i++) {
        cin >> h_inicio >> h_fim >> cat;
        filmes.push_back({h_inicio, h_fim, cat});
    }

    sort(filmes.begin(), filmes.end(), [](auto &i, auto &j) { return i.h_fim < j.h_fim; });
    // Falta consertar sort para ignorar filmes de dias diferentes
    // Print all filmes

    // print_filmes(filmes);

    int total_number_of_hours = 0;

    for (auto &el : filmes) {
        if (total_number_of_hours == 24)
            break;
        if (allowed_number_movies == (programacao.size()))
            break;
        if (el.h_inicio >= el.h_fim)
            continue;
        if (categorias[el.cat - 1] == 0)
            continue;

        // Nao aceita filmes que comecam, por ex, 23 e terminam 1
        if (is_available(el, timetable, categorias)) {
            for (int i = el.h_inicio; i < el.h_fim; i++) {
                timetable[i] = true;
                total_number_of_hours++;
            }
            categorias[el.cat - 1]--;
            programacao.push_back(el);
        }
    }
    // print_filmes(programacao);
    return 0;
}
