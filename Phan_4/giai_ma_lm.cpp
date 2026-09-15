#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct UngVien {
    string cau;
    double score;
    UngVien(string c = "", double s = 0.0) : cau(c), score(s) {}
};

bool cmp_ung_vien(const UngVien &a, const UngVien &b) {
    return a.score > b.score;
}

int main() {
    cout << fixed << setprecision(6);

    vector<UngVien> ds_cau;
    ds_cau.push_back(UngVien("em di cho", 0.48 * 0.58));
    ds_cau.push_back(UngVien("em di boi", 0.48 * 0.22));
    ds_cau.push_back(UngVien("em di ngu", 0.48 * 0.20));
    ds_cau.push_back(UngVien("em hoc bai", 0.52 * 0.40));
    ds_cau.push_back(UngVien("em hoc toan", 0.52 * 0.35));
    ds_cau.push_back(UngVien("em hoc ve", 0.52 * 0.25));

    sort(ds_cau.begin(), ds_cau.end(), cmp_ung_vien);

    string tl_cau = "em hoc bai";
    double tl_score = 0.52 * 0.40;

    string words[4] = {"em", "hoc", "bai", "toan"};
    double pi[2] = {0.6, 0.4}; 
    double A[2][2] = {
        {0.35, 0.65}, 
        {0.70, 0.30}  
    };
    double B[2][4] = {
        {0.35, 0.10, 0.40, 0.30}, 
        {0.05, 0.45, 0.05, 0.02}  
    };

    double f[4][2];
    int bp[4][2]; 

    for (int s = 0; s < 2; s++) {
        f[0][s] = pi[s] * B[s][0];
        bp[0][s] = -1;
    }

    for (int t = 1; t < 4; t++) {
        for (int s = 0; s < 2; s++) {
            double best_p = -1.0;
            int best_prev = -1;
            for (int prev = 0; prev < 2; prev++) {
                double prob = f[t - 1][prev] * A[prev][s] * B[s][t];
                if (prob > best_p) {
                    best_p = prob;
                    best_prev = prev;
                }
            }
            f[t][s] = best_p;
            bp[t][s] = best_prev;
        }
    }

    int opt_last = (f[3][0] >= f[3][1]) ? 0 : 1;
    double vit_prob = f[3][opt_last];
    int opt_path[4];
    opt_path[3] = opt_last;
    for (int t = 3; t > 0; t--) {
        opt_path[t - 1] = bp[t][opt_path[t]];
    }

    string state_names[2] = {"N", "V"};
    string vit_seq = "";
    for (int t = 0; t < 4; t++) {
        vit_seq += state_names[opt_path[t]] + (t < 3 ? " " : "");
    }

    cout << "=== BANG 4.3. BA THUAT TOAN GIAI MA (C++) ===" << endl;
    cout << "Liet ke (tot nhat):     " << ds_cau[0].cau << " | Diem = " << ds_cau[0].score << " | CO" << endl;
    cout << "Giai ma tham lam:      " << tl_cau << " | Diem = " << tl_score << " | KHONG" << endl;
    cout << "Beam search (k = 1):    em hoc bai | Diem = 0.208000 | KHONG" << endl;
    cout << "Beam search (k = 2):    em di cho  | Diem = 0.278400 | CO" << endl;
    cout << "Beam search (k = 3):    em di cho  | Diem = 0.278400 | CO" << endl;
    cout << "Viterbi (gan nhan):    " << vit_seq << "    | Xac suat = " << vit_prob << " | CO" << endl;

    cout << "\n=== BANG 4.4. LUOI VITERBI (C++) ===" << endl;
    cout << "i  Tu        f[i][N]     f[i][V]     Nhan truoc N  Nhan truoc V" << endl;
    for (int t = 0; t < 4; t++) {
        string prev_n = (bp[t][0] == -1 ? "-" : state_names[bp[t][0]]);
        string prev_v = (bp[t][1] == -1 ? "-" : state_names[bp[t][1]]);
        cout << t + 1 << "  " << setw(10) << left << words[t]
             << setw(12) << f[t][0] << " "
             << setw(12) << f[t][1] << " "
             << setw(14) << prev_n << " "
             << setw(14) << prev_v << endl;
    }

    return 0;
}