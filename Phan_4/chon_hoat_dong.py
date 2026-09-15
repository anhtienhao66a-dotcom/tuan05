def tuong_thich(h1, h2):
    return h1[2] <= h2[1] or h2[2] <= h1[1]

def tieu_chi_ket_thuc_som(hd):
    ds = sorted(hd, key=lambda x: (x[2], x[1]))
    chon = []
    cur_f = 0
    for h in ds:
        if h[1] >= cur_f:
            chon.append(h[0])
            cur_f = h[2]
    return chon

def tieu_chi_bat_dau_som(hd):
    ds = sorted(hd, key=lambda x: (x[1], x[2]))
    chon = []
    for h in ds:
        if all(tuong_thich(h, next(x for x in hd if x[0] == cid)) for cid in chon):
            chon.append(h[0])
    return chon

def tieu_chi_ngan_nhat(hd):
    ds = sorted(hd, key=lambda x: (x[2] - x[1], x[2]))
    chon = []
    for h in ds:
        if all(tuong_thich(h, next(x for x in hd if x[0] == cid)) for cid in chon):
            chon.append(h[0])
    return chon

def tieu_chi_it_chong_lan_nhat(hd):
    def dem_xung_dot(target, tap):
        return sum(1 for h in tap if h[0] != target[0] and not tuong_thich(target, h))
    
    con_lai = list(hd)
    chon = []
    while con_lai:
        best = min(con_lai, key=lambda x: (dem_xung_dot(x, con_lai), x[2]))
        chon.append(best[0])
        con_lai = [h for h in con_lai if h[0] != best[0] and tuong_thich(best, h)]
    return chon

def kiem_chung_toi_uu(hd):
    import itertools
    for k in range(len(hd), 0, -1):
        for comb in itertools.combinations(hd, k):
            ok = True
            for i in range(len(comb)):
                for j in range(i + 1, len(comb)):
                    if not tuong_thich(comb[i], comb[j]):
                        ok = False
                        break
                if not ok:
                    break
            if ok:
                return [h[0] for h in comb]
    return []

if __name__ == "__main__":
    hd = [
        ("H1", 1, 5), ("H2", 2, 5), ("H3", 2, 6), ("H4", 3, 4), ("H5", 4, 8),
        ("H6", 6, 9), ("H7", 8, 11), ("H8", 9, 14), ("H9", 11, 13), ("H10", 12, 15)
    ]

    c1 = tieu_chi_ket_thuc_som(hd)
    c2 = tieu_chi_bat_dau_som(hd)
    c3 = tieu_chi_ngan_nhat(hd)
    c4 = tieu_chi_it_chong_lan_nhat(hd)
    opt = kiem_chung_toi_uu(hd)

    print("=== KET QUA CHON HOAT DONG (PYTHON) ===")
    print(f"Ket thuc som nhat:       {{{', '.join(c1)}}} (So luong: {len(c1)}) -> {'CO' if len(c1)==len(opt) else 'KHONG'}")
    print(f"Bat dau som nhat:        {{{', '.join(c2)}}} (So luong: {len(c2)}) -> {'CO' if len(c2)==len(opt) else 'KHONG'}")
    print(f"Ngan nhat:               {{{', '.join(c3)}}} (So luong: {len(c3)}) -> {'CO' if len(c3)==len(opt) else 'KHONG'}")
    print(f"It chong lan nhat:       {{{', '.join(c4)}}} (So luong: {len(c4)}) -> {'CO' if len(c4)==len(opt) else 'KHONG'}")
    print(f"So nhieu nhat (Toi uu):  {{{', '.join(opt)}}} (So luong: {len(opt)}) -> CO")