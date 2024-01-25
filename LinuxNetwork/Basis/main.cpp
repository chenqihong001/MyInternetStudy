#include <iostream>
#include <vector>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

// 序列化向量
template <typename T>
void SerializeVector(const std::vector<T> &vec, const std::string &filename)
{
    std::ofstream ofs(filename, std::ios::binary);
    boost::archive::binary_oarchive ar(ofs);
    ar << vec;
}

// 反序列化向量
template <typename T>
void DeserializeVector(std::vector<T> &vec, const std::string &filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    boost::archive::binary_iarchive ar(ifs);
    ar >> vec;
}

int main()
{
    // 创建一个 std::vector
    std::vector<int> originalVector = {1, 2, 3, 4, 5};

    // 序列化向量到文件
    SerializeVector(originalVector, "serialized_vector.dat");

    // 清空向量，模拟重新加载
    originalVector.clear();

    // 反序列化向量
    DeserializeVector(originalVector, "serialized_vector.dat");

    // 输出还原后的向量
    std::cout << "Deserialized Vector: ";
    for (const auto &elem : originalVector)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
