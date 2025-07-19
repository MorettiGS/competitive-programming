/* Construcao de anagramas */
bool is_anagram(const std::string& s, const std::string& t)
{
    std::string a(s), b(t);

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    return a == b;
}


/* Construcao de histogramas */
map<char, int> histogram(const std::string& s)
{
    std::map<char, int> h;

    for (auto c : s)
        ++h[c];

    return h;
}


/* Tokenizacao */
int main() {
    std::istringstream is("123.456.789-10");
    std::string token;

    getline(is, token, '.');
    std::cout << token << '\n';      // token = "123";

    getline(is, token, '.');
    std::cout << token << '\n';      // token = "456";

    getline(is, token, '-');
    std::cout << token << '\n';      // token = "789";

    getline(is, token);
    std::cout << token << '\n';      // token = "10";

    return 0;
}


