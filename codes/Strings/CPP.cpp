/* Find P em S O(nm) */
int main()
{
    string S = "bananada", P = "ana";

    auto x = S.find(P);         // x = 1

    x = S.find(P, 2);           // x = 3
    x = S.find(P, 4);           // x = npos

    x = S.rfind(P);             // x = 3

    return 0;
}

/* Find first and last em S O(nm) */
int main()
{
    string S { "exemplo" }, P { "abcde" }, Q { "xyz" };

    auto x = S.find_first_of(P);        // x = 0
    x = S.find_first_not_of(P);         // x = 1
    x = S.find_last_of(P);              // x = 2
    x = S.find_last_not_of(P);          // x = 6

    auto y = S.find_first_of(Q);        // y = 1
    y = S.find_first_not_of(Q);         // y = 0
    y = S.find_last_of(Q);              // y = 1
    y = S.find_last_not_of(Q);          // y = 6

    return 0;
}

/* função search() O(n+m) */
auto it = search(S.begin(), S.end(), P.begin(), P.end());
