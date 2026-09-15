function cai_tui(items, w, v, W)
    n = length(w)
    f = zeros(Int, n + 1, W + 1)

    for i in 1:n
        for j in 0:W
            f[i + 1, j + 1] = f[i, j + 1] 
            if w[i] <= j
                f[i + 1, j + 1] = max(f[i + 1, j + 1], f[i, j - w[i] + 1] + v[i]) 
            end
        end
    end

    println("=== BANG f ===")
    print("f[i][j]\t")
    for j in 0:W
        print(j, "\t")
    end
    println()

    for i in 0:n
        if i == 0
            print("i=0\t")
        else
            print("i=", i, " (", items[i], ")\t")
        end
        for j in 0:W
            print(f[i + 1, j + 1], "\t")
        end
        println()
    end

    chon = String[]
    j = W
    for i in n:-1:1
        if f[i + 1, j + 1] != f[i, j + 1] 
            push!(chon, items[i])
            j -= w[i]
        end
    end
    reverse!(chon)

    println("\nGia tri lon nhat: ", f[n + 1, W + 1])
    println("Tap do vat duoc chon: ", chon)
end
items = ["A", "B", "C", "D", "E"]
w = [2, 3, 4, 5, 7]
v = [3, 7, 9, 12, 16]
W = 11

cai_tui(items, w, v, W)