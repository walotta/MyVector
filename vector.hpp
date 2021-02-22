#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
private:
    T* _storeBegin=nullptr;
    T* _storeEnd=nullptr;
    T* _dataBegin=nullptr;
    T* _dataEnd=nullptr;
    void _build(int size=8)
    {
        T* tem=(T*)::operator new(size*sizeof(T));
        int k=1;
        if(_dataBegin!=nullptr)
        {
            for(int i=_dataBegin-_storeBegin;i<_dataEnd-_storeBegin+1;i++)
            {
                tem[k]=_storeBegin[i];
                k++;
            }
        }
        _dataBegin=tem+1;
        _dataEnd=tem+k-1;
        _storeEnd=tem+size-1;
        _deleteStorage();
        _storeBegin=tem;
    }
    void _rebuildMore()
    {
        size_t NewSize=2*(_dataEnd-_dataBegin+1);
        _build(NewSize);
    }
    void _deleteStorage()
    {
        auto it=_storeBegin;
        if(it==nullptr)return;
        else
        {
            auto itEnd=_storeEnd+1;
            for(;it!=itEnd;it++)
            {
                it->~T();
            }
            operator delete(_storeBegin);
        }
    }
public:
	/**
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	class const_iterator;
	class iterator {
	private:
		/**
		 * add data members
		 * just add whatever you want.
		 */
		 int _header=1;//1向后，-1向前
		 vector* _father=nullptr;
		 T* _where=nullptr;
	public:
		/**
		 *
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		iterator(vector* father=nullptr,T* where=nullptr,int header=1):_header(header),_father(father),_where(where) {	}
		iterator(const iterator &o):_header(o._header),_father(o._father),_where(o._where){}
		iterator operator+(const int &n) const {
		    int __pos=_where-_father->_dataBegin+n*_header;
            if(__pos<-1+(1+_header)/2 || __pos>(_father->_dataEnd-_father->_dataBegin)+(1+_header)/2)throw invalid_iterator();
            else{
                iterator ans(*this);
                ans._where+=n*_header;
                return ans;
            }
		}
		iterator operator-(const int &n) const {
			return ((*this)+(-n));
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
            if((this->_father)!=rhs._father)throw invalid_iterator();
            else return _where-rhs._where;
		}
		iterator& operator+=(const int &n) {
            (*this)=(*this)+n;
            return *this;
		}
		iterator& operator-=(const int &n) {
			return ((*this)+=(-n));
		}
		/**
		 *  iter++
		 */
		iterator operator++(int) {
		    iterator ans(*this);
            (*this)+=1;
		    return ans;
		}
		/**
		 *  ++iter
		 */
		iterator& operator++() {
            return((*this)+=1);
		}
		/**
		 *  iter--
		 */
		iterator operator--(int) {
            iterator ans(*this);
            (*this)+=-1;
            return ans;
		}
		/**
		 *  --iter
		 */
		iterator& operator--() {
            return((*this)+=-1);
		}
		/**
		 *
		 */
		T& operator*() const{
            if(_father==nullptr || _where>_father->_dataEnd || _where < _father->_dataBegin)throw invalid_iterator();
            else return *_where;
		}
		/**
		 *
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const {
            if(_header==rhs._header && _father==rhs._father && _where==rhs._where)return true;
            else return false;
		}
		bool operator==(const const_iterator &rhs) const {
            if(_header==rhs._header && _father==rhs._father && _where==rhs._where)return true;
            else return false;
		}
		/**'
		 *
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
		    return !((*this)==rhs);
		}
		bool operator!=(const const_iterator &rhs) const {
            return !((*this)==rhs);
		}
	};
	/**
	 *
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator {
    private:
        /**
         * add data members
         * just add whatever you want.
         */
        const int _header=1;//1向后，-1向前
        const vector* _father;
        const T* _where=nullptr;
    public:
        /**
         *
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        const_iterator(const vector* father=nullptr,T* where=nullptr,int header=1):_header(header),_father(father),_where(where) {	}
        const_iterator(const const_iterator &o):_header(o._header),_father(o._father),_where(o._where){}
        const_iterator operator+(const int &n) const {
            int __pos=_where-_father->_dataBegin+n*_header;
            if(__pos<-1+(1+_header)/2 || __pos>(_father->_dataEnd-_father->_dataBegin)+(1+_header)/2)throw invalid_iterator();
            else
            {
                const_iterator ans(*this);
                ans._where+=n*_header;
                return ans;
            }
        }
        const_iterator operator-(const int &n) const {
            return ((*this)+(-n));
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            if((*this)!=rhs)throw invalid_iterator();
            else return _where-rhs._where;
        }
        const_iterator& operator+=(const int &n) {
            int __pos=_where-_father->_dataBegin+n*_header;
            if(__pos<-1+(1+_header)/2 || __pos>(_father->_dataEnd-_father->_dataBegin)+(1+_header)/2)throw invalid_iterator();
            _where+=n*_header;
            return *this;
        }
        const_iterator& operator-=(const int &n) {
            int __pos=_where-_father->_dataBegin-n*_header;
            if(__pos<-1+(1+_header)/2 || __pos>(_father->_dataEnd-_father->_dataBegin)+(1+_header)/2)throw invalid_iterator();
            _where-=n*_header;
            return *this;
        }
        /**
         *  iter++
         */
        const_iterator operator++(int) {
            const_iterator ans(*this);
            (*this)+=1;
            return ans;
        }
        /**
         *  ++iter
         */
        const_iterator& operator++() {
            return((*this)+=1);
        }
        /**
         *  iter--
         */
        const_iterator operator--(int) {
            const_iterator ans(*this);
            (*this)+=-1;
            return ans;
        }
        /**
         *  --iter
         */
        const_iterator& operator--() {
            return((*this)+=-1);
        }
        /**
         *
         */
        const T& operator*() const{
            if(_father==nullptr || _where>_father->_dataEnd || _where < _father->_dataBegin)throw invalid_iterator();
            else return *_where;
        }
        /**
         *
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            if(_header==rhs._header && _father==rhs._father && _where==rhs._where)return true;
            else return false;
        }
        bool operator==(const const_iterator &rhs) const {
            if(_header==rhs._header && _father==rhs._father && _where==rhs._where)return true;
            else return false;
        }
        /**'
         *
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return !((*this)==rhs);
        }
        bool operator!=(const const_iterator &rhs) const {
            return !((*this)==rhs);
        }
	};
	/**
	 * Constructs
	 * AtLeast two: default constructor, copy constructor
	 */
	vector() {}
	vector(const vector &other) {
	    int n=other._storeEnd-other._storeBegin;
	    _storeBegin=new T[n+1];
	    _storeEnd=_storeBegin+n;
	    _dataBegin=(other._dataBegin-other._storeBegin)+_storeBegin;
	    _dataEnd=(other._dataEnd-other._storeBegin)+_storeBegin;
	    for(int i=other._dataBegin-other._storeBegin;i<other._dataEnd-other._storeBegin+1;i++)
        {
	        _storeBegin[i]=other._storeBegin[i];
        }
	}
	/**
	 * Destructor
	 */
	~vector() {
	    _deleteStorage();
	}
	/**
	 * Assignment operator
	 */
	vector &operator=(const vector &other) {
        if(&other==this)return *this;
        else
        {
            _deleteStorage();
            int n=other._storeEnd-other._storeBegin;
            _storeBegin=new T[n+1];
            _storeEnd=_storeBegin+n;
            _dataBegin=(other._dataBegin-other._storeBegin)+_storeBegin;
            _dataEnd=(other._dataEnd-other._storeBegin)+_storeBegin;
            for(int i=other._dataBegin-other._storeBegin;i<other._dataEnd-other._storeBegin+1;i++)
            {
                _storeBegin[i]=other._storeBegin[i];
            }
        }
        return *this;
	}
	/**
	 *
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 */
	T & at(const size_t &pos) {
        if(pos<0 || pos>_dataEnd-_dataBegin)throw index_out_of_bound();
        else return *(_dataBegin+pos);
	}
	const T & at(const size_t &pos) const {
        if(pos<0 || pos>_dataEnd-_dataBegin)throw index_out_of_bound();
        else return *(_dataBegin+pos);
	}
	/**
	 *
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T & operator[](const size_t &pos) {
        if(pos<0 || pos>_dataEnd-_dataBegin)throw index_out_of_bound();
        else return *(_dataBegin+pos);
	}
	const T & operator[](const size_t &pos) const {
        if(pos<0 || pos>_dataEnd-_dataBegin)throw index_out_of_bound();
        else return *(_dataBegin+pos);
	}
	/**
	 *
	 * access the first element.
	 * throw container_is_empty if size == 0
	 */
	const T & front() const {
        if(_dataEnd<_dataBegin)throw container_is_empty();
        else return *_dataBegin;
	}
	/**
	 *
	 * access the last element.
	 * throw container_is_empty if size == 0
	 */
	const T & back() const {
        if(_dataEnd<_dataBegin)throw container_is_empty();
        else return *_dataEnd;
	}
	/**
	 *
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
	    iterator ans(this,_dataBegin,1);
	    return ans;
	}
	const_iterator rbegin() const {
        const_iterator ans(this,_dataEnd,-1);
        return ans;
	}
    const_iterator cbegin() const {
        const_iterator ans(this,_dataBegin,1);
        return ans;
    }
	/**
	 *
	 * returns an iterator to the end.
	 */
	iterator end() {
	    iterator ans(this,_dataEnd+1,1);
	    return ans;
	}
	const_iterator rend() const {
	    const_iterator ans(this,_dataBegin-1,-1);
	    return ans;
	}
    const_iterator cend() const {
        const_iterator ans(this,_dataEnd+1,1);
        return ans;
    }
	/**
	 * checks whether the container is empty
	 */
	bool empty() const {
	    if(_dataBegin==nullptr)return true;
        else if(_dataBegin==_dataEnd)return false;
	}
	/**
	 * returns the number of elements
	 */
	size_t size() const {
	    if(_dataBegin==nullptr)return 0;
	    else return _dataEnd-_dataBegin+1;
	}
	/**
	 *
	 * clears the contents
	 */
	void clear() {
	    _dataEnd=_dataBegin-1;
	}
	/**
	 *
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) {
        if(_storeBegin==nullptr)
        {
            _build();
        }
        int p=pos-this->begin();
        if(_dataEnd==_storeEnd)_rebuildMore();
        int base=_dataBegin-_storeBegin;
        for(int i=_dataEnd-_dataBegin;i>=p;i--)
        {
            _storeBegin[base+i+1]=_storeBegin[base+i];
        }
        _dataEnd++;
        _storeBegin[base+p]=value;
        iterator ans(this,_storeBegin+base+p,1);
        return ans;
	}
	/**
	 *
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value
	 * returns an iterator pointing to the inserted value.
	 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	iterator insert(const size_t &ind, const T &value) {
        if(_storeBegin==nullptr)
        {
            _build();
        }
        if(ind>_dataEnd-_dataBegin+1)throw index_out_of_bound();
        int p=ind;
        if(_dataEnd==_storeEnd)_rebuildMore();
        int base=_dataBegin-_storeBegin;
        for(int i=_dataEnd-_dataBegin;i>=p;i--)
        {
            _storeBegin[base+i+1]=_storeBegin[base+i];
        }
        _dataEnd++;
        _storeBegin[base+p]=value;
        iterator ans(this,_storeBegin+base+p,1);
        return ans;
	}
	/**
	 *
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
	    int p=(pos-this->begin())+_dataBegin-_storeBegin;
	    T* _p=_storeBegin+p;
	    for(;_p!=_dataEnd;_p++)
        {
            (*_p)=*(_p+1);
        }
	    _dataEnd--;
	    _p=_storeBegin+p;
	    if(_p>_dataEnd)return this->end();
	    else
        {
	        iterator ans(this,_p,1);
	        return ans;
        }
	}
	/**
	 *
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw index_out_of_bound if ind >= size
	 */
	iterator erase(const size_t &ind) {
	    if(ind>=_dataEnd-_dataBegin+1)throw index_out_of_bound();
        int p=(ind)+_dataBegin-_storeBegin;
        T* _p=_storeBegin+p;
        for(;_p!=_dataEnd;_p++)
        {
            (*_p)=*(_p+1);
        }
        _dataEnd--;
        _p=_storeBegin+p;
        if(_p>_dataEnd)return this->end();
        else
        {
            iterator ans(this,_p,1);
            return ans;
        }
	}
	/**
	 * todo
	 * adds an element to the end.
	 */
	void push_back(const T &value) {
        if(_storeBegin==nullptr)
        {
            _build();
        }
        if(_dataEnd==_storeEnd)_rebuildMore();
        _dataEnd++;
        new(_dataEnd) T(value);
	}
	/**
	 * todo
	 * remove the last element from the end.
	 * throw container_is_empty if size() == 0
	 */
	void pop_back() {
	    if(_dataEnd<_dataBegin)throw container_is_empty();
	    _dataEnd--;
	}
};


}

#endif
