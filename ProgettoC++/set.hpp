/** 
    @file set.hpp

    @brief File header della classe set templata

    File di dichiarazioni/definizioni della classe set templata
*/
#ifndef SET_HPP
#define SET_HPP

#include <iostream> // std::cout
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

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
        Funzione booleana che controlla se è presente valore passato come parametro nel set

        @param p valore da controllare se è presente
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

    unsigned int size() const{
        return _size;
    }

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

	class iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;

	
		iterator() : current(nullptr){
			//!!!
		}
		
		iterator(const iterator &other) : current(other.current){
			//!!!
		}

		iterator& operator=(const iterator &other) {
			if (this != &other){
                current = other.current;
            }

            return *this;
		}

		~iterator() {
			//!!!
		}

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
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(_head);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(nullptr);
	}
	
	
	
	class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : current(nullptr){
			//!!!
		}
		
		const_iterator(const const_iterator &other) : current(other.current) {
			//!!!
		}

		const_iterator& operator=(const const_iterator &other) {
			if (this != &other){
                current = other.current;
            }
            return *this;
		}

		~const_iterator() {
			//!!!
		}

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
		const_iterator(const iterator &other) : current(other.current) {
			//!!!
		}

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
		const_iterator(const node* n) : current(n) { 
			//!!! 
		}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_head);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	
	
	
	
//}; // CLASSE_CONTAINER_PADR

};

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



#endif