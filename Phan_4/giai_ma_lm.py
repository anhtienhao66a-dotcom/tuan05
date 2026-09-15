import itertools
import sys

sys.stdout.reconfigure(encoding='utf-8')

def liet_ke_cau(lm):
    danh_sach = []
    for w2, p2 in lm["em"].items():
        for w3, p3 in lm[w2].items():
            cau = f"em {w2} {w3}"
            diem = p2 * p3
            danh_sach.append((cau, diem))
    danh_sach.sort(key=lambda x: x[1], reverse=True)
    return danh_sach

def giai_ma_tham_lam(lm):
    w1 = "em"
    w2 = max(lm[w1].items(), key=lambda x: x[1])
    w3 = max(lm[w2[0]].items(), key=lambda x: x[1])
    cau = f"em {w2[0]} {w3[0]}"
    diem = w2[1] * w3[1]
    return cau, diem

def beam_search(lm, k):
    beam = [(["em"], 1.0)]
    for step in range(2):
        candidates = []
        for seq, score in beam:
            last = seq[-1]
            for nxt, p in lm[last].items():
                candidates.append((seq + [nxt], score * p))
        candidates.sort(key=lambda x: x[1], reverse=True)
        beam = candidates[:k]
    best_seq, best_score = beam[0]
    return " ".join(best_seq), best_score

def viterbi(words, states, pi, A, B):
    T = len(words)
    f = [{} for _ in range(T)]
    backpointer = [{} for _ in range(T)]

    for s in states:
        f[0][s] = pi[s] * B[s][words[0]]
        backpointer[0][s] = "-"

    for t in range(1, T):
        for s in states:
            best_prob = -1.0
            best_prev = "-"
            for prev_s in states:
                prob = f[t - 1][prev_s] * A[prev_s][s] * B[s][words[t]]
                if prob > best_prob:
                    best_prob = prob
                    best_prev = prev_s
            f[t][s] = best_prob
            backpointer[t][s] = best_prev

    best_last_state = max(states, key=lambda s: f[T - 1][s])
    best_prob = f[T - 1][best_last_state]
    opt_seq = [best_last_state]
    for t in range(T - 1, 0, -1):
        opt_seq.append(backpointer[t][opt_seq[-1]])
    opt_seq.reverse()

    return f, backpointer, " ".join(opt_seq), best_prob

def vet_can_nhan(words, states, pi, A, B):
    best_seq = None
    best_prob = -1.0
    for seq in itertools.product(states, repeat=len(words)):
        prob = pi[seq[0]] * B[seq[0]][words[0]]
        for t in range(1, len(words)):
            prob *= A[seq[t - 1]][seq[t]] * B[seq[t]][words[t]]
        if prob > best_prob:
            best_prob = prob
            best_seq = seq
    return " ".join(best_seq), best_prob

if __name__ == "__main__":
    lm = {
        "em": {"học": 0.52, "đi": 0.48},
        "học": {"bài": 0.40, "toán": 0.35, "vẽ": 0.25},
        "đi": {"chợ": 0.58, "bơi": 0.22, "ngủ": 0.20}
    }

    print("=== BANG 4.3. BA THUAT TOAN GIAI MA (PYTHON) ===")
    ds_cau = liet_ke_cau(lm)
    cau_best, diem_best = ds_cau[0]
    print(f"Liet ke (tot nhat):     {cau_best:<15} | Diem = {diem_best:.6f} | CO")

    tl_cau, tl_diem = giai_ma_tham_lam(lm)
    print(f"Giai ma tham lam:      {tl_cau:<15} | Diem = {tl_diem:.6f} | {'CO' if tl_cau == cau_best else 'KHONG'}")

    for k in [1, 2, 3]:
        bm_cau, bm_diem = beam_search(lm, k)
        print(f"Beam search (k = {k}):     {bm_cau:<15} | Diem = {bm_diem:.6f} | {'CO' if bm_cau == cau_best else 'KHONG'}")

    words = ["em", "học", "bài", "toán"]
    states = ["N", "V"]
    pi = {"N": 0.6, "V": 0.4}
    A = {"N": {"N": 0.35, "V": 0.65}, "V": {"N": 0.70, "V": 0.30}}
    B = {
        "N": {"em": 0.35, "học": 0.10, "bài": 0.40, "toán": 0.30},
        "V": {"em": 0.05, "học": 0.45, "bài": 0.05, "toán": 0.02}
    }

    f, bp, vit_seq, vit_prob = viterbi(words, states, pi, A, B)
    vc_seq, vc_prob = vet_can_nhan(words, states, pi, A, B)

    print(f"Viterbi (gan nhan):    {vit_seq:<15} | Xac suat = {vit_prob:.6f} | CO")
    print(f"Vet can kiem chung:    {vc_seq:<15} | Xac suat = {vc_prob:.6f} | CO")

    print("\n=== BANG 4.4. LUOI VITERBI (PYTHON) ===")
    print(f"{'i':<3}{'Tu':<8}{'f[i][N]':<12}{'f[i][V]':<12}{'Prev_N':<10}{'Prev_V':<10}")
    for t in range(len(words)):
        print(f"{t+1:<3}{words[t]:<8}{f[t]['N']:<12.6f}{f[t]['V']:<12.6f}{bp[t]['N']:<10}{bp[t]['V']:<10}")