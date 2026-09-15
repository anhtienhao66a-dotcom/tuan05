def doi_tien_tham_lam(menh_gia, S):
    mg = sorted(menh_gia, reverse=True)
    kq = {}
    con = S
    for m in mg:
        if con >= m:
            kq[m] = con // m
            con %= m
    so_to = sum(kq.values())
    cach_tra = " + ".join(f"{cnt}x{m}" for m, cnt in kq.items())
    return so_to, cach_tra

def doi_tien_qhd(menh_gia, S):
    f = [float('inf')] * (S + 1)
    vet = [-1] * (S + 1)
    f[0] = 0
    for j in range(1, S + 1):
        for m in menh_gia:
            if m <= j and f[j - m] + 1 < f[j]:
                f[j] = f[j - m] + 1
                vet[j] = m
    kq = {}
    cur = S
    while cur > 0:
        m = vet[cur]
        kq[m] = kq.get(m, 0) + 1
        cur -= m
    so_to = f[S]
    cach_tra = " + ".join(f"{cnt}x{m}" for m, cnt in sorted(kq.items(), reverse=True))
    return so_to, cach_tra

if __name__ == "__main__":
    bo_tien = [
        (1, [1, 4, 6, 9], 12),
        (2, [1, 5, 10, 20, 50], 85),
        (3, [1, 3, 7, 12], 20),
        (4, [1, 2, 5, 10], 38),
        (5, [1, 6, 10], 12),
        (6, [1, 4, 5, 15, 20], 23)
    ]
    for stt, mg, S in bo_tien:
        tl_to, tl_cach = doi_tien_tham_lam(mg, S)
        qh_to, qh_cach = doi_tien_qhd(mg, S)
        dung = "Dung" if tl_to == qh_to else "Sai"
        print(f"Bo {stt} (S={S}): Tham lam = {tl_to} to ({tl_cach}) | Toi uu = {qh_to} to ({qh_cach}) => {dung}")