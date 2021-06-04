# class BinarySearchTree<T>
Для работы данного класса необходимо, чтобы к типу T было возможно применить функцию std::hash. Так же для возможности перевода дерева в строку необходимо перегрузить у класса T operator<<. Ниже приведен пример как это можно сделать для произвольного класса на примере std::complex.

	namespace std
	{  
		//Перегрузка operator<< для возможности вывода в строку
		template<typename T>
		std::ostream& operator<<(std::ostream& out, const std::complex<T>& comp)
		{
			out << "(" << comp.real() << ", " << comp.imag() << ")";
			return out;
		}

		//Перегрузка у класса std::hash operator() для взятия хэша. 
		//Объединение двух хэшей происходит путем побитового сдвига и взятия операции XOR. 
		//Так же есть возможность скомбинировать два хэш значения с помощью функции has_combine из библиотеки boost. 
		template<typename T>
		struct hash<std::complex<T>>
		{
			std::size_t operator()(const std::complex<T>& comp) const
			{
				std::size_t h1 = hash<T>{}(comp.real());
				std::size_t h2 = hash<T>{}(comp.imag());
				return h1 ^ (h2 << 1);
			}
		};
	}
