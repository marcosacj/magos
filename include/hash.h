#include <iostream>
#include <vector>
#include <iterator>

typedef std::size_t Nat;

template<typename K, typename V>
class HashNode {

private:

	K key;
	V value;

	HashNode<K,V> * next;

public:

	/// Default constructor.
	HashNode( const K & key, const V & value ){
		this->key = key;
		this->value = value;
		this->next = nullptr;
	}

	// getters 
	inline K get_key( void ) const { return key; };
	inline V get_value( void ) const { return value; };
	inline HashNode * get_next( void ) const { return next; };

	// setters 
	inline void set_key( const K & key ) { this->key = key; };
	inline void set_value( const V & value ){ this->value = value; };
	
	inline void set_next( HashNode * next ){
		next->set_key( this->get_key() );
		this->next = next;
	};

	friend std::ostream & operator << ( std::ostream & os, const HashNode & n ){

		// os << "< key = " << n.get_key() <<  " , value = " << n.get_value() << " , next = ";
		os << "< " << n.get_key() <<  " , " << n.get_value() << " , ";
		
		if( n.next == nullptr )
			os << "nullptr";
		else
			os << *n.next;

		os << " >";

		return os;

	}

};

template<typename K, typename V>
class HashTable {

private:

	/// Abstraction of a HashNode
	typedef HashNode<K, V> TableNode;

	/// Table of HashNodes
	std::vector< TableNode * > table;

	/// Number of HashNodes in the HashTable.
	Nat size() const {
		return table.size();
	};

public:

	/// Default constructor.
	HashTable( const Nat & TABLE_SIZE ){

		table.reserve( TABLE_SIZE );

	}

	/// Default destructor.
	~HashTable(){

		// todo

	}

	/// Insert and pair <key, value> to the HashTable
	void insert( const K & key, const V & value ){

		TableNode * n = new TableNode{ key, value };

		table.push_back( n );

	}

	void insert( TableNode * n ){

		table.push_back( n );

	}

	Nat key2index( const K & key ){

		// TableNode * runner { table.front() };

		// while( runner != table.back() ){
		// 	if( runner->get_key() == key )
		// 		break;

		// 	runner++;
		// }

		// std::cout << "aqui..." << std::endl;

		// return runner;

		for ( Nat i{0} ; i < table.size() ; i++ ){

			if( table[i]->get_key() == key ){
				return i;
			}

		}

		return table.size();

	}

	/// Merges two TableNodes based on position in HashTable
	void merge( const K & from, const K & to ){

		TableNode * fromNode{ table[ key2index(from) ] };
		TableNode * toNode{ table[ key2index(to) ] };

		// go to last linked node
		while( toNode->get_next() != nullptr ){
			toNode = toNode->get_next();
		}

		// link nodes
		toNode->set_next( fromNode );

		// update keys of linked nodes in from node
		TableNode * aux{ fromNode };
		while( aux->get_next() != nullptr ){
			aux = aux->get_next();
			aux->set_key( toNode->get_key() );
		}

		// table.erase( table.cbegin() + key2index(from) );
		// table.erase( std::begin(table) + key2index(from) );
		// table.erase( key2index(from) );

		/* anterior version based on index as parameter to the function */
		// table[to]->set_next( table[from] );

		// TableNode * aux{ table[from] };
		// while( aux->get_next() != nullptr ){
		// 	aux = aux->get_next();
		// 	aux->set_key( table[to]->get_key() );
		// }

		// table[from] = table[to];

		// table.erase( std::begin(table) + from );

	}

	K get_key( const V & value ){

		// todo

	}

	V get_value( const K & key ){

		// todo
		// problem: merged keys

	}

	void remove( const K & key ){

		// todo

	}

	friend std::ostream & operator << ( std::ostream & os, const HashTable & H ){

		os << "HashTable = [" << std::endl;
		for ( Nat i{0} ; i < H.size() ; i++ ){
			os << "  " << *H.table[i] << std::endl;
		}
		os << "]";

		return os;

	}

};