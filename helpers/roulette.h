#include <vector>
#include <iterator>
#include <algorithm>

template<typename T>
class Roulette {

private:

	std::vector<T> circle;
	
	typename std::vector<T>::iterator it;

public:

	// Constructor without parameters.
	Roulette( void ){
		it = circle.begin();
	}

	// Defauts destructor.
	~Roulette( void ){
		// todo
	}

	// Point internal iterator to next element
	void step( void ){
		if( circle.empty() )
			return;
		else if( it == circle.end() - 1 )
			it = std::begin( circle );
		else
			it++;
	}

	// Consult current value of the internal iterator.
	T value( void ){
		if( circle.empty() )
			throw std::runtime_error( "The roullete is empty!" );
		else
			return *it;
	}

	// Perform an step and returns the value.
	T step_value( void ){
		step();
		return value();
	}

	// Add an element to the circle
	void add( const T & e ){
		circle.push_back( e );
		it = circle.end() - 1;
	}

	// Remove current element from the circle
	void remove( void ){
		circle.erase( it );
	}

	// Set the iterator to certain index of the circle.
	void point_to( const unsigned int & i ){
		it = circle.begin() + i % circle.size();
	}

	// shuffle elements of the circle.
	void shuffle( void ){
		std::shuffle( std::begin(circle), std::end(circle), std::mt19937{ std::random_device{}() } );
	}

	friend std::ostream & operator << ( std::ostream & os, const Roulette & r ) {

		std::cout << "[ ";
		std::copy( r.circle.begin() , r.circle.end() , std::ostream_iterator<T>( os, " ") );
		std::cout << "]";

		return os;

	}

};