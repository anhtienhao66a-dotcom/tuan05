#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct HoatDong {
    string id;
    int s;
    int f;
    HoatDong(string id_ = "", int s_ = 0, int f_ = 0) : id(id_), s(s_), f(f_) {}
};

bool tuong_thich(const HoatDong &a, const HoatDong &b) {
    return a.f <= b.s || b.f <= a.s;
}

bool cmp_ket_thuc(const HoatDong &a, const HoatDong &b) {
    if (a.f != b.f) return a.f < b.f;
    return a.s < b.s;
}

vector<string> ket_thuc_som(vector<HoatDong> ds) {
    sort(ds.begin(), ds.end(), cmp_ket_thuc);
    vector<string> chon;
    int cur_f = 0;
    for (size_t i = 0; i < ds.size(); i++) {
        if (ds[i].s >= cur_f) {
            chon.push_back(ds[i].id);
            cur_f = ds[i].f;
        }
    }
    return chon;
}

bool cmp_bat_dau(const HoatDong &a, const HoatDong &b) {
    if (a.s != b.s) return a.s < b.s;
    return a.f < b.f;
}

vector<string> bat_dau_som(vector<HoatDong> ds) {
    sort(ds.begin(), ds.end(), cmp_bat_dau);
    vector<HoatDong> chon;
    for (size_t i = 0; i < ds.size(); i++) {
        bool ok = true;
        for (size_t j = 0; j < chon.size(); j++) {
            if (!tuong_thich(ds[i], chon[j])) {
                ok = false;
                break;
            }
        }
        if (ok) {
            chon.push_back(ds[i]);
        }
    }
    vector<string> res;
    for (size_t i = 0; i < chon.size(); i++) {
        res.push_back(chon[i].id);
    }
    return res;
}

bool cmp_ngan_nhat(const HoatDong &a, const HoatDong &b) {
    int len_a = a.f - a.s;
    int len_b = b.f - b.s;
    if (len_a != len_b) return len_a < len_b;
    return a.f < b.f;
}

vector<string> ngan_nhat(vector<HoatDong> ds) {
    sort(ds.begin(), ds.end(), cmp_ngan_nhat);
    vector<HoatDong> chon;
    for (size_t i = 0; i < ds.size(); i++) {
        bool ok = true;
        for (size_t j = 0; j < chon.size(); j++) {
            if (!tuong_thich(ds[i], chon[j])) {
                ok = false;
                break;
            }
        }
        if (ok) {
            chon.push_back(ds[i]);
        }
    }
    vector<string> res;
    for (size_t i = 0; i < chon.size(); i++) {
        res.push_back(chon[i].id);
    }
    return res;
}

int dem_xung_dot(const HoatDong &target, const vector<HoatDong> &tap) {
    int cnt = 0;
    for (size_t i = 0; i < tap.size(); i++) {
        if (tap[i].id != target.id && !tuong_thich(target, tap[i])) {
            cnt++;
        }
    }
    return cnt;
}

vector<string> it_chong_lan(vector<HoatDong> ds) {
    vector<HoatDong> con_lai = ds;
    vector<string> chon;
    while (!con_lai.empty()) {
        int best_idx = 0;
        int min_cnt = dem_xung_dot(con_lai[0], con_lai);
        for (size_t i = 1; i < con_lai.size(); i++) {
            int cur_cnt = dem_xung_dot(con_lai[i], con_lai);
            if (cur_cnt < min_cnt || (cur_cnt == min_cnt && con_lai[i].f < con_lai[best_idx].f)) {
                min_cnt = cur_cnt;
                best_idx = i;
            }
        }
        HoatDong best = con_lai[best_idx];
        chon.push_back(best.id);

        vector<HoatDong> tiep_theo;
        for (size_t i = 0; i < con_lai.size(); i++) {
            if (con_lai[i].id != best.id && tuong_thich(best, con_lai[i])) {
                tiep_theo.push_back(con_lai[i]);
            }
        }
        con_lai = tiep_theo;
    }
    return chon;
}

vector<string> kiem_chung_toi_uu(const vector<HoatDong> &ds) {
    int n = (int)ds.size();
    vector<string> best;
    int max_mask = 1 << n;
    for (int mask = 1; mask < max_mask; mask++) {
        vector<HoatDong> sub;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                sub.push_back(ds[i]);
            }
        }
        bool ok = true;
        for (size_t i = 0; i < sub.size(); i++) {
            for (size_t j = i + 1; j < sub.size(); j++) {
                if (!tuong_thich(sub[i], sub[j])) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok && sub.size() > best.size()) {
            best.clear();
            for (size_t i = 0; i < sub.size(); i++) {
                best.push_back(sub[i].id);
            }
        }
    }
    return best;
}

void in_kq(const string &ten, const vector<string> &ds, size_t opt_sz) {
    cout << ten << ": {";
    for (size_t i = 0; i < ds.size(); i++) {
        cout << ds[i] << (i + 1 < ds.size() ? ", " : "");
    }
    cout << "} (So luong: " << ds.size() << ") -> " << (ds.size() == opt_sz ? "CO" : "KHONG") << endl;
}

int main() {
    vector<HoatDong> ds;
    ds.push_back(HoatDong("H1", 1, 5));
    ds.push_back(HoatDong("H2", 2, 5));
    ds.push_back(HoatDong("H3", 2, 6));
    ds.push_back(HoatDong("H4", 3, 4));
    ds.push_back(HoatDong("H5", 4, 8));
    ds.push_back(HoatDong("H6", 6, 9));
    ds.push_back(HoatDong("H7", 8, 11));
    ds.push_back(HoatDong("H8", 9, 14));
    ds.push_back(HoatDong("H9", 11, 13));
    ds.push_back(HoatDong("H10", 12, 15));

    vector<string> c1 = ket_thuc_som(ds);
    vector<string> c2 = bat_dau_som(ds);
    vector<string> c3 = ngan_nhat(ds);
    vector<string> c4 = it_chong_lan(ds);
    vector<string> opt = kiem_chung_toi_uu(ds);

    cout << "=== KET QUA CHON HOAT DONG (C++) ===" << endl;
    in_kq("Ket thuc som nhat     ", c1, opt.size());
    in_kq("Bat dau som nhat      ", c2, opt.size());
    in_kq("Ngan nhat             ", c3, opt.size());
    in_kq("It chong lan nhat     ", c4, opt.size());
    in_kq("So nhieu nhat (Toi uu)", opt, opt.size());

    return 0;
}