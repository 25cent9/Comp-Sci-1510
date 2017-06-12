/*
  Programmer: Innocent Niyibizi
  File: mystringmap.hpp
  Date: 4/18/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: hpp file for an implementation of a string hash-table
*/

template <typename T>
MyStringMap<T>::MyStringMap()
{
  m_max = 69;
  m_size = 0;
  EMPTYKEY = "INNOCNET IS COOL";
  map = new KeyValue<T>[m_max];
  for(unsigned int i = 0; i < m_max; i++)
    map[i].setKey(EMPTYKEY);
}

template <typename T>
MyStringMap<T>::MyStringMap(const MyStringMap<T>& cpy)
{
  m_max = 69;
  m_size = 0;
  EMPTYKEY = "INNOCNET IS COOL";
  map = new KeyValue<T>[m_max];
  for(unsigned int i = 0; i < m_max; i++)
  {
    map[i].setKey(EMPTYKEY);
    map[i].active = false;
  }
  *this = cpy;
}

template <typename T>
MyStringMap<T>::~MyStringMap()
{
  delete [] map;
  m_size = 0;
}

template <typename T>
bool MyStringMap<T>::isEmpty() const
{
  if(m_size == 0)
    return true;
  else
    return false;
}

template <typename T>
int MyStringMap<T>::size() const
{
  return m_size;
}

template <typename T>
const T& MyStringMap<T>::valueOf(const string& key) const throw ( Oops )
{
  int start, count=1;
  int currPos = start = hash(key);
  while((key != map[currPos].getKey()) && (EMPTYKEY != map[currPos].getKey()))
  {
    currPos = (start + count) % m_max;
    count++;
  }
  if(map[currPos].getKey() == key)
  {
    return map[currPos].getValue();
  }
  else
  {
    throw Oops ("Key Not Found!!");
  }
}

template <typename T>
void MyStringMap<T>::clear()
{
  delete [] map;
  m_max = 69;
  m_size = 0;
  EMPTYKEY = "INNOCNET IS COOL";
  map = new KeyValue<T>[m_max];
  for(unsigned int i = 0; i < m_max; i++)
  {
    map[i].setKey(EMPTYKEY);
    map[i].active = false;
  }
  return;
}

template <typename T>
void MyStringMap<T>::insert(const string& key, const T& val)
{
  int hashKey = hash(key);
  KeyValue<T> entry(key, val);
  if(map[hashKey].getKey()==EMPTYKEY)
  {
    map[hashKey] = entry;
    map[hashKey].active = true;
    if(m_size+1 > (m_max/4))
    {
      grow();
      m_size++;
    }
    else
      m_size++;
  }
  else if(map[hashKey].getKey()==key)
  {
    map[hashKey].setValue(val);
  }
  else
  {
    int start, count=1;
    int currPos = start = hashKey;
    bool replaced = false;
    while(map[currPos].getKey() != EMPTYKEY)
    {
      if(map[currPos].getKey()==key)
      {
        map[currPos] = entry;
        replaced = true;
        break;
      }
      currPos = (start + count) % m_max;
      count++;
    }
    if(!replaced)
    {
      map[currPos] = entry;
      map[currPos].active = true;
      m_size++;
    }
  }
  return;
}

template <typename T>
void MyStringMap<T>::remove(const string& k)
{
  int hashVal = hash(k);
  int start, count=1;
  int currPos = start = hashVal;
  if(map[hashVal].getKey()!=k)
  {
    while(map[currPos].getKey() != EMPTYKEY)
    {
      if(map[currPos].getKey()==k)
      {
        map[hashVal].setKey(EMPTYKEY);
        map[hashVal].active = false;
        m_size--;
        break;
      }
      currPos = (start + count) % m_max;
      count++;
    }
  }
  else
  {
    map[hashVal].setKey(EMPTYKEY);
    map[hashVal].active = false;
    m_size--;
  }
  return;
}

template <typename T>
void MyStringMap<T>::print() const
{
  for(unsigned int i = 0; i<m_max; i++)
  {
    if(map[i].getKey() != EMPTYKEY && map[i].active)
      cout<<"< "<<map[i].getKey()<<", "<<map[i].getValue()<<" >"<<endl;
  }
  return;
}

template <typename T>
int MyStringMap<T>::hash(const string &s) const
{
  unsigned int total=0;
  for(unsigned int i = 0; i<s.length(); i++)
  {
    total+=s[i];
  }
  return total%m_max;
}

template <typename T>
int MyStringMap<T>::reHash(const string &s, const int MAX) const
{
  unsigned int total=0;
  for(unsigned int i = 0; i<s.length(); i++)
  {
    total+=s[i];
  }
  return total%MAX;
}

template <typename T>
void MyStringMap<T>::grow()
{
  unsigned int newSize = m_max*2;
  KeyValue<T>* newMap = new KeyValue<T>[newSize];
  for(unsigned int i = 0; i < newSize; i++)
  {
    newMap[i].setKey(EMPTYKEY);
    newMap[i].active = false;
  }
  for(unsigned int i = 0; i<m_max; i++)
  {
    KeyValue<T> entry = map[i];
    if(map[i].getKey()!=EMPTYKEY)
    {
      newMap[reHash(entry.getKey(), newSize)] = entry;
    }
  }
  m_max = newSize;
  delete []map;
  map = newMap;
  return;
}

template <typename T>
MyStringMap<T>& MyStringMap<T>::operator=(const MyStringMap<T>& rhs)
{
  delete [] map;
  m_size = rhs.size();
  m_max = rhs.max();
  map = new KeyValue<T>[m_max];
  for(unsigned int i = 0; i<m_max; i++)
  {
    map[i] = rhs.map[i];
  }
  return *this;
}
