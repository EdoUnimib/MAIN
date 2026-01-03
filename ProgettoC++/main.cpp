#include <iostream>
#include <cassert>
#include "set.hpp"
#include <stdexcept>

struct IsEven{
    bool operator()(int x) const{
        return x % 2 == 0;
    }
};

struct IsOdd{
    bool operator()(int x) const{
        return !(x % 2 == 0);
    }
};
/* ============================
   TEST COSTRUTTORE DEFAULT
   ============================ */

void test_constructor(){
    std::cout << "[TEST CONSTRUCTOR] Costruttore di default" << std::endl;

    set<int> s;
    std::cout << "Verifica il set appena creato" << std::endl;
    std::cout << "  size: " << s.size() << " (expected 0)" << std::endl;

    assert(s.size() == 0);

    std::cout << "  >>> [END] Costruttore di default OK" << std::endl << std::endl;

}

/* ============================
   TEST ADD / CONTAINS / SIZE
   ============================ */

void test_add_contains(){
    std::cout << "[TEST ADD] add / contains / size" << std::endl;

    set<int> s;
    s.add(10);
    s.add(20);
    s.add(10);

    std::cout << "  Inseriti: 10, 20, 10 (duplicato)" << std::endl;
    std::cout << "  size: " << s.size() << " (expected 2)" << std::endl;
    std::cout << "  contains(10): " << s.contains(10) << " (expected 1)" << std::endl;
    std::cout << "  contains(30): " << s.contains(30) << " (expected 0)" << std::endl;
    std::cout << "  set" << s << std::endl;

    assert(s.size() == 2);
    assert(s.contains(20));
    assert(!s.contains(30));

    std::cout << "  >>> [END] add / contains / size OK" << std::endl << std::endl;
}

/* ============================
   TEST REMOVE
   ============================ */

void test_remove(){
    std::cout << "[TEST REMOVE] remove" << std::endl;

    set<int> s;
    s.add(1);
    s.add(2);
    s.add(3);

    std::cout << "  Set iniziale: " << s << std::endl;

    s.remove(2);
    std::cout << "  Rimosso 2 -> set: " << s << std::endl;
    std::cout << "   size: " << s.size() << " (expected 2)" << std::endl;

    assert(!s.contains(2));
    assert(s.size() == 2);

    s.remove(5);
    std::cout << "  Tentata rimozione elemento non presente (5)" << std::endl;
    std::cout << "   size invariata : " << s.size() << std::endl;

    assert(s.size() == 2);

    std::cout << "  >>> [END] remove OK" << std::endl << std::endl;
}

/* ============================
   TEST OPERATOR[]
   ============================ */

void test_operatore_di_accesso(){
    std::cout << "[TEST OPERATORE DI ACCESSO] operator[]" << std::endl;

    set<int> s;
    s.add(5);
    s.add(10);

    std::cout << "  Set: " << s << std::endl;
    std::cout << "  s[0]: " << s[0] << std::endl;
    std::cout << "  s[1]: " << s[1] << std::endl;

    try{
        std::cout << "  Accesso fuori dal range s[10]" << std::endl;
        std::cout << s[10] << std::endl;
        assert(false);
    }catch(const std::out_of_range& e){
        std::cout << "  [EXCEPTION] out_of_range catturata correttamente" << std::endl;
    }

    std::cout << "  >>> [END] operator[] OK" << std::endl << std::endl;
}

/* ============================
   TEST COPY CONSTRUCTOR
   ============================ */

void test_copy_constructor(){
    std::cout << "[TEST CONSTRUCTOR] Copy constructor" << std::endl;

    set<int> s1;
    s1.add(7);
    s1.add(9);

    std::cout << "  Set originale: " << s1 << std::endl;

    set<int> s2(s1);
    std::cout << "  Set copiato:   " << s2 << std::endl;

    assert(s1 == s2);

    std::cout << "  >>> [END] Copy constructor OK" << std::endl << std::endl;
}

/* ============================
   TEST OPERATOR=
   ============================ */

void test_operatore_assegnamento(){
    std::cout << "[TEST ASSEGNAMENTO] operator=" << std::endl;

    set<int> s1;
    s1.add(7);
    s1.add(9);

    set<int> s2(s1);

    std::cout << "  s1: " << s1 << std::endl;
    std::cout << "  s2: " << s2 << std::endl;

    assert(s1 == s2);

    std::cout << "  >>> [END] operator= OK" << std::endl << std::endl;
}

/* ============================
   TEST OPERATOR==
   ============================ */

void test_uguaglianza(){
    std::cout << "[TEST BOOL] operator==" << std::endl;

    set<int> a, b;
    a.add(1); a.add(2);
    b.add(2); b.add(1);

    std::cout << "  a: " << a << std::endl;
    std::cout << "  b: " << b << std::endl;
    std::cout << "   a == b ? " << (a == b) << " (expected 1)" << std::endl;

    assert(a == b);

    b.add(3);
    std::cout << "  Aggiunto 3 a b -> b: " << b << std::endl;
    std::cout << "  a == b ? " << (a == b) << " (expected 0)" << std::endl;

    assert(!(a == b));

    std::cout << "  >>> [END] operator== OK" << std::endl << std::endl;

}

/* ============================
   TEST CLEAR
   ============================ */

void test_clear(){
    std::cout << "[TEST CLEAR] clear()" << std::endl;

    set<int> s;
    s.add(1);
    s.add(2);

    std::cout << "  Prima del clear: " << s << std::endl;

    s.clear();

    std::cout << "  Dopo il clear: " << s << std::endl;
    std::cout << "   size: " << s.size() << " (expected 0)" << std::endl;

    assert(s.size() == 0);

    std::cout << "  >>>[END] clear OK" << std::endl << std::endl;

}

/* ============================
   TEST ITERATOR BASE
   ============================ */

void test_iteratore_base(){
    std::cout << "[TEST ITERATORE] base" << std::endl;

    set<int> s;
    s.add(10);
    s.add(20);
    s.add(30);

    std::cout << "  set: " << s << std::endl;

    set<int>::iterator it = s.begin();
    set<int>::iterator it_end = s.end();

    int c = 0;
    while(it != it_end){
        std::cout << "  valore: " << *it << std::endl;
        ++it;
        ++c;
    }

    assert(c == s.size());

    std::cout << "  >>>[OK] iteratore base" << std::endl << std::endl;

}

/* ============================
   TEST PRE / POST INCREMENTO
   ============================ */

void test_iteratore_incremento(){
    std::cout << "[TEST ITERATORE] ++it / it++" << std::endl;

    set<int> s;
    s.add(1);
    s.add(2);

    std::cout << "  set: " << s << std::endl;

    set<int>::iterator it = s.begin();

    int a = *it;
    it++; //vale lo stesso per ++it
    int b = *it;

    assert(a != b);

    std::cout << "  a: " << a << std::endl;
    std::cout << "  b: " << b << std::endl;

    std::cout << "  >>> [OK] incremento iteratore" << std::endl << std::endl;
}

/* ============================
   TEST CONST_ITERATOR
   ============================ */

void test_const_iterator(){
    std::cout << "[TEST CONST_ITERATOR]" << std::endl;

    set<int> s;
    s.add(5);
    s.add(6);

    std::cout << "  set: " << s << std::endl;

    const set<int>& const_s = s;

    set<int>::const_iterator it = const_s.begin();
    set<int>::const_iterator it_end = const_s.end();

    int c = 0;
    while(it != it_end){
        std::cout << "  valore const: " << *it << std::endl;
        ++it;
        ++c;
    }

    assert(c == const_s.size());

    std::cout << "  >>> [OK] const_iterator" << std::endl << std::endl;

}

/* ============================
   TEST CONFRONTO ITERATOR /
   CONST_ITERATOR
   ============================ */

void test_iterator_confronto(){
    std::cout << "[TEST ITERATOR VS CONST_ITERATOR]" << std::endl;

    set<int> s;
    s.add(100);
    s.add(200);

    set<int>::iterator it = s.begin();
    set<int>::const_iterator c_it = s.begin();

    assert(it == c_it);
    ++it;
    assert(it != c_it);

    std::cout << "  >>> [OK] confronto iterator / const_iterator" << std::endl << std::endl;
}

/* ============================
   TEST OPERATOR+
   ============================ */

void test_operator_unione(){
    std::cout << "[TEST OPERATOR+]" << std::endl;

    set<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);

    set<int> s2;
    s2.add(3);
    s2.add(4);
    s2.add(5);

    std::cout << "  set 1: " << s1 << std::endl;
    std::cout << "  set 2: " << s2 << std::endl;

    set<int> s3 = s1 + s2;

    std::cout << "  s3 = s1 + s2 =  " << s3 << std::endl;

    assert(s3.size() ==  5);
    assert(s3.contains(1));
    assert(s3.contains(2));
    assert(s3.contains(3));
    assert(s3.contains(4));
    assert(s3.contains(5));

    std::cout << "  >>> [OK] operator+" << std::endl << std::endl;
}

/* ============================
   TEST OPERATOR- (INTERSEZIONE)
   ============================ */

void test_operator_intersezione(){
    std::cout << "[TEST OPERATOR- (intersezione)]" << std::endl;

    set<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);
    s1.add(4);

    std::cout << "  set 1: " << s1 << std::endl;

    set<int> s2;
    s2.add(3);
    s2.add(4);
    s2.add(5);

    std::cout << "  set 2: " << s2 << std::endl;

    set<int> s3 = s1 - s2;

    std::cout << "  set 3 = s1 - s2 = " << s3 << std::endl;

    assert(s3.size() == 2);
    assert(s3.contains(3));
    assert(s3.contains(4));

    std::cout << "  >>> [OK] operator-" << std::endl << std::endl;
}

/* ============================
   TEST COSTRUTTORE DA ITERATORI
   ============================ */

void test_iterator_constructor(){
    std::cout << "[TEST COSTRUTTORE DA ITERATORI]" << std::endl;

    int a[] = {1, 2, 3, 4, 4};
    set<int> s(a, a+5);

    std::cout << "  s = " << s << std::endl;

    assert(s.size() == 4);
    assert(s.contains(1));
    assert(s.contains(1));
    assert(s.contains(3));
    assert(s.contains(4));

    std::cout << "  >>> [OK] costruttore da iteratori" << std::endl << std::endl;
}

/* ============================
   TEST FILTER 
   ============================ */

void test_filter_out(){
    std::cout << "[TEST filter_out]" << std::endl;

    set<int> s;
    s.add(1);
    s.add(2);
    s.add(3);
    s.add(4);

    std::cout << "  s = " << s << std::endl;

    set<int> pari = filter_out(s, IsEven());
    std::cout << "  s (predicato pari) = " << pari << std::endl;
    set<int> dispari = filter_out(s, IsOdd());
    std::cout << "  s (predicato dispari) = " << dispari << std::endl;

    assert(pari.size() == 2);
    assert(pari.contains(2));
    assert(pari.contains(4));

    assert(dispari.size() == 2);
    assert(dispari.contains(1));
    assert(dispari.contains(3));



    std::cout << "  >>> [OK] filter_out" << std::endl << std::endl;

    
}




int main() {

    std::cout << std::endl;
    std::cout << "[NOTA] Per ogni test viene stampato a schermo i valori che verifica, e successivamente usa 'assert' per verificare a runtime." << std::endl << std::endl;
    test_constructor();

    test_add_contains();

    test_remove();

    test_operatore_di_accesso();

    test_copy_constructor();

    test_operatore_assegnamento();

    test_uguaglianza();

    test_clear();

    test_iteratore_base();

    test_iteratore_incremento();

    test_const_iterator();

    test_iterator_confronto();

    test_operator_unione();

    test_operator_intersezione();

    test_iterator_constructor();

    test_filter_out();



    return 0;
}
