#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

#include <iostream>
#include <memory>

namespace qh
{
    template<class T>
    class vector {
	public:
		typedef T *iterator;


    public:
        //ctor
        vector()
			: data_(NULL), finish_(NULL), end_of_storage_(NULL), size_(0)
        {

        }

        explicit vector( size_t n, const T& value = T())
        {
			data_ = alloc_.allocate(n);
			finish_ = end_of_storage_ = data_ + n;

			std::uninitialized_fill(data_, finish_, value);
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
			if (this == &rhs)
			{
				return *this;
			}
			// �ͷ�ԭ�����ڴ�
			free_memory();

			// ��ֵ
			data_   = alloc_.allocate(rhs.finish_ - rhs.data_);
			finish_ = end_of_storage_ = std::uninitialized_copy(rhs.data_, rhs.finish_, data_);
			return *this;
        }

        //dtor
        ~vector()
        {
			// �ͷ��ڴ�
			free_memory();
        }

        //get
        size_t size() const
        {
			return (finish_ - data_);
        }
        size_t capacity() const
		{
			return (end_of_storage_ - data_);
		}

        // set & get
        T& operator[](size_t index);

        // set
        void push_back(const T& element);
        void pop_back();
		void resize(size_t new_size, const T& value);
		void reserve(size_t new_capacity);
        void clear();
        bool empty();

		// iterator

    private:
        T*       data_;            // ��Ԫ��
		iterator finish_;          // ĩβԪ�ص���һ��
		iterator end_of_storage_;  // capacity

		std::allocator<T> alloc_;  // �ڴ������

		void free_memory();        // �ͷ��ڴ�

        size_t  size_;
		// size_t  capacity_;
    };

	template<class  T>
	void vector<T>::free_memory()
	{
		if (data_)
		{
			iterator it = finish_;
			while (it != data_)
			{
				alloc_.destroy(--it);
			}
			alloc_.deallocate(data_, finish_ - data_);
		}
		data_ = finish_ = end_of_storage_ = NULL;

	}

	// set & get
	template<class  T>
	T& vector<T>::operator[](size_t index)
	{
		return data_[index];
		/*
		if (size_ > 0) {
			if (index >= 0 && index < size_) {
				return data_[index];
			}
			else
			{
				throw exception("Out of range");
			}
		}
		else
		{
			throw exception("Out of range");
		}
		*/
	}

	// set
	template<class  T>
	void vector<T>::push_back(const T& element)
	{
		if (finish_ == end_of_storage_)
		{
			// vector��������Ϊ2��
			size_t new_size_     = 2 * (finish_ - data_);
			iterator new_data_   = alloc_.allocate(new_size_);
			iterator new_finish_ = std:: uninitialized_copy(data_, finish_, new_data_);

			// �ͷ��ڴ�
			free_memory();

			// ����iterator
			data_                = new_data_;
			finish_              = new_finish_;
			end_of_storage_      = data_ + new_size_;
		}
		alloc_.construct(finish_++, element);
		std::cout << "push_back:  " << element << std::endl;
	}

	template<class  T>
	void vector<T>::pop_back()
	{
		// If is empty vector, then return
		if (size() == 0) {
			return;
		}

		alloc_.destroy(--finish_);

		std::cout << "pop_back:  " << *finish_ << std::endl;

		//alloc_.deallocate(it, 1);

	}

	template<class  T>
	void vector<T>::resize(size_t new_size, const T& value)
	{
		if (size() == 0)
		{
			data_   = alloc_.allocate(new_size);
			finish_ = end_of_storage_ = data_ + new_size;

			std::uninitialized_fill(data_, finish_, value);
		}
		else if (new_size > size())
		{
			if (new_size > capacity())
			{
				free_memory();

				data_   = alloc_.allocate(new_size);
				finish_ = end_of_storage_ = data_ + new_size;

				std::uninitialized_fill(data_, finish_, value);
			}
			else
            {
                size_t t = new_size - size();
                finish_ += t;
            }
		}
		else  // new_size <= size()
        {
            size_t t = size() - new_size;
            finish_ -= t;
            std::uninitialized_fill(data_, finish_, value);
        }

		std::cout << "resize:  " << new_size << std::endl;
	}

	template<class  T>
	void vector<T>::reserve(size_t new_capacity)
	{
	    if (new_capacity > capacity())
        {
            // vector��������Ϊ2��
			size_t new_size_     = 2 * new_capacity;
			iterator new_data_   = alloc_.allocate(new_size_);
			iterator new_finish_ = std:: uninitialized_copy(data_, finish_, new_data_);

			// �ͷ��ڴ�
			free_memory();

			// ����iterator
			data_                = new_data_;
			finish_              = new_finish_;
			end_of_storage_      = data_ + new_size_;
        }

		std::cout << "reserve:  " << new_capacity << std::endl;
	}

	template<class  T>
	void vector<T>::clear()
	{
		free_memory();
	}

	template<class  T>
	bool vector<T>::empty()
	{
		return size() == 0;
	}
}

#endif


