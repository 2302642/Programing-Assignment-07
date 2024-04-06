/*!****************************************************************************************************************************************************************************************************************************************************************************************\file       vector.hpp
\file       vct.hpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202    
\par        Section:         RSE
\par        Tutorial:        Assignment 7
\par        File created on: 07/03/2024 
\brief      user created vector with class and template
\par        File information:         
            This file is contains 5 constructors and 19 function definition to called by main in vector-driver.\n    
            
            CONSTRUCTORS:
            - vector:: vector()                                                                                                                                             // default constructor
            - vector:: vector(size_type n)                                                                                                                                  // non-default constructor with size
            - vector:: vector(std::initializer_list<int> rhs)                                                                                                               // non-default constructor with initializer list
            - vector:: vector(const vector& rhs)                                                                                                                            // copy constructor
            - vector::~vector()                                                                                                                                             // destructor
            
            COPY ASSIGNMENT OPERATORS:
            - vector& vector::operator=(const vector& rhs)                                                                                                                  // copy assignment operator to assigns the content of another vector to this vector
            - vector& vector::operator=(std::initializer_list<int> rhs)                                                                                                     // assignment operator for initializer list to assigns elements from an initializer list to this vector
            
            ELEMENT ACCESSOR OPERATORS:
            - vector::reference vector::operator[](size_type index)                                                                                                         // Subscript operator for non-const objects to hrow exception if index is out of range
            - vector::const_reference vector::operator[](size_type index) const                                                                                             // Subscript operator for const objects to Throw exception if index is out of range
            
            CAPACITY STATUS FUNCTIONS:
            - bool vector::empty() const                                                                                                                                    // checking if the vector is empty
            - vector::size_type vector::size() const                                                                                                                        // getting the size of the vector
            - vector::size_type vector::capacity() const                                                                                                                    // getting the capacity of the vector
            - vector::size_type vector::allocations() const                                                                                                                  // getting the number of allocations	
           
            MODIFIER FUNCTIONS:
            - void vector::reserve(size_type n)                                                                                                                             // reserve function to update spaces allocated 
            - void vector::resize(size_type n)                                                                                                                              // resize function to updated the size of the vector
            - void vector::push_back(value_type val)                                                                                                                        // push back function to add a new value to the end of the vector
            - void pop_back();                                                                                                                                              // pop back function to remove value from the back of the vector
            - void swap(vector& rhs);                                                                                                                                       // swap function to swap the values with rhs and inital values 
            
            ITERATOR FUNCTIONS SECTION 
            - vector::pointer vector::begin()                                                                                                                               // iterator function to point to the start of the vector
            - vector::pointer vector::end()                                                                                                                                 // iterator function to Point to one past the end of the vector
            - vector::const_pointer vector::begin()   const                                                                                                                 // iterator function to Point to the start of the vector (const version)
            - vector::const_pointer vector::end()     const                                                                                                                 // iterator function to Point to one past the end of the vector (const version)
            - vector::const_pointer vector::cbegin()  const                                                                                                                 // iterator function to Point to the start of the vector (const version)
            - vector::const_pointer vector::cend()    const                                                                                                                 // iterator function to Point to one past the end of the vector (const version)
 
******************************************************************************************************************************************************************************************************************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VCT_HPP
#define VCT_HPP

#include <cstddef>              // need this for size_t
#include <initializer_list>     // need this for std::initializer_list<int>
#include <algorithm>            // for std::swap
namespace hlp2 {
//##########################################################################################################################################################################################################################################################################################
template<typename T> class vector {                                      // FUNCTIONS ARE DECLARATION IN CLASS 
    public:
        // Type aliases
        using size_type = std::size_t;
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
//==========================================================================================================================================================================================================================================================================================
//|                                                                          CONSTRUCTORS SECTION                                                                                                                                                                                          |
//==========================================================================================================================================================================================================================================================================================
        vector()                             : sz{0},          space{0},          allocs{0}, data{nullptr} {}                                                               // default constructor
        vector(size_type n)                  : sz{n},          space{n},          allocs{1}, data{new value_type[n]} {}                                                     // non-default constructor with size
        vector(std::initializer_list<T> rhs) : sz{rhs.size()}, space{rhs.size()}, allocs{1}, data{new value_type[rhs.size()]} { std::copy(rhs.begin(), rhs.end(), data); }  // non-default constructor with initializer list
        vector(const vector& rhs)            : sz{rhs.sz},     space{rhs.sz},     allocs{1}, data{new value_type[rhs.sz]}     { std::copy(rhs.data,  rhs.data+sz, data); }  // copy constructor
        ~vector() { delete[] data; }                                                                                                                                        // destructor
//==========================================================================================================================================================================================================================================================================================
//|                                                                          COPY ASSIGNMENT OPERATORS                                                                                                                                                                                     |
//==========================================================================================================================================================================================================================================================================================
        vector<T>& operator=(const vector& rhs) {                                                                                                                           // copy assignment operator to assigns the content of another vector to this vector
            if (this != &rhs) {                                                                                                                                             // Check for self-assignment
                delete[] data;                                                                                                                                              // deallocating old storage
                sz = rhs.sz;                                                                                                                                                // copying size from rhs
                space = rhs.sz;                                                                                                                                             // copying space from rhs
                ++allocs;                                                                                                                                                   // incrementing allocation count
                data = new value_type[sz];                                                                                                                                  // allocating new storage
                std::copy(rhs.data, rhs.data + sz, data);                                                                                                                   // copying elements from rhs.data to data array
            }
            else if(this == &rhs){ space = rhs.sz; ++allocs; }                                                                                                              // Handle self-assignment  
            return *this;                                                                                                                                                   // returning reference to the modified vector
        }
//*******************************************************************************************************************************************************************************************************************************************************************************************
        vector<T>& operator=(std::initializer_list<T> rhs) {                                                                                                                // assignment operator for initializer list to assigns elements from an initializer list to this vector
            delete[] data;                                                                                                                                                  // deallocating old storage
            sz = rhs.size();                                                                                                                                                // copying size from initializer list
            space = rhs.size();                                                                                                                                             // copying space from initializer list
            allocs = 1;                                                                                                                                                     // Set allocation count to 1
            data = new value_type[sz];                                                                                                                                      // allocating new storage
            std::copy(rhs.begin(), rhs.end(), data);                                                                                                                        // copying elements from initializer list to data vector
            return *this;                                                                                                                                                   // returning reference to the modified vector
        }
//==========================================================================================================================================================================================================================================================================================
//|                                                                          ELEMENT ACCESSOR OPERATORS                                                                                                                                                                                    |
//==========================================================================================================================================================================================================================================================================================
        reference operator[](size_type index){ if (index >= sz) { throw std::out_of_range("Index out of range"); } return data[index]; }                                    // Subscript operator for non-const objects to hrow exception if index is out of range
        const_reference operator[](size_type index) const { if (index >= sz) { throw std::out_of_range("Index out of range"); } return data[index]; }                       // Subscript operator for const objects to Throw exception if index is out of range
//==========================================================================================================================================================================================================================================================================================
//|                                                                          CAPACITY STATUS FUNCTIONS                                                                                                                                                                                     |
//==========================================================================================================================================================================================================================================================================================
        bool empty() const { return sz == 0; }                                                                                                                              // checking if the vector is empty
        size_type size() const { return sz; }                                                                                                                               // getting the size of the vector
        size_type capacity() const { return space; }                                                                                                                        // getting the capacity of the vector
        size_type allocations() const { return allocs;    }                                                                                                                 // getting the number of allocations
//==========================================================================================================================================================================================================================================================================================
//|                                                                          MODIFIER FUNCTIONS                                                                                                                                                                                            |
//==========================================================================================================================================================================================================================================================================================
        void reserve(size_type n) {                                                                                                                                         // reserve function to update spaces allocated 
            if (n <= space) { return; }                                                                                                                                     // do nothing if requested capacity is less than or equal to current capacity
            value_type* temp = new value_type[n];                                                                                                                           // allocate new vector for temp
            std::copy(data, data + sz, temp);                                                                                                                               // copy old elements to temp vector
            delete[] data;                                                                                                                                                  // deallocate old vector
            data = temp;                                                                                                                                                    // updating cleared vector with data in temp vector
            space = n;                                                                                                                                                      // update the capacity in the new vector
            ++allocs;                                                                                                                                                       // incrementing the allocation count 
        }
//*******************************************************************************************************************************************************************************************************************************************************************************************
        void resize(size_type n) {                                                                                                                                          // resize function to updated the size of the vector
            if (n == sz) { return; }                                                                                                                                        // do nothing if requested size is equal to current size
            reserve(n);                                                                                                                                                     // allocating new space
            if (n < sz) { sz = n; }                                                                                                                                         // shrinking the vector
            else {                                                                                                                                                          // expanding the vector
                std::fill(data + sz, data + n, value_type{});                                                                                                               // initializing new elements if the expanding the vector
                sz = n;
            }
        }
//*******************************************************************************************************************************************************************************************************************************************************************************************
        void push_back(value_type val) {                                                                                                                                    // push back function to add a new value to the end of the vector
            if (space == 0) { reserve(1); }                                                                                                                                 // reserving space for 1 element if the vector is empty
            else if (sz == space) { reserve(2 * space); }                                                                                                                   // doubling the space if the vector is full
            data[sz++] = val;                                                                                                                                               // adding element at the end of the vector and incrementing the size
        }
//*******************************************************************************************************************************************************************************************************************************************************************************************
        void pop_back() { if (sz > 0) {--sz;} }                                                                                                                             // pop back function to remove value from the back of the vector
//*******************************************************************************************************************************************************************************************************************************************************************************************
        void swap(vector& rhs){                                                                                                                                             // swap function to swap the values with rhs and inital values 
            std::swap(sz, rhs.sz);                                                                                                                                          // Swapping the size of this vector with the size of 'rhs'
            std::swap(space, rhs.space);                                                                                                                                    // Swapping the capacity of this vector with the capacity of 'rhs'
            std::swap(allocs, rhs.allocs);                                                                                                                                  // Swapping the number of allocations of this vector with 'rhs'
            std::swap(data, rhs.data);                                                                                                                                      // Swapping the pointer to the data of this vector with the pointer to the data of 'rhs'
        }      
//==========================================================================================================================================================================================================================================================================================
//|                                                                            ITERATOR FUNCTIONS SECTION                                                                                                                                                                                  |
//==========================================================================================================================================================================================================================================================================================
        pointer       begin()         { return data;      }                                                                                                                 // point to the start of the vector
        pointer       end()           { return data + sz; }                                                                                                                 // Point to one past the end of the vector
        const_pointer begin()   const { return data;      }                                                                                                                 // Point to the start of the vector (const version)
        const_pointer end()     const { return data + sz; }                                                                                                                 // Point to one past the end of the vector (const version)
        const_pointer cbegin()  const { return data;      }                                                                                                                 // Point to the start of the vector (const version)
        const_pointer cend()    const { return data + sz; } 

    private:
        size_type sz;                                                                                                                                                       // the number of elements in the array
        size_type space;                                                                                                                                                    // the allocated size (in terms of elements) of the array
        size_type allocs;                                                                                                                                                   // number of times space has been updated
        pointer   data;                                                                                                                                                     // the dynamically allocated array
  };
//##########################################################################################################################################################################################################################################################################################
} // namespace hlp2
#endif // VCT_HPP

/*                                                                   CODE WHERE THERE IS FUNCTIONS DECLARATION AND DEFINITION
#ifndef VCT_HPP
#define VCT_HPP

#include <cstddef>          // need this for size_t
#include <initializer_list> // need this for std::initializer_list<int>
#include <algorithm>        // for std::swap
namespace hlp2 {

template<typename T> class vector {
    public:
        // Type aliases
        using size_type = std::size_t;
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        // Constructors
        vector();                                             // default constructor
        explicit vector(size_type n);                         // non-default constructor with size
        vector(std::initializer_list<T> rhs);                 // non-default constructor with initializer list
        vector(const vector& rhs);                            // copy constructor
        ~vector();                                            // destructor

        // Copy assignment operators
        vector& operator=(const vector& rhs);                 // copy assignment operator to assigns the content of another vector to this vector
        vector& operator=(std::initializer_list<T> rhs);      // assignment operator for initializer list to assigns elements from an initializer list to this vector

        // Element access operators
        reference operator[](size_type index);                // Subscript operator for non-const objects to hrow exception if index is out of range
        const_reference operator[](size_type index) const;    // Subscript operator for const objects to Throw exception if index is out of range

        // Capacity
        bool empty() const;                                   // checking if the vector is empty
        size_type size() const;                               // getting the size of the vector
        size_type capacity() const;                           // getting the capacity of the vector
        size_type allocations() const;                        // getting the number of allocations

        // Modifiers
        void reserve(size_type n);                            // reserve function to update spaces allocated
        void resize(size_type n);                             // resize function to updated the size of the vector
        void push_back(value_type val);                       // push back function to add a new value to the end of the vector
        void pop_back();                                      // pop back function to remove value from the back of the vector
        void swap(vector& rhs);                               // swap function to swap the values with rhs and inital values 

        // Iterators
        pointer begin();                                      // point to the start of the vector
        pointer end();                                        // Point to one past the end of the vector
        const_pointer begin()  const;                         // Point to the start of the vector (const version)
        const_pointer end()    const;                         // Point to one past the end of the vector (const version)
        const_pointer cbegin() const;                         // Point to the start of the vector (const version)
        const_pointer cend()   const;                         // Point to one past the end of the vector (const version)
      
    private:
        size_type sz;                                         // the number of elements in the array
        size_type space;                                      // the allocated size (in terms of elements) of the array
        size_type allocs;                                     // number of times space has been updated
        pointer   data;                                       // the dynamically allocated array
  };
//==========================================================================================================================================================================================================================================================================================
//|                                                                          CONSTRUCTORS SECTION                                                                                                                                                                                          |
//==========================================================================================================================================================================================================================================================================================
    template<typename T> vector<T>::vector()                             : sz{0},          space{0},          allocs{0}, data{nullptr} {}                                                                 // default constructor
    template<typename T> vector<T>::vector(size_type n)                  : sz{n},          space{n},          allocs{1}, data{new value_type[n]} {}                                                       // non-default constructor with size
    template<typename T> vector<T>::vector(std::initializer_list<T> rhs) : sz{rhs.size()}, space{rhs.size()}, allocs{1}, data{new value_type[rhs.size()]} { std::copy(rhs.begin(), rhs.end(), data); }    // non-default constructor with initializer list
    template<typename T> vector<T>::vector(const vector& rhs)            : sz{rhs.sz},     space{rhs.sz},     allocs{1}, data{new value_type[rhs.sz]}     { std::copy(rhs.data,  rhs.data+sz, data); }    // copy constructor
    template<typename T> vector<T>::~vector() { delete[] data; }                                                                                                                                          // destructor
//==========================================================================================================================================================================================================================================================================================
//|                                                                          FUNCTIONS SECTION                                                                                                                                                                                             |
//==========================================================================================================================================================================================================================================================================================
    template<typename T> vector<T>& vector<T>::operator=(const vector& rhs) {                                                                                                                             // copy assignment operator to assigns the content of another vector to this vector
        if (this != &rhs) {                                                                                                                                                                               // Check for self-assignment
            delete[] data;                                                                                                                                                                                // deallocating old storage
            sz = rhs.sz;                                                                                                                                                                                  // copying size from rhs
            space = rhs.sz;                                                                                                                                                                               // copying space from rhs
            ++allocs;                                                                                                                                                                                     // incrementing allocation count
            data = new value_type[sz];                                                                                                                                                                    // allocating new storage
            std::copy(rhs.data, rhs.data + sz, data);                                                                                                                                                     // copying elements from rhs.data to data array
        }
        else if(this == &rhs){ space = rhs.sz; ++allocs; }                                                                                                                                                // Handle self-assignment  
        return *this;                                                                                                                                                                                     // returning reference to the modified vector
    }
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> vector<T>& vector<T>::operator=(std::initializer_list<T> rhs) {                                                                                                                  // assignment operator for initializer list to assigns elements from an initializer list to this vector
        delete[] data;                                                                                                                                                                                    // deallocating old storage
        sz = rhs.size();                                                                                                                                                                                  // copying size from initializer list
        space = rhs.size();                                                                                                                                                                               // copying space from initializer list
        allocs = 1;                                                                                                                                                                                       // Set allocation count to 1
        data = new value_type[sz];                                                                                                                                                                        // allocating new storage
        std::copy(rhs.begin(), rhs.end(), data);                                                                                                                                                          // copying elements from initializer list to data vector
        return *this;                                                                                                                                                                                     // returning reference to the modified vector
    }
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> typename vector<T>::reference vector<T>::operator[](size_type index){ if (index >= sz) { throw std::out_of_range("Index out of range"); } return data[index]; }                  // Subscript operator for non-const objects to hrow exception if index is out of range
    template<typename T> typename vector<T>::const_reference vector<T>::operator[](size_type index) const { if (index >= sz) { throw std::out_of_range("Index out of range"); } return data[index]; }     // Subscript operator for const objects to Throw exception if index is out of range
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> bool vector<T>::empty() const {  return sz == 0; }                                                                                                                               // checking if the vector is empty
    template<typename T> typename vector<T>::size_type vector<T>::size() const { return sz; }                                                                                                             // getting the size of the vector
    template<typename T> typename vector<T>::size_type vector<T>::capacity() const { return space; }                                                                                                      // getting the capacity of the vector
    template<typename T> typename vector<T>::size_type vector<T>::allocations() const { return allocs;    }                                                                                               // getting the number of allocations
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> void vector<T>::reserve(size_type n) {                                                                                                                                           // reserve function to update spaces allocated 
        if (n <= space) { return; }                                                                                                                                                                       // do nothing if requested capacity is less than or equal to current capacity
        value_type* temp = new value_type[n];                                                                                                                                                             // allocate new vector for temp
        std::copy(data, data + sz, temp);                                                                                                                                                                 // copy old elements to temp vector
        delete[] data;                                                                                                                                                                                    // deallocate old vector
        data = temp;                                                                                                                                                                                      // updating cleared vector with data in temp vector
        space = n;                                                                                                                                                                                        // update the capacity in the new vector
        ++allocs;                                                                                                                                                                                         // incrementing the allocation count 
    }
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> void vector<T>::resize(size_type n) {                                                                                                                                            // resize function to updated the size of the vector
        if (n == sz) { return; }                                                                                                                                                                          // do nothing if requested size is equal to current size
        reserve(n);                                                                                                                                                                                       // allocating new space
        if (n < sz) { sz = n; }                                                                                                                                                                           // shrinking the vector
        else {                                                                                                                                                                                            // expanding the vector
            std::fill(data + sz, data + n, value_type{});                                                                                                                                                 // initializing new elements if the expanding the vector
            sz = n;
        }
    }
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> void vector<T>::push_back(value_type val) {                                                                                                                                      // push back function to add a new value to the end of the vector
        if (space == 0) { reserve(1); }                                                                                                                                                                   // reserving space for 1 element if the vector is empty
        else if (sz == space) { reserve(2 * space); }                                                                                                                                                     // doubling the space if the vector is full
        data[sz++] = val;                                                                                                                                                                                 // adding element at the end of the vector and incrementing the size
    }
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> void vector<T>::pop_back() { if (sz > 0) {--sz;} }                                                                                                                               // pop back function to remove value from the back of the vector
//  *******************************************************************************************************************************************************************************************************************************************************************************************
    template<typename T> void vector<T>::swap(vector& rhs){                                                                                                                                               // swap function to swap the values with rhs and inital values 
        std::swap(sz, rhs.sz);                                                                                                                                                                            // Swapping the size of this vector with the size of 'rhs'
        std::swap(space, rhs.space);                                                                                                                                                                      // Swapping the capacity of this vector with the capacity of 'rhs'
        std::swap(allocs, rhs.allocs);                                                                                                                                                                    // Swapping the number of allocations of this vector with 'rhs'
        std::swap(data, rhs.data);                                                                                                                                                                        // Swapping the pointer to the data of this vector with the pointer to the data of 'rhs'
    }      
//==========================================================================================================================================================================================================================================================================================
//|                                                                            ITERATOR FUNCTIONS SECTION                                                                                                                                                                                  |
//==========================================================================================================================================================================================================================================================================================
    template<typename T> typename vector<T>::pointer       vector<T>::begin()         { return data;      }                                                                                               // point to the start of the vector
    template<typename T> typename vector<T>::pointer       vector<T>::end()           { return data + sz; }                                                                                               // Point to one past the end of the vector
    template<typename T> typename vector<T>::const_pointer vector<T>::begin()   const { return data;      }                                                                                               // Point to the start of the vector (const version)
    template<typename T> typename vector<T>::const_pointer vector<T>::end()     const { return data + sz; }                                                                                               // Point to one past the end of the vector (const version)
    template<typename T> typename vector<T>::const_pointer vector<T>::cbegin()  const { return data;      }                                                                                               // Point to the start of the vector (const version)
    template<typename T> typename vector<T>::const_pointer vector<T>::cend()    const { return data + sz; } 
//##########################################################################################################################################################################################################################################################################################
} // namespace hlp2
#endif // VCT_HPP
*/
