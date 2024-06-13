#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <unordered_map>


std::string get_lexem(const std::string& line, size_t index)
{
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	std::string token;
	while (iss >> token)
	{
		tokens.push_back(token);
	}
	if (index >= 0 && index <= tokens.size())
	{
		return tokens[index];
	}
	else
	{
		return "index out of range";
	}
}

std::int16_t get_lexem_convertInt(const std::string& lb)
{
	std::istringstream iss(lb);
	int lb_int;
	iss >> lb_int;
	return lb_int;
}

std::string convert_toupper(std::string& name_array)
{
	for (char &c : name_array)
	{
		c = toupper(c);
	}
	return name_array;
}

void create_array(std::string name, std::map<std::string, std::vector<int>> arrays)
{
	arrays[name] = std::vector<int>();
}

int main()
{
	system("color F0");
	std::map<std::string, std::vector<int>> arrays;
	std::string line;
	std::ifstream instr("instruction.txt");
	if (instr.is_open())
	{
		std::string name_array = "A";
		std::string name_array2 = "B";
		create_array(name_array, arrays);
		create_array(name_array2, arrays);
		while (std::getline(instr, line))
		{
			/*line.pop_back();*/

			if (get_lexem(line,0) == "Load")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				auto name_input_file = get_lexem(line, 2);
				name_input_file.pop_back();
				std::ifstream input_file(name_input_file);
				if (instr.is_open())
				{
					int number;
					while (input_file >> number)
					{
						arrays[name_array].push_back(number);
					}
				}
				else 
				{
					std::cout << "Unable to open file";
				}

				std::cout << "Load - array A with numbers from the in.txt file: ";
				for (int num: arrays[name_array])
				{
					std::cout << num << " ";
				}
				input_file.close();
				std::cout << "\n";
			}
			if (get_lexem(line, 0) == "Save")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				auto name_out_file = get_lexem(line, 2);
				name_out_file.pop_back();
				std::ofstream outFile(name_out_file);

				if (outFile.is_open())
				{
					for (int item : arrays[name_array])
					{
						outFile << item << " ";
					}
					outFile.close();
				}
				else
				{
					std::cout << "Unable to open file";
				}
				std::cout << "Save - array elements are uploaded to the in2.txt file: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}
			if (get_lexem(line, 0) == "Rand")
			{
				srand(time(NULL));
				name_array = get_lexem(line, 1);
				std::string count_str = get_lexem(line, 2);
				std::string lb = get_lexem(line, 3);
				std::string rb = get_lexem(line, 4);
				name_array.pop_back();
				count_str.pop_back();
				lb.pop_back();
				rb.pop_back();
				auto count_int = get_lexem_convertInt(count_str);
				for (int i = 0; i < count_int; ++i)
				{
					std::int16_t random_number = get_lexem_convertInt(lb) + rand() % get_lexem_convertInt(rb);
					arrays[name_array].push_back(random_number);
				}
				
				std::cout << "Rand - array A is filled with random elements from the segment [ " <<lb <<" , "<< rb <<" ]in the number of " << count_str <<" pieces: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}
			if (get_lexem(line, 0) == "Concat")
			{
				name_array = get_lexem(line, 1);
				name_array2 = get_lexem(line, 2);
				name_array.pop_back();
				name_array2.pop_back();
				convert_toupper(name_array);
				convert_toupper(name_array2);
				if (arrays[name_array2].empty()) {
					std::cout << "Array B is empty, add the numbers 1 and 2 to it to check " << std::endl;
					arrays[name_array2].push_back(1);
					arrays[name_array2].push_back(2);
				}
				arrays[name_array].insert(arrays[name_array].end(), arrays[name_array2].begin(), arrays[name_array2].end());
				
				std::cout << "Concat - array A = A + B: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}
			if (get_lexem(line, 0)[0] == 'F')
			{
				name_array = get_lexem(line, 0)[5];
				convert_toupper(name_array);
				arrays[name_array].clear();
				std::cout << "Free - array A empty, add the numbers 39, 29, 19, 49, 39, 9, 78, 87, 33 to itt to check: ";
				arrays[name_array].push_back(39);
				arrays[name_array].push_back(29);
				arrays[name_array].push_back(19);
				arrays[name_array].push_back(49);
				arrays[name_array].push_back(39);
				arrays[name_array].push_back(9);
				arrays[name_array].push_back(78);
				arrays[name_array].push_back(87);
				arrays[name_array].push_back(33);
				
				std::cout << "A - ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}
			if (get_lexem(line, 0) == "Remove")
			{
				std::string name_array = get_lexem(line, 1);
				name_array.pop_back();
				convert_toupper(name_array);

				auto start_index = get_lexem(line, 2);
				auto elements_to_remove = get_lexem(line, 3);
				start_index.pop_back();
				elements_to_remove.pop_back();
				auto start_indexInt = get_lexem_convertInt(start_index);
				auto elements_to_removeInt = get_lexem_convertInt(elements_to_remove);

				arrays[name_array].erase(arrays[name_array].begin() + start_indexInt, arrays[name_array].begin() + start_indexInt + elements_to_removeInt);
				std::cout << "Remove - removing 7 elements from array A, starting with the second index: ";
				for (int item : arrays[name_array]) 
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}
			if (get_lexem(line, 0) == "Copy")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();

				name_array2 = get_lexem(line, 4);
				name_array2.pop_back();
				convert_toupper(name_array2);

				auto start_index = get_lexem(line, 2);
				start_index.pop_back();
				auto start_indexInt = get_lexem_convertInt(start_index);

				auto end_index = get_lexem(line, 3);
				end_index.pop_back();
				auto end_indexInt = get_lexem_convertInt(end_index);
				if (arrays[name_array].size() < 10)
				{
					std::cout << "Copy - There are no 10 elements in array A, add ten elements from 1 to 10 \n";
					for (int i = 1; i < 11; ++i)
					{
						arrays[name_array].push_back(i);
					}
				}
				std::cout << "Array A: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
				std::copy(arrays[name_array].begin() + start_indexInt, arrays[name_array].begin() + end_indexInt + 1, std::back_inserter(arrays[name_array2]));
				std::cout << "Array B after copying: ";
				for (int item : arrays[name_array2])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}

			if (get_lexem(line, 0) == "Sort")
			{
				name_array = get_lexem(line, 1)[0];
				convert_toupper(name_array);
				auto n = sizeof(arrays[name_array]) / sizeof(arrays[name_array][0]);

				if (get_lexem(line, 1)[1] == '+')
				{
					std::sort(arrays[name_array].begin(), arrays[name_array].end());
				}
				if (get_lexem(line, 1)[1] == '-')
				{
					std::sort(arrays[name_array].begin(), arrays[name_array].end(), std::greater<int>());
				}
				std::cout << "Sort - array A after sorting: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}

			if (get_lexem(line, 0) == "Permute")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();

				std::random_device rand;
				std::mt19937 g(rand());

				std::shuffle(arrays[name_array].begin(), arrays[name_array].end(), g);
				std::cout << "Permute - Permutation of elements in array A in random order: ";
	
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}

			if (get_lexem(line, 0) == "Intersect")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				convert_toupper(name_array);
				name_array2 = get_lexem(line, 2);
				name_array2.pop_back();
				convert_toupper(name_array2);
				std::cout << "Intersect - save the intersection of array A and B to array A:\n";
				std::cout << "Array A: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "Array B: ";
				for (int item : arrays[name_array2])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";

				/*arrays[name_array2].push_back(1);
				arrays[name_array2].push_back(2);
				arrays[name_array2].push_back(5);
				arrays[name_array2].push_back(3);
				arrays[name_array2].push_back(2);
				arrays[name_array2].push_back(87);
				arrays[name_array2].push_back(3);
				arrays[name_array2].push_back(4);*/

				std::vector<int> result;
				std::unordered_set<int> unique_set_name_array2(arrays[name_array2].begin(), arrays[name_array2].end());
				
				for (auto n : arrays[name_array])
				{
					if (unique_set_name_array2.find(n) != unique_set_name_array2.end())
					{
						result.push_back(n);
					}
				}

				std::unordered_set<int> unique_set_result(result.begin(), result.end());

				for (auto i : unique_set_result)
				{
					arrays[name_array].push_back(i);
				}

				std::cout << "Array A: ";
				for (int i : arrays[name_array])
				{
					std::cout << i << " ";
				}
				std::cout << "\n";
			}

			if (get_lexem(line, 0) == "Xor")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				convert_toupper(name_array);
				name_array2 = get_lexem(line, 2);
				name_array2.pop_back();
				convert_toupper(name_array2);
				std::cout << "Xor - Let's keep the symmetric difference of arrays A and B in array A:\n";
				std::cout << "Array A: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "Array B: ";
				for (int item : arrays[name_array2])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";

				/*arrays[name_array2].push_back(1);
				arrays[name_array2].push_back(2);
				arrays[name_array2].push_back(5);
				arrays[name_array2].push_back(3);
				arrays[name_array2].push_back(2);
				arrays[name_array2].push_back(87);
				arrays[name_array2].push_back(3);
				arrays[name_array2].push_back(4);
				arrays[name_array2].push_back(30);
				arrays[name_array2].push_back(30);*/

				std::vector<int> result;
				std::unordered_set<int> unique_set_name_array2(arrays[name_array2].begin(), arrays[name_array2].end());
				std::unordered_set<int> unique_set_name_array(arrays[name_array].begin(), arrays[name_array].end());

				for (auto item : arrays[name_array])
				{
					if (unique_set_name_array2.find(item) == unique_set_name_array2.end())
					{
						result.push_back(item);
					}
				}

				for (auto item : arrays[name_array2])
				{
					if (unique_set_name_array.find(item) == unique_set_name_array.end())
					{
						result.push_back(item);
					}
				}

				for (auto item : result)
				{
					arrays[name_array].push_back(item);
				}

				std::cout << "Array A: ";
				for (int i : arrays[name_array])
				{
					std::cout << i << " ";
				}
				std::cout << "\n\n";
			}

			if (get_lexem(line, 0) == "Stat")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				convert_toupper(name_array);

				auto size = arrays[name_array].size();

				auto max_element = arrays[name_array][0];
				auto min_element = arrays[name_array][0];
				auto max_element_index = 0;
				auto min_element_index = 0;
				auto count = 0;
				auto most_frequent_element = 0;
				auto max_deviation = 0.0;


				for (int item : arrays[name_array])
				{
					if (item > max_element)
					{
						max_element = item;
						max_element_index = count;
					}
					count++;
				}

				count = 0;

				for (int item : arrays[name_array])
				{
					
					if (item < min_element)
					{
						min_element = item;
						min_element_index = count;
					}
					count++;
				}

				std::unordered_map<int, int> frequency_map;
				for (int item : arrays[name_array])
				{
					frequency_map[item]++;
				}

				int max_frequency = 0;
				for (const auto& pair : frequency_map)
				{
					if (pair.second > max_frequency)
					{
						max_frequency = pair.second;
						most_frequent_element = pair.first;
					}
				}
				double sum = 0.0;
				for (int item : arrays[name_array])
				{
					sum += item;
				}
				auto average = sum / size;

				for (int item : arrays[name_array])
				{
					double deviation = std::abs(item - average);
					if (deviation > max_deviation)
					{
						max_deviation = deviation;
					}
				}
				 
				std::cout << "Stat: \n";
				std::cout << "Size " << size << std::endl;
				std::cout << "Max element " << max_element << " (index " << max_element_index << ")" << std::endl;
				std::cout << "Min element " << min_element << " (index " << min_element_index << ")" << std::endl;
				std::cout << "Most frequent: " << most_frequent_element << std::endl;
				std::cout << "Average: " << average << std::endl;
				std::cout << "Max deviation: " << max_deviation << std::endl;
			}

			if (get_lexem(line, 0) == "Print" && get_lexem(line, 2) != "ALL;")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				convert_toupper(name_array);
				auto start_index = get_lexem(line, 2);
				start_index.pop_back();
				auto start_indexInt = get_lexem_convertInt(start_index);
				auto end_index = get_lexem(line, 3);
				end_index.pop_back();
				auto end_indexInt = get_lexem_convertInt(end_index);

				std::cout << "Print (4-16) - Output of array A elements from 4 to 16: ";
				for (int i = start_indexInt; i < end_indexInt && i < arrays[name_array].size(); ++i)
				{
					std::cout << arrays[name_array][i] << " ";
				}
				
				std::cout << "\n";
			}

			if (get_lexem(line, 0) == "Print" && get_lexem(line, 2) == "ALL;")
			{
				name_array = get_lexem(line, 1);
				name_array.pop_back();
				convert_toupper(name_array);
				std::cout << "Print - Output of array A: ";
				for (int item : arrays[name_array])
				{
					std::cout << item << " ";
				}
				std::cout << "\n";
			}
		}
	}
	instr.close();
}