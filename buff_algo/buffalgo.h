#ifndef __BUFFALGO_H__
#define __BUFFALGO_H__

namespace juho {

	// shared pointer or unique pointer ??
	// swap - Effective C++
	// swap for triple buffering
	// internal swap for double buffering, triple buffering
	// configurable base index - OK
	// don't need dynamic capacity change
	// boundary check for debug mode
	template <typename T>
	class buffalgo1 {
		int* refcnt;
		T* data;
		T* ptr;
		int len;

	public:
		// constructor
		buffalgo1(int n, int base_idx = 0) {
			refcnt = new int;
			*refcnt = 1;
			data = new T[n];
			ptr = data - base_idx;
			len = n;
		}

		// copy constructor
		buffalgo1(const buffalgo1& other) {
			refcnt = other.refcnt;
			++(*refcnt);
			data = other.data;
			ptr = other.ptr;
			len = other.len;
		}

		// destructor
		~buffalgo1() {
			if (--(*refcnt) == 0) {
				delete[] data;
				delete refcnt;
			}
		}

		// assign operator
		buffalgo1& operator=(const buffalgo1& other) {
			if (this == &other)
				return *this;

			if (--(*refcnt) == 0) {
				delete[] data;
				delete refcnt;
			}

			refcnt = other.refcnt;
			++(*refcnt);
			data = other.data;
			ptr = other.ptr;
			len = other.len;
			return *this;
		}

		// init
		void init(T v) {
			for (int i = 0; i < len; ++i)
				data[i] = v;
		}

		// operator[]
		T& operator[](int k) {
			return ptr[k];
		}

		const T& operator[](int k) const {
			return ptr[k];
		}

		// get_ptr
		T*& get() {
			return ptr;
		}

		const T*& get() const {
			return ptr;
		}
	};

	// shared pointer
	// configurable base index
	// rectangle and triangle shaped
	// no dynamic capacity change
	// no boundary check
	template <typename T>
	class buffalgo2 {
		int* refcnt;
		T* data;
		T** rows;
		T** ptrs;
		int len;

		// triangle constructor
		buffalgo2(int n, int base_row_idx, int base_col_idx, int triangle_type, int place_holder) {
			refcnt = new int;
			*refcnt = 1;
			len = n * (n + 1) / 2;
			data = new T[len];
			rows = new T*[n];
			rows[0] = data - base_col_idx;
			if (triangle_type == 3)
				rows[0] -= (n - 1);
			switch (triangle_type) {
			case 0:
				for (int i = 1; i < n; ++i)
					rows[i] = rows[i - 1] + (n + 1 - i);
				break;
			case 1:
				for (int i = 1; i < n; ++i)
					rows[i] = rows[i - 1] + i;
				break;
			case 2:
				for (int i = 1; i < n; ++i)
					rows[i] = rows[i - 1] + (n - i);
				break;
			default:
				for (int i = 1; i < n; ++i)
					rows[i] = rows[i - 1] + (i + 1);
				break;
			}
			ptrs = rows - base_row_idx;
		}

	public:
		// constructor
		buffalgo2(int n, int m, int base_row_idx = 0, int base_col_idx = 0) {
			refcnt = new int;
			*refcnt = 1;
			len = n * m;
			data = new T[len];
			rows = new T*[n];
			rows[0] = data - base_col_idx;
			for (int i = 1; i < n; ++i)
				rows[i] = rows[i - 1] + m;
			ptrs = rows - base_row_idx;
		}

		// copy constructor
		buffalgo2(const buffalgo2& other) {
			refcnt = other.refcnt;
			++(*refcnt);
			data = other.data;
			rows = other.rows;
			ptrs = other.ptrs;
			len = other.len;
		}

		// destructor
		~buffalgo2() {
			if (--(*refcnt) == 0) {
				delete[] rows;
				delete[] data;
				delete refcnt;
			}
		}

		// assign operator
		buffalgo2& operator=(const buffalgo2& other) {
			if (this == &other)
				return *this;

			if (--(*refcnt) == 0) {
				delete[] rows;
				delete[] data;
				delete refcnt;
			}

			refcnt = other.refcnt;
			++(*refcnt);
			data = other.data;
			rows = other.rows;
			ptrs = other.ptrs;
			len = other.len;
			return *this;
		}

		// init
		void init(T v) {
			for (int i = 0; i < len; ++i)
				data[i] = v;
		}

		// operator[]
		T*& operator[](int k) {
			return ptrs[k];
		}

		const T*& operator[](int k) const {
			return ptrs[k];
		}

		// get_ptr
		T**& get() {
			return ptrs;
		}

		const T**& get() const {
			return ptrs;
		}

		// static constructors
		static buffalgo2 rectangle(int n, int m, int base_row_idx = 0, int base_col_idx = 0) {
			return buffalgo2(n, m, base_row_idx, base_col_idx);
		}

		static buffalgo2 square(int n, int base_idx = 0) {
			return buffalgo2(n, n, base_idx, base_idx);
		}

		static buffalgo2 square(int n, int base_row_idx, int base_col_idx) {
			return buffalgo2(n, n, base_row_idx, base_col_idx);
		}

		static buffalgo2 triangle_upper_left(int n, int base_idx = 0) {
			return buffalgo2(n, base_idx, base_idx, 0, 0);
		}

		static buffalgo2 triangle_upper_left(int n, int base_row_idx, int base_col_idx) {
			return buffalgo2(n, base_row_idx, base_col_idx, 0, 0);
		}

		static buffalgo2 triangle_lower_left(int n, int base_idx = 0) {
			return buffalgo2(n, base_idx, base_idx, 1, 0);
		}

		static buffalgo2 triangle_lower_left(int n, int base_row_idx, int base_col_idx) {
			return buffalgo2(n, base_row_idx, base_col_idx, 1, 0);
		}

		static buffalgo2 triangle_upper_right(int n, int base_idx = 0) {
			return buffalgo2(n, base_idx, base_idx, 2, 0);
		}

		static buffalgo2 triangle_upper_right(int n, int base_row_idx, int base_col_idx) {
			return buffalgo2(n, base_row_idx, base_col_idx, 2, 0);
		}

		static buffalgo2 triangle_lower_right(int n, int base_idx = 0) {
			return buffalgo2(n, base_idx, base_idx, 3, 0);
		}

		static buffalgo2 triangle_lower_right(int n, int base_row_idx, int base_col_idx) {
			return buffalgo2(n, base_row_idx, base_col_idx, 3, 0);
		}
	};
}

#endif // __BUFFALGO_H__
