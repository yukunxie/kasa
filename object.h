#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <string.h>
#include "kasa_assert.h"

enum BuiltinType
{
    TYPE_INT,
    TYPE_DECIMAL,
    TYPE_STRING,
    //--------------------------------
    TYPE_COUNT
};

class Object 
{
public:
    virtual ~Object()
    {}

    virtual BuiltinType getType() const
    {
        return m_type;
    }

    virtual std::string toString()
    {
        return "";
    }

    virtual size_t serialize(char* buffer, size_t bufferSize)
    {
        return (size_t)0;
    }

    virtual bool cmpEQ(const Object* obj) const
    {
        return this == obj;
    }

    virtual bool cmpNE(const Object* obj) const
    {
        return this == obj;
    }

    virtual bool cmpLE(const Object* obj) const
    {
        return this <= obj;
    }

    virtual bool cmpLT(const Object* obj) const
    {
        return this < obj;
    }

    virtual bool cmpGE(const Object* obj) const
    {
        return this >= obj;
    }

    virtual bool cmpGT(const Object* obj) const
    {
        return this > obj;
    }

protected:
    BuiltinType m_type;
};

class ObjectInteger: public Object
{
public:
    ObjectInteger(int value):
        m_value(value)
    {
        m_type = TYPE_INT;
    }

    virtual size_t serialize(char* buffer, size_t bufferSize)
    {
        const static size_t vsize = sizeof(m_value);
        KASA_ASSERT(bufferSize >= vsize, "buffer space is not enough");
        memcpy(buffer, (char*)&m_value, vsize);
        return vsize;
    }

    virtual std::string toString()
    {
        return std::to_string(m_value);
    }

    virtual bool cmpEQ(const Object* obj) const;
    virtual bool cmpNE(const Object* obj) const;
    virtual bool cmpLE(const Object* obj) const;
    virtual bool cmpLT(const Object* obj) const;
    virtual bool cmpGE(const Object* obj) const;
    virtual bool cmpGT(const Object* obj) const;

    int getValue() const
    {
        return m_value;
    }

    void setValue(const int&& value)
    {
        m_value = value;
    }

private:
    int m_value;
};

class ObjectDecimal: public Object
{
public:
    ObjectDecimal(double value):
        m_value(value)
    {
        m_type = TYPE_DECIMAL;
    }

    virtual bool cmpEQ(const Object* obj) const;
    virtual bool cmpNE(const Object* obj) const;
    virtual bool cmpLE(const Object* obj) const;
    virtual bool cmpLT(const Object* obj) const;
    virtual bool cmpGE(const Object* obj) const;
    virtual bool cmpGT(const Object* obj) const;

    virtual size_t serialize(char* buffer, size_t bufferSize)
    {
        const static size_t vsize = sizeof(m_value);
        KASA_ASSERT(bufferSize >= vsize, "buffer space is not enough");
        memcpy(buffer, (char*)&m_value, vsize);
        return vsize;
    }

    virtual std::string toString()
    {
        return std::to_string(m_value);
    }

    double getValue() const
    {
        return m_value;
    }

    void setValue(const double&& value)
    {
        m_value = value;
    }

private:
    double m_value;
};

class ObjectString: public Object
{
public:
    ObjectString(const std::string&& value):
        m_value(value)
    {
        m_type = TYPE_STRING;
    }

    virtual bool cmpEQ(const Object* obj) const;
    virtual bool cmpNE(const Object* obj) const;
    virtual bool cmpLE(const Object* obj) const;
    virtual bool cmpLT(const Object* obj) const;
    virtual bool cmpGE(const Object* obj) const;
    virtual bool cmpGT(const Object* obj) const;

    virtual size_t serialize(char* buffer, size_t bufferSize)
    {
        size_t vsize = m_value.size();
        KASA_ASSERT(bufferSize >= vsize, "buffer space is not enough");
        memcpy(buffer, m_value.c_str(), vsize);
        return vsize;
    }

    virtual std::string toString()
    {
        return m_value;
    }

    std::string getValue() const
    {
        return m_value;
    }

    void setValue(std::string&& value)
    {
        m_value = value;
    }

private:
    std::string m_value;
};

#endif