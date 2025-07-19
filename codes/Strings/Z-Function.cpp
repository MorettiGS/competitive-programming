//
// A ideia principal da implementa¸c˜ao ´e o uso dos dois ponteiros L e R.
//
// Para qualquer posicao i (na implementacao a string é indexada de 0 a n - 1), L e R representam o inıcio e o fim de prefixo comum entre S e algum sufixo S[k..(n - 1)], para k < i
//
// Este prefixo deve ser nao nulo, e caso exista mais de um prefixo comum já identificado, deve ser escolhido aquele termina mais à direita possıvel.
//

/* Z-Function */
vector<int> z(const string &s) {
    int n = s.size(), L = 0, R = 0;
    vector<int> zs(n, 0);

    for (int i = 1; i < n; i++) {
        if (i <= R) zs[i] = min(zs[i - L], R - i + 1);

        while (zs[i] + i < n && s[zs[i]] == s[i + zs[i]]) zs[i]++;

        if (R < i + zs[i] - 1) L = i, R = i + zs[i] - 1;
    }
    return zs;
}

/* Busca utilizando z-function */
int search(const string& S, const string& P, char delim = '#') {
    string T { P + delim + S };
    auto zs = z(T);
    int occ = 0, m = P.size();

    for (const auto x : zs) occ += (x == m ? 1 : 0);

    return occ;
}
