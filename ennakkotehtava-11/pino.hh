#ifndef PINO_HH
#define PINO_HH


class Pino
{
public:
    Pino();
    ~Pino();

    bool empty() const;
    void push_front(int lisattava_arvo);
    bool pop_front(int& poistettu_arvo);

    void print() const;
    int koko() const;
    void takaperin();
    int& top();
private:
    int* alkiot;
    int* ensimmainen_osoite_;
    int koko_;
};

#endif // PINO_HH
