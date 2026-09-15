using Printf

lm = Dict(
    "em" => Dict("hoc" => 0.52, "di" => 0.48),
    "hoc" => Dict("bai" => 0.40, "toan" => 0.35, "ve" => 0.25),
    "di" => Dict("cho" => 0.58, "boi" => 0.22, "ngu" => 0.20)
)

ds_cau = Tuple{String, Float64}[]
for (w2, p2) in lm["em"]
    for (w3, p3) in lm[w2]
        push!(ds_cau, ("em $w2 $w3", p2 * p3))
    end
end
sort!(ds_cau, by = x -> x[2], rev = true)

w2_g = argmax(lm["em"])
w3_g = argmax(lm[w2_g])
tl_cau = "em $w2_g $w3_g"
tl_diem = lm["em"][w2_g] * lm[w2_g][w3_g]

function beam_search(lm, k)
    beam = [(["em"], 1.0)]
    for step in 1:2
        candidates = Tuple{Vector{String}, Float64}[]
        for (seq, score) in beam
            last_w = seq[end]
            for (nxt, p) in lm[last_w]
                push!(candidates, (vcat(seq, [nxt]), score * p))
            end
        end
        sort!(candidates, by = x -> x[2], rev = true)
        beam = candidates[1:min(k, length(candidates))]
    end
    return join(beam[1][1], " "), beam[1][2]
end

words = ["em", "hoc", "bai", "toan"]
states = ["N", "V"]
pi = [0.6, 0.4]
A = [0.35 0.65; 0.70 0.30]
B = [
    0.35 0.10 0.40 0.30;
    0.05 0.45 0.05 0.02
]

T = length(words)
f = zeros(Float64, T, 2)
bp = zeros(Int, T, 2)

for s in 1:2
    f[1, s] = pi[s] * B[s, 1]
    bp[1, s] = 0
end

for t in 2:T
    for s in 1:2
        best_p = -1.0
        best_prev = 0
        for prev in 1:2
            prob = f[t - 1, prev] * A[prev, s] * B[s, t]
            if prob > best_p
                best_p = prob
                best_prev = prev
            end
        end
        f[t, s] = best_p
        bp[t, s] = best_prev
    end
end

opt_last = f[T, 1] >= f[T, 2] ? 1 : 2
vit_prob = f[T, opt_last]
opt_path = zeros(Int, T)
opt_path[T] = opt_last
for t in T:-1:2
    opt_path[t - 1] = bp[t, opt_path[t]]
end
vit_seq = join([states[opt_path[t]] for t in 1:T], " ")

println("=== BANG 4.3. BA THUAT TOAN GIAI MA (JULIA) ===")
@printf("Liet ke (tot nhat):     %-15s | Diem = %.6f | CO\n", ds_cau[1][1], ds_cau[1][2])
@printf("Giai ma tham lam:      %-15s | Diem = %.6f | %s\n", tl_cau, tl_diem, tl_cau == ds_cau[1][1] ? "CO" : "KHONG")
for k in 1:3
    bm_c, bm_d = beam_search(lm, k)
    @printf("Beam search (k = %d):    %-15s | Diem = %.6f | %s\n", k, bm_c, bm_d, bm_c == ds_cau[1][1] ? "CO" : "KHONG")
end
@printf("Viterbi (gan nhan):    %-15s | Xac suat = %.6f | CO\n", vit_seq, vit_prob)

println("\n=== BANG 4.4. LUOI VITERBI (JULIA) ===")
println("i  Tu        f[i][N]     f[i][V]     Nhan truoc N  Nhan truoc V")
for t in 1:T
    prev_n = bp[t, 1] == 0 ? "-" : states[bp[t, 1]]
    prev_v = bp[t, 2] == 0 ? "-" : states[bp[t, 2]]
    @printf("%-3d%-10s%-12.6f%-12.6f%-14s%-14s\n", t, words[t], f[t, 1], f[t, 2], prev_n, prev_v)
end