/* @Copyright (c) 2019 by Yukun Xie
 *
 * ./object.h
 *
 * This file is part of the "KASA" project (Copyright (c) 2019 by Yukun Xie)
 * See "LICENSE.txt" for license information.
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <string.h>
#include <iostream>
#include "kasa_assert.h"

// triats object type from C++ builtin types
#define DECLARE_OBJECT_TYPE_TRIATS(PrimitiveType, Typename) \
template<>                                                  \
struct ObjectTypeTraits <PrimitiveType>                     \
{                                                           \
typedef Typename ObjectType;                                \
};

enum BuiltinType
{
    TYPE_INT,
    TYPE_DECIMAL,
    TYPE_STRING,
    //--------------------------------
    TYPE_COUNT
};

template<typename _Tp>
struct ObjectTypeTraits
{
    typedef _Tp ObjectType;
};

class ObjectInteger;
class ObjectDecimal;
class ObjectString;

DECLARE_OBJECT_TYPE_TRIATS(int, ObjectInteger)
DECLARE_OBJECT_TYPE_TRIATS(double, ObjectDecimal)
DECLARE_OBJECT_TYPE_TRIATS(std::string, ObjectString)

std::ostream &operator<<(std::ostream &out, const ObjectInteger &obj);
std::ostream &operator<<(std::ostream &out, const ObjectDecimal &obj);
std::ostream &operator<<(std::ostream &out, const ObjectString &obj);

class Object
{
  public:
    virtual ~Object()
    {
    }

    virtual BuiltinType getType() const
    {
        return m_type;
    }

    virtual std::string getTypeName() const
    {
        return "Object";
    }

    virtual std::string toString() const
    {
        return "";
    }

    virtual size_t serialize(char *buffer, size_t bufferSize)
    {
        return (size_t)0;
    }

    virtual bool cmpEQ(const Object *obj) const
    {
        return this == obj;
    }

    virtual bool cmpNE(const Object *obj) const
    {
        return this == obj;
    }

    virtual bool cmpLE(const Object *obj) const
    {
        return this <= obj;
    }

    virtual bool cmpLT(const Object *obj) const
    {
        return this < obj;
    }

    virtual bool cmpGE(const Object *obj) const
    {
        return this >= obj;
    }

    virtual bool cmpGT(const Object *obj) const
    {
        return this > obj;
    }

  protected:
    BuiltinType m_type;
};

class ObjectInteger : public Object
{
  public:
    ObjectInteger() : m_value(0)
    {
        m_type = TYPE_INT;
    }

    ObjectInteger(const int &value) : m_value(value)
    {
        m_type = TYPE_INT;
    }

    ObjectInteger(const int &&value) : m_value(value)
    {
        m_type = TYPE_INT;
    }

    virtual std::string getTypeName() const
    {
        return "ObjectInteger";
    }

    virtual size_t serialize(char *buffer, size_t bufferSize)
    {
        const static size_t vsize = sizeof(m_value);
        KASA_ASSERT(bufferSize >= vsize, "buffer space is not enough");
        memcpy(buffer, (char *)&m_value, vsize);
        return vsize;
    }

    virtual std::string toString() const
    {
        return std::to_string(m_value);
    }

    virtual bool cmpEQ(const Object *obj) const;
    virtual bool cmpNE(const Object *obj) const;
    virtual bool cmpLE(const Object *obj) const;
    virtual bool cmpLT(const Object *obj) const;
    virtual bool cmpGE(const Object *obj) const;
    virtual bool cmpGT(const Object *obj) const;

    int getValue() const
    {
        return m_value;
    }

    void setValue(const int &&value)
    {
        m_value = value;
    }

  private:
    int m_value;
};

class ObjectDecimal : public Object
{
  public:
    ObjectDecimal() : m_value(0)
    {
        m_type = TYPE_DECIMAL;
    }

    ObjectDecimal(const double &value) : m_value(value)
    {
        m_type = TYPE_DECIMAL;
    }

    ObjectDecimal(const double &&value) : m_value(value)
    {
        m_type = TYPE_DECIMAL;
    }

    virtual std::string getTypeName() const
    {
        return "ObjectDecimal";
    }

    virtual bool cmpEQ(const Object *obj) const;
    virtual bool cmpNE(const Object *obj) const;
    virtual bool cmpLE(const Object *obj) const;
    virtual bool cmpLT(const Object *obj) const;
    virtual bool cmpGE(const Object *obj) const;
    virtual bool cmpGT(const Object *obj) const;

    virtual size_t serialize(char *buffer, size_t bufferSize)
    {
        const static size_t vsize = sizeof(m_value);
        KASA_ASSERT(bufferSize >= vsize, "buffer space is not enough");
        memcpy(buffer, (char *)&m_value, vsize);
        return vsize;
    }

    virtual std::string toString() const
    {
        return std::to_string(m_value);
    }

    double getValue() const
    {
        return m_value;
    }

    void setValue(const double &&value)
    {
        m_value = value;
    }

  private:
    double m_value;
};

class ObjectString : public Object
{
  public:
    ObjectString() : m_value("")
    {
        m_type = TYPE_STRING;
    }

    ObjectString(const std::string &value) : m_value(value)
    {
        m_type = TYPE_STRING;
    }

    ObjectString(const std::string &&value) : m_value(value)
    {
        m_type = TYPE_STRING;
    }

    virtual std::string getTypeName() const
    {
        return "ObjectString";
    }

    virtual bool cmpEQ(const Object *obj) const;
    virtual bool cmpNE(const Object *obj) const;
    virtual bool cmpLE(const Object *obj) const;
    virtual bool cmpLT(const Object *obj) const;
    virtual bool cmpGE(const Object *obj) const;
    virtual bool cmpGT(const Object *obj) const;

    virtual size_t serialize(char *buffer, size_t bufferSize)
    {
        size_t vsize = m_value.size();
        KASA_ASSERT(bufferSize >= vsize, "buffer space is not enough");
        memcpy(buffer, m_value.c_str(), vsize);
        return vsize;
    }

    virtual std::string toString() const
    {
        return m_value;
    }

    std::string getValue() const
    {
        return m_value;
    }

    void setValue(const std::string &value)
    {
        m_value = value;
    }

    void setValue(const std::string &&value)
    {
        m_value = value;
    }

  private:
    std::string m_value;
};

#endif
