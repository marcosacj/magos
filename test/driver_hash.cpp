#include <iostream>

#include "hash.h"

int main(){

	HashNode<int, int> n{0, 1};
	HashNode<int, int> m{1, 2};

	HashTable<int, int> t{ 10 };

	std::cout << t << std::endl;

	t.insert( & n );
	t.insert( & m);
	t.insert( 2, 3 );
	t.insert( 3, 4 );
	t.insert( 4, 5 );

	std::cout << t << std::endl;

	t.merge_by_key(2, 1);
	std::cout << t << std::endl;

	t.merge_by_key(1, 0);
	std::cout << t << std::endl;

	for ( int i(0) ; i < 5 ; i++ ){
		std::cout << "key of " << i+1 << " is = " << t.get_key( i + 1 ) << std::endl;
	}

	t.merge_by_key(4, 3);
	std::cout << t << std::endl;

	for ( int i(0) ; i < 5 ; i++ ){
		std::cout << "key of " << i+1 << " is = " << t.get_key( i + 1 ) << std::endl;
	}

	std::cout << "isEqualKey true = " << ( t.isEqualKey( 2, 3 ) ? "yes" : "no" ) << std::endl;
	std::cout << "isEqualKey true = " << ( t.isEqualKey( 2, 4 ) ? "yes" : "no" ) << std::endl;

	t.merge_by_key(3, 0);
	std::cout << t << std::endl;

	for ( int i(0) ; i < 5 ; i++ ){
		std::cout << "key of " << i+1 << " is = " << t.get_key( i + 1 ) << std::endl;
	}

	std::cout << "isEqualKey true = " << ( t.isEqualKey( 2, 3 ) ? "yes" : "no" ) << std::endl;
	std::cout << "isEqualKey true = " << ( t.isEqualKey( 2, 4 ) ? "yes" : "no" ) << std::endl;

	return 0;
	
}