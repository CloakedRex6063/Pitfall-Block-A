#pragma once

// Made along with code suggestion from chatGPT
class DynamicArray
{
    Object** data;
    int size;
    int capacity;

public:
    DynamicArray(int newCapacity = 2) : size(0), capacity(newCapacity) {data = new Object*[capacity];}
    ~DynamicArray()
    {
        for(int i = 0; i < size; ++i)
        {
            delete data[i];
        }
        delete[] data;
    }

    void SetElem(Object* value, int index) const
    {
        data[index] = value;
    }
    
    void AddElem(Object* value)
    {
        if (size == capacity)
        {
            const int newCapacity = capacity + 1;
            const auto newData = new Object*[newCapacity];
            for (int i = 0; i < size; ++i)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[size++] = value;
    }

    void RemoveElemAtIndex(const int index, const bool bDelete = false)
    {
        if (index < size && index >= 0)
        {
            if (bDelete)
            {
                delete data[index];
                for (auto i = index; i < size - 1; i++)
                {
                    data[i] = data[i + 1];
                }
                size--;
                const auto newData = new Object*[size];
                for (auto i = 0; i < size; i++)
                {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                return;
            }
            if (index < size && index >= 0)
            {
                delete data[index];
                data[index] = nullptr;
            }
        }
    }

    int RemoveElem(const Object* obj, const bool bDelete = false)
    {
        for (auto i = 0; i < size; i++)
        {
            if (data[i] == obj)
            {
                RemoveElemAtIndex(i,bDelete);
                return i;
            }
        }
        return -1;
    }

    Object* AtIndex(int index) const
    {
        if (index < size && index > -1)
        {
            return data[index];
        }
        throw exception("Index out of bounds");
    }

    template <typename T>
    T** FindObjectsOfType(int& num) const
    {
        T** newArray = new T*[size];
        for (auto i = 0; i < size; i++)
        {
            if (dynamic_cast<T*>(data[i]))
            {
                newArray[num] = dynamic_cast<T*>(data[i]);
                num++;
            }
        }
        T** array = new T*[num];
        for (auto i = 0; i < num; i++)
        {
            array[i] = newArray[i];
        }
        return array;
    }

    template <typename T>
    T* FindObjectOfType() const
    {
        for (auto i = 0; i < size; i++)
        {
            if (dynamic_cast<T*>(data[i]))
            {
                return dynamic_cast<T*>(data[i]);
            }
        }
        return nullptr;
    }

    int GetSize() const {return size;}

    Object** GetArray() const {return data;}
};
