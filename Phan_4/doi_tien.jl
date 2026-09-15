function doi_tien_tham_lam(menh_gia, S)
    mg = sort(menh_gia, rev = true)
    con = S
    so_to = 0
    kq = Dict{Int, Int}()
    for m in mg
        if con >= m
            cnt = div(con, m)
            so_to += cnt
            kq[m] = cnt
            con %= m
        end
    end
    cach = join(["$(kq[m])x$m" for m in sort(collect(keys(kq)), rev=true)], " + ")
    return so_to, cach
end

function doi_tien_qhd(menh_gia, S)
    f = fill(typemax(Int) - 1, S + 1)
    vet = fill(-1, S + 1)
    f[1] = 0 
    for j in 1:S, m in menh_gia
        if m <= j && f[j - m + 1] + 1 < f[j + 1]
            f[j + 1] = f[j - m + 1] + 1
            vet[j + 1] = m
        end
    end
    kq = Dict{Int, Int}()
    cur = S
    while cur > 0
        m = vet[cur + 1]
        kq[m] = get(kq, m, 0) + 1
        cur -= m
    end
    cach = join(["$(kq[m])x$m" for m in sort(collect(keys(kq)), rev=true)], " + ")
    return f[S + 1], cach
end

bo_tien = [
    (1, [1, 4, 6, 9], 12),
    (2, [1, 5, 10, 20, 50], 85),
    (3, [1, 3, 7, 12], 20),
    (4, [1, 2, 5, 10], 38),
    (5, [1, 6, 10], 12),
    (6, [1, 4, 5, 15, 20], 23)
]

for (stt, mg, S) in bo_tien
    tl_to, tl_cach = doi_tien_tham_lam(mg, S)
    qh_to, qh_cach = doi_tien_qhd(mg, S)
    dung = (tl_to == qh_to) ? "Dung" : "Sai"
    println("Bo $stt (S=$S): Tham lam = $tl_to to ($tl_cach) | Toi uu = $qh_to to ($qh_cach) => $dung")
end