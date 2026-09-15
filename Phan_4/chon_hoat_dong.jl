# Quy uoc: Trong Julia mang danh chi so bat dau tu 1

struct HoatDong
    id::String
    s::Int
    f::Int
end

tuong_thich(a::HoatDong, b::HoatDong) = (a.f <= b.s || b.f <= a.s)

function ket_thuc_som(ds)
    # Sap xep theo f tang dan
    ds_sorted = sort(ds, by = x -> (x.f, x.s))
    chon = String[]
    cur_f = 0
    for h in ds_sorted
        if h.s >= cur_f
            push!(chon, h.id)
            cur_f = h.f
        end
    end
    return chon
end

function bat_dau_som(ds)
    # Sap xep theo s tang dan
    ds_sorted = sort(ds, by = x -> (x.s, x.f))
    chon = HoatDong[]
    for h in ds_sorted
        if all(tuong_thich(h, c) for c in chon)
            push!(chon, h)
        end
    end
    return [h.id for h in chon]
end

function ngan_nhat(ds)
    # Sap xep theo thoi luong (f - s) tang dan
    ds_sorted = sort(ds, by = x -> (x.f - x.s, x.f))
    chon = HoatDong[]
    for h in ds_sorted
        if all(tuong_thich(h, c) for c in chon)
            push!(chon, h)
        end
    end
    return [h.id for h in chon]
end

function it_chong_lan(ds)
    # Chon hoat dong it xung dot nhat voi cac hoat dong con lai
    con_lai = copy(ds)
    chon = String[]
    while !isempty(con_lai)
        dem_xung_dot(target) = count(h -> h.id != target.id && !tuong_thich(target, h), con_lai)
        sort!(con_lai, by = x -> (dem_xung_dot(x), x.f))
        best = con_lai[1]
        push!(chon, best.id)
        filter!(h -> h.id != best.id && tuong_thich(best, h), con_lai)
    end
    return chon
end

# Kiem chung doc lap: Vet can moi tap con tu lon xuong nho
function kiem_chung_toi_uu(ds)
    n = length(ds)
    best = String[]
    for mask in 1:(1 << n) - 1
        sub = [ds[i] for i in 1:n if (mask & (1 << (i - 1))) != 0]
        ok = true
        for i in 1:length(sub)
            for j in (i + 1):length(sub)
                if !tuong_thich(sub[i], sub[j])
                    ok = false
                    break
                end
            end
            !ok && break
        end
        if ok && length(sub) > length(best)
            best = [h.id for h in sub]
        end
    end
    return best
end

ds = [
    HoatDong("H1", 1, 5), HoatDong("H2", 2, 5), HoatDong("H3", 2, 6), HoatDong("H4", 3, 4), HoatDong("H5", 4, 8),
    HoatDong("H6", 6, 9), HoatDong("H7", 8, 11), HoatDong("H8", 9, 14), HoatDong("H9", 11, 13), HoatDong("H10", 12, 15)
]

c1 = ket_thuc_som(ds)
c2 = bat_dau_som(ds)
c3 = ngan_nhat(ds)
c4 = it_chong_lan(ds)
opt = kiem_chung_toi_uu(ds)

println("=== KET QUA CHON HOAT DONG (JULIA) ===")
println("Ket thuc som nhat:       {", join(c1, ", "), "} (So luong: $(length(c1))) -> $(length(c1) == length(opt) ? "CO" : "KHONG")")
println("Bat dau som nhat:        {", join(c2, ", "), "} (So luong: $(length(c2))) -> $(length(c2) == length(opt) ? "CO" : "KHONG")")
println("Ngan nhat:               {", join(c3, ", "), "} (So luong: $(length(c3))) -> $(length(c3) == length(opt) ? "CO" : "KHONG")")
println("It chong lan nhat:       {", join(c4, ", "), "} (So luong: $(length(c4))) -> $(length(c4) == length(opt) ? "CO" : "KHONG")")
println("So nhieu nhat (Toi uu):  {", join(opt, ", "), "} (So luong: $(length(opt))) -> CO")