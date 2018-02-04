// Minimal class to replace std::vector
template<typename Data>
struct Vector
{
	size_t d_size; // Stores no. of actually stored objects
	size_t d_capacity; // Stores allocated capacity
	Data *d_data; // Stores data

	Vector() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor

	Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0)
	{
		d_data = (Data *)malloc(d_capacity * sizeof(Data));
		memcpy(d_data, other.d_data, d_size * sizeof(Data));
	}; // Copy constuctor

	~Vector()
	{
		free(d_data);
	}; // Destructor

	Vector &operator=(Vector const &other)
	{
		free(d_data);
		d_size = other.d_size;
		d_capacity = other.d_capacity;
		d_data = (Data *)malloc(d_capacity * sizeof(Data));
		memcpy(d_data, other.d_data, d_size * sizeof(Data));
		return *this;
	}; // Needed for memory management

	void clear()
	{
		d_size = 0;
	}

	void erase(int index)
	{
		for (int i = index; i < d_size; ++i)
		{
			d_data[i] = d_data[i + 1]; // Copy next element left
		}

		d_size--;
	}

	int begin()
	{
		return 0;
	}

	int end()
	{
		return d_size;
	}

	void push_back(Data const &x)
	{
		d_data[d_size++] = x;
	}; // Adds new value

	size_t size() const
	{
		return d_size;
	}; // Size getter

	Data const &operator[](size_t index) const
	{
		return d_data[index];
	}; // Const getter

	Data &operator[](size_t index)
	{
		return d_data[index];
	}; // Changeable getter
};
