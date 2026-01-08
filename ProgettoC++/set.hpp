/** 
    @file set.hpp

    @brief Implementazione della classe set templata

    Questo file contiene la definizione e l'implementazione
    della classe template set<T>. Un Set è una collezione di dati che NON può
    contenere duplicati. 
*/
#ifndef SET_HPP
#define SET_HPP

#include <iostream> // std::cout
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

/** 
    @brief Struttura che rappresenta un'attività

    Contiene le informazioni principali di un'attività
    come il titolo e l'orario di inizio e fine. 
*/
struct Attivita{
    std::string titolo;
    int ora_inizio;
    int ora_fine;
};

/** 
    @brief Operatore di uguaglianza tra due Attività

    Due attività sono considerate uguali se hanno lo stesso titolo, 
    la stessa ora di inizio e la stessa ora di fine. 

    @param a prima attività
    @param b seconda attività
    @return true se le due attvità sono uguali, false altrimenti
*/
bool operator==(const Attivita &a, const Attivita &b){
    return a.titolo == b.titolo &&
           a.ora_inizio == b.ora_inizio &&
           a.ora_fine == b.ora_fine;
}

/** 
    @brief Operatore di output per Attività

    Stampa un'attività nel formato: 
    "titolo ora_inizio-ora_fine".

    @param os flusso di output
    @param a attvità da stampare
    @return riferimento al flusso di output
*/
std::ostream& operator<<(std::ostream& os, const Attivita &a){
    os << a.titolo << " "
       << a.ora_inizio << "-"
       << a.ora_fine;
    return os;
}

/** 
    @brief Classe set templata

    Rappresenta un insieme di elementi unici di tipo T.

    @tparam T tipo degli elementi contenuti nel set
*/
template<typename T>
class set{

    /** 
        @brief Struttura dati node

        Struttura dati node interna che viene usata per creare il set. 
        Implementazione come una lista ma non ordinata. 
    */
    struct node{
        T value; // dato di un elemento del set
        node *next; // puntatore al nodo successivo del set

        /** 
            Costrutture di default
            @post next == nullptr
        */
        node() : next(nullptr){}

        /** 
            Costruttore secondario
            @param v valore da copiare

            @post value == v
            @post next == nullptr
        */
        node(const T &v) : value(v), next(nullptr){}

        /** 
            Costrutture secondario  
            @param v valore da copiare
            @param n puntatore al prossimo nodo

            @post value == v
            @post next == n
        */
       node(const T &v, node *n) : value(v), next(n){}
    }; // fine struct node

    node *_head ;// puntatore all'inizio del set
    unsigned int _size; // dimensione del set

    public:

    /** 
        Costruttore di default

        @post _head == nullptr
        @post _size == 0
    */
    set() : _head(nullptr), _size(0) {}

    /** 
        Copy constructor
        
        @param other set da copiare

        @throw std::bad_alloc possibie eccezione di allocazione
    */
    set(const set &other) : _head(nullptr), _size(0){
        node *curr = other._head;

        try
        {
           while(curr != nullptr){
                add(curr->value);
                curr = curr->next;
           }
        }
        catch(...)
        {
            clear();
            throw;
        }
    }

    /** 
        Operatore di assegnamento

        @param other set da copiare
        @return reference al set this
        @throw std::bad_alloc possibile eccezione di allocazione
     
    */
    set& operator=(const set &other){
        if(this != &other){
            set temp(other);
            this->swap(temp);
        }
        return *this;
    }

    /** 
        Distruttore, svuota il set

        @post _head == nullptr
        @post _size == 0;
    */
    ~set(){
       clear();
    }

    /** 
        Svuota il set

        @post _head == nullptr
        @post _size == 0;
    */
    void clear(){
       node *curr = _head;
       while(curr != nullptr){
        node *tmp = curr->next;
        delete curr;
        curr = tmp;
       }

       _size = 0;
       _head = nullptr;
    }

    /** 
        Funzione di swap che scambia il set corrente con quello passato come parametro

        @param other set da scambiare
    */
    void swap(set &other){
        std::swap(_head, other._head);
        std::swap(_size, other._size);
   }

    /** 
        @brief Verifica se un valore è presente nel set

        @param p valore da cercare
        @return treu se il valore è presente, false altrimenti
    */
    bool contains(const T &p) const{
        node *curr = _head;
        while(curr != nullptr){
            if(curr->value == p)
                return true;
            curr = curr->next;
        }

        return false;
    }
    /** 
        @brief Ritorna la dimensione del set

        @return _size
    */
    unsigned int size() const{
        return _size;
    }

    /** 
        @brief Inserisce un valore nel set

        Inserisce il valore solo se non è già presente.

        @param value valore da inserire
    */
    void add(const T &value){

        // se già presente, non fare nulla
        if(contains(value))
            return;

        node *n = new node(value);

        // inserimento in testa
        n->next = _head;
        _head = n;

        ++_size;
    }

    /** 
        @brief Rimuove un valore dal set

        Se il valore non è presente, il set rimane invariato

        @param value valore da rimuovere
    */
    void remove(const T &value){

        // caso lista vuota
        if(_head == nullptr)
            return;

        // caso elemento in testa
        if(_head->value == value){
            node *tmp = _head;
            _head = _head->next;
            delete tmp;
            --_size;
            return;
        }
           
        // caso generale
        node *curr = _head;
        while(curr->next != nullptr){
            if(curr->next->value == value){
                node *tmp = curr->next;
                curr->next = tmp->next;
                delete tmp;
                --_size;
                return;
            }
            
            curr = curr->next;
        }
    }

    /** 
        @brief Operatore di uguaglianza tra due set

        Due set sono considerati uguali se contengono
        gli stessi elementi indipendentemente dall'ordine. 

        @param other set da confrontare con l'oggetto corrente
        @return true se i due set contengono gli stessi elementi, false altrimenti
    */
    bool operator==(const set &other) const{

        if(this->_size != other._size)
            return false;

        node *curr = _head;
        while(curr != nullptr){
            if(!other.contains(curr->value))
                return false;
            curr = curr->next;
        }

        return true;
    }

    /** 
        @brief Operatore di accesso in lettura

        @param i indice dell'elemento
        @return riferimento costante all'elemento
        @throw std::out_of_range se l'indice non è valido
    */
    const T& operator[](unsigned int i) const{

        if(i >= _size)
            throw std::out_of_range("Indice fuori dal range");

        node *curr = _head;
        unsigned int index = 0;

        while(curr != nullptr){
            if(index == i)
                return curr->value;
            
                curr = curr->next;
                ++index;
        }

        throw std::out_of_range("Indice fuori dal range");
    }

    /** 
        @brief Operatore di accesso in lettura e scrittura 

        @param i indice dell'elemento
        @return riferimento costante all'elemento
        @throw std::out_of_range se l'indice non è valido
    */
    T& operator[](unsigned int i){

        if(i >= _size)
            throw std::out_of_range("Indice fuori dal range");

        node *curr = _head;
        unsigned int index = 0;

        while(curr != nullptr){
            if(index == i)
                return curr->value;
            
                curr = curr->next;
                ++index;
        }

        throw std::out_of_range("Indice fuori dal range");
    }

    /** 
        @brief Operatore di intersezione tra due set

        Restituisce un nuovo set contenente gli elementi
        presenti sia nel set corrente sia nel set passato
        come parametro. 
        L'operatore non modifica i set originali. 

        @param other set con cui calcolare l'intersezione
        @return nuovo set risultato dell'intersezione.
    */
    set operator-(const set &other) const{

        set risultato;

        const_iterator it = begin();
        const_iterator it_end = end();

        while(it != it_end){
            if(other.contains(*it)){
                risultato.add(*it);
            }
            
            ++it;
        }

        return risultato;
    }

    /** 
        @brief Costruttore da intervallo di iteratori

        Crea un set a partire da una coppia generica di iteratori. Gli elementi
        compresi nell'intervallo [first, last) vengono inseriti nel set con la funzione add()
        che garantisce l'assenza di duplicati. In caso si eccezioni durante l'inserimento
        o l'allocazione dinamica della memoria, il set viene svuotato per evitare memory leak
        e l'eccezione viene rilanciata. 

        @tparam Iterator tipo dell'iteratore
        @param first iteratore all'inizio dell'intervallo
        @param last iteratore alla fine dell'intervallo
        @throw qualunque eccezione sollevata durante l'inseriemento
    */
    template<typename Iterator>
    set(Iterator first, Iterator last) : _head(nullptr), _size(0){

        try{
            while(first != last){
                add(static_cast<T>(*first));
                ++first;
            }
        }catch (...){
            clear();
            throw;
        }
    }


    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const set<U>&);



	
	class const_iterator; // forward declaration

    /** 
        @brief Iteratore forward per la classe set

        Permette di scorrere gli elementi del set e di accedere in lettura
        e scrittura ai valori contenuti. Implementa un iteratore di tipo forward. 
    */
	class iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;

	
		iterator() : current(nullptr){}
		
		iterator(const iterator &other) : current(other.current){}

		iterator& operator=(const iterator &other) {
			if (this != &other){
                current = other.current;
            }

            return *this;
		}

		~iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return current->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(current->value);
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
			iterator tmp(*this);
            current = current->next;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		iterator& operator++() {
			current = current->next;
            return *this;
		}

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return current == other.current;
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return current != other.current;
		}
		
		
		friend class const_iterator;

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return current == other.current;
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return current != other.current;
		}

		// Solo se serve anche const_iterator aggiungere le precedenti definizioni

	private:
		node* current;  //Dati membro

		friend class set; 

		
		iterator(node* n) : current(n) { 
			//!!! 
		}
	
		
	}; // classe iterator
	
	/** 
        @brief Restituisce un iteratore all'inizio del set

        @return iteratore al primo elemento
    */
	iterator begin() {
		return iterator(_head);
	}
	
	/** 
        @brief Restituisce un iteratore alla fine del set

        L'iteratore restituito non fa riferimento ad alcun elemento

        @return iteratore alla fine del set
    */
	iterator end() {
		return iterator(nullptr);
	}
	
	
	/** 
        @brief Iteratore costante per la classe set

        Permette di scorrere gli elementi del set in sola lettura. 
        Non consente la modifica dei vari valori a cui punta. 
        Implmenta un iteratore di tipo forword. 
    */
	class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : current(nullptr){}
		
		const_iterator(const const_iterator &other) : current(other.current) {}

		const_iterator& operator=(const const_iterator &other) {
			if (this != &other){
                current = other.current;
            }
            return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return current->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(current->value);
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
            current = current->next;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			current = current->next;
            return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return current == other.current;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return current != other.current;
		}

		
		friend class iterator;

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return current == other.current;
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return current != other.current;
		}

		// Costruttore di conversione iterator -> const_iterator
		const_iterator(const iterator &other) : current(other.current) {}

		// Assegnamento di un iterator ad un const_iterator
		const_iterator &operator=(const iterator &other) {
			current = other.current;
            return *this;
		}


	private:
		const node* current; //Dati membro
		
		friend class set; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const node* n) : current(n) {}
		
	}; // classe const_iterator
	
	/** 
        @brief Restituisce un iteratore costante all'inzio del set

        @return iteratore costante al primo elemento
    */
	const_iterator begin() const {
		return const_iterator(_head);
	}
	
	/** 
        @brief Restituisce un iteratore costante alla fine del set

        L'iteratore restituito non fa riferimento ad alcun elemento

        @return iteratore costante alla fine del set.
    */
	const_iterator end() const {
		return const_iterator(nullptr);
	}	
//}; // CLASSE_CONTAINER_PADRE
};

/** 
    @brief Operatore di output per il set

    @tparam T tipo degli elementi del set
    @param os flusso di output
    @param s set da stampare
    @return riferimento al flusso di output
*/
template <typename T>
std::ostream &operator<<(std::ostream &os, const set<T> &s){
    
    typename set<T>::node *curr = s._head;

    os << "{";

    while(curr != nullptr){
        os << curr->value;
        if(curr->next != nullptr)
            os << ", ";
        curr = curr->next;
    }

    os << "}";
    return os;

}

/** 
    @brief Operatore di unione tra due set

    Restituisce un nuovo set contenente tutti gli elementi presenti
    in almeno uno dei due set passati come parametro. L'operatore non modifica i set originali.

    @tparam T tipo degli elementi contenuti nei set
    @param s1 primo set
    @param s2 secondo set
    @return nuovo set risultato dell'unione di s1 e s2
*/
template<typename T>
set<T> operator+(const set<T>& s1, const set<T>& s2){

    set<T> risultato(s1); 

    typename set<T>::const_iterator it = s2.begin();
    typename set<T>::const_iterator it_end = s2.end();

    while(it != it_end){
        risultato.add(*it);
        ++it;
    }

    return risultato;
}

/** 
    @brief Filtra gli elementi del set secondo un predicato

    @tparam T tipo degli elementi
    @tparam Predicato tipo del predicato
    @param s set di partenza
    @param P predicato di filtraggio
    @return nuovo set contenente gli elementi che soddisfano il predicato
*/
template <typename T, typename Predicato>
set<T> filter_out(const set<T>& s, Predicato P){

    set<T> risultato;

    typename set<T>::const_iterator it = s.begin();
    typename set<T>::const_iterator it_end = s.end();

    while(it != it_end){
        if(P(*it)){
            risultato.add(*it);
        }

        ++it;
    }

    return risultato;
}

/** 
    @brief Salva il contenuto di un set di Attivita su file 

    Scrive ogni elemento del set su una riga del file, 
    utilizzando il carattere ';' come separatore tra i campi. 

    @param s set di Attività da salvare
    @param filename nome del file di output
    @param std::runtime_error se il file non può essere aperto
*/
void save(const set<Attivita> &s, const std::string &filename){
    std::ofstream file(filename.c_str());

    if(!file)
        throw std::runtime_error("Errore apertura file");

    for(set<Attivita>::const_iterator it = s.begin(); it != s.end(); ++it){

        file << it->titolo << ";"
             << it->ora_inizio << ";"
             << it->ora_fine << std::endl;
    }
}

/** 
    @brief Carica il contenuto di un set di Attività da file

    Se esiste il file, il set passato come parametro viene prima svuotato
    e successivamente riempito con i dati letti dal file
    Se il file non esiste o non è accessibile, la funzione termina. 

    @param filename nome del file di input
    @param s set di Attivita in cui caricare i dati
*/
void load(const std::string &filename, set<Attivita> &s){
    std::ifstream file(filename.c_str());

    if(!file)
        return; // se il file non esiste non fa nulla

    s.clear();

    std::string titolo;
    int ora_inizio;
    int ora_fine;
    char separatore; // (;)

    while(std::getline(file, titolo, ';')){
        file >> ora_inizio;
        file >> separatore;
        file >> ora_fine;
        file.ignore(); // salta il newline
        
        Attivita a;
        a.titolo = titolo;
        a.ora_inizio = ora_inizio;
        a.ora_fine = ora_fine;

        s.add(a);
    }
}

#endif