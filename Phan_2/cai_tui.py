def cai_tui(items, w, v, W):
    n = len(w)
    f = [[0] * (W + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(W + 1):
            f[i][j] = f[i - 1][j]  
            if w[i - 1] <= j:     
                f[i][j] = max(f[i][j], f[i - 1][j - w[i - 1]] + v[i - 1])

    print("=== BANG f ===")
    print("f[i][j]\t" + "\t".join(str(j) for j in range(W + 1)))
    for i in range(n + 1):
        label = f"i={i}" + (f" ({items[i - 1]})" if i > 0 else "")
        print(label + "\t" + "\t".join(str(f[i][j]) for j in range(W + 1)))

    chon = []
    j = W
    for i in range(n, 0, -1):
        if f[i][j] != f[i - 1][j]:  
            chon.append(items[i - 1])
            j -= w[i - 1]
    chon.reverse()

    print(f"\nGia tri lon nhat: {f[n][W]}")
    print(f"Tap do vat duoc chon: {chon}")
    return f[n][W], chon

if __name__ == "__main__":
    items = ["A", "B", "C", "D", "E"]
    w = [2, 3, 4, 5, 7]
    v = [3, 7, 9, 12, 16]
    W = 11

    cai_tui(items, w, v, W)