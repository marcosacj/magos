// < https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250 >
// < https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/ >
// < https://www.hackerearth.com/pt-br/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/ >

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
		// os << & n << " ";
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
	std::vector< TableNode * > Nodes;

	Nat key2index( const K & key ){

		auto runner { std::begin(Nodes) };

		while( runner != std::end(Nodes) ){

			if( (*runner)->get_key() == key )
				return std::distance( std::begin(Nodes), runner );
			else
				runner++;

		}

		// return std::distance( std::begin(Nodes), std::end(Nodes) );
		throw std::runtime_error( "The key was not found!" );

	}

public:

	inline Nat size( void ) const { return Nodes.size(); };

	/// Default constructor.
	HashTable( const Nat & TABLE_SIZE ){

		Nodes.reserve( TABLE_SIZE );

	}

	/// Default destructor.
	~HashTable(){

		// todo

	}

	/// Insert a pair <key, value> to the HashTable
	void insert( const K & key, const V & value ){

		TableNode * n = new TableNode{ key, value };

		Nodes.push_back( n );

	}

	void insert( TableNode * n ){

		Nodes.push_back( n );

	}

	/// Merges two TableNodes based on keys.
	void merge_by_key( const K & from, const K & to ){

		Nat fromIndex{ key2index(from) };
		Nat toIndex{ key2index(to) };

		TableNode * fromNode{ Nodes[ fromIndex ] };
		TableNode * toNode{ Nodes[ toIndex ] };

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

		Nodes.erase( Nodes.begin() + fromIndex );

	}

	K get_key( const V & value ){

		// for ( auto i{ std::begin(Nodes) } ; i < std::end(Nodes) ; i++ ){
		for ( Nat i{0} ; i < (Nat) std::distance( std::begin(Nodes), std::end(Nodes) ) ; i++ ){

			TableNode * checker{ Nodes[i] };

			while( checker->get_next() != nullptr ){

				if( checker->get_value() == value )
					return checker->get_key();
				else
					checker = checker->get_next();

			}

			if( checker->get_value() == value )
				return checker->get_key();

		}

		throw std::invalid_argument("The key does not exist in the HashTable!");

	}

	bool isEqualKey( const V & john, const V & josh ){

		return get_key( john ) == get_key( josh );

	}

	V get_value( const K & key ){

		// todo
		// problem: merged keys

	}

	friend std::ostream & operator << ( std::ostream & os, const HashTable & H ){

		os << "HashTable = [" << std::endl;
		for ( Nat i{0} ; i < (Nat) std::distance( std::begin(H.Nodes), std::end(H.Nodes) ) ; i++ ){
			os << "  " << *H.Nodes[i] << std::endl;
		}
		os << "] = " << H.size();

		return os;

	}

};