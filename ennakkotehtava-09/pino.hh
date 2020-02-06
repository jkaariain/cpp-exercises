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
private:
    struct Alkio{
        int data;
        Alkio* seuraava_ptr;
    };

    Alkio* ensimmainen_osoite_;
};

#endif // PINO_HH
