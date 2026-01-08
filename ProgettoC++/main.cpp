/** 
    @file main.cpp
    @brief File di test per la classe template set

    Questo file contiene una serie di test automatici
    per verificare il corretto funzionamento della classe set<T> e
    delle funzionalità associate. I test utilizzano assert per 
    la verifica a runtime. 
*/

#include <iostream>
#include <cassert>
#include "set.hpp"
#include <stdexcept>

/** 
    @brief Predicato che verifica se un intero è pari
*/
struct IsEven{
    bool operator()(int x) const{
        return x % 2 == 0;
    }
};

/** 
    @brief Predicato che verifica se un intero è dispari
*/
struct IsOdd{
    bool operator()(int x) const{
        return !(x % 2 == 0);
    }
};

/* ============================
   TEST COSTRUTTORE DEFAULT
   ============================ */
/** 
    @brief Test del costruttore di default

    Verifica che un set appena creato sia vuoto
*/
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
/** 
    @brief Test delle operazioni add, contains e size

    Verifica che:
    - l'inserimento di elementi funzioni correttamente
    - i duplicati non vengano inseriti
    - contains restituisca il valore corretto
    - size rappresenti il numero corretto di elementi
*/
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

    std::cout << "[TEST] set<string>" << std::endl;
    set<std::string> set_string;
    set_string.add("c++");
    set_string.add("java");
    set_string.add("python");
    set_string.add("c++");

    std::cout << "  set: " << set_string << std::endl;

    std::cout << "   size: " << set_string.size() << " (expected 3)" << std::endl;
    assert(set_string.size() == 3);
    assert(set_string.contains("c++"));
    assert(set_string.contains("java"));
    assert(set_string.contains("python"));
    assert(!set_string.contains("javascript"));

    set_string.remove("java");
    std::cout << "  Rimosso 'java' -> set: " << set_string << std::endl;

    assert(!set_string.contains("java"));
    std::cout << "   size: " << set_string.size() << " (expected 2)" << std::endl;
    assert(set_string.size() == 2);

    std::cout << "  >>> [OK] set<string> " << std::endl << std::endl;
}

/* ============================
   TEST REMOVE
   ============================ */
/** 
    @brief Test della funzione remove

    Verifica la rimozione di elementi presenti, 
    l'assenza di effetti per elementi non presenti 
    e il caso di set con un solo elemento. 
*/
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

    std::cout << "[TEST REMOVE] remove su set con un solo elemento" << std::endl;

    set<int> f;
    f.add(10);
    std::cout << "  Set prima: " << f << std::endl;
    f.remove(10);
    std::cout << "  Set dopo: " << f << std::endl;
    assert(!f.contains(10));
    assert(f.size() == 0);

    std::cout << "  >>> [OK] remove su set con un solo elemento" << std::endl << std::endl;
}

/* ============================
   TEST OPERATOR[]
   ============================ */
/** 
    @brief Test dell'operatore di accesso operator[]

    Verifica che l'operatore di accesso consenta la lettura corretta degli elementi del set
    tramite indice e che venga sollevata un'eccezione std::out_of_range in caso di accesso non valido. 
*/
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
/** 
    @brief Test del costruttore di copia

    Verifica che il costruttore di copia crei un nuovo set con lo stesso contenuto del set originale,
    mantenendo l'indipendenza tra i due oggetti. 
*/
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
/** 
    @brief Test dell'operatore di assegnamento

    Verifica che l'operatore di assegnamento esegua correttamente la copia di un set, 
    producendo due oggetti distinti ma equivalenti nel contenuto. 
*/
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
/** 
    @brief Test dell'operatore di uguaglianza ==

    Verifica che due set siano considerati uguali quando contengono gli stessi elementi, indipendentemente dall'ordine 
    di inserimento, e diversi quando la loro cardinalità o il contenuto differiscono. 
*/
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
/** 
    @brief Test della funzione clear
    
    Verifica che la funzione clear rimuova correttamente tutti gli elementi
    dal set e che la dimensione venga riportata a zero. 
*/
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
/** 
    @brief Test dell'iteratore base

    Verifica che l'iteratore permetta di scorrere correttamente tutti gli elementi del set
*/
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
/** 
    @brief Test di pre e post incremento degli iteratori

    Verifica il corretto funzionamento di ++it e it++.
*/
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
/** 
    @brief Test del const_iterator

    Verifica che il const_iterator consenta
    l'accesso in sola lettura agli elementi. 
*/
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
/** 
    @brief Test del confronto tra iterator e const_iterator

    Verifica che un iterator e un const_iterator possano essere confrontati correttamente 
    tramite gli operatori di uguaglianza e disuguaglianza.

    In particolare, il test controlla che: 
    - iterator e const_iterator che puntano allo stesso elemento risultino uguali
    - dopo l'incremento dell'iterator, il confronto evidenzi correttamente la differenza
*/
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
/** 
    @brief Test dell'operatore di unione +

    Verifica che l'unione tra due set produca un nuovo set contenente tutti gli elementi. 
*/
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
/** 
    @brief Test dell'operatore di intersezione - 

    Verifica che l'intersezione tra due set contenga solo gli elementi comuni.
*/
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
/** 
    @brief Test del costruttore da iteratori

    Verifica la corretta costruzione di un set a partire da una sequenza di iteratori
*/
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
/** 
    @brief Test della funzione filter_out

    Verifica il filtraggio degli elementi del set tramite un predicato passato come parametro.
*/
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

/* ============================
   TEST LOAD / SAVE
   ============================ */
/** 
    @brief Test delle funzioni save e load

    Verifica il salvataggio e il caricamento di un set di Attivita su file inclusi i casi di set vuoto.
*/
void test_load_save(){

    std::cout << "[TEST save / load] tipi custom (attività)" << std::endl;

    std::cout << "[1] Creo un set di Attività s vuoto" << std::endl;
    set<Attivita> s;
    std::cout << "[2] Creo due attività e le inserisco nel set appena creato" << std::endl;
    Attivita attivita1;
    attivita1.titolo = "StudioC++";
    attivita1.ora_inizio = 14;
    attivita1.ora_fine = 17;

    Attivita attivita2;
    attivita2.titolo = "Allenamento";
    attivita2.ora_inizio = 18;
    attivita2.ora_fine = 20;

    s.add(attivita1);
    s.add(attivita2);

    std::cout << "   Attivita inserite nel set: " << std::endl;
    std::cout << "   - " << attivita1 << std::endl;
    std::cout << "   - " << attivita2 << std::endl << std::endl;

    std::cout << "[3] Salvo il contenuto del set su file (attivita_set.txt)" << std::endl;
    save(s, "attivita_set.txt");
    std::cout << "    Salvataggio completato" << std::endl << std::endl;

    std::cout << "[4] Creo un nuovo set vuoto s2 e carico i dati dal file" << std::endl;
    set<Attivita> s2;
    load("attivita_set.txt", s2);
    std::cout << "    Caricamento completato" << std::endl << std::endl;

    std::cout << "Set s: " << s << std::endl;
    std::cout << "Set s2: " << s2 << std::endl << std::endl; 

    std::cout << "[5] Verifico che i due set siano uguali" << std::endl;
    assert(s == s2);
    std::cout << "    I due set coincidono" << std::endl << std::endl;

    std::cout << "[6] Inserisco una attivita fittizia in s2" << std::endl;
    Attivita f;
    f.titolo = "prova";
    f.ora_inizio = 12;
    f.ora_fine = 14;
    s2.add(f);

    std::cout << "[7] Verifico che i due set siano diversi dopo l'inserimento dell'attività fittizia" << std::endl;
    assert(!(s==s2));
    std::cout << "Set s: " << s << std::endl;
    std::cout << "Set s2: " << s2 << std::endl << std::endl; 
    std::cout << "    [OK] I due set non coincidono" << std::endl << std::endl;

    std::cout << "[8] Ricarico dal file, gli eventuali dati già presenti nel set vengono rimossi e sostituiti" << std::endl;
    load("attivita_set.txt", s2);
    std::cout << "    Caricamento completato" << std::endl << std::endl;

    std::cout << "[9] Verifico che i due set DOPO il load coincidano di nuovo " << std::endl;
    assert(s==s2);
    std::cout << "    [OK] Coincidono" << std::endl << std::endl;

    std::cout << "[TEST save / load] con set vuoto" << std::endl;

    set<Attivita> g;
    save(g, "vuoto.txt");
    std::cout << "Salvo set vuoto: " << g << std::endl;

    set<Attivita> g2;
    load("vuoto.txt", g2);
    std::cout << "Carico set vuoto: " << g2 << std::endl;
    
    assert(g2.size() == 0);

    std::cout << "  >>> [OK] save / load con set vuoto" << std::endl << std::endl;
}

/* ============================
   TEST TIPO CUSTOM ATTIVITA
   ============================ */
/** 
    @brief Test dell'utilizzo di un tipo custom Attivita

    Verifica che il set funzioni correttamente con tipi definiti dall'utente
*/
void test_tipo_custom(){

    std::cout << "[TEST] Tipo custom Attivita" << std::endl;

    std::cout << "[1] Creo un set <Attivita> vuoto" << std::endl;
    set<Attivita> s;
    assert(s.size() == 0);

    std::cout << "[2] Creo alcune attivita" << std::endl;
    Attivita a1; a1.titolo = "StudioC++"; a1.ora_inizio = 10; a1.ora_fine = 15;
    Attivita a2; a2.titolo = "Allenamento"; a2.ora_inizio = 18; a2.ora_fine = 20; 
    Attivita a3; a3.titolo = "Cena"; a3.ora_inizio = 21; a3.ora_fine = 22;  

    std::cout << "[3] Inserisco le attivita nel set" << std::endl;
    s.add(a1); s.add(a2); s.add(a3);
    std::cout << "Set dopo inserimento: " << s << std::endl;

    std::cout << "[4] Verifico contains su tipi custum" << std::endl;
    assert(s.contains(a1)); assert(s.contains(a2)); assert(s.contains(a3));

    Attivita d; d.titolo = "Dormire"; d.ora_inizio = 23; d.ora_fine = 7;
    assert(!s.contains(d));

    std::cout << "[5] Iterazione sul set (stampa elemento per elemento)" << std::endl;
    set<Attivita>::const_iterator it;
    for(it = s.begin(); it != s.end(); ++it){
        std::cout << " - "<< *it << std::endl;
    }

    std::cout << "[6] Rimuovo una attivita (Allenamento)" << std::endl;
    s.remove(a2);
    assert(s.size() == 2);
    assert(!s.contains(a2));

    std::cout << "Set dopo la remove: " << s << std::endl;

    std::cout << "  >>> [OK] Tipo custom Attivita" << std::endl << std::endl;
}

/** 
    @brief Funzione principale di test

    Esegue tutti i test definiti per la classe set 
    e ne verifica il corretto comportamento tramite assert

    @return 0 se tutti i test terminano correttamente.
*/
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

    test_load_save();

    test_tipo_custom();

    std::cout << " *** TUTTI I TEST PASSATI CORRETTAMENTE ***" << std::endl << std::endl;

    return 0;
}
