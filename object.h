#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

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

    int getValue() const
    {
        return m_value;
    }

    void setValue(const int&& value)
    {
        m_value = value;
    }

    virtual bool cmpEQ(const Object* obj) const;
    virtual bool cmpNE(const Object* obj) const;
    virtual bool cmpLE(const Object* obj) const;
    virtual bool cmpLT(const Object* obj) const;
    virtual bool cmpGE(const Object* obj) const;
    virtual bool cmpGT(const Object* obj) const;

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

    double getValue() const
    {
        return m_value;
    }

    void setValue(const double&& value)
    {
        m_value = value;
    }

    virtual bool cmpEQ(const Object* obj) const;
    virtual bool cmpNE(const Object* obj) const;
    virtual bool cmpLE(const Object* obj) const;
    virtual bool cmpLT(const Object* obj) const;
    virtual bool cmpGE(const Object* obj) const;
    virtual bool cmpGT(const Object* obj) const;

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

    std::string getValue() const
    {
        return m_value;
    }

    void setValue(std::string&& value)
    {
        m_value = value;
    }

    virtual bool cmpEQ(const Object* obj) const;
    virtual bool cmpNE(const Object* obj) const;
    virtual bool cmpLE(const Object* obj) const;
    virtual bool cmpLT(const Object* obj) const;
    virtual bool cmpGE(const Object* obj) const;
    virtual bool cmpGT(const Object* obj) const;

private:
    std::string m_value;
};

#endif